

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
#include <boost/date_time/gregorian/gregorian.hpp>

#include "std_msgs/String.h"

#include "ExternMode.hpp"



#define DBUG 0

class MAsyncSerialImpl
{
public:
    CallbackAsyncSerial serial;
    std::string receivedData;
};


ExternMode::ExternMode(std::string& port, unsigned int rate)
:pimpl(new MAsyncSerialImpl)
{
 	ptr_resv=0;
	recv_count = 0; 
	pimpl->receivedData.clear();
	Readarray.assign(0);
	
	open(port,rate);	
	ttyport = port;
	bandrate = rate;

	 fan1_mode=Mode_open;    //爆闪灯
	 fan2_mode=Mode_open;
	 //Ledcolor = Mode_red_fli;
	 Ledcolor = Mode_green_fli;
	//Ledcolor = Mode_blue_fli;

	 fan1_open=35;
	 fan1_close = 20;
	 fan1_statue = Mode_close;
	 fan2_open=35;
	 fan2_close = 20;
	 fan2_statue = Mode_close;
	 
	 config_flag = false;

	 light_left = LED_open;
	 light_right = LED_open;
	
	// 4路PT100
	SensorMsg.add_temp_pt100(255);
	SensorMsg.add_temp_pt100(255);
	SensorMsg.add_temp_pt100(255);
	SensorMsg.add_temp_pt100(255);

	// 2路 温湿度
	ExternSensor_Mode_Temp_humi  * pMode_Temp_humi = 
		SensorMsg.add_temp_humi();
	pMode_Temp_humi->Clear();
	pMode_Temp_humi->set_interior_temp(255);
	pMode_Temp_humi->set_interior_humi(101);

	pMode_Temp_humi = SensorMsg.add_temp_humi();
	pMode_Temp_humi->Clear();
	pMode_Temp_humi->set_interior_temp(255);
	pMode_Temp_humi->set_interior_humi(101);
	
	// 2 路风扇状态
	ExternSensor_Mode_fan * pMode_fan = 
		SensorMsg.add_fan_msg();
	pMode_fan->set_fan_id(1);
	pMode_fan->set_fan_mode(1); //	默认工作在自动模式下
	pMode_fan->set_fan_status(0);  // 默认 close
	pMode_fan->set_vaule_close(20);
	pMode_fan->set_vaule_open(35);

	pMode_fan = SensorMsg.add_fan_msg();
	pMode_fan->set_fan_id(1);
	pMode_fan->set_fan_mode(1); //	默认工作在自动模式下
	pMode_fan->set_fan_status(0);  // 默认 close
	pMode_fan->set_vaule_close(20);
	pMode_fan->set_vaule_open(35);	

	//预留8路防跌落，实际使用前4路
	SensorMsg.add_io_infrared(1);
	SensorMsg.add_io_infrared(1);
	SensorMsg.add_io_infrared(1);
	SensorMsg.add_io_infrared(1);
	
	SensorMsg.add_io_infrared(1);
	SensorMsg.add_io_infrared(1);
	SensorMsg.add_io_infrared(1);
	SensorMsg.add_io_infrared(1);

	//预留8路防碰撞，实际不使用
	SensorMsg.add_io_collision(1);
	SensorMsg.add_io_collision(1);
	SensorMsg.add_io_collision(1);
	SensorMsg.add_io_collision(1);

	SensorMsg.add_io_collision(1);
	SensorMsg.add_io_collision(1);
	SensorMsg.add_io_collision(1);
	SensorMsg.add_io_collision(1);

	// 4路超声波状态 实际全部使用
	//SensorMsg.add_distance_ultrasonic(1200);
	//SensorMsg.add_distance_ultrasonic(1200);
	//SensorMsg.add_distance_ultrasonic(1200);
	//SensorMsg.add_distance_ultrasonic(1200);
	
	//三色指示灯状态
	//"LED_CLOSE" "LED_GREEN" "LED_RED" "LED_BLUE" "LED_GREEN_FLI" "LED_RED_FLI" "LED_BLUE_FLI"
	SensorMsg.set_led_status("LED_RED_FLI");

	// 1路松下壁障传感器
	ExternSensor_Mode_PX24ES * pMode_PX24ES =SensorMsg.mutable_px24es();
	pMode_PX24ES->set_out1(1);
	pMode_PX24ES->set_out2(1);
	pMode_PX24ES->set_extraneouslight_out(1);

	recvsize=0;

	Devonline.online=0;

	
	
}

ExternMode::~ExternMode()
{
    pimpl->serial.clearCallback();
    try {
        pimpl->serial.close();
    } catch(...)
    {
        //Don't throw from a destructor
    }
}
void ExternMode::open(std::string devname, unsigned int baudrate)
{
    try {
        pimpl->serial.open(devname,baudrate);
    } catch(boost::system::system_error&)
    {
        //Errors during open
    }
    pimpl->serial.setCallback(bind(&ExternMode::readCallback,this, _1, _2));
}

