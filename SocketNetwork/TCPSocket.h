#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Socket.h"

class TCPSocket : public Socket
{
public:
	TCPSocket() : mIsConnected(false), mIsBound(false), mIsListening(false) { Initialize(); }
	TCPSocket(const char *ip, int port) : mIsConnected(true) { Initialize(); Connect(ip, port); }
	~TCPSocket() { Shutdown(); }

	int Send(char *buffer, int length) { return send(mRealSocket, buffer, length, 0); }
	int Receive(char *buffer, int length) { return recv(mRealSocket, buffer, length, 0); }
	void Connect(const char *ip, int port);
	void Bind(int port);
	void Listen(int maxConnections);
	TCPSocket* Accept();
	

private:
	TCPSocket(SOCKET socket);
	void Initialize();
	void Shutdown();
	struct addrinfo *mAddrInfo, *mAddrInfoPtr;
	bool mIsConnected;
	bool mIsBound;
	bool mIsListening;
};