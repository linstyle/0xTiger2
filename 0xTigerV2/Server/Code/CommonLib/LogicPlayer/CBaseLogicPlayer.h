/*
	@lindp lin_style@foxmail.com   
	@2012/3/22
	@�߼������Ļ����࣬ά����һЩidʲô�ġ�
*/
#pragma once
#include <WTypes.h>
class CBaseLogicPlayer
{
public:
	CBaseLogicPlayer();
	~CBaseLogicPlayer();

	INT64 GetUserID();
	void SetUserID(INT64 nUserID);

private:

public:
	
private:
	INT64 m_nUserID;
};