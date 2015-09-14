//////////////////////////////////////////////////////////////////////////////
/// @file       GTAQTSInterfaceBase.h 
/// @brief      QTS行情接口定义，按结构体返回数据，自动重连
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_INTERFACE_BASE_H_
#define GTA_QTS_INTERFACE_BASE_H_
#include "QTSDataType.h"
#include "QTSStruct.h"
#include "QTSDataFieldDefine.h"

/// 实时数据、连接状态回调接口，按结构体返回数据
class GTA_API_EXPORT IGTAQTSCallbackBase
{
public:
    /// 登陆状态返回
    /// @param  errCode  -- 失败原因(用户过期、重复登陆)用户需对这两个进行处理
    virtual void OnLoginState( RetCode errCode){}

    /// 连接状态返回，连接成功/失败
    /// @param  msgType      -- 消息类型
    /// @param  errCode     -- 失败原因，成功时返回0
    virtual void OnConnectionState(MsgType msgType, RetCode errCode){}

    /// 上交所L1静态数据订阅数据实时回调接口
    /// @param  RealSSEL1Static     -- 实时数据
    virtual void OnSubscribe_SSEL1_Static(const SSEL1_Static& RealSSEL1Static){}

    /// 上交所L1实时行情订阅数据实时回调接口
    /// @param  RealSSEL1Quotation  -- 实时数据
    virtual void OnSubscribe_SSEL1_Quotation(const SSEL1_Quotation& RealSSEL1Quotation){}

    /// 上交所L2静态数据订阅数据实时回调接口
    /// @param  RealSSEL2Static     -- 实时数据
    virtual void OnSubscribe_SSEL2_Static(const SSEL2_Static& RealSSEL2Static){}

    /// 上交所L2实时行情快照订阅数据实时回调接口
    /// @param  RealSSEL2Quotation  -- 实时数据
    virtual void OnSubscribe_SSEL2_Quotation(const SSEL2_Quotation& RealSSEL2Quotation){}

    /// 上交所L2指数行情订阅数据实时回调接口
    /// @param  RealSSEL2Index      -- 实时数据
    virtual void OnSubscribe_SSEL2_Index(const SSEL2_Index& RealSSEL2Index){}

    /// 上交所L2逐笔成交订阅数据实时回调接口
    /// @param  RealSSEL2Transaction    -- 实时数据
    virtual void OnSubscribe_SSEL2_Transaction(const SSEL2_Transaction& RealSSEL2Transaction){}

    /// 上交所L2虚拟集合竞价订阅数据实时回调接口
    /// @param  RealSSEL2Auction    -- 实时数据
    virtual void OnSubscribe_SSEL2_Auction(const SSEL2_Auction& RealSSEL2Auction){}

    /// 上交所L2市场总览订阅数据实时回调接口
    /// @param  RealSSEL2Overview   -- 实时数据
    virtual void OnSubscribe_SSEL2_Overview(const SSEL2_Overview& RealSSEL2Overview){}

    /// 上交所个股期权静态数据订阅数据实时回调接口
    /// @param  RealSSEIOL1Static   -- 实时数据
    virtual void OnSubscribe_SSEIOL1_Static(const SSEIOL1_Static& RealSSEIOL1Static){}

    /// 上交所个股期权实时行情订阅数据实时回调接口
    /// @param  RealSSEIOL1Quotation    -- 实时数据
    virtual void OnSubscribe_SSEIOL1_Quotation(const SSEIOL1_Quotation& RealSSEIOL1Quotation){}

    /// 深交所L1静态数据订阅数据实时回调接口
    /// @param  RealSZSEL1Static    -- 实时数据
    virtual void OnSubscribe_SZSEL1_Static(const SZSEL1_Static& RealSZSEL1Static){}

    /// 深交所L1实时行情订阅数据实时回调接口
    /// @param  RealSZSEL1Quotation -- 实时数据
    virtual void OnSubscribe_SZSEL1_Quotation(const SZSEL1_Quotation& RealSZSEL1Quotation){}

    /// 深交所L2静态数据订阅数据实时回调接口
    /// @param  RealSZSEL2Static    -- 实时数据
    virtual void OnSubscribe_SZSEL2_Static(const SZSEL2_Static& RealSZSEL2Static){}

