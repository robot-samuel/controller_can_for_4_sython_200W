

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



#include "usbcandevMode.hpp"

#define  DEBUG_ECHO 1



usbcandevMode::usbcandevMode( unsigned int rate)
:bandrate(rate)
{
 	std::string SDevType;
	std::string SDevIdx;
	std::string SChMask;
	std::string SBaud;
	std::string STxType;
	std::string STxSleep;
	std::string STxFrames;
	std::string STxCount;


	SDevType = "4";   //ï¿½å¿¨ï¿½ï¿½ï¿½ï¿½
	SDevIdx= "0";	//ï¿½è±¸ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	SChMask= "3"; 	//Í¨ï¿½ï¿½Ñ¡ï¿½ï¿½
	//SBaud= argv[1];  //0x1400-1M, 0x1c03-125K,0x1600-800K ,0x1c00-500K....\n" 
	
	STxType= "0";
	STxSleep= "3";
	STxFrames= "1";
	STxCount= "1";

	std::cout<<"SDevType:" <<SDevType<<std::endl;
	std::cout<<"SDevIdx:" <<SDevIdx<<std::endl;
	std::cout<<"SChMask:" <<SChMask<<std::endl;
	std::cout<<"SBaud:" <<bandrate<<std::endl;
	std::cout<<"STxType:" <<STxType<<std::endl;
	std::cout<<"STxSleep:" <<STxSleep<<std::endl;
	std::cout<<"STxFrames:" <<STxFrames<<std::endl;
	std::cout<<"STxCount:" <<STxCount<<std::endl;

	candev.set_DevType( boost::lexical_cast<unsigned int>(SDevType));
	candev.set_DevIdx( boost::lexical_cast<unsigned int>(SDevIdx));
	candev.set_ChMask( boost::lexical_cast<unsigned int>(SChMask));
	candev.set_TxType( boost::lexical_cast<unsigned int>(STxType));
	candev.set_TxSleep(boost::lexical_cast<unsigned int>(STxSleep));
	candev.set_TxFrames(boost::lexical_cast<unsigned int>(STxFrames));
	candev.set_TxCount(boost::lexical_cast<unsigned int>(STxCount));

	candev.set_Baud(bandrate);
 	//ï¿½è±¸ï¿½ï¿½Ê¼ï¿½ï¿½
 	candev.usbcandevOpen(candev.DevType(), candev.DevIdx());
	candev.usbcandevconfig();

	candev.usbcandevStartRx();
	
	onlineMsg.online=0;
	onlineMsg.Set_timeout(5);	


	LF_counter = 0 ;
	RF_counter = 0 ;
	LB_counter = 0 ;
	RB_counter = 0 ;

	SLF_counter = 0 ;
	SRF_counter = 0 ;
	SLB_counter = 0 ;
	SRB_counter = 0 ;

	
	can1_srecv.clear();
	can2_srecv.clear();

	 m_LFDrivStatus = 0;
	  m_RFDrivStatus = 0;
	   m_LBDrivStatus = 0;
	    m_RBDrivStatus = 0;

	 m_SLFDrivStatus = 0;
	  m_SRFDrivStatus = 0;
	   m_SLBDrivStatus = 0;
	    m_SRBDrivStatus = 0;

	
}

usbcandevMode::~usbcandevMode()
{
  /*
    pimpl->serial.clearCallback();
    try {
        pimpl->serial.close();
    } catch(...)
    {
        //Don't throw from a destructor
    }
    */
    
}

void usbcandevMode::set_Baud(unsigned int Baud ){ bandrate = Baud;}


 void usbcandevMode::can1_ros_sendCall(const std_msgs::String::ConstPtr& msg)
{
  try{
		std::string cmdstr = msg->data;
		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ð£ï¿½ï¿½
		candev.sendRequest(cmdstr,candev.ctx_can1);
	}
   catch(...){
        std::cout << "can1_ros_sendCall interrupt" << std:: endl;
       }

 } 


 void usbcandevMode::can2_ros_sendCall(const std_msgs::String::ConstPtr& msg)
{
try{
		std::string cmdstr = msg->data;
		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ð£ï¿½ï¿½
		candev.sendRequest(cmdstr,candev.ctx_can2);
		}
   catch(...){
        std::cout << "can2_ros_sendCall interrupt" << std:: endl;
       }
                      
 } 


