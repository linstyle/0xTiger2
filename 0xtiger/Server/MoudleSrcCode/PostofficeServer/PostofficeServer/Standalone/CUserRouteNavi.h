#pragma once


/*
	�洢�û�ת����·��ָʾ��Ϣ
	����ת���Ķ���

	ת���ı��, BIN, DPC.
	����DPC��ʱΪ0(��ʱһ̨)
*/

class CUserRouteNavi
{
public:	

private:
	/*
		�߱�ʶ  Bin��������ʶ Dpc��������ʶ(����һ̨)
	*/
	int nIdentiLine;
	int nIdentiBin;
	int nIdentiDpc;

	/*
		nNaviBinResNumber:��Bin�������϶�Ӧ����Դ���
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