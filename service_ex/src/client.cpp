// 包含必要文件，注意Service文件的包含方式，我们定义的srv文件为Greeting.srv,在包含时需要写成Greeting.h
# include "ros/ros.h"
# include "service_ex/Greeting.h"

/*******service请求端节点的实现*******
 *①初始化（节点命名、创建句柄）
 *②创建client，请求的服务名称，和对应srv类型
 *③实例化request（定义一个Greeting对象，并赋值以发送请求）
 *④利用call函数获取服务，服务值通过③中定义的对象返回
 */

int main(int argc, char **argv)
{
	ros::init(argc, argv, "greetings_client");
	ros::NodeHandle nh;

	ros::ServiceClient cli = nh.serviceClient<service_ex::Greeting>("greetings");
	/*定义service的client端,命名为cli
	 *服务中srv的类型为service_ex::Greeting
	 *要接受的service名称为greetings
	 */

	// 实例化srv，设置其request消息的内容，这里request包含两个变量，name和age，见Greeting.srv
	service_ex::Greeting srv;
	srv.request.name = "HAN";
	srv.request.age = 20;

	//用于实现定时请求（增加演示效果）
	ros::Rate loop_rate(1.0);

	while (ros::ok()){
		if (cli.call(srv))
			// 注意我们的response部分中的内容只包含一个变量response，另，注意将其转变成字符串
			ROS_INFO("Response from server: %s", srv.response.feedback.c_str());
		else{
			ROS_ERROR("Failed to call service Service_ex");
			return 1;
		}
		loop_rate.sleep();//根据前面的定义的loop_rate,设置1s的暂停
	}
	return 0;
}