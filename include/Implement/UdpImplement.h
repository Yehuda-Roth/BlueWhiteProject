#pragma once

#ifndef IMPLEMENT_UDP_H_
#define IMPLEMENT_UDP_H_


#include "ImplementBase.h"
#include "ImplementMsg.h"

class UdpImplement : public ImplementBase
{
public:
	UdpImplement(int port);

	virtual ~UdpImplement();

	virtual void doCycleInternal();
};

#endif