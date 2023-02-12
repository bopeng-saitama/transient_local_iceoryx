#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include "interfaces/msg/static_size_array.hpp"
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("transient_local_pub_loan");

  rclcpp::Publisher<interfaces::msg::StaticSizeArray>::SharedPtr pub = node->create_publisher<interfaces::msg::StaticSizeArray>("/loan_topic", rclcpp::QoS(5).reliable().transient_local());

  auto msg = pub->borrow_loaned_message();
  msg.get().data = {"transient_local_test"};
  pub->publish(std::move(msg));

  rclcpp::spin(node);

  rclcpp::shutdown();

  return 0;
}
