#ifndef COMMON_ENCRYPT_HEAD_FILE
#define COMMON_ENCRYPT_HEAD_FILE

// C RunTime Header Files
#include <windows.h>
#include <stdio.h>


//////////////////////////////////////////////////////////////////////////

//MD5 ������
class CMD5Encrypt
{
	//��������
private:
	//���캯��
	

	//���ܺ���
public:
	CMD5Encrypt() {}
	//��������
	static void EncryptData(LPCTSTR pszSrcData, TCHAR szMD5Result[33]);
};

//////////////////////////////////////////////////////////////////////////

//��������
class  CXOREncrypt
{
	//��������
private:
	//���캯��
	CXOREncrypt() {}

	//���ܺ���
public:
	//��������
	static WORD EncryptData(LPCTSTR pszSrcData, LPTSTR pszEncrypData, WORD wSize);
	//�⿪����
	static WORD CrevasseData(LPCTSTR pszEncrypData, LPTSTR pszSrcData, WORD wSize);
};

//////////////////////////////////////////////////////////////////////////

#endif