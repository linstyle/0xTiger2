/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/07/21                                                         
    ����˵����  �����
*/
#include <stdlib.h>

int Random(double start, double end)
{
	return (int)(start+(end-start)*rand()/(RAND_MAX + 1.0));
}