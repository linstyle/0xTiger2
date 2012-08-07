/*
	@lindp lin_style@foxmail.com   
	@2012/1/29
	@��������ع��������߳�
*/
#include "CIOCP.h"
#include "CSocketServer.h"
#include "CSocketClient.h"


class CNetAcceptThread
{
public:
	CNetAcceptThread();
	~CNetAcceptThread();
	
	/*
		AddSocketServer����˳��һ��Ҫ��Init֮ǰ��Ҳ���Զ�̬�ĵ��á�
		�ڲ�ʵ����һ�����飬������ȴ洢��ֵ��Ȼ��ı������±꣬�Թ�����һ�������ȡ��
	*/
	void Init(CIOCP *pIOCP);
	bool AddSocketServer(const char* pName, const char* pListenIP, USHORT nListenPort);

	bool IOCPPostConnect(CSocketClient *pSocketClient);

	CSocketServer* GetSocketServerByIndex(int nIndex);
	
private:
	static unsigned int WINAPI ThreadAccept(void* pParam);

	void Release();

	void InitThread();	
	void ReleaseThread();
	
	bool InitSocketTCPServer(CSocketServer *pSocketServer);
	bool InitAccpetExlpfn(CSocketServer *pSocketServer);

public:

private:
	//�߳�
	volatile bool m_bThreadRun;
	HANDLE m_hThreadAccept;
	unsigned int   m_uThreadAccept;

	CSocketServer m_SocketServer[SOCKET_SERVER_COUNT];
	volatile int m_nSocketServerCount;

	//iocp,�ⲿ��ʼ��
	CIOCP *m_pIOCP;
};
