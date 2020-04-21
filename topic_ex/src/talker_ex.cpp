#include <ros/ros.h>        //每一个ROS文件都必须包含的头文件
#include <topic_ex/gps_ex.h>   //gps_ex.msg在编译之后会在工作空间下的devel/include/topic_ex文件夹下生成一个同名头文件
#include <string>
using std::string;
/*******topic发送节点的实现*******
 *①初始化（节点命名、创建句柄）
 *②通过.msg编译后得到的.h中定义的同名类，定义一个储存要发送消息的对象
 *③创建一个publisher，指定其名称、要发送的数据类型等
 *④设定发送周期，通过循环或其他方式实现数据的循环发送
 */
 
int main(int argc,char** argv){
    //初始化操作
    ros::init(argc, argv, "talker_ex");//对节点命名
    ros::NodeHandle nh_ex;         //创建一个句柄，实例化node,通过这个句柄就可以用来创建Pub、Sub、Ser等
                                //句柄名称nh是自定义的

    //读取参数服务器中的几个参数
    double cheng_x,cheng_y;
    string name;
    //nh_ex.getParam("upx",cheng_x);
    //ros::param:get("upx",cheng_x);    //该命令与上面一行功能相同
    nh_ex.param("/talker_ex/trans_set/upx",cheng_x,1.00);   //1.00为默认值
    nh_ex.param("/talker_ex/trans_set/upy",cheng_y,1.00);
    nh_ex.param<std::string>("/talker_ex/agv_info/agv_name",name,"Unknown");

    //在定义pub之前先设置定义储存值的msg，并初始化msg的值
    topic_ex::gps_ex msg;          //topic_ex是一个命名空间，gps是一个类，其定义是在gps.h中实现的
    msg.x=1.0;
    msg.y=1.0;
    msg.state="working";

    //创建publisher
    ros::Publisher pub = nh_ex.advertise<topic_ex::gps_ex>("gps_ex_info",1);
        /*ros::Publisher是用于创建一个publisher的类；
         *pub为该类定义的Publisher对象，自定义；
         *nh.advertise是一个模板，<> 中为msg的类型；
         *()中的两个参数分别为：要发送到的topic的名称、发送队列的长度（一般比较小）；该行可以自动生成gps_ex_info这个topic
         */

    //为了方便实现循环发布，定义一个循环控制对象
    ros::Rate loop_rate(1.0);       
        /*ros::Rate为ros提供的一个用于循环控制的类
         *这里定义了一个名为loop_rate的对象
         *对象的初始化值为发布频率，这里设置为1Hz
         */
    
    //循环发送
    while(ros::ok){     //ros::ok指ros处于运行状态，即只要ros在运行，该发送过程就持续工作

        //定时刷新param
        nh_ex.getParam("/talker_ex/trans_set/upx",cheng_x);
        nh_ex.getParam("/talker_ex/trans_set/upy",cheng_y);
        //nh_ex.getParam<std::string>("/talker_ex/agv_info/agv_name",name);
        nh_ex.param<std::string>("/talker_ex/agv_info/agv_name",name,"Unknown");   

        msg.x = cheng_x * msg.x;   //为了展示效果，使msg的值指数型变化
        msg.y = cheng_y * msg.y;
        ROS_INFO("Talker:GPS:x=%f,y=%f",msg.x,msg.y);   //通过屏幕显示msg，类似于printf
        ROS_INFO("The name of agv is %s",name.c_str());
        pub.publish(msg);               //发布消息
        loop_rate.sleep();              //根据定义的频率休眠相应时间
    }
    return 0;
}
