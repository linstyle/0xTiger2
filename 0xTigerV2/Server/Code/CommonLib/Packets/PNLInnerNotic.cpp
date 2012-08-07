#include "StdAfx.h"
#include "PNLInnerNotic.h"
#include "CObjectMapManager.h"

initialiseSingleton(PNLInnerNoticObject);

int	PNLInnerNoticObject::Execute(IPackHead* pPackHead)
{
	switch (pPackHead->GetPacketDefine2())
	{
	case PACKET2_NTOL_ACCEPT_SOCKET:  //���µ�����
		LOGN("PNLInnerNoticObject::Execute.PACKET2_NTOL_ACCEPT_SOCKET :%x\n", pPackHead);

		break;
	case  PACKET2_NTOL_ERR: //�����Ͷ�ݵĳ����
		LOGN("PNLInnerNoticObject::Execute.PACKET2_NTOL_ERR  :%x\n", pPackHead);
		break;

	default:
		//IF(pPackHead->GetPacketDefine2())
		LOGE("PNLInnerNoticObject::Execute. case default:%d\n", pPackHead->GetPacketDefine2());

	}
	return 0;
}
