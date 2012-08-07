#pragma once

#include "CMRole.h"
#include <hash_map>

#define   _DEFINE_DEPRECATED_HASH_CLASSES   0  
using   namespace   stdext;
/*
	������Դ��CGlobalResMRole�У�����ֻ�Ǵ洢MROLE��Դ��ַ��һ������
*/
namespace name_mrole_manager
{
	const int MAX_ELEMENT = 1000;		//������1000��
};



class CMRoleManager
{
public:
	
	
private:	
	hash_map<CMRole*, CMRole*> m_UserList;
	typedef hash_map<CMRole*, CMRole*>::iterator IterMap_t;	

	int nMRoleMaxElement;

public:
	CMRoleManager();
	~CMRoleManager();
	void Init();
	void CallBackTracerMe();

	/*
		���ŵĽӿڣ�����ɾ����ѯ
		MRoleAdd:��GlobalResMRole����һ����Դ�����Ҽ�¼����ָ���ַ�洢��������
		MRoleErase:���ر�ɾ����ָ�룬�Թ�����ֱ�ӵ���.�ṩnFrom...����ָʾ�Ƿ��ȫ����Դ���ͷ�
	*/
	CMRole* MRoleAdd();
	CMRole* MRoleErase(CMRole *pMRole, int nFromGlobalResMRole=0);

	int GetMRoleSumUse();
	int GetMRoleSumFree();

private:
	/*
		void CounterTick(int nAddOrErase)
		�������Ӽ�
		0 ����MROLE
		1 �ͷ�MROLE
	*/

};