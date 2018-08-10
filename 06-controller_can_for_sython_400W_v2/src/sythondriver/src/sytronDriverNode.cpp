#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream> 

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/assign/list_of.hpp> //for ref_list_of  
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/progress.hpp>
#include <boost/program_options.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>



#include "sytronDriverMode.hpp"
#include "zmqclient.h"

#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "dgvmsg/ctrl_ModeMessage.h"
#include "dgvmsg/DriverVelocity.h"
#include "dgvmsg/Encounter.h"
#include "dgvmsg/EncounterV.h"
#include "dgvmsg/DriverStatues.h"

int main(int argc, char **argv)
{
   	ros::init(argc, argv, "SynthondriverNode");
	boost::shared_ptr< ros::NodeHandle> handel(new ros::NodeHandle); 

		
//参数打印
	std::cout<<"argc= "<<argc<<std::endl;
	for(int index=0;index<argc;index++){
			std::cout<<"argv"<<"["<<index<<"]= "<<argv[index]<<std::endl;
		}

	std::string argv_add=argv[1];
	std::string argv_com=argv[2];
	std::string argv_dir=argv[3];
	//端口

	unsigned int  COM=boost::lexical_cast<int>(argv_com);
	if((COM==CAN1)||(COM==CAN2)){

		}
	else{
		std::cout<<"argv_com  wrong ! "<<std::endl;
		return 0;
		}


	//驱动器地址
	int add = 1;
	try{  
		    add=boost::lexical_cast<int>(argv_add); // 将字符串转化为整数
		    if((add != sytronDriverMode::DEV_DIR_ADD_LF )&&
			(add != sytronDriverMode::DEV_DIR_ADD_LB )&&
			(add != sytronDriverMode::DEV_DIR_ADD_RF )&&
			(add != sytronDriverMode::DEV_DIR_ADD_RB )){
				std::cout<<"add wrong ! "<<(int)add<<std::endl;
				return 0;
		    	}
		}  
	catch(boost::bad_lexical_cast&)    // 转换失败会抛出一个异常  
		{  
		        add=0;
				std::cout<<"add wrong ! "<<std::endl;
			return 0;
		}
	//旋转方向
	int dir=0;
	try{  
		    dir=boost::lexical_cast<int>(argv_dir); // 将字符串转化为整数
		    if((dir != 1 )&&
			(dir != -1 )){
			std::cout<<"dir wrong ! "<<std::endl;
				return 0;
		    	}
		}  
	catch(boost::bad_lexical_cast&)    // 转换失败会抛出一个异常  
		{  
		        dir=0;
			std::cout<<"dir wrong ! "<<std::endl;
			return 0;
		}
	
	sytronDriverMode driver(COM,add,dir);
		
	

	// pub 
	driver.rospub_mode_driverstatues = handel->advertise<dgvmsg::DriverStatues>("Synthonfeedback", 10);
	std::string topic="Synthondriverencounter"+argv_add;	
	ROS_INFO("  Initialization rospub_mode_driverstatues [topic = %s] port  is ok",topic.c_str());
	


	ros::Subscriber rossub_CanRecv;	
	//发送命令
	if(COM == CAN1){
		driver.rospub_CAN_sendcmd = handel->advertise<std_msgs::String>("sendcan1", 10);
		ROS_INFO("[ %s ]Initialization rospub_CAN_sendcmd  [topic = %s] port  is ok",topic.c_str(),"sendcan1");
		
		rossub_CanRecv =
			handel->subscribe("can1Recv", 10,  &sytronDriverMode::Can1Recv_driverCall,&driver);
		ROS_INFO("[ %s ]Initialization rossub_CanRecv  [topic = %s] port  is ok",topic.c_str(),"can1Recv");	

		}
	else if(COM == CAN2){
		driver.rospub_CAN_sendcmd = handel->advertise<std_msgs::String>("sendcan2", 10);
		ROS_INFO("[ %s ]Initialization rospub_CAN_sendcmd  [topic = %s] port  is ok",topic.c_str(),"sendcan2");
		rossub_CanRecv = 
			handel->subscribe("can2Recv", 60, &sytronDriverMode::Can2Recv_driverCall,&driver);
		ROS_INFO("[ %s ]Initialization rossub_Can2Recv  [topic = %s] port  is ok",topic.c_str(),"can2Recv");			

		}



	
	//驱动模块刷新的状态数据
	ros::Subscriber rossub_mode_driver =
		handel->subscribe("Net2Ctrl", 10,  &sytronDriverMode::Net2Ctrl_driverCall,&driver);
	ROS_INFO("  SynthondriverNode Initialization rossub_mode_driver  [topic = %s] port  is ok","Net2Ctrl");

	ros::Subscriber rossub_mode_Sdriver = 
		handel->subscribe("Net2SCtrl", 10, &sytronDriverMode::Net2SCtrl_driverCall,&driver);
	ROS_INFO("  SynthondriverNode Initialization rossub_mode_Sdriver  [topic = %s] port  is ok","Net2SCtrl");

	ros::Subscriber rossub_encounter_Sdriver = 
		handel->subscribe("DriverEncounterS", 30, &sytronDriverMode::CAN_EncounterCall,&driver);
	ROS_INFO("  SynthondriverNode Initialization rossub_encounter_Sdriver  [topic = %s] port  is ok","DriverEncounterS");



	boost::thread t1(boost::bind(&sytronDriverMode::sytronDriverMode_master,&driver)); 

	
	ros::spin();
	t1.join();

              return 0;


}





