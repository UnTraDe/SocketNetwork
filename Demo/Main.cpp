#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include "TCPSocket.h"

using namespace std;

char httpReq[] = "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n";

int main()
{
	try
	{
		TCPSocket socket;

		socket.Connect("www.google.co.il", 80);
		socket.Send(httpReq, sizeof(httpReq));

		char buffer[1024];
		memset(buffer, 0, 1024);

		socket.Receive(buffer, 1024);

		cout << buffer << endl;

		socket.Shutdown();
	}
	catch (SocketException e)
	{
		cout << e.what() << endl;
	}

	system("pause");

	return 0;
}