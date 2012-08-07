#pragma once
/*
������ȡ���������
*/

/*
Rand��Ҫά����һ��int���������������ⲿ������Ҫ�������Ϣ��
��ˣ��ⲿ���ݽṹ�ﱣ�����ṩ��rand��int���鼴��.���ң�SERVER_INFO���������
���־�̬���䣬������rand�ҵ�intʱ������ֱ�Ӹ��ݵ�ǰ������λ��
*/
#include "../stdafx.h"
#include "../CConfigManager.h"

namespace name_route_rand
{
	//
	//���֧�ֵ��ʾַ�������������Ϊ��̬����.Ī����64��	
	const int PEOPLE_PRICISION_PROPORTION = 1000;
};

//
//�ⲿ��Ҫ����Ϣ�ṹ
//����Ľṹ�����ݺ���������CRouteServerTCP�б���һ�£�����Ϊ��Ӧ��ϵ
struct SERVER_INFO
{
	SERVER_INFO()
	{	
		nEnable = false;
		nSocket = nPort = nIP = nSumPeople = 0;		
	}
	bool nEnable;
	int nPort;
	unsigned long nIP;		//TCP/IP network byte order
	int nSumPeople;			//CRouteRand�����Ҫ��

	//
	//debug
	int nSocket;			//�ж��Ƿ��ж����ĺۼ�
};

class CRouteRand
{
public:
	int *m_pServerSelectRecord;
	SERVER_INFO *m_pServerInfo;

private:	
	int nSumServerPeople;
	int nMaxServerPeople;			//was read from config
	int *m_pServerProportion;
	int *m_pServerProportionOffset;
	
public:
	CRouteRand();
	~CRouteRand();

	bool Init();

	void CtrlProportion();
	const SERVER_INFO* GetRandObject();
	SERVER_INFO* GetServerObject(int nIndex);
	
	void EnableServerInfo(int i)
	{
		m_pServerInfo[i].nSumPeople = 0;
	}
	void DisableServerInfo(int i)
	{
		m_pServerInfo[i].nSumPeople = 0;	
	}


private:
	//
	//Debug Tracer
	void TracerMe();
	//
	//Init
	void ReadFromConfigManager();	

//debug
public:
	void TracerMe_All();
};