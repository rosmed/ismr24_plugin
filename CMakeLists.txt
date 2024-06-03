cmake_minimum_required(VERSION 3.8)
project(ismr24_plugin)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ignition-cmake2 REQUIRED)

include_directories( include )

# check with ign plugin --version and ign gazebo --version
ign_find_package( ignition-plugin1 REQUIRED COMPONENTS register )
ign_find_package( ignition-gazebo6 REQUIRED )

add_library( ismr24_system SHARED src/ismr24_system.cpp )

target_link_libraries( ismr24_system ignition-plugin1 ignition-gazebo6 )

install( DIRECTORY urdf DESTINATION share/${PROJECT_NAME} )
install( DIRECTORY launch DESTINATION share/${PROJECT_NAME} )
install( TARGETS ismr24_system LIBRARY DESTINATION lib )

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
