#pragma once
#ifndef IMPLEMENT_BASE_H_
#define IMPLEMENT_BASE_H_

#include "ImplementIF.h"
#include "CommunicationIF.h"

class ImplementBase : public ImplementIF
{
public:

	ImplementBase();

	virtual ~ImplementBase() {}

	virtual bool init();

	virtual bool activate(bool active);

	virtual long getFuelLevel();

	virtual bool isActive();

	virtual void doCycle();

protected:
	
	virtual void doCycleInternal() = 0;


	long m_fuelLevel;

	long m_fuelThresholdLevel;

	bool m_isActive;

	bool m_activateCmd;

	bool m_lastActivateCmd;

	CommunicationIF* m_comm;
};

#endif