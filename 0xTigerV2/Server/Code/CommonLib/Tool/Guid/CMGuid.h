/*  ���ߣ�			�ֶ�ƽ                                                              
	����ʱ�䣺	2011/03/01                                                         
    ����˵����  GUID����
	guid�ⶫ����ʵ�����޵���á����õ��ǲ����õȵȡ���λ���������ϣ�һ�㶼����һЩ�������󡣱���
	���ڳ����ﾭ�����õ�HASH����ϣ����������Ϊ��ֵ�����и����ڴ濽���ȵȡ�����������������һ����֤
	�Ķ�����
	��ô�ڷ���֮ǰ���Ҷ�������Ӧ�õ�������Ϊ����������ڸ�����
	һ�Ƿǳ��鷳���ڸ�����չ�ͽ����ϣ�
	���Ǹ�Ӧ�÷�չ�÷ǳ�NB�ˣ���Ϊ�������㣬�Ѿ�����Ҫ������^_^
*/

#pragma  once
#include "GlobalType.h"
#include "GameEnum.h"
#include "Singleton.h"

/*
	GUID ��8���ֽڣ�64λ���������£�
	0  -11bit :����������,		12bit, ֧�� 0-4096��
    12-18bit :��һ���࣬		7bit,  ֧�� 0-127
	19-25bit :�ڶ����࣬		7bit,  ֧��0-127
	26-31bit :����,					6bit,  ֧��0-64

	��5~8�ֽڣ���š��������ļ��ж�ȡ
*/
namespace name_mguid
{
	const int FIELD1_BIT = 12;
	const int FIELD2_BIT = 7;
	const int FIELD3_BIT = 7;
	const int FIELD4_BIT = 6;
	const int FIELD5_BIT = 32;

	//д������ļ���·����
	const int LEN_APP_NAME = 64;
	const int LEN_KEY_NAME = 64;
	const int LEN_VALUE_NAME = 24;
	const int LEN_FILE_NAME = 128;
};

struct GUID_SET
{
	GUID_SET()
	{
		m_nGuidBegin = m_nGuidEnd = 0;
	}
	/*
		m_nGuidBegin:		�������ʼ����,ÿ�η���󶼻��Լ�
		m_nGuidEnd:			����Ľ�ֹ��
	*/
	unsigned int m_nGuidBegin;
	unsigned int m_nGuidEnd;
};

class CMGuid:public Singleton<CMGuid>
{
public:
	/*
		Init
		nBatchFreeGuid:һ����������ٿ����GUID
		pGuidSet:�����ļ��еĳ�ʼ������,��С��IDENTI_COUNT_MAX
	*/
	void Init(int nBatchFreeGuid, wchar_t *pFileName, GUID_SET* pGuidSet);

	/*
		MallocGUID
		����һ��GUIDֵ��������GUID�ֶε��������
		12-18bit :��һ���࣬������IdentiType
		19-25bit :�ڶ�����, ������nSubType
		26-31bit :����,Ĭ��0
		32-63bit :��ţ��ڲ�д��
	*/
	MGUID MallocGUID(int _nQuID, GAME_IDENTI_TYPE  IdentiType, int _nSubType);

private:
	/*
		GetSerialNumber
		����IdentiType,�ҵ���Ӧ��m_nGuidSet,Ȼ�󷵻�һ�����ñ��
		�������Ϊ0����ʾ��ų����ù����������
	*/
	unsigned int GetSerialNumber(GAME_IDENTI_TYPE  IdentiType);
	MGUID FormatGUID(int nField1, int nField2, int nField3, int nField4, unsigned int nSerialNumber);

	void UpdateGuidSet(GAME_IDENTI_TYPE IdentiType, GUID_SET *pGuidSet);
	GUID_SET *GetGuidSet(int nIndex);
public:

private:
	//һ����������ٿ����GUID
	int m_nBatchFreeGuid;
	GUID_SET m_nGuidSet[GAME_IDENTI_COUNT_MAX];

	//Ҫд������ļ���·��
	wchar_t m_strFileName[name_mguid::LEN_FILE_NAME];
};

#define g_Guid CMGuid::getSingleton()