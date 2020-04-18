// 加载必要文件，注意Service_ex的加载方式
# include "ros/ros.h"
# include "service_ex/Greeting.h"
# include "string"

/*******service服务节点的实现*******
 *①初始化（节点命名、创建句柄）
 *②创建server，指定提供的服务名称，和对应回调函数
 *③编写回调函数
 *④利用spin执行回调函数
 */



// 定义请求处理函数
//service_ex是一个命名空间，Greeting是一个类，Request、Response是指向结构体的一个指针，定义在.h文件中
bool handle_function(service_ex::Greeting::Request &req,
					service_ex::Greeting::Response &res)
{
	// 输出，表示已经收到了服务请求
	ROS_INFO("Request from %s with age %d ", req.name.c_str(), req.age);
	
	// 通过res的feedback返回一个值，完成服务
	res.feedback = "Hi " + req.name + ". I'm server!";			//string类可以用加法处理字符串；
	return true;
}


int main(int argc, char **argv)
{
	// 初始化节点，命名为"greetings_server"
	ros::init(argc, argv, "greetings_server");
	ros::NodeHandle nh;

	ros::ServiceServer ser = nh.advertiseService("greetings", handle_function);
		/* 定义service的server端,命名为ser
		 *service名称为greetings
		 *收到request请求之后传递给handle_function进行处理
		 */

	ros::spin();	//查看并执行队列中的回调函数，完成服务

	return 0;
}