/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2011/02/28                                                         
    ����˵����  ��Ϸ����Ҫʹ�õ��������ݽṹ���������ļ��г������������
				�ⲿ���ݵĸı���ı�
*/

#pragma  once

/*
	DataServer������������Ϣ
*/
struct DATA_SERVER_NET
{
	DATA_SERVER_NET();
	~DATA_SERVER_NET();

	int nGateWayCount;				//��Ҫ���ӵ�������
	unsigned long *pGateWayIP;		//IP
	int *pGateWayPort;				//�˿�
	int nAcceptPort;				//���ص�Accept�˿�
};

/*
	���ص�GUID������Ϣ
*/
struct DATA_SERVER_GUID
{
	DATA_SERVER_GUID();
	unsigned int GUID_HUMAN_BEGIN;
	unsigned int GUID_HUMAN_END;

	unsigned int GUID_ITEM_BEGIN;
	unsigned int GUID_ITEM_END;

	unsigned int GUID_MONSTER_BEGIN;
	unsigned int GUID_MONSTER_END;
};