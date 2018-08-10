

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



#include "sytronDriverMode.hpp"


#define  DEBUG_ECHO 0



sytronDriverMode::sytronDriverMode(unsigned int port)
{
 	
	canport = port;
	DEV_add = 1;
	driverprco.set_add(1);
	onlineMsg.Set_connect();

	
	
	
}
sytronDriverMode::sytronDriverMode(unsigned int port,int devadd,int dir)
{
 
	canport = port;


	//driverprco.Set_add((unsigned char)devadd);
	DEV_add = devadd;
	driverprco.set_add(devadd);
	driverprco.set_dir(dir);
	
	std::cout<<"port= "<<port<<std::endl;
	std::cout<<"devadd= "<<(int)devadd<<std::endl;
	std::cout<<"dir= "<<dir<<std::endl;

	onlineMsg.Set_connect();
	
	
	
}
sytronDriverMode::~sytronDriverMode()
{
	
}
/*
void sytronDriverMode::sytronDriverMode_test(){
	std::cout<< "hello sytronDriverMode_master "<<std::endl;
	ros::Rate loop_rate(1);
	while(ros::ok()){
			DevCtrlDisEndable();
			 loop_rate.sleep();

		}
}
*/

void sytronDriverMode::sytronDriverMode_master()
{
       std::cout<< "hello sytronDriverMode_master "<<std::endl;
        

       
         int preokstatues_ptr=0;
         int errorcount=0;
	int satas_count = 0;

        //初始化
            statues_ptr=FUN_INIT;
            preokstatues_ptr=statues_ptr;

            //设定速度
            //int vecspeed=1000;   

            SpeedClear();
            //获取参数
            InitGetDevParam();
             
         ros::Rate loop_rate(30);
		 
         try{
                    while(ros::ok()){
                     // time_now =  boost::posix_time::microsec_clock::universal_time();  
                      // std::cout<<"time_now:"<<time_now<<std::endl;
                        // boost::progress_timer pt; 
                        //伺服状态机                
                        switch(statues_ptr){
                                case FUN_INIT:
                                    //伺服使能
                                            if(DriveInit()){
                                           
                                                    statues_ptr=FUN_SPEEDLOOP;
                                                    errorcount=0;
                                                }
                                    break;
                                 case FUN_SPEEDLOOP:
                                      //发送速度
                                     DriveSpeedCtrl();
                                      errorcount=0;
                                    break;
                                case FUN_KEEPERROR:
                                    //伺服系统出错
                                    DevCtrlDisEndable();
					DevSetClearError();
                                    SpeedClear();
					//DevGetDin();
                                    //statues_ptr=0;
                                    errorcount=0;
                                    break;
                                case FUN_RELEASE:
                                    //伺服系统出错
                                    if(DriveRelease()){
                                            statues_ptr=FUN_DEFAULT;
                                        }

                                    errorcount=0;
                                    break; 
                                 case FUN_ENABLE:
                                     if(DriveEnable()){
                                            statues_ptr=FUN_SPEEDLOOP;
                                        }
                                        errorcount=0;
                                       break; 
                                case FUN_CLEARERROR:
                                      if(DriveClearError()){
                                              statues_ptr=FUN_DEFAULT;
                                           }
                                        errorcount=0;
                                         break; 
                                case FUN_EMERAGENCE:
                                        if(DriveEmergencyStop()){
                                               statues_ptr=FUN_DEFAULT;
                                           }
                                         errorcount=0;
                                         break; 
                                case FUN_STOPRUN:
                                          if(DriveStop()){
                                                  statues_ptr=FUN_DEFAULT;
                                             }
                                         errorcount=0;
                                         break; 
                                case FUN_REENABLE:
                                          if(DriveREEnable()){
                                                    statues_ptr=FUN_SPEEDLOOP;
                                              }
                                          errorcount=0;
                                         break; 

                                default:
					#if DEBUG_ECHO
				        std::cout << "FUN_DEFAULT is running"<<std::endl;
					#endif    
                                    DevGetCurCurent();
				      GetCruError();
					//DevGetDin();
                                    break;
                            }
                        
                        //驱动器状态失联
			onlineMsg.check_connect();			
			if(onlineMsg.online!=FN_ONLINE){
                          	statues_ptr=FUN_DEFAULT;
					      
                       }
                         //错误报警
			 				 
                          //检查是否有报警
                        for(int index=0 ; index < 1 ;index++){
                                     if((driverprco.m_BitStatus.bit3_isFault ==1) ||
						(driverprco.m_BitStatus.bit7_Warning == 1) ||
						(driverprco.m_BitStatus.bit5_EMGING == 1)){
						 std::cout<<(int)DEV_add<<":"<<driverprco.GetStrError()<<std::endl;
                                            //某一台电机出现故障
                                            statues_ptr=FUN_RELEASE;
                                           // if(errorcount%300==0){
                                                    // statues_ptr=0;
                                               // }
                                        }
                                     
                            } 
			
                        //所有状态OK
                        if((preokstatues_ptr != 0) &&(statues_ptr == 0)){
                                 int ok=0;
                            for(int index=0;index < 1 ;index++){
                               
                                if(onlineMsg.online!=FN_ONLINE){
                                             ok++;
                                              //std::cout<<'\a'<<std::endl;
                                    }

                                }  
                             if(ok == 1){
                                        // preokstatues_ptr  = 1;
                                         statues_ptr=preokstatues_ptr;
                                    }
                            }

			
                        //当速度控制模式时
                        if(statues_ptr ==FUN_SPEEDLOOP){
                             for(int index=0;index < 1 ;index++){
                                        if(driverprco.m_BitStatus.bit1_isENA_SRV !=1){
                                                //故障开环
                                                statues_ptr=FUN_INIT;
                                                
                                            }
                                    }                                  
                            }
                          
                            
			satas_count++;
			if(satas_count>=6){
				satas_count=0;
				//dirv_pub_allstatues();
				Pack_driver_msg_statues();
				}
                        
                        boost::this_thread::interruption_point();
                        loop_rate.sleep();
                     }
             }
        catch(boost::thread_interrupted&){
                 std::cout << "thread interrupt" << std:: endl;
             }
    

    
	
}


