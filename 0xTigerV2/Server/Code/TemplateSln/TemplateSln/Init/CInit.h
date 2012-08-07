/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/12/25                                                       
    ����˵����  ��ʼ������
*/

#pragma once
#include "Singleton.h"
#include "CCommonLibInit.h"
#include "CInitPackets.h"

#include "../Logic/Role/CRoleAllocator.h"



class CInit:public Singleton<CInit>
{
public:
	CInit();
	~CInit();

	/*
		�������ʼ��
	*/
	void InitCommonLib();
	void DeleteCommonLib();

	/*
		Э���
	*/
	void InitPackets();
	void DeletePackets();

	/*
		�����������
	*/
	void InitRoleAllocator();
	void DeleteRoleAllocator();
private:

public:

private:

};