void ExternMode::close()
{
    pimpl->serial.clearCallback();
    try {
        pimpl->serial.close();
    } catch(boost::system::system_error&)
    {
        //Errors during port close
    }
    pimpl->receivedData.clear();//Clear eventual data remaining in read buffer
}

bool ExternMode::isOpen()
{
    return pimpl->serial.isOpen();
}

bool ExternMode::errorStatus()
{
    return pimpl->serial.errorStatus();
}

void ExternMode::write(std::string data)
{
    pimpl->serial.writeString(data);
}

void ExternMode::readCallback(const char *data, size_t size)
{
    //pimpl->receivedData+=QString::fromAscii(data,size);
        std::string res;
        res.clear();
        res.assign(data,size);
        pimpl->receivedData+=res;
	#if 0
	print_hex(pimpl->receivedData);
	#endif
	//do something
	
	//pimpl->receivedData.clear();
 	
  
}


void ExternMode::ExternMode_master()
{
	
             //int count=0;
		ros::Rate loop_rate(10);
		std::string str="ExternMode wait for recv";
		write(str);
		
		TC_Ctrl_CentrControl(fan1_mode,fan2_mode,Ledcolor,light_left,light_right);
		
             while(ros::ok())
                    { 
			     loop_rate.sleep();
			    //处理接收到的数据
			    //process_recv_buffer();
			    Devonline.check_connect();
			    if(config_flag == false){
			    	TC_Ctrl_CentrControl(fan1_mode,fan2_mode,Ledcolor,light_left,light_right);
			    	}
			   else{
				config_flag = false;
				TC_SetFan1_valu(fan1_open,fan1_close);
				TC_SetFan2_valu(fan2_open,fan2_close);				
				}
			   
			if(fan1_mode != Mode_auto)	{
				
				ExternSensor_Mode_fan * pMode_fan = SensorMsg.mutable_fan_msg(0);
				pMode_fan->set_fan_mode(0);
				
				}
			else{
				
				ExternSensor_Mode_fan * pMode_fan = SensorMsg.mutable_fan_msg(0);
				pMode_fan->set_fan_mode(1);
				}
			
			if(fan2_mode != Mode_auto)	{
				
				ExternSensor_Mode_fan * pMode_fan = SensorMsg.mutable_fan_msg(1);
				pMode_fan->set_fan_mode(0);
				
				}
			else{
				
				ExternSensor_Mode_fan * pMode_fan = SensorMsg.mutable_fan_msg(1);
				pMode_fan->set_fan_mode(1);
				}
			
			//ros PUB string 
			ros_SendRpc(packdata());
			   

                    }
	
}



int ExternMode::getcheck( char * p)
{
    int index=0;
    char sum=0;
	//int prtf=(unsigned char)(p[0]);
	//std::cout<<boost::format("%02X ")%prtf<<std::endl;   
    if((unsigned char)(p[0]) != 0xAA){
		return -1;
    	}
   for(int index=1;index<17-1;index++){
		sum+=(unsigned char)(p[index]);
		//int pr=(unsigned char)(p[index]);
		//std::cout<<boost::format("%02X ")%pr<<std::endl;   
   	}
   int prtf=(unsigned char)(p[16]);
   //std::cout<<boost::format("%02X ")%prtf<<std::endl;  
  std::cout<<"sum="<<boost::format("%02X ")%((int)sum)<<":"<<boost::format("%02X ")%prtf<<std::endl;
   
   
   if(p[17-1] != sum){
		return -2;
   	}
   return 0;
}

