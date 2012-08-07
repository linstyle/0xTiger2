#include "CMRole.h"


CMRole::CMRole()
{

}

int CMRole::Close()
{
	if( name_mrole_head::RUN_STATE_DEAD==MRoleHead.GetMRoleRunState() )
	{		
		printf("Err, __nMRoleFlow has equal 'FLOW_DEAD' \n");
	}

	MRoleHead.SetMRoleRunState( name_mrole_head::RUN_STATE_DEAD );
	printf("Warning, CMRole Close \n");	

	return 0;
}

int CMRole::Open()
{
	if( name_mrole_head::RUN_STATE_DEAD!=MRoleHead.GetMRoleRunState() )
	{		
		printf("Err, __nMRoleFlow has don't equal 'FLOW_DEAD' \n");
	}

	MRoleHead.SetMRoleRunState( name_mrole_head::RUN_STATE_ENTER );	
	printf("Warning, CMRole Open\n");

	return 0;
}