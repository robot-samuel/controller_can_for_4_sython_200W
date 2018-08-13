#include "synctronDriver.hpp"
#include <boost/format.hpp>

#define  DEBUG_ECHO 0
//D8
#define BROADCAST  0x0000
#define P2P  0x0100

//D9-D10
#define CHANGSTATUS  0x0600
#define CHANGCMD         0x0400
#define SUPERSTATUS   0x0100
#define SUPERCMD         0x0000

//点到点
#define ID_UNKNOW  0x00

typedef      short                  int16; 
typedef      short                  INT16; 
typedef    unsigned short int       uint16; 
typedef    unsigned short int       UINT16; 

typedef    int                      int32; 
typedef    int                      INT32; 
typedef    unsigned int             uint32; 
typedef    unsigned int             UINT32;

using namespace std;


synctronDriver::synctronDriver(char id)
    :m_add(id)
{
  //  framflushcounter.assign(0);
         m_cru_speed=0;  //电机当前运行速度
         m_effectiveTorque_I =0;  //电机当前运行速度
         m_cru_speedcmd=0;  //电机当前运行速度
         m_cru_absspeed=0;  //电机当前运行速度
         m_effectiveTorque_T=0;  //电机当前运行速度
         m_IpmTem=0;  //电机当前运行速度
         m_drivboardTem=0;  //电机当前运行速度
         m_Udc=0;  //电机当前运行速度
         m_AppStatus=0;  //电机当前运行速度
         m_DrivStatus=0;  //电机当前运行速度
         m_CruError=0;  //电机当前运行速度
         m_PreError=0;  //电机当前运行速度
         //m_CumulativePos=0;  //电机当前运行速度
         //m_CmdPos=0;  //电机当前运行速度
         m_CruPos=0;  //电机当前运行速度    
         m_Dins = 0;

         errormap.insert( pair <int, std::string>(1100 , "E AbPE ") );
         errormap.insert( pair <int, std::string>(1200 , "E brSL ") );
         errormap.insert( pair <int, std::string>(1201 , "E broL ") );
         errormap.insert( pair <int, std::string>(1202 , "E brEr ") );
         errormap.insert( pair <int, std::string>(1301 , "E coUt ") );
         errormap.insert( pair <int, std::string>(1310 , "E cLoS ") );
         errormap.insert( pair <int, std::string>(1401 , "E dnRE ") );
         errormap.insert( pair <int, std::string>(1500 , "E EnAb ") );
         errormap.insert( pair <int, std::string>(1510 , "E EncU ") );
         errormap.insert( pair <int, std::string>(1600 , "E FrAE ") );
         errormap.insert( pair <int, std::string>(1700 , "E GEAr ") );
         errormap.insert( pair <int, std::string>(2200 , "E LUdc ") );
         errormap.insert( pair <int, std::string>(2500 , "E oc-A  ") );
         errormap.insert( pair <int, std::string>(2501 , "E oc-b  ") );
         errormap.insert( pair <int, std::string>(2502 , "E oc-C  ") );
         errormap.insert( pair <int, std::string>(2510 , "E oLod ") );
         errormap.insert( pair <int, std::string>(2520 , "E oSPE ") );
         errormap.insert( pair <int, std::string>(2530 , "E oUdc ") );
         errormap.insert( pair <int, std::string>(2600 , "E PArA ") );
         errormap.insert( pair <int, std::string>(2610 , "E PEOU ") );
         errormap.insert( pair <int, std::string>(2620 , "E PHAS ") );
         errormap.insert( pair <int, std::string>(2630 , "E PHot ") );
         errormap.insert( pair <int, std::string>(2631 , "E PoEr ") );
         errormap.insert( pair <int, std::string>(2640 , "E PorF ") );
         errormap.insert( pair <int, std::string>(2645 , "E PosE ") );
         errormap.insert( pair <int, std::string>(2650 , "E PoUt ") );
         errormap.insert( pair <int, std::string>(2660 , "E PS1E ") );
         errormap.insert( pair <int, std::string>(2661 , "E PS2E ") );
         errormap.insert( pair <int, std::string>(2900 , "E SPEE ") );
         errormap.insert( pair <int, std::string>(3000 , "E Tcon ") );
         errormap.insert( pair <int, std::string>(3100 , "E Ubrt ") );
         errormap.insert( pair <int, std::string>(3110 , "E USPn ") );
         errormap.insert( pair <int, std::string>(3600 , "E 2LoS ") );
         errormap.insert( pair <int, std::string>(3601 , "E 2EtE ") );
}

