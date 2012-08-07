//PhonebookServer,main��������
#include "StdAfx.h"
#include "CMaster.h"
#include "DemoPFileTrans.h"

initialiseSingleton(CMaster);


void CMaster::ServerInit()
{
	/*
		���̱��ص�������
	*/
	new CRoleAllocator;
	new PExceptionObject;	
	new PAcceptObject;
	new PHelloWorldObject;

	for(int i=0; i<CONNECT_COUNT; ++i)
	{
	//	g_NetDriver.AddLocalObjectConnect(&m_NetConnect[i]);
	}
	//g_NetDriver.Fire();
}

bool CMaster::ServerLoop()
{
	for(int i=0; i<CONNECT_COUNT; ++i)
	{
		if( true==m_NetConnect[i].IsConnect() )
		{
			PHelloWorld HelloWorld;
			m_NetConnect[i].Send(&HelloWorld);
		}
	}
	
//	g_NetDriver.TracerMe();

	return true;
}

void CMaster::ServerExit()
{
	g_ThreadPool.Exit();

	/*
		���̱��ص���ɾ��
	*/
	delete PHelloWorldObject::getSingletonPtr();
	delete PAcceptObject::getSingletonPtr();
	delete PExceptionObject::getSingletonPtr();
	delete CRoleAllocator::getSingletonPtr();
}