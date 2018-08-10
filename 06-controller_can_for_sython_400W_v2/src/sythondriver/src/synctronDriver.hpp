#pragma once


#include <boost/smart_ptr.hpp>
#include <boost/array.hpp>
#include <numeric>
#include <string>
#include <iostream>
#include "message.hpp"
#include<map>





class synctronDriver
{

    

public:


    typedef      short                  int16; 
    typedef      short                  INT16; 
    typedef    unsigned short int       uint16; 
    typedef    unsigned short int       UINT16; 
    
    typedef    int                      int32; 
    typedef    int                      INT32; 
    typedef    unsigned int             uint32; 
    typedef    unsigned int             UINT32;
    
    enum CMD{
         ID_GetStatus16=10,
         ID_GetStatus16_ACK=11,
         ID_GetStatus16_ERROR=12,
                
         ID_GetStatus32=13,
         ID_GetStatus32_ACK=14,
         ID_GetStatus32_ERROR=15,
                
         ID_GetParam16=20,
         ID_GetParam16_ACK=21,
         ID_GetParam16_ERROR=22,
                
         ID_GetParam32=23,
         ID_GetParam32_ACK=24,
         ID_GetParam32_ERROR=25,
                
         ID_SetParam16=30,
         ID_SetParam16_ACK=31,
         ID_SetParam16_ERROR=32,
                
         ID_SetParam32=33,
         ID_SetParam32_ACK=34,
         ID_SetParam32_ERROR=35,
                
         ID_SetParam16UR=36,
         ID_SetParam16UR_ACK=37,
         ID_SetParam16UR_ERROR=38,
                
         ID_SetCmd16=40,
         ID_SetCmd16_ACK=41,
         ID_SetCmd16_ERROR=42,
                
         ID_SetCmd32=43,
         ID_SetCmd32_ACK=44,
         ID_SetCmd32_ERROR=45,

	 ID_AUTURETURN=0xCA
        };
    enum sattues_addr{
        //Dn码
                /*电机当前的速度*/
         DN_GetCrurrentSpeed=0x0000,
         DN_GetEffectiveTorque_I =0x0002,   //'电机有效转矩率(绝对值): 电流法

        // DN_GetSpeedCmd =0x0008,  //'电机速度命令给定值
         //DN_GetCruAbsSpeed= 0x0009,  //'电机当前运行速度绝对值,
         DN_GetEffectiveTorque_T =0x000C, // '电机有效转矩率(绝对值）：转矩观测法
         DN_GetIpmTem =0x0024, // '功率器件温度（单位：度）
         DN_GetDrivBoardTem =0x0025, // ''控制板温度（单位：度）
         DN_GetUdc =0x0080, //'直流母线电压值Udc（单位：0.1V）
        DN_GetAppStatus=0x002C, //'应用层 状态字
        DN_GetDrivStatus =0x005B, //'驱动控制应用状态字
        DN_GetCruError =0x0036, //''当前扫描的系统故障代码
        DN_GetPreError =0x0037, //上拍扫描的系统故障代码 
        DN030_DIN = 0x0030,//输入io物理输入状态
        DN007_CMDVelocity  = 0x0007,   //速度指令
        DN032_DIO_IN  = 0x0032,//'数字量逻辑输入

         // D19 总线模式下，电机绝对位置指令的时间累积。
         // D1A 总线模式下，电机绝对位置指令的时间累积。
         // D1B 总线模式下，电机绝对位置指令（单位：编码器 脉冲）
         // D1C 总线模式下，电机绝对位置指令（单位：编码器 脉冲）
        //  D1D 总线模式下，电机绝对位置（单位：编码器 脉冲）
        //  D1E 总线模式下，电机绝对位置（单位：编码器 脉冲）
           
           DN_GetCumulativePos =0x0019,   //32w位
           DN_GetCmdPos =0x001B, //32w位
           DN_GetCruPos =0x001D, //32w位

        };
     enum Cmd_addr{
        //Cn码
                /*电机当前的速度*/
         CN_Setspeed=0x0000,   //设置命令参数 Cn 00给定电机的速度(100rpm
         CN_SetTorque=0x0001,  //给定电机的转矩
         CN_SetAbspos=0x0003,  //给定电机的绝对位

        };  
     enum Fnmd_addr{
        //Cn码
                /*电机当前的速度*/
         FN_SETHS_Endable=0x0010,   
         FN_ClearErrors=0x0011, 
         FN_EmergencyStop=0x0012,
         FN0E3_LIFEGUARD  = 0x00E3,   //通信中断停车E3

        };  

