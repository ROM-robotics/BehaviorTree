#ifndef ROM_BT_BUMPGO_ISOBSTACLE_HPP_
#define ROM_BT_BUMPGO_ISOBSTACLE_HPP_

#include <string>
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "sensor_msgs/msg/laser_scan.hpp"
#include "rclcpp/rclcpp.hpp"

namespace rom_bt_bumpgo 
 {
    class IsObstacle : public BT::ConditionNode
    {
        public:
            explicit IsObstacle(const std::string &xml_tag_name, const BT::NodeConfiguration & conf);
            BT::NodeStatus tick();
            static BT::PortsList providedPorts()
            {
                return BT::PortsList(
                    {
                        BT::InputPort<double>("distance")
                    }
                );
            }

            void laser_callback(sensor_msgs::msg::LaserScan::UniquePtr msg);

        private:
            rclcpp::Node::SharedPtr node_;
            rclcpp::Time last_reading_time_;
            rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;
            sensor_msgs::msg::LaserScan::UniquePtr last_scan_;
    };
}

#endif