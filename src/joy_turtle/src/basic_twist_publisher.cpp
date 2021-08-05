#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

//rosrun joy joy_node  activate joy node
//rostopic echo /joy   show subscribing topic data

//to see a messege type and sub or pub
//rostopic info /joy

//to see messegetyp detail 
//rosmsg show sensor_msgs/Joy

//to see topic messege type
//rostopic type /joy





geometry_msgs::Twist cmd_vel;

void joy_callback(const sensor_msgs::Joy& joy_msg)
{
  cmd_vel.linear.x = joy_msg.axes[1];
  cmd_vel.linear.y = joy_msg.axes[0];
  cmd_vel.angular.z = joy_msg.axes[2];
  ROS_INFO("received");
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "basic_twist_publisher");
  ros::NodeHandle nh;
  ros::Publisher cmd_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
  ros::Subscriber joy_sub = nh.subscribe("joy", 10, joy_callback);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    cmd_pub.publish(cmd_vel);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}