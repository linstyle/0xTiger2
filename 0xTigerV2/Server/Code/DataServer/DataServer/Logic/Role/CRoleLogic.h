/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2011/02/25                                                        
    ����˵����  �߼����󣬻��߳�Ϊ����
*/


#pragma once

/*
	�ļ������CRoleLogic DEMO
*/
#include <stdio.h>
#include <string>
#include "md5.h"


using namespace std;
namespace name_role
{
	const int BUFFER_SIZE = 1024*1024; //byte
}

class CRoleLogic
{
public:
	CRoleLogic();
	~CRoleLogic();
	void Init();
	

	/*
		�������ݳ��Ⱥ�ָ�룬�����ǰ�������������ɣ����Զ�����
		FlushHDˢ�µ����̡�
	*/
	void Recv(const char* pBuffer, int nSize);
	/*
		ˢ�µ�����
	*/
	void FlushHD();
	
private:
	//md5У��
	void VerifyMD5();
	
	void InitSavaTerminalW();	//д��
	void InitSavaTerminalR();	//��ȡ
	void CloseSaveTerminal();
	void _FlushHD();

public:
	char m_BufferFile[name_role::BUFFER_SIZE];
	int m_nHasRecvLen;
	FILE *m_pFile;

private:
	char m_SavaTerminalName[128];	//������ļ���
};