#pragma once

#include <map> 
using namespace std;

#include "CMRole.h"
#include "Algorithm/CListOfArray.h"
/*
   �����MROLE����ص����룬�ͷţ���ȡ�ȹ���
   ��ν�ķ�����ͷ�ָ����MROLE��__nMRoleRunState״̬.
   �����RUN_STATE_DEAD��ʾ���У�����֮
*/

/*
	�������ṹ��һ���ǳ�m_MRoleList,���ڶ���������ͷ�
	һ����MRoleMap,ͨ��һ��socket��mrole��
	����������ô���ģ�����select���ƺ��������������Ǿ������ˡ�
	��Ҫע����Ƕ�map����ʱһЩ�ӿڵķ���ֵ������ɾ�����ͱ��뷵�����ļ�ֵ����MRoleList��ֱ��ɾ��
*/

class CMRoleManager
{
public:	
	typedef CListOfArray<CMRole, 0, true>::ELEMENT Element_t;
	CListOfArray<CMRole, 0, true> m_MRoleList;

private:
	map<int, CMRole*> MRoleMap;
	typedef map<int, CMRole*>::iterator IterMap_t;

	const int m_nMRoleMaxElement;
public:
	CMRoleManager();
	~CMRoleManager();

	bool Init();

	CMRole* MRoleAdd( int nNetKey );
	void MRoleErase(int nNetKey);
	//Element_t* MRoleErase(CMRole* pMRole, int nNetKey);
	CMRole* GetMRoleByNetKey( int nNetKey);
	
	int GetMRoleSumUse();
	int GetMRoleSumFree();

private:
	CMRole* AddToMRoleSet();
	void EraseFromMRoleSet(CMRole* pMRole);

	void AddToMRoleMap(int nNetKey, CMRole* pMRole);
	CMRole* EraseFromMRoleMap(int nNetKey);
	

};