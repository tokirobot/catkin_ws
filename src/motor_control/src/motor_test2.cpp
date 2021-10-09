#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/String.h"
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termio.h>
#include <unistd.h>
#include <stdio.h>

//std_msgs::String cro;
std_msgs::Int32MultiArray cro_n,cro_s,cro_w,cro_e,stp_c,mtcmd;

int a=0;
int frontflag=0;
int backflag=0;
int rightflag=0;
int leftflag=0;
int stopcmd=0;

void motorjoycallback(const sensor_msgs::Joy &joy_msg){
    //int i=0;
    //i=joy_msg.buttons[14];
    
       
       // stp_c.data[0]=10;
        //stp_c.data[1]=joy_msg.buttons[0];
        //stopcmd=joy_msg.buttons[0];

        //cro_n.data[0]=20;
        //cro_n.data[1]=joy_msg.buttons[13];
        
    frontflag=joy_msg.buttons[13];
    mtcmd.data[0]=frontflag;


   
        //cro_s.data[0]=30;
        //cro_s.data[1]=joy_msg.buttons[14];
        
    
    backflag=joy_msg.buttons[14];
    mtcmd.data[1]=backflag;

 
        //cro_e.data[0]=40;
        //cro_e.data[1]=joy_msg.buttons[15];
        
    
     rightflag=joy_msg.buttons[15];   
     mtcmd.data[2]=rightflag;


        //cro_w.data[0]=50;
        //cro_w.data[1]=joy_msg.buttons[16];
        
    
    leftflag=joy_msg.buttons[16];
    mtcmd.data[3]=leftflag;

//mtcmd.data[4]=20;
//mtcmd.data[5]=30;
//mtcmd.data[6]=40;


   /* if(frontflag==1)
    mtcmd.data[4]=20;
    else
    mtcmd.data[4]=21;

    if(backflag==1)
    mtcmd.data[5]=30;
    else
    mtcmd.data[5]=31;

    if(rightflag==1)
    mtcmd.data[6]=40;
    else
    mtcmd.data[6]=41;

    if(leftflag==1)
    mtcmd.data[7]=50;
    else
    mtcmd.data[7]=51;*/

    

    

   // ROS_INFO("joy callback");
   // l2.data[0]=joy_msg.axes[5];
    //ROS_INFO("l2 :%lf",l2.data[0]);
  //  std::cout<<cro_n;
    //std::cout<<cro_s;
    //cro.data = (char)i*810;
}
void stm_rcv_callback(const std_msgs::Float32MultiArray &f_msg){
    /*for(int i=0; i<4 ;i++){
        ROS_INFO("receive from stm %lf",f_msg.data[i]);
    }*/
    //ROS_INFO("receive from stm %lf",f_msg.data[2]);
    //ROS_INFO("l2 :%lf",l2.data[0]);
    //ROS_INFO("-------------------------------------");
    
}

int main (int argc, char **argv){
    ros::init(argc, argv , "motor_test2");
    ros::NodeHandle nh;
    //ros::Subscriber receive = nh.subscribe("")
    ros::Subscriber joy_sub = nh.subscribe("joy", 10, motorjoycallback);
    ros::Subscriber re_stm = nh.subscribe("Serial_pub_float", 50, stm_rcv_callback);
    ros::Publisher motorcmd = nh.advertise<std_msgs::Int32MultiArray>("Serial_sub_int", 10);
   // cro_n.data.resize(2);
    //cro_s.data.resize(2);
    //cro_w.data.resize(2);
    //cro_e.data.resize(2);
    //stp_c.data.resize(2);
    mtcmd.data.resize(8);
    ros::Rate loop_rate(10);
    ROS_INFO("motor_test2");


    while(ros::ok()){
       
         /*if (frontflag==1){
             motorcmd.publish(cro_n);

         }
         
       
       
         if (backflag==1){
             motorcmd.publish(cro_s);

         }
         

         if (leftflag==1){
             motorcmd.publish(cro_w);

         }
         if (rightflag==1){
             motorcmd.publish(cro_e);

         }
         if (stopcmd==1){
             motorcmd.publish(stp_c);
         }*/
         motorcmd.publish(mtcmd);


         
         
         //ROS_INFO("send %lf",l2.data[0]);
       
        ros::spinOnce();
        loop_rate.sleep();
         //ROS_INFO("motor_test2");

    }
    return 0;


}
