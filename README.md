<div><b><u># linux_serial_assamble_ros_vrpn_client</u></b><br /><span style="font-size: 20px;">环境依赖：</span><br /><span style="color: rgb(158, 15, 48);"><u>ubuntu版本20.04 ros1</u><br /><span style="background-color: rgb(255, 255, 255);"><u>ros-melodic-vrpn</u><br /><u>&nbsp;ros-melodic-serial</u></span></span>功能包<br /><span style="font-size: 20px;">&nbsp;使用前置步骤：</span><br />&nbsp;1.查看使用自己的串口，并赋予权限<br />&nbsp;lu@lu-INVALID:~$<span style="color: rgb(158, 15, 48);"> ls -l /dev/ttyUSB*</span><br />crwxrwxrwx 1 root dialout 188, 0 4月&nbsp; 18 16:31 /dev/ttyUSB0<br />lu@lu-INVALID:~$ <span style="color: rgb(158, 15, 48);">sudo chmod 777 /dev/ttyUSB0</span></div><div><br /></div><div>2.查看自己使用的串口助手是否支持自己定义波特率<br />如ch340波特率上限为115200,设置超过这个值会导致打不开串口<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <br /><span style="font-size: 20px;">使用步骤：</span><br />1.在linux桌面下建立catkin_ws文件夹，进入catkin_ws文件夹,在该文件架下打开终端 ，执行下面的命令<br /><span style="color: rgb(158, 15, 48);">git clone https://github.com/LWL0857/linux_serial_assamble_ros_vrpn_client.git</span><br />2将clone得到的文件夹linux_serial_assamble_ros_vrpn_client改名为src<br />进入src文件夹，删除CMAKELIST.TXT，打开终端，执行<br /><span style="color: rgb(158, 15, 48);">catkin_init_workspace</span><br />3.进入catkin_ws文件夹，打开终端，输入<br /><span style="color: rgb(158, 15, 48);">catkin_make</span><br />编译完成<br />4.执行<br /><span style="color: rgb(158, 15, 48);">source devel/setup.bash<br />roslaunch vrpn_client_ros sample.launch</span><br />可以启动launch文件来启动<br /><br /></div>
![image](
https://github.com/LWL0857/linux_serial_assamble_ros_vrpn_client/blob/main/image/2023-04-18%2016-35-33%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png
)
![image](
https://github.com/LWL0857/linux_serial_assamble_ros_vrpn_client/blob/main/image/2023-04-18%2016-34-38%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png
)

