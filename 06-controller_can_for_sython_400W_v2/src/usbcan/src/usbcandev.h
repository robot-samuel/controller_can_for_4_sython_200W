#pragma once


#include "controlcan.h"
#include "message.hpp"
#include <numeric>
#include <string>
#include <iostream>
#include <boost/array.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>

#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"


class usbcandev
{
public:
	typedef struct {
	    unsigned int channel; // channel index, 0~3
	    unsigned int stop; // stop RX-thread
	    unsigned int total; // total received
	    unsigned int error; // error(s) detected
	} RX_CTX;

#define MAX_CHANNELS  2
#define CHECK_POINT  10
#define RX_WAIT_TIME  10
#define RX_BUFF_SIZE  600

#define CAN1   0
#define CAN2   1
private:
    usbcandev(const usbcandev& rhs);
    usbcandev& operator=(const usbcandev& rhs);

public:
    

    usbcandev();
    usbcandev(unsigned int DevType,unsigned int DevIdx);
    usbcandev(unsigned int DevType,unsigned int DevIdx,unsigned int Baud);
	
    ~usbcandev();

	unsigned int  s2n(const char *s);
	
	unsigned int  DevType();
	unsigned int  DevIdx();
	unsigned int  ChMask();
	unsigned int  Baud();
	unsigned int  TxType();
	unsigned int  TxSleep();
	unsigned int  TxFrames();
	unsigned int  TxCount();

	void set_DevType(unsigned int DevType );
	void set_DevIdx(unsigned int DevIdx );
	void set_ChMask(unsigned int ChMask );
	void set_Baud(unsigned int Baud );
	void set_TxType(unsigned int TxType );
	void set_TxSleep(unsigned int TxSleep );
	void set_TxFrames(unsigned int TxFrames );
	void set_TxCount(unsigned int TxCount );

	int usbcandevOpen(unsigned int DevType,unsigned int DevIdx);
	int usbcandevOpen();
	int usbcandevconfig();
	int usbcandev_ReadBoardInfo();
	int usbcandev_ReadErrInfo(RX_CTX ctx);
	int usbcandev_ReadCANStatus(RX_CTX ctx);
	int usbcandev_ClearBuffer(RX_CTX ctx);
	void printf_frame(VCI_CAN_OBJ *can);

	int verify_frame(VCI_CAN_OBJ *can);
	void generate_frame(VCI_CAN_OBJ *can);

	int usbcandevStartRx();
	void sendRequest(const std::string &cmd,RX_CTX ctx);

	
	int is_recvbuf_empty(unsigned int id);
	int is_recvbuf_full(unsigned int id);
	int recvbuf_size(unsigned int id);
	std::string pop_cur_toarray(unsigned int id);
	
	void  rx_thread();
	void  rx_thread_can2();
	void usbcan_rxthred_interupt();
	//void th_loop_test(std::vector < boost::shared_ptr<usbcandev> > &vecpa);
	
	std::string Cmd_test();
	void th_loop_test();
	
public:
	unsigned int gDevType;
	unsigned int gDevIdx;
	unsigned int gChMask;
	unsigned int gBaud ;
	unsigned int gTxType ;
	unsigned int gTxSleep ;
	unsigned int gTxFrames;
	unsigned int gTxCount;	

	RX_CTX ctx_can1;
	RX_CTX ctx_can2;

	boost::shared_ptr<boost::thread>canrecv_ptr;
	boost::shared_ptr<boost::thread>can2recv_ptr;
	boost::shared_ptr<boost::circular_buffer<VCI_CAN_OBJ > > can1buf_ptr;
	boost::shared_ptr<boost::circular_buffer<VCI_CAN_OBJ > > can2buf_ptr;
	
};