void sytronDriverMode::print_dec(unsigned char *datBUF,int Num)
{

 std::cout<< "print_dec:";
 for(std::size_t index=0;index<Num;index++){
                  int x=(unsigned  char)datBUF[index];
                   std::cout<<boost::format("%d ")%x;
              }
std::cout<<"\n";

}

  void sytronDriverMode::print_hex(std::string str)
 {
 	#if 1   
	int Num = str.size();
	const char * datBUF =  str.c_str();
	
  std::cout<< "["<<boost::format("%02X ")%(int)DEV_add<<"] print_recv hex:";
  for(std::size_t index=0;index<Num;index++){
                   int x=(unsigned  char)datBUF[index];
                    std::cout<<boost::format("%02X ")%x;
               }
 std::cout<<"\n";
 	#endif   

 }

void sytronDriverMode::DevCtrlDisEndable(){

	//发送
	dirv_pub_CAN_sendcmd(driverprco.Cmd_SetRealse());
	boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));	
}
void sytronDriverMode::DevCtrleEndable(){
	//发送
	dirv_pub_CAN_sendcmd(driverprco.Cmd_SetEnable());
	boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));	
	
}


void sytronDriverMode::DevGetActPos()
{
    //获取实际位置
	//发送
	dirv_pub_CAN_sendcmd(driverprco.Cmd_GetCruPos());
	boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));	

}



void sytronDriverMode::DevGetUdc(){
	//获取母线电压
	dirv_pub_CAN_sendcmd(driverprco.Cmd_GetUdc());
	boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));	      
}

void sytronDriverMode::DevGetVelocity()
{
    //获取实际速度
	//获取母线电压
	dirv_pub_CAN_sendcmd(driverprco.Cmd_GetVelocity());
	boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));	 



}

