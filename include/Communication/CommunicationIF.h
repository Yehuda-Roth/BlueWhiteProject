#pragma once
#ifndef COMMUNICATION_IF_H_
#define COMMUNICATION_IF_H_

class CommunicationIF
{
public:
	virtual ~CommunicationIF() {}

	virtual bool init() = 0;

	virtual int readMessage(char* buffer, int maxBytes) = 0;

	virtual int writeMessage(char* buffer, int nBytes) = 0;

private:

};

#endif
