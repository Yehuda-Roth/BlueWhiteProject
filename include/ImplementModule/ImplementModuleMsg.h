#pragma once

#include "ImplementTypes.h"

#define MSG_HEADER 0xdeadbeef

#pragma pack(push,1)

enum class enumImpModuleMsgId
{
	ACTIVATE_IMP = 0x11,
	DEACTIVATE_IMP = 0x12,
	GET_IMP_FUEL = 0x13
};

struct ImpModuleMsg
{
	ImpModuleMsg()
		: m_msgHeader(MSG_HEADER), m_msgId(), m_id()
	{}

	ImpModuleMsg(enumImpModuleMsgId msgId, enumImplement id)
		: m_msgHeader(MSG_HEADER), m_msgId(msgId), m_id(id)
	{}

	int m_msgHeader;
	enumImpModuleMsgId m_msgId;
	enumImplement m_id;
};



#pragma pack(pop)

