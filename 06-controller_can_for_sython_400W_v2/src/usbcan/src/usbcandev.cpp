#include "usbcandev.h"



#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include<stdlib.h>



#define DEBUG_ECHO 0


/*
        printf("test [DevType] [DevIdx] [ChMask] [Baud] [TxType] [TxSleep] [TxFrames] [TxCount]\n"
            "    example: test 16 0 3 0x1400 2 3 10 1000\n"
            "                  |  | | |      | | |  | 1000 times\n"
            "                  |  | | |      | | |\n"
            "                  |  | | |      | | |10 frames once\n"
            "                  |  | | |      | |\n"
            "                  |  | | |      | |tx > sleep(3ms) > tx > sleep(3ms) ....\n"
            "                  |  | | |      |\n"
            "                  |  | | |      |0-normal, 1-single, 2-self_test, 3-single_self_test, 4-single_no_wait....\n"
            "                  |  | | |\n"
            "                  |  | | |//0x1400-1M, 0x1c03-125K,0x1600-800K ,0x1c00-500K....\n" 
            "                  |  | |\n"
            "                  |  | |bit0-CAN1, bit1-CAN2, bit2-CAN3, bit3-CAN4, 3=CAN1+CAN2, 7=CAN1+CAN2+CAN3\n"
            "                  |  |\n"
            "                  |  |Card0\n"
            "                  |\n"
            "                  |4-usbcan-ii, 5-pci9820, 14-pci9840, 16-pci9820i, ....\n"
            );
*/
            
usbcandev::usbcandev()
{ 
	
	gDevType = 4;   // 4-usbcan-ii, 5-pci9820, 14-pci9840, 16-pci9820i, ....\n"
	gDevIdx = 0;    //Card0\n"
	gChMask = 3 ;    //bit0-CAN1, bit1-CAN2, bit2-CAN3, bit3-CAN4, 3=CAN1+CAN2, 7=CAN1+CAN2+CAN3\n"
	gBaud = 0x1600;      ////0x1400-1M, 0x1c03-125K,0x1600-800K ,0x1c00-500K....\n" 
	gTxType = 0;    // 0-normal, 1-single, 2-self_test, 3-single_self_test, 4-single_no_wait....\n"
	gTxSleep = 3;   //  tx > sleep(3ms) > tx > sleep(3ms) ....\n"
	gTxFrames = 1;  //10 frames once\n"
	gTxCount = 1;	   //| 1000 times\n"


	ctx_can1.channel=CAN1; // channel index, 0~3
	ctx_can1.stop = 0; // stop RX-thread
	ctx_can1.total = 0; // total received
	ctx_can1.error = 0 ; // error(s) detected

	ctx_can2.channel=CAN2; // channel index, 0~3
	ctx_can2.stop = 0; // stop RX-thread
	ctx_can2.total = 0; // total received
	ctx_can2.error = 0 ; // error(s) detected
	
   can1buf_ptr = boost::shared_ptr<boost::circular_buffer<  VCI_CAN_OBJ> > (
    new boost::circular_buffer<VCI_CAN_OBJ> (RX_BUFF_SIZE)	);

   can2buf_ptr = boost::shared_ptr<boost::circular_buffer<  VCI_CAN_OBJ> > (
   new boost::circular_buffer<VCI_CAN_OBJ> (RX_BUFF_SIZE)	);


	/*
      //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ß³ï¿½
     
   boost::function0<void> f = boost::bind(&usbcandev::rx_thread, this);  
   canrecv_ptr = boost::shared_ptr<boost::thread>(new boost::thread (f));
   */
   
    
}

