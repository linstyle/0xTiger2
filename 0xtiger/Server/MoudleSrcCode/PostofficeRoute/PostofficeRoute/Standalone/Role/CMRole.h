#pragma once

#include "CMRoleHead.h"
#include "../CRouteRand.h"

/*
	�ṩ��һ������ı�ʾ���������Open��Close.
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