synctronDriver::synctronDriver()
{
  //  framflushcounter.assign(0);
         m_cru_speed=0;  //电机当前运行速度
         m_effectiveTorque_I =0;  //电机当前运行速度
         m_cru_speedcmd=0;  //电机当前运行速度
         m_cru_absspeed=0;  //电机当前运行速度
         m_effectiveTorque_T=0;  //电机当前运行速度
         m_IpmTem=0;  //电机当前运行速度
         m_drivboardTem=0;  //电机当前运行速度
         m_Udc=0;  //电机当前运行速度
         m_AppStatus=0;  //电机当前运行速度
         m_DrivStatus=0;  //电机当前运行速度
         m_CruError=0;  //电机当前运行速度
         m_PreError=0;  //电机当前运行速度
        // m_CumulativePos=0;  //电机当前运行速度
//         m_CruPos=0;  //电机当前运行速度    
 	m_Dins = 0;
		
         m_add = 0;
         errormap.insert( pair <int, std::string>(1100 , "E AbPE ") );
         errormap.insert( pair <int, std::string>(1200 , "E brSL ") );
         errormap.insert( pair <int, std::string>(1201 , "E broL ") );
         errormap.insert( pair <int, std::string>(1202 , "E brEr ") );
         errormap.insert( pair <int, std::string>(1301 , "E coUt ") );
         errormap.insert( pair <int, std::string>(1310 , "E cLoS ") );
         errormap.insert( pair <int, std::string>(1401 , "E dnRE ") );
         errormap.insert( pair <int, std::string>(1500 , "E EnAb ") );
         errormap.insert( pair <int, std::string>(1510 , "E EncU ") );
         errormap.insert( pair <int, std::string>(1600 , "E FrAE ") );
         errormap.insert( pair <int, std::string>(1700 , "E GEAr ") );
         errormap.insert( pair <int, std::string>(2200 , "E LUdc ") );
         errormap.insert( pair <int, std::string>(2500 , "E oc-A  ") );
         errormap.insert( pair <int, std::string>(2501 , "E oc-b  ") );
         errormap.insert( pair <int, std::string>(2502 , "E oc-C  ") );
         errormap.insert( pair <int, std::string>(2510 , "E oLod ") );
         errormap.insert( pair <int, std::string>(2520 , "E oSPE ") );
         errormap.insert( pair <int, std::string>(2530 , "E oUdc ") );
         errormap.insert( pair <int, std::string>(2600 , "E PArA ") );
         errormap.insert( pair <int, std::string>(2610 , "E PEOU ") );
         errormap.insert( pair <int, std::string>(2620 , "E PHAS ") );
         errormap.insert( pair <int, std::string>(2630 , "E PHot ") );
         errormap.insert( pair <int, std::string>(2631 , "E PoEr ") );
         errormap.insert( pair <int, std::string>(2640 , "E PorF ") );
         errormap.insert( pair <int, std::string>(2645 , "E PosE ") );
         errormap.insert( pair <int, std::string>(2650 , "E PoUt ") );
         errormap.insert( pair <int, std::string>(2660 , "E PS1E ") );
         errormap.insert( pair <int, std::string>(2661 , "E PS2E ") );
         errormap.insert( pair <int, std::string>(2900 , "E SPEE ") );
         errormap.insert( pair <int, std::string>(3000 , "E Tcon ") );
         errormap.insert( pair <int, std::string>(3100 , "E Ubrt ") );
         errormap.insert( pair <int, std::string>(3110 , "E USPn ") );
         errormap.insert( pair <int, std::string>(3600 , "E 2LoS ") );
         errormap.insert( pair <int, std::string>(3601 , "E 2EtE ") );
}


synctronDriver::~synctronDriver()
{
}

void synctronDriver::set_add(char id){
    m_add = id;
}

unsigned char synctronDriver::Getadd()
{
	return m_add;
 }


 void synctronDriver::set_dir(int dir)
{
    this->m_dir_flag = dir;
}

int synctronDriver::dir()
{
    return this->m_dir_flag ;
}

std::string synctronDriver::HSDriver_GetCrurrentSpeed(char targID)
{

    std::string res;
   // const  UINT16 DN_GetCrurrentSpeed = 0x0000;
    res = HSDriver_GetStatus16(targID,DN_GetCrurrentSpeed);
    return res;

}

std::string synctronDriver::HSDriver_GetCrurrentHZ(char targID)
{
    std::string res;
  const  UINT16 DN_GetCrurrentHZ = 0x0001;
    res = HSDriver_GetStatus16(targID,DN_GetCrurrentHZ);
    return res;
}

std::string synctronDriver::HSDriver_GetStatus16(char targID,UINT16 cmdaddr)
{

    std::string res;
    message msg;
   // const char ID_GetStatus16=10;
    
    msg.set_fram_info(0x08);
    msg.set_fram_ID(CHANGSTATUS+P2P+this->m_add);
    //msg.set_fram_data(data.c_array());
    msg.set_data_m_byte(targID, 0);
    
    msg.set_data_m_byte(ID_GetStatus16, 1);
    msg.set_data_m_param2(cmdaddr);
    msg.set_data_m_param3(0);
    msg.set_data_m_param4(0);

	#if DEBUG_ECHO
    	msg.print_hex();
	#endif
    
    res = msg.to_string();
    
  //  res.clear();
  //  res.assign(fram.begin(),fram.end());
    /*
     std::cout<< "HSDriver_GetCrurrentSpeed send:";
     for(std::size_t index=0;index<res.size();index++){
                      int x=(unsigned  char)res[index];
                       std::cout<<boost::format("%02X ")%x;
                  }
    std::cout<<"\n";
    */
    
    return res;
}

