#include <ignition/gazebo/System.hh>

#include <ignition/transport/Node.hh>
#include <ignition/gazebo/Model.hh>

class ismr24_system:
  public ignition::gazebo::System,
  public ignition::gazebo::ISystemConfigure,
  public ignition::gazebo::ISystemPreUpdate,
  public ignition::gazebo::ISystemUpdate,
  public ignition::gazebo::ISystemPostUpdate {

private:

  ignition::transport::Node node;

  ignition::gazebo::Entity joint;
  std::string joint_name;

  double joint_speed{0};
  ignition::gazebo::Model model{ignition::gazebo::kNullEntity};

  bool enabled;

public:

  ismr24_system();
  ~ismr24_system();

  void callback( const ignition::msgs::Boolean& msg );
  
  void Configure( const ignition::gazebo::Entity& entity,
		  const std::shared_ptr<const sdf::Element>& sdf,
		  ignition::gazebo::EntityComponentManager& ecm,
		  ignition::gazebo::EventManager& eventmgr ) override;

  void PreUpdate( const ignition::gazebo::UpdateInfo& info,
		  ignition::gazebo::EntityComponentManager& ecm ) override;
  void Update( const ignition::gazebo::UpdateInfo& info,
	       ignition::gazebo::EntityComponentManager& ecm ) override;
  void PostUpdate( const ignition::gazebo::UpdateInfo& info,
		   const ignition::gazebo::EntityComponentManager& ecm ) override;
  
};
