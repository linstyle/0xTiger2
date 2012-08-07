/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/02/14                                                         
    ����˵����  ���ص��׽��ִ���Ŀǰ����Accept,Connect
*/

#pragma once

#include "GlobalType.h"
#include "CIOCP.h"
#include "CNetObject.h"

class CSocketAccept
{
public:
	CSocketAccept();
	~CSocketAccept();

	void Init();
	void TracerMe();

	void Run();

	void AddLocalObjectConnect(ILocalObjectConnect* pLocalObject);
	void AddLocalObjectAccept(ILocalObjectAccept* pLocalObject);

private:
	void FlushConnect();
	void _FlushConnect(int nIndex);
	

public:

private:
	std::vector<ILocalObjectAccept*> m_LocalObjectAccept;
	

	bool m_bThreadRun;
};
