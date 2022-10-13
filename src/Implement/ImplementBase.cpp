#include "..\..\include\Implement\ImplementBase.h"

ImplementBase::ImplementBase()
	: m_comm(nullptr), m_activateCmd(false), m_fuelLevel(0), m_isActive(false)
	, m_lastActivateCmd(false)
{}

bool ImplementBase::init()
{
	return m_comm->init();
}

bool ImplementBase::activate(bool active)
{
	m_activateCmd = active;

	return true;
}

long ImplementBase::getFuelLevel()
{
	return m_fuelLevel;
}

bool ImplementBase::isActive()
{
	return m_isActive;
}

void ImplementBase::doCycle()
{
	if (m_fuelLevel < m_fuelThresholdLevel)
	{
		m_activateCmd = false;
	}

	doCycleInternal();
}
