#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv){
    ros::init(argc, argv, "tf_listener");
    ros::NodeHandle nh;

    ros::service::waitForService("spawn");
    ros::ServiceClient add_turtle = nh.serviceClient<turtlesim::Spawn>("spawn");

    srand(getpid());
    turtlesim::Spawn srv;
    srv.request.x = rand()%10;
    srv.request.y = rand()%10;
    srv.request.theta = 0;
    add_turtle.call(srv);

    ros::Publisher turtle_vel = nh.advertise<geometry_msgs::Twist>("turtle2/cmd_vel",10);
    tf::TransformListener listener;
    double scale_linear = 0.5 , scale_angular = 4.0;
    nh.param("scale_linear",scale_linear,scale_linear);
    nh.param("scale_angular",scale_angular,scale_angular);  

    ros::Rate rate(10.0);

    while(nh.ok()){

        tf::StampedTransform transform;

        try{
            listener.waitForTransform("/turtle2", "/turtle1", ros::Time(0), ros::Duration(3.0));
            listener.lookupTransform("/turtle2", "/turtle1", ros::Time(0), transform);
        }
        catch (tf::TransformException &ex){
            ROS_INFO("%s", ex.what());
            ros::Duration(1.0).sleep();
            continue;

        }

        geometry_msgs::Twist vel_msg;
        vel_msg.angular.z = scale_angular*atan2(transform.getOrigin().y(), transform.getOrigin().x());
        vel_msg.linear.x = scale_linear*sqrt(pow(transform.getOrigin().x(),2)+pow(transform.getOrigin().y(),2));
        turtle_vel.publish(vel_msg);

        rate.sleep();

    }  
    return 0;



    
}