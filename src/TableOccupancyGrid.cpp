#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h" //library of rgbd scan
#include "nav_msgs/OccupancyGrid.h"

using namespace std;

float ranges[106];

// publisher declaration
ros::Publisher pub;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg){

	for(int i = 0; i < 106 ; i++){
		ranges[i] = msg -> ranges[i]; 
	}

	nav_msgs::OccupancyGrid map;

	for(int i = 0; i < 106 ; i++){
		map.data[i] = ranges[i]; 
	}

	pub.publish(map);

}

int main(int argc, char ** argv){

    ros::init(argc, argv, "occupancy_grid");
	
	// the NodeHandle is used for handling the communication with the ROS system
	// ( it is an object wich rapresents the ROS node ).
	ros::NodeHandle n;
	
	// subscription to the /rgbd_scan topic
	ros::Subscriber sub = n.subscribe("/rgbd_scan",1000,scanCallback);

	pub = n.advertise<nav_msgs::OccupancyGrid>("/map",1000);
	
	// it blocks the main thread from exiting until ROS invokes a shutdown.
	ros::spin();

    return 0;
}


