#pragma once
#include <windows.h>
/*
  管理转发的后台服务器
*/

namespace name_servers_manager
{
	//能控制的最大转发服务器数，包括bin和dpc或者其他等
	const int SERVER_BIN_NUMBER_OF = 3;
	const int SERVER_DPC_NUMBER_OF = 1;

	const int LEVEL_BIN = 1;
	const int LEVEL_DPC = 2;
};
/*
   用户数据->server->bin 
   server保存场景数组，以及一个nIdentification
   用户登录成功后，携带场景索引和nIdentification

   转发的步骤：
   收到用户发送的数据后，直接定位到索引，比对nIdentification是否一致


   bin->sever->用户数据
   从server到bin时夹带用户套接字，ip, port，

   bin返回时，这些信息原样返回。验证套接字是否一致。

*/
struct SERVER_INFO
{
	SERVER_INFO()
	{
		bEnable = false;
	}

	int nSocket;
	unsigned long nIP;
	int nPort;
	int nIdentification;		//场景标识，以时间为数

	bool bEnable;
};


class CServersManager
{
public:

private:
	SERVER_INFO ServerInfo[name_servers_manager::SERVER_DPC_NUMBER_OF+
							  name_servers_manager::SERVER_BIN_NUMBER_OF];

public:
	CServersManager();

	bool IsExisted(const int nBinIdenti);
	SERVER_INFO* GetServerInfo(int nIndex);

	void DisableServerInfo(int nIndex);
	void EnableServerInfo(int nIndex);

private:


};
