#include "CTProtocol.h"
#include <stdio.h>

void CProtocolA::TracerMe()
{
	printf("m_nT1:%d\n", m_nT1);
	printf("m_nT2:%d\n", m_nT2);
	printf("m_nT3:%d\n", m_nT3);
	printf("m_nT4:%d\n", m_nT4);
	printf("m_nT5:%d\n", m_nT5);
	printf("m_nT6:%d\n", m_nT6);
}

CProtocolA::CProtocolA()
{
	Init();
}

bool CProtocolA::Init()
{
	m_nSize = 0;
	//-1为无效值
	m_nT1 = -1;
	m_nT2 = -1;
	m_nT3 = -1;
	m_nT4 = -1;
	m_nT5 = -1;
	m_nT6 = -1;
	return true;
}

int CProtocolA::GetSize()
{
	return m_nSize;
}

void CProtocolA::SetT1(int nValue)
{
	m_nT1=nValue;
}
void CProtocolA::SetT2(int nValue)
{
	m_nT2=nValue;
}
void CProtocolA::SetT3(int nValue)
{
	m_nT3=nValue;
}

void CProtocolA::SetT4(int nValue)
{
	m_nT4=nValue;
	m_ProtocolFlagLite.SetFlag(0);
}
void CProtocolA::SetT5(int nValue)
{
	m_nT5=nValue;
	m_ProtocolFlagLite.SetFlag(1);
}
void CProtocolA::SetT6(int nValue)
{
	m_nT6=nValue;
	m_ProtocolFlagLite.SetFlag(2);
}

void CProtocolA::Send(char* pBuffer)
{
	CProtocolSerialLiteSend SerialLiteSend;
	Serial(&SerialLiteSend, pBuffer);
}

void CProtocolA::Recv(char* pBuffer)
{
	CProtocolSerialLiteRecv SerialLiteRecv;
	Serial(&SerialLiteRecv, pBuffer);
}


void CProtocolA::Serial(CIProtocolSerialLite *pSerialLite, char* pBuffer)
{
	pBuffer=pSerialLite->Serial(pBuffer, (char*)&m_nT1, sizeof(m_nT1));
	m_nSize += sizeof(m_nT1);

	pBuffer=pSerialLite->Serial(pBuffer, (char*)&m_nT2, sizeof(m_nT2));
	m_nSize += sizeof(m_nT2);

	pBuffer=pSerialLite->Serial(pBuffer, (char*)&m_nT3, sizeof(m_nT3));
	m_nSize += sizeof(m_nT3);

	//flag数据
	pBuffer=pSerialLite->Serial(pBuffer, (char*)&m_ProtocolFlagLite, sizeof(m_ProtocolFlagLite));
	m_nSize += sizeof(m_ProtocolFlagLite);

	if(0!=m_ProtocolFlagLite.GetFlag(0))
	{
		pBuffer=pSerialLite->Serial(pBuffer, (char*)&m_nT4, sizeof(m_nT4));
		m_nSize += sizeof(m_nT4);
	}

	if(0!=m_ProtocolFlagLite.GetFlag(1))
	{
		pBuffer=pSerialLite->Serial(pBuffer, (char*)&m_nT5, sizeof(m_nT5));
		m_nSize += sizeof(m_nT5);
	}

	if(0!=m_ProtocolFlagLite.GetFlag(2))
	{
		pBuffer=pSerialLite->Serial(pBuffer, (char*)&m_nT6, sizeof(m_nT6));
		m_nSize += sizeof(m_nT6);
	}
}