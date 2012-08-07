/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/12/25                                                       
    ����˵����  �����������ڹ���
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
		����������
	*/
	void InitCommonLib();
	void DeleteCommonLib();

	/*
		��־
	*/
	void InitLog();
	void DeleteLog();
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