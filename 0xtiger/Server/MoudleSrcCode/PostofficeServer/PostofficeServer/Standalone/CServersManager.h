#pragma once
#include <windows.h>
/*
  ����ת���ĺ�̨������
*/

namespace name_servers_manager
{
	//�ܿ��Ƶ����ת����������������bin��dpc����������
	const int SERVER_BIN_NUMBER_OF = 3;
	const int SERVER_DPC_NUMBER_OF = 1;

	const int LEVEL_BIN = 1;
	const int LEVEL_DPC = 2;
};
/*
   �û�����->server->bin 
   server���泡�����飬�Լ�һ��nIdentification
   �û���¼�ɹ���Я������������nIdentification

   ת���Ĳ��裺
   �յ��û����͵����ݺ�ֱ�Ӷ�λ���������ȶ�nIdentification�Ƿ�һ��


   bin->sever->�û�����
   ��server��binʱ�д��û��׽��֣�ip, port��

   bin����ʱ����Щ��Ϣԭ�����ء���֤�׽����Ƿ�һ�¡�

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
	int nIdentification;		//������ʶ����ʱ��Ϊ��

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
