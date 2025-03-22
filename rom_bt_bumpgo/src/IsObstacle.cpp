#include <string>
#include <utility>
#include "rom_bt_bumpgo/IsObstacle.hpp"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "rclcpp/rclcpp.hpp"

namespace rom_bt_bumpgo
{
    using namespace std::chrono_literals;
    using namespace std::placeholders;

    IsObstacle::IsObstacle( const std::string &xml_tag_name, const BT::NodeConfiguration &conf ) : BT::ConditionNode(xml_tag_name, conf)
    {
        config().blackboard->get("node", node_);
        laser_sub_ = node_->create_subscription<sensor_msgs::msg::LaserScan>("/scan", 100, std::bind(&IsObstacle::laser_callback, this, _1));
        last_reading_time_ = node_->now();
    }

    void 
    IsObstacle::laser_callback(sensor_msgs::msg::LaserScan::UniquePtr msg)
    {
        last_scan_ = std::move(msg);
    }

    BT::NodeStatus
    IsObstacle::tick()
    {
        if( last_scan_ == nullptr )
        {
            return BT::NodeStatus::FAILURE;
        }

        double distance = 1.0;
        getInput("distance", distance);

        if( last_scan_->ranges[last_scan_->ranges.size() / 2] < distance )
        {
            return BT::NodeStatus::SUCCESS;
        } else {
            return BT::NodeStatus::FAILURE;
        }
    }
}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
    factory.registerNodeType<rom_bt_bumpgo::IsObstacle>("IsObstacle");
}