void ExternMode::ros_SendRpc(std::string msg)
{   
    //ros::NodeHandle npub;
    // ros::Publisher zmq_pub = npub.advertise<std_msgs::String>("dirv_recvcmd", 1);
   
    std_msgs::String stdmsg;
     stdmsg.data = msg;
   // ROS_INFO("ros pub: to=%s,size= [%d]", "dirv_recvcmd",stdmsg.data.size());
   #if 0
    std::cout<<"ros pub: to="
        <<"dirv_recvcmd"<<",size="
        <<stdmsg.data.size()<<std::endl;
   #endif
     Externpub.publish(stdmsg);
     ros::spinOnce();
}
void ExternMode::ConfigMode(std::string data)
{
       // Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	ExternSensorConfig param;
	param.Clear();
	param.ParseFromString(data);
	
	if(param.has_led_color()){
			Ledcolor = (unsigned char)(param.led_color());
		}
	if(param.has_led_flight()){
			std::cout<<"light_right="<<"param.led_flight()";
			if(param.led_flight() !=0){
				light_right =0;
				light_left = 0;
				}
			else{
				light_right =1;
				light_left = 1;
				}

		}
	if(param.config_fan_msg_size()!=0){
			int siez = param.config_fan_msg_size();
			for(int index=0;index<siez;index++){
			ExternSensorConfig_Config_Mode_fan * pConfig_Mode_fan = 
				param.mutable_config_fan_msg( index);
				switch(pConfig_Mode_fan->fan_id()){

						case 1:
							if(pConfig_Mode_fan->has_fan_enable()){
									fan1_mode=pConfig_Mode_fan->fan_enable();
								}
							if(pConfig_Mode_fan->has_vaule_open()){
									fan1_open = pConfig_Mode_fan->vaule_open();
								}
							if(pConfig_Mode_fan->has_vaule_close()){
									fan1_close = pConfig_Mode_fan->vaule_close();
								}
							if(pConfig_Mode_fan->has_ctrl_switch()){
									if(pConfig_Mode_fan->ctrl_switch()==1){
										fan1_mode = Mode_open;
										}
									else{
										fan1_mode = Mode_close;
										}
								}
							break;
						case 2:
							if(pConfig_Mode_fan->has_fan_enable()){
									fan2_mode=pConfig_Mode_fan->fan_enable();
								}
							if(pConfig_Mode_fan->has_vaule_open()){
									fan2_open = pConfig_Mode_fan->vaule_open();
								}
							if(pConfig_Mode_fan->has_vaule_close()){
									fan2_close = pConfig_Mode_fan->vaule_close();
								}
							if(pConfig_Mode_fan->has_ctrl_switch()){
									if(pConfig_Mode_fan->ctrl_switch()==1){
										fan2_mode = Mode_open;
										}
									else{
										fan2_mode = Mode_close;
										}
								}
							break;
						default:
							
							break;
					}

				}
		}	
}
void ExternMode::cmdCallback(const std_msgs::String::ConstPtr& msg)
{

   std::cout<<"ExternMode"<<" I heard:"<<"msg->data.size()"<<std::endl;
     if(msg->data.size() >0){
		ConfigMode(msg->data);
		config_flag=true;
        }

}


std::string ExternMode::packdata()
{
      // Verify that the version of the library that we linked against is
     // compatible with the version of the headers we compiled against.
	 
     GOOGLE_PROTOBUF_VERIFY_VERSION;

         //BMSMessage msg;
          
          //序列化到内存
          std::ostringstream stream;
	   SensorMsg.set_online(Devonline.online);
          SensorMsg.SerializeToOstream(&stream);
          
         std::string text = stream.str();
         // std::string text;
	  // text.clear();	 
          //char* buf = text.c_str();
          
        // int length = msg.ByteSize();
	return text;
	
	
}

int ExternMode::netrecvDelay(
    boost::shared_ptr<MAsyncSerialImpl> pa,
    int size,
    int timeout,
    std::string errprint){
    
    int count=0;
    while(pa->receivedData.size()<size){
          count++;
          boost::this_thread::sleep(boost::posix_time::milliseconds(1));
          if(count>timeout){
                          std::cout<<errprint<<":"<<pa->receivedData.size()<<'\a'<<std::endl;
			   // print_hex(pimpl->receivedData);
                         // printf("\a");
                          count=0;
                         return pa->receivedData.size();
                       }
            }
        return pa->receivedData.size();

}

void ExternMode::print_dec(char *datBUF,int Num){

 std::cout<< "print_dec:";
 for(std::size_t index=0;index<Num;index++){
                  int x=(unsigned  char)datBUF[index];
                   std::cout<<boost::format("%d ")%x;
              }
std::cout<<"\n";

}
 void ExternMode::print_hex(char *datBUF,int Num){

  std::cout<< "print_hex:";
  for(std::size_t index=0;index<Num;index++){
                   int x=(unsigned  char)datBUF[index];
                    std::cout<<boost::format("%02X ")%x;
               }
 std::cout<<"\n";

 }
 
void ExternMode::print_hex(std::string str)
 {
	int Num = str.size();
	const char * datBUF =  str.c_str();
	
  std::cout<< "print_hex:";
  for(std::size_t index=0;index<Num;index++){
                   int x=(unsigned  char)datBUF[index];
                    std::cout<<boost::format("%02X ")%x;
               }
 std::cout<<"\n";

 }
 
unsigned short int  ExternMode::GetCheckSUM(  unsigned char *datBUF,int Num)
{

	unsigned short int SUM=0;
	int i;
	
	for(i=0;i<Num;i++){
		SUM += (unsigned short int)datBUF[i];
		//std::cout<<"SUM="<<SUM<<std::endl;
		if(SUM>>8){
			//std::cout<<"SUM="<<SUM<<std::endl;
			SUM = ((SUM>>8)) + ((SUM&0x00ff));
			//std::cout<<"SUM="<<SUM<<std::endl;
		}
	}
	SUM = ~SUM;
	SUM = SUM&0x00ff;
	
	return (SUM);  
}

