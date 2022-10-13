#include <stdio.h> 
#include <stdlib.h> 

#include "UdpCommunication.h"

UdpCommunication::UdpCommunication(int port)
    : m_port(port), m_sockfd(-1), m_cliaddr()
{
    WSADATA Data;
    WSAStartup(MAKEWORD(2, 2), &Data); // 2.2 version
}

UdpCommunication::~UdpCommunication()
{
    if (m_sockfd >= 0)
    {
        closesocket(m_sockfd);
    }
}

bool UdpCommunication::init()
{
    // Code based on https://www.geeksforgeeks.org/udp-server-client-implementation-c/

    //char buffer[MAXLINE];
    //char* hello = "Hello from server";
    struct sockaddr_in servaddr;

    // Creating socket file descriptor 
    if ((m_sockfd = (int)socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return false;
    }

    // Set non-blocking socket
    u_long iMode = 1;

    int iResult = ioctlsocket(m_sockfd, FIONBIO, &iMode);
    if (iResult != NO_ERROR)
        printf("ioctlsocket failed with error: %ld\n", iResult);

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information 
    servaddr.sin_family = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(m_port);

    // Bind the socket with the server address 
    if (bind(m_sockfd, (const struct sockaddr*)&servaddr,
        sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        return false;
    }

    return true;
}

int UdpCommunication::readMessage(char* buffer, int maxBytes)
{
    int len, n;

    memset(&m_cliaddr, 0, sizeof(m_cliaddr));

    len = sizeof(m_cliaddr);  //len is value/result 

    n = recvfrom(m_sockfd, (char*)buffer, maxBytes,
        0, (struct sockaddr*)&m_cliaddr,
        &len);

    return n;
}

int UdpCommunication::writeMessage(char* buffer, int nBytes)
{
    int len = sizeof(m_cliaddr);  //len is value/result 

    return sendto(m_sockfd, (const char*)buffer, nBytes,
        0, (const struct sockaddr*)&m_cliaddr,
        len);
}
