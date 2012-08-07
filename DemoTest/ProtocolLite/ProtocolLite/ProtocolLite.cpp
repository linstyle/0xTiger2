// ProtocolLite.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CTProtocol.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//char Buffer[34]={0};

	//printf("%s\n", DecimalToBinary(100, Buffer));
	//printf("%s\n", DecimalToBinary(32, Buffer));
	//printf("%s\n", DecimalToBinary(33, Buffer));
	char Buffer[1024]={0};
	CProtocolA ProtocolA1;

	ProtocolA1.SetT1(10);
	ProtocolA1.SetT2(20);

	ProtocolA1.SetT4(40);
	ProtocolA1.SetT5(50);
	ProtocolA1.SetT6(60);

	printf("------ProtocolA1-------\n");
	ProtocolA1.TracerMe();

	ProtocolA1.Send(Buffer);

	CProtocolA ProtocolA2;
	ProtocolA2.Recv(Buffer);

	printf("------ProtocolA2-------\n");
	ProtocolA2.TracerMe();

	return 0;
}

