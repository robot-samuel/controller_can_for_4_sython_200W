#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>


#include "usbcandev.h"
#include "controlcan.h"
#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "dgvmsg/Encounter.h"
#include "dgvmsg/EncounterV.h"



using namespace std;
using namespace boost;


#define CAN1   0
#define CAN2   1

class OnlineLogMessage
{
public:
       int online;
 	int timeout;
       boost::posix_time::ptime time_recvnow;  
       boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;
       OnlineLogMessage()
       	{
		online = 0; 
		timeout = 2;
		time_recvnow = boost::posix_time::microsec_clock::universal_time();  
       	}
	int check_connect()
	{   

	    if(online == 1)
	        {
	            //
	             boost::posix_time::ptime now;
	            // 这里为微秒为单位;这里可以将microsec_clock替换成second_clock以秒为单位;  
	            now = boost::posix_time::microsec_clock::universal_time();
	            time_elapse = now - time_recvnow;
	            // 类似GetTickCount，只是这边得到的是2个时间的ticket值的差，以微秒为单位;  
	            int ticks = time_elapse.ticks();  
	            // 得到两个时间间隔的秒数;   
	            int sec = time_elapse.total_seconds();
	            if(sec>=timeout){
	                    online = 0;
	                }
	            
	        
		}
        return online;
	        
	} 

	int Set_connect()
	{   
              online=1;
                    // 这里为微秒为单位;这里可以将microsec_clock替换成second_clock以秒为单位;  
               time_recvnow = boost::posix_time::microsec_clock::universal_time();  
	        
	} 
	
	int Set_timeout(int time)
	{   
		timeout =  time;
	} 
	       
};

class usbcandevMode
{
    

private:
    usbcandevMode(const usbcandevMode& rhs);
    usbcandevMode& operator=(const usbcandevMode& rhs);
    

public:

   enum dev_add{
            MYADD  =100,
            DEV_DIR_ADD_LF =100,
            DEV_DIR_ADD_LB =102,
            DEV_DIR_ADD_RF =101,
            DEV_DIR_ADD_RB =103,
    };
	

   
    usbcandevMode(unsigned int rate);
	
    ~usbcandevMode();

	void set_Baud(unsigned int Baud );
	
	void usbcandevMode_master();
	void usbcandevMode_mastercan2();
	void usbcandevMode_mastercan1();
	void usbcandevMode_Pubencounter();

	//ros
	ros::Publisher Can1Recvpub;	
	ros::Publisher Can2Recvpub;	
	
	ros::Publisher LCEncounterpub;
		
	void can1_ros_sendCall(const std_msgs::String::ConstPtr& msg);
	void can2_ros_sendCall(const std_msgs::String::ConstPtr& msg);
	

	void ros_Can1Recvpub_SendRpc(std::string msg);
	void ros_Can2Recvpub_SendRpc(std::string msg);
	void ros_SendEncounterRpc();
	
	 void print_hex(std::string str,std::string com);
	
	std::string pop_cur_toarray(unsigned int id);
	void printf_frame(VCI_CAN_OBJ *can);
	  
private:
	
	int  bandrate;

	OnlineLogMessage onlineMsg;
	usbcandev candev;

	int LF_counter;
	int RF_counter;
	int LB_counter;
	int RB_counter;


	int SLF_counter;
	int SRF_counter;
	int SLB_counter;
	int SRB_counter;

	unsigned short int  m_LFDrivStatus;
	unsigned short int m_RFDrivStatus;

	unsigned short int m_LBDrivStatus;
	unsigned short int m_RBDrivStatus;

	unsigned short int  m_SLFDrivStatus;
	unsigned short int m_SRFDrivStatus;

	unsigned short int m_SLBDrivStatus;
	unsigned short int m_SRBDrivStatus;
	
	
	std::string can1_srecv;
	std::string can2_srecv;
};





