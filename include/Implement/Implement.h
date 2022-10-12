#pragma once

class ImplementIF
{
public:
	ImplementIF();

	~ImplementIF();

	virtual bool activate(bool active);

	virtual long getFuelLevel();

	virtual bool isActive();

	virtual void doCycle();



private:

};

class UdpImplement : public ImplementIF
{
public:
	virtual bool activate(bool active)
	{
		m_activateCmd = active;
	}

	virtual long getFuelLevel()
	{
		return m_fuelLevel;
	}

	virtual bool isActive()
	{
		return m_isActive;
	}

	long m_fuelLevel;

	bool m_isActive;

	bool m_activateCmd;

	virtual void doCycle()
	{
		char buffer[1024];
		int msgLen = 0;

		if (m_fuelLevel < m_fuelThresholdLevel)
		{
			m_activateCmd = false;
		}

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


private:
	CommunicationIF* m_comm;
};