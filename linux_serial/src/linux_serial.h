#ifndef LINUX_SERIAL_H
#define LINUX_SERIAL_H

#include <ros/ros.h>
#include <ros/time.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <serial/serial.h>
extern void openserial(const std::string& serial_name,const std::string& port_baurdrate);
extern void serial_callback(const geometry_msgs::PoseStamped::ConstPtr &msg);
extern void write_pose_and_orientation(double positionX, double positionY, double positionZ,
                                       double orientationX, double orientationY, double orientationZ, double orientationW);
unsigned char getCrc8(unsigned char *ptr, unsigned short len);
extern bool read_pose_and_orientation(double &positionX_rec, double &positionY_rec, double &positionZ_rec,
                                      double &orientationX_rec, double &orientationY_rec, double &orientationZ_rec, double &orientationW_rec);

#endif
