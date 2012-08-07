#include "StdAfx.h"
#include "HelloWorld.h"
#include "../Logic/Role/CRole.h"


initialiseSingleton(PHelloWorldObject);
//TemplateSln
int	PHelloWorldObject::Execute(IPackHead* pPackHead, void* pPlayLogic, void* pPlayNet)
{	
	PHelloWorld *pHelloWorld = (PHelloWorld *)pPageHead;
	CRole *pRole = (CRole*)pPlayLogic;

	DWORD dwEnd = GetTickCount();
	/*
	printf("Recvxxxxxxxxxxxtime:%d\n", dwBegin);
	printf("RecvxxxxxxxxxxxxxxxRole time:%d, sub time:%d, id:%d \n", 
		pHelloWorld->nTimeSec, dwBegin- pHelloWorld->nTimeSec, pHelloWorld->id);
		*/

	//printf("xxxxsub time:%d\n", dwEnd - pHelloWorld->nTimeSec);
	return 0;
}