#include "CNetworkPublicSelect.h"


CNetworkPublicSelect::CNetworkPublicSelect()
{
	FD_ZERO(&SetRead);
	FD_ZERO(&SetWrite);

}

int CNetworkPublicSelect::GetConnectSum()
{
	return SetRead.fd_count;
}

int CNetworkPublicSelect::AddToReadSet(int nSocket)
{
	if( SetRead.fd_count >= 63 )
	{
		//closesocket(nSocket);
		return -1;
	}

	FD_SET(nSocket, &SetRead);

	return 0;
}

void CNetworkPublicSelect::EraseFromReadSet(int nSocket)
{
	FD_CLR(nSocket, &SetRead);

	closesocket(nSocket);
}
