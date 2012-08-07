#include "StdAfx.h"
#include "CCommonLibInit.h"

initialiseSingleton(CCommonLibInit);

//CNetTaskQueue *g_pNetTaskQueue;//�����������

CCommonLibInit::CCommonLibInit()
{
//	g_pNetTaskQueue = new CNetTaskQueue; //�����������
	
	new CWindowsSlabManager;          //�ڴ��
	printf("Notic, CCommonLibInit::CCommonLibInit():CWindowsSlabManager() OK\n");

	new CLogManager2;                       //��־
	printf("Notic, CCommonLibInit::CCommonLibInit():New CLogManager2 OK\n");

	new CPacketFactory;						//������
	printf("Notic, CCommonLibInit::CCommonLibInit():New CPacketFactory OK\n");

	new CObjectMapManager;              //����������
	printf("Notic, CCommonLibInit::CCommonLibInit():New CNetObjectManager OK\n");

	//new CThreadPool;						//�̳߳�	
	//printf("Notic, CCommonLibInit::CCommonLibInit():New CThreadPool OK\n");

	//new CNetTransToLogic;					//����-�߼����Ͳ�	
	//printf("Notic, CCommonLibInit::CCommonLibInit():New CNetTransToLogic OK\n");

	//new CNetDriver;							//����-������
	//printf("Notic, CCommonLibInit::CCommonLibInit():New CNetDriver OK\n");

	new CCmInitPackets;						//����Э���
	printf("Notic, CCommonLibInit::CCommonLibInit():New CCmInitPackets OK\n");

	new CLogicDriver;						//�߼�������
	printf("Notic, CCommonLibInit::CCommonLibInit():New CLogicDriver OK\n");

	new CNetDriver2;						//����������
	printf("Notic, CCommonLibInit::CCommonLibInit():New CNetDriver2 OK\n");

	new CThreadQuit;						//�˳��߳�
	printf("Notic, CCommonLibInit::CCommonLibInit():New CThreadQuit OK\n");
}

CCommonLibInit::~CCommonLibInit()
{
	delete g_ThreadQuit.getSingletonPtr();		//�˳��߳�
	printf("Notic, CCommonLibInit::~CCommonLibInit():Delete CThreadQuit OK\n");

	delete g_NetDriver2.getSingletonPtr();      //����������
	printf("Notic, CCommonLibInit::~CCommonLibInit():Delete CNetDriver2 OK\n");

	delete g_LogicDriver.getSingletonPtr();						//�߼�������
	printf("Notic, CCommonLibInit::CCommonLibInit():Delete CLogicDriver OK\n");

	delete CCmInitPackets::getSingletonPtr();  //����Э���
	printf("Notic, CCommonLibInit::~CCommonLibInit():Delete CCmInitPackets OK\n");

	//delete g_NetDriver.getSingletonPtr();   //����-������
	//printf("Notic, CCommonLibInit::~CCommonLibInit():Delete CNetDriver OK\n");

	//delete g_NetTransToLogic.getSingletonPtr();  //����-�߼����Ͳ�	
	//printf("Notic, CCommonLibInit::~CCommonLibInit():Delete CNetTransToLogic OK\n");


	//delete g_ThreadPool.getSingletonPtr();
	//printf("Notic, CCommonLibInit::~CCommonLibInit():Delete CThreadPool OK\n");

	delete g_NetObjectManager.getSingletonPtr();   //�������
	printf("Notic, CCommonLibInit::~CCommonLibInit():Delete CNetObjectManager OK\n");

	delete g_PacketFactory.getSingletonPtr();  //������
	printf("Notic, CCommonLibInit::~CCommonLibInit():Delete CPacketFactory OK\n");

	//�ȴ���־д��
	Sleep(2000);
	delete CLogManager2::getSingletonPtr();    //��־
	printf("Notic, CCommonLibInit::~CCommonLibInit():Delete CLogManager2 OK\n");
//	delete g_pNetTaskQueue;	

	delete CWindowsSlabManager::getSingletonPtr();
	printf("Notic, CCommonLibInit::~CCommonLibInit():CWindowsSlabManager OK\n");
}
