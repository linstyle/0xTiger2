/*  作者：		林东平                                                              
	创建时间：	2010/07/22                                                         
    功能说明：  本地监听网络对象
*/

#pragma once

#include "ILocalObject.h"

class CNetAccept:public ILocalObjectAccept
{
public:
	void Init();

private:
	void ReadConfig();

public:

private:

};