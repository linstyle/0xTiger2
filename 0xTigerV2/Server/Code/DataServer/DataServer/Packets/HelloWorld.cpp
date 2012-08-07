#include "StdAfx.h"
#include "HelloWorld.h"
#include "../Logic/Role/CRole.h"


initialiseSingleton(PHelloWorldObject);
//TemplateSln
int	PHelloWorldObject::Execute(IPackHead* pPackHead, void* pRoleObject)
{	
	PHelloWorld *pHelloWorld = (PHelloWorld *)pPackHead;
	CRole *pRole = (CRole *)pRoleObject;
	CRoleLogic *pRoleLogic = pRole->GetRoleLogic();
	CIOCPData *pRoleNet = pRole->GetRoleNet();

//	printf("Recvxxxxxxxxxxxtime:%d\n", GetTickCount());
//	printf("Sendxxxxxxxxxxx,role:%x, time:%d, id:%d\n", pRole, pHelloWorld->nTimeSec, pHelloWorld->id);
//	pHelloWorld->nTimeSec1 = GetTickCount();

	return pRoleNet->Send(pPackHead);

	return 0;
}