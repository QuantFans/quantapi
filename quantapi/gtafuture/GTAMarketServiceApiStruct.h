//////////////////////////////////////////////////////////////////////////////
///
/// @file    GTAMarketServiceApiStruct.h
/// @brief   �ӿ��õ������ݽṹ����
/// @note    Copyright (C), 2008-2010, GTA Information Tech. Co., Ltd.
/// @version 1.0
/// @author  �οɶ�
/// @date    2010.10.18
///
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_MARKET_SERVICE_API_STRUCT_H_
#define GTA_MARKET_SERVICE_API_STRUCT_H_


#ifdef _WIN32
#define _CDECL         __cdecl
#ifdef GTAMarketServiceApi_EXPORTS
#define GTA_API_EXPORT __declspec(dllexport)
#else
#define GTA_API_EXPORT __declspec(dllimport)
#endif
#else
#define _CDECL
#define GTA_API_EXPORT
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif


#ifdef _WIN32
#include <windows.h>
#else
typedef unsigned char      BYTE;
typedef unsigned short int WORD;
typedef unsigned int       DWORD;
typedef unsigned int       UINT;
typedef long long          LONGLONG;
typedef long long          __int64;
typedef unsigned long long UINT64;
typedef int                INT;
#endif

#pragma pack(push)
#pragma pack(1)

const DWORD MARKET_DESC_LEN    = 21; ///< �г������ַ�����󳤶�.
const DWORD MAX_DATA_TYPE_SIZE = 20; ///< ���������������.

/// �г���־.
struct MarketInfo
{
    BYTE source;  ///< ���
    BYTE market;  ///< �г�
};

/// �г����ݱ�־.
struct MarketDataInfo
{
    MarketInfo mi;   ///< �г���־
    BYTE       type; ///< ��������
};

/// �г�����.
struct MarketDesc
{
    MarketInfo mi;                            ///< �г���־
    BYTE       dataTypeSize;                  ///< �г�����������������Ŀ
    BYTE       dataTypes[MAX_DATA_TYPE_SIZE]; ///< �洢��dataTypeSize����������
    char       desc[MARKET_DESC_LEN];         ///< ������GB2312����
};

/// ��֤����.
struct CertifyReq
{
    char           username[64];   ///< �û���
    char           passwd[32];     ///< ����
    char           addr[20];       ///< ��֤��������ַ
    unsigned short port;           ///< ��֤�������˿�
};

/// ��֤��Ӧ.
struct CertifyResp
{
    BYTE result;  ///< ��֤��� 0�ɹ� ����ʧ�ܣ����ʧ�ܴ����
    int  userID;  ///< �û�ID
};

/// ��֤���񷵻ص�������Ϣ.
struct MarketServerInfo
{
    MarketInfo mi;                            ///< ����
    BYTE       dataTypeSize;                  ///< �г�����������������Ŀ
    BYTE       dataTypes[MAX_DATA_TYPE_SIZE]; ///< �洢��dataTypeSize����������
    char       addr[16];                      ///< ������ IP
    WORD       port;                          ///< �˿�
    char       desc[MARKET_DESC_LEN];         ///< ������GB2312����
};

/// �г������ӳ���Ϣ.
struct MarketDelay
{
    MarketDataInfo mdi;   ///< �г����ݱ�־
	__int64        delay; ///< �ӳ�
};

/// ������������.
struct DataDownloadReq
{
    MarketDataInfo mdi;      ///< �г����ݱ�־
    char           addr[20]; ///< ��֤��������ַ
    WORD           port;     ///< ��֤�������˿�
};
//----------------------------------------------------------

#pragma pack(pop)

/// �����붨��.
enum ErrorDefine
{
    GTA_ERROR_SUCCESS               = 0,  ///< �ɹ�

    // = ������ش���
    GTA_ERROR_NET_CONN              = 1,   ///< ���Ӵ���
    GTA_ERROR_NET_BREAK             = 2,   ///< �����쳣
    GTA_ERROR_NET_HEARTBEAT         = 3,   ///< ������ʱ

    // = ��֤��ش���
    GTA_ERROR_AUTH_NOT_INIT         = 10,  ///< ���δ��ʼ������Ҫ�ȵ���Init
    GTA_ERROR_AUTH_BUSY             = 11,  ///< ���ڴ���һ��������Ҫ�ȴ����ز��ܴ�����һ������
    GTA_ERROR_AUTH_USERPASSWD       = 12,  ///< �û���/�������
    GTA_ERROR_AUTH_LOGON            = 13,  ///< �Ѿ���¼
    GTA_ERROR_AUTH_NOT_EXIST        = 14,  ///< �û�������
    GTA_ERROR_AUTH_PASSWD           = 15,  ///< �������
    GTA_ERROR_AUTH_EXPIRE           = 16,  ///< �˻��ѹ���
    GTA_ERROR_AUTH_INVALID_USERNAME = 17,  ///< �û���������Ч�ַ�

    // = ������֤��ش���
    GTA_ERROR_RECONN_NEED_AUTH      = 20,  ///< ��Ҫ������֤
    GTA_ERROR_RECONN_CONNECTED      = 21,  ///< �������������

    // = �ַ���ش���
    GTA_ERROR_QUOTE_LOGONFAILED     = 30  ///< �ַ���������¼ʧ��
};

/// ����״̬����.
enum NetState
{
    GTA_CONN_STATE_CONNECTING   = 0,   ///< ��������
    GTA_CONN_STATE_OPEN         = 1,   ///< ������
    GTA_CONN_STATE_CLOSING      = 2,   ///< ���ڹر�
    GTA_CONN_STATE_CLOSED       = 3,    ///< �ѹر�
    GTA_STATE_VERSION_DIFFERENCE = 4    /// <API��ַ��汾�Ų�һ��
};

/// ����ģʽ����.
enum SubscribeMode
{
    SUBSCRIBE_MODE_SUBSCRIBE    = 0,    ///< ����
    SUBSCRIBE_MODE_UNSUBSCRIBE  = 1     ///< �˶�
};

/// �г���Χ����.
enum MarketRange
{
    MARKET_RANGE_ALL    = 0,    ///< ȫ�г�
    MARKET_RANGE_PART   = 1     ///< ���ָ���
};

/// ϵͳ״̬�������Ͷ���.
enum SysStateType
{
    SYS_STATE_TYPE_DELAY = 0, ///< �ӳ���Ϣ����
};

/// ����Դ����.
enum SnapDataSource
{
    SNAP_DATA_SOURCE_CACHE  = 0,    ///< ���ػ������
    SNAP_DATA_SOURCE_SERVER = 1     ///< ����������
};

#endif // GTA_MARKET_SERVICE_API_STRUCT_H_