usbcandev::usbcandev(unsigned int DevType,unsigned int DevIdx)
:gDevType(DevType),gDevIdx(DevIdx)
{

	gChMask = 3 ;    //bit0-CAN1, bit1-CAN2, bit2-CAN3, bit3-CAN4, 3=CAN1+CAN2, 7=CAN1+CAN2+CAN3\n"
	gBaud = 0x1600;      //0x1400-1M, 0x1c03-125K,0x1600-800K ,0x1c00-500K....\n" 
	gTxType = 0;    // 0-normal, 1-single, 2-self_test, 3-single_self_test, 4-single_no_wait....\n"
	gTxSleep = 0;   //  tx > sleep(3ms) > tx > sleep(3ms) ....\n"
	gTxFrames = 0;  //10 frames once\n"
	gTxCount = 0;	   //| 1000 times\n"

	ctx_can1.channel=CAN1; // channel index, 0~3
	ctx_can1.stop = 0; // stop RX-thread
	ctx_can1.total = 0; // total received
	ctx_can1.error = 0 ; // error(s) detected

	ctx_can2.channel=CAN2; // channel index, 0~3
	ctx_can2.stop = 0; // stop RX-thread
	ctx_can2.total = 0; // total received
	ctx_can2.error = 0 ; // error(s) detected

   can1buf_ptr = boost::shared_ptr<boost::circular_buffer<  VCI_CAN_OBJ> > (
    new boost::circular_buffer<VCI_CAN_OBJ> (RX_BUFF_SIZE)	);

   can2buf_ptr = boost::shared_ptr<boost::circular_buffer<  VCI_CAN_OBJ> > (
   new boost::circular_buffer<VCI_CAN_OBJ> (RX_BUFF_SIZE)	);
    

    if (!VCI_OpenDevice(gDevType, gDevIdx, 0)) {
		
	std::cout<<"VCI_OpenDevice failed"<<std::endl;
        throw "VCI_OpenDevice failed";
    }
	std::cout<<"VCI_OpenDevice succeeded"<<std::endl;

	usbcandev_ClearBuffer(ctx_can1);
	 usbcandev_ClearBuffer(ctx_can2);
     //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ß³ï¿½
     
  // boost::function0<void> f = boost::bind(&usbcandev::rx_thread, this);  
  // canrecv_ptr = boost::shared_ptr<boost::thread>(new boost::thread (f));

  // boost::function0<void> f2 = boost::bind(&usbcandev::rx_thread_can2, this);  
 //  can2recv_ptr = boost::shared_ptr<boost::thread>(new boost::thread (f2));
   
}


usbcandev::usbcandev(unsigned int DevType,unsigned int DevIdx,unsigned int Baud)
:gDevType(DevType),gDevIdx(DevIdx),gBaud(Baud)
{

	gChMask = 3 ;    //bit0-CAN1, bit1-CAN2, bit2-CAN3, bit3-CAN4, 3=CAN1+CAN2, 7=CAN1+CAN2+CAN3\n"
	
	gTxType = 0;    // 0-normal, 1-single, 2-self_test, 3-single_self_test, 4-single_no_wait....\n"
	gTxSleep = 0;   //  tx > sleep(3ms) > tx > sleep(3ms) ....\n"
	gTxFrames = 0;  //10 frames once\n"
	gTxCount = 0;	   //| 1000 times\n"

	ctx_can1.channel=CAN1; // channel index, 0~3
	ctx_can1.stop = 0; // stop RX-thread
	ctx_can1.total = 0; // total received
	ctx_can1.error = 0 ; // error(s) detected

	ctx_can2.channel=CAN2; // channel index, 0~3
	ctx_can2.stop = 0; // stop RX-thread
	ctx_can2.total = 0; // total received
	ctx_can2.error = 0 ; // error(s) detected

    if (!VCI_OpenDevice(gDevType, gDevIdx, 0)) {
        std::cout<<"VCI_OpenDevice failed"<<std::endl;
         throw "VCI_OpenDevice failed";
    }
  std::cout<<"VCI_OpenDevice succeeded"<<std::endl;

	usbcandev_ClearBuffer(ctx_can1);
	 usbcandev_ClearBuffer(ctx_can2);
	 
     //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ß³ï¿½
     
  // boost::function0<void> f = boost::bind(&usbcandev::rx_thread, this);  
//   canrecv_ptr = boost::shared_ptr<boost::thread>(new boost::thread (f));

 //  boost::function0<void> f2 = boost::bind(&usbcandev::rx_thread_can2, this);  
 //  can2recv_ptr = boost::shared_ptr<boost::thread>(new boost::thread (f2));
}


