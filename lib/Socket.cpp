#include "Socket.h"
#include "InetAddr.h"
namespace lib
{
//------------------------Begin of Socket --------------------------    

Socket::Socket(socket_t fd) : m_tFd(fd)
{

}


Socket::~Socket()
{
	CSocketHelper::CloseSocket(m_tFd);
}


int Socket::listen()
{
	return CSocketHelper::Listen(m_tFd);
}


int Socket::bindaddress(const STAddrInfo &stAddrinfo)
{
	struct sockaddr addr;
	stAddrinfo.CopyTo(addr);
	return CSocketHelper::Bind(m_tFd, &addr);
}

int Socket::accept(STAddrInfo *stPeerAddrInfo)
{
	return;
}





//----------------------End of Socket ---------------------------------

/*static*/ int CSocketHelper::SetNonblocking(socket_t fd)
{
  int flags = ::fcntl(sockfd, F_GETFL, 0);
  flags |= O_NONBLOCK;
  int ret = ::fcntl(sockfd, F_SETFL, flags);

  return ret;
}


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


	if (0 != SetNonblocking(fd))
	{
		LOG_ERROR << "SetTcpNonblocking return faild\n";
		return ERR_INVALID_SOCKET;
	}

	return fd;
}

/*static*/ socket_t CSocketHelper::CreateUDPServer(int Port)
{
	int errorcode = 0;
	socket_t fd = ::socket(AF_INET, SOCK_DGRAM, 0);

	if(-1 == fd)
	{
		errorcode = errno;
		LOG_ERROR << "socket error" << strerror(errorcode);
		return ERR_INVALID_SOCKET;	
	}	
	
	/*
	if(false == SetTcpNonblocking(fd))
	{
		LOG_ERROR << "SetTcpNonblocking return faild\n";
		return ERR_INVALID_SOCKET;		
	}*/

	return fd;
}

/*static*/ std::string CSocketHelper::ToIPPort(const struct sockaddr_in* ss)
{

	std::string stTmp("0.0.0.0:123");

	return stTmp;
}


/*static*/ int CSocketHelper::Connect(socket_t socketfd, const struct sockaddr* addr)
{
	return ::connect(socketfd, addr, sizeof(struct sockaddr));
}

/*static*/ int CSocketHelper::Bind(socket_t socketfd, const struct sockaddr* addr)
{
	int ret = ::bind(socketfd, addr, sizeof(struct sockaddr));

	if(ret < 0)
	{
		LOG_ERROR << "socket bind return " << ret;
		return ret;
	}

	return 0;

}

/*static*/ int CSocketHelper::Listen(socket_t socketfd)
{
	const static uint32 max_back_log_num = 128;
	int ret = ::listen(socketfd, max_back_log_num);

	if(ret < 0)
	{
		LOG_ERROR << "socket:: listen return " << ret;
	}

	return ret;
}

/*static*/ int CSocketHelper::Accept(socket_t socketfd, struct sockaddr* addr)
{
	socklen_t len = sizeof(struct sockaddr);
	int conndfd = ::accept(socketfd, addr, &len);
	
	if(conndfd < 0)
	{
		LOG_ERROR << "accpet return " << conndfd;
	}

	SetNonblocking(conndfd);

	return 0;
}

/*static*/ ssize_t CSocketHelper::read(socket_t sockfd, void *buf, size_t count)
{
	return ::read(sockfd, buf, count);
}

/*static*/ ssize_t CSocketHelper::readv(socket_t sockfd, const struct iovec *iov, int iovcnt)
{
	return ::readv(sockfd, iov, iovcnt);
}

	
	
/*static*/ ssize_t CSocketHelper::write(socket_t sockfd, const void *buf, size_t count)
{
	return ::write(sockfd, buf, coount);
}



/*static*/ void CSocketHelper::close(socket_t sockfd)
{
	if(::close(sockfd) < 0)
	{
		LOG_ERROR << "close socket faild";
	}
	return;
}

/*static*/ void CSocketHelper::shutdownWrite(socket_t sockfd)
{
	if(::shutdown(sockfd, SHUT_WR) < 0)
	{
		LOG_ERROR << "shut down write faild";
	}

	return;
}
}