void usbcandevMode::ros_SendEncounterRpc()
{   
	dgvmsg::EncounterV Ent;
        Ent.cnt.resize(4);
		
	Ent.cnt[0].devadd=(int)DEV_DIR_ADD_LF;
	Ent.cnt[0].now=  ros::Time::now();
	Ent.cnt[0].encounter = SLF_counter;
	Ent.cnt[0].DrivStatus = m_SLFDrivStatus;
		
	Ent.cnt[1].devadd=(int)DEV_DIR_ADD_RF;
	Ent.cnt[1].now=  ros::Time::now();
	Ent.cnt[1].encounter = SRF_counter;
	Ent.cnt[1].DrivStatus = m_SRFDrivStatus;

	Ent.cnt[2].devadd=(int)DEV_DIR_ADD_LB;
	Ent.cnt[2].now=  ros::Time::now();
	Ent.cnt[2].encounter = SLB_counter;
	Ent.cnt[2].DrivStatus = m_SLBDrivStatus;

	Ent.cnt[3].devadd =(int)DEV_DIR_ADD_RB;
	Ent.cnt[3].now =  ros::Time::now();
	Ent.cnt[3].encounter = SRB_counter;
	Ent.cnt[3].DrivStatus = m_SRBDrivStatus;
	
	
   #if 0
   	std::cout<<"********************ros_SendEncounterRpc**********************"<<std::endl;
	std::cout<<"LF_counter="<<SLF_counter<<std::endl;
   	std::cout<<"RF_counter="<<SRF_counter<<std::endl;
	std::cout<<"LB_counter="<<SLB_counter<<std::endl;
	std::cout<<"RB_counter="<<SRB_counter<<std::endl;
   #endif
     LCEncounterpub.publish(Ent);
     ros::spinOnce();
}


void usbcandevMode::ros_Can1Recvpub_SendRpc(std::string msg)
{   

    std_msgs::String stdmsg;
     stdmsg.data = msg;
     #if 0
    std::cout<<"ros pub: extern_sensor/cmd"<<"size= "<<stdmsg.data.size()<<std::endl;
     #endif
     Can1Recvpub.publish(stdmsg);
     ros::spinOnce();
}

void usbcandevMode::ros_Can2Recvpub_SendRpc(std::string msg)
{   

    std_msgs::String stdmsg;
     stdmsg.data = msg;
     #if 0
    std::cout<<"ros pub: extern_sensor/cmd"<<"size= "<<stdmsg.data.size()<<std::endl;
     #endif
     Can2Recvpub.publish(stdmsg);
     ros::spinOnce();
}

