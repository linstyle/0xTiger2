#pragma once

#include "CMRole.h"
#include <hash_map>

#define   _DEFINE_DEPRECATED_HASH_CLASSES   0  
using   namespace   stdext;
/*
	真正资源在CGlobalResMRole中，这里只是存储MROLE资源地址的一个链表
*/
namespace name_mrole_manager
{
	const int MAX_ELEMENT = 1000;		//单场景1000个
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
		开放的接口：增，删，查询
		MRoleAdd:向GlobalResMRole申请一个资源，并且记录它的指针地址存储到链表里
		MRoleErase:返回被删除的指针，以供场景直接调用.提供nFrom...参数指示是否从全局资源中释放
	*/
	CMRole* MRoleAdd();
	CMRole* MRoleErase(CMRole *pMRole, int nFromGlobalResMRole=0);

	int GetMRoleSumUse();
	int GetMRoleSumFree();

private:
	/*
		void CounterTick(int nAddOrErase)
		计数器加减
		0 增加MROLE
		1 释放MROLE
	*/

};