std::string synctronDriver::HSDriver_GetStatus32(char targID,UINT16 cmdaddr)
{

    std::string res;
    message msg;
    //const char ID_GetStatus32=13;

    msg.set_fram_info(0x08);
    msg.set_fram_ID(CHANGSTATUS+P2P+this->m_add);
    //msg.set_fram_data(data.c_array());
    msg.set_data_m_byte(targID, 0);
    
    msg.set_data_m_byte(ID_GetStatus32, 1);
    msg.set_data_m_param2(cmdaddr);
    msg.set_data_m_param3(0);
    msg.set_data_m_param4(0);
    
	#if DEBUG_ECHO
    	msg.print_hex();
	#endif
    
    res = msg.to_string();
    
  //  res.clear();
  //  res.assign(fram.begin(),fram.end());
    /*
     std::cout<< "HSDriver_GetCrurrentSpeed send:";
     for(std::size_t index=0;index<res.size();index++){
                      int x=(unsigned  char)res[index];
                       std::cout<<boost::format("%02X ")%x;
                  }
    std::cout<<"\n";
    */
    
    return res;
}

std::string synctronDriver::HSDriver_GetParam16(char targID,UINT16 cmdaddr)
{

    std::string res;
    message msg;
   // #define ID_GetParam16  20
    //const char ID_GetParam16=20;
    
    msg.set_fram_info(0x08);
    msg.set_fram_ID(CHANGSTATUS+P2P+this->m_add);
    //msg.set_fram_data(data.c_array());
    msg.set_data_m_byte(targID, 0);
    
    msg.set_data_m_byte(ID_GetParam16, 1);
    msg.set_data_m_param2(cmdaddr);
    msg.set_data_m_param3(0);
    msg.set_data_m_param4(0);
    
	#if DEBUG_ECHO
    	msg.print_hex();
	#endif
    
    res = msg.to_string();
    
  //  res.clear();
  //  res.assign(fram.begin(),fram.end());
    /*
     std::cout<< "HSDriver_GetCrurrentSpeed send:";
     for(std::size_t index=0;index<res.size();index++){
                      int x=(unsigned  char)res[index];
                       std::cout<<boost::format("%02X ")%x;
                  }
    std::cout<<"\n";
    */
    
    return res;
}

std::string synctronDriver::HSDriver_GetParam32(char targID,UINT16 cmdaddr)
{

    std::string res;
    message msg;
   // #define ID_GetParam32  23
    //const char ID_GetParam32=23;
    
    msg.set_fram_info(0x08);
    msg.set_fram_ID(CHANGSTATUS+P2P+this->m_add);
    //msg.set_fram_data(data.c_array());
    msg.set_data_m_byte(targID, 0);
    
    msg.set_data_m_byte(ID_GetParam32, 1);
    msg.set_data_m_param2(cmdaddr);
    msg.set_data_m_param3(0);
    msg.set_data_m_param4(0);
    
	#if DEBUG_ECHO
    	msg.print_hex();
	#endif
    
    res = msg.to_string();
    
  //  res.clear();
  //  res.assign(fram.begin(),fram.end());
    /*
     std::cout<< "HSDriver_GetCrurrentSpeed send:";
     for(std::size_t index=0;index<res.size();index++){
                      int x=(unsigned  char)res[index];
                       std::cout<<boost::format("%02X ")%x;
                  }
    std::cout<<"\n";
    */
    
    return res;
}
std::string synctronDriver::HSDriver_SetParam16(char targID,UINT16 
cmdaddr,UINT16 res_Data)
{

    std::string res;
    message msg;
   // #define ID_SetParam16  30
   // const char ID_SetParam16= 30;
    
    msg.set_fram_info(0x08);
    msg.set_fram_ID(CHANGSTATUS+P2P+this->m_add);
    //msg.set_fram_data(data.c_array());
    msg.set_data_m_byte(targID, 0);
    
    msg.set_data_m_byte(ID_SetParam16, 1);
    msg.set_data_m_param2(cmdaddr);
    msg.set_data_m_param3(res_Data);
    msg.set_data_m_param4(0);
    
	#if DEBUG_ECHO
    	msg.print_hex();
	#endif
    
    res = msg.to_string();
    
  //  res.clear();
  //  res.assign(fram.begin(),fram.end());
    /*
     std::cout<< "HSDriver_GetCrurrentSpeed send:";
     for(std::size_t index=0;index<res.size();index++){
                      int x=(unsigned  char)res[index];
                       std::cout<<boost::format("%02X ")%x;
                  }
    std::cout<<"\n";
    */
    
    return res;
}

