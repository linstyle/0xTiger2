/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/07/29                                                         
    ����˵����  ����ȫ���˳��߳�
*/

#include "Singleton.h"
#include "OSOther.h"
#include "MTASSERT.h"

class CThreadQuit:public Singleton<CThreadQuit>
{
public:
	CThreadQuit();
	~CThreadQuit();


private:
	void Init();

	static unsigned int WINAPI ThreadProc(void* pParam);


public:

private:
	HANDLE m_hThread;
	unsigned int   m_uThread;
};

#define g_ThreadQuit CThreadQuit::getSingleton()

