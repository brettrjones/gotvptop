//============================================================================
// this code came from http://www.codeproject.com/KB/IP/port-forwarding.aspx
// license: The Code Project Open License (CPOL)
//============================================================================

#ifdef WINDOWS_PLATFORM

#ifndef UPNPNAT_H
#define UPNPNAT_H

#include <string>
#include <vector>
#include <CoreLib/VxDefs.h>

#ifdef _MSC_VER
    #pragma   warning(disable:   4251)
#endif // _MSC_VER

#define DefaultTimeOut  10
#define DefaultInterval 200

class UPNPNAT
{
public:
 
	bool init(int time_out=DefaultTimeOut,int interval=DefaultInterval); //init
	bool discovery();//find router

	/****
	 **** _description: port mapping name
	 **** _destination_ip: internal ip address
	 **** _port_ex:external: external listen port
	 **** _destination_port: internal port
	 **** _protocal: TCP or UDP
	 ***/
	bool add_port_mapping(char * _description, char * _destination_ip, unsigned short int _port_ex, unsigned short int _destination_port, char * _protocal);//add port mapping

	const char * get_last_error(){ return last_error.c_str();}//get last error
private:
	bool get_description();			//
	bool parser_description();		//
	bool tcp_connect(const char * _addr,unsigned short int _port);
	bool parse_mapping_info();
	SOCKET udp_socket_fd;
	SOCKET tcp_socket_fd;
	typedef enum 
	{
		NAT_INIT=0,
		NAT_FOUND,
		NAT_TCP_CONNECTED,
		NAT_GETDESCRIPTION,
		NAT_GETCONTROL,
		NAT_ADD,
		NAT_DEL,
		NAT_GET,
		NAT_ERROR
	} NAT_STAT;
	NAT_STAT status;
    int time_out;
    int interval;
	std::string service_type;
	std::string describe_url;
	std::string control_url;
	std::string base_url;
	std::string service_describe_url;
	std::string description_info;
	std::string last_error;
	std::string mapping_info;
};

#endif

#endif // WINDOWS_PLATFORM