void usbcandevMode::usbcandevMode_master()
{
	ros::Rate loop_rate(30);
	try{
	std::cout << "======usbcandevMode_master======"<<std::endl;
	while (ros::ok()){
		//ï¿½Ç·ï¿½ï¿½Ð½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		//std::cout<<"size1="<< candev.recvbuf_size(CAN1)<<std::endl;
		//std::cout<<"size2="<< candev.recvbuf_size(CAN2)<<std::endl;
		if(candev.recvbuf_size(CAN1)){
			//int sendsize=candev.recvbuf_size(CAN1)>20?20:candev.recvbuf_size(CAN1);
			for(int i =0 ;i<1;i++ ){
			std::string recv1 =candev.pop_cur_toarray(CAN1);
			if(recv1.size()>5){
				 
				 //ros_Can1Recvpub_SendRpc(recv1);
				 //print_hex(recv1,"Can1Recvpub");
				}
			//boost::this_thread::sleep(boost::posix_time::milliseconds(1));
			}
			}
		if(candev.recvbuf_size(CAN2)){
			//int sendsize=candev.recvbuf_size(CAN2)>30?30:candev.recvbuf_size(CAN2);
			for(int i =0 ;i<2;i++ ){
			std::string recv3 =candev.pop_cur_toarray(CAN2);
			if(recv3.size()>5){
				ros_Can2Recvpub_SendRpc(recv3);
				//print_hex(recv3,"Can2Recvpub");
				}
			//boost::this_thread::sleep(boost::posix_time::milliseconds(1));
			}
			}
        	loop_rate.sleep();
		//
		boost::this_thread::interruption_point();
	}
	}
        catch(boost::thread_interrupted&){
                 std::cout << "usbcandevMode_master interrupt" << std:: endl;
		candev.usbcan_rxthred_interupt();
             }
    

}
void usbcandevMode::usbcandevMode_Pubencounter(){

	ros::Rate loop_rate(30);
	while (ros::ok()){
			loop_rate.sleep();
			boost::this_thread::interruption_point();
			ros_SendEncounterRpc();	
		}

}
void usbcandevMode::usbcandevMode_mastercan2()
{
	ros::Rate loop_rate(40);
	try{
	std::cout << "======usbcandevMode_mastercan2======"<<std::endl;
	while (ros::ok()){
		//ï¿½Ç·ï¿½ï¿½Ð½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½


		if(candev.recvbuf_size(CAN2)){
			int sendsize=candev.recvbuf_size(CAN2)>100?100:candev.recvbuf_size(CAN2);
			for(int i =0 ;i<sendsize;i++ ){
				std::string recv2 =pop_cur_toarray(CAN2);
			   //boost::this_thread::sleep(boost::posix_time::milliseconds(1));
			}
			if(can2_srecv.size()>5){
				//std::cout<<"size2="<< candev.recvbuf_size(CAN2);
				//std::cout<<"send size2="<< can2_srecv.size()<< std:: endl;
				ros_Can2Recvpub_SendRpc(can2_srecv);
				can2_srecv.clear();
				 //print_hex(recv1,"Can1Recvpub");
				}
			}
        	loop_rate.sleep();
		//
		boost::this_thread::interruption_point();
	}
	}
        catch(...){
                 std::cout << "usbcandevMode_mastercan2 interrupt" << std:: endl;
		    candev.usbcan_rxthred_interupt();
             }
    

}
void usbcandevMode::usbcandevMode_mastercan1()
{
	ros::Rate loop_rate(40);
	try{
	std::cout << "======usbcandevMode_mastercan1======"<<std::endl;
	while (ros::ok()){
		//ï¿½Ç·ï¿½ï¿½Ð½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		//std::cout<<"size1="<< candev.recvbuf_size(CAN1)<<std::endl;
		if(candev.recvbuf_size(CAN1)){
			int sendsize=candev.recvbuf_size(CAN1)>100?100:candev.recvbuf_size(CAN1);
			for(int i =0 ;i<sendsize;i++ ){
				std::string recv1 =pop_cur_toarray(CAN1);
			   //boost::this_thread::sleep(boost::posix_time::milliseconds(1));
			}
			if(can1_srecv.size()>5){
				//std::cout<<"size1="<< candev.recvbuf_size(CAN1);
				//std::cout<<"send size1="<< can1_srecv.size()<< std:: endl;
				
				ros_Can1Recvpub_SendRpc(can1_srecv);
				can1_srecv.clear();
				 //print_hex(recv1,"Can1Recvpub");
				}
			}
        	loop_rate.sleep();
		//
		boost::this_thread::interruption_point();
		}
	}
        catch(...){
                 std::cout << "usbcandevMode_mastercan1 interrupt" << std:: endl;
		candev.usbcan_rxthred_interupt();
             }
    

}

 void usbcandevMode::print_hex(std::string str,std::string com)
 {
	int Num = str.size();
	const char * datBUF =  str.c_str();
	
  std::cout<<com<< " usbcandevMode print_pub hex:";
  for(std::size_t index=0;index<Num;index++){
                   int x=(unsigned  char)datBUF[index];
                    std::cout<<boost::format("%02X ")%x;
               }
 std::cout<<"\n";

 }