std::string synctronDriver::HSDriver_SetParam32(char targID,UINT16 
cmdaddr,UINT16 res_Data1,UINT16 res_Data2)
{

    std::string res;
    message msg;
   // #define ID_SetParam32  33
   // const char ID_SetParam32= 33;
    
    msg.set_fram_info(0x08);
    msg.set_fram_ID(CHANGSTATUS+P2P+this->m_add);
    //msg.set_fram_data(data.c_array());
    msg.set_data_m_byte(targID, 0);
    
    msg.set_data_m_byte(ID_SetParam32, 1);
    msg.set_data_m_param2(cmdaddr);
    msg.set_data_m_param3(res_Data1);
    msg.set_data_m_param4(res_Data2);
    
	#if DEBUG_ECHO
    	msg.print_hex();
	#endif
    
    res = msg.to_string();
    
  //  res.clear();
  //  res.assign(fram.begin(),fram.end());
    /*
     std::cout<< "HSDriver_GetCrurrentSpeed send:";
     for(std::size_t index=0;index<res.size();index++){
                      int x=(unsigned  char)res[index];
                       std::cout<<boost::format("%02X ")%x;
                  }
    std::cout<<"\n";
    */
    
    return res;
}

std::string synctronDriver::HSDriver_SetCmd16(char targID,UINT16 
cmdaddr,UINT16 res_Data)
{

    std::string res;
    message msg;
   // #define ID_SetCmd16  40
    //const char ID_SetCmd16= 40;
    
    msg.set_fram_info(0x08);
    msg.set_fram_ID(CHANGSTATUS+P2P+this->m_add);
    //msg.set_fram_data(data.c_array());
    msg.set_data_m_byte(targID, 0);
    
    msg.set_data_m_byte(ID_SetCmd16, 1);
    msg.set_data_m_param2(cmdaddr);
    msg.set_data_m_param3(res_Data);
    msg.set_data_m_param4(0);
    
	#if DEBUG_ECHO
    	msg.print_hex();
	#endif
    
    res = msg.to_string();
    
  //  res.clear();
  //  res.assign(fram.begin(),fram.end());
    /*
     std::cout<< "HSDriver_GetCrurrentSpeed send:";
     for(std::size_t index=0;index<res.size();index++){
                      int x=(unsigned  char)res[index];
                       std::cout<<boost::format("%02X ")%x;
                  }
    std::cout<<"\n";
    */
    
    return res;
}

std::string synctronDriver::HSDriver_SetCmd32(char targID,UINT16 
cmdaddr,UINT16 res_Data1,UINT16 res_Data2)
{

    std::string res;
    message msg;
   // #define ID_SetCmd32  43
   // const char ID_SetCmd32= 43;
    
    msg.set_fram_info(0x08);
    msg.set_fram_ID(CHANGSTATUS+P2P+this->m_add);
    //msg.set_fram_data(data.c_array());
    msg.set_data_m_byte(targID, 0);
    
    msg.set_data_m_byte(ID_SetCmd32, 1);
    msg.set_data_m_param2(cmdaddr);
    msg.set_data_m_param3(res_Data1);
    msg.set_data_m_param4(res_Data2);
    
	#if DEBUG_ECHO
    	msg.print_hex();
	#endif
    
    res = msg.to_string();
    
  //  res.clear();
  //  res.assign(fram.begin(),fram.end());
    /*
     std::cout<< "HSDriver_GetCrurrentSpeed send:";
     for(std::size_t index=0;index<res.size();index++){
                      int x=(unsigned  char)res[index];
                       std::cout<<boost::format("%02X ")%x;
                  }
    std::cout<<"\n";
    */
    
    return res;
}