void sytronDriverMode::GetCruError(){

   //获取错误代码

        dirv_pub_CAN_sendcmd(driverprco.Cmd_GetError());
	boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));

}
void sytronDriverMode::DevSetspeed(short int vec_speed){
    
   
     //下发速度指令

        dirv_pub_CAN_sendcmd(driverprco.Cmd_SetVelocity(vec_speed));
	boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));

}
void sytronDriverMode::DevGetDin(){
	 //读取IO口状态
        dirv_pub_CAN_sendcmd(driverprco.Cmd_GetDinStatues());
	boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));     
}

void sytronDriverMode::DevGetCurCurent()
{
    //获取实际电机电流
        dirv_pub_CAN_sendcmd(driverprco.Cmd_GetCurrent());
	boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));    

}
void sytronDriverMode::GetSpeedCmd(){

    //获取速度指令
        dirv_pub_CAN_sendcmd(driverprco.Cmd_GetCmdVelocity());
	boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));    
}
void sytronDriverMode::DevSetClearError(){

    //清楚错误

        dirv_pub_CAN_sendcmd(driverprco.Cmd_SetClearError());
	boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));    
}

void sytronDriverMode::DevSetLifeGuard(short int timeout){
    
   
     //发送
        dirv_pub_CAN_sendcmd(driverprco.Cmd_SetLifeGuard(timeout));
	 boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));    
  
}


void sytronDriverMode::DevSetCmdStop(){
    
        dirv_pub_CAN_sendcmd(driverprco.Cmd_SetStop());
	 boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));  
}

void sytronDriverMode::DevEmergencyStop(){


        dirv_pub_CAN_sendcmd(driverprco.Cmd_QuickStop());
	boost::this_thread::sleep(boost::posix_time::milliseconds(SEND_WAITE_TIME));	

}



void sytronDriverMode::InitGetDevParam()
{
	//DevGetActPos();
	DevGetVelocity();
	DevGetUdc();
	GetCruError();
	//DevGetDrivStatus();
	DevCtrlDisEndable();
	DevSetspeed(0);
	//DevGetDin();
}

int sytronDriverMode::DriveInit()
{
	#if DEBUG_ECHO
        std::cout << "DriveInit is running"<<std::endl;
	#endif
        //获取初始状态
        
        DevSetClearError();
        SpeedClear();
	DevSetspeed(0);
	//使能	
       DevCtrleEndable();	
	GetCruError();
	DevGetCurCurent();   
	DevGetUdc();
	DevGetVelocity();
	 DevSetLifeGuard(LIFECOM);
	
    if( driverprco.m_BitStatus.bit1_isENA_SRV != 1 ){//没有使能
                    //DevCtrleEndable(vecpa);
                    return 0;
                }

      if(onlineMsg.online !=FN_ONLINE ){  //通信错误
                     return 0;
                 }
   

  	if(driverprco.GetStrError()!="OK"){  //驱动器报警
			 return 0;
		}     
        return 1;
}

void sytronDriverMode::DriveSpeedCtrl(short int  vec_speed)
{
        static int listcounter=0;
        
        int num=0;
      //  int recvsize=0; 
        listcounter++;
        //std::cout << "DriveSpeedCtrl is running"<<std::endl;
        //设置速度
        SetSpeed(vec_speed);
        DevSetspeed(velocity);
        DevGetCurCurent();   //电流
	 DevGetVelocity();  //实际速度
	 GetCruError();
}
void sytronDriverMode::DriveSpeedCtrl()
{
       // static int listcounter=0;
	#if DEBUG_ECHO
        std::cout <<(int)DEV_add<< " DriveSpeedCtrl is running"<<std::endl;
	#endif
      //  int num=0;
      //  int recvsize=0; 
      //  listcounter++;
        
        //设置速度
       // SetSpeed(vec_speed);
        DevSetspeed(velocity);
        DevGetCurCurent();   //电流
	 DevGetVelocity();  //实际速度
	 GetCruError();
	// DevGetDin();
}

