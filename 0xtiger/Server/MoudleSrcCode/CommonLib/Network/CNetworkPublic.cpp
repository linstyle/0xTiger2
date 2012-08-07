#include "CNetworkPublic.h"

//
//CCommonSocket with struct
//
CCommonSocket::CCommonSocket()
{
	nSocket = -1;
	nPort = -1;
	nIP = 0;	

	nFirstRecvTime = nSecondRecvTime = nFirstSendTime = nSecondSendTime;
}

CCommonSocket::~CCommonSocket()
{
	if( -1!=nSocket )
	{
		closesocket(nSocket);
	}	
}

bool CCommonSocket::InitSocketTCPC(unsigned long nNonb)
{
	// Prepare a socket to listen for connections.
	int nResult;

	nSocket = socket(AF_INET, SOCK_STREAM, 0);
	MTVERIFY( INVALID_SOCKET!=nSocket );
	
	nResult = ioctlsocket(nSocket, FIONBIO, &nNonb);
	MTVERIFY( SOCKET_ERROR!=nResult );

	ZeroMemory(&Addr, sizeof(Addr));
	Addr.sin_family	= AF_INET;
	Addr.sin_port	= htons(nPort);
	Addr.sin_addr.s_addr = nIP;
	return true;
}

bool CCommonSocket::InitSocketTCPS(unsigned long nNonb)
{
	// Prepare a socket to listen for connections.
	int nResult;

	nSocket = WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
	MTVERIFY( INVALID_SOCKET!=nSocket );

	ZeroMemory(&Addr, sizeof(Addr));
	Addr.sin_family	= AF_INET;
	Addr.sin_port	= htons(nPort);
	Addr.sin_addr.s_addr = nIP;

	nResult = bind(nSocket, (sockaddr*)&Addr, sizeof(Addr));
	MTVERIFY( SOCKET_ERROR!=nResult );

	nResult = listen(nSocket,5);
	MTVERIFY( SOCKET_ERROR!=nResult );

	// Change the socket mode on the listening socket from blocking to
	// non-block so the application will not block waiting for requests.		
	nResult = ioctlsocket(nSocket, FIONBIO, &nNonb);
	MTVERIFY( SOCKET_ERROR!=nResult );

	return true;
}

bool CCommonSocket::InitSocketUDPS(unsigned long nNonb)
{
	int nResult;

	nSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	MTVERIFY( INVALID_SOCKET!=nSocket );

	nResult = ioctlsocket(nSocket, FIONBIO,(unsigned long*)&nNonb);
	MTVERIFY( SOCKET_ERROR!=nSocket );

	ZeroMemory(&Addr, sizeof(Addr));
	Addr.sin_family	   = AF_INET;
	Addr.sin_port		   = htons(nPort);
	Addr.sin_addr.s_addr = nIP;

	nResult = bind(nSocket, (sockaddr*)&Addr, sizeof(Addr) );
	MTVERIFY( nResult!=SOCKET_ERROR );
	
	return true;
}

bool CCommonSocket::InitSocketUDPC(unsigned long nNonb)
{
	int nResult;

	nSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	MTVERIFY( INVALID_SOCKET!=nSocket );

	nResult = ioctlsocket(nSocket, FIONBIO,(unsigned long*)&nNonb);
	MTVERIFY( SOCKET_ERROR!=nSocket );

	ZeroMemory(&Addr, sizeof(Addr));
	Addr.sin_family	   = AF_INET;
	Addr.sin_port		= htons(nPort);
	Addr.sin_addr.s_addr = nIP;
	
	return true;
}

int CCommonSocket::ConnectNonb(int fdNonb, const sockaddr *pConnectAddr, int nConnectAddrSize, int nSec)
{
	int nResult;
/*
	int nOptVal, nLenOptVal=sizeof(nOptVal);

	nResult = getsockopt(fdNonb, SOL_SOCKET, SO_TYPE, (char*)&nOptVal, &nLenOptVal);
	if( SOCKET_ERROR==nResult )
	{
		return -1;
	}
*/

	unsigned long argp = 1;
	nResult = ioctlsocket(fdNonb, FIONBIO,(unsigned long*)&argp);
	if( SOCKET_ERROR==nResult )
	{
		return -1;
	}

	nResult = connect(fdNonb, pConnectAddr, nConnectAddrSize);
	if( WSAEWOULDBLOCK != WSAGetLastError())
	{
		closesocket(fdNonb);
		return -1;
	}		
	else if(0==nResult)				//connect completed immediately 
	{
		return 0;
	}


	fd_set SetWrite;
	timeval TimeSelect;

	TimeSelect.tv_sec=nSec;
	TimeSelect.tv_usec=0;

	FD_ZERO(&SetWrite);
	FD_SET(fdNonb, &SetWrite);

	nResult = select(0, NULL, &SetWrite, NULL, &TimeSelect);
	if( nResult<=0 )
	{
		closesocket(fdNonb);
		WSASetLastError(WSAETIMEDOUT);
		return -1;
	}

	if( FD_ISSET(fdNonb, &SetWrite) )
	{
		return 0;
	}

	return -1;
}

