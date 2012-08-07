/************************************************************************/
/*  作者：		林东平                                                              
	创建时间：	2010/06/17                                                         
    功能说明：  静态的读取配置信息，供全局使用
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