std::string synctronDriver::HSDriver_GetAllstatues(char targID){
      std::string res;
      res.clear();
      
    {
     //获取当前速度
      std::string cmd;
   
    cmd = HSDriver_GetStatus16(targID,DN_GetCrurrentSpeed);
    res+=cmd;
   // return res;    
    }
    
      
       {
        //'电机有效转矩率(绝对值): 电流法
         std::string cmd;
      
       cmd = HSDriver_GetStatus16(targID,DN_GetEffectiveTorque_I);
       res+=cmd;
      // return res;    
       }
/*
 {
  //电机速度命令给定值
   std::string cmd;

 cmd = HSDriver_GetStatus16(targID,DN_GetSpeedCmd);
 res+=cmd;
// return res;    
 }
*/
/*
 {
  // DN_GetCruAbsSpeed= 0x0009,  //'电机当前运行速度绝对值,
   std::string cmd;

 cmd = HSDriver_GetStatus16(targID,DN_GetCruAbsSpeed);
 res+=cmd;
// return res;    
 }
*/

/*
 {
    // DN_GetEffectiveTorque_T =0x000C, // '电机有效转矩率(绝对值）：转矩观测法
   std::string cmd;

 cmd = HSDriver_GetStatus16(targID,DN_GetEffectiveTorque_T);
 res+=cmd;
// return res;    
 }
 */
 
  {
      //DN_GetIpmTem =0x0024, // '功率器件温度（单位：度）
    std::string cmd;
 
  cmd = HSDriver_GetStatus16(targID,DN_GetIpmTem);
  res+=cmd;
 // return res;    
  }
 /*
 {
    // DN_GetDrivBoardTem =0x0025, // ''控制板温度（单位：度）
   std::string cmd;

 cmd = HSDriver_GetStatus16(targID,DN_GetDrivBoardTem);
 res+=cmd;
// return res;    
 }
 */

 {
     //DN_GetUdc =0x0080, //'直流母线电压值Udc（单位：0.1V）
   std::string cmd;

 cmd = HSDriver_GetStatus16(targID,DN_GetUdc);
 res+=cmd;
// return res;    
 }

    /*
 {
     //DN_GetAppStatus=0x002C, //'应用层 状态字
   std::string cmd;

 cmd = HSDriver_GetStatus16(targID,DN_GetAppStatus);
 res+=cmd;
// return res;    
 }
 
 {
    // DN_GetDrivStatus =0x005B, //'驱动控制应用状态字
   std::string cmd;

 cmd = HSDriver_GetStatus16(targID,DN_GetDrivStatus);
 res+=cmd;
// return res;    
 } 
 */

 {
     //DN_GetCruError =0x0036, //''当前扫描的系统故障代码
   std::string cmd;

 cmd = HSDriver_GetStatus16(targID,DN_GetCruError);
 res+=cmd;
// return res;    
 } 
/*
 {
     //DN_GetCumulativePos =0x0019,   //32w位
   std::string cmd;

 cmd = HSDriver_GetStatus32(targID,DN_GetCumulativePos);
 res+=cmd;
// return res;    
 } 

*/
/*
  {
      //DN_GetCruPos =0x001F, //32w位
   std::string cmd;

 cmd = HSDriver_GetStatus32(targID,DN_GetCruPos);
 res+=cmd;
// return res;    
 } 


*/

  std::cout<< res.size() << std::endl;
  
    return res;
}

INT16  synctronDriver::cru_speed(){
    return m_cru_speed;
    }

UINT16 synctronDriver::effectiveTorque_I(){return m_effectiveTorque_I;}
UINT16 synctronDriver::cru_speedcmd(){return m_cru_speedcmd;} 
UINT16 synctronDriver::cru_absspeed(){return m_cru_absspeed;}  
UINT16 synctronDriver::effectiveTorque_T(){return m_effectiveTorque_T;} 
UINT16 synctronDriver::IpmTem(){return m_IpmTem;}  
UINT16 synctronDriver::drivboardTem(){return m_drivboardTem;}  
UINT16 synctronDriver::Udc(){return m_Udc;}  
UINT16 synctronDriver::AppStatus(){return m_AppStatus;} 
UINT16 synctronDriver::DrivStatus(){return m_DrivStatus;}  
UINT16 synctronDriver::CruError(){return m_CruError;}  
UINT16 synctronDriver::PreError(){return m_PreError;}  
//UINT32 synctronDriver::CumulativePos(){return m_CumulativePos;}  
//UINT32 synctronDriver::CmdPos(){return m_CmdPos;} 
UINT32 synctronDriver::CruPos(){return m_CruPos;}  
UINT16 synctronDriver::Dins(){return m_Dins;}  

