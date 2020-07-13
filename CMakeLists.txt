## Tested Using ROS Noetic

cmake_minimum_required(VERSION 3.0.2)
project(pcan_gps)

## Find catkin and any catkin packages
find_package(
  catkin REQUIRED COMPONENTS
  can_msgs
  roscpp
  rospy
  socketcan_bridge
  socketcan_interface
  std_msgs
)

## Generate added messages and services
generate_messages(
  DEPENDENCIES
  can_msgs
  std_msgs
)

## Declare a catkin package
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES pcan_gps
  CATKIN_DEPENDS can_msgs roscpp rospy socketcan_bridge socketcan_interface std_msgs
  DEPENDS system_lib
)

## Build subscriber
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(pcan_gps src/pcan_gps.cpp)
target_link_libraries(pcan_gps ${catkin_LIBRARIES})
add_dependencies(pcan_gps pcan_gps)