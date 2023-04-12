cmake_minimum_required(VERSION 2.8.3)
project(linux_serial)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  std_msgs
  serial
)


catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES topic_example
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)



add_executable(linux_serial_node src/linux_serial_node.cpp 
			    src/linux_serial.cpp)
target_link_libraries(linux_serial_node ${catkin_LIBRARIES})