unsigned short int  ExternMode::CheckSUM( char *datBUF,int Num){

	unsigned short int SUM=0;
	int i;
	
	for(i=2;i<Num;i++){
		SUM += (unsigned char)(datBUF[i]);
		if(SUM>>8){
			SUM = ((unsigned short int)(SUM>>8)) + ((unsigned short int)(SUM&0x00ff));
		}
	}
	SUM = ~SUM;
	SUM = SUM&0x00ff;
	
	return (SUM);  
}
std::string  ExternMode::TC_Cmd_package(char cmdID, short int sData1,short int sData2)
{
	
	boost::array<char,nomal_length> data;
	short int Data1=sData1;
	short int Data2=sData2;
	
	data.assign(0);
	
	data[0] = HEAD;
	data[1] = ADD;
	data[2] = cmdID;
	char * ps1  = (char *)(&Data1);
	data[4]=  *(ps1);ps1++;  //低位
	data[3]=  *(ps1);ps1++; //高位
	
	char * ps2  = (char *)(&Data2);
	data[6]=  *(ps2);ps2++;  //低位
	data[5]=  *(ps2);ps2++; //高位
	//计算校验
	char* pd=data.c_array();	
	unsigned short int check= CheckSUM(pd,nomal_length-2);
	char * p  = (char *)(&check);
	data[8]=  *(p);p++;  //低位
	data[7]=  *(p);p++; //高位
	
	data[9] = SEND;
	#if 0
	print_hex(pd,nomal_length);
	#endif
	
    	std::string res(data.begin(),data.end());
    	return res;
	
}
std::string  ExternMode::TC_GetBox1_temHuim()
{
	//获取1通道湿度数据
    	std::string res=TC_Cmd_package(ID_TC_GetBox1_temHuim,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_GetBox1_temHuim recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_GetBox1_temHuim);
		}
    	return res;
}

std::string  ExternMode::TC_GetBox2_temHuim()
{
	//获取2通道湿度数据
    	std::string res=TC_Cmd_package(ID_TC_GetBox2_temHuim,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_GetBox2_temHuim recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_GetBox2_temHuim);
		}
    	return res;
}

std::string  ExternMode::TC_GetFan1_openvalu()
{
	//打开第1路风扇
    	std::string res=TC_Cmd_package(ID_TC_GetFan1_openvalu,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_GetFan1_openvalu recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_GetFan1_openvalu);
		}
    	return res;
}

std::string  ExternMode::TC_GetFan1_closevalu()
{
	//关闭第1路风扇
    	std::string res=TC_Cmd_package(ID_TC_GetFan1_closevalu,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_GetFan1_closevalu recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_GetFan1_closevalu);
		}
    	return res;
}

std::string  ExternMode::TC_GetFan2_openvalu()
{
	//打开第2路风扇
    	std::string res=TC_Cmd_package(ID_TC_GetFan2_openvalu,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_GetFan2_openvalu recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_GetFan2_openvalu);
		}
    	return res;
}

std::string  ExternMode::TC_GetFan2_closevalu()
{
	//关闭第2路风扇
    	std::string res=TC_Cmd_package(ID_TC_GetFan2_closevalu,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_GetFan2_closevalu recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_GetFan2_closevalu);
		}
    	return res;
}

std::string  ExternMode::TC_Fan2_enable()
{
	//使能第2路风扇自动模式
    	std::string res=TC_Cmd_package(ID_TC_Fan2_enable,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_Fan2_enable recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_Fan2_enable);
		}
    	return res;
}

std::string  ExternMode::TC_Fan2_release()
{
	//使能第2路风扇手动模式
    	std::string res=TC_Cmd_package(ID_TC_Fan2_release,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_Fan2_release recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_Fan2_release);
		}
    	return res;
}

std::string  ExternMode::TC_Fan1_enable()
{
	//使能第1路风扇自动模式
    	std::string res=TC_Cmd_package(ID_TC_Fan1_enable,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_Fan1_enable recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_Fan1_enable);
		}
    	return res;
}

std::string  ExternMode::TC_Fan1_release()
{
	//使能第1路风扇手动模式
    	std::string res=TC_Cmd_package(ID_TC_Fan1_release,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_Fan1_release recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_Fan1_release);
		}
    	return res;
}

std::string  ExternMode::TC_SetFan1_valu( short int open, short int close)
{
	//设置第1路风扇自动开启关闭值
    	std::string res=TC_Cmd_package(ID_TC_SetFan1_valu,open,close);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_SetFan1_valu recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_SetFan1_valu);
		}
    	return res;
}
std::string  ExternMode::TC_SetFan2_valu(short int open, short int close)
{
	//设置第2路风扇自动开启关闭值
    	std::string res=TC_Cmd_package(ID_TC_SetFan2_valu,open,close);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_SetFan2_valu recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_SetFan2_valu);
		}
    	return res;
}
std::string  ExternMode::TC_GetFan1_valu()
{
	//获取第1路风扇自动值
    	std::string res=TC_Cmd_package(ID_TC_GetFan1_valu,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_GetFan1_valu recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_GetFan1_valu);
		}
    	return res;
}

std::string  ExternMode::TC_GetFan2_valu()
{
	//获取第2路风扇自动值
    	std::string res=TC_Cmd_package(ID_TC_GetFan2_valu,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_GetFan2_valu recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_GetFan2_valu);
		}
    	return res;
}

std::string  ExternMode::TC_GetPt100ChannelAB()
{
	//获得第1&2路温度值
    	std::string res=TC_Cmd_package(ID_TC_GetPt100ChannelAB,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_GetPt100ChannelAB recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_GetPt100ChannelAB);
		}
    	return res;
}

