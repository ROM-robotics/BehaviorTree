#include <string>
#include <iostream>

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"

#include "rom_bt_bumpgo/Forward.hpp"

namespace rom_bt_bumpgo
{
    using namespace std::chrono_literals;

    Forward::Forward(const std::string &xml_tag_name, const BT::NodeConfiguration & conf) : BT::ActionNodeBase(xml_tag_name, conf)
    {
        config().blackboard->get("node", node_);
        vel_pub_  = node_->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    }

    BT::NodeStatus
    Forward::tick()
    {
        geometry_msgs::msg::Twist msg;
        msg.linear.x = 0.1;
        vel_pub_->publish(msg);

        return BT::NodeStatus::RUNNING;
    }
}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
    factory.registerNodeType<rom_bt_bumpgo::Forward>("Forward");
}