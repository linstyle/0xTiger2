#pragma once

#include <map> 
using namespace std;

#include "CMRole.h"
#include "Algorithm/CListOfArray.h"
/*
   管理对MROLE对象池的申请，释放，获取等工作
   所谓的分配和释放指的是MROLE的__nMRoleRunState状态.
   如果是RUN_STATE_DEAD表示空闲，否则反之
*/

/*
	有两个结构，一个是池m_MRoleList,用于对象申请和释放
	一个是MRoleMap,通过一个socket和mrole绑定
	本来不想这么做的，不过select的似乎都得这样。。那就这样了。
	需要注意的是对map操作时一些接口的返回值。比如删除，就必须返回他的键值，而MRoleList则直接删除
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