//////////////////////////////////////////////////////////////////////////////
///
/// @file    GTAMarketServiceApiStruct.h
/// @brief   接口用到的数据结构定义
/// @note    Copyright (C), 2008-2010, GTA Information Tech. Co., Ltd.
/// @version 1.0
/// @author  何可丁
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

const DWORD MARKET_DESC_LEN    = 21; ///< 市场描述字符串最大长度.
const DWORD MAX_DATA_TYPE_SIZE = 20; ///< 最大数据类型数量.

/// 市场标志.
struct MarketInfo
{
    BYTE source;  ///< 深度
    BYTE market;  ///< 市场
};

/// 市场数据标志.
struct MarketDataInfo
{
    MarketInfo mi;   ///< 市场标志
    BYTE       type; ///< 数据类型
};

/// 市场描述.
struct MarketDesc
{
    MarketInfo mi;                            ///< 市场标志
    BYTE       dataTypeSize;                  ///< 市场包含的数据类型数目
    BYTE       dataTypes[MAX_DATA_TYPE_SIZE]; ///< 存储了dataTypeSize个数据类型
    char       desc[MARKET_DESC_LEN];         ///< 描述，GB2312编码
};

/// 认证请求.
struct CertifyReq
{
    char           username[64];   ///< 用户名
    char           passwd[32];     ///< 密码
    char           addr[20];       ///< 认证服务器地址
    unsigned short port;           ///< 认证服务器端口
};

/// 认证回应.
struct CertifyResp
{
    BYTE result;  ///< 认证结果 0成功 其余失败，详见失败代码表
    int  userID;  ///< 用户ID
};

/// 认证服务返回的行情信息.
struct MarketServerInfo
{
    MarketInfo mi;                            ///< 行情
    BYTE       dataTypeSize;                  ///< 市场包含的数据类型数目
    BYTE       dataTypes[MAX_DATA_TYPE_SIZE]; ///< 存储了dataTypeSize个数据类型
    char       addr[16];                      ///< 服务器 IP
    WORD       port;                          ///< 端口
    char       desc[MARKET_DESC_LEN];         ///< 描述，GB2312编码
};

/// 市场数据延迟信息.
struct MarketDelay
{
    MarketDataInfo mdi;   ///< 市场数据标志
	__int64        delay; ///< 延迟
};

/// 数据下载请求.
struct DataDownloadReq
{
    MarketDataInfo mdi;      ///< 市场数据标志
    char           addr[20]; ///< 认证服务器地址
    WORD           port;     ///< 认证服务器端口
};
//----------------------------------------------------------

#pragma pack(pop)

/// 错误码定义.
enum ErrorDefine
{
    GTA_ERROR_SUCCESS               = 0,  ///< 成功

    // = 网络相关错误
    GTA_ERROR_NET_CONN              = 1,   ///< 连接错误
    GTA_ERROR_NET_BREAK             = 2,   ///< 网络异常
    GTA_ERROR_NET_HEARTBEAT         = 3,   ///< 心跳超时

    // = 认证相关错误
    GTA_ERROR_AUTH_NOT_INIT         = 10,  ///< 组件未初始化，需要先调用Init
    GTA_ERROR_AUTH_BUSY             = 11,  ///< 正在处理一种任务，需要等待返回才能处理下一种任务
    GTA_ERROR_AUTH_USERPASSWD       = 12,  ///< 用户名/密码错误
    GTA_ERROR_AUTH_LOGON            = 13,  ///< 已经登录
    GTA_ERROR_AUTH_NOT_EXIST        = 14,  ///< 用户不存在
    GTA_ERROR_AUTH_PASSWD           = 15,  ///< 密码错误
    GTA_ERROR_AUTH_EXPIRE           = 16,  ///< 账户已过期
    GTA_ERROR_AUTH_INVALID_USERNAME = 17,  ///< 用户名包含无效字符

    // = 重连认证相关错误
    GTA_ERROR_RECONN_NEED_AUTH      = 20,  ///< 需要重新认证
    GTA_ERROR_RECONN_CONNECTED      = 21,  ///< 与服务器连接中

    // = 分发相关错误
    GTA_ERROR_QUOTE_LOGONFAILED     = 30  ///< 分发服务器登录失败
};

/// 网络状态定义.
enum NetState
{
    GTA_CONN_STATE_CONNECTING   = 0,   ///< 正在连接
    GTA_CONN_STATE_OPEN         = 1,   ///< 已连接
    GTA_CONN_STATE_CLOSING      = 2,   ///< 正在关闭
    GTA_CONN_STATE_CLOSED       = 3,    ///< 已关闭
    GTA_STATE_VERSION_DIFFERENCE = 4    /// <API与分发版本号不一致
};

/// 订阅模式定义.
enum SubscribeMode
{
    SUBSCRIBE_MODE_SUBSCRIBE    = 0,    ///< 订阅
    SUBSCRIBE_MODE_UNSUBSCRIBE  = 1     ///< 退订
};

/// 市场范围定义.
enum MarketRange
{
    MARKET_RANGE_ALL    = 0,    ///< 全市场
    MARKET_RANGE_PART   = 1     ///< 部分个股
};

/// 系统状态数据类型定义.
enum SysStateType
{
    SYS_STATE_TYPE_DELAY = 0, ///< 延迟信息数据
};

/// 快照源类型.
enum SnapDataSource
{
    SNAP_DATA_SOURCE_CACHE  = 0,    ///< 本地缓存快照
    SNAP_DATA_SOURCE_SERVER = 1     ///< 服务器快照
};

#endif // GTA_MARKET_SERVICE_API_STRUCT_H_
