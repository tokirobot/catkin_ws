#include <ros/ros.h>
#include <tutorial_topic/Int32Stamped.h>

static tutorial_topic::Int32Stamped g_number;

void onNumberSubscribed(const tutorial_topic::Int32Stamped &msg){
    g_number=msg;
}

int main(int argc, char **argv){
    //initialize ros node
    ros::init(argc,argv,"subscriber");
    ros::NodeHandle nh;
    //configure the topic subsucribed and register the callback function
    ros::Subscriber sub=nh.subscribe("number",10,onNumberSubscribed);
    ros::Rate loop_rate(1);
    while(ros::ok()){
        //convince callback que
        ros::spinOnce();
        ROS_INFO("Number : %d , Time : %lf",g_number.data, g_number.header.stamp.toSec());
        loop_rate.sleep();

    }
    return 0;
}