/*
If no error occurs, recv returns the Identi of bytes received. If the connection has been gracefully 
closed, the return value is zero. Otherwise, a value of SOCKET_ERROR is returned, and a specific error 
code can be retrieved by calling WSAGetLastError.
*/
int CCommonSocket::RecvnTCP(int fd, char* pRecvBuffer, int nRecvLen)
{
	char *Ptr = pRecvBuffer;
	int nRecv = nRecvLen;
	int nRecvHasLen;

	while( nRecv>0 )
	{
		nRecvHasLen = recv(fd, Ptr, nRecv, 0);
		if( nRecvHasLen<=0 )
		{
			if( WSAEWOULDBLOCK != WSAGetLastError())
			{
				return nRecvHasLen;
			}
			//
			//would block , must read again
			nRecvHasLen = 0;
		}

		nRecv -= nRecvHasLen;
		Ptr += nRecvHasLen;
	}

	return nRecvLen;
}

int CCommonSocket::SendnTCP(int fd, const char* pSendBuffer, int nSendLen)
{
	const char *Ptr = pSendBuffer;
	int nSend = nSendLen;
	int nSendHasLen;

	while( nSend>0 )
	{
		nSendHasLen = send(fd, Ptr, nSend, 0);
		if( nSendHasLen<=0 )
		{
			if( WSAEWOULDBLOCK != WSAGetLastError())
			{
				return nSendHasLen;
			}
			//
			//send again
			nSendHasLen = 0;
		}

		nSend -= nSendHasLen;
		Ptr += nSendHasLen;

	}

	return nSendLen;
}

int CCommonSocket::RecvnUDP(int fd, char* pRecvBuffer, int nRecvLen, int nRecvFlag, sockaddr* RecvAddr)
{
/*
If no error occurs, recvfrom returns the Identi of bytes received. If the connection has been 
gracefully closed, the return value is zero. Otherwise, a value of SOCKET_ERROR is returned, 
and a specific error code can be retrieved by calling WSAGetLastError.
*/
	int nResult;
	int nRecvAddrSize = sizeof(*RecvAddr);

	nResult = recvfrom(fd, pRecvBuffer, nRecvLen, nRecvFlag, RecvAddr, &nRecvAddrSize);
	if( SOCKET_ERROR==nResult )
	{
		//有错误发生,或者接收的字节数不够,或者套接字关闭
		return -1;
	}

	return nResult;
}
int CCommonSocket::SendnUDP(int fd, const char* pSendBuffer, int nSendLen, int nSendFlag, const struct sockaddr* SendAddr)
{
/*
If no error occurs, sendto returns the total Identi of bytes sent, which can be less than 
the Identi indicated by len. Otherwise, a value of SOCKET_ERROR is returned, and a specific 
error code can be retrieved by calling WSAGetLastError.
*/
	int nResult;
	int nSendAddrSize = sizeof(*SendAddr);
	
	nResult = sendto(fd, pSendBuffer, nSendLen, nSendFlag, SendAddr, nSendAddrSize);
	if( nResult<nSendLen )
	{
		//有错误发生或者发送的字节数不够
		return -1;
	}

	return nResult;
}

//
//CCommonSocket end

void CPublicProtocolVerify::SetVersion1(int nMaxMsgOraderAction)
{
	m_nMaxMsgOrderAction = nMaxMsgOraderAction;
}

//
//检测数据大小
bool CPublicProtocolVerify::IsMsgSize(int nInSizeOfMsg, int nWillRecvBytes, int nHasRecvBytes)
{

	if( ( name_msg_protocol::SOCKET_BUFF_SIZE < nInSizeOfMsg )
	 || ( nWillRecvBytes != nHasRecvBytes)
	  )
	{
		return false;
	}

	return true;
}

//
//检测动作序号
bool CPublicProtocolVerify::IsMsgAction(int nRecvOrderAction)
{
	if( nRecvOrderAction>=m_nMaxMsgOrderAction )
	{
		return false;
	}

	return true;
}