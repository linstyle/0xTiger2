/*
	@lindp lin_style@foxmail.com   
	@2012/1/24
	@��д���������
	���¶���������㣺ֻ�ǰ����ݴ�����ת�ɱ��ص���ʽ������ʲô��������
	���߼����ͨ���ö��б��֣����Ҷ�����¼�ö�٣����ɡ�
	@���� 2012/2/19
	driver�������AcceptThread,KernelThread,NetCallBack���������
	���publicҲ�Ƕ��⿪�ŵĽӿ�,���߼���ͳһ��¶��API,��ʵ���Ƿ�װ��PNLInnerNoticЭ�顣
	ֻ���Ҿ���ֱ���ṩ�������Ѻõ�
*/

#pragma  once
#include "Singleton.h"
#include "CMyStackWalker.h"

#include "CSocketClient.h"
#include "CSocketServer.h"
#include "CNetKernelThread.h"
#include "CNetAcceptThread.h"
#include "NetCallBackFun.h"
#include "PNLInnerNotic.h"

enum
{
	NET_ENUM_CONNECT,
	NET_ENUM_DISCONNECT
};
/*
	�̣߳� �����̣߳������̣߳�
	���Ӷ������
	�ڴ�ع���
	�����ʽ��
	д���������У�д�¼����У�
*/
class CNetDriver2: public Singleton<CNetDriver2>
{
public:
	CNetDriver2();
	~CNetDriver2();

	/*
		@AddSocketServer
		@����һ�������׽���

		@AddClientSocket
		@����һ��connect�׽���	
	*/
	bool AddSocketServer(const char* pName, const char* pListenIP, USHORT nListenPort);	
	bool AddClientSocket(const char* pConnectIP, USHORT nConnectPort);

	/*
		@NoticNetErr
		@֪ͨ����㣬�߼����д�����
		@pNetObject:����������ǵ������accept��һ���׽���ʱ����֪ͨ�߼���ĸ�������
	*/
	bool NoticNetErr(void *pNetObject);

	/*
		@GetPacketStream
		@�Ӷ����л�ȡһ�������
		@pNetObject:����������ǵ������accept��һ���׽���ʱ����֪ͨ�߼���ĸ�������
	*/
	int GetPacketStream(char *pBuffer, int nBufferLen);
	int PutPacketStream(const char *pBuffer, int nBufferLen);

private:
	/*
		��ʼ�����ͷ�
	*/
	void Init();
	void Release();
	void InitSocketLib();	
	void ReleaseSocketLib();
	void ReleaseAllConnect();

public:

private:
	CNetAcceptThread m_NetAcceptThread;
	CNetKernelThread m_NetKernelThread;

};

#define g_NetDriver2 CNetDriver2::getSingleton()