int sytronDriverMode::DriveRelease()
{
	#if DEBUG_ECHO
        std::cout << "DriveRelease is running"<<std::endl;
	#endif
        GetCruError();
        DevCtrlDisEndable();
        DriveClearError();
	 DevSetspeed(0);
	SpeedClear();
        DevGetUdc();
	//DevGetDin();
	

        DevSetLifeGuard(LIFECOM);
       
            if( driverprco.m_BitStatus.bit1_isENA_SRV != 0 ){
                    //DevCtrleEndable(vecpa);
                    return 0;
                }

      if(onlineMsg.online !=FN_ONLINE ){
                     return 0;
                 }
         
        return 1;
}

int sytronDriverMode::DriveEnable()
{
	#if DEBUG_ECHO
        std::cout << "DriveEnable is running"<<std::endl;
	#endif

        //DevSetLifeGuard(0);
        DevCtrleEndable();
        //SpeedClear();

        DevGetUdc();
        DevGetCurCurent();
	//DevGetDin();
        GetCruError();
        DevSetLifeGuard(LIFECOM);     
		
      if( driverprco.m_BitStatus.bit1_isENA_SRV !=1 ){
                    //DevCtrleEndable(vecpa);
                    return 0;
                }
	if(onlineMsg.online !=FN_ONLINE ){
                     return 0;
                 }
	if(driverprco.m_BitStatus.bit3_isFault == 1){
			 return 0;
		}
        return 1;
        
}
int sytronDriverMode::DriveREEnable()
{
	#if DEBUG_ECHO
        std::cout << "DriveREEnable is running"<<std::endl;
        #endif
	//DevSetLifeGuard(0);
        
		
	DevCtrlDisEndable();
        DevSetClearError();
        GetSpeedCmd();

        //SpeedClear();

        DevGetUdc();
		
	DevCtrleEndable();
	DevSetspeed(0);
        GetCruError();
        DevGetCurCurent();
	//DevGetDin();
       DevSetLifeGuard(LIFECOM);
     
            if( driverprco.m_BitStatus.bit1_isENA_SRV !=1 ){
			#if DEBUG_ECHO
                    std::cout<<"DriveREEnable is  here #1 "<<std::endl;
			#endif
                 
                    return 0;
                }

	if(driverprco.GetStrError()!="OK"){
		#if DEBUG_ECHO
			 std::cout<<"DriveREEnable is  here #2 "<<driverprco.GetStrError()<<std::endl;
		#endif
			 return 0;
		}	
	
	if(onlineMsg.online !=FN_ONLINE ){
		#if DEBUG_ECHO
		      std::cout<<"DriveREEnable is  here #3 "<<std::endl;
		#endif
                     return 0;
                 }
        
        return 1;
        
}

int sytronDriverMode::DriveClearError()
{
	#if DEBUG_ECHO
       std::cout << "DriveClearError is running"<<std::endl;
	#endif
        
        //DevEncRst(vecpa);
        //DevSetLifeGuard(0);
        
	DevSetClearError();	
	DevCtrlDisEndable();

        DevGetUdc();

        DevGetCurCurent();
	//DevGetDin();
	GetCruError();
       DevSetLifeGuard(LIFECOM);

	
            if( driverprco.m_BitStatus.bit1_isENA_SRV !=1 ){
                    //DevCtrleEndable(vecpa);
                    return 0;
                }
	if(driverprco.GetStrError()!="OK"){
			 return 0;
		}
	if(onlineMsg.online !=FN_ONLINE ){
                     return 0;
                 }
        
        return 1;
}

int sytronDriverMode::DriveStop()
{
   // std::cout << "DriveStop is DriveStop"<<std::endl;
	#if DEBUG_ECHO
        std::cout << "DriveStop is running"<<std::endl;
	#endif    
   DevSetCmdStop();
    
   SpeedClear();
   DevSetspeed(velocity);  
  
   DevGetCurCurent();

   GetCruError();
   //DevGetDin();
   DevSetLifeGuard(LIFECOM);
   if(onlineMsg.online !=FN_ONLINE ){
                     return 0;
	}

        return 1;
}