usbcandev::~usbcandev()
{
    canrecv_ptr->interrupt();
     canrecv_ptr->join();

   can2recv_ptr->interrupt();
    can2recv_ptr->join();
	 
	usbcandev_ClearBuffer(ctx_can1);
	 usbcandev_ClearBuffer(ctx_can2);
	 
    VCI_CloseDevice(gDevType, gDevIdx);
     std::cout<<"VCI_CloseDevice succeeded"<<std::endl;
}


void usbcandev::usbcan_rxthred_interupt()
{
    canrecv_ptr->interrupt();
     canrecv_ptr->join();

     can2recv_ptr->interrupt();
     can2recv_ptr->join();
	 
	usbcandev_ClearBuffer(ctx_can1);
	 usbcandev_ClearBuffer(ctx_can2);
	 
    VCI_CloseDevice(gDevType, gDevIdx);
     std::cout<<"VCI_CloseDevice succeeded"<<std::endl;
}

unsigned int  usbcandev::s2n(const char *s)
{
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


unsigned int  usbcandev::DevType(){return gDevType;}
unsigned int  usbcandev::DevIdx(){return gDevIdx;} 
unsigned int  usbcandev::ChMask(){return gChMask;}
unsigned int  usbcandev::Baud(){return gBaud;}
unsigned int  usbcandev::TxType(){return gTxType;}
unsigned int  usbcandev::TxSleep(){return gTxSleep;}
unsigned int  usbcandev::TxFrames(){return gTxFrames;}
unsigned int  usbcandev::TxCount(){return gTxCount;}


void usbcandev::set_DevType(unsigned int DevType ){ gDevType = DevType;}
void usbcandev::set_DevIdx(unsigned int DevIdx ){ gDevIdx = DevIdx;}
void usbcandev::set_ChMask(unsigned int ChMask ){ gChMask = ChMask;}
void usbcandev::set_Baud(unsigned int Baud ){ gBaud = Baud;}
void usbcandev::set_TxType(unsigned int TxType ){ gTxType = TxType;}
void usbcandev::set_TxSleep(unsigned int TxSleep ){ gTxSleep = TxSleep;}
void usbcandev::set_TxFrames(unsigned int TxFrames ){ gTxFrames = TxFrames;}
void usbcandev::set_TxCount(unsigned int TxCount ){ gTxCount = TxCount;}



int usbcandev::usbcandevOpen(unsigned int DevType,unsigned int DevIdx)
{

	gDevType = DevType;
	gDevIdx = DevIdx;

    if (!VCI_OpenDevice(gDevType, gDevIdx, 0)) {
		
	std::cout<<"VCI_OpenDevice failed"<<std::endl;
        return -1;
    }
	std::cout<<"VCI_OpenDevice succeeded"<<std::endl;
	
	std::cout<<"usbcandevOpen: " ;
	std::cout<<" gDevType:" <<gDevType;
	std::cout<<" gDevIdx:" <<gDevIdx<<std::endl;

     //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ß³ï¿½
	usbcandev_ClearBuffer(ctx_can1);
	 usbcandev_ClearBuffer(ctx_can2);
	 
   // boost::function0<void> f = boost::bind(&usbcandev::rx_thread, this);  
   // canrecv_ptr = boost::shared_ptr<boost::thread>(new boost::thread (f));

   //boost::function0<void> f2 = boost::bind(&usbcandev::rx_thread_can2, this);  
  // can2recv_ptr = boost::shared_ptr<boost::thread>(new boost::thread (f2));

    return 1;
}

int usbcandev::usbcandevOpen()
{


    if (!VCI_OpenDevice(gDevType, gDevIdx, 0)) {
		
	std::cout<<"VCI_OpenDevice failed"<<std::endl;
        return -1;
    }
	std::cout<<"VCI_OpenDevice succeeded"<<std::endl;


     //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ß³ï¿½
     
 //  boost::function0<void> f = boost::bind(&usbcandev::rx_thread, this);  
 //  canrecv_ptr = boost::shared_ptr<boost::thread>(new boost::thread (f));

    return 1;
}

int usbcandev::usbcandevconfig()
{
    // ----- init & start -------------------------------------------------

    VCI_INIT_CONFIG config;
    config.AccCode = 0;
    config.AccMask = 0xffffffff;
    config.Filter = 0;
    config.Mode = 0;
    config.Timing0 = gBaud & 0xff;
    config.Timing1 = gBaud >> 8;
	
	std::cout<<" config.AccCode= " <<config.AccCode;
	std::cout<<"  config.AccMask: " <<config.AccMask;
	std::cout<<"  config.Filter: " <<(unsigned int )config.Filter;
	std::cout<<"  config.Mode: " <<(unsigned int )config.Mode;
	std::cout<<"  config.Timing0: " <<(unsigned int )config.Timing0;
	std::cout<<"  config.Timing1: " <<(unsigned int )config.Timing1<<std::endl;
	
    int i;
    for (i = 0; i < MAX_CHANNELS; i++)
    {
        if ((gChMask & (1 << i)) == 0) continue;

        if (!VCI_InitCAN(gDevType, gDevIdx, i, &config))
        {
		std::cout<<"VCI_InitCAN("<<i<<") failed"<<std::endl;
		return -1;
        }
	std::cout<<"VCI_InitCAN("<<i<<") succeeded"<<std::endl;


        if (!VCI_StartCAN(gDevType, gDevIdx, i))
        {
            std::cout<<"VCI_StartCAN("<<i<<") failed"<<std::endl;
            return -1;
        }
	std::cout<<"VCI_StartCAN("<<i<<") succeeded"<<std::endl;
	std::cout<<"i:" <<i;
	std::cout<<" gDevType:" <<gDevType;
	std::cout<<" gDevIdx:" <<gDevIdx;
	std::cout<<" CHANNELS:" <<gChMask<<std::endl;
    }

	usbcandev_ReadBoardInfo();
	return 1;
}


int usbcandev::usbcandev_ReadBoardInfo(){

	VCI_BOARD_INFO pInfo;
	

	if(!VCI_ReadBoardInfo(gDevType,gDevIdx,&pInfo)){
			std::cout<<"VCI_ReadBoardInfo failed"<<std::endl;
			return -1;
		}

	std::cout<<"hw_Version: " <<pInfo.hw_Version;
	std::cout<<" fw_Version: " <<pInfo.fw_Version;
	std::cout<<" dr_Version: " <<pInfo.dr_Version;
	std::cout<<" in_Version: " <<pInfo.in_Version;
	std::cout<<" irq_Num: " <<pInfo.irq_Num;
	std::cout<<" can_Num: " <<(unsigned int )pInfo.can_Num;
	
	std::string Serial_Num = pInfo.str_Serial_Num;
	std::string hw_Type = pInfo.str_hw_Type;
	std::cout<<" str_Serial_Num: " <<Serial_Num;
	std::cout<<" str_hw_Type: " <<hw_Type<<std::endl;

	return 1;

}


int usbcandev::usbcandev_ReadErrInfo(RX_CTX ctx){

	VCI_ERR_INFO ErrInfo;
	
	if(!VCI_ReadErrInfo(gDevType,gDevIdx,ctx.channel, &ErrInfo)){
			std::cout<<"VCI_ReadErrInfo failed"<<std::endl;
			return -1;
		}
		
	std::cout<<"ErrCode: " <<ErrInfo.ErrCode;

	return 1;

}

int usbcandev::usbcandev_ReadCANStatus(RX_CTX ctx){

	VCI_CAN_STATUS CANStatus;
	if(!VCI_ReadCANStatus(gDevType,gDevIdx,ctx.channel, &CANStatus)){
			std::cout<<"VCI_ReadCANStatus failed"<<std::endl;
			return -1;
		}
		
	std::cout<<"ErrInterrupt: " <<(unsigned int )CANStatus.ErrInterrupt;
	std::cout<<" regMode: " <<(unsigned int )CANStatus.regMode;
	std::cout<<" regStatus: " <<(unsigned int )CANStatus.regStatus;
	std::cout<<" regALCapture: " <<(unsigned int )CANStatus.regALCapture;
	std::cout<<" regECCapture: " <<(unsigned int )CANStatus.regECCapture;
	std::cout<<" regEWLimit: " <<(unsigned int )CANStatus.regEWLimit;
	std::cout<<" regRECounter: " <<(unsigned int )CANStatus.regRECounter;
	std::cout<<" regTECounter: " <<(unsigned int )CANStatus.regTECounter<<std::endl;

	

	return 1;

}

int usbcandev::usbcandev_ClearBuffer(RX_CTX ctx){

	if(!VCI_ClearBuffer(gDevType,gDevIdx,ctx.channel)){
			std::cout<<"VCI_ClearBuffer failed"<<std::endl;
			return -1;
		}

	return 1;

}


int usbcandev::verify_frame(VCI_CAN_OBJ *can)
{
    if (can->DataLen > 8) return 0; // error: data length
    unsigned bcc = 0;
    unsigned i;
    for (i = 0; i < can->DataLen; i++)
        bcc ^= can->Data[i];
    if ((can->ID & 0xff) != bcc) return 0; // error: data checksum
    if (((can->ID >> 8) & 7) != (can->DataLen - 1)) return 0; // error: data length
    if (!can->ExternFlag) return 1; // std-frame ok
    if (((can->ID >> 11) & 0x7ff) != (can->ID & 0x7ff)) return 0; // error: frame id
    if (((can->ID >> 22) & 0x7f) != (can->ID & 0x7f)) return 0; // error: frame id
    return 1; // ext-frame ok
}

void usbcandev::generate_frame(VCI_CAN_OBJ *can)
{
    memset(can, 0, sizeof(VCI_CAN_OBJ));
    can->SendType = gTxType;
    //can->DataLen = 1 + (rand() % 8); // random data length: 1~8
    can->DataLen = 8; // random data length: 1~8
    unsigned i;
    for (i = 0; i < can->DataLen; i++)
    {
        can->Data[i] = rand() & 0xff; // random data
        can->ID ^= can->Data[i]; // id: bit0~7, checksum of data0~N
    }
    can->ID |= ((unsigned)can->DataLen - 1) << 8; // id: bit8~bit10 = data_length-1
    can->ExternFlag = rand() % 2; // random frame format
    if (!can->ExternFlag)
        return;
    can->ID |= can->ID << 11; // id: bit11~bit21 == bit0~bit10
    can->ID |= can->ID << 11; // id: bit22~bit28 == bit0~bit7
    
}

void usbcandev::printf_frame(VCI_CAN_OBJ *can){


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

void usbcandev::sendRequest(const std::string &cmd,RX_CTX ctx){
    int id=0;
    VCI_CAN_OBJ sendfram;
    
    id += cmd[1];
    id<<=8;
    id += cmd[2];
    id<<=8;
    id += cmd[3];
    id<<=8;
    id += cmd[4];

    sendfram.DataLen = 8;
    sendfram.ID =  id; 

	sendfram.SendType = gTxType;
	sendfram.ExternFlag = 0;
	sendfram.RemoteFlag = 0;
    
    for(int index =0 ;index<sendfram.DataLen;index++){
            sendfram.Data[index] = (unsigned char)cmd[5+index];
        }
    
    /* send frame */
	if (1 != VCI_Transmit(gDevType, gDevIdx,ctx.channel, &sendfram, 1))
            {
                usbcandev_ReadErrInfo(ctx);
		std::cout<<"CAN "<< ctx.channel <<" TX failed: ID="<<sendfram.ID<<std::endl;
                
            }

}

void  usbcandev::rx_thread()
{
	VCI_CAN_OBJ can[RX_BUFF_SIZE]; // buffer
	
	int cnt; // current received
	int i;

	unsigned check_point = 0;
	
  try{       
           while(!ctx_can1.stop && !ctx_can1.error){
		   	//boost::this_thread::sleep(boost::posix_time::milliseconds(100));
			cnt = VCI_Receive(gDevType, gDevIdx, ctx_can1.channel, can, RX_BUFF_SIZE, RX_WAIT_TIME);
			if (!cnt){
					
					continue;
				}
			 /** ÊÖ¶¯ÔÚÏß³ÌÖÐ¼ÓÈëÖÐ¶Ïµã£¬ÖÐ¶Ïµã²»Ó°ÏìÆäËûÓï¾äÖ´ÐÐ */  
            		boost::this_thread::interruption_point();  
			//std::cout << "cnt=" << cnt<<std::endl;  
			//std::cout << "ctx_can1.channel=" << ctx_can1.channel<<std::endl;  
			
			for (i = 0; i < cnt; i++) {
						can1buf_ptr->push_back(can[i]);
						#if DEBUG_ECHO
						printf_frame(&can[i]);
						#endif

				}
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
			/*
        		ctx.total += cnt;
        		if (ctx.total / CHECK_POINT >= check_point) {
					std::cout<<"CAN"<<ctx.channel<<": "<<ctx.total<<" frames received & verified"<<std::endl;
            				check_point++;
        			}
        			*/
		   }

  	}
 catch(boost::thread_interrupted&){
                  std::cout << "rx_thread Interrupt exception was thrown." << std::endl;  
       }
 /*
    printf("CAN%d RX thread terminated, %d frames received & verified: %s\n",
        ctx->channel, ctx->total, ctx->error ? "error(s) detected" : "no error");
        */

	std::cout << "CAN "<< ctx_can1.channel<<" RX thread terminated, "<<ctx_can1.total <<" frames received & verified:" << std::endl;  
	
}

void  usbcandev::rx_thread_can2()
{
	VCI_CAN_OBJ can[RX_BUFF_SIZE]; // buffer
	
	int cnt; // current received
	int i;

	unsigned check_point = 0;
	
  try{       
           while(!ctx_can2.stop && !ctx_can2.error){
		   	//boost::this_thread::sleep(boost::posix_time::milliseconds(100));
			cnt = VCI_Receive(gDevType, gDevIdx, ctx_can2.channel, can, RX_BUFF_SIZE, RX_WAIT_TIME);
			if (!cnt){
					//boost::this_thread::sleep(boost::posix_time::milliseconds(1));
					continue;
				}
			 /** ÊÖ¶¯ÔÚÏß³ÌÖÐ¼ÓÈëÖÐ¶Ïµã£¬ÖÐ¶Ïµã²»Ó°ÏìÆäËûÓï¾äÖ´ÐÐ */  
            		boost::this_thread::interruption_point();  
			//std::cout << "cnt=" << cnt<<std::endl;  
			//std::cout << "ctx_can2.channel=" << ctx_can2.channel<<std::endl;  
			
			for (i = 0; i < cnt; i++) {

						can2buf_ptr->push_back(can[i]);
						#if DEBUG_ECHO
						printf_frame(&can[i]);
						#endif

				}
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
			/*
        		ctx.total += cnt;
        		if (ctx.total / CHECK_POINT >= check_point) {
					std::cout<<"CAN"<<ctx.channel<<": "<<ctx.total<<" frames received & verified"<<std::endl;
            				check_point++;
        			}
        			*/
		   }

  	}
 catch(boost::thread_interrupted&){
                  std::cout << "rx_thread Interrupt exception was thrown." << std::endl;  
       }
 /*
    printf("CAN%d RX thread terminated, %d frames received & verified: %s\n",
        ctx->channel, ctx->total, ctx->error ? "error(s) detected" : "no error");
        */

	std::cout << "CAN "<< ctx_can2.channel<<" RX thread terminated, "<<ctx_can2.total <<" frames received & verified:" << std::endl;  
	
}

int usbcandev::usbcandevStartRx(){
	
     //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ß³ï¿½

    // ----- RX-timeout test ----------------------------------------------

    //VCI_CAN_OBJ can;
    //time_t tm1, tm2;
    //for (int i = 0; i < 3; i++)
    //{
      //  time(&tm1);
       // VCI_Receive(gDevType, gDevIdx, 0, &can, 1, (i + 1) * 1000/*ms*/);
       // time(&tm2);
       // printf("VCI_Receive returned: time ~= %ld seconds\n", tm2 - tm1);
    //}
	
   boost::function0<void> f = boost::bind(&usbcandev::rx_thread, this);  
   canrecv_ptr = boost::shared_ptr<boost::thread>(new boost::thread (f));

   boost::function0<void> f2 = boost::bind(&usbcandev::rx_thread_can2, this);  
   can2recv_ptr = boost::shared_ptr<boost::thread>(new boost::thread (f2));

    return 1;
	


}
int usbcandev::is_recvbuf_empty(unsigned int id){

	if(id == CAN1){
    			if(can1buf_ptr->size()){
    					return 0;
        			}
   			 return 1;
		}
	if(id == CAN2){
    			if(can2buf_ptr->size()){
    					return 0;
        			}
   			 return 1;
		}
}
int usbcandev::is_recvbuf_full(unsigned int id){

	if(id == CAN1){
    			if(can1buf_ptr->size()>=RX_BUFF_SIZE){
    					return 1;
        			}
   			 return 0;
		}
	if(id == CAN2){
    			if(can2buf_ptr->size()>=RX_BUFF_SIZE){
    					return 1;
        			}
   			 return 0;
		}
}
int usbcandev::recvbuf_size(unsigned int id){

	if(id == CAN1){
    		 return can1buf_ptr->size();

		}
	if(id == CAN2){
		return can2buf_ptr->size();
		}

}

std::string usbcandev::pop_cur_toarray(unsigned int id){
        VCI_CAN_OBJ frame;
        boost::array<char,13>cur_data={0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::string res;
	res.clear();
	
	if(id == CAN1){	
	        if(can1buf_ptr->size()>0){
	                    frame = *(can1buf_ptr->begin());
	                    //print_fram(frame);
	                   
	                    
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
		  	     std::string res1(cur_data.begin(),cur_data.end());
			     can1buf_ptr->pop_front();	
	                    //print_hex();
	                    return res1;
	            }
			 return res;
		}
	if(id == CAN2){	
	        if(can2buf_ptr->size()>0){
	                    frame = *(can2buf_ptr->begin());
	                    //print_fram(frame);
	                    
	                    
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
				 can2buf_ptr->pop_front();
	                    //print_hex();
	                    return res2;
	            }
			return res;
		}

	
}


void usbcandev::th_loop_test()
{
	
       std::cout<< "hello can_master "<<std::endl;
       
             
        ros::Rate loop_rate(10);
		 
         try{
                    while(ros::ok()){
             		//while(1){
             			usbcandev_ClearBuffer(ctx_can1);
    				std::string cmd = Cmd_test();
				sendRequest(cmd,ctx_can1);
				usbcandev_ReadCANStatus(ctx_can1);
				loop_rate.sleep();
                     }
             }
        catch(boost::thread_interrupted&){
                 std::cout << "thread interrupt" << std:: endl;
             }
    
	
}



std::string usbcandev::Cmd_test()
{
	#if DEBUG_ECHO
	std::cout<< "hello Cmd_test "<<std::endl;
	#endif
	//40 FD 60 00 00 00 00 00   //ï¿½ï¿½ï¿½ë¿ªï¿½ï¿½×´Ì¬
	message msg;

	//msg.Set_add(m_add);
	//msg.Set_sizetype(WBYTE4);

	//msg.Set_CMD(SetEnable);
	//msg.Set_BYTE(0x06);
	//msg.Set_check();
	msg.set_fram_info(0x08);
	msg.set_fram_ID(0x0600+1);

	msg.set_data_m_byte(3,0);
	//msg.Set_CMD(SetEnable);
	unsigned int data = 0x1234;
	unsigned char *p = (unsigned char *)&data;
	msg.set_data_m_byte(*(p+1),1);
	msg.set_data_m_byte(*(p+2),2);
	msg.set_data_m_byte(*(p+0),3);	

	
      msg.set_data_m_param3(0x0006);
      msg.set_data_m_param4(0);
	 std::string res = msg.to_string();
	 return res;
	 
}


