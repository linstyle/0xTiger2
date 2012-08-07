#pragma once

#include "CMRoleHead.h"
#include "../CRouteRand.h"

/*
	提供了一个整体的表示。必须的是Open和Close.
*/

class CMRole
{
public:	
	CMRoleHead MRoleHead;
	SERVER_INFO *pServerUpdate;
	
private:

public:	
	CMRole();

	int Open();
	int Close();

private:

};

