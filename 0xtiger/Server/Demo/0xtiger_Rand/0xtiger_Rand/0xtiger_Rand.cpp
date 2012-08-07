// 0xtiger_Rand.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//
//���ԵĴ���
const int TEST_COUNT = 12000;
//
//������̨��
const int SERVER_NUMBER_OF = 5;
//
//��������̨�������
const int SERVER_PEOPLE_SIZE_MAX = 2500;
//
//
const int PEOPLE_PRICISION_PROPORTION = 1000;
//
//������
int ServerSumPeople=0;
//
//��������Ϣ�ṹ��
int ServerInfo[SERVER_NUMBER_OF];
//
//�����������ı������
int ServerProportion[SERVER_NUMBER_OF];
//
//��������������������ʵ�ƫ��ֵ
int ServerProportionOffset[SERVER_NUMBER_OF];
//
//��¼��ѡ�˶��ٴ�
int ServerSelectRecord[SERVER_NUMBER_OF];

void Tracer_ServerSelectRecord()
{
	cout<<"server select record"<<endl;

	for(int i=0; i<SERVER_NUMBER_OF; ++i)
	{
		cout<<"num "<<i<<":"<<ServerSelectRecord[i]<<endl;
	}

	cout<<"*************end*************"<<endl<<endl;
}

void Tracer_ServerInfo()
{
	cout<<"server pepole"<<endl;

	cout<<"now sum people:"<<ServerSumPeople<<endl;

	cout<<"max people size of a server:"<<SERVER_PEOPLE_SIZE_MAX<<endl;

	for(int i=0; i<SERVER_NUMBER_OF; ++i)
	{
		cout<<"num "<<i<<":"<<ServerInfo[i]<<endl;
	}

	cout<<"*************end*************"<<endl<<endl;
}

void Tracer_ServerProportion()
{
	int i;
	cout<<"server Proportion"<<endl;

	cout<<"max people_pricision_proportion:"<<PEOPLE_PRICISION_PROPORTION<<endl;

	for(i=0; i<SERVER_NUMBER_OF; ++i)
	{
		cout<<"num "<<i<<":"<<ServerProportion[i]<<endl;
	}

	cout<<"max people_pricision_proportion offset:"<<endl;
	for(i=0; i<SERVER_NUMBER_OF; ++i)
	{
		cout<<"num "<<i<<":"<<ServerProportionOffset[i]<<endl;
	}

	cout<<"*************end*************"<<endl<<endl;	
}

void InitServerInfo()
{
	ServerInfo[0] = 1;
	ServerInfo[1] = 2;
	ServerInfo[2] = 500;
	ServerInfo[3] = 0;
	ServerInfo[4] = 0;

	int i;
	for(i=0; i<SERVER_NUMBER_OF; ++i)
	{
		ServerSumPeople+=ServerInfo[i];
	}
}

//
//������� 
void CtrlProportion()
{
	int i;
	int nSumServerProportion=0;
	double d;
	
	for(i=0; i<SERVER_NUMBER_OF; ++i)
	{ 		
		//
		//�ж��Ƿ񳬳���̨����
		if( SERVER_PEOPLE_SIZE_MAX<ServerInfo[i] )
		{
			ServerProportion[i] = 0;
		}
		else
		{				
			ServerProportion[i] = (SERVER_PEOPLE_SIZE_MAX-ServerInfo[i]) / (double)SERVER_PEOPLE_SIZE_MAX * PEOPLE_PRICISION_PROPORTION;		
		}

		nSumServerProportion += ServerProportion[i];
	}

	for(i=0; i<SERVER_NUMBER_OF; ++i)
	{		
		ServerProportion[i] = ServerProportion[i] / (double)nSumServerProportion * PEOPLE_PRICISION_PROPORTION;
	}

	ServerProportionOffset[0]=ServerProportion[0];
	for(i=1; i<SERVER_NUMBER_OF; ++i)
	{
		ServerProportionOffset[i] = ServerProportionOffset[i-1]+ServerProportion[i];
	}

}
 
int GetRandObject(int nRandBase)
{
	for(int i=0; i<SERVER_NUMBER_OF; ++i)
	{
		int nBegin = ServerProportionOffset[i] - ServerProportion[i];
		int nEnd = ServerProportionOffset[i];
		if( nRandBase>=nBegin&& nRandBase<nEnd )
		{
			return i;
		}
	}

	return SERVER_NUMBER_OF-1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand( (unsigned)time( NULL ) );
	InitServerInfo();
	CtrlProportion();

	Tracer_ServerInfo();
	Tracer_ServerProportion();

	int i;
	for(i=0; i<TEST_COUNT; ++i)
	{
		int nRecord;
		//
		//rand 0-32767
		nRecord = GetRandObject( rand()%PEOPLE_PRICISION_PROPORTION );
		ServerSelectRecord[nRecord]++;
		ServerInfo[nRecord]++;
		ServerSumPeople++;

		//CtrlProportion();
	}


	Tracer_ServerSelectRecord();

	cout<<"now server people:"<<endl;
	Tracer_ServerInfo();

	return 0;
}

