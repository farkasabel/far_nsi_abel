cmake_minimum_required(VERSION 3.8)
project(far_nsi_abel)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Függőségek
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

set(ament_dependencies
  rclcpp
  std_msgs
  geometry_msgs
)

# 1. Node: Fahrenheit Publisher
add_executable(fahrenheit_publisher src/fahrenheit_publisher.cpp)
ament_target_dependencies(fahrenheit_publisher ${ament_dependencies})

# 2. Node: Celsius Converter
add_executable(celsius_converter src/celsius_converter.cpp)
ament_target_dependencies(celsius_converter ${ament_dependencies})

# Telepítési szabályok (Executable-ök és Launch mappa)
install(TARGETS
  fahrenheit_publisher
  celsius_converter
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()