int sytronDriverMode::DriveEmergencyStop()
{
	
	#if DEBUG_ECHO
        std::cout << "DriveEmergencyStop is running"<<std::endl;
	#endif    
	
   //DevSetLifeGuard(0);
   SpeedClear();
   
   DevSetspeed(0);   
     
   DevEmergencyStop();
  
   GetSpeedCmd(); 

   DevGetCurCurent();
   //DevGetDin();
   GetCruError();
   DevSetLifeGuard(LIFECOM);
   if(onlineMsg.online !=FN_ONLINE ){
                     return 0;
	}

        return 1;
}

#ifdef ROSIN
void sytronDriverMode::SetSpeed(short int speed)
{
   
    velocity = (speed>MAXSPEEDRPM?MAXSPEEDRPM:speed);
}

void sytronDriverMode::SpeedClear()
{
   
    velocity = 0;
}

//SUB 接收命令 
void sytronDriverMode::Can1Recv_driverCall(const std_msgs::String::ConstPtr& msg)
{

	std::string recvstr = msg->data;
        int msgsize = (int)(recvstr.size()/13);
   	 for(int i=0;i<msgsize;i++){
             		boost::array<char,13>fram;
			 for(int index=0;index<13;index++){
					fram[index]=recvstr[index+i*13];
			 	}
			 message msg(fram.c_array(),13);
			 //print_hex(recvstr);
			if((msg.get_fram_ID()&0x000000ff)==(int)DEV_add){
					driverprco.signleRecord(msg);
					onlineMsg.Set_connect();
				}
   	 	}


}

void sytronDriverMode::Can2Recv_driverCall(const std_msgs::String::ConstPtr& msg)
{

	std::string recvstr = msg->data;
        int msgsize = (int)(recvstr.size()/13);
   	 for(int i=0;i<msgsize;i++){
             		boost::array<char,13>fram;
			 for(int index=0;index<13;index++){
					fram[index]=recvstr[index+i*13];
			 	}
			 message msg(fram.c_array(),13);
			 //print_hex(recvstr);
			if((msg.get_fram_ID()&0x000000ff)==(int)DEV_add){
					driverprco.signleRecord(msg);
					onlineMsg.Set_connect();
				}
   	 	}

   	 

}

//SUB 接收命令 
void sytronDriverMode::CAN_EncounterCall(const dgvmsg::EncounterV::ConstPtr& msg)
{
	//dgvmsg::EncounterV Ent;
	//Ent = msg;
	int size = msg->cnt.size();
	for(int index =0; index<size ; index++){
		if(msg->cnt[index].devadd ==DEV_add){
				driverprco.m_DrivStatus = msg->cnt[index].DrivStatus;
				driverprco.recordBitstauts(driverprco.m_DrivStatus);
				 #if 1
				 //std::cout<<"devadd="<<(int)msg->cnt[index].devadd;
				 //std::cout<<" m_DrivStatus ="<<driverprco.m_DrivStatus<<std::endl;
				   // std::cout<<"bit0_isSRDY ="<<(UINT16)driverprco.m_BitStatus.bit0_isSRDY<<std::endl;
				   // std::cout<<"bit1_isENA_SRV ="<<(UINT16)driverprco.m_BitStatus.bit1_isENA_SRV<<std::endl;
				    //std::cout<<"bit2_isRes1 ="<<(UINT16)driverprco.m_BitStatus.bit2_isRes1<<std::endl;
				   // std::cout<<"bit3_isFault ="<<(UINT16)driverprco.m_BitStatus.bit3_isFault<<std::endl;
				   // std::cout<<"bit4_isRes2 ="<<(UINT16)driverprco.m_BitStatus.bit4_isRes2<<std::endl;
				  //std::cout<<"devadd="<<(int)msg->cnt[index].devadd<<" bit5_EMGING ="<<(UINT16)driverprco.m_BitStatus.bit5_EMGING<<std::endl;
				   // std::cout<<"bit6_isDIS_SRV ="<<(UINT16)driverprco.m_BitStatus.bit6_isDIS_SRV<<std::endl;
				   // std::cout<<"devadd="<<(int)msg->cnt[index].devadd<<"bit7_Warning ="<<(UINT16)driverprco.m_BitStatus.bit7_Warning<<std::endl;
				 #endif
			}
		}
	

}

