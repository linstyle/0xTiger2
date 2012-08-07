#include "CRoutePublic.h"


extern bool g_bQuit;

int GetCPUNumberOf()
{
	SYSTEM_INFO sinf;
	GetSystemInfo(&sinf);

	int nCPUNumberOf=0;
	CConfigManager::ReadRouteMain(&nCPUNumberOf);

	printf("Main:\n");
	printf("System CPU:%d\n", sinf.dwNumberOfProcessors);
	printf("Config CPU:%d\n", nCPUNumberOf);	

	if( nCPUNumberOf>(int)sinf.dwNumberOfProcessors )
	{
		nCPUNumberOf = sinf.dwNumberOfProcessors;
	}

	printf("So to take:%d\n", nCPUNumberOf);

	return nCPUNumberOf;
}

void GetQuitCommand()
{
	while(1)  
	{  
		if(!_kbhit())  
		/*   Use   _getch   to   throw   key   away.   */  
		{  
			int c;
			if   ((c=_getch())==0x3)     //crrl   -c   
			{				
				g_bQuit = true;
				break;
			}
		}  
	}  
}