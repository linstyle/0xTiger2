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
	//pVariable拷贝到pBuffer
	virtual char* Serial(char* pBuffer, char* pVariable, int nVariableSize);

private:

public:

private:

};

class CProtocolSerialLiteRecv:public CIProtocolSerialLite
{
public:
	//pBuffer拷贝到pVariable
	virtual char* Serial(char* pBuffer, char* pVariable, int nVariableSize);

private:

public:

private:

};

class CProtocolFlagLite
{
public:
	CProtocolFlagLite();
	//按2进制打印，方便DEBUG
	void TracerMe();
	
	//nBit:表示第几个,从0开始，失败返回-1
	int SetFlag(int nBit);

	//nBit:表示第几个,从0开始，无效返回0
	int GetFlag(int nBit);
private:

	//十进制转二进制,供debug用
	char* DecimalToBinary(int nDecimal, char *pBuffer);

public:

private:
	int m_nFlag[2];

	int m_nMaxFlag;  //支持的最大标识位，大小是m_nFlag的总和
	int m_nFlagCount; //数组m_nFlag的个数
};
