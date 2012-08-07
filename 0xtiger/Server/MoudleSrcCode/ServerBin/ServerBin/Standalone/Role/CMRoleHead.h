#pragma once
#include "Algorithm/CListOfArray.h"
/*
	�ṩ�������򲿼���һЩ��Դ����Ҫ�Ķ�����Ϣ
*/
namespace name_mrole_head
{
	const int IDENTI_NORMAL = 0;
	const int IDENTI_BIN = 1;
	const int IDENTI_OTHER = 2;

	const int RUN_STATE_DEAD  = -1;   //��Ч��������
	const int RUN_STATE_ENTER = 0;	  //��������
	const int RUN_STATE_DOING = 1;	  //�Ѿ���½��������
};

/*
	���ʾַ������ϵļ�¼��Ϣ
*/
struct IN_POSTOFFICE
{
	int nWherePostoffice;			//�ĸ�����
	int nSocket;					//�������ϵ��׽���ֵ
	int nResIdenti;					//�ڸ������ϵ���Դ���
};

/*
	��dpc�������ϵļ�¼��Ϣ
*/
struct IN_DPC
{
	int nResIdenti;					//��DPC�������ϵ���Դ���
};

/*
	��CGlobalResMRole�ϵļ�¼��Ϣ
*/
struct IN_GLOBALRES_MROLE
{
	int nResIdenti;					//��Global�ϵ���Դ���
};

/*
	��CMRoleManger,ָ�������еļ�¼��Ϣ
*/
struct IN_CMROLEMANAGER
{
	int nResIdenti;
};

/*
	���ĸ���������Ϣ
*/
struct IN_SCENE
{
	int nWhereIdenti;
};

class CMRoleHead
{
public:
	IN_DPC				InDpc;
	IN_POSTOFFICE		InPostoffice;
	IN_GLOBALRES_MROLE  InGlobalResMRole;
	IN_CMROLEMANAGER	InMRoleManager;
	IN_SCENE			InScene;

	unsigned long bActiveTime;
	
private:
	//
	//namespace name_mrole_head
	int __nMRoleLevel;
	int __nMRoleRunState;

public:
	CMRoleHead();

	bool Init();

	void SetMRoleLevel(int nLevel)
	{
		__nMRoleLevel = nLevel;
	}

	int GetMRoleLevel()
	{
		return __nMRoleLevel;
	}

	void SetMRoleRunState(int nState)
	{
		__nMRoleRunState = nState;
	}

	int GetMRoleRunState()
	{
		return __nMRoleRunState;
	}

private:

};