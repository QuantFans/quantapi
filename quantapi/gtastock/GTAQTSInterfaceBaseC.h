//////////////////////////////////////////////////////////////////////////////
/// @file       GTAQTSInterfaceBaseC.h 
/// @brief      QTS行情接口C语言接口，按结构体返回数据，自动重连
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_INTERFACE_BASE_C_H_
#define GTA_QTS_INTERFACE_BASE_C_H_
#include "QTSDataType.h"
#include "QTSStruct.h"
#include "QTSDataFieldDefine.h"
extern "C"
{

/// 实时数据、连接状态回调函数，按结构体返回数据


/// 登陆状态返回
/// @param  errCode  -- 失败原因(用户过期、重复登陆)用户需对这两个进行处理
typedef void (*OnBaseLoginState)( RetCode errCode);
void GTA_API_EXPORT _CDECL SetOnBaseLoginState(OnBaseLoginState cbOnBaseLoginState);

/// 连接状态返回，连接成功/失败
/// @param  msgType      -- 消息类型
/// @param  errCode     -- 失败原因，成功时返回0
typedef void (*OnBaseConnectionState)(MsgType msgType, RetCode errCode);
void GTA_API_EXPORT _CDECL SetOnBaseConnectionState(OnBaseConnectionState cbOnBaseConnectionState);

/// 上交所L1静态数据订阅数据实时回调接口
/// @param  pRealSSEL1Static     -- 实时数据
typedef void (*OnBaseSubscribe_SSEL1_Static)(const SSEL1_Static* pRealSSEL1Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL1_Static(OnBaseSubscribe_SSEL1_Static cbOnBaseSubscribe_SSEL1_Static);

/// 上交所L1实时行情订阅数据实时回调接口
/// @param  pRealSSEL1Quotation  -- 实时数据
typedef void (*OnBaseSubscribe_SSEL1_Quotation)(const SSEL1_Quotation* pRealSSEL1Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL1_Quotation(OnBaseSubscribe_SSEL1_Quotation cbOnBaseSubscribe_SSEL1_Quotation);

/// 上交所L2静态数据订阅数据实时回调接口
/// @param  pRealSSEL2Static     -- 实时数据
typedef void (*OnBaseSubscribe_SSEL2_Static)(const SSEL2_Static* pRealSSEL2Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL2_Static(OnBaseSubscribe_SSEL2_Static cbOnBaseSubscribe_SSEL2_Static);

/// 上交所L2实时行情快照订阅数据实时回调接口
/// @param  pRealSSEL2Quotation  -- 实时数据
typedef void (*OnBaseSubscribe_SSEL2_Quotation)(const SSEL2_Quotation* pRealSSEL2Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL2_Quotation(OnBaseSubscribe_SSEL2_Quotation cbOnBaseSubscribe_SSEL2_Quotation);

/// 上交所L2指数行情订阅数据实时回调接口
/// @param  pRealSSEL2Index      -- 实时数据
typedef void (*OnBaseSubscribe_SSEL2_Index)(const SSEL2_Index* pRealSSEL2Index);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL2_Index(OnBaseSubscribe_SSEL2_Index cbOnBaseSubscribe_SSEL2_Index);

/// 上交所L2逐笔成交订阅数据实时回调接口
/// @param  pRealSSEL2Transaction    -- 实时数据
typedef void (*OnBaseSubscribe_SSEL2_Transaction)(const SSEL2_Transaction* pRealSSEL2Transaction);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL2_Transaction(OnBaseSubscribe_SSEL2_Transaction cbOnBaseSubscribe_SSEL2_Transaction);

/// 上交所L2虚拟集合竞价订阅数据实时回调接口
/// @param  pRealSSEL2Auction    -- 实时数据
typedef void (*OnBaseSubscribe_SSEL2_Auction)(const SSEL2_Auction* pRealSSEL2Auction);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL2_Auction(OnBaseSubscribe_SSEL2_Auction cbOnBaseSubscribe_SSEL2_Auction);

/// 上交所L2市场总览订阅数据实时回调接口
/// @param  pRealSSEL2Overview   -- 实时数据
typedef void (*OnBaseSubscribe_SSEL2_Overview)(const SSEL2_Overview* pRealSSEL2Overview);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL2_Overview(OnBaseSubscribe_SSEL2_Overview cbOnBaseSubscribe_SSEL2_Overview);

/// 上交所个股期权静态数据订阅数据实时回调接口
/// @param  pRealSSEIOL1Static   -- 实时数据
typedef void (*OnBaseSubscribe_SSEIOL1_Static)(const SSEIOL1_Static* pRealSSEIOL1Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEIOL1_Static(OnBaseSubscribe_SSEIOL1_Static cbOnBaseSubscribe_SSEIOL1_Static);

/// 上交所个股期权实时行情订阅数据实时回调接口
/// @param  pRealSSEIOL1Quotation    -- 实时数据
typedef void (*OnBaseSubscribe_SSEIOL1_Quotation)(const SSEIOL1_Quotation* pRealSSEIOL1Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEIOL1_Quotation(OnBaseSubscribe_SSEIOL1_Quotation cbOnBaseSubscribe_SSEIOL1_Quotation);

/// 深交所L1静态数据订阅数据实时回调接口
/// @param  pRealSZSEL1Static    -- 实时数据
typedef void (*OnBaseSubscribe_SZSEL1_Static)(const SZSEL1_Static* pRealSZSEL1Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL1_Static(OnBaseSubscribe_SZSEL1_Static cbOnBaseSubscribe_SZSEL1_Static);

/// 深交所L1实时行情订阅数据实时回调接口
/// @param  pRealSZSEL1Quotation -- 实时数据
typedef void (*OnBaseSubscribe_SZSEL1_Quotation)(const SZSEL1_Quotation* pRealSZSEL1Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL1_Quotation(OnBaseSubscribe_SZSEL1_Quotation cbOnBaseSubscribe_SZSEL1_Quotation);

/// 深交所L2静态数据订阅数据实时回调接口
/// @param  pRealSZSEL2Static    -- 实时数据
typedef void (*OnBaseSubscribe_SZSEL2_Static)(const SZSEL2_Static* pRealSZSEL2Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL2_Static(OnBaseSubscribe_SZSEL2_Static cbOnBaseSubscribe_SZSEL2_Static);

/// 深交所L2实时行情订阅数据实时回调接口
/// @param  pRealSZSEL2Quotation -- 实时数据
typedef void (*OnBaseSubscribe_SZSEL2_Quotation)(const SZSEL2_Quotation* pRealSZSEL2Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL2_Quotation(OnBaseSubscribe_SZSEL2_Quotation cbOnBaseSubscribe_SZSEL2_Quotation);

/// 深交所L2证券状态订阅数据实时回调接口
/// @param  pRealSZSEL2Status    -- 实时数据
typedef void (*OnBaseSubscribe_SZSEL2_Status)(const SZSEL2_Status* pRealSZSEL2Status);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL2_Status(OnBaseSubscribe_SZSEL2_Status cbOnBaseSubscribe_SZSEL2_Status);

/// 深交所L2指数行情订阅数据实时回调接口
/// @param  pRealSZSEL2Index     -- 实时数据
typedef void (*OnBaseSubscribe_SZSEL2_Index)(const SZSEL2_Index* pRealSZSEL2Index);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL2_Index(OnBaseSubscribe_SZSEL2_Index cbOnBaseSubscribe_SZSEL2_Index);

/// 深交所L2逐笔委托订阅数据实时回调接口
/// @param  pRealSZSEL2Order     -- 实时数据
typedef void (*OnBaseSubscribe_SZSEL2_Order)(const SZSEL2_Order* pRealSZSEL2Order);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL2_Order(OnBaseSubscribe_SZSEL2_Order cbOnBaseSubscribe_SZSEL2_Order);

/// 深交所L2逐笔成交订阅数据实时回调接口
/// @param  pRealSZSEL2Transaction   -- 实时数据
typedef void (*OnBaseSubscribe_SZSEL2_Transaction)(const SZSEL2_Transaction* pRealSZSEL2Transaction);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL2_Transaction(OnBaseSubscribe_SZSEL2_Transaction cbOnBaseSubscribe_SZSEL2_Transaction);

/// 中金所静态数据订阅数据实时回调接口
/// @param  pRealCFFEXL2Static   -- 实时数据
typedef void (*OnBaseSubscribe_CFFEXL2_Static)(const CFFEXL2_Static* pRealCFFEXL2Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_CFFEXL2_Static(OnBaseSubscribe_CFFEXL2_Static cbOnBaseSubscribe_CFFEXL2_Static);

/// 中金所L2实时行情订阅数据实时回调接口
/// @param  pRealCFFEXL2Quotation    -- 实时数据
typedef void (*OnBaseSubscribe_CFFEXL2_Quotation)(const CFFEXL2_Quotation* pRealCFFEXL2Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_CFFEXL2_Quotation(OnBaseSubscribe_CFFEXL2_Quotation cbOnBaseSubscribe_CFFEXL2_Quotation);

/// 郑商所静态数据订阅数据实时回调接口
/// @param  pRealCZCEL1Static    -- 实时数据
typedef void (*OnBaseSubscribe_CZCEL1_Static)(const CZCEL1_Static* pRealCZCEL1Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_CZCEL1_Static(OnBaseSubscribe_CZCEL1_Static cbOnBaseSubscribe_CZCEL1_Static);

/// 郑商所实时行情订阅数据实时回调接口
/// @param  pRealCZCEL1Quotation -- 实时数据
typedef void (*OnBaseSubscribe_CZCEL1_Quotation)(const CZCEL1_Quotation* pRealCZCEL1Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_CZCEL1_Quotation(OnBaseSubscribe_CZCEL1_Quotation cbOnBaseSubscribe_CZCEL1_Quotation);

/// 大商所L1静态数据订阅数据实时回调接口
/// @param  pRealDCEL1Static     -- 实时数据
typedef void (*OnBaseSubscribe_DCEL1_Static)(const DCEL1_Static* pRealDCEL1Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL1_Static(OnBaseSubscribe_DCEL1_Static cbOnBaseSubscribe_DCEL1_Static);

/// 大商所L1深度行情订阅数据实时回调接口
/// @param  pRealDCEL1Quotation  -- 实时数据
typedef void (*OnBaseSubscribe_DCEL1_Quotation)(const DCEL1_Quotation* pRealDCEL1Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL1_Quotation(OnBaseSubscribe_DCEL1_Quotation cbOnBaseSubscribe_DCEL1_Quotation);

/// 大商所L1套利深度行情订阅数据实时回调接口
/// @param  pRealDCEL1ArbiQuotation  -- 实时数据
typedef void (*OnBaseSubscribe_DCEL1_ArbiQuotation)(const DCEL1_ArbiQuotation* pRealDCEL1ArbiQuotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL1_ArbiQuotation(OnBaseSubscribe_DCEL1_ArbiQuotation cbOnBaseSubscribe_DCEL1_ArbiQuotation);

/// 大商所L2静态数据订阅数据实时回调接口
/// @param  pRealDCEL2Static     -- 实时数据
typedef void (*OnBaseSubscribe_DCEL2_Static)(const DCEL2_Static* pRealDCEL2Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL2_Static(OnBaseSubscribe_DCEL2_Static cbOnBaseSubscribe_DCEL2_Static);

/// 大商所L2最优深度行情订阅数据实时回调接口
/// @param  pRealDCEL2Quotation  -- 实时数据
typedef void (*OnBaseSubscribe_DCEL2_Quotation)(const DCEL2_Quotation* pRealDCEL2Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL2_Quotation(OnBaseSubscribe_DCEL2_Quotation cbOnBaseSubscribe_DCEL2_Quotation);

/// 大商所L2最优套利深度行情订阅数据实时回调接口
/// @param  pRealDCEL2ArbiQuotation  -- 实时数据
typedef void (*OnBaseSubscribe_DCEL2_ArbiQuotation)(const DCEL2_ArbiQuotation* pRealDCEL2ArbiQuotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL2_ArbiQuotation(OnBaseSubscribe_DCEL2_ArbiQuotation cbOnBaseSubscribe_DCEL2_ArbiQuotation);

/// 大商所L2实时结算价订阅数据实时回调接口
/// @param  pRealDCEL2RealTimePrice  -- 实时数据
typedef void (*OnBaseSubscribe_DCEL2_RealTimePrice)(const DCEL2_RealTimePrice* pRealDCEL2RealTimePrice);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL2_RealTimePrice(OnBaseSubscribe_DCEL2_RealTimePrice cbOnBaseSubscribe_DCEL2_RealTimePrice);

/// 大商所L2委托统计行情订阅数据实时回调接口
/// @param  pRealDCEL2OrderStatistic -- 实时数据
typedef void (*OnBaseSubscribe_DCEL2_OrderStatistic)(const DCEL2_OrderStatistic* pRealDCEL2OrderStatistic);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL2_OrderStatistic(OnBaseSubscribe_DCEL2_OrderStatistic cbOnBaseSubscribe_DCEL2_OrderStatistic);

/// 大商所L2分价成交量行情订阅数据实时回调接口
/// @param  pRealDCEL2MarchPriceQty  -- 实时数据
typedef void (*OnBaseSubscribe_DCEL2_MarchPriceQty)(const DCEL2_MarchPriceQty* pRealDCEL2MarchPriceQty);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL2_MarchPriceQty(OnBaseSubscribe_DCEL2_MarchPriceQty cbOnBaseSubscribe_DCEL2_MarchPriceQty);

/// 上期所静态数据订阅数据实时回调接口
/// @param  pRealSHFEL1Static    -- 实时数据
typedef void (*OnBaseSubscribe_SHFEL1_Static)(const SHFEL1_Static* pRealSHFEL1Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SHFEL1_Static(OnBaseSubscribe_SHFEL1_Static cbOnBaseSubscribe_SHFEL1_Static);

/// 上期所实时行情订阅数据实时回调接口
/// @param  pRealSHFEL1Quotation -- 实时数据
typedef void (*OnBaseSubscribe_SHFEL1_Quotation)(const SHFEL1_Quotation* pRealSHFEL1Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SHFEL1_Quotation(OnBaseSubscribe_SHFEL1_Quotation cbOnBaseSubscribe_SHFEL1_Quotation);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 行情系统服务接口，连接服务器进行认证，订阅数据，查询快照.

/// 基础API环境初始化
void GTA_API_EXPORT _CDECL BaseInit();

/// 基础API环境反初始化
void GTA_API_EXPORT _CDECL BaseUninit();


/// 设置超时时间，设置即时生效，同步调用的超时时间
/// @param  nSenond     -- 超时时间，单位秒
void GTA_API_EXPORT _CDECL BaseSetTimeout(int nSecond = TIMEOUT_DEFAULT);

/// 注册行情服务器地址，可注册多个不同地址，实现高可用，连接顺序为顺序连接，断线时先重连当前使用地址
/// @param  pIP         -- 服务器地址.
/// @param  uPort       -- 服务器端口.
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseRegisterService(const char* pIP, unsigned short uPort);

/// 连接行情服务器，发送用户认证信息，同步请求，调用前需先
/// @param  pUserName   -- 账号名称
/// @param  pPassword   -- 账号密码，加密后密码
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseLogin(const char* pUserName, const char* pPassword);

/// 获取行情订阅服务器地址信息
/// @param  ppServerAddrs               -- 存放服务器地址对象，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode      -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseGetServerAddr(ServerState** ppServerAddrs, int* pSize);

/// 获取有权限的数据类型.
/// @param  ppDataTypeList  -- 数据类型指针，数据大小即为有权限的数据个数，需调用BaseReleaseValue释放内存
/// @param  pSize           -- 返回数据个数
/// @return RetCode         -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseGetMsgTypeList(MsgType** ppDataTypeList, int* pSize);

/// 订阅行情，重复订阅同一个数据多次时取并集
/// @param  msgType     -- 需要订阅的数据类型
/// @param  pCodeList   -- 个股订阅列表，以“,”分割，末尾必须以\0结束，为NULL时订阅全市场
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseSubscribe(MsgType msgType, char* pCodeList = NULL);

/// 取消订阅
/// @param  msgType     -- 需要取消订阅的数据类型
/// @param  pCodeList   -- 取消个股列表，以“,”分割，末尾必须以\0结束，为NULL时取消所有代码
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseUnsubscribe(MsgType msgType, char* pCodeList = NULL);

/// 取消所有订阅信息
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseUnsubscribeAll();

/// 获取股票列表
/// @param  pMarketTag  -- 市场标识，以“,”分割多个市场标识，末尾必须以\0结束，不允许为NULL
/// @param  ppStockList -- 返回的个股代码列表，带市场标志，需调用BaseReleaseValue释放内存
/// @param  pSize       -- 返回数据个数
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseGetStockList(char* pMarketTag, StockSymbol** ppStockList, int* pSize);

/// 查询上交所L1静态数据
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSSEL1Static     -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize               -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL1_Static(char* pCodeList, SSEL1_Static** ppSnapSSEL1Static, int* pSize);

/// 查询上交所L1实时行情
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSSEQuotation     -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL1_Quotation(char* pCodeList, SSEL1_Quotation** ppSnapSSEQuotation, int* pSize);

/// 查询上交所L2静态数据
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSSEStatic        -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL2_Static(char* pCodeList, SSEL2_Static** ppSnapSSEL2Static, int* pSize);

/// 查询上交所L2实时行情快照
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSSEL2Quotation    -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL2_Quotation(char* pCodeList, SSEL2_Quotation** ppSnapSSEL2Quotation, int* pSize);

/// 查询上交所L2指数行情
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSSEL2Index        -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL2_Index(char* pCodeList, SSEL2_Index** ppSnapSSEL2Index, int* pSize);

/// 查询上交所L2逐笔成交
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSSEL2Transation   -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL2_Transaction(char* pCodeList, SSEL2_Transaction** ppSnapSSEL2Transation, int* pSize);

/// 查询上交所L2虚拟集合竞价
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSSEL2Auction    -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL2_Auction(char* pCodeList, SSEL2_Auction** ppSnapSSEL2Auction, int* pSize);

/// 查询上交所L2市场总览
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSSEL2Overview   -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL2_Overview(char* pCodeList, SSEL2_Overview** ppSnapSSEL2Overview, int* pSize);

/// 查询上交所个股期权静态数据
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSSEIOL1Static   -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEIOL1_Static(char* pCodeList, SSEIOL1_Static** ppSnapSSEIOL1Static, int* pSize);

/// 查询上交所个股期权实时行情
/// @param  pCodeList               -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSSEIOL1Quotation    -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode                 -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEIOL1_Quotation(char* pCodeList, SSEIOL1_Quotation** ppSnapSSEIOL1Quotation, int* pSize);

/// 查询深交所L1静态数据
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSZSEL1Static    -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL1_Static(char* pCodeList, SZSEL1_Static** ppSnapSZSEL1Static, int* pSize);

/// 查询深交所L1实时行情
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSZSEL1Quotation -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL1_Quotation(char* pCodeList, SZSEL1_Quotation** ppSnapSZSEL1Quotation, int* pSize);

/// 查询深交所L2静态数据
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSZSEL2Static    -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL2_Static(char* pCodeList, SZSEL2_Static** ppSnapSZSEL2Static, int* pSize);

/// 查询深交所L2实时行情
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSZSEL2Quotation    -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL2_Quotation(char* pCodeList, SZSEL2_Quotation** ppSnapSZSEL2Quotation, int* pSize);

/// 查询深交所L2证券状态
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSZSEL2StockStatus  -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL2_Status(char* pCodeList, SZSEL2_Status** ppSnapSZSEL2StockStatus, int* pSize);

/// 查询深交所L2指数行情
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSZSEL2Index        -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL2_Index(char* pCodeList, SZSEL2_Index** ppSnapSZSEL2Index, int* pSize);

/// 查询深交所L2逐笔委托
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSZSEL2Order        -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL2_Order(char* pCodeList, SZSEL2_Order** ppSnapSZSEL2Order, int* pSize);

/// 查询深交所L2逐笔成交
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSZSEL2Transaction  -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL2_Transaction(char* pCodeList, SZSEL2_Transaction** ppSnapSZSEL2Transaction, int* pSize);

/// 查询中金所静态数据
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapCFFEXL2Static       -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_CFFEXL2_Static(char* pCodeList, CFFEXL2_Static** ppSnapCFFEXL2Static, int* pSize);

/// 查询中金所L2实时行情
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapCFFEXL2Quotation    -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_CFFEXL2_Quotation(char* pCodeList, CFFEXL2_Quotation** ppSnapCFFEXL2Quotation, int* pSize);


/// 查询郑商所静态数据
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapCZCEL1Static    -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_CZCEL1_Static(char* pCodeList, CZCEL1_Static** ppSnapCZCEL1Static, int* pSize);

/// 查询郑商所实时行情
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapCZCEL1Quotation -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_CZCEL1_Quotation(char* pCodeList, CZCEL1_Quotation** ppSnapCZCEL1Quotation, int* pSize);

/// 查询大商所L1静态数据
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapDCEL1Static     -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL1_Static(char* pCodeList, DCEL1_Static** ppSnapDCEL1Static, int* pSize);

/// 查询大商所L1深度行情
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapDCEL1Quotation  -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL1_Quotation(char* pCodeList, DCEL1_Quotation** ppSnapDCEL1Quotation, int* pSize);

/// 查询大商所L1套利深度行情
/// @param  pCodeList               -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapDCEL1ArbiQuotation  -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode                 -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL1_ArbiQuotation(char* pCodeList, DCEL1_ArbiQuotation** ppSnapDCEL1ArbiQuotation, int* pSize);

/// 查询大商所L2静态数据
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapDCEL2Static     -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL2_Static(char* pCodeList, DCEL2_Static** ppSnapDCEL2Static, int* pSize);

/// 查询大商所L2最优深度行情
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapDCEL2Quotation  -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode              -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL2_Quotation(char* pCodeList, DCEL2_Quotation** ppSnapDCEL2Quotation, int* pSize);

/// 查询大商所L2最优套利深度行情
/// @param  pCodeList               -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapDCEL2ArbiQuotation  -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode                 -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL2_ArbiQuotation(char* pCodeList, DCEL2_ArbiQuotation** ppSnapDCEL2ArbiQuotation, int* pSize);

/// 查询大商所L2实时结算价
/// @param  pCodeList               -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapDCEL2RealTimePrice  -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode                 -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL2_RealTimePrice(char* pCodeList, DCEL2_RealTimePrice** ppSnapDCEL2RealTimePrice, int* pSize);

/// 查询大商所L2委托统计行情
/// @param  pCodeList               -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapDCEL2OrderStatistic -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                       -- 返回数据个数
/// @return RetCode                 -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL2_OrderStatistic(char* pCodeList, DCEL2_OrderStatistic** ppSnapDCEL2OrderStatistic, int* pSize);

/// 查询大商所L2分价成交量行情
/// @param  pCodeList               -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapDCEL2MarchPriceQty  -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize                   -- 返回数据个数
/// @return RetCode                 -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL2_MarchPriceQty(char* pCodeList, DCEL2_MarchPriceQty** ppSnapDCEL2MarchPriceQty, int* pSize);

/// 查询上期所静态数据
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSHFEL1Static    -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize               -- 返回数据个数
/// @return RetCode             -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SHFEL1_Static(char* pCodeList, SHFEL1_Static** ppSnapSHFEL1Static, int* pSize);

/// 查询上期所实时行情
/// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
/// @param  ppSnapSHFEL1Quotation -- 快照数据列表，需调用BaseReleaseValue释放内存
/// @param  pSize               -- 返回数据个数
/// @return RetCode             -- 错误代码
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SHFEL1_Quotation(char* pCodeList, SHFEL1_Quotation** ppSnapSHFEL1Quotation, int* pSize);

/// 释放对象内存
/// @param  ppDataValue         -- 需释放内存
void GTA_API_EXPORT _CDECL BaseReleaseValue(void** ppDataValue);

};

#endif // GTA_QTS_INTERFACE_BASE_C_H_
