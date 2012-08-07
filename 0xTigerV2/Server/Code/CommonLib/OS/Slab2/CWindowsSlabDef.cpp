#include "stdafx.h"
#include "CWindowsSlabDef.h"
#include "CVirPageHead.h"
using namespace name_slab;

long name_slab::CalcSingleObjectHeadSize()
{
	long nUseObjectSize=0;
	if( DEBUG_SLAB_FALGS & SLAB_RED_ZONE )
	{
		nUseObjectSize += sizeof(HEAD_BAD_ALIEN_MAGIC);
	}

	nUseObjectSize += HEAD_PAGE_ADDR_SIZE;

	return nUseObjectSize;
}

long name_slab::CalcSingleObjectSize(long nUseObjectSize)
{
	nUseObjectSize += CalcSingleObjectHeadSize();

	nUseObjectSize = _ALIGN(nUseObjectSize, __ALIGN_SIZE_LONG);

	return nUseObjectSize;		
}

//���ʵ�ҳ��ͷ��ַ
VIR_PAGE_HEAD* name_slab::OffsetPageHead(void *p)
{
	//С�˻�
	long *_p = (long*) ( (long)p-HEAD_PAGE_ADDR_SIZE );
	VIR_PAGE_HEAD *pPage =(VIR_PAGE_HEAD* ) (*_p);
	if (HEAD_BAD_ALIEN_MAGIC!=pPage->m_nBadAlienMagic)
	{
		return NULL;
	}

	return pPage;
}

//���ʵ�ҳ��ħ������
unsigned int name_slab::OffsetBadMagic(void *p)
{
	//С�˻�
	return *(unsigned int*)( (long)p-HEAD_PAGE_ADDR_SIZE-sizeof(HEAD_BAD_ALIEN_MAGIC) );
}

//���ʵ�ǰCPUID
int name_slab::GetCPURunId()
{
	_asm {mov eax, 1} 
	_asm {cpuid} 
	_asm {shr ebx, 24} 
	_asm {mov eax, ebx} 
}