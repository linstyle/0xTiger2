/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/12/25                                                       
    ����˵����  ��ʼ��Э��
*/
#pragma once
#include "Singleton.h"

#include "../Packets/Accept.h"
#include "../Packets/Exception.h"
#include "DemoPFileTrans.h"

class CInitPackets:public Singleton<CInitPackets>
{
public:
	CInitPackets();
	~CInitPackets();

	void InitPackets();
	void DeletePackets();

private:

public:

private:

};