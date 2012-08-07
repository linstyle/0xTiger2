#pragma  once
/*
	CProtocolLite�Ĳ�������
*/
#include "CProtocolSerialLite.h"

class CProtocolA
{
public:
	CProtocolA();
	bool Init();
	void TracerMe();

	void Send(char* pBuffer);
	void Recv(char* pBuffer);

	int GetSize();
	void SetT1(int nValue);
	void SetT2(int nValue);
	void SetT3(int nValue);

	void SetT4(int nValue);
	void SetT5(int nValue);
	void SetT6(int nValue);
private:
	void Serial(CIProtocolSerialLite *pSerialLite, char* pBuffer);

public:

private:
	CProtocolFlagLite m_ProtocolFlagLite;
	int m_nSize;		//ʵ�ʷ��͵Ĵ�С

	//��������
	int m_nT1;
	int m_nT2;
	int m_nT3;

	//��ѡ���Եķ���
	int m_nT4;
	int m_nT5;
	int m_nT6;


};