 #ifndef ROM_BT_BUMPGO_FORWARD_HPP_
 #define ROM_BT_BUMPGO_FORWARD_HPP_

 #include <string>
 #include "behaviortree_cpp_v3/behavior_tree.h"
 #include "behaviortree_cpp_v3/bt_factory.h"
 
 #include "geometry_msgs/msg/twist.hpp"
 #include "rclcpp/rclcpp.hpp"

 namespace rom_bt_bumpgo 
 {
    class Forward : public BT::ActionNodeBase 
    {
        public:
            explicit Forward(const std::string &xml_tag_name, const BT::NodeConfiguration & conf);

            void halt() {};

            BT::NodeStatus tick();

            static BT::PortsList providedPorts() {
                return BT::PortsList({});
            }

        private:
            rclcpp::Node::SharedPtr node_;
            rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub_;
    };
}
#endif