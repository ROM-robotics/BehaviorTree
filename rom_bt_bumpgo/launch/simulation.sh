#!/bin/bash

export TURTLEBOT3_MODEL=waffle
#export LD_LIBRARY_PATH=/home/mr_robot/turtlebot3_ws/build/rom_bt_bumpgo:$LD_LIBRARY_PATH

gnome-terminal --tab -- bash -c "ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py"

gnome-terminal --tab -- bash -c "ros2 launch turtlebot3_navigation2 navigation2.launch.py use_sim_time:=True"

gnome-terminal --tab -- bash -c "echo \"ros2 run rom_bt_bumpgo bt_bumpgo\" "

echo "Launched Gazebo and Navigation2 in separate gnome-terminal windows."
echo "You can close these terminals individually when you are finished."