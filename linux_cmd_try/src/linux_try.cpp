# include "ros/ros.h"
#include <cstdlib>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "linux_try");

    system("mkdir ~/Music/kankan");
    system("vi ~/Music/kankan/youdianlihai.txt");
    return 0;
}