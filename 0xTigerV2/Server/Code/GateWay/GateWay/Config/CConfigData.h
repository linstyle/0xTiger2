/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2011/02/28                                                         
    ����˵����  ��Ϸ����Ҫʹ�õ��������ݽṹ���������ļ��г������������
				�ⲿ���ݵĸı���ı�
*/

#pragma  once

/*
	���ص�����������Ϣ
*/
struct GATEWAY_NET
{
	GATEWAY_NET();
	int nAcceptPort;			//���ص�Accept�˿�
	int nMaxConnectClient;//֧�����Ŀͻ��˸���
	int nMaxConnectChatServer;	//֧�������������������
	int nMaxConnectDataServer;	//֧������Data����������
	
};

/*
	���ص�GUID������Ϣ
*/
struct GATEWAY_GUID
{
	GATEWAY_GUID();
	unsigned int GUID_HUMAN_BEGIN;
	unsigned int GUID_HUMAN_END;

	unsigned int GUID_ITEM_BEGIN;
	unsigned int GUID_ITEM_END;

	unsigned int GUID_MONSTER_BEGIN;
	unsigned int GUID_MONSTER_END;
};