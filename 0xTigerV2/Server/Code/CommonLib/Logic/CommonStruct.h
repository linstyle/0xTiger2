/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2011/1/19                                                         
    ����˵����  commonlib���һЩ�����ṹ��
*/

//#include "CNetObject.h"
/*
	�����Ͷ�ŵ�����Ľṹ
	����޸ģ�ע��PPutTaskQueueObject::Execute�Ŀ�������
*/

struct NET_TASK_QUEUE
{
	void* pPlayLogic;
	void* pPlayNet;
	int GetPackHeadOffset()
	{
		return sizeof(void*)+sizeof(void*);
	}
	/*
		IPackHead* pPackHead
	*/
};