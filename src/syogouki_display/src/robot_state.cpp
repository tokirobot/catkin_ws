#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

#include <string>
#include <math.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "robot_state");
  ros::NodeHandle nh;
  ros::Publisher joint_pub = nh.advertise<sensor_msgs::JointState>("joint_states", 10);

  ros::Rate loop_rate(100);
  int count = 0;
//you must write all joints in index
//otherwise your urdf model displaiied in rviz never move
  sensor_msgs::JointState js0;
  js0.name.resize(18);
  js0.name[0] = "xprismatic";
  js0.name[1] = "yprismatic";
  js0.name[2] = "xaxis";
  js0.name[3] = "yaxis";
  js0.name[4] = "zaxis";
  js0.name[5] = "2main_body";
  js0.name[6] = "left_front";
  js0.name[7] = "left_rear";
  js0.name[8] = "right_front";
  js0.name[9] = "right_rear";
  js0.name[10] = "2table";
  js0.name[11] = "turn_table";
  js0.name[12] = "first_link";
  js0.name[13] = "second_link";
  js0.name[14] = "hand_base";
  js0.name[15] = "hand_roll";
  js0.name[16] = "hand_yaw";
  js0.name[17] = "hand_pitch";

  while (ros::ok())
  {
    
    js0.header.stamp = ros::Time::now();


    //js0.name[1] = "body3_joint";
    js0.position.resize(18);
    js0.position[0] = 0;
    js0.position[1] = 0;
    js0.position[2] = 0;
    js0.position[3] = 0;
    js0.position[4] = 0;
    js0.position[5] = 0;
    js0.position[6] = 0;
    js0.position[7] = 0;
    js0.position[8] = 0;
    js0.position[9] = 0;
    js0.position[10] = 0;
    js0.position[11] = 3.14*(float)count / 500.0;
    js0.position[13] = 0;
    js0.position[14] = 0;
    js0.position[15] = 0;
    js0.position[16] = 0;
    js0.position[17] = 0;
    //js0.position[1] = 2.0 * (float)count / 40.0;
    joint_pub.publish(js0);
    count++;

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}