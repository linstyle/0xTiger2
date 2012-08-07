#include "CMRoleHead.h"

CMRoleHead::CMRoleHead()
{
	Init();	
}


bool CMRoleHead::Init()
{
	bActiveTime = __nMRoleLevel = 0;

	__nMRoleRunState = name_mrole_head::RUN_STATE_DEAD;

	return true;
}