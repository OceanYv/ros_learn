# ros_learn  
  
****说明****  
	主要是学习一些ros的基本操作；  
	解压之后得到的src文件放在工作空间路径下，编译后运行；  
*	__下面是为新手提供的示例命令,无需在github中自行下载压缩包，在终端运行__
	```  
	$ mkdir -p yhy_roslearn/src			//新建工作空间
	$ cd yhy_roslearn/src				//将当前路径设置为工作空间下的src文件夹
	$ git clone git@github.com:OceanYv/ros_learn.git		//从github上下载代码
	$ cd ..								//将当前路径设置为工作空间路径（返回上级）
	$ catkin_make						//编译，无报错即完成
	$ echo "source ~/yhy_roslearn/devel/setup.bash" >> ~/.bashrc		//添加到环境变量中
	$ source ~/.bashrc					//刷新环境变量
	_下面不是必须的操作_
	$ cd src
	$ tree								//查看代码文件结构
	```  

****package****  
*service_ex:  
	##service通讯方式的练习例程，依次运行server和client即可；
	```
	$ roscore
	打开一个新终端
	$ rosrun service_ex server
	打开一个新终端
	$ rosrun service_ex client
	```	

*topic_ex:  
	##topic通讯方式的练习例程，依次运行server和client即可；  
  	```
	$ roscore
	打开一个新终端
	$ rosrun topic_ex talker_ex
	打开一个新终端
	$ rosrun topic_ex listener_ex
	```	

	##同时也包含了launch和param的练习，可以通过launch文件运行两个节点，并通过两个窗口输出信息；  
	```
	关闭之前打开的终端
	$ roslaunch topic_ex topic_ex.launch
	```

	##param包括了数据的读取和字符串类型的读取和输出；  
	程序会定时读取参数服务器数据，因此可以通过命令行更新param传输给程序； 
	```
	$ roslaunch topic_ex topic_ex.launch	//先运行起来两个节点
	$ rosparam list 						//查看当前参数服务器中的参数
	$ rosparam set /talker_ex/agv_info/agv_name agv2	//修改参数，观察终端输出的变化
	``` 
  
*linux_cmd_try:  
	试着通过c++来运行linux命令:<roscore>，<rosrun linux_cmd_try linux_try>  
	以及Eigen的使用方法  
  
*class_ex:  
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
