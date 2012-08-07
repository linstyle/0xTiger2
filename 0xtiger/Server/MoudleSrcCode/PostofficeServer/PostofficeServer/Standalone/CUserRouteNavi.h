#pragma once


/*
	存储用户转发的路由指示信息
	包括转发的对象

	转发的编号, BIN, DPC.
	其中DPC暂时为0(暂时一台)
*/

class CUserRouteNavi
{
public:	

private:
	/*
		线标识  Bin服务器标识 Dpc服务器标识(独立一台)
	*/
	int nIdentiLine;
	int nIdentiBin;
	int nIdentiDpc;

	/*
		nNaviBinResNumber:在Bin服务器上对应的资源编号
	*/
	int nInBinPoolRes;

public:
	CUserRouteNavi()
	{
		nIdentiLine=nIdentiBin=nIdentiDpc=-1;
	}

	int GetIdentiLine()
	{
		return nIdentiLine;
	}
	int GetIdentiBin()
	{
		return nIdentiBin;
	}
	int GetIdentiDpc()
	{
		return nIdentiDpc;
	}
	int GetResIdentiInBin()
	{
		return nInBinPoolRes;
	}

	void SetIdentiLine(int nLine)
	{
		nIdentiLine = nLine;
	}

	void SetIdentiBin(int nIdenti)
	{
		nIdentiBin = nIdenti;
	}
	void SetIdentiDpc(int nIdenti)
	{
		nIdentiDpc = nIdenti;
	}
	void SetResIdentiInBin(int nIdenti)
	{
		nInBinPoolRes = nIdenti;
	}



private:

};