    /// 深交所L2实时行情订阅数据实时回调接口
    /// @param  RealSZSEL2Quotation -- 实时数据
    virtual void OnSubscribe_SZSEL2_Quotation(const SZSEL2_Quotation& RealSZSEL2Quotation){}

    /// 深交所L2证券状态订阅数据实时回调接口
    /// @param  RealSZSEL2Status    -- 实时数据
    virtual void OnSubscribe_SZSEL2_Status(const SZSEL2_Status& RealSZSEL2Status){}

    /// 深交所L2指数行情订阅数据实时回调接口
    /// @param  RealSZSEL2Index     -- 实时数据
    virtual void OnSubscribe_SZSEL2_Index(const SZSEL2_Index& RealSZSEL2Index){}

    /// 深交所L2逐笔委托订阅数据实时回调接口
    /// @param  RealSZSEL2Order     -- 实时数据
    virtual void OnSubscribe_SZSEL2_Order(const SZSEL2_Order& RealSZSEL2Order){}

    /// 深交所L2逐笔成交订阅数据实时回调接口
    /// @param  RealSZSEL2Transaction   -- 实时数据
    virtual void OnSubscribe_SZSEL2_Transaction(const SZSEL2_Transaction& RealSZSEL2Transaction){}

    /// 中金所静态数据订阅数据实时回调接口
    /// @param  RealCFFEXL2Static   -- 实时数据
    virtual void OnSubscribe_CFFEXL2_Static(const CFFEXL2_Static& RealCFFEXL2Static){}

    /// 中金所L2实时行情订阅数据实时回调接口
    /// @param  RealCFFEXL2Quotation    -- 实时数据
    virtual void OnSubscribe_CFFEXL2_Quotation(const CFFEXL2_Quotation& RealCFFEXL2Quotation){}

    /// 郑商所静态数据订阅数据实时回调接口
    /// @param  RealCZCEL1Static    -- 实时数据
    virtual void OnSubscribe_CZCEL1_Static(const CZCEL1_Static& RealCZCEL1Static){}

    /// 郑商所实时行情订阅数据实时回调接口
    /// @param  RealCZCEL1Quotation -- 实时数据
    virtual void OnSubscribe_CZCEL1_Quotation(const CZCEL1_Quotation& RealCZCEL1Quotation){}

    /// 大商所L1静态数据订阅数据实时回调接口
    /// @param  RealDCEL1Static     -- 实时数据
    virtual void OnSubscribe_DCEL1_Static(const DCEL1_Static& RealDCEL1Static){}

    /// 大商所L1深度行情订阅数据实时回调接口
    /// @param  RealDCEL1Quotation  -- 实时数据
    virtual void OnSubscribe_DCEL1_Quotation(const DCEL1_Quotation& RealDCEL1Quotation){}

    /// 大商所L1套利深度行情订阅数据实时回调接口
    /// @param  RealDCEL1ArbiQuotation  -- 实时数据
    virtual void OnSubscribe_DCEL1_ArbiQuotation(const DCEL1_ArbiQuotation& RealDCEL1ArbiQuotation){}

    /// 大商所L2静态数据订阅数据实时回调接口
    /// @param  RealDCEL2Static     -- 实时数据
    virtual void OnSubscribe_DCEL2_Static(const DCEL2_Static& RealDCEL2Static){}

    /// 大商所L2最优深度行情订阅数据实时回调接口
    /// @param  RealDCEL2Quotation  -- 实时数据
    virtual void OnSubscribe_DCEL2_Quotation(const DCEL2_Quotation& RealDCEL2Quotation){}

    /// 大商所L2最优套利深度行情订阅数据实时回调接口
    /// @param  RealDCEL2ArbiQuotation  -- 实时数据
    virtual void OnSubscribe_DCEL2_ArbiQuotation(const DCEL2_ArbiQuotation& RealDCEL2ArbiQuotation){}

    /// 大商所L2实时结算价订阅数据实时回调接口
    /// @param  RealDCEL2RealTimePrice  -- 实时数据
    virtual void OnSubscribe_DCEL2_RealTimePrice(const DCEL2_RealTimePrice& RealDCEL2RealTimePrice){}

    /// 大商所L2委托统计行情订阅数据实时回调接口
    /// @param  RealDCEL2OrderStatistic -- 实时数据
    virtual void OnSubscribe_DCEL2_OrderStatistic(const DCEL2_OrderStatistic& RealDCEL2OrderStatistic){}