std::string  ExternMode::TC_GetPt100ChannelCD()
{
	//获得第3&4路温度值
    	std::string res=TC_Cmd_package(ID_TC_GetPt100ChannelCD,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_GetPt100ChannelCD recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_GetPt100ChannelCD);
		}
    	return res;
}

std::string  ExternMode::TC_SAFETY_GetLEDStates()
{
	//获取三色灯状态
    	std::string res=TC_Cmd_package(ID_SAFETY_GetLEDStates,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_SAFETY_GetLEDStates recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_SAFETY_GetLEDStates);
		}
    	return res;
}

std::string  ExternMode::TC_SAFETY_SetLEDColor(short int coloe)
{
	//控制三色灯颜色
    	std::string res=TC_Cmd_package(ID_SAFETY_SetLEDColor,coloe,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_SAFETY_SetLEDColor recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_SAFETY_SetLEDColor);
		}
    	return res;
}

std::string  ExternMode::TC_SAFETY_GetIOInput()
{
	//安全输入状态
    	std::string res=TC_Cmd_package(ID_SAFETY_GetIOInput,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_SAFETY_GetIOInput recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_SAFETY_GetIOInput);
		}
	
    	return res;
}
std::string  ExternMode::TC_LED_LEFT()
{
	//安全输入状态
    	std::string res=TC_Cmd_package(ID_TC_LED_LEFT,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_LED_LEFT recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_LED_LEFT);
		}
	
    	return res;
}
std::string  ExternMode::TC_LED_RIGHT()
{
	//安全输入状态
    	std::string res=TC_Cmd_package(ID_TC_LED_RIGHT,0,0);
       //发送命令
       pimpl->receivedData.clear();
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	int size = netrecvDelay(pimpl,nomal_length,10,"TC_LED_RIGHT recv timeout");
	if(size>=nomal_length){
			Devonline.Set_connect();
			RecordData(ID_TC_LED_RIGHT);
		}
	
    	return res;
}

std::string  ExternMode::TC_Ctrl_CentrControl(char fan1,char fan2,char color,char lightL,char lightR)
{
	//控制三色灯颜色
	char cmd=0;
	
	cmd = fan1|(fan2<<2)|(color<<4);
	short int Icmd=cmd;
	Icmd<<=8;
	Icmd&=0xff00;

	
	cmd = 0;
	cmd = lightL|(lightR<<1);
	
	char * ps1  = (char *)(&Icmd);
	*(ps1) = cmd;


	
	std::string res=TC_Cmd_package(ID_Ctrl_CentrControl,Icmd,0);
       //发送命令
       pimpl->receivedData.clear();
       boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	write(res );
	boost::this_thread::sleep(boost::posix_time::milliseconds(10));
	int size = netrecvDelay(pimpl,extend_length,30,"TC_Ctrl_CentrControl recv timeout");
	if(size>=extend_length){
			Devonline.Set_connect();
			RecordData(ID_Ctrl_CentrControl);
		}	
    	return res;
}

