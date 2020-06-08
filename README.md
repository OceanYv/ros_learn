# ros_learn

****说明****
	一些ros的基本操作；
	解压之后得到的src文件放在工作空间路径下，编译后运行；

****package说明****
service_ex:
	service通讯方式的练习例程，以此运行server和client即可；	

topic_ex:
	topic通讯方式的练习例程，以此运行server和client即可；

	同时也包含了launch和param的练习，可以通过launch文件运行两个节点，并通过两个窗口输出信息；
	param包括了数据的读取和字符串类型的读取和输出；
	程序会定时读取参数服务器数据，因此可以通过命令行更新param传输给程序；

	同时，也提供了回调函数传入自定义参数的使用方法；
	此外，若想要在回调函数中实现topic的发布，可以采用自定义class的方法，具体实现可以参考AGV/gp_agv/base_controller/pub_odom.c中的使用方法；
	subscribe函数可以有第四个输入参数，用于将所在类的对象实例的指针传给同类的回调函数；

linux_cmd_try:
	试着通过c++来运行linux命令:<roscore>，<rosrun linux_cmd_try linux_try>  
	以及Eigen的使用方法  

class_ex:  
	自定义类的使用方法，主要有三个注意点：
	1.头文件的引用，#include “包名/头文件名”
	2.在Cmakelist文件中，类对应的.h和.cpp文件应该用add_library
	3.调用类的可执行文件，要在target_link_libraries中加上类对应的库的名字

****param提供字符串类型数据的实现说明****
在yaml文件里面就简简单单定义一下就好了，关键是cpp文件中有几个地方要注意
①#include <string>       using std::string;			//这两行不能忘
②在读取参数服务器数据时，格式为：
	nodehandle_name.param<std::string>("param_path_and_name",string_name,"默认值");
③输出格式为：
	ROS_INFO("%s",string_name.c_str());
