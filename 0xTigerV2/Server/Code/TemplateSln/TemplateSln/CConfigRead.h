/************************************************************************/
/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/06/17                                                         
    ����˵����  ��̬�Ķ�ȡ������Ϣ����ȫ��ʹ��
*/
/************************************************************************/


#pragma once

#include "MTVERIFY.h"

class CConfigRead
{
public:
	void Read_CNetAccept(USHORT *pPort);
	void Read_CNetConnect(USHORT *pPort, ULONG *pIP);

private:

public:

private:

};

extern CConfigRead g_ConfigRead;