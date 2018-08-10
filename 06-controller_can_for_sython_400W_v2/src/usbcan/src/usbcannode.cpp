#include <string>
#include <algorithm>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/assign/list_of.hpp> //for ref_list_of  
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/progress.hpp>
#include <boost/program_options.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

//#include "usbcandev.h"

#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"


using namespace std;
using namespace boost;
#define NODENAME "usbcannode"

template <typename ElemT>
    struct HexTo {
        ElemT value;
        operator ElemT() const {return value;}
        friend std::istream& operator>>(std::istream& in, HexTo& out) {
            in >> std::hex >> out.value;
            return in;
        }
    };



	
int main(int argc, char* argv[])
{
	ros::init(argc, argv,NODENAME); 
	boost::shared_ptr< ros::NodeHandle> handel(new ros::NodeHandle);
    if (argc < 2) {
        printf("usbcannode [Baud]\n"
            "    example: usbcannode 0x1400 \n"
            "                  |  | | |0x1400-1M, 0x1c03-125K, ....\n"
            );
        return 0;
    }
	
	std::string SDevType;
	std::string SDevIdx;
	std::string SChMask;
	std::string SBaud;
	std::string STxType;
	std::string STxSleep;
	std::string STxFrames;
	std::string STxCount;


	SDevType = "4";   //�忨����
	SDevIdx= "0";	//�豸��������
	SChMask= "3"; 	//ͨ��ѡ��
	SBaud= argv[1];  //0x1400-1M, 0x1c03-125K,0x1600-800K ,0x1c00-500K....\n" 
	
	STxType= "0";
	STxSleep= "3";
	STxFrames= "1";
	STxCount= "1";

	std::cout<<"SDevType:" <<SDevType<<std::endl;
	std::cout<<"SDevIdx:" <<SDevIdx<<std::endl;
	std::cout<<"SChMask:" <<SChMask<<std::endl;
	std::cout<<"SBaud:" <<SBaud<<std::endl;
	std::cout<<"STxType:" <<STxType<<std::endl;
	std::cout<<"STxSleep:" <<STxSleep<<std::endl;
	std::cout<<"STxFrames:" <<STxFrames<<std::endl;
	std::cout<<"STxCount:" <<STxCount<<std::endl;

	
	//������ʼ��
	usbcandev candev;

//iband	
	//������
			unsigned int iband =candev.s2n(argv[4]);
			
			if((iband>=0x1400)&&(iband <= 0x1c03)){
				candev.set_Baud( iband);
				}
			else{
				std::cout<<"iband  wrong ! "<<std::endl;		
				return 0;	
				}

	candev.set_DevType( boost::lexical_cast<unsigned int>(SDevType));
	candev.set_DevIdx( boost::lexical_cast<unsigned int>(SDevIdx));
	candev.set_ChMask( boost::lexical_cast<unsigned int>(SChMask));
	candev.set_TxType( boost::lexical_cast<unsigned int>(STxType));
	candev.set_TxSleep(boost::lexical_cast<unsigned int>(STxSleep));
	candev.set_TxFrames(boost::lexical_cast<unsigned int>(STxFrames));
	candev.set_TxCount(boost::lexical_cast<unsigned int>(STxCount));


 	//�豸��ʼ��
 	candev.usbcandevOpen(candev.DevType(), candev.DevIdx());
	candev.usbcandevconfig();

	candev.usbcandevStartRx();

	
	//�忨�����߳�
	boost::thread t1(boost::bind(&usbcandev::rx_thread,&candev));  

	
	
	ros::spin();
	t1.join();	


}