void synctronDriver::paramRecord(message &msg,CMD cmd){
        switch(msg.get_data_m_param2()){
            
                case DN_GetCrurrentSpeed:
                          m_cru_speed = (INT16)msg.get_data_m_param3();
			      //msg.print_hex();
				#if 0
				
				 std::cout<<"m_cru_speed=";
				std::cout<<m_cru_speed;
				std::cout<<std::endl;
				#endif
                        break;
                case DN_GetEffectiveTorque_I:
                     //   std::cout<<"DN_GetEffectiveTorque_I"<<std::endl;
                          m_effectiveTorque_I= msg.get_data_m_param3();
                           //framflushcounter[1]++;
                        break;
                case DN007_CMDVelocity:
                        if(cmd == ID_GetStatus32_ACK){
                          //   std::cout<<"DN32_GetSpeedCmd"<<std::endl;
                                 m_cru_speedcmd= msg.get_data_m_param3();
  //                                framflushcounter[2]++;
                                 m_cru_absspeed= msg.get_data_m_param4();
  //                               framflushcounter[3]++;
                            }
                        else{
                         //   std::cout<<"DN007_CMDVelocity"<<std::endl;
                        m_cru_speedcmd= msg.get_data_m_param3();
                      //    framflushcounter[2]++;
                            }
                         break;
                case DN_GetIpmTem:
                         if(cmd == ID_GetStatus32_ACK){
                        //    std::cout<<"DN32_GetIpmTem"<<std::endl;
                                 m_IpmTem= msg.get_data_m_param3();
  //                                framflushcounter[5]++;
                                 m_drivboardTem= msg.get_data_m_param4();
//                                  framflushcounter[6]++;
                            }
                         else{
                         //    std::cout<<"DN_GetIpmTem"<<std::endl;
                            m_IpmTem= msg.get_data_m_param3();
 //                            framflushcounter[5]++;
                            }
                            break;
                 case DN_GetDrivBoardTem:
                        //    std::cout<<"DN_GetDrivBoardTem"<<std::endl;
                            m_drivboardTem= msg.get_data_m_param3();
 //                            framflushcounter[6]++;
                             break;
                 case DN_GetUdc:
                          // std::cout<<"DN_GetUdc"<<std::endl;
                           //msg.print_hex();
                            m_Udc= msg.get_data_m_param3();
                           
                             break;
                  case DN_GetAppStatus:
                      //      std::cout<<"DN_GetAppStatus"<<std::endl;
                            m_AppStatus= msg.get_data_m_param3();
 //                            framflushcounter[8]++;
                           break;
                  case DN_GetDrivStatus:
                       //     std::cout<<"DN_GetDrivStatus"<<std::endl;
                            m_DrivStatus= msg.get_data_m_param3();
  //                           framflushcounter[9]++;
                            break;
                   case DN_GetCruError:
                     if(cmd == ID_GetStatus32_ACK){
                      //      std::cout<<"DN32_GetCruError"<<std::endl;
                            m_CruError= msg.get_data_m_param3();
                      
                            m_PreError= msg.get_data_m_param4();
                             
                        }
                     else{
                    //        std::cout<<"DN_GetCruError"<<std::endl;
                          m_CruError= msg.get_data_m_param3();
                           GetStrError();
                        }
                            break;
                   case DN_GetPreError:
                //    std::cout<<"DN_GetPreError"<<std::endl;
                            m_PreError= msg.get_data_m_param3();
                            
                            break;

			case DN032_DIO_IN:
				//unsigned short int data= 
				#if 0
				m_Dins = msg.get_data_m_param4();
				//m_BitStatus.bit5_EMGING
				if(m_Dins == 0x0017){
						m_BitStatus.bit5_EMGING = 0;   //
					}
				else{
						m_BitStatus.bit5_EMGING = 1;   //急停被处罚
					}
				
				std::cout<< "sytronDriver:recv:DN032_DIO_IN: ";
				std::cout<<boost::format("%02X ")%m_Dins<<std::endl;
				#endif
				 break;
                    default:
                        std::cout<<"paramRecord default=";
                         msg.print_hex();
                        break;

            }

}
void synctronDriver::autureturnRecord(message &msg){
 
	m_CruPos= msg.get_data_m_param23();
	m_DrivStatus= msg.get_data_m_param4();
	recordBitstauts(m_DrivStatus);
	
}
/*
void synctronDriver::StatusRecord(std::string &status){

   
    int size = (int)(status.size()/13);

    for(int i=0;i<size;i++){
             boost::array<char,13>fram;
            for(int index=0;index<13;index++){
                fram[index]=status[index+i*13];
                }
                message msg(fram.c_array(),13);
                char * pd = msg.get_fram_data();
                //校验地址
                if(pd[0] == m_add){
                        switch(pd[1]){
                                case ID_GetStatus16_ACK:
                                     //std::cout<<"ID_GetStatus16_ACK=";
                                    //msg.print_hex();
                                        paramRecord(msg,ID_GetStatus16_ACK);
                                        break;
                                 case ID_GetStatus32_ACK:
                                   //  std::cout<<"ID_GetStatus32_ACK=";
                                          //msg.print_hex();
                                          paramRecord(msg,ID_GetStatus32_ACK);
                                        break;
                                 case ID_GetParam16_ACK:
                                            //std::cout<<"ID_GetParam16_ACK=";
                                             //msg.print_hex();
                                        break;
                                 case ID_GetParam32_ACK:
                                    //std::cout<<"ID_GetParam32_ACK=";
                                              // msg.print_hex();
                                        break;
                                 case ID_SetParam16_ACK:
                                    //std::cout<<"ID_SetParam16_ACK=";
                                             // msg.print_hex();
                                       break;
                                  case ID_SetCmd16_ACK:
                                  //  std::cout<<"ID_SetCmd16_ACK=";
                                            //  msg.print_hex();  
                                       break;

                                    default:
                                      //  std::cout<<"default=";
                                         // msg.print_hex();
                                        break;

                            }
                    }
        }

}
*/
void synctronDriver::signleRecord(message &msg){

          char * pd = msg.get_fram_data();
		
	   //std::cout<<"["<<boost::format("%d ")%(unsigned int)pd[1]<<"]="<<"\n";
            switch((unsigned char)pd[1]){
                       case ID_GetStatus16_ACK:
                                   // std::cout<<"ID_GetStatus16_ACK=";
                                    //msg.print_hex();
                                     paramRecord(msg,ID_GetStatus16_ACK);
                                     break;
                        case ID_GetStatus32_ACK:
                                    //std::cout<<"ID_GetStatus32_ACK=";
                                   //  msg.print_hex();
                                    paramRecord(msg,ID_GetStatus32_ACK);
                                      break;
									
                         case ID_GetParam16_ACK:
                                    // std::cout<<"ID_GetParam16_ACK=";
                                    // msg.print_hex();
                                     paramRecord(msg,ID_GetParam16_ACK);
                                      break;
                         case ID_GetParam32_ACK:
                                    // std::cout<<"ID_GetParam32_ACK=";
                                    // msg.print_hex();
                                     paramRecord(msg,ID_GetParam32_ACK);
                                     break;
                          case ID_SetParam16_ACK:
                                    // std::cout<<"ID_SetParam16_ACK=";
                                    // msg.print_hex();
                                     break;
                           case ID_SetCmd16_ACK:
                                    // std::cout<<"ID_SetCmd16_ACK=";
                                     // msg.print_hex();  
                                      break;
                           case ID_AUTURETURN:
				    //  msg.print_hex();
                                    autureturnRecord(msg);
                                     // msg.print_hex();  
                                      break;

                             default:
                                     // std::cout<<"default=";
                                   //    msg.print_hex();
                                      break;
                            }          

}

