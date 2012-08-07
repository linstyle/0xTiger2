/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/07/14                                                         
    ����˵����  ����Э���壬����Э�鴦�������
*/

#pragma once
#include "GlobalType.h"
#include "MTASSERT.h"

/*
	@PACKET_DEFINE

	Client  C   �ͻ���
	LoginServer L
	WeightServer W
	GatewayServer G
	PhonebookServer P
	GameServer G
	DataServer  D
	ChatServer  C

	������������£�Ԥ�������࣬�������Ӳ���Ҫ��Э���ļ���:
	PACKET_DEFINE2��ΪPACKET_DEFINE1������.ע����������
*/
enum PACKET_DEFINE1
{
	PACKET1_MIN,
	/* 0-4 */ //�ڲ��������߼����ͨѶ
	PACKET1_INNER_NET_LOGIC,        //�ڲ�ͨѶ���������߼���
	PACKET1_LOGIN,                           //��½Э��
	
	PACKET1_HELLO,				               //ÿ������������̶���Э��ʵ��,������ʱ����һ���ʺ�
	PACKET1_REHELLO,			               //���ظ��ʺ�
	PACKET1_FILE_TRANS,		          //�����ļ�����
	PACKET1_ACCEPT,				          //�¶������ӽ���
	PACKET1_EXCEPTION,		              //���������Ҫ�رյĶ���

	PACKET1_LOGIN_GL,			         //GS��½��LS
	PACKET1_LOGIN_CG,			         //ChatServer��½��GateWay

	PACKET1_MAX
};

enum PACKET_DEFINE2
{
	PACKET2_MIN = 0,
	//-----------PACKET1_HELLO
	PACKET2_HELLO_GL_SAY,
	PACKET2_HELLO_GL_RESAY,

	//-----------PACKET1_INNER_NET_LOGIC
	PACKET2_NTOL_ACCEPT_SOCKET,           //�������յ�һ������
	PACKET2_NTOL_ERR,                                //�����Ͷ�ݵĳ����
	PACKET2_LTON_SERVER_SOCKET,           //�߼���Ͷ�ݵ�server�׽��ְ�
	PACKET2_LTON_CONNECT_SOCKET,       //�߼���Ͷ�ݵ�client�׽��ְ�
	PACKET2_LTON_ERR,                                //�߼���Ͷ�ݵĳ����
	PACKET2_MAX,

	//-----------PACKET1_LOGIN
	PACKET2_LOGIN_GL,                        //GS��LS��½

};

/*
	Э���ͷ��
	����Ĵ�С�����ں����Ż�
*/

class IPackHead
{
public:
	IPackHead(PACKET_DEFINE1 nPacketDefine1, int nPacketSize);

	void SetNetObject(void *pNetObject);
	void* GetNetObject()  const;

	void SetPacketDefine2(PACKET_DEFINE2 nPacketDefine2);
	void SetPacketSize(int nPacketSize);

	PACKET_DEFINE1 GetPacketDefine1() const;
	PACKET_DEFINE2 GetPacketDefine2() const;

	//����С��head+content
	int GetPacketSize()  const;
	int GetPacketContentSize()  const;

private:

public:

private:
	int m_nPacketSize;  //����С��head+content
	PACKET_DEFINE1 m_nPacketDefine1;
	PACKET_DEFINE2 m_nPacketDefine2;
	int m_nRoutePriority;//·��ת���ĵȼ�, ��Ҫ�ֶ�����
	void *m_pNetObject; //����㣬�߼��������˵�ǲ�ͬ�Ľڵ㡣��������֮�䴫�ݵĲ���Ҳ����Э���һ����
};

namespace name_msg_packet
{
	/*
		 byte��ÿ�����������ֽ���,�����MTU��ء�����ͨ��MTU 1400Ϊ������Ϊ2800
	*/
	const unsigned int SOCKET_BUFF_SIZE = 2800; 
	const unsigned int PACKET_HEAD_SIZE = sizeof(IPackHead);
};

/*
	Э��Ĵ���������
*/
class IPacketObject
{
public:
	PACKET_DEFINE1 m_nPacketDefine;	

private:

public:
	IPacketObject(PACKET_DEFINE1 nPacketDefine);
	PACKET_DEFINE1 GetPacketID();

	/*
		RoleObject�ڴ���Accept�¼�ʱ��ʾRoleNet����,
		�����ʾRole����
	*/
	virtual int	Execute(IPackHead* pPackHead)=0;

private:


};

