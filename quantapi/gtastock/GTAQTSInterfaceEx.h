//////////////////////////////////////////////////////////////////////////////
/// @file       GTAQTSInterfaceEx.h 
/// @brief      扩展行情接口定义，按字段查询返回数据内容，自动重连
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_INTERFACE_EX_H_
#define GTA_QTS_INTERFACE_EX_H_
#include "QTSDataType.h"
#include "QTSStruct.h"
#include "QTSDataFieldDefine.h"

/// 实时数据、连接状态回调接口，按字段返回数据
class GTA_API_EXPORT IGTAQTSCallbackEx
{
public:

    /// 登陆状态返回
    /// @param  errCode  -- 失败原因(用户过期、重复登陆)用户需对这两个进行处理
    virtual void OnLoginState( RetCode errCode){}

    /// 连接状态返回，连接成功/失败
    /// @param  msgType      -- 消息类型
    /// @param  errCode     -- 失败原因，成功时返回0
    virtual void OnConnectionState(MsgType msgType, RetCode errCode){}

    /// 会话标志失效（即在API中已经没有使用）
    /// @param  pSessionTag    -- 会话标志
    virtual void OnSessionTagInvalid(void* pSessionTag){}

    /// 订阅数据实时回调接口
    /// @param  msgCategory -- 返回的数据分类
    /// @param  RealData    -- 实时数据
    /// @param  pSessionTag -- 订阅数据时传入的用户标志
    virtual void OnSubscribe(const DataCategory msgCategory, IQuotationData& RealData, void*  pSessionTag){}
};


/// 行情系统服务接口，连接服务器进行认证，订阅数据，查询快照.
class GTA_API_EXPORT IGTAQTSApiEx
{
public:
    virtual ~IGTAQTSApiEx(){};
public:
    /// 创建一个实例.所有实例都必须通过本接口生成.
    /// @param  CallBack    -- 连接回调函数，通知连接状态
    /// @return NULL        -- 创建实例失败
    static IGTAQTSApiEx* CreateInstance(IGTAQTSCallbackEx& CallBack);

    /// 释放一个实例,该实例是通过CreateInstance生成的.
    /// @param  pInstance   -- 实例对象指针.
    static void ReleaseInstance(IGTAQTSApiEx* pInstance);

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
    /// @param  msgCategory -- 需要订阅的数据分类
    /// @param  pCodeList   -- 个股订阅列表，以“,”分割，末尾必须以\0结束，不允许为NULL
    /// @param  pSessionTag -- 会话标志,回调参数，在OnSubscribe时返回该数值
    /// @return RetCode     -- 错误代码
    virtual RetCode Subscribe(DataCategory msgCategory, char* pCodeList, void*  pSessionTag) = 0;

    /// 根据数据分类、用户标识和代码列表取消订阅
    /// @param  msgCategory -- 取消订阅的数据分类
    /// @param  pCodeList   -- 取消个股列表，以“,”分割，末尾必须以\0结束
    /// @param  pSessionTag -- 会话标志,取消该标志关联的所有订阅
    /// @return RetCode     -- 错误代码
    virtual RetCode Unsubscribe(DataCategory msgCategory, char* pCodeList, void*  pSessionTag) = 0;

    /// 根据数据分类和代码列表取消订阅
    /// @param  msgCategory -- 取消订阅的数据分类
    /// @param  pCodeList   -- 取消个股列表，以“,”分割，末尾必须以\0结束
    /// @return RetCode     -- 错误代码
    virtual RetCode UnsubscribeByCategory(DataCategory msgCategory, char* pCodeList) = 0;

    /// 根据会话标志和代码列表取消订阅
    /// @param  pSessionTag -- 会话标志,取消该标志关联的所有订阅
    /// @param  pCodeList   -- 取消个股列表，以“,”分割，末尾必须以\0结束
    /// @return RetCode     -- 错误代码
    virtual RetCode UnsubscribeBySessionTag(void*  pSessionTag, char* pCodeList) = 0;

    /// 取消所有订阅信息
    /// @return RetCode     -- 错误代码
    virtual RetCode UnsubscribeAll() = 0;

    /// 查询上交所静态数据
    /// @param  msgCategory -- 需要查询的数据分类
    /// @param  pCodeList   -- 个股订阅列表，以“,”分割，末尾必须以\0结束，不允许为NULL
    /// @param  SnapData    -- 快照数据列表
    /// @return RetCode     -- 错误代码
    virtual RetCode QuerySnap(DataCategory msgCategory, char* pCodeList, CDataBuffer<CQuotationDataPtr>& SnapData) = 0;

    /// 获取股票列表
    /// @param  pMarketTag  -- 市场标识，以“,”分割多个市场标识，末尾必须以\0结束，不允许为NULL
    /// @param  StockList   -- 返回的个股代码列表，带市场标志。
    /// @return RetCode     -- 错误代码
    virtual RetCode GetStockList(char* pMarketTag, CDataBuffer<StockSymbol>& StockList) = 0;
};


#endif // GTA_QTS_INTERFACE_EX_H_
