#include <iostream>

#include "ImplementModule.h"
#include "ImplementIF.h"
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

bool ImplementModule::getImplementStatus(enumImplement id)
{
	bool status = false;

	auto it = m_implements.find(id);
	if (it != m_implements.end())
	{
		status = it->second->isActive();
	}
	else
		std::cout << "Implement " << (int)id << " Not exist!!!\n";

	return status;
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
					std::cout << "ACTIVATE_IMP MSG" << std::endl;
					activateImplement(msg->m_id, true);
					break;
				case enumImpModuleMsgId::DEACTIVATE_IMP:
					std::cout << "DEACTIVATE_IMP MSG" << std::endl;
					activateImplement(msg->m_id, false);
					break;
				case enumImpModuleMsgId::QUERY_IMP_FUEL:
				{
					std::cout << "QUERY_IMP_FUEL MSG" << std::endl;
					int fuel = getImplementFuel(msg->m_id);
					ImpModuleMsg outMsg(enumImpModuleMsgId::QUERY_IMP_FUEL, msg->m_id, fuel);
					m_comm->writeMessage((char*)&outMsg, sizeof(outMsg));
					break;
				}
				case enumImpModuleMsgId::QUERY_IMP_STATUS:
				{
					std::cout << "QUERY_IMP_STATUS MSG" << std::endl;
					int fuel = getImplementFuel(msg->m_id);
					ImpModuleMsg outMsg(enumImpModuleMsgId::QUERY_IMP_FUEL, msg->m_id, fuel);
					m_comm->writeMessage((char*)&outMsg, sizeof(outMsg));
					break;
				}
				default:
					break;
				}

			}
		}
	}

	// Run all implements
	for (auto const& pair : m_implements) 
	{
		pair.second->doCycle();
	}
}
