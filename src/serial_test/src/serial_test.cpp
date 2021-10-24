#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include "stdlib.h"
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


int open_serial(const char *device_name){
    int fd1=open(device_name, O_RDWR | O_NOCTTY | O_NONBLOCK);
    fcntl(fd1, F_SETFL,0);
    //load configuration
    struct termios conf_tio;
    tcgetattr(fd1,&conf_tio);
    //set baudrate
    speed_t BAUDRATE = B115200;
    cfsetispeed(&conf_tio, BAUDRATE);
    cfsetospeed(&conf_tio, BAUDRATE);
    //non canonical, non echo back
    conf_tio.c_lflag &= ~(ECHO | ICANON);
    //non blocking
    conf_tio.c_cc[VMIN]=0;
    conf_tio.c_cc[VTIME]=0;
    //store configuration
    tcsetattr(fd1,TCSANOW,&conf_tio);
    return fd1;
}

int fd1=0;
char endmsg = '\n';
char *inttochar;
int intdatasize = 0;

//you have to send data type char!
//c_str() convert string into char
void serial_callback(const std_msgs::String& serial_msg){
    //serial_msg.data==uart Transmission


    delete[] inttochar;
    intdatasize = serial_msg.data.size();
    inttochar = new char[intdatasize * 4 + 6];
    inttochar[0] = 'i';
    *(int *)(&inttochar[1]) = intdatasize;
    for (int i = 0; i < intdatasize; i++)
    {
        *(int *)(&inttochar[i * 4 + 5]) = serial_msg.data[i];
        //*(int *)inttochar[i + 2] = serial_msg.data[i];
        //memcpy(&inttochar[i * 4 + 5], &serial_msg.data[i], 4);
    }
    inttochar[intdatasize * 4 + 5] = endmsg;        

    //int rec=write(fd1,serial_msg.data.c_str(),serial_msg.data.size());
    int rec = write(fd1, inttochar, intdatasize * 4 + 6);

    if(rec>=0)printf("send:%s\n",serial_msg.data.c_str());
    else{
        ROS_ERROR_ONCE("Serial Fail: cound not write");
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "serial_test");
    ros::NodeHandle n;

    //Publisher
    ros::Publisher serial_pub = n.advertise<std_msgs::String>("Serial_in", 1000);

    //Subscriber
    ros::Subscriber serial_sub = n.subscribe("Serial_out", 100, serial_callback); 

    char device_name[]="/dev/ttyACM0";
    fd1=open_serial(device_name);
    if(fd1<0){
        ROS_ERROR("Serial Fail: cound not open %s", device_name);
        printf("Serial Fail\n");
        ros::shutdown();
    }

    ros::Rate loop_rate(200); 
    while (ros::ok()){
        char buf[256]={0};
        int recv_data=read(fd1, buf, sizeof(buf));
        
        if(recv_data>0){
            //printf("I received :%s\n",buf[0]);
            
            std_msgs::String serial_msg;
            serial_msg.data=buf;
            serial_pub.publish(serial_msg);
        }
        ros::spinOnce();
        loop_rate.sleep();
    } 
    return 0;
}
