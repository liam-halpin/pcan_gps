# PCAN_GPS

## 1) Installing ROS Packages

Ensure the following ROS packages are installed correctly:
    * socketcan_bridge
    * socketcan_interface
    * can_msgs
    * std_msgs

Some of these may come with your ROS installation, but if you wish to install them seperately, run the following command:

``` $> sudo apt install ros-<distro>-<package> ```

## 2) Initialising VCAN

The instructions to setup VCAN are also embedded in the code.  You can use these by uncommenting the lines, or run them yourself in a terminal.  You may need to install the 'can-utils' package first.  Just run:

``` $> sudo apt-get install can-utils ```

Then, run the following commands to setup the device:

``` $> sudo modprobe can_dev ```
``` $> sudo modprobe can ```
``` $> sudo modprobe can_raw ```
``` $> sudo modprobe vcan ```
``` $> sudo modprobe peak_pci ```

To initialise the 'vcan' device:


``` $> sudo ip link add dev vcan0 type vcan ```
``` $> sudo ip link set vcan0 up ```


To bring down the link (to reset):


``` $> sudo ip link set vcan0 down ```
``` $> sudo ip link delete vcan0 ```


## 3) Creating and Running the Package

To build the package first navigate to the ~/catkin_ws folder on your file system:

``` $> cd ~/catkin_ws ```

Then, run:

``` $> catkin_make ```

This will build the package using catkin.

To run the package:

``` $> rosrun pcan_gps ```


## 4) Output

The output of the should be:

``` Data matches! ```