void  ExternMode::RecordData(char cmd)
{
	
		switch((unsigned char)cmd){
		 	  case ID_TC_GetBox1_temHuim:
			  	if(check_nomal_recv_buffer(ID_TC_GetBox1_temHuim)>0){
					// 1路 温湿度
					ExternSensor_Mode_Temp_humi  * pMode_Temp_humi = 
						SensorMsg.mutable_temp_humi(0);
					pMode_Temp_humi->set_interior_temp(Get_Sdata1());
					pMode_Temp_humi->set_interior_humi(Get_Sdata2());						
			  		}
			  	break;
		         case ID_TC_GetBox2_temHuim:
			  	if(check_nomal_recv_buffer(ID_TC_GetBox2_temHuim)>0){
					// 2路 温湿度
					ExternSensor_Mode_Temp_humi  * pMode_Temp_humi = 
						SensorMsg.mutable_temp_humi(1);
					pMode_Temp_humi->set_interior_temp(Get_Sdata1());
					pMode_Temp_humi->set_interior_humi(Get_Sdata2());						
			  		}
				break;
		         case ID_TC_GetFan1_openvalu:
			  	if(check_nomal_recv_buffer(ID_TC_GetFan1_openvalu)>0){

			  		}
				 break;
		         case ID_TC_GetFan1_closevalu:
			  	if(check_nomal_recv_buffer(ID_TC_GetFan1_closevalu)>0){

			  		}
				 break;
		         case ID_TC_GetFan2_openvalu:
			  	if(check_nomal_recv_buffer(ID_TC_GetFan2_openvalu)>0){

			  		}
				 break;
		         case ID_TC_GetFan2_closevalu:
			  	if(check_nomal_recv_buffer(ID_TC_GetFan2_closevalu)>0){

			  		}
				 break;
		         case ID_TC_Fan2_enable:
			  	if(check_nomal_recv_buffer(ID_TC_Fan2_enable)>0){

			  		}
				 break;
		         case ID_TC_Fan2_release:
			  	if(check_nomal_recv_buffer(ID_TC_Fan2_release)>0){

			  		}
				 break;
		         case ID_TC_Fan1_enable:
			  	if(check_nomal_recv_buffer(ID_TC_Fan1_enable)>0){

			  		}
				 break;
		         case ID_TC_Fan1_release:
			  	if(check_nomal_recv_buffer(ID_TC_Fan1_release)>0){

			  		}
				 break;
		         case ID_TC_SetFan1_valu:
			  	if(check_nomal_recv_buffer(ID_TC_SetFan1_valu)>0){

			  		}
				 break;
		         case ID_TC_SetFan2_valu:
			  	if(check_nomal_recv_buffer(ID_TC_SetFan2_valu)>0){

			  		}
				 break;
		         case ID_TC_GetFan1_valu:
			  	if(check_nomal_recv_buffer(ID_TC_GetFan1_valu)>0){

			  		}
				 break;
		         case ID_TC_GetFan2_valu:
			  	if(check_nomal_recv_buffer(ID_TC_GetFan1_closevalu)>0){

			  		}
				 break;
		         case ID_TC_GetPt100ChannelAB:
			  	if(check_nomal_recv_buffer(ID_TC_GetPt100ChannelAB)>0){
						SensorMsg.set_temp_pt100(0,Get_Sdata1());
						SensorMsg.set_temp_pt100(1,Get_Sdata2());
			  		}
				 break;
		         case ID_TC_GetPt100ChannelCD:
			  	if(check_nomal_recv_buffer(ID_TC_GetPt100ChannelCD)>0){
						SensorMsg.set_temp_pt100(3,Get_Sdata1());
						SensorMsg.set_temp_pt100(4,Get_Sdata2());
			  		}
				 break;
		         case ID_SAFETY_GetLEDStates:
			  	if(check_nomal_recv_buffer(ID_SAFETY_GetLEDStates)>0){
						char led = (char)(Get_Sdata2()&0x00ff);
						
					 	SensorMsg.set_led_status(Get_Ledstr(led));
			  		}
				 break;
		         case ID_SAFETY_SetLEDColor:
			  	if(check_nomal_recv_buffer(ID_SAFETY_SetLEDColor)>0){

			  		}
				 break;
		         case ID_SAFETY_GetIOInput:	
			  	if(check_nomal_recv_buffer(ID_SAFETY_GetIOInput)>0){
						//防跌落
						char infrared =(char)((Get_Sdata1()&0xff00)>>8); 
						//SensorMsg.set_io_infrared(infrared);
						Set_infrared(infrared);
						//防碰撞
						char collision =(char)(Get_Sdata1()&0x00ff);
						//SensorMsg.set_io_collision(collision);
						Set_collision(collision);
						//PX24
						char PX24 =(char)((Get_Sdata1()&0xff00)>>8); 
						
						ExternSensor_Mode_PX24ES * pMode_PX24ES = 
						SensorMsg.mutable_px24es();
						pMode_PX24ES->set_out1((PX24&0x01));
						pMode_PX24ES->set_out2(((PX24&0x02)>>1));
						pMode_PX24ES->set_extraneouslight_out(((PX24&0x04)>>3));
						
			  		}
				 break;
		         case ID_Ctrl_CentrControl:	
				 //std::cout<<"recv return "<<" ID_Ctrl_CentrControl"<<std::endl;
			  	if(check_extend_recv_buffer(ID_Ctrl_CentrControl)>0){
						//recvsize++;
						//std::cout<<"check right "<<" ID_Ctrl_CentrControl :"<<recvsize<<std::endl;
						Record_Extend_buffer();
			  		}
				 break;
				 
			  case ID_TC_LED_LEFT:	
			  	if(check_nomal_recv_buffer(ID_TC_LED_LEFT)>0){

			  		}
				 break;
				 
			  case ID_TC_LED_RIGHT:	
			  	if(check_nomal_recv_buffer(ID_TC_LED_RIGHT)>0){

			  		}
				 break;
			default:
				break;
			}
		Readarray.assign(0);
}

