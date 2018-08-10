#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>



#include "zmqclient.h"
#include "message.hpp"
#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "dgvmsg/ctrl_ModeMessage.h"
#include "dgvmsg/DriverVelocity.h"
#include "dgvmsg/Encounter.h"
#include "dgvmsg/EncounterV.h"
#include "dgvmsg/DriverStatues.h"


#include "message.hpp"
#include "synctronDriver.hpp"

#define RECV_WAITE_TIME 10
#define RECV_NO_COUNTER 3
#define SEND_WAITE_TIME 5

#define ROSIN 1
#define MAXSPEEDRPM 3000
#define LIFECOM 2000

using namespace std;
using namespace boost;


class synctronDriver;


class OnlineLogMessage
{
public:
       int online;
       boost::posix_time::ptime time_recvnow;  
       boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;
       OnlineLogMessage()
       	{
		online = 0; 
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
	            if(sec>=2){
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
	
       
};

class sytronDriverMode
{
public:    
   enum dev_add{
            MYADD  =100,
            DEV_DIR_ADD_LF =100,
            DEV_DIR_ADD_LB =102,
            DEV_DIR_ADD_RF =101,
            DEV_DIR_ADD_RB =103,
    };
	enum DEV_FUN{
	    FUN_INIT=1,   
	    FUN_SPEEDLOOP, 
	    FUN_KEEPERROR, 
	    FUN_RELEASE,   
	    FUN_ENABLE,
	    FUN_CLEARERROR,
	    FUN_EMERAGENCE,
	    FUN_STOPRUN,
	    FUN_REENABLE,
	    FUN_DEFAULT,
	   };
    enum ONLINE{
	FN_ONLINE=1,
	FN_LOST=0
        };
	
      typedef      short                  int16; 
    typedef      short                  INT16; 
    typedef    unsigned short int       uint16; 
    typedef    unsigned short int       UINT16; 
    
    typedef    int                      int32; 
    typedef    int                      INT32; 
    typedef    unsigned int             uint32; 
    typedef    unsigned int             UINT32;
private:
    sytronDriverMode(const sytronDriverMode& rhs);
    sytronDriverMode& operator=(const sytronDriverMode& rhs);
    

public:

    sytronDriverMode(unsigned int port);
    sytronDriverMode(unsigned int port,int devadd,int dir);
	
    ~sytronDriverMode();

	void sytronDriverMode_master();
	//void sytronDriverMode_test();
	
	
	void print_dec(unsigned char *datBUF,int Num);
	void print_hex(std::string str);


	void DevCtrlDisEndable();
	void DevCtrleEndable();
	void DevGetActPos();

	void DevGetUdc();
	void DevGetVelocity();
	void GetCruError();
	void DevSetspeed(short int vec_speed);
	void DevGetDin();
	void DevGetCurCurent();
	void GetSpeedCmd();
	void DevSetClearError();
	void DevSetLifeGuard(short int timeout);
	void DevSetCmdStop();
	void DevEmergencyStop();

	void InitGetDevParam();
	int DriveInit();
	void DriveSpeedCtrl(short int  vec_speed);
	void DriveSpeedCtrl();

	int DriveRelease();
	int DriveEnable();
	int DriveREEnable();
	int DriveClearError();
	int DriveStop();
	int DriveEmergencyStop();

	
	
public: //ROS	
	ros::Publisher rospub_mode_driverstatues;
	

	ros::Publisher rospub_CAN_sendcmd;	
#ifdef ROSIN
	void SetSpeed(short int speed);
	void SpeedClear();
	
	void Net2Ctrl_driverCall(const dgvmsg::DriverVelocity::ConstPtr& cmdmsg);
	void Net2SCtrl_driverCall(const std_msgs::String::ConstPtr& ctrlcmd);
	void Can1Recv_driverCall(const std_msgs::String::ConstPtr& msg);
	void Can2Recv_driverCall(const std_msgs::String::ConstPtr& msg);
	
	void CAN_EncounterCall(const dgvmsg::EncounterV::ConstPtr& msg);
	
	//void dirv_pub_encounter();
	//void dirv_pub_allstatues();
	//std::string  Pack_driver_statues();
	void Pack_driver_msg_statues();
	
	int check_recv5bits(std::string &data) ;

	void dirv_pub_CAN_sendcmd(std::string cmd);
	
	
	
	
#endif

private:
	unsigned int  canport;

	OnlineLogMessage onlineMsg;
	
	synctronDriver driverprco;
	unsigned char DEV_add;

	int statues_ptr;
	short int   velocity;  //速度指令

	

};





