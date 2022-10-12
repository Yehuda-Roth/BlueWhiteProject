#include <iostream>

#include "ImplementModule.h"
#include "Implement.h"
#include "CommunicationIF.h"
#include "UdpCommunication.h"
#include "ImplementModuleMsg.h"


ImplementModule::ImplementModule()
{
	m_comm = new UdpCommunication(8080);
	m_comm->init();
}

bool ImplementModule::registerImpelement(enumImplement id, ImplementIF* implement)
{
	// Check if already registered
	if (m_implements.find(id) != m_implements.end())
	{
		std::cout << "Implement is already exist!!!" << std::endl;
		return false;
	}
	// Insert to implements map
	m_implements[id] = implement;

	return true;
}

bool ImplementModule::activateImplement(enumImplement id, bool active)
{
	bool retVal = false;
	auto it = m_implements.find(id);
	if (it != m_implements.end())
	{
		retVal = it->second->activate(active);
	}
	else
		std::cout << "Implement " << (int)id << " Not exist!!!\n";

	return retVal;
}

int ImplementModule::getImplementFuel(enumImplement id)
{
	int fuel = 0;

	auto it = m_implements.find(id);
	if (it != m_implements.end())
	{
		fuel = it->second->getFuelLevel();
	}
	else
		std::cout << "Implement " << (int)id << " Not exist!!!\n";

	return fuel;
}

void ImplementModule::doCycle()
{
	char buffer[1024];
	int msgLen = 0;

	if ((msgLen = m_comm->readMessage(buffer, sizeof(buffer))) > 0)
	{
		for (int i = 0; i < msgLen && msgLen - i >= sizeof(ImpModuleMsg); i++)
		{
			if (*(int*)(&buffer[i]) == MSG_HEADER)
			{
				ImpModuleMsg* msg = (ImpModuleMsg*)buffer;
				switch (msg->m_msgId)
				{
				case enumImpModuleMsgId::ACTIVATE_IMP:
					activateImplement(msg->m_id, true);
					break;
				case enumImpModuleMsgId::DEACTIVATE_IMP:
					activateImplement(msg->m_id, false);
					break;
				case enumImpModuleMsgId::GET_IMP_FUEL:
				{
					int fuel = getImplementFuel(msg->m_id);
					ImpModuleMsg outMsg(enumImpModuleMsgId::GET_IMP_FUEL, msg->m_id);
					m_comm->writeMessage((char*)&outMsg, sizeof(outMsg));
					break;
				}
				default:
					break;
				}

			}
		}
	}
}