int  ExternMode::check_nomal_recv_buffer( char cmd)
{
	const char* ch=pimpl->receivedData.c_str();
	int size = pimpl->receivedData.size();
	if(size == nomal_length){
		if((unsigned char)ch[0] != HEAD){return -1;}
		if((unsigned char)ch[1] != ADD){return -2;}
		if((unsigned char)ch[2] != (unsigned char)cmd){return -3;}
		if((unsigned char)ch[nomal_length-1] != 0xB0){return -4;}
		
		
		for(int index=0;index<nomal_length;index++){
			Readarray[index] = ch[index];
			}
	}
	else{
			int index=0;
			for(index=0;index<size;index++){
				if((unsigned char)ch[index] == HEAD){
					if((unsigned char)ch[1] == ADD){break;}
						}
			}
			int leng=(size-index)>nomal_length?nomal_length:(size-index);
			if(leng<nomal_length){
					return -1;
				}
			if((unsigned char)ch[index+leng-1]!= 0xB0){return -4;}
			
		for(int dex=0;dex<nomal_length;dex++){
			Readarray[dex] = ch[index+dex];
			}			
		}
	
   	pimpl->receivedData.clear();
	return 1;
}
int  ExternMode::check_extend_recv_buffer(char cmd)
{
	//boost::array<char,nomal_length> data;
	const char* ch=pimpl->receivedData.c_str();
	int size = pimpl->receivedData.size();

	if((unsigned char)ch[0] != 0xA0){return -1;}
	if((unsigned char)ch[1] != 0x01){return -2;}
	if((unsigned char)ch[2] != (unsigned char)cmd){return -3;}
	if((unsigned char)ch[extend_length-1] != 0xB0){return -4;}

	for(int index=0;index<extend_length;index++){
		Readarray[index] = ch[index];
		}
	
   	pimpl->receivedData.clear();
	return 1;
}

short int  ExternMode::Get_Sdata1()
{
	short int Data1;
	char * ps1  = (char *)(&Data1);
	
    * (ps1+1) = Readarray[3];
    * (ps1+0) = Readarray[4];	
	
	return Data1;
}

short int  ExternMode::Get_Sdata2()
{
	short int Data1;
	char * ps1  = (char *)(&Data1);
	
    * (ps1+1) = Readarray[5];
    * (ps1+0) = Readarray[6];	
	
	return Data1;
}

std::string  ExternMode::Get_Ledstr(char led)
{
	//"LED_CLOSE" "LED_GREEN" "LED_RED" "LED_BLUE" "LED_GREEN_FLI" "LED_RED_FLI" "LED_BLUE_FLI"

	std::string str;
	switch(led){
		case 0:
			str= "LED_CLOSE";
			break;
		case 1:
			str= "LED_GREEN";
			break;
		case 2:
			str= "LED_RED";
			break;
		case 3:
			str= "LED_BLUE";
			break;
		case 4:
			str= "LED_GREEN_FLI";
			break;
		case 5:
			str= "LED_RED_FLI";
			break;
		case 6:
			str= "LED_BLUE_FLI";
			break;
		default:
			str= "LED_CLOSE";
			break;
		}
	
	return str;
}

void ExternMode::Set_infrared(char IO)
{
	boost::array<int,8> data;
	for(int index=0;index<8;index++){
		data[index]= (unsigned int)((IO>>index)&0x01);
		SensorMsg.set_io_infrared(index,data[index]);
		//std::cout<< "io_infrared["<<index<<"] "<<SensorMsg.io_infrared( index)<<std::endl;
		}
	
}

void ExternMode::Set_collision(char IO)
{
	boost::array<int,8> data;
	for(int index=0;index<8;index++){
		data[index]= (unsigned int)((IO>>index)&0x01);
		SensorMsg.set_io_collision(index,data[index]);
		//std::cout<< "io_collision["<<index<<"] "<<SensorMsg.io_collision(index)<<std::endl;
		}	
}

void ExternMode::Record_Extend_buffer()
{
	//boost::array<char,nomal_length> data;
	//const char* ch=pimpl->receivedData.c_str();
	char* ch = Readarray.c_array();
	int size = extend_length;

	char fan=ch[3];
	
	ExternSensor_Mode_fan *  pMsg_Mode_fan = SensorMsg.mutable_fan_msg(0);
	pMsg_Mode_fan->set_fan_status((unsigned int)(fan&0x01));
	pMsg_Mode_fan->set_vaule_open(ch[21]);
	pMsg_Mode_fan->set_vaule_close(ch[22]);

	
	pMsg_Mode_fan = SensorMsg.mutable_fan_msg(1);
	pMsg_Mode_fan->set_fan_status((unsigned int)((fan>>1)&0x01));
	pMsg_Mode_fan->set_vaule_open(ch[23]);
	pMsg_Mode_fan->set_vaule_close(ch[24]);

	SensorMsg.set_led_status(Get_Ledstr((unsigned char)((fan>>2)&0x03)));

	// 4路PT100
	short int tem=0;
	char * ps1  = (char *)(&tem);
	* (ps1+1) = ch[4];
	* (ps1+0) = ch[5];
	SensorMsg.set_temp_pt100(0,tem);

	ps1  = (char *)(&tem);
	* (ps1+1) = ch[6];
	* (ps1+0) = ch[7];
	SensorMsg.set_temp_pt100(1,tem);	

	
	ps1  = (char *)(&tem);
	* (ps1+1) = ch[8];
	* (ps1+0) = ch[9];
	SensorMsg.set_temp_pt100(2,tem);	

	
	ps1  = (char *)(&tem);
	* (ps1+1) = ch[10];
	* (ps1+0) = ch[11];
	SensorMsg.set_temp_pt100(3,tem);

	// 2路温湿度
	ps1  = (char *)(&tem);
	* (ps1+1) = ch[12];
	* (ps1+0) = ch[13];
	ExternSensor_Mode_Temp_humi * pMode_Temp_humi = SensorMsg.mutable_temp_humi(0);
	pMode_Temp_humi->set_interior_temp(tem);
	unsigned char huim1=ch[14];
	pMode_Temp_humi->set_interior_humi(huim1);

	
	ps1  = (char *)(&tem);
	* (ps1+1) = ch[15];
	* (ps1+0) = ch[16];
	pMode_Temp_humi = SensorMsg.mutable_temp_humi(1);
	pMode_Temp_humi->set_interior_temp(tem);
	unsigned char huim2=ch[17];
	pMode_Temp_humi->set_interior_humi(huim2);	
	
	//防跌落
	Set_infrared(ch[18]);

	//防碰撞
	Set_collision(ch[19]);

	//松下红外
	char PX24 =ch[20]; 
						
	ExternSensor_Mode_PX24ES * pMode_PX24ES = 
	SensorMsg.mutable_px24es();
	pMode_PX24ES->set_out1(((PX24>>0)&0x01));
	pMode_PX24ES->set_out2(((PX24>>1)&0x01));
	pMode_PX24ES->set_extraneouslight_out(((PX24>>2)&0x01));

	#if 0 
	Printf_Extend_buffer();
	#endif

	
}

