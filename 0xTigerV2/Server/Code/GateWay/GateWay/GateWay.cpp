// GateWay.cpp : �������̨Ӧ�ó������ڵ㡣
//
/*
	1������ѹ������ѹ
	2��������ȷ��У��
	
	1��ά��һ������ͼ������һЩ��Ϣ���ͻ��˰��Դ���gateway��ά���ģ�֪��
		 �ͻ��˵İ�Ҫ�����Ǹ��߼���������

		  �ͻ���1->�߼�������
		  �ͻ���2->�߼�������
		  �ͻ���3->�߼�������
*/

#include "StdAfx.h"
#include <vld.h>
#include "CMaster.h"
#include "CSlab.h"

#include <vector>

using namespace std;

volatile bool g_bQuit=false;


int _tmain(int argc, _TCHAR* argv[])
{
	printf("GateWayServer Start\n");
	new CMaster;


	while( false==g_bQuit)
	{
		g_Master.Loop();
		Sleep(100);
	}


	printf("GateWayServer Stopping.....\n");
	delete CMaster::getSingletonPtr();
	printf("GateWayServer End\n");
	system("pause");
	return 0;
}

