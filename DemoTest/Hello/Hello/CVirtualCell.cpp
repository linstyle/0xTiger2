#include "stdafx.h"
#include "CVirtualCell.h"

CVirtualCell::CVirtualCell()
{
	m_nBlockLen = 0;
	m_nMaxX = 0;
	m_nMaxY = 0;
}

void CVirtualCell::Init(int nX, int nY, int nBlockLen)
{
	if (nX<=0 || nY<=0 || nBlockLen<=0)
	{
		return;
	}

	m_nMaxX = nX-1; //0~m_nMaxX
	m_nMaxY = nY-1;
	m_nBlockLen = nBlockLen;

	InitBlocks();
}

void CVirtualCell::InitBlocks()
{
	int nMaxBlockX = GetXOfBlock();
	int nMaxBlockY = GetYOfBlock();

	m_setBlocks.resize(nMaxBlockX);
	for (unsigned int i=0; i<m_setBlocks.size(); ++i)
	{
		m_setBlocks[i].resize(nMaxBlockY);

		for (unsigned int j=0; j<m_setBlocks[i].size(); ++j)
		{
			m_setBlocks[i][j] = i*nMaxBlockX + j;
		}
	}
}


int CVirtualCell::GetMapBlockIndex(int nPos)
{
	return nPos/m_nBlockLen;
}

int CVirtualCell::GetXOfBlock()
{
	return m_nMaxX/m_nBlockLen + 1;
}

int CVirtualCell::GetYOfBlock()
{
	return m_nMaxY/m_nBlockLen + 1;
}


bool CVirtualCell::GetAroundBlockByLevel(int nPosX, int nPosY, std::vector<int>& vecGetBlock, int nLevel)
{
	if (m_nMaxX<nPosX || m_nMaxY<nPosY || nLevel<0)
	{
		return false;
	}

	int nDebugX = GetMapBlockIndex(nPosX);
	int nDebugY = GetMapBlockIndex(nPosY);
	printf("GetAroundBlockByLevel x:%d, y:%d, value:%d\n", nDebugX, nDebugY, m_setBlocks[nDebugX][nDebugY]);

	int x,y;
	FOR_BLOCKS(this, nPosX, nPosY, nLevel)
	{
		vecGetBlock.push_back(m_setBlocks[x][y]);
	}
	
	return true;
}

void CVirtualCell::TraceMe()
{
	for (unsigned int i=0; i<m_setBlocks.size(); ++i)
	{
		for (unsigned int j=0; j<m_setBlocks[i].size(); ++j)
		{
			printf("%5d", m_setBlocks[i][j]);
		}
		printf("\n"); 
	}	
}