/**
 * PCAN-GPS Code
 * 
 * Tested using ROS Noetic
 */



#include <ros/ros.h>
#include <socketcan_bridge/socketcan_to_topic.h>
#include <socketcan_bridge/topic_to_socketcan.h>
#include <socketcan_interface/socketcan.h>
#include <socketcan_interface/dummy.h>
#include <can_msgs/Frame.h>
#include <std_msgs/String.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

/**
 * 1.) Make sure everything is installed (if this doesn't work, just run
 * 'sudo' commands from the terminal)
 */

// system(sudo modprobe can_dev);
// system(sudo modprobe can);
// system(sudo modprobe can_raw);
// system(sudo modprobe vcan);
// system(sudo modprobe peak_pci);
// system(sudo apt-get install can-utils);

/**
 * 2.) Initialise 'vcan' device:
 */
// system(sudo ip link add dev vcan0 type vcan);
// system(sudo ip link set vcan0 up);

/**
 * 3.) Function to simulate data
 */
std_msgs::Header simulator() {
    std_msgs::Header msg_header;
    uint32_t id = 0x29F;
    bool is_rtr = 0;
    bool is_extended = 0;
    bool is_error = 0;
    uint8_t dlc = 8;
    int data[8];      // array with 8 random ints [0, 99]

    srand((unsigned)time(0));
    for (int i=0; i<8; i++) {
        data[i] = (rand() % 100);
    }
    return msg_header;
}

/**
 * 4.) Callback function that checks if received data matches simulated data
 */
void valid_data(const std_msgs::Header sim_data, std_msgs::Header pcan_received) {
    bool valid = 1;
    for (int i=0; i<8; i++) {
        if (sim_data != pcan_received) {
            valid = 0;
        }
    }
    if (valid) {
        ROS_INFO("Data matches!");
    } else {
        ROS_INFO("Data doesn't match!");
    }
}

/**
 * 5.) Main function simulates data, publishes it, sends it to 'vcan' device, reads it
 * back from the 'vcan' device and validates results
 */
int main(int argc, char **argv) {
    ros::init(argc, argv, "pcan_data");     // initialise ROS
    
    ros::NodeHandle n;      // initialise node

    std_msgs::Header sim_data = simulator();    // simulate sensor data

    ros::Publisher pcan_data_sim = n.advertise<std_msgs::Header>("messages", 10);    // initialise publisher object

    pcan_data_sim.publish(sim_data);      // publish data to sent_messages (can_msgs/Frame)


    // socketcan_bridge::TopicToSocketCAN::TopicToSocketCAN.setup("vcan0");     // transfer data from topic to 'vcan' device
    // socketcan_bridge::SocketCANToTopic("vcan0");     // transfer data from 'vcan' device to topic
    ros::Subscriber pcan_received = n.subscribe("messages", 10, valid_data);     // read data from topic and validate it

    ros::spin();

    return 0;
}

/**
 * To bring down the link to reset:
 * - sudo ip link set vcan0 down
 * - sudo ip link delete vcan0
 */