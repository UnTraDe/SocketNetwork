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
	SocketException(const char *message) { mMessage = message; mErrorCode = 0; };
	SocketException(const char *message, int errorCode) { mMessage = message;  mErrorCode = errorCode; };

	virtual const char* what() const throw() { return mMessage; }
	int getErrorCode() { return mErrorCode;  }

private:
	const char *mMessage;
	int mErrorCode;
};