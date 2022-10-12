#pragma once

#include "CommunicationIF.h"

// Ugly shortcut... luck of time
#if WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#endif
// End of shortcut

class UdpCommunication : public CommunicationIF
{
public:
    UdpCommunication(int port);

    int m_port;

    int m_sockfd;

    virtual bool init();

	virtual int readMessage(char* buffer, int maxBytes);

	virtual int writeMessage(char* buffer, int nBytes);

private:

    struct sockaddr_in m_cliaddr; // Ugly shortcut... luck of time
};



