#pragma once

#ifndef IMPLEMENT_RS422_H_
#define IMPLEMENT_RS422_H_


#include "ImplementBase.h"
#include "ImplementMsg.h"
#include "DummyCommunication.h"


class Rs422Implement : public ImplementBase
{
public:
	Rs422Implement() 
	{
		m_comm = new DummyCommunication();
	}

	virtual ~Rs422Implement() {}

	virtual void doCycleInternal() {}
};

#endif