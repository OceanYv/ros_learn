#include <ros/ros.h>
#include <topic_ex/gps_ex.h>
#include <std_msgs/Float32.h>

/*******topic接收节点的实现*******
 *①初始化（节点命名、创建句柄）
 *②创建subscriber，指定要接收的topic和回调函数
 *③编写回调函数
 *④利用spin执行回调函数
 */

//接收到数据之后调用的函数
void gpsCallback_ex(const topic_ex::gps_ex::ConstPtr &msg_ex){    //处理接收到的信息的回调函数，topic_ex是一个命名空间，gps是一个类，ConstPtr是指向结构体的一个指针，定义在gps.h文件中
    std_msgs::Float32 distance;         //Float32是ROS自定义的一个float类型，其为一个结构体，结构体中只有一个成员date
    distance.data= sqrt(pow(msg_ex->x,2)+pow(msg_ex->y,2));           //msg是一个指向结构体的指针，访问成员时用 ->
    ROS_INFO("Listener:Distance to origin = %f,state= %s",distance.data,msg_ex->state.c_str());        //c_str()是类string中的一个函数，用于返回字符串首地址；
}

int main(int argc, char *argv[]){
    //初始化操作
    ros::init(argc, argv, "listener_ex");
    ros::NodeHandle n_ex;

    //创建subscriber 
    ros::Subscriber sub_ex = n_ex.subscribe("gps_ex_info", 1, gpsCallback_ex);
        /*ros::Subscriber是用于创建Subscriber的类；
         *sub为该类定义的Subscriber对象，名称自定义；
         *n.advertise是一个模板；
         *()中的三个参数分别为：要监听topic的名称、队列的长度（一般比较小）、处理消息的回调函数的指针；
            回调函数：通过函数指针调用的函数；在本行执行完之后，回调函数会带着实参进入回调函数队列
         */

    /*如果想要向回调函数中传入参数，除了将参数设为全局变量之外，还可以使用C++ 的boost库中的boost::bind() 函数
    ros::Subscriber sub_ex = n_ex.subscribe("gps_ex_info", 1, boost::bind(gpsCallback_ex, _1, a));
        *boost::bind函数的传入参数如下：
        *第一个：回调函数名
        *第二个：占位符，为回调函数的参数msg占一个位置
        *第三+个：自己想要传入的参数
    对应的，定义回调函数的时候，也会发生相应的变化：
    void gpsCallback_ex(const topic_ex::gps_ex::ConstPtr &msg_ex, 自定义传入类型 自定义参数形参)*/
        
    ros::spin();        //反复查看并执行回调函数队列中的回调函数；
                        //ros::spin()为一个阻塞函数，会反复执行陷入死循环；ros::spinOnce()函数为非阻塞函数，只执行队列中的第一个回调函数；
    return 0;
}