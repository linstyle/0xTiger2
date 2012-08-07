#include "CClientPlayPublic.h"

extern volatile bool g_bQuit;

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