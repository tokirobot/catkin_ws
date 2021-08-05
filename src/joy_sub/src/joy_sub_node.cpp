#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
//how to wireless connection 

//joycon test
//$ roscore
//$ rosrun joy joy_node
//$ rostopic echo /joy

//if you can not connect try rosrun joy joy_node , remove usb and attach usb

//sudo jstest /dev/input/js?
//see the roswiki
//$ rosdep install ps3joy
//$ rosmake ps3joy
//conect the usb and pscon
//$sudo bash
//$ rosrun ps3joy sixpair 
//$ rosrun ps3joy sixpair macadress(like 00:3d:f4:4g:....)
//remove the usb from pc
//# rosrun ps3joy ps3joy.py

//if several dongle connected
//# hciconfig
//if you connected as blootooth device , you must remove device from setting 
//you must go Setting and push blutooth on button

//if pscon is recognized as mouse
//xinput --list
//sudo apt purge xserver-xorg-input-joystic
//xinput set-prop 'Sony Playstation SixAxis/DS3' 'Device Enabled' 0

void joy_callback(const sensor_msgs::Joy &joy_msg)
{
  //wired connection
  ROS_INFO("axes[0] ST_L_LR:%f", joy_msg.axes[0]); 
  ROS_INFO("axes[1] ST_L_BF:%f", joy_msg.axes[1]); 
  ROS_INFO("axes[2] LEFT2:%f", joy_msg.axes[2]); 
  ROS_INFO("axes[3] ST_R_LR:%f", joy_msg.axes[3]);  
  ROS_INFO("axes[4] ST_R_BF:%f", joy_msg.axes[4]); 
  ROS_INFO("axes[5] RIGHT2:%f", joy_msg.axes[5]); 


  ROS_INFO("Button[0] CRO :%d", joy_msg.buttons[0]); 
  ROS_INFO("Button[1] ROU :%d", joy_msg.buttons[1]); 
  ROS_INFO("Button[2] TRY :%d", joy_msg.buttons[2]); 
  ROS_INFO("Button[3] SQU :%d", joy_msg.buttons[3]); 
  ROS_INFO("Button[4] LEFT1 :%d", joy_msg.buttons[4]); 
  ROS_INFO("Button[5] RIGHT1 :%d", joy_msg.buttons[5]); 
  ROS_INFO("Button[6] LEFT2 :%d", joy_msg.buttons[6]); 
  ROS_INFO("Button[7] RIGHT2 :%d", joy_msg.buttons[7]); 
  ROS_INFO("Button[8] SELECT :%d", joy_msg.buttons[8]); 
  ROS_INFO("Button[9] START :%d", joy_msg.buttons[9]); 
  ROS_INFO("Button[10] PAIR :%d", joy_msg.buttons[10]); 
  ROS_INFO("Button[11] LFET_AXES :%d", joy_msg.buttons[11]); 
  ROS_INFO("Button[12] RIGHT_AXES :%d", joy_msg.buttons[12]); 
  ROS_INFO("Button[13] CROK_N :%d", joy_msg.buttons[13]); 
  ROS_INFO("Button[14] CROK_S :%d", joy_msg.buttons[14]); 
  ROS_INFO("Button[15] CROK_W :%d", joy_msg.buttons[15]);
  ROS_INFO("Button[16] CROK_E :%d", joy_msg.buttons[16]);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "joy_sub_node");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("joy", 10, joy_callback);
  ros::Rate loop_rate(5);

  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}