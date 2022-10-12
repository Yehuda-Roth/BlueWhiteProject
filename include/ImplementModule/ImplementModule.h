#pragma once

#include <map>

#include "ImplementTypes.h"

// Forward Declaration
class ImplementIF;
class CommunicationIF;


class ImplementModule
{
public:
	ImplementModule();

	virtual bool registerImpelement(enumImplement id, ImplementIF* implement);

	virtual bool activateImplement(enumImplement id, bool active);

	virtual int getImplementFuel(enumImplement id);

	void doCycle();

private:
	std::map<enumImplement, ImplementIF*> m_implements;

	CommunicationIF* m_comm;
};