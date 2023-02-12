#include <functional>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include "interfaces/msg/static_size_array.hpp"

void sub_callback(const interfaces::msg::StaticSizeArray msg)
{
  fprintf(stderr, "Got message: %s\n", msg.data.data());
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("transient_local_sub_loan");

  rclcpp::Subscription<interfaces::msg::StaticSizeArray>::SharedPtr sub = node->create_subscription<interfaces::msg::StaticSizeArray>("/loan_topic", rclcpp::QoS(5).transient_local(), std::bind(&sub_callback, std::placeholders::_1));

  rclcpp::spin(node);

  rclcpp::shutdown();

  return 0;
}