void synctronDriver::Statusprint(){

    int count=0;
    std::cout<<"******************Statusprint**********************"<<"\n";
    std::cout<<"m_cru_speed="<<m_cru_speed<<" ["<< framflushcounter[count++]<<"]\n";
    std::cout<<"m_effectiveTorque_I="<<m_effectiveTorque_I<<" ["<< framflushcounter[count++]<<"]\n";
    std::cout<<"m_cru_speedcmd="<<m_cru_speedcmd<<" ["<< framflushcounter[count++]<<"]\n";
    std::cout<<"m_cru_absspeed="<<m_cru_absspeed<<" ["<< framflushcounter[count++]<<"]\n";
    std::cout<<"m_effectiveTorque_T="<<m_effectiveTorque_T<<" ["<< framflushcounter[count++]<<"]\n";
    std::cout<<"m_IpmTem="<<m_IpmTem<<" ["<< framflushcounter[count++]<<"]\n";
    std::cout<<"m_drivboardTem="<<m_drivboardTem<<" ["<< framflushcounter[count++]<<"]\n";
    std::cout<<"m_Udc="<<m_Udc<<" ["<< framflushcounter[count++]<<"]\n";
    std::cout<<"m_AppStatus="<<m_AppStatus<<" ["<< framflushcounter[count++]<<"]\n";
    std::cout<<"m_DrivStatus="<<m_DrivStatus<<" ["<< framflushcounter[count++]<<"]\n";
    std::cout<<"m_CruError="<<m_CruError<<" ["<< framflushcounter[count++]<<"]\n";
    std::cout<<"m_PreError="<<m_PreError<<" ["<< framflushcounter[count++]<<"]\n";
   // std::cout<<"m_CumulativePos="<<m_CumulativePos<<" ["<< framflushcounter[count++]<<"]\n";
    //std::cout<<"m_CmdPos="<<m_CmdPos<<" ["<< framflushcounter[count++]<<"]\n";
    std::cout<<"m_CruPos="<<m_CruPos<<" ["<< framflushcounter[count++]<<"]\n";
     //std::cout<<std::endl;
}


std::string synctronDriver::GetStrError(){

    std::string error;
    error = errormap[m_CruError];
    
    if(error== ""){
            error = "OK";
        }

    return error;

}

std::string synctronDriver::Cmd_SetEnable(){


	std::string cmd = HSDriver_SetCmd16(m_add,FN_SETHS_Endable,0x0001);
	return cmd;

}

std::string synctronDriver::Cmd_SetRealse(){


	std::string cmd = HSDriver_SetCmd16(m_add,FN_SETHS_Endable,0x0000);
	return cmd;

}

std::string synctronDriver::Cmd_GetCruPos(){


	std::string cmd = HSDriver_GetStatus32(m_add,DN_GetCruPos);
	return cmd;

}

std::string synctronDriver::Cmd_GetUdc(){
	
	std::string cmd = HSDriver_GetStatus16(m_add,DN_GetUdc);
	return cmd;
}

std::string synctronDriver::Cmd_GetVelocity(){
	
	std::string cmd = HSDriver_GetStatus16(m_add,DN_GetCrurrentSpeed);
	return cmd;
}

std::string synctronDriver::Cmd_GetError(){

	std::string cmd = HSDriver_GetStatus16(m_add,DN_GetCruError);
	return cmd;
}

//设置速度
std::string synctronDriver::Cmd_SetVelocity(INT16 Velocity)
{


	std::string cmd = HSDriver_SetCmd16(m_add,CN_Setspeed,(unsigned short int)Velocity*(dir()));
	return cmd;
	 
}

//停车
std::string synctronDriver::Cmd_SetStop()
{

	std::string cmd = HSDriver_SetCmd16(m_add,CN_Setspeed,(unsigned short int)0);
	return cmd;
	 
}

