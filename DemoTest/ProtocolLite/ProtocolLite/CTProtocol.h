#pragma  once
/*
	CProtocolLite的测试用例
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
	int m_nSize;		//实际发送的大小

	//连续发送
	int m_nT1;
	int m_nT2;
	int m_nT3;

	//有选择性的发送
	int m_nT4;
	int m_nT5;
	int m_nT6;


};