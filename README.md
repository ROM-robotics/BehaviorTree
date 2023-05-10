#####
clone to your ROS2 workspace
git clone git@github.com:BehaviorTree/BehaviorTree.CPP.git
colcon build 


ros2 pkg create test --build--type ament_cmake --dependencies behaviortree_cpp rclcpp
colcon build
 