//输入开口状态
std::string synctronDriver::Cmd_GetDinStatues()
{
	std::string cmd = HSDriver_GetStatus16(m_add,DN032_DIO_IN);
	return cmd;
}

//查询实际电流
std::string synctronDriver::Cmd_GetCurrent()
{
	std::string cmd = HSDriver_GetStatus16(m_add,DN_GetEffectiveTorque_I);
	return cmd;
	 
}

//驱动器目标速度
std::string synctronDriver::Cmd_GetCmdVelocity()
{
	std::string cmd = HSDriver_GetStatus16(m_add,DN007_CMDVelocity);
	return cmd;
	 
	 
}

//清楚错误
std::string synctronDriver::Cmd_SetClearError()
{
	std::string cmd = HSDriver_SetParam16(m_add,FN_ClearErrors,1);
	return cmd;
	 
}

std::string synctronDriver::Cmd_SetLifeGuard(INT16 TIMEOUT)
{
	std::string cmd = HSDriver_SetParam16(m_add,FN0E3_LIFEGUARD,TIMEOUT);
	return cmd;
	 
}

//急停车
std::string synctronDriver::Cmd_QuickStop()
{
	std::string cmd = HSDriver_SetCmd16(m_add,CN_Setspeed,(unsigned short int)0);
	return cmd;
	 
}

void synctronDriver::recordBitstauts(UINT16 statues)
{
 	m_BitStatus.bit0_isSRDY  = statues&0x0001; 
	m_BitStatus.bit1_isENA_SRV     = (statues>>1)&0x0001; 
	m_BitStatus.bit2_isRes1= (statues>>2)&0x0001; 
	m_BitStatus.bit3_isFault= (statues>>3)&0x0001; 
	m_BitStatus.bit4_isRes2= (statues>>4)&0x0001; 
	//m_BitStatus.bit5_EMGING = (statues>>5)&0x0001; 
	m_BitStatus.bit6_isDIS_SRV = (statues>>6)&0x0001; 
	m_BitStatus.bit7_Warning = (statues>>7)&0x0001; 
	m_BitStatus.bit8_isRes3 = (statues>>8)&0x0001; 
	m_BitStatus.bit9_isRes4 = (statues>>9)&0x0001; 
	m_BitStatus.bit10_isTR = (statues>>10)&0x0001; 
	m_BitStatus.bit11_isINL= (statues>>11)&0x0001; 
	m_BitStatus.bit12_isRes5= (statues>>12)&0x0001; 
	m_BitStatus.bit13_isRes6= (statues>>13)&0x0001; 
	m_BitStatus.bit14_isRes7= (statues>>14)&0x0001; 
	m_BitStatus.bit15_isRes8 = (statues>>15)&0x0001; 
     
    //#if DEBUG_ECHO
    #if 0
    std::cout<<"bit0_isSRDY ="<<(UINT16)m_BitStatus.bit0_isSRDY<<std::endl;
    std::cout<<"bit1_isENA_SRV ="<<(UINT16)m_BitStatus.bit1_isENA_SRV<<std::endl;
    std::cout<<"bit2_isRes1 ="<<(UINT16)m_BitStatus.bit2_isRes1<<std::endl;
    std::cout<<"bit3_isFault ="<<(UINT16)m_BitStatus.bit3_isFault<<std::endl;
    std::cout<<"bit4_isRes2 ="<<(UINT16)m_BitStatus.bit4_isRes2<<std::endl;
    std::cout<<"bit5_EMGING ="<<(UINT16)m_BitStatus.bit5_EMGING<<std::endl;
    std::cout<<"bit6_isDIS_SRV ="<<(UINT16)m_BitStatus.bit6_isDIS_SRV<<std::endl;
    std::cout<<"bit7_Warning ="<<(UINT16)m_BitStatus.bit7_Warning<<std::endl;
    std::cout<<"bit8_isRes3 ="<<(UINT16)m_BitStatus.bit8_isRes3<<std::endl;
    std::cout<<"bit9_isRes4 ="<<(UINT16)m_BitStatus.bit9_isRes4<<std::endl;
    std::cout<<"bit10_isTR ="<<(UINT16)m_BitStatus.bit10_isTR<<std::endl;
    std::cout<<"bit11_isINL ="<<(UINT16)m_BitStatus.bit11_isINL<<std::endl;
    std::cout<<"bit12_isRes5 ="<<(UINT16)m_BitStatus.bit12_isRes5<<std::endl;
    std::cout<<"bit13_isRes6 ="<<(UINT16)m_BitStatus.bit13_isRes6<<std::endl;
    std::cout<<"bit14_isRes7 ="<<(UINT16)m_BitStatus.bit14_isRes7<<std::endl;
    std::cout<<"bit15_isRes8 ="<<(UINT16)m_BitStatus.bit15_isRes8<<std::endl;
  #endif   
}

