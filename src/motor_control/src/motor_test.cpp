#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/String.h"
//TOPIC(Publish Subscribe) can not use premitive type like 'int' 'float'  if you do so, you can not publish data to topic
//you must use lapper messege type not 'int' but 'Int32'  (float  Float32   char  Char) 
/*error: request for member ‘__getMD5Sum’ in ‘m’, which is of non-class type ‘const int’
     return m.__getMD5Sum().c_str();*/


//std::String   and    std_mdgs::String
//std_msgs::Int32MultiArray cro;

//command 
//conect usb with pc a
//sudo bash 
//# hciconfig
//# rosrun ps3joy sixpair 68:3E:26:EA:FA:D2
//remove usb from pc
//# rosrun ps3joy ps3joy.py
//if pscon is recognized as mouse
//xinput --list
//sudo apt purge xserver-xorg-input-joystic
//xinput set-prop 'Sony Playstation SixAxis/DS3' 'Device Enabled' 0
//connect micro controler
//sudo chmod 666 /dev/ttyACM0(open oort)
//stanby ok!!
//if you want to see data from microcontroler
//cu -s 9600 -l /dev/ttyACM0()

std_msgs::String cro;
void motorjoycallback(const sensor_msgs::Joy &joy_msg){
    //motorcmd.publish(joy_msg.buttons[0]);
    int i=0;
    i=joy_msg.buttons[14];
    cro.data = (char)i;
    //int i=0;
    /*for(std::vector<int>::const_iterator it = cro->data.begin(); it != cro->data.end(); ++it)
    {
        cro[i] = *it;
        i++;
    }*/

}
void receivecallback(const std_msgs::String &rdata){

    ROS_INFO("%s",rdata.data);
  
}


int main (int argc , char **argv){
    ros::init(argc, argv, "motor_test");

    ros::NodeHandle nh;
    ros::Subscriber joy_sub = nh.subscribe("joy", 10, motorjoycallback);
    ros::Subscriber serial_receivedata = nh.subscribe("Serial_in", 100, receivecallback);
    //ros::Publisher motorcmd = nh.advertise<std_msgs::Int32MultiArray>("Serial_sub_int", 10);
    ros::Publisher motorcmd = nh.advertise<std_msgs::String>("Serial_out", 10);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    motorcmd.publish(cro);
    ros::spinOnce();
    loop_rate.sleep();
  }
    return 0;
}