	struct DEVICE_DRIV_Status{		
		unsigned char bit0_isSRDY;		//系统上电自检通过，等待伺服使能（SON）信号
		unsigned char bit1_isENA_SRV;	 //伺服已经使能	
		unsigned char bit2_isRes1;	      //保留	
		unsigned char bit3_isFault;	     //严重故障，必须通过断电才能清除故障报警状态	
		unsigned char bit4_isRes2;	    // 保留	
		unsigned char bit5_EMGING;	   //伺服电机急停状态
		unsigned char bit6_isDIS_SRV;  //内部使能无效，当驱动器发生异常报警时有效	
		unsigned char bit7_Warning;	   //般警告，可以通过报警清除信号（ARST）清除报警状态			
		unsigned char bit8_isRes3; //		
		unsigned char bit9_isRes4;		
		unsigned char bit10_isTR;	 //位置（位置模式）、转速（速度模式）、转矩到达（转矩模式）任意一种有效时即有效；否则无效	
		unsigned char bit11_isINL;	  //	正转禁止或者反转禁止时有效；否则无效
		unsigned char bit12_isRes5;		
		unsigned char bit13_isRes6;		
		unsigned char bit14_isRes7;		
		unsigned char bit15_isRes8;		
		};
private:

        char m_add;   //设备自身地址
        int  m_dir_flag;    //转动方向标志 顺时针1 逆时针-1
        


        boost::array<int,15>framflushcounter;
        std::map<int,std::string >errormap;
public:
	
        INT16 m_cru_speed;  //电机当前运行速度
        UINT16 m_effectiveTorque_I ;  //'电机有效转矩率(绝对值): 电流法
        UINT16 m_cru_speedcmd;  //'电机速度调节指令值
        UINT16 m_cru_absspeed;  //'电机当前运行速度绝对值
        UINT16 m_effectiveTorque_T;  //'电机有效转矩率(绝对值）：转矩观测法
        UINT16 m_IpmTem;  //'功率器件温度（单位：度）
        UINT16 m_drivboardTem;  //'控制板温度（单位：度）
        UINT16 m_Udc;  //母线电压值
        UINT16 m_AppStatus;  //应用状态字
        UINT16 m_DrivStatus;  //控制字
        UINT16 m_CruError;  //当前错误
        UINT16 m_PreError;  //前一次错误
        //UINT32 m_CumulativePos;  //'总线模式下，电机绝对位置（单位：编码器 脉冲）
       // UINT32 m_CmdPos;  //'总线模式下，电机绝对位置指令（单位：编码器 脉冲）
        UINT32 m_CruPos;  //'电机当前位置
        UINT16 m_Dins;
	void recordBitstauts(UINT16 statues);
	struct DEVICE_DRIV_Status m_BitStatus;
	
    synctronDriver(char id);
    synctronDriver();
    ~synctronDriver();
    void set_add(char id);
	unsigned char Getadd();
	 void set_dir(int dir);
	 int dir();
	 
    std::string HSDriver_GetCrurrentSpeed(char targID);
    std::string HSDriver_GetCrurrentHZ(char targID);
    std::string HSDriver_GetStatus16(char targID,UINT16 cmdaddr);
    std::string HSDriver_GetStatus32(char targID,UINT16 cmdaddr);
    std::string HSDriver_GetParam16(char targID,UINT16 cmdaddr);
    std::string HSDriver_GetParam32(char targID,UINT16 cmdaddr);
    std::string HSDriver_SetParam16(char targID,UINT16 cmdaddr,UINT16 res_Data);
    std::string HSDriver_SetParam32(char targID,UINT16 cmdaddr,UINT16 res_Data1,UINT16 res_Data2);
    std::string HSDriver_SetCmd16(char targID,UINT16 cmdaddr,UINT16 res_Data);
    std::string HSDriver_SetCmd32(char targID,UINT16 cmdaddr,UINT16 res_Data1,UINT16 res_Data2);

    std::string HSDriver_GetAllstatues(char targID);

        INT16 cru_speed();
        UINT16 effectiveTorque_I() ; 
        UINT16 cru_speedcmd();  //电机当前运行速度
        UINT16 cru_absspeed();  //电机当前运行速度
        UINT16 effectiveTorque_T();  //电机当前运行速度
        UINT16 IpmTem();  //电机当前运行速度
        UINT16 drivboardTem();  //电机当前运行速度
        UINT16 Udc();  //电机当前运行速度
        UINT16 AppStatus();  //电机当前运行速度
        UINT16 DrivStatus();  //电机当前运行速度
        UINT16 CruError();  //电机当前运行速度
        UINT16 PreError();  //电机当前运行速度
        //UINT32 CumulativePos();  //电机当前运行速度
       //UINT32 CmdPos();  //电机当前运行速度
        UINT32 CruPos();  //电机当前运行速度
         UINT16 Dins();  //电机当前运行速度

       // void StatusRecord(std::string &status);
       void paramRecord(message &msg,CMD cmd);
       void Statusprint();
       void signleRecord(message &msg);
	   void autureturnRecord(message &msg);

        std::string GetStrError(); 


	std::string Cmd_SetEnable();
	std::string Cmd_SetRealse();
	std::string Cmd_GetCruPos();
	std::string Cmd_GetUdc();
	std::string Cmd_GetVelocity();
	std::string Cmd_GetError();

	std::string Cmd_SetVelocity(INT16 Velocity);
	std::string Cmd_SetStop();
	std::string Cmd_GetDinStatues();
	std::string Cmd_GetCurrent();
	std::string Cmd_GetCmdVelocity();
	std::string Cmd_SetClearError();
	std::string Cmd_SetLifeGuard(INT16 TIMEOUT);
	std::string Cmd_QuickStop();
	
	
	


};

