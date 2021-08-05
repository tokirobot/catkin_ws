#include<ros/ros.h>

int main (int argc, char **argv){
    //initialize rosnode
    ros::init(argc,argv, "param_test");
    //ros
    ros::NodeHandle nh;
    //read the parameter
    std::string text = nh.param<std::string>("text", "Hello World");
    int repeat_times = nh.param<int>("repeat_times", 10);
    double frequency = nh.param<double>("frecency", 0.5);
    
    //configure the char disp frequency 
    //constructor : 
    ros::Rate loop_rate(frequency);
    
    //loop_rate.sleep();//HAL_delay() or delay()
    for(int i=0; i<repeat_times; i++){
        ROS_INFO("%s", text.c_str());
        loop_rate.sleep();
    }
    return 0;
    //bool ros::NodeHandle::getParam
    //void ros::NodeHandle::setParam
    //bool ros::NodeHandle::hasParam

//once you close roscore or terminal , parameter will reset
//rosparam dump [file].yaml ... save the file
//rosparam load [file].yaml ... read the file
//rosparam list             ... show parameter 



}