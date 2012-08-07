#include "StdAfx.h"
#include "CCmInitPackets.h"

initialiseSingleton(CCmInitPackets);

CCmInitPackets::CCmInitPackets()
{
	new PNLInnerNoticObject;   //�ڲ�Э��
	new PLoginGLObject;               //��½��
}


CCmInitPackets::~CCmInitPackets()
{
	delete PNLInnerNoticObject::getSingletonPtr();
	delete PLoginGLObject::getSingletonPtr();
}