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

#include "ros/ros.h"
#include "ros/console.h"
#include "dgvmsg/Encounter.h"
#include "dgvmsg/EncounterV.h"

#include "std_msgs/String.h"

//#include "usbcandev.h"
#include "usbcandevMode.hpp"
#include "zmqclient.h"


#define NODENAME "usbcannode"

unsigned int  s2n(const char *s){
	unsigned int l = strlen(s);
	unsigned int v = 0;
	unsigned int h = ((l > 2) && (s[0] == '0' )&& (s[1] == 'x' || s[1] == 'X'));
	unsigned char c;
	unsigned char t;
	
	if (!h) return atoi(s);
	if (l > 10) return 0;
	for (s += 2; c = *s; s++)
	{
		if (c >= 'A' && c <= 'F') c += 32;
		if (c >= '0' && c <= '9') t = c - '0';
		else if (c >= 'a' && c <= 'f') t = c - 'a' + 10;
		else return 0;
		v = (v << 4) | t;
	}
	return v;
}

int main(int argc, char **argv)
{
   	ros::init(argc, argv, NODENAME);
	boost::shared_ptr< ros::NodeHandle> handel(new ros::NodeHandle); 
	
	std::string   band="0x1600";   //800K

		
//������ӡ
if (argc < 2) {
	printf("usbcannode [Baud]\n"
		"    example: usbcannode 0x1400 \n"
		"                  |  | | |0x1400-1M, 0x1c03-125K, ....\n"
		);
	return 0;
}


	//������ʼ��
	//������
			unsigned int iband =s2n(argv[1]);
			
			if((iband>=0x1400)&&(iband <= 0x1c03)){
				
				}
			else{
				std::cout<<"iband  wrong ! "<<std::endl;		
				return 0;	
				}	
	
	
	usbcandevMode UsbCanDev(iband);
	// pub 

	UsbCanDev.Can1Recvpub = handel->advertise<std_msgs::String>("can1Recv", 320);
	ROS_INFO("  usbcannode Initialization Can1Recvpub  [topic = %s] port  is ok","can1Recv");
	

	UsbCanDev.Can2Recvpub = handel->advertise<std_msgs::String>("can2Recv", 320);
	
	ROS_INFO("  usbcannode Initialization Can2Recvpub  [topic = %s] port  is ok","can2Recv");
	

	UsbCanDev.LCEncounterpub = handel->advertise<dgvmsg::EncounterV>("DriverEncounterS", 10);
	
	ROS_INFO("  usbcannode Initialization LCEncounterpub  [topic = %s] port  is ok","DriverEncounterS");

	// SUB
	//����ʹ��CAN1���ͳ�ȥ������
	ros::Subscriber rossub_send_can1 =
		handel->subscribe("sendcan1", 40, &usbcandevMode::can1_ros_sendCall,&UsbCanDev);
	ROS_INFO("  usbcannode Initialization rossub_send_can1  [topic = %s] port  is ok","sendcan1");

	//����ʹ��CAN2���ͳ�ȥ������
	ros::Subscriber rossub_send_can2 =
		handel->subscribe("sendcan2", 40, &usbcandevMode::can2_ros_sendCall,&UsbCanDev);
	
	ROS_INFO("  usbcannode Initialization rossub_send_can2  [topic = %s] port  is ok","sendcan2");

        //boost::thread t1(boost::bind(&usbcandevMode::usbcandevMode_master,&UsbCanDev));  
	 boost::thread t1(boost::bind(&usbcandevMode::usbcandevMode_mastercan1,&UsbCanDev));  	
	 boost::thread t2(boost::bind(&usbcandevMode::usbcandevMode_mastercan2,&UsbCanDev)); 
	 boost::thread t3(boost::bind(&usbcandevMode::usbcandevMode_Pubencounter,&UsbCanDev));  
	ros::spin();		   
       t1.join();
       t2.join();
	t3.join();	
        return 0;


}





