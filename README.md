# linux_serial_assamble_ros_vrpn_client
ubuntu版本20.04 ros1
使用前需要安装 ros-melodic-vrpn
              ros-melodic-serial 功能包
 
              
              
使用步骤：
1.在linux桌面下建立catkin_ws文件夹，进入catkin_ws文件夹,在该文件架下打开终端 ，执行下面的命令
git clone https://github.com/LWL0857/linux_serial_assamble_ros_vrpn_client.git
2将clone得到的文件夹linux_serial_assamble_ros_vrpn_client改名为src
进入src文件夹，打开终端，执行
catkin_init_workspace
3.进入catkin_ws文件夹，打开终端，输入
catkin_make
编译完成
4.执行
source devel/setup.bash
roslaunch vrpn_client_ros sample.launch
可以启动launch文件来启动