std::string usbcandevMode::pop_cur_toarray(unsigned int id){
        VCI_CAN_OBJ frame;
        boost::array<char,13>cur_data={0,0,0,0,0,0,0,0,0,0,0,0,0};
	//std::string res;
	//res.clear();
	
	if(id == CAN1){	
	        if(candev.can1buf_ptr->size()>0){
	                    frame = *(candev.can1buf_ptr->begin());
	                   
	                   printf_frame(&frame);
	                    if((frame.ID&0x000000ff)==(int)DEV_DIR_ADD_LF){
					//ÊÇ²»ÊÇÎ»ÖÃÊý¾Ý
					if(frame.Data[1]==0xCA){
							LF_counter=0;
							char * p = (char *)&LF_counter;
							    * (p+3) = frame.Data[2];
							    * (p+2) = frame.Data[3];
							    * (p+1) = frame.Data[4];
							    * (p+0) = frame.Data[5];
							SLF_counter = LF_counter;
							
							p = (char *)&m_LFDrivStatus;
							    * (p+1) = frame.Data[6];
							    * (p+0) = frame.Data[7];							
							
							m_SLFDrivStatus = m_LFDrivStatus;
							
						}
					else{

				                    cur_data[0] = frame.DataLen;
				                    cur_data[1] =(char)((frame.ID&0xff000000)>>24);
				                    cur_data[2] =(char)((frame.ID&0x00ff0000)>>16);
				                    cur_data[3] =(char)((frame.ID&0x0000ff00)>>8);
				                    cur_data[4] =(char)((frame.ID&0x000000ff));
				                    cur_data[5] = frame.Data[0];
				                    cur_data[6] = frame.Data[1];
				                    cur_data[7] = frame.Data[2];
				                    cur_data[8] = frame.Data[3];
				                    cur_data[9] = frame.Data[4];
				                    cur_data[10] = frame.Data[5];
				                    cur_data[11] = frame.Data[6];
				                    cur_data[12] = frame.Data[7];
						     std::string res2(cur_data.begin(),cur_data.end());
						     can1_srecv+=res2;
						}
					
					
	                    	}
	                    if((frame.ID&0x000000ff)==(int)DEV_DIR_ADD_LB){
					//ÊÇ²»ÊÇÎ»ÖÃÊý¾Ý
					
					if(frame.Data[1]==0xCA){
							LB_counter=0;
							char * p = (char *)&LB_counter;
							    * (p+3) = frame.Data[2];
							    * (p+2) = frame.Data[3];
							    * (p+1) = frame.Data[4];
							    * (p+0) = frame.Data[5];
							SLB_counter = LB_counter;
							p = (char *)&m_LBDrivStatus;
							    * (p+1) = frame.Data[6];
							    * (p+0) = frame.Data[7];							
							
							m_SLBDrivStatus = m_LBDrivStatus;							
						}
					else{

				                    cur_data[0] = frame.DataLen;
				                    cur_data[1] =(char)((frame.ID&0xff000000)>>24);
				                    cur_data[2] =(char)((frame.ID&0x00ff0000)>>16);
				                    cur_data[3] =(char)((frame.ID&0x0000ff00)>>8);
				                    cur_data[4] =(char)((frame.ID&0x000000ff));
				                    cur_data[5] = frame.Data[0];
				                    cur_data[6] = frame.Data[1];
				                    cur_data[7] = frame.Data[2];
				                    cur_data[8] = frame.Data[3];
				                    cur_data[9] = frame.Data[4];
				                    cur_data[10] = frame.Data[5];
				                    cur_data[11] = frame.Data[6];
				                    cur_data[12] = frame.Data[7];
						     std::string res2(cur_data.begin(),cur_data.end());
						     can1_srecv+=res2;
						}
	                    	}
			     candev.can1buf_ptr->pop_front();	
			     return can1_srecv;
	            }

			return can1_srecv;
		}
	if(id == CAN2){	
  		if(candev.can2buf_ptr->size()>0){
	                    frame = *(candev.can2buf_ptr->begin());
	                   
	                   // printf_frame(&frame);
	                    if((frame.ID&0x000000ff)==(int)DEV_DIR_ADD_RF){
					//ÊÇ²»ÊÇÎ»ÖÃÊý¾Ý
					if(frame.Data[1]==0xCA){
							RF_counter=0;
							char * p = (char *)&RF_counter;
							    * (p+3) = frame.Data[2];
							    * (p+2) = frame.Data[3];
							    * (p+1) = frame.Data[4];
							    * (p+0) = frame.Data[5];
							SRF_counter = RF_counter;
							p = (char *)&m_RFDrivStatus;
							    * (p+1) = frame.Data[6];
							    * (p+0) = frame.Data[7];							
							
							m_SRFDrivStatus = m_RFDrivStatus;							
						}
					else{

				                    cur_data[0] = frame.DataLen;
				                    cur_data[1] =(char)((frame.ID&0xff000000)>>24);
				                    cur_data[2] =(char)((frame.ID&0x00ff0000)>>16);
				                    cur_data[3] =(char)((frame.ID&0x0000ff00)>>8);
				                    cur_data[4] =(char)((frame.ID&0x000000ff));
				                    cur_data[5] = frame.Data[0];
				                    cur_data[6] = frame.Data[1];
				                    cur_data[7] = frame.Data[2];
				                    cur_data[8] = frame.Data[3];
				                    cur_data[9] = frame.Data[4];
				                    cur_data[10] = frame.Data[5];
				                    cur_data[11] = frame.Data[6];
				                    cur_data[12] = frame.Data[7];
						     std::string res2(cur_data.begin(),cur_data.end());
						     can2_srecv+=res2;
						}
					
					
	                    	}
	                    if((frame.ID&0x000000ff)==(int)DEV_DIR_ADD_RB){
					//ÊÇ²»ÊÇÎ»ÖÃÊý¾Ý
					
					if(frame.Data[1]==0xCA){
							RB_counter=0;
							char * p = (char *)&RB_counter;
							    * (p+3) = frame.Data[2];
							    * (p+2) = frame.Data[3];
							    * (p+1) = frame.Data[4];
							    * (p+0) = frame.Data[5];

							SRB_counter = RB_counter;
							p = (char *)&m_RBDrivStatus;
							    * (p+1) = frame.Data[6];
							    * (p+0) = frame.Data[7];							
							
							m_SRBDrivStatus = m_RBDrivStatus;							
						}
					else{

				                    cur_data[0] = frame.DataLen;
				                    cur_data[1] =(char)((frame.ID&0xff000000)>>24);
				                    cur_data[2] =(char)((frame.ID&0x00ff0000)>>16);
				                    cur_data[3] =(char)((frame.ID&0x0000ff00)>>8);
				                    cur_data[4] =(char)((frame.ID&0x000000ff));
				                    cur_data[5] = frame.Data[0];
				                    cur_data[6] = frame.Data[1];
				                    cur_data[7] = frame.Data[2];
				                    cur_data[8] = frame.Data[3];
				                    cur_data[9] = frame.Data[4];
				                    cur_data[10] = frame.Data[5];
				                    cur_data[11] = frame.Data[6];
				                    cur_data[12] = frame.Data[7];
						     std::string res2(cur_data.begin(),cur_data.end());
						     can2_srecv+=res2;
						}
	                    	}
			     candev.can2buf_ptr->pop_front();
			     return can2_srecv;
	            }

			 return can2_srecv;
		}

	
}

