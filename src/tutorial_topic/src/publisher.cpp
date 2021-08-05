#include <ros/ros.h>
//#include <std_msgs/Int32.h>
#include<tutorial_topic/Int32Stamped.h>

// "/home/toki/catkin_ws/src/ros_start/include/**",
int main (int argc , char **argv){
    using tutorial_topic::Int32Stamped;
    ros::init(argc, argv, "publisher");
    //class to communicate with other nodes 
    ros::NodeHandle nh;
    //register the topics and buffuers
    //templete dao
    ros::Publisher pub=nh.advertise<Int32Stamped>("number",10);
    //ros::Publisher pub=nh.advertise<std_msgs::Int32>("number",10);
    /***constructor dayo***/
    ros::Rate loop_rate(1);
    Int32Stamped cnt;
    cnt.data=0;
    cnt.header.stamp=ros::Time::now();

    //std_msgs::Int32 cnt;
    //cnt.data=0;
    while(ros::ok()){
        ROS_INFO("count : %d", cnt.data);
        ROS_INFO("GIT");
        pub.publish(cnt);
        cnt.data++;
        cnt.header.stamp=ros::Time::now();
        loop_rate.sleep();

    }
    return 0;

}