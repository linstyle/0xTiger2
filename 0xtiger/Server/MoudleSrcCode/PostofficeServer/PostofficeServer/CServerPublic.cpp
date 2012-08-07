#include "CServerPublic.h"

extern volatile bool g_bQuit;

int GetCPUNumberOf()
{
	SYSTEM_INFO sinf;
	GetSystemInfo(&sinf);

	int nCPUNumberOf=0;

	nCPUNumberOf = sinf.dwNumberOfProcessors;

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