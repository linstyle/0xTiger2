#include "CRouteTableManager.h"
#include <Winsock2.h>

CRouteTableManager::CRouteTableManager()
{
	ReadFromConfigManager();
	Init();
	TracerMe();
}

CRouteTableManager::~CRouteTableManager()
{
	delete[] pLogicServerBin;
}

void CRouteTableManager::Init()
{
	pLogicServerBin = new LOGIC_SERVER_LINE[nMaxLine];

	for(int i=0; i<nMaxLine; ++i)
	{
		pLogicServerBin[i].nLine = i;
		pLogicServerBin[i].pScene = new LOGIC_SERVER_BIN[nMaxBinCount];
		for(int j=0; j<nMaxBinCount; ++j)
		{
			pLogicServerBin[i].pScene[j].nIdenti = j;
		}
	}

}

void CRouteTableManager::TracerMe()
{
	printf("\nCRouteTableManager::TracerMe()\n");
	printf("nMaxLine:%d		nMaxBinCount:%d\n", nMaxLine, nMaxBinCount);
	CallBackTracerMe();
}

void CRouteTableManager::CallBackTracerMe()
{
	int i,j, nAddrLen;
	sockaddr Addr;
	sockaddr_in *pAddrUse;
	LOGIC_SERVER_BIN *pLogicBin;

	printf("\nCRouteTableManager::CallBackTracerMe()\n");
	printf("LogicServerBin:\n");
	for(i=0; i<nMaxLine; ++i)
	{
		printf("Line:%d\n", i);
		for(j=0; j<nMaxBinCount; ++j)
		{
			nAddrLen = sizeof(Addr);
			pLogicBin = &pLogicServerBin[i].pScene[j];
			if( false==pLogicBin->bEnable )
			{
				printf("Index(Identi):%d	Enable:%d\n", pLogicBin->nIdenti, pLogicBin->bEnable);
				continue;
			}
			if( 0!=getsockname(pLogicBin->nSocket, &Addr, &nAddrLen))
			{
				continue;
			}
			pAddrUse = (sockaddr_in*)&Addr;
			printf("Index(Identi):%d	Enable:%d	IP:%s	Port:%d  MRoleSum:%d\n", 
					pLogicBin->nIdenti, pLogicBin->bEnable,
					inet_ntoa(pAddrUse->sin_addr), ntohs(pAddrUse->sin_port),
					pLogicBin->nMRoleSum	
				   );
		}
	}

	printf("LogicServerDpc:\n");
	
	if( false==LogicServerDpc.bEnable ) 
	{
		printf("Enable:%d \n", LogicServerDpc.bEnable);
		return;
	}
	nAddrLen = sizeof(Addr);
	if( 0!=getsockname(LogicServerDpc.nSocket, &Addr, &nAddrLen))
	{
		return;
	}
	pAddrUse = (sockaddr_in*)&Addr;
	printf("Enable:%d	IP:%s	Port:%d\n",
			inet_ntoa(pAddrUse->sin_addr), ntohs(pAddrUse->sin_port)
		  );

}

void CRouteTableManager::ReadFromConfigManager()
{
	CConfigManager::ReadGameInfo(&nMaxLine, &nMaxBinCount);
}

LOGIC_SERVER_BIN * CRouteTableManager::BinVerifyIdenti(int nLine, int nBinIdenti)
{	
	if( nLine>=nMaxLine || nBinIdenti>=nMaxBinCount)
		return NULL;

	return &pLogicServerBin[nLine].pScene[nBinIdenti];
}


int CRouteTableManager::BinAdd(int nLine, int nBinIdenti, int nSocket)
{
	LOGIC_SERVER_BIN *pBinScene = BinVerifyIdenti(nLine, nBinIdenti);

	if( NULL==pBinScene )
		return -1;
//debug
	if( true==pBinScene->bEnable )
	{
		printf("Warning, CRouteTableManager::BinAdd:true==pBinScene[nServerIdenti].bEnable\n");
	}
	
	pBinScene->bEnable = true;
	pBinScene->nSocket = nSocket;

	return 0;
}

int CRouteTableManager::DpcAdd(int nSocket)
{
	LogicServerDpc.bEnable = true;
	LogicServerDpc.nSocket = nSocket;
	return 0;
}


void CRouteTableManager::BinErase(int nLine, int nBinIdenti)
{
	LOGIC_SERVER_BIN *pBinScene = BinVerifyIdenti(nLine, nBinIdenti);

	if( NULL==pBinScene )
		return ;

	pBinScene->bEnable = false;
}


int CRouteTableManager::GetBinSocketByIdenti(int nLine, int nBinIdenti)
{
	LOGIC_SERVER_BIN *pLogicServer = BinVerifyIdenti(nLine, nBinIdenti);

	if( NULL==pLogicServer )
		return -1;

	if( false==pLogicServer->bEnable )
	{
		return -1;
	}

	return pLogicServer->nSocket;	
}

int CRouteTableManager::GetDpcSocket()
{
	return LogicServerDpc.nSocket;
}
