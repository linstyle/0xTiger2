#pragma  once




class CIProtocolSerialLite
{
public:
	virtual char* Serial(char* pBuffer, char* pVariable, int nVariableSize)=0;

private:

public:

private:

};

class CProtocolSerialLiteSend:public CIProtocolSerialLite
{
public:	
	//pVariable������pBuffer
	virtual char* Serial(char* pBuffer, char* pVariable, int nVariableSize);

private:

public:

private:

};

class CProtocolSerialLiteRecv:public CIProtocolSerialLite
{
public:
	//pBuffer������pVariable
	virtual char* Serial(char* pBuffer, char* pVariable, int nVariableSize);

private:

public:

private:

};

class CProtocolFlagLite
{
public:
	CProtocolFlagLite();
	//��2���ƴ�ӡ������DEBUG
	void TracerMe();
	
	//nBit:��ʾ�ڼ���,��0��ʼ��ʧ�ܷ���-1
	int SetFlag(int nBit);

	//nBit:��ʾ�ڼ���,��0��ʼ����Ч����0
	int GetFlag(int nBit);
private:

	//ʮ����ת������,��debug��
	char* DecimalToBinary(int nDecimal, char *pBuffer);

public:

private:
	int m_nFlag[2];

	int m_nMaxFlag;  //֧�ֵ�����ʶλ����С��m_nFlag���ܺ�
	int m_nFlagCount; //����m_nFlag�ĸ���
};