void usbcandevMode::printf_frame(VCI_CAN_OBJ *can){

/*
typedef  struct  _VCI_CAN_OBJ{
	UINT	ID;
	UINT	TimeStamp;
	BYTE	TimeFlag;
	BYTE	SendType;
	BYTE	RemoteFlag;//æ˜¯å¦æ˜¯è¿œç¨‹å¸§
	BYTE	ExternFlag;//æ˜¯å¦æ˜¯æ‰©å±•å¸§
	BYTE	DataLen;
	BYTE	Data[8];
	BYTE	Reserved[3];
}VCI_CAN_OBJ,*PVCI_CAN_OBJ;



*/
    boost::format fmt("ID=%1% DataLen=%2%  SendType=%3% data=[%4%,%5%,%6%,%7%,%8%,%9%,%10%,%11%] ");
      fmt % (boost::format("%04X ")%(can->ID));
      fmt %(int)can->DataLen;
      fmt %(int)can->SendType;
      fmt %(boost::format("%02X ")%(int)can->Data[0]);
      fmt %(boost::format("%02X ")%(int)can->Data[1]);
      fmt %(boost::format("%02X ")%(int)can->Data[2]);
      fmt %(boost::format("%02X ")%(int)can->Data[3]);
      fmt %(boost::format("%02X ")%(int)can->Data[4]);
      fmt %(boost::format("%02X ")%(int)can->Data[5]);
      fmt %(boost::format("%02X ")%(int)can->Data[6]);
      fmt %(boost::format("%02X ")%(int)can->Data[7]);

      std::cout<<fmt.str()<<std::endl;   
}

	

