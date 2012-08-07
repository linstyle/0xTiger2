/*
	@lindp
	@2012/03/13
	@���ݴ���ı߽磬������ɢ�ܱߵĸ��ӷ���
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
		nX:������ͼ�ĳ���
		nX:������ͼ�Ŀ��
		nBlock:ÿ�����ӵĴ�С
	*/
	void Init(int nX, int nY, int nBlockLen);

	/*
		@bool GetBlock(int nPos, std::vector<int>& Block, int nLevel);
		nPos:���ڵ�����
		Block:ȡ���Ľ��
		nLevel:�ܱߵڼ�Ȧ����1��ʼ
	*/
	bool GetAroundBlockByLevel(int nPosX, int nPosY, std::vector<int>& vecGetBlock, int nLevel);


	//debug
	void TraceMe();


private:
	void InitBlocks();

	int GetMapBlockIndex(int nPos);

	/*
		�ܳ��ȶ�Ӧ�Ŀ���
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