#include "StdAfx.h"
#include "CRoleLogic.h"
#include "MTVERIFY.h"

CRoleLogic::CRoleLogic()
{
	Init();
	InitSavaTerminalW();
}
CRoleLogic::~CRoleLogic()
{
	CloseSaveTerminal();
}
void CRoleLogic::Init()
{
	m_nHasRecvLen = 0;
	static int m_nID=0;
	sprintf(m_SavaTerminalName, "recv%d", m_nID++);
}

void CRoleLogic::InitSavaTerminalW()
{
	m_pFile = fopen(m_SavaTerminalName, "wb+");
	MTVERIFY(m_pFile!=NULL);
}
void CRoleLogic::InitSavaTerminalR()
{
	m_pFile = fopen(m_SavaTerminalName, "rb+");
	MTVERIFY(m_pFile!=NULL);
}

void CRoleLogic::CloseSaveTerminal()
{
	fclose(m_pFile);
}

void CRoleLogic::Recv(const char* pBuffer, int nSize)
{
	if( nSize>name_role::BUFFER_SIZE )
	{
		printf("Notic, CRoleLogic::Recv:nSize(%d)>name_role::BUFFER_SIZE(%d)", nSize, name_role::BUFFER_SIZE);
		return;
	}
	if( nSize>(name_role::BUFFER_SIZE-m_nHasRecvLen) )
	{
		_FlushHD();
	}
	memcpy(&m_BufferFile[m_nHasRecvLen], pBuffer, nSize);
	m_nHasRecvLen += nSize;

	static int _nSize=0;
	_nSize += nSize;
}

void CRoleLogic::FlushHD()
{	
	_FlushHD();
	VerifyMD5();
}

void CRoleLogic::_FlushHD()
{
	int nTempLen;
	nTempLen = fwrite(m_BufferFile, 1, m_nHasRecvLen, m_pFile);
	if(nTempLen!=m_nHasRecvLen)
	{
		assert(0);
	}
	m_nHasRecvLen = 0;
	fflush(m_pFile);
}

void CRoleLogic::VerifyMD5()
{
	//两边MD5对比，是否正确
	int nFileLen, nFileHasRead;
	char *pFileBuffer;

	//先进行关闭
	CloseSaveTerminal();
	InitSavaTerminalR();

	//求长度
	fseek(m_pFile, 0, SEEK_END);
	nFileLen = ftell(m_pFile);
	pFileBuffer = new char[nFileLen];
	fseek(m_pFile, 0, SEEK_SET);

	//读入
	nFileHasRead = fread(pFileBuffer, 1, nFileLen, m_pFile);
	if(nFileHasRead != nFileLen)
	{
		printf("Err, CRoleLogic::FlushHD():fread:nFileHasRead != nFileLen, errid:%d\n", GetLastError());
	}

	string strMD5 = CMD5::MD5(pFileBuffer, nFileLen);
	printf("Notic, File Len:%d, MD5:%s\n", nFileLen, strMD5.c_str());

	delete pFileBuffer;
}