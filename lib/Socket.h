#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>

#include "base.h"
namespace lib
{

using socket_t = int;

class STAddrInfo;

class Socket
{
  public:
	Socket(socket_t fd);

	~Socket();

	int listen();

	int bindaddress(const STAddrInfo &stAddrinfo);

	int accept(STAddrInfo *stPeerAddrInfo);

	socket_t getfd() const
	{
		return m_tFd;
	}

	void shutdownWrite();

	///
	/// Enable/disable TCP_NODELAY (disable/enable Nagle's algorithm).
	///
	void setTcpNoDelay(bool on);

	///
	/// Enable/disable SO_REUSEADDR
	///
	void setReuseAddr(bool on);

	///
	/// Enable/disable SO_REUSEPORT
	///
	void setReusePort(bool on);

	///
	/// Enable/disable SO_KEEPALIVE
	///
	void setKeepAlive(bool on);

  private:
	socket_t m_tFd;
};

class CSocketHelper
{
  public:
	CSocketHelper()
	{
	}

	~CSocketHelper()
	{
	}


	static int SetNonblocking(socket_t fd);

	static int Connect(socket_t socketfd, const struct sockaddr* addr);

	static int Bind(socket_t socketfd, const struct sockaddr* addr);

	static int Listen(socket_t socketfd);

	static int Accept(socket_t socketfd, struct sockaddr* addr);

	static ssize_t read(socket_t sockfd, void *buf, size_t count);
	static ssize_t readv(socket_t sockfd, const struct iovec *iov, int iovcnt);

	static ssize_t write(socket_t sockfd, const void *buf, size_t count);

	static void close(socket_t sockfd);

	static void shutdownWrite(socket_t sockfd);

	static socket_t CreateNonblockingSocket();

	static socket_t CreateUDPServer(int Port);

	static void CloseSocket(socket_t fd);

	static std::string ToIPPort(const struct sockaddr_in *ss);
};

} // namespace lib