void sytronDriverMode::Net2Ctrl_driverCall(const dgvmsg::DriverVelocity::ConstPtr& cmdmsg)
{
        //ROS_INFO("ros sub:");
         short int speed=0; 

        //前进速度
        int size = cmdmsg->driver.size();
	 #if 0
	 std::cout<<"Net2Ctrl_driverCall="<<size<<std::endl;
	 #endif
	for(int index=0;index<size;index++){
			// std::cout<<"cmdmsg->driver[index].add ="<<cmdmsg->driver[index].add<<std::endl;
			if(cmdmsg->driver[index].add ==DEV_add){
					speed = cmdmsg->driver[index].VRPM;
					SetSpeed(speed);
					//std::cout<<"add="<<(int)this->driverprco.Getadd();
					//std::cout<<" speed="<<speed<<std::endl;
				}
		}
    
    if(statues_ptr != FUN_SPEEDLOOP){
                statues_ptr = FUN_REENABLE;
        }  
    
      //  ClearJoyFlag();  
}

void sytronDriverMode::Net2SCtrl_driverCall(const std_msgs::String::ConstPtr& ctrlcmd)
{
         // Verify that the version of the library that we linked against is
      // compatible with the version of the headers we compiled against.
      GOOGLE_PROTOBUF_VERIFY_VERSION;
		 
    std::string msg= ctrlcmd->data;
    if(msg.size()>50){
		PackageMessage msgrecv;
		msgrecv.ParseFromString(msg);
		PackageMessage_Call* callmsg = msgrecv.mutable_callmessage();
		if(callmsg->has_function()){
				std::string fun=callmsg->function();
			  	if(fun =="CAR_CTRL_STOP" ){
			            if((statues_ptr != FUN_STOPRUN)&&
			                (statues_ptr != FUN_RELEASE)&&
			               // (statues_ptr != FUN_EMERAGENCE)&&
			                (statues_ptr != FUN_ENABLE)){
			                        statues_ptr = FUN_STOPRUN;
			                }
			        }
			     else if(fun =="CAR_CTRL_EmergencyStop" ){
			            if(
			                //(statues_ptr != FUN_STOPRUN)&&
			                (statues_ptr != FUN_RELEASE)&&
			                (statues_ptr != FUN_EMERAGENCE)
			                //&&(statues_ptr != FUN_ENABLE)
			                ){
			                        statues_ptr = FUN_EMERAGENCE;
			                }            
			        }
			     else if(fun =="CAR_CTRL_Realse_Loop" ){
			            if((statues_ptr != FUN_RELEASE)
			                //&&(statues_ptr != FUN_RELEASE)&&
			               // (statues_ptr != FUN_EMERAGENCE)&&
			               // (statues_ptr != FUN_ENABLE)
			               ){
			                        statues_ptr = FUN_RELEASE;
			                }             
			         }
			     else if(fun =="CAR_CTRL_Enable_Loop" ){
			            if((statues_ptr != FUN_ENABLE)
			                &&(statues_ptr != FUN_RELEASE)&&
			                (statues_ptr != FUN_EMERAGENCE)&&
			                (statues_ptr != FUN_STOPRUN)
			                ){
			                        statues_ptr = FUN_ENABLE;
			                }            
			        }
			     else if(fun =="CAR_CTRL_ClearError" ){
			            if((statues_ptr != FUN_CLEARERROR)
			                //&&(statues_ptr != FUN_RELEASE)&&
			               // (statues_ptr != FUN_EMERAGENCE)&&
			                //(statues_ptr != FUN_ENABLE)
			                ){
			                        statues_ptr = FUN_CLEARERROR;
			                }        
			     	}
			     else if(fun =="CAR_CTRL_Config" ){
					if(callmsg->parameters_size()==1){
							std::string recvmsg = callmsg->parameters(0);
							if(recvmsg.size()>10){
									//Recv_driver_Config(recvmsg);
								}
						}
			        }
			}

    	}
  
    // ROS_INFO("recv SCMD msg :%s",msg.c_str());

}

