#include <string>
#include <iostream>

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"

#include "rom_bt_bumpgo/Turn.hpp"

namespace rom_bt_bumpgo
{
    using namespace std::chrono_literals;

    Turn::Turn(const std::string &xml_tag_name, const BT::NodeConfiguration & conf) : BT::ActionNodeBase(xml_tag_name, conf)
    {
        config().blackboard->get("node", node_);
        vel_pub_  = node_->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    }

    void Turn::halt() {};

    BT::NodeStatus
    Turn::tick()
    {
        if( status() == BT::NodeStatus::IDLE )
        {
            start_time_ = node_->now();
        }

        geometry_msgs::msg::Twist msg;
        msg.angular.z = 0.5;
        vel_pub_->publish(msg);

        auto elapsed = node_->now() - start_time_;
        
        if( elapsed < 3s )
        {
            return BT::NodeStatus::RUNNING;
        } else {
            return BT::NodeStatus::SUCCESS;
        }
    }
}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
    factory.registerNodeType<rom_bt_bumpgo::Turn>("Turn");
}