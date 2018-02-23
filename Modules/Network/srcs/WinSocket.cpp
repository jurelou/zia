//
// Created by marmus_a on 25/01/18.
//

#include "WinSocket.hpp"

WinSocket::WinSocket()
{

	WSADATA wsaData = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	this->opened = false;
	this->netInfo.sock = this;
	if ((this->socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		std::cerr << "Failed to open socket:" << WSAGetLastError() << std::endl;
	}
}

WinSocket::~WinSocket()
{
	this->close();
}

bool WinSocket::bind(const std::string & addr, const std::string & port)
{
	return (this->bind(addr, std::stoi(port)));
}

bool WinSocket::bind(const std::string & addr, int port)
{
	this->addr.sin_family = AF_INET;
	this->addr.sin_port = htons(port);
	this->addr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(this->socket, (const struct sockaddr *)(&this->addr), sizeof(this->addr)) != 0) {
		std::cerr << "failed to bind socket on " << addr << std::endl;
		return (false);
	}
	this->netInfo.port = port;
	this->netInfo.ip.i = this->addr.sin_addr.S_un.S_addr;
	this->netInfo.ip.str = ::inet_ntoa(this->addr.sin_addr);
	return (true);
}

bool WinSocket::listen()
{
	this->opened = true;
	this->netInfo.time = std::chrono::system_clock::now();
	return (!::listen(this->socket, WinSocket::MAXQUEUE));
}

bool WinSocket::accept(zia::api::ImplSocket& socket)
{
	int addrLen = sizeof(struct sockaddr_in);

	auto winSocket = dynamic_cast<WinSocket *>(&socket);
	if (winSocket) {
		if ((winSocket->socket = ::accept(this->socket, (struct sockaddr *)&winSocket->addr, &addrLen)) == INVALID_SOCKET) {
			std::cerr << "Failed to accept " << ::inet_ntoa(winSocket->addr.sin_addr) << std::endl;
			return (false);
		}
		winSocket->netInfo.ip.i = winSocket->addr.sin_addr.S_un.S_addr;
		winSocket->netInfo.ip.str = ::inet_ntoa(winSocket->addr.sin_addr);
		winSocket->netInfo.port = this->netInfo.port;
		winSocket->netInfo.time = std::chrono::system_clock::now();
		winSocket->opened = true;
		return (true);
	}
	return (false);
}

bool WinSocket::close()
{
	this->opened = false;
	return (!::closesocket(this->socket));
}

int WinSocket::send(const std::string & str)
{
	return (::send(this->socket, str.c_str(), str.size(), 0));
}

int WinSocket::recv(std::string & buff)
{
	char	buffer[4046];
	int		res;

	res = ::recv(this->socket, (char *)&buffer, 4096, 0);
	buffer[res] = 0;
	buff = buffer;
	return (res);
}

int WinSocket::getSocket() const
{
	return (this->socket);
}

bool WinSocket::isOpen() const
{
	return (this->opened);
}

const zia::api::NetInfo & WinSocket::getInfo() const
{
	return (this->netInfo);
}