    /// 大商所L2分价成交量行情订阅数据实时回调接口
    /// @param  RealDCEL2MarchPriceQty  -- 实时数据
    virtual void OnSubscribe_DCEL2_MarchPriceQty(const DCEL2_MarchPriceQty& RealDCEL2MarchPriceQty){}

    /// 上期所静态数据订阅数据实时回调接口
    /// @param  RealSHFEL1Static    -- 实时数据
    virtual void OnSubscribe_SHFEL1_Static(const SHFEL1_Static& RealSHFEL1Static){}

    /// 上期所实时行情订阅数据实时回调接口
    /// @param  RealSHFEL1Quotation -- 实时数据
    virtual void OnSubscribe_SHFEL1_Quotation(const SHFEL1_Quotation& RealSHFEL1Quotation){}
};



/// 行情系统服务接口，连接服务器进行认证，订阅数据，查询快照.
class GTA_API_EXPORT IGTAQTSApiBase
{
public:
    virtual ~IGTAQTSApiBase(){};
public:
    /// 创建一个实例.所有实例都必须通过本接口生成.
    /// @param  CallBack    -- 连接回调函数，通知连接状态
    /// @return NULL        -- 创建实例失败
    static IGTAQTSApiBase* CreateInstance(IGTAQTSCallbackBase& CallBack);

    /// 释放一个实例,该实例是通过CreateInstance生成的.
    /// @param  pInstance   -- 实例对象指针.
    static void ReleaseInstance(IGTAQTSApiBase* pInstance);

    /// 设置超时时间，设置即时生效，同步调用的超时时间
    /// @param  nSenond     -- 超时时间，单位秒
    virtual void SetTimeout(int nSecond = TIMEOUT_DEFAULT) = 0;

    /// 注册行情服务器地址，可注册多个不同地址，实现高可用，连接顺序为顺序连接，断线时先重连当前使用地址
    /// @param  pIP         -- 服务器地址.
    /// @param  uPort       -- 服务器端口.
    /// @return RetCode     -- 错误代码
    virtual RetCode RegisterService(const char* pIP, unsigned short uPort) = 0;

    /// 连接行情服务器，发送用户认证信息，同步请求，调用前需先
    /// @param  pUserName   -- 账号名称
    /// @param  pPassword   -- 账号密码，加密后密码
    /// @return RetCode     -- 错误代码
    virtual RetCode Login(const char* pUserName, const char* pPassword) = 0;

    /// 获取行情订阅服务器地址信息
    /// @param  ServerStates    -- 存放服务器地址对象
    /// @return RetCode         -- 错误代码
    virtual RetCode GetConnectState(CDataBuffer<ServerState>& ServerStates) = 0;

    /// 获取有权限的数据类型.
    /// @param  DataTypeList-- 数据类型指针，数据大小即为有权限的数据个数
    /// @return RetCode     -- 错误代码
    virtual RetCode GetDataTypeList(CDataBuffer<MsgType>& DataTypeList) = 0;

    /// 订阅行情，重复订阅同一个数据多次时取并集
    /// @param  msgType     -- 需要订阅的数据类型
    /// @param  pCodeList   -- 个股订阅列表，以“,”分割，末尾必须以\0结束，为NULL时订阅全市场
    /// @return RetCode     -- 错误代码
    virtual RetCode Subscribe(MsgType msgType, char* pCodeList = NULL) = 0;

    /// 取消订阅
    /// @param  msgType     -- 需要取消订阅的数据类型
    /// @param  pCodeList   -- 取消个股列表，以“,”分割，末尾必须以\0结束，为NULL时取消所有代码
    /// @return RetCode     -- 错误代码
    virtual RetCode Unsubscribe(MsgType msgType, char* pCodeList = NULL) = 0;

    /// 取消所有订阅信息
    /// @return RetCode     -- 错误代码
    virtual RetCode UnsubscribeAll() = 0;

    /// 获取股票列表
    /// @param  pMarketTag  -- 市场标识，以“,”分割多个市场标识，末尾必须以\0结束，不允许为NULL
    /// @param  StockList   -- 返回的个股代码列表，带市场标志。
    /// @return RetCode     -- 错误代码
    virtual RetCode GetStockList(char* pMarketTag, CDataBuffer<StockSymbol>& StockList) = 0;

