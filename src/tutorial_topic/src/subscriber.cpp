#include <ros/ros.h>
//#include <std_msgs/Int32.h>
#include<tutorial_topic/Int32Stamped.h>
/*void onNumberSubscribed(const std_msgs::Int32 &msg){
    ROS_INFO("KIKOETA!!! [%d]", msg.data);
}*/
void onNumberSubscribed(const tutorial_topic::Int32Stamped &msg){
    ROS_INFO("KIKOERU~~!:[%ld],  timestamp:[%lf]",msg.data,msg.header.stamp.toSec());
}

int main (int argc , char **argv){
    ros::init(argc, argv, "subscriber");
    ros::NodeHandle nh;
    ros::Subscriber sub=nh.subscribe("number", 10,onNumberSubscribed);
    //printf("");
    ros::spin();
    return 0;
    
}