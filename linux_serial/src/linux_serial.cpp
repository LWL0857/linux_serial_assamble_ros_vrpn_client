#include "linux_serial.h"
#include <serial/serial.h>
using namespace std;

serial::Serial ser; // 串口变量

/********************************************************
            串口发送接收相关常量、变量、共用体对象
********************************************************/
const unsigned char ender[2] = {0x0d, 0x0a};
const unsigned char header[2] = {0x55, 0xaa};

// 发送动捕接收的数据给飞控 共用体
union sendData
{
    double d;
    unsigned char data[8];
} positionX_mocap, positionY_mocap, positionZ_mocap,
    orientationX_mocap, orientationY_mocap, orientationZ_mocap, orientationW_mocap;

// 接收飞控数据给linux 共用体
union receiveData
{
    double d;
    unsigned char data[8];
} positionX_rec_32, positionY_rec_32, positionZ_rec_32, orientationX_rec_32, orientationY_rec_32, orientationZ_rec_32, orientationW_rec_32;
unsigned char buf[62] = {0}; //

// 打开串口
/********************************************************
函数功能：串口参数初始化
入口参数：无
出口参数：
********************************************************/
void openserial(const std::string& serial_name,const std::string& port_baurdrate)
{
    int32_t temp = std::stoi(port_baurdrate);
    try
    {
        ser.setPort(serial_name);                              // 设备端口号
        ser.setBaudrate(temp);                                  // 波特率
        serial::Timeout t = serial::Timeout::simpleTimeout(1000); // 这个应该是超时，但是是必须的！！
        ser.setTimeout(t);
        ser.open(); // 打开串口
    }
    catch (serial::IOException &e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
    }
    if (ser.isOpen())
    {
        ROS_INFO("OPEN");
    }
}
/********************************************************
函数功能：将动捕接收的数据，打包发送给下位机
入口参数：pose and orientation
出口参数：
********************************************************/
void write_pose_and_orientation(double positionX, double positionY, double positionZ,
                                double orientationX, double orientationY, double orientationZ, double orientationW)
{
    int i, length = 0;
    positionX_mocap.d = positionX; // mm/s
    positionY_mocap.d = positionY;
    positionZ_mocap.d = positionZ;
    orientationX_mocap.d = orientationX;
    orientationY_mocap.d = orientationY;
    orientationZ_mocap.d = orientationZ;
    orientationW_mocap.d = orientationW;
    // 数据传输的数据头
    for (i = 0; i < 2; i++)
        buf[i] = header[i]; // buf[0]  buf[1]

    // 将动捕数据移动到buf中
    length = 56;
    buf[2] = length; // buf[2]

    memcpy(&buf[3], &positionX_mocap.data, 8);
    memcpy(&buf[11], &positionY_mocap.data, 8);
    memcpy(&buf[19], &positionZ_mocap.data, 8);
    memcpy(&buf[27], &orientationX_mocap.data, 8);
    memcpy(&buf[35], &orientationY_mocap.data, 8);
    memcpy(&buf[43], &orientationZ_mocap.data, 8);
    memcpy(&buf[51], &orientationW_mocap.data, 8);
    // 设置校验值、消息尾
    buf[3 + length] = getCrc8(buf, 3 + length); // buf[59]
    buf[3 + length + 1] = ender[0];             // buf[60]
    buf[3 + length + 2] = ender[1];             // buf[61]

    // 通过串口下发数据
    ser.write(buf, 62);
}
/********************************************************
函数功能：从下位机读取数据发送给ubuntu
入口参数：pose and orientation
出口参数：bool
********************************************************/
bool read_pose_and_orientation(double &positionX_rec, double &positionY_rec, double &positionZ_rec,
                               double &orientationX_rec, double &orientationY_rec, double &orientationZ_rec, double &orientationW_rec)
{
    char i, length = 0;
    unsigned char checkSum;
    unsigned char buf[150] = {0};
    size_t w = ser.available(); // 串口缓存区字节数
    if (w != 0)
    {
        ser.read(buf, w);
        w = 0;
    }

    // 检查信息头
    if (buf[0] != header[0] || buf[1] != header[1]) // buf[0] buf[1]
    {
        ROS_ERROR("Received message header error!");
        return false;
    }
    // 数据长度
    length = buf[2]; // buf[2]

    // 检查信息校验值
    checkSum = getCrc8(buf, 3 + length); // buf[10] 计算得出
    if (checkSum != buf[3 + length])     // buf[10] 串口接收
    {
        ROS_ERROR("Received data check sum error!");
        return false;
    }
    // 读取控制标志位
    // 读取速度值
    memcpy(&positionX_rec_32.data, &buf[3], 8);
    memcpy(&positionY_rec_32.data, &buf[11], 8);
    memcpy(&positionZ_rec_32.data, &buf[19], 8);
    memcpy(&orientationX_rec_32.data, &buf[27], 8);
    memcpy(&orientationY_rec_32.data, &buf[35], 8);
    memcpy(&orientationZ_rec_32.data, &buf[43], 8);
    memcpy(&orientationW_rec_32.data, &buf[51], 8);

    positionX_rec = positionX_rec_32.d;
    positionY_rec = positionY_rec_32.d;
    positionZ_rec = positionZ_rec_32.d;
    orientationX_rec = orientationX_rec_32.d;
    orientationY_rec = orientationY_rec_32.d;
    orientationZ_rec = orientationZ_rec_32.d;
    orientationW_rec = orientationW_rec_32.d;
    return true;
}
/********************************************************
函数功能：获得8位循环冗余校验值
入口参数：数组地址、长度
出口参数：校验值
********************************************************/
unsigned char getCrc8(unsigned char *ptr, unsigned short len)
{
    unsigned char crc;
    unsigned char i;
    crc = 0;
    while (len--)
    {
        crc ^= *ptr++;
        for (i = 0; i < 8; i++)
        {
            if (crc & 0x01)
                crc = (crc >> 1) ^ 0x8C;
            else
                crc >>= 1;
        }
    }
    return crc;
}
