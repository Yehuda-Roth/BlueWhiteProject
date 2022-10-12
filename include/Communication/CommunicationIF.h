#pragma once

class CommunicationIF
{
public:
	virtual bool init() = 0;

	virtual int readMessage(char* buffer, int maxBytes) = 0;

	virtual int writeMessage(char* buffer, int nBytes) = 0;

private:

};
