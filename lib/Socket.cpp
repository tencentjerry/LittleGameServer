#include "Socket.h"

namespace lib
{


/*static*/ socket_t CSocketHelper::CreateNonblockingSocket()
{
	int errorcode = 0;

	socket_t fd = ::socket(AF_INET, SOCK_STREAM, 0);

	if (-1 == fd)
	{
		errorcode = errno;
		LOG_ERROR << "socket error" << strerror(errorcode);

		return ERR_INVALID_SOCKET;
	}


	if (false == SetTcpNonblocking(fd))
	{
		LOG_ERROR << "SetTcpNonblocking return faild\n";
		return ERR_INVALID_SOCKET;
	}

	SetKeepAlive(fd, true);
	SetRefuseAddr(fd);

	return fd;
}

/*static*/ socket_t CSocketHelper::CreateUDPServer(int Port)
{
	
}

/*static*/ void CSocketHelper::SetKeepAlive(socket_t fd, bool On)
{
	int optval = On ? 1 : 0;
	int rc = ::setsockopt(fd
						, SOL_SOCKET
						, SO_KEEPALIVE
						, reinterpret_cast<const char*>(&optval)
						, static_cast<socklen_t>(sizeof optval));
	if (rc != 0) 
	{
		int serrno = errno;
		LOG_ERROR << "setsockopt(SO_KEEPALIVE) failed, errno=" << serrno << " " << strerror(serrno);
	}

	return;
}


/*static*/ void CSocketHelper::SetRefuseAddr(socket_t fd)
{
	int optval = 1;
	int rc = ::setsockopt(fd
						  , SOL_SOCKET
						  , SO_REUSEADDR
						  , reinterpret_cast<const char*>(&optval)
						  , static_cast<socklen_t>(sizeof optval));
	if (rc != 0)
	{
		int serrno = errno;
		LOG_ERROR << "setsockopt(SO_KEEPALIVE) failed, errno=" << serrno << " " << strerror(serrno);
	}
	return;
}


/*static*/ void CSocketHelper::SetTcpNoDelay(socket_t fd, bool On)
{
	int optval = On ? 1 : 0;
	int rc = ::setsockopt(fd
						 , IPPROTO_TCP
						 , TCP_NODELAY
						 , reinterpret_cast<const char*>(&optval)
						 , static_cast<socklen_t>(sizeof optval)
						);
	if (rc != 0) 
	{
		int serrno = errno;
		LOG_ERROR << "setsockopt(TCP_NODELAY) failed, errno=" << serrno << " " << strerror(serrno);
	}

	return;
}

/*static*/ int CSocketHelper::SetTcpNonblocking(socket_t fd)
{
	int iFlags;
	iFlags = fcntl(fd, F_GETFL, 0);
	iFlags |= O_NONBLOCK;
	iFlags |= O_NDELAY;

	if (0 != fcntl(fd, F_SETFL, iFlags))
	{
		return false;
	}

	return true;
}

/*static*/ std::string CSocketHelper::ToIPPort(const struct sockaddr_in* ss)
{

	std::string stTmp("0.0.0.0:123");

	return stTmp;
}
}