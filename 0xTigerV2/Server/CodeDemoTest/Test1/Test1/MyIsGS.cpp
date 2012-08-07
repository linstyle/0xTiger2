#include "stdafx.h"
#include "MyIsGS.h"

#include "NetAPI.h"
#include "CLog2.0.h"

CMyIsGS::CMyIsGS()
{
	Init();
}

void CMyIsGS::Init()
{


}

//发起一次连接
void CMyIsGS::Connect()
{
	IF( false==net::AddClientSocket("127.0.0.1", 9527) )
	{

	}
}

//关闭连接
void CMyIsGS::Close()
{

}
