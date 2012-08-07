#include "StdAfx.h"
#include "DemoPFileTrans.h"
#include "../Logic/Role/CRole.h"
#include "CNetObject.h"

using namespace std;

initialiseSingleton(PFileTransObject);
//TemplateSln
int	PFileTransObject::Execute(IPackHead* pPackHead, void* pRole)
{	
	PFileTrans *pFileTrans = (PFileTrans *)pPackHead;
	CRoleLogic *pRoleLogic =  ((CRole*)pRole)->GetRoleLogic();
	CIOCPData  *pRoleNet    =  ((CRole*)pRole)->GetRoleNet();
	
	pRoleLogic->Recv(pFileTrans->m_Buffer, pFileTrans->m_BufferLen);
	if( true==pFileTrans->m_bEnd )
	{
		printf("Notic, PFileTransObject::Execute:FlushHD(%x)\n", pRoleNet);
		pRoleLogic->FlushHD();
	}
	
	return 0;
}
