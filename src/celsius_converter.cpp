#include <memory>
#include <cmath>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

class CelsiusConverter : public rclcpp::Node {
public:
  CelsiusConverter() : Node("celsius_converter") {
    subscription_ = this->create_subscription<std_msgs::msg::Float32>(
      "temperature_fahrenheit", 10,
      std::bind(&CelsiusConverter::topic_callback, this, std::placeholders::_1));
    
    publisher_ = this->create_publisher<std_msgs::msg::Float32>("temperature_celsius", 10);
    RCLCPP_INFO(this->get_logger(), "Celsius Converter Node elindult.");
  }

private:
  void topic_callback(const std_msgs::msg::Float32::SharedPtr msg) const {
    float fahrenheit = msg->data;
    float celsius = (fahrenheit - 32.0f) * 5.0f / 9.0f;
    celsius = std::round(celsius * 100.0f) / 100.0f;

    auto out_msg = std_msgs::msg::Float32();
    out_msg.data = celsius;
    
    RCLCPP_INFO(this->get_logger(), "Átváltva: %.2f °F -> %.2f °C", fahrenheit, celsius);
    publisher_->publish(out_msg);
  }

  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CelsiusConverter>());
  rclcpp::shutdown();
  return 0;
}