void ExternMode::Printf_Extend_buffer()
{
	 std::cout<< "Printf_Extend_buffer:";
	 ExternSensor_Mode_fan *  pMsg_Mode_fan = SensorMsg.mutable_fan_msg(0);
	if(pMsg_Mode_fan->has_fan_mode()){
			std::cout<< "Printf_fan_mode[0]:"<<pMsg_Mode_fan->fan_mode()<<std::endl;
		}
	if(pMsg_Mode_fan->has_fan_status()){
			std::cout<< "Printf_fan_statusr[0]:"<<pMsg_Mode_fan->fan_status()<<std::endl;
		}
	if(pMsg_Mode_fan->has_vaule_open()){
			std::cout<< "vaule_open[0]:"<<pMsg_Mode_fan->vaule_open()<<std::endl;
		}
	
	if(pMsg_Mode_fan->has_vaule_close()){
			std::cout<< "vaule_close[0]:"<<pMsg_Mode_fan->vaule_close()<<std::endl;
		}	 

	 pMsg_Mode_fan = SensorMsg.mutable_fan_msg(1);
	if(pMsg_Mode_fan->has_fan_mode()){
			std::cout<< "Printf_fan_mode[1]:"<<pMsg_Mode_fan->fan_mode()<<std::endl;
		}
	if(pMsg_Mode_fan->has_fan_status()){
			std::cout<< "Printf_fan_statusr[1]:"<<pMsg_Mode_fan->fan_status()<<std::endl;
		}
	if(pMsg_Mode_fan->has_vaule_open()){
			std::cout<< "vaule_open[1]:"<<pMsg_Mode_fan->vaule_open()<<std::endl;
		}
	
	if(pMsg_Mode_fan->has_vaule_close()){
			std::cout<< "vaule_close[1]:"<<pMsg_Mode_fan->vaule_close()<<std::endl;
		}

	std::cout<< "led_status:"<<SensorMsg.led_status()<<std::endl;

	std::cout<< "temp_pt100(0):"<<SensorMsg.temp_pt100(0)<<std::endl;
	std::cout<< "temp_pt100(1):"<<SensorMsg.temp_pt100(1)<<std::endl;
	std::cout<< "temp_pt100(2):"<<SensorMsg.temp_pt100(2)<<std::endl;
	std::cout<< "temp_pt100(3):"<<SensorMsg.temp_pt100(3)<<std::endl;

	ExternSensor_Mode_Temp_humi * pMode_Temp_humi = SensorMsg.mutable_temp_humi(0);
	std::cout<< "interior_temp(0):"<<pMode_Temp_humi->interior_temp()<<std::endl;
	std::cout<< "interior_humi(0):"<<pMode_Temp_humi->interior_humi()<<std::endl;

	pMode_Temp_humi = SensorMsg.mutable_temp_humi(1);
	std::cout<< "interior_temp(1):"<<pMode_Temp_humi->interior_temp()<<std::endl;
	std::cout<< "interior_humi(1):"<<pMode_Temp_humi->interior_humi()<<std::endl;


	ExternSensor_Mode_PX24ES * pMode_PX24ES = 
	SensorMsg.mutable_px24es();
	std::cout<< "PX24ES_out1:"<<pMode_PX24ES->out1()<<std::endl;
	std::cout<< "PX24ES_out2:"<<pMode_PX24ES->out2()<<std::endl;
	std::cout<< "PX24ES_extraneouslight_out:"<<pMode_PX24ES->extraneouslight_out()<<std::endl;

	for(int index=0;index<8;index++){
		std::cout<< "io_infrared["<<index<<"] "<<SensorMsg.io_infrared( index)<<std::endl;
		}

	for(int index=0;index<8;index++){
		std::cout<< "io_collision["<<index<<"] "<<SensorMsg.io_collision(index)<<std::endl;
		}	
	
}
