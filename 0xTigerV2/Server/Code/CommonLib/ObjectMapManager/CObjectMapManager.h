/*
	@lindp lin_style@foxmail.com   
	@2012/2/28
	@�����������ӡ�
	    ����һ��GS��½����������ӽӿ�SendByGS�������һ�Զ�ķ��ͣ���
	   SendByRole�ȡ�

   @2012/3/22����
   ����ȷ����Ϊ�����ת�Ӳ㡣
   ά���� userid->NetObject, userid->LogicPlayer
   ����ʱ����userid�ҵ�NetObject,
   �հ�ʱ����userid�ҵ�LogicPlayer
   ����������������׽������Ӳ�ѯ
*/
#include "Singleton.h"
#include "CMyStackWalker.h"
#include "IPackets.h"
#include "CBaseLogicPlayer.h"
#include <map>

using namespace std;

namespace name_objectmap
{
	struct OBJECT_VALUE
	{
		OBJECT_VALUE(void* pNetObject, CBaseLogicPlayer* pBaseLogicPlayer)
		{
			m_pNetObject=pNetObject;
			m_pBaseLogicPlayer=pBaseLogicPlayer;
		}

		OBJECT_VALUE()
		{
			m_pNetObject=NULL;
			m_pBaseLogicPlayer=NULL;
		}
		void* m_pNetObject;
		CBaseLogicPlayer* m_pBaseLogicPlayer;
	};

	enum IDENT
	{
		GS=0,
		HS=1,
		LS=2
	};

/*
	���к���ʱ��ô��
	1-100:gs
	101-200:hs
	201-300:ls
	300-1000:����
	1001-xxxxxxxx:player
*/
	bool IsGS(INT64 nUserID);
	bool IsLG(INT64 nUserID);
	bool IsHS(INT64 nUserID); 
};

class CObjectMapManager: public Singleton<CObjectMapManager>
{
public:
	CObjectMapManager();

	/*
		�����playerָ��ͨ�Ŀͻ�������
	*/
	void AddPlayer(INT64 nUserID, void *pNetObject, CBaseLogicPlayer* pBaseLogicPlayer);
	CBaseLogicPlayer* GetPlayerByUserID();
	void* GetNetObjectByUserID();

	void SendByUser(INT64 nUserID, const char* pBuffer, int nBufferLen);
	void CloseByUser(INT64 nUserID);

	//��Ȩ
	bool ChangeIdent(INT64 nUserID, IDENT nIdent);
	
	/*
		����ʹ�ã�Ҳ���Գ����һЩ�߼��ӿ�
	*/
	void SendToLS(const char *pBuffer, int nBufferLen);


	//void TracerMe();
private:
	name_objectmap::OBJECT_VALUE* GetObjectValueByUserID(INT64 nUserID);
	bool VerifyUserValid(INT64 nUserID);
	//������С��ȷ��
	bool VerifySendPacket(const IPackHead *pPackHead, int nBufferLen);
	int PutPacketStream(const char *pBuffer,  int nBufferLen, void *pNetObject);

public:

private:
	typedef map<INT64,  name_objectmap::OBJECT_VALUE*> MAP_USERID_OBJECT;

	MAP_USERID_OBJECT m_mapUserIDObject;
};

#define g_NetObjectManager CObjectMapManager::getSingleton()