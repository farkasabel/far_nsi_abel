#include <chrono>
#include <memory>
#include <random>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;

class FahrenheitPublisher : public rclcpp::Node {
public:
  FahrenheitPublisher() : Node("fahrenheit_publisher"), rd_(), gen_(rd_()), dist_(50.0, 100.0) {
    publisher_ = this->create_publisher<std_msgs::msg::Float32>("temperature_fahrenheit", 10);
    timer_ = this->create_wall_timer(1s, std::bind(&FahrenheitPublisher::timer_callback, this));
    RCLCPP_INFO(this->get_logger(), "Fahrenheit Publisher Node elindult.");
  }

private:
  void timer_callback() {
    auto message = std_msgs::msg::Float32();
    message.data = static_cast<float>(std::round(dist_(gen_) * 100.0) / 100.0);
    
    RCLCPP_INFO(this->get_logger(), "Mért érték: %.2f °F", message.data);
    publisher_->publish(message);
  }

  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::random_device rd_;
  std::mt19937 gen_;
  std::uniform_real_distribution<float> dist_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FahrenheitPublisher>());
  rclcpp::shutdown();
  return 0;
}