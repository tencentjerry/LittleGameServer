#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>

#include "base.h"
namespace lib
{

using socket_t = int;

class CSocketHelper
{
public:
	CSocketHelper()
	{

	}

	~CSocketHelper()
	{

	}

	static socket_t CreateNonblockingSocket();

	static socket_t CreateUDPServer(int Port);

	static void SetKeepAlive(socket_t fd, bool On);

	static void SetRefuseAddr(socket_t fd);


	static void SetTcpNoDelay(socket_t fd, bool On);

	static bool SetTcpNonblocking(socket_t fd);


	static std::string ToIPPort(const struct sockaddr_in* ss);


};




}
