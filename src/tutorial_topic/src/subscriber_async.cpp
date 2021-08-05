#include <ros/ros.h>
#include <tutorial_topic/Int32Stamped.h>
#include <mutex>

//definition of global varuance
static tutorial_topic::Int32Stamped g_number;
static std::mutex g_mutex;

void onNumberSubscribed(const tutorial_topic::Int32Stamped &msg){
    //lock the mutex until function end
    std::lock_guard<std::mutex>lock(g_mutex);
    g_number=msg;
}

int main(int argc , char **argv){
    ros::init(argc, argv, "subscriber");
    //class to communicate with other nodes
    ros::NodeHandle nh;
    //configureing topic subscrib and register the callback function
    ros::Subscriber sub=nh.subscribe("number", 10, onNumberSubscribed);
    //configureing a span of loop
    ros::Rate loop_rate(1);
    //initialize AsyncSpinner
    //spiner(n) n...number of callback que 
    ros::AsyncSpinner spinner(1);
    spinner.start();
    while(ros::ok()){
        //lock the mutex
        g_mutex.lock();
        ROS_INFO("Number : %d, Time : %lf",g_number.data, g_number.header.stamp.toSec());
        //unlock the mutex
        g_mutex.unlock();
        //wait until loop span become 1 second
        loop_rate.sleep();

    }
return 0;


}

