**# linux_serial_assamble_ros_vrpn_client**

# 环境依赖：

ubuntu版本20.04 ros1

 ros-melodic-vrpn
 ros-melodic-serial功能包

##  使用前置步骤：

安装ros1

```c++
sudo apt-get install  ros-melodic-vrpn
sudo apt-get install   ros-melodic-serial
```

###  1.查看使用自己的串口，并赋予权限

```
 lu@lu-INVALID:~$ ls -l /dev/ttyUSB*
 
crwxrwxrwx 1 root dialout 188, 0 4月 18 16:31 /dev/ttyUSB0`

lu@lu-INVALID:~$ sudo chmod 777 /dev/ttyUSB0
```

![2023-04-18 16-35-33屏幕截图](image/2023-04-18%2016-35-33%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

### 2.查看自己使用的串口助手是否支持自己定义波特率

如ch340波特率上限为115200,设置超过这个值会导致打不开串口



# 使用步骤：

### 1.在linux桌面下建立catkin_ws文件夹，进入catkin_ws文件夹,在该文件架下打开终端 ，执行下面的命令

```
git clone https://github.com/LWL0857/linux_serial_assamble_ros_vrpn_client.git
```

![image](image/2023-04-18%2009-52-53%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

### 2.将clone得到的文件夹linux_serial_assamble_ros_vrpn_client改名为src

![2023-04-18 10-01-47屏幕截图](image/2023-04-18%2010-01-47%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

![2023-04-18 10-03-05屏幕截图](image/2023-04-18%2010-03-05%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

进入src文件夹，**删除CMAKELIST.TXT(也就是下图里面和vrpn_client_ros并列的CMakelist.txt)**

![微信截图_20230418183548](image/%E5%BE%AE%E4%BF%A1%E6%88%AA%E5%9B%BE_20230418183548.png)

打开终端，执行

```
catkin_init_workspace
```





### 3.更改linux_serial/launch/linux_serial.launch文件

确认这三个参数，保存在linux_serial/launch/linux_serial.launch中

![2023-04-18 16-34-38屏幕截图](image/2023-04-18%2016-34-38%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

 serial_subscribe_topic_name是订阅的刚体话题名

serial_using_name是串口名

 port_baurdrate是串口波特率



### 4.进入catkin_ws文件夹，打开终端，输入

```
catkin_make
```

编译完成



### 5.执行

在上面编译的终端中执行下面

```
source devel/setup.bash
roslaunch vrpn_client_ros sample.launch
```

可以启动launch文件来启动

![2023-04-18 16-32-05屏幕截图](image/2023-04-18%2016-32-05%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

![2023-04-18 16-32-25屏幕截图](image/2023-04-18%2016-32-25%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

