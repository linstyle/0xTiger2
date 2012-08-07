/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/07/14                                                         
    ����˵����  ��Ҫ�������򽻵����׽��֣�Ȼ��ת���߼��׽���
				Physical����ʵ�����������򽻵��Ķ�����API���������ӣ�recv,send
				�����׽����Ѿ�������֮����ô����Ӧ�ò���ֻ�Ƕ��仺�����е�����
				���д�ȡ��Ȼ��������ݵ����ݽ�������������������������ˡ�
				��Ϊ���Ⱪ¶����Physical�Ľӿڣ�����Physical������һЩ�����ϵĽӿڡ�
				��ȻҲ���Ե���дһ�����ƹ���Ķ���

*/

/*
			SendFlush / del/add(gc+-)
	PhysicalSocket	---RecvFlush(�൱GetIOCP)(gc) del/add(gc+-)
		
	LogicSocket		--RecvFlush(gc) del/add(gc+-)
					--ExceptionFlush
		
*/

#pragma once

#include <vector>

#include "GlobalType.h"
#include "Singleton.h"
#include "CIOCP.h"
#include "ILocalObject.h"
#include "CSocketLogic.h"
#include "CNetTracer.h"

#include "CPacketFactory.h"
#include "CSlab.h"

#include "OSOther.h"


/*
	��������ն˹�������
*/

class CSocketPhysical;
struct THREAD_PARAM
{
	CSocketPhysical *pSocketPhysical;
	int i;	
};

namespace name_socket_physical
{
	struct THREAD_PARAM_ACCPET
	{
		bool *pRun;
		CSocketPhysical *pSocketPhysical;
		ILocalObjectAccept *pObjectAccept;
	};

	struct THREAD_PARAM_CONNECT
	{
		bool *pRun;
		CSocketPhysical *pSocketPhysical;
	};
};

/*
	ִ��˳��
	AddLocalObjectConnect, AddLocalObjectAccept,�����׽��ֵ����
	Fire(),IOCP���߳̿�ʼ����
	Run(),ʱ��Ƭ���нӿڿ�������һ���߳���ִ�У�Ҳ�������̵߳���
*/
class CSocketPhysical
{
public:
	CSocketPhysical();
	~CSocketPhysical();

	void TracerMe();
	void Run();

	void AddLocalObjectConnect(ILocalObjectConnect* pLocalObject);
	void AddLocalObjectAccept(ILocalObjectAccept* pLocalObject);
	void Fire();	

	/*
		connect,accept�̵߳���
	*/
	void DelIOCPRecv(CIOCPData* pIOCPKey, bool bException=false);
	
private: 
	/*
		���ա����ӵ��߳�
	*/
	static unsigned int WINAPI ProcAccept(void* param);
	static unsigned int WINAPI ProcConnect(void* param);
	std::vector<HANDLE> m_hThreadAccept;
	std::vector<HANDLE> m_hThreadConnect;

	/*
		�߳������͹ر�
	*/
	bool StartIOCP();
	bool StartThreadAccept();
	bool StartThreadConnect();
	void EndThreadAccept();
	void EndThreadConnect();

	/*
		���쳣�׽��ֵĴ���
	*/
	void FlushException();
	
	/*
		Recv�߳�(����)ִ�еĶ���
		FramsStatus��ʱ��ȡ�������������Ϊ��ȡ��ֹͣ
	*/
	void RunStatus();
	bool FramStatus();
	void AcceptConnect(CIOCPData* pIOCPKey);
	
	/*
		�����AddIOCPRecvָ��������ɶ˿�GetStatus�Ķ�������Accept,Connect,WSARecv
		����WSARecv�Դ���post�Ķ����������øú���
	*/
	int AddIOCPRecv(CIOCPData* pIOCPKey);
	
	/*
		���󻺳�ص�һ����װ
	*/
	CIOCPData* MallocNetObject();
	void FreeNetObject(CIOCPData* p);

	/*
		Close
	*/
	void CloseSocket(CIOCPData* pIOCPKey);
	int  CloseLocalObject(CIOCPData* pIOCPKey);
	void CloseAllSocket();

public:
	CIOCP m_IOCP;

private:
	CSocketLogic m_SocketLogic;

	/*
		��ű��ص�����
	*/
	std::vector<ILocalObjectAccept*> m_LocalObjectAccept;
	std::vector<ILocalObjectConnect*> m_LocalObjectConnect;

	bool m_bThreadRun;
};

