#pragma once

#include <exception>
#include <string>
#include <WinSock2.h>

class ISocket
{
public:
	virtual int Send(char *buffer, int length) = 0;
	virtual int Receive(char *buffer, int length) = 0;
};

class Socket : public ISocket
{
public:
	virtual int Send(char *buffer, int length) = 0;
	virtual int Receive(char *buffer, int length) = 0;
	virtual void Shutdown() = 0;

protected:
	SOCKET mRealSocket;
	WSADATA mWsaData;
};


class SocketException : public std::exception
{
public:
	SocketException(char *message) { mMessage = message; };

	virtual const char* what() const throw() { return mMessage; }

private:
	char *mMessage;
};