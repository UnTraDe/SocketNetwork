#include "TCPSocket.h"


TCPSocket::TCPSocket(SOCKET client)
{
	mRealSocket = client;
	mIsConnected = true;
}

void TCPSocket::Connect(const char *ip, int port)
{
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &mWsaData);

	if (iResult != 0)
	{
		WSACleanup();

		if (iResult == WSAVERNOTSUPPORTED)
		{
			throw SocketException("This implementation of WinSock does not support the requested version");
		}
		else
		{
			throw SocketException("Unknown error");
		}
	}

	struct addrinfo hints;

	ZeroMemory(&hints, sizeof (hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;


	char _port[5];
	memset(_port, 0, sizeof(port));
	_itoa_s(port, _port, 10);

	iResult = getaddrinfo(ip, _port, &hints, &mAddrInfo);

	if (iResult != 0)
	{
		WSACleanup();
		throw SocketException("Failed to resolve address");
	}

	mRealSocket = INVALID_SOCKET;

	mAddrInfoPtr = mAddrInfo;

	mRealSocket = socket(mAddrInfoPtr->ai_family, mAddrInfoPtr->ai_socktype, mAddrInfoPtr->ai_protocol);

	if (mRealSocket == INVALID_SOCKET)
	{
		Shutdown();
		throw SocketException("Failed to create socket");
	}

	iResult = connect(mRealSocket, mAddrInfoPtr->ai_addr, (int)mAddrInfoPtr->ai_addrlen);

	if (iResult == SOCKET_ERROR)
	{
		Shutdown();
		throw SocketException("Failed to connect to the remote address");
	}

	mIsConnected = true;
}

void TCPSocket::Bind(int port)
{
	int iResult = bind(mRealSocket, mAddrInfoPtr->ai_addr, (int)mAddrInfoPtr->ai_addrlen);

	if (iResult == SOCKET_ERROR)
	{
		Shutdown();
		throw SocketException("Failed to bind socket");
	}

	mIsBound = true;
}

void TCPSocket::Listen(int maxConnections)
{
	if (!mIsBound)
		throw SocketException("The socket must be bound in order to listen");

	int iResult = listen(mRealSocket, maxConnections);

	if (iResult == SOCKET_ERROR)
	{
		Shutdown();
		throw SocketException("Failed to bind socket");
	}

	mIsListening = true;
}

TCPSocket TCPSocket::Accept()
{
	SOCKET client = INVALID_SOCKET;

	client = accept(mRealSocket, NULL, NULL);

	if (client == INVALID_SOCKET)
	{
		Shutdown();
		throw SocketException("Error encountered during accept");
	}

	return TCPSocket(client);
}

void TCPSocket::Shutdown()
{
	//freeaddrinfo(mAddrInfo);
	closesocket(mRealSocket);
	WSACleanup();
}