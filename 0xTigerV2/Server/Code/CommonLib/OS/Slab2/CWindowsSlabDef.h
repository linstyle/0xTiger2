#pragma  once

//lindp
//2010.7.17 2:51

/*
	CONFIG_SLAB_DEBUG	:�ܿ���
	DEBUG_DEFAULT_FALGS :��Ҫ���ٵľ���DEBUG��ǩ
*/
#define CONFIG_SLAB_DEBUG


#ifdef CONFIG_SLAB_DEBUG

	#define DEBUG_SLAB_FALGS (SLAB_RED_ZONE | SLAB_CPU_RUN_ID | SLAB_GC_PARTIAL )

#else
	
	#define DEBUG_DEFAULT_FALGS 0

#endif 

/*
	��Ҫ���Ե�DEBUG��ǩ������˳��Ϊ
	0x1,0x2,0x4,0x8
	0x10,0x20,0x40,0x80
	0x100,0x200,0x300,0x400
	...
*/
#define SLAB_RED_ZONE 0x0			//0x1	�����������
#define SLAB_CPU_RUN_ID 0x0		//0x2	�������CPU����,��������֤�л�ʱ����ʹ���ϲ���������ҳ����Ҫ��ˢ
#define SLAB_GC_PARTIAL 0x0			//0x4	��������ҳ�����

//  |red|haed address|[list]content|
/*
	���ñ���
*/
struct VIR_PAGE_HEAD;
namespace name_slab
{
	//kmem�������Ĵ�С,��λbyte.��С4byte,��Ҫ�Ļ�������������ӡ�
	const int KmemMallocByte[]=
	{8,16,32,64,128,512,1024, 2048,8192,16384,32768};

	//��������ħ������
	const unsigned long HEAD_BAD_ALIEN_MAGIC = 0x01020304;

	//Ԥ����page��ַ��С
	const long HEAD_PAGE_ADDR_SIZE = sizeof(VIR_PAGE_HEAD*);

	//partialҪ������ҳ�������ò������Ե���
	const int FREE_KEEP_PARTIAL=30;

	//�������ͷ��С
	long CalcSingleObjectHeadSize();
	//��������С
	long CalcSingleObjectSize(long nUseObjectSize);

	//���ʵ�ҳ��ͷ��ַ
	VIR_PAGE_HEAD* OffsetPageHead(void *p);

	//���ʵ�ҳ��ħ������
	unsigned int OffsetBadMagic(void *p);

	//���ʵ�ǰCPUID
	int GetCPURunId();
};


