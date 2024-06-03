#include <ismr24_system/ismr24_system.hpp>

#include <ignition/plugin/Register.hh>

#include <ignition/gazebo/components/JointVelocityCmd.hh>

ismr24_system::ismr24_system(){
  std::cout << "constructor" << std::endl;
  enabled=true;
  joint = 0;
}
ismr24_system::~ismr24_system(){}

void ismr24_system::Configure( const ignition::gazebo::Entity& entity,
			    const std::shared_ptr<const sdf::Element>& sdf,
			    ignition::gazebo::EntityComponentManager&,
			    ignition::gazebo::EventManager&){

  std::cout << "configure" << std::endl;
  model = ignition::gazebo::Model(entity);

  std::cout << sdf->ToString("element") << std::endl;

  if( sdf->HasElement("max_velocity") ){
    const double maxVel = sdf->Get<double>("max_velocity");
    std::cout << "max velocity: " << maxVel << std::endl;
  }

  if( sdf->HasElement("topic") ){
    std::string topic = sdf->Get<std::string>("topic");
    std::cout << "topic: " << topic << std::endl;
    if( node.Subscribe(topic, &ismr24_system::callback, this ) ){
      std::cout << "Created subscriber" << std::endl;
    }
  }

  auto ptr = const_cast<sdf::Element*>(sdf.get());
  if( sdf->HasElement("joint") ){
    joint_name = ptr->GetElement("joint")->Get<std::string>();
    std::cout << "joint: " << joint_name << std::endl;
  }
  
}

void ismr24_system::callback( const ignition::msgs::Boolean& msg ){
  std::cout << msg.data() << std::endl;
  enabled = msg.data();
}

void ismr24_system::PreUpdate( const ignition::gazebo::UpdateInfo&,
			    ignition::gazebo::EntityComponentManager& ecm ){
  if( joint == 0 ){
    joint = model.JointByName( ecm, joint_name );
    std::cout << "Model: " << model.Name(ecm)
	      << " has " << model.LinkCount(ecm)
	      << " links and " << model.JointCount(ecm)
	      << " joints " << std::endl;
  }

  auto vel = ecm.Component<ignition::gazebo::components::JointVelocityCmd>(joint);
  if( vel == nullptr ){
    ecm.CreateComponent(joint,ignition::gazebo::components::JointVelocityCmd({joint_speed}));
  }
  else{
    *vel = ignition::gazebo::components::JointVelocityCmd({joint_speed});
  }
  
}

void ismr24_system::Update( const ignition::gazebo::UpdateInfo&,
			 ignition::gazebo::EntityComponentManager& ){}

void ismr24_system::PostUpdate( const ignition::gazebo::UpdateInfo&,
			     const ignition::gazebo::EntityComponentManager&){

  static double t=0.0;
  if( enabled ){
    joint_speed = sin(t)/10;
    t+=0.001;
  }
  else{
    joint_speed = 0.0;
  }
  
}

IGNITION_ADD_PLUGIN( ismr24_system,
		     ignition::gazebo::System,
		     ismr24_system::ISystemConfigure,
		     ismr24_system::ISystemPreUpdate,
		     ismr24_system::ISystemUpdate,
		     ismr24_system::ISystemPostUpdate )

