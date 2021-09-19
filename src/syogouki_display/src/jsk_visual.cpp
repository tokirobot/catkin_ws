
#include <ros/ros.h>
#include <jsk_rviz_plugins/OverlayMenu.h>
#include <jsk_rviz_plugins/OverlayText.h>
#include <string>
#include "std_msgs/Int32.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Int32MultiArray.h"

enum mode {
    Asynchronous=1,
    Synchronous,
    DynamixelArm
};

enum speed {
  lowspeed=1,
  middlespeed,
  highspeed

};




int mode=0;
int speedmode=0;
int defaultspeed=0;

void operation_mode_callback(const std_msgs::Int32MultiArray &operation_mode){
  mode = operation_mode.data[0];
  defaultspeed = operation_mode.data[1];
  speedmode = operation_mode.data[2];
  
}



int main(int argc, char** argv)
{
  ros::init(argc, argv, "jsk_visual");
  ros::NodeHandle nh;


  ros::Subscriber operation_mode = nh.subscribe("operation_mode", 10, operation_mode_callback);
  ros::Publisher menu_pub = nh.advertise<jsk_rviz_plugins::OverlayMenu>("menu", 1);
  ros::Publisher menu_pub2 = nh.advertise<jsk_rviz_plugins::OverlayMenu>("menu2", 1);
  ros::Publisher float_pub = nh.advertise<std_msgs::Float32>("float32", 10);

  
  ros::Rate loop_rate(20);
  //bool flip = true;
  jsk_rviz_plugins::OverlayMenu menu;
  menu.menus.resize(3);
  menu.menus[0] = "Asynchronous";
  menu.menus[1] = "Synchronous";
  menu.menus[2] = "DynamixelArm";
  menu.title = "OPERARION MODE";

  jsk_rviz_plugins::OverlayMenu menu2;
  menu2.menus.resize(3);
  menu2.menus[0] = "LOW_SPEED";
  menu2.menus[1] = "MIDDLE_SPEED";
  menu2.menus[2] = "HIGH_SPEED";
  menu2.title = "ROTATE SPEED";

  std_msgs::Float32 float_data;
  int count = 0;

  menu.action = jsk_rviz_plugins::OverlayMenu::ACTION_SELECT;
  menu2.action = jsk_rviz_plugins::OverlayMenu::ACTION_SELECT;

  
   
  //int lowspeed=300;
  //int middlespeed=600;
  //int highspeed=900;
  int currentspeed=0;

  while (ros::ok())
  {
      

      //currentspeed=defaultspeed*speedmode;

      if (mode==Asynchronous)
        menu.current_index = 0;

      else if(mode==Synchronous)
        menu.current_index = 1;

      else if(mode==DynamixelArm)
        menu.current_index = 2;



      if (speedmode==lowspeed)
        menu2.current_index = 0;

      else if(speedmode==middlespeed)
        menu2.current_index = 1; 

      else if(speedmode==highspeed)
        menu2.current_index = 2; 

        menu_pub.publish(menu);
        menu_pub2.publish(menu2);

        //std_msgs::Float32 float_data;
        float_data.data = sin(0.02 * count * 2 * M_PI);
        float_pub.publish(float_data);

    count++;
        //flip = !flip;
        ros::spinOnce();
        loop_rate.sleep();
    }
  return 0;
}


