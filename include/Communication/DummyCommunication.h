#pragma once
#ifndef DUMMY_COMMUNICATION_H_
#define DUMMY_COMMUNICATION_H_

#include "CommunicationIF.h"

class DummyCommunication : public CommunicationIF
{
public:
    DummyCommunication() {}

    virtual ~DummyCommunication() {}

    virtual bool init() { return true; }

    virtual int readMessage(char* buffer, int maxBytes) { return 0; }

    virtual int writeMessage(char* buffer, int nBytes) { return 0; }

private:

};

#endif