/*
void sytronDriverMode::dirv_pub_encounter()
{   
	dgvmsg::Encounter encounter;
	
	//encounter.devadd = driverprco.add();
	encounter.devadd = DEV_add;
	encounter.encounter = driverprco.CruPos();
	encounter.now = ros::Time::now();

	rospub_mode_driverencounter.publish(encounter);
	ros::spinOnce();
	
}
*/
/*
void sytronDriverMode::dirv_pub_allstatues()
{   
    std_msgs::String stdmsg;
    
     stdmsg.data = Pack_driver_statues();
     
     rospub_mode_driverstatues.publish(stdmsg);
     ros::spinOnce();
}

std::string  sytronDriverMode::Pack_driver_statues()
{       
         // Verify that the version of the library that we linked against is
      // compatible with the version of the headers we compiled against.
      GOOGLE_PROTOBUF_VERIFY_VERSION;

       ControllerMessage_Dirver driver_status;
      //driver_status.r

      for(int index=0;index<1;index++){
        
       driver_status.set_device_status((::google::protobuf::int32)onlineMsg.online);
      // driver_status.set_device_add((::google::protobuf::int32)driverprco.add());
      driver_status.set_device_add((::google::protobuf::int32)DEV_add);
       driver_status.set_actvelocity((::google::protobuf::int32)(driverprco.cru_speed())*driverprco.dir());
       //driver_status.set_setvelocity(driverprco.cru_speedcmd()*driverprco.dir());
       driver_status.set_setvelocity(velocity*driverprco.dir());
       
       driver_status.set_ctrl_dc_voltage(driverprco.Udc());

       driver_status.set_ctrl_ipm_temperature(driverprco.IpmTem());
       driver_status.set_actcurrent((float)driverprco.effectiveTorque_I());
       
       driver_status.set_actualpos(driverprco.CruPos()*driverprco.dir());
	
	 if(driverprco.Dins() ==0x17){ //急停
       		   driver_status.set_emergencyinputvalue(0);
	 	}
	 else{
		driver_status.set_emergencyinputvalue(1);
	 	}
	     
      driver_status.clear_motec();
       driver_status.set_error(driverprco.GetStrError());
        }


       
       std::string res;
       if (!driver_status.SerializeToString(&res)  ) {
           std::cerr << "Failed to write msg driver Message." << std::endl; 
           return ""; 
       }  
    return res;
}  
*/
void sytronDriverMode::Pack_driver_msg_statues()
{       
       dgvmsg::DriverStatues feedback;

	feedback.device_status = onlineMsg.online;
	feedback.device_add = DEV_add;
	feedback.actvelocityRPM = ((driverprco.cru_speed())*driverprco.dir());
	feedback.setvelocityRPM = velocity*driverprco.dir();
	feedback.dc_voltage = driverprco.Udc();
	feedback.ipm_temperature = driverprco.IpmTem();
	feedback.actcurrent =  (float)driverprco.effectiveTorque_I();
	feedback.actualpos = driverprco.CruPos()*driverprco.dir();
	feedback.emergencyinputvalue =driverprco.m_BitStatus.bit5_EMGING;
	feedback.errorcode	= driverprco.GetStrError();

     rospub_mode_driverstatues.publish(feedback);
     ros::spinOnce();
	
}  


void sytronDriverMode::dirv_pub_CAN_sendcmd(std::string cmd)
{   

	std_msgs::String stdmsg;
	stdmsg.data = cmd;
	rospub_CAN_sendcmd.publish(stdmsg);
	ros::spinOnce();
	
}
int sytronDriverMode::check_recv5bits(std::string &data) 
{   
	if(data[0] != driverprco.Getadd()){
		return -1;
		}
	if(data[1] != 0x86){
		return -1;
		}	
	if(data[2] != 0x04){
		return -1;
		}
	return 1;
}

#endif