    /// 查询上交所L1静态数据
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSSEL1Static     -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SSEL1_Static(char* pCodeList, CDataBuffer<SSEL1_Static>& SnapSSEL1Static) = 0;

    /// 查询上交所L1实时行情
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSSEQuotation     -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SSEL1_Quotation(char* pCodeList, CDataBuffer<SSEL1_Quotation>& SnapSSEQuotation) = 0;

    /// 查询上交所L2静态数据
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSSEStatic        -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SSEL2_Static(char* pCodeList, CDataBuffer<SSEL2_Static>& SnapSSEL2Static) = 0;

    /// 查询上交所L2实时行情快照
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSSEL2Quotation    -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SSEL2_Quotation(char* pCodeList, CDataBuffer<SSEL2_Quotation>& SnapSSEL2Quotation) = 0;

    /// 查询上交所L2指数行情
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSSEL2Index        -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SSEL2_Index(char* pCodeList, CDataBuffer<SSEL2_Index>& SnapSSEL2Index) = 0;

    /// 查询上交所L2逐笔成交
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSSEL2Transation   -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SSEL2_Transaction(char* pCodeList, CDataBuffer<SSEL2_Transaction>& SnapSSEL2Transation) = 0;

    /// 查询上交所L2虚拟集合竞价
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSSEL2Auction    -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SSEL2_Auction(char* pCodeList, CDataBuffer<SSEL2_Auction>& SnapSSEL2Auction) = 0;

    /// 查询上交所L2市场总览
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSSEL2Overview   -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SSEL2_Overview(char* pCodeList, CDataBuffer<SSEL2_Overview>& SnapSSEL2Overview) = 0;

    /// 查询上交所个股期权静态数据
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSSEIOL1Static   -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SSEIOL1_Static(char* pCodeList, CDataBuffer<SSEIOL1_Static>& SnapSSEIOL1Static) = 0;

    /// 查询上交所个股期权实时行情
    /// @param  pCodeList               -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSSEIOL1Quotation    -- 快照数据列表
    /// @return RetCode                 -- 错误代码
    virtual RetCode QuerySnap_SSEIOL1_Quotation(char* pCodeList, CDataBuffer<SSEIOL1_Quotation>& SnapSSEIOL1Quotation) = 0;

    /// 查询深交所L1静态数据
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSZSEL1Static    -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SZSEL1_Static(char* pCodeList, CDataBuffer<SZSEL1_Static>& SnapSZSEL1Static) = 0;

    /// 查询深交所L1实时行情
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSZSEL1Quotation -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SZSEL1_Quotation(char* pCodeList, CDataBuffer<SZSEL1_Quotation>& SnapSZSEL1Quotation) = 0;

    /// 查询深交所L2静态数据
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSZSEL2Static    -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SZSEL2_Static(char* pCodeList, CDataBuffer<SZSEL2_Static>& SnapSZSEL2Static) = 0;

    /// 查询深交所L2实时行情
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSZSEL2Quotation    -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SZSEL2_Quotation(char* pCodeList, CDataBuffer<SZSEL2_Quotation>& SnapSZSEL2Quotation) = 0;

    /// 查询深交所L2证券状态
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSZSEL2StockStatus  -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SZSEL2_Status(char* pCodeList, CDataBuffer<SZSEL2_Status>& SnapSZSEL2StockStatus) = 0;

    /// 查询深交所L2指数行情
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSZSEL2Index        -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SZSEL2_Index(char* pCodeList, CDataBuffer<SZSEL2_Index>& SnapSZSEL2Index) = 0;

    /// 查询深交所L2逐笔委托
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSZSEL2Order        -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SZSEL2_Order(char* pCodeList, CDataBuffer<SZSEL2_Order>& SnapSZSEL2Order) = 0;

    /// 查询深交所L2逐笔成交
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSZSEL2Transaction  -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SZSEL2_Transaction(char* pCodeList, CDataBuffer<SZSEL2_Transaction>& SnapSZSEL2Transaction) = 0;

    /// 查询中金所静态数据
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapCFFEXL2Static       -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_CFFEXL2_Static(char* pCodeList, CDataBuffer<CFFEXL2_Static>& SnapCFFEXL2Static) = 0;

