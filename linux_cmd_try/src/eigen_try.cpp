# include "ros/ros.h"
#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/Eigenvalues>
#include <linux_cmd_try/shishi.h>

using namespace Eigen;

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "eigen_try");

    Matrix3f Identity_matrix_;  //单位矩阵
    Identity_matrix_ = Matrix3f::Identity(3,3);
    Matrix<float, 6, 6> P66_,P66_inverse;
    

    P66_.block<3,3>(0,0) << Identity_matrix_;
    P66_.block<3,3>(3,3) << Identity_matrix_;
    P66_.block<3,3>(0,3) << Identity_matrix_;
    P66_.block<3,3>(3,0) << Identity_matrix_;

    P66_inverse =  P66_.inverse();
    
    std::cout<< P66_ << std::endl;
    std::cout<< std::endl;
    std::cout<< P66_inverse << std::endl;

    return 0;
}