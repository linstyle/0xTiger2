//TemplateSln, main��������
#include "StdAfx.h"
#include "CMaster.h"
#include "Init/CInit.h"

initialiseSingleton(CMaster);

extern volatile bool g_bQuit;

CMaster::CMaster()
{
	ServerInit();
}

CMaster::~CMaster()
{
	ServerExit();
}


void CMaster::ServerInit()
{
	new CInit;

	//��������
	g_NetDriver.Init(&NetConnect, 1, NULL, 0);

	m_bLastTransSucceed = true;
}

bool CMaster::ServerLoop()
{	
	//g_NetDriver.Run();
	//return true;

	if( false==TransFile())
	{
		return false;
	}
	g_NetDriver.Run();
	DemoTransFile.TracerMe();
	g_NetDriver.TracerMe();	
	
	return true;
}

bool CMaster::TransFile()
{
	//�ж��Ƿ�����
	if(false==NetConnect.IsConnect())
	{
		return true;
	}

	//�ж��ϻ��Ƿ��ͳɹ�
	if(false==m_bLastTransSucceed)
	{
		if( 1==g_NetDriver.Send(&NetConnect, &m_FileTrans) )
		{
			printf("Warning, CMaster::ServerLoop:Send:Full\n");
			return true;
		}
	}

	unsigned int nLen = DemoTransFile.ReadContent(m_FileTrans.m_Buffer, 1000);
	if( 0==nLen ) //�������
	{
		return false;
	}

	m_FileTrans.m_BufferLen = nLen;
	if(nLen<1000)
	{
		printf("Notic, CMaster::TransFile():Trans End\n");
		m_FileTrans.m_bEnd=true;
	}
	

	if( 1==g_NetDriver.Send(&NetConnect, &m_FileTrans) )
	{
		printf("Warning, CMaster::ServerLoop:Send:Full\n");
		m_bLastTransSucceed = false;
		return true;
	}

	m_bLastTransSucceed = true;

	return true;
}

void CMaster::ServerExit()
{
	//g_bQuit = true;
	g_ThreadPool.Exit();

	/*
		���̱��ص���ɾ��
	*/
	delete CInit::getSingletonPtr();
}