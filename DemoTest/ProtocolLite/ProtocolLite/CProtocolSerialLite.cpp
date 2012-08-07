#include "CProtocolSerialLite.h"
#include <memory.h>
#include <stdio.h>
 
/*
		CProtocolSerialLiteSend
*/
char* CProtocolSerialLiteSend::Serial(char* pBuffer, char* pVariable, int nVariableSize)
{
	memcpy(pBuffer, pVariable, nVariableSize);
	pBuffer+=nVariableSize;

	return pBuffer;
}

/*
		CProtocolSerialLiteRecv
*/
char* CProtocolSerialLiteRecv::Serial(char* pBuffer, char* pVariable, int nVariableSize)
{
	memcpy(pVariable, pBuffer, nVariableSize);
	pBuffer+=nVariableSize;

	return pBuffer;
}


/*
	CProtocolFlagLite
*/
CProtocolFlagLite::CProtocolFlagLite()
{
	memset(m_nFlag, 0, sizeof(m_nFlag));

	m_nMaxFlag = sizeof(m_nFlag)*8;

	m_nFlagCount = sizeof(m_nFlag)/sizeof(*m_nFlag);
}

void CProtocolFlagLite::TracerMe()
{
	char Buffer[34];
	for(int i=0; i<m_nFlagCount; ++i)
	{
		memset(Buffer, 0, sizeof(Buffer));
		printf("i:%d, %s\n", i, DecimalToBinary(m_nFlag[i], Buffer) );
	}
}

//nBit:表示第几个，失败返回-1
int CProtocolFlagLite::SetFlag(int nBit)
{
	if(nBit>=m_nMaxFlag)
	{
		return -1;
	}

	int nIndex = nBit/(m_nMaxFlag/m_nFlagCount);
	m_nFlag[nIndex] |= (1<<nBit);

	return 0;
}

//nBit:表示第几个，无效返回0
int CProtocolFlagLite::GetFlag(int nBit)
{
	if(nBit>=m_nMaxFlag)
	{
		return -1;
	}

	int nIndex = nBit/(m_nMaxFlag/m_nFlagCount);

	return m_nFlag[nIndex] & (1<<nBit);
}

char* CProtocolFlagLite::DecimalToBinary(int nDecimal, char *pBuffer)
{
	if( nDecimal<0 )
	{
		return NULL;
	}

	int nIndex=0;
	while(nDecimal>0)
	{
		sprintf(&pBuffer[nIndex++], "%d", nDecimal%2);
		nDecimal/=2;
	}
	//反转
	for (int i=0; i<nIndex/2; i++)
	{
		char c=pBuffer[i];
		pBuffer[i] = pBuffer[nIndex-i-1];
		pBuffer[nIndex-i-1] = c;
	}
	return pBuffer;
}