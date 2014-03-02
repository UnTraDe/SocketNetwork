SocketNetwork
=============

A simple library which wraps the WinSock 2 sockets to provide a simpler object-oriented interface with them.


Usage
=============


    char httpReq[] = "GET / HTTP/1.1\r\nHost: www.google.co.il\r\n\r\n";
    
    TCPSocket socket;
    socket.Connect("www.google.co.il", 80);
    socket.Send(httpReq, sizeof(httpReq));
    
    char buffer[1024];
    memset(buffer, 0, 1024);
    
    socket.Receive(buffer, 1024);
    
    printf("%s", buffer);
    
    socket.Shutdown();