    /// 查询中金所L2实时行情
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapCFFEXL2Quotation    -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_CFFEXL2_Quotation(char* pCodeList, CDataBuffer<CFFEXL2_Quotation>& SnapCFFEXL2Quotation) = 0;

    /// 查询郑商所静态数据
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapCZCEL1Static    -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_CZCEL1_Static(char* pCodeList, CDataBuffer<CZCEL1_Static>& SnapCZCEL1Static) = 0;

    /// 查询郑商所实时行情
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapCZCEL1Quotation -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_CZCEL1_Quotation(char* pCodeList, CDataBuffer<CZCEL1_Quotation>& SnapCZCEL1Quotation) = 0;

    /// 查询大商所L1静态数据
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapDCEL1Static     -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_DCEL1_Static(char* pCodeList, CDataBuffer<DCEL1_Static>& SnapDCEL1Static) = 0;

    /// 查询大商所L1深度行情
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapDCEL1Quotation  -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_DCEL1_Quotation(char* pCodeList, CDataBuffer<DCEL1_Quotation>& SnapDCEL1Quotation) = 0;

    /// 查询大商所L1套利深度行情
    /// @param  pCodeList               -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapDCEL1ArbiQuotation  -- 快照数据列表
    /// @return RetCode                 -- 错误代码
    virtual RetCode QuerySnap_DCEL1_ArbiQuotation(char* pCodeList, CDataBuffer<DCEL1_ArbiQuotation>& SnapDCEL1ArbiQuotation) = 0;

    /// 查询大商所L2静态数据
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapDCEL2Static     -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_DCEL2_Static(char* pCodeList, CDataBuffer<DCEL2_Static>& SnapDCEL2Static) = 0;

    /// 查询大商所L2最优深度行情
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapDCEL2Quotation  -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_DCEL2_Quotation(char* pCodeList, CDataBuffer<DCEL2_Quotation>& SnapDCEL2Quotation) = 0;

    /// 查询大商所L2最优套利深度行情
    /// @param  pCodeList               -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapDCEL2ArbiQuotation  -- 快照数据列表
    /// @return RetCode                 -- 错误代码
    virtual RetCode QuerySnap_DCEL2_ArbiQuotation(char* pCodeList, CDataBuffer<DCEL2_ArbiQuotation>& SnapDCEL2ArbiQuotation) = 0;

    /// 查询大商所L2实时结算价
    /// @param  pCodeList               -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapDCEL2RealTimePrice  -- 快照数据列表
    /// @return RetCode                 -- 错误代码
    virtual RetCode QuerySnap_DCEL2_RealTimePrice(char* pCodeList, CDataBuffer<DCEL2_RealTimePrice>& SnapDCEL2RealTimePrice) = 0;

    /// 查询大商所L2委托统计行情
    /// @param  pCodeList               -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapDCEL2OrderStatistic -- 快照数据列表
    /// @return RetCode                 -- 错误代码
    virtual RetCode QuerySnap_DCEL2_OrderStatistic(char* pCodeList, CDataBuffer<DCEL2_OrderStatistic>& SnapDCEL2OrderStatistic) = 0;

    /// 查询大商所L2分价成交量行情
    /// @param  pCodeList               -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapDCEL2MarchPriceQty  -- 快照数据列表
    /// @return RetCode                 -- 错误代码
    virtual RetCode QuerySnap_DCEL2_MarchPriceQty(char* pCodeList, CDataBuffer<DCEL2_MarchPriceQty>& SnapDCEL2MarchPriceQty) = 0;

    /// 查询上期所静态数据
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSHFEL1Static    -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SHFEL1_Static(char* pCodeList, CDataBuffer<SHFEL1_Static>& SnapSHFEL1Static) = 0;

    /// 查询上期所实时行情
    /// @param  pCodeList           -- 快照订阅列表，NULL时为全市场快照数据
    /// @param  SnapSHFEL1Quotation -- 快照数据列表
    /// @return RetCode             -- 错误代码
    virtual RetCode QuerySnap_SHFEL1_Quotation(char* pCodeList, CDataBuffer<SHFEL1_Quotation>& SnapSHFEL1Quotation) = 0;

};

#endif // GTA_QTS_INTERFACE_BASE_H_
