#pragma once

#include <boost/smart_ptr.hpp>
#include <boost/array.hpp>
#include <numeric>
#include <string>
#include <iostream>




class message
{

public:

    
   enum { fram_length = 13 };
   enum { data_length = 8 };
   
private:

    
    boost::array<char,fram_length> data;
    char m_cfram_info;
    unsigned int  m_Ifram_ID;
    boost::array<char,data_length> m_Afram_data;

    unsigned short int  m_param1;
    unsigned short int  m_param2;
    unsigned short int  m_param3;
    unsigned short int  m_param4;
    
public:
    

    
    message();
    
    message(char * buf,int len);
   message(std::string &str);
    ~message();

    void set_fram_info(char info);
    void set_fram_ID(unsigned int id);
    void set_fram_data(char * _char) ;
    
    char get_fram_info();
    unsigned int get_fram_ID();
    char * get_fram_data();

    void set_data_m_param1(unsigned short int para);
    void set_data_m_param2(unsigned short int para);
    void set_data_m_param3(unsigned short int para);
    void set_data_m_param4(unsigned short int para);
    
    void set_data_m_byte(char para,int pos);
	void set_data_m_param34(int data);
    
    unsigned short int get_data_m_param1();
    unsigned short int get_data_m_param2();
    unsigned short int get_data_m_param3();
    unsigned short int get_data_m_param4();
    unsigned int get_data_m_param34();
   std::string to_string();
   std::string data_to_string();
   unsigned char Get_sizetype();
     unsigned char get_data_m_byte(int pos);
   void print_dec();
    void print_hex();
   void getPRIMcheck();

    void Set_CMD(int cmd);
    unsigned int Get_CMD();

};

