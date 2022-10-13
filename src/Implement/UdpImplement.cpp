#include "UdpImplement.h"
#include "UdpCommunication.h"

UdpImplement::UdpImplement(int port)
{
	m_comm = new UdpCommunication(port);
}

UdpImplement::~UdpImplement()
{
	delete m_comm;
}

void UdpImplement::doCycleInternal()
{
	char buffer[1024];
	int msgLen = 0;

	if ((msgLen = m_comm->readMessage(buffer, sizeof(buffer))) > 0)
	{
		for (int i = 0; i < msgLen && msgLen - i >= sizeof(ImpMsg); i++)
		{
			if (*(int*)(&buffer[i]) == MSG_HEADER)
			{
				ImpMsg* msg = (ImpMsg*)buffer;
				switch (msg->m_msgId)
				{
				case enumImpMsgId::IMP_FUEL_MSG:
					m_fuelLevel = msg->m_param;
					break;
				case enumImpMsgId::IMP_STATUS_MSG:
					m_isActive = (bool)msg->m_param;
					break;
				default:
					break;
				}

			}
		}
	}

	if (m_activateCmd != m_lastActivateCmd)
	{
		ImpMsg outMsg(m_activateCmd ? enumImpMsgId::ACTIVATE_IMP_MSG : enumImpMsgId::DEACTIVATE_IMP_MSG);
		m_comm->writeMessage((char*)&outMsg, sizeof(outMsg));
		m_lastActivateCmd = m_activateCmd;
	}
}
