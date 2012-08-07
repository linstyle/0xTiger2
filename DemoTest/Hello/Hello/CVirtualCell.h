/*
	@lindp
	@2012/03/13
	@根据传入的边界，依次扩散周边的格子返回
*/

#pragma  once

#include <vector>

#define  FOR_BLOCKS(P,X,Y,Lev)	\
	for(x=__max(P->GetMapBlockIndex(X)-Lev, 0); x<=P->GetMapBlockIndex(X)+Lev && x < P->GetXOfBlock(); x++)	\
		for(y=__max(P->GetMapBlockIndex(Y)-Lev, 0); y<=P->GetMapBlockIndex(Y)+Lev && y < P->GetXOfBlock(); y++)
	

class CVirtualCell
{
public:
	CVirtualCell();

	/*
		@Init(int nX, int nY, int nBlock);
		nX:整个地图的长度
		nX:整个地图的宽度
		nBlock:每个格子的大小
	*/
	void Init(int nX, int nY, int nBlockLen);

	/*
		@bool GetBlock(int nPos, std::vector<int>& Block, int nLevel);
		nPos:你在的坐标
		Block:取到的结果
		nLevel:周边第几圈，从1开始
	*/
	bool GetAroundBlockByLevel(int nPosX, int nPosY, std::vector<int>& vecGetBlock, int nLevel);


	//debug
	void TraceMe();


private:
	void InitBlocks();

	int GetMapBlockIndex(int nPos);

	/*
		总长度对应的块数
	*/
	int GetXOfBlock();
	int GetYOfBlock();

public:

private:
	int m_nMaxX;
	int m_nMaxY;
	int m_nBlockLen;

	typedef std::vector<int> BLOCK_VEC;
	typedef std::vector< BLOCK_VEC > BLOCKS_VEC;

	BLOCKS_VEC m_setBlocks;
};