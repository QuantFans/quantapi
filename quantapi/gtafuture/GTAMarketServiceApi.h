//////////////////////////////////////////////////////////////////////////////
///
/// @file    GTAMarketServiceApi.h
/// @brief   认证和行情接口定义
/// @note    Copyright (C), 2008-2010, GTA Information Tech. Co., Ltd.
/// @version 1.0
/// @author  何可丁
/// @date    2010.10.18
///
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_MARKET_SERVICE_API_H_
#define GTA_MARKET_SERVICE_API_H_

#include "GTAMarketServiceApiStruct.h"
#include "QutoSvrDefine.h"
#include "OutputData.h"

/// 数据封装类.
/// 主要用于同步调用api接口时，对api内部返回的数据进行封装.
class GTA_API_EXPORT IDataBuf
{
public:
    /// 创建实例.
    static IDataBuf* CreateInstance();

    /// 释放实例.
    static void ReleaseInstance(IDataBuf* db);

    /// 获取数据指针头.
    virtual char* GetBuf() = 0;

    /// 获取数据长度.
    virtual int GetLength() = 0;

    /// 添加数据.
    ///
    /// @param data 数据指针.
    /// @param len 数据长度.
    virtual int Append(char* data, int len) = 0;

    virtual ~IDataBuf(){};
};

/// 认证回调接口.
/// 认证请求的结果都在此接口通知应用.
class IGTAAuthCallback
{
public:
    /// 通知认证结果信息.
    ///
    /// @param cr 认证回应信息.
    /// @param msi 市场服务器信息.
    /// @param msicnt 市场服务器信息个数.
    virtual void OnCertify(CertifyResp* cr, MarketServerInfo* msi, int msicnt){};

    /// 通知请求市场服务器结果信息.
    ///
    /// @param result 操作结果 0成功，其余失败，详见错误码.
    /// @param msi 市场服务器信息(单个).
    virtual void OnMarketServer(unsigned char result, MarketServerInfo* msi){};
};

/// 认证接口.
/// 提供用户认证以及重新获取行情服务器地址等功能.
class GTA_API_EXPORT IGTAAuthApi
{
public:
    /// 创建一个IGTAAuthApi实例.
    /// 所有IGTAAuthApi实例都必须通过本接口生成.
    ///
    /// @return IGTAAuthApi* 失败返回NULL.
    static IGTAAuthApi* CreateInstance();

    /// 释放一个IGTAAuthApi实例.
    /// 该实例是通过CreateInstance生成的. 
    ///
    /// @param pInstance 接口实例.
    static void ReleaseInstance(IGTAAuthApi* pInstance);

    /// 初始化认证模块.
    /// 完成启动工作线程，初始化网络环境等操作.
    /// 
    /// @param cb 认证服务回调接口.
    ///
    /// @return 0成功，其余失败.
    virtual int Init(IGTAAuthCallback* cb) = 0;

    /// 停止模块.
    /// 模块提供的所有服务停止.
    virtual void Fini() = 0;

    /// 请求认证.
    /// 
    /// @param req 请求信息.
    virtual void RequestCertify(CertifyReq* req) = 0;

    /// 请求市场服务器信息.
    ///
    /// @param userID 用户ID,认证返回的信息CertifyResp里面的userID字段.
    /// @param mi 市场标志.
    virtual void RequestMarketServer(int userID, MarketInfo* mi) = 0;

    virtual ~IGTAAuthApi(){};
};

/// 行情服务回调接口.
/// 异步请求的行情接口的结果在此接口通知应用.
class IGTAMarketServiceCallback
{
public:
    /// 通知行情连接结果.
    /// 
    /// @param reason 连接结果标志 0成功，其余失败，详见失败代码表.
    virtual void OnConnect(int reason){};

    /// 通知行情断开.
    ///
    /// @param reason 错误码，详见失败代码表.
    virtual void OnConnectionFail(int reason){};

    /// 登录结果.
    /// 
    /// @param userID 用户ID.
    /// @param result 登录结果，0成功过，其余失败.
    virtual void OnLogon(int userID, int result){};

	/// 通知市场列表数据.
    /// 
    /// @param md 市场列表数据，包含cnt个MarketDesc.
    /// @param cnt 市场个数.
    virtual void OnMarketList(MarketDesc* md, int cnt){};

    /// 通知市场个股列表.
    /// 
    /// @param mi 市场.
    /// @param data 个股列表数据，代码之间以逗号分隔. 
    /// @param datalen 数据长度.
    virtual void OnStockList(MarketInfo* mi, void* data, int datalen){};

    /// 增加/取消订阅操作结果.
    /// 
    /// @param mdi 市场数据标志
    /// @param result 操作结果 0成功 其余失败.
    virtual void OnSubscribe(MarketDataInfo* mdi, int result){};

    /// 通知实时数据.
    /// 
    /// @param mdi 市场数据标志.
    /// @param dataType 数据类型，参见具体市场数据类型定义
    /// @param data 行情数据，每个市场不同，由应用自行解析.
    /// @param datalen 数据长度
    virtual void OnRealData(MarketDataInfo* mdi, void* data, int datalen){};

    /// 通知快照数据.
    ///
    /// @param mdi 市场数据标志.
    /// @param data 行情数据，每个市场不同，由应用自行解析.
    /// @param datalen 数据长度.
    virtual void OnSnapData(MarketDataInfo* mdi, void* data, int datalen){};

    /// 通知香港价位表.
    /// 
    /// @param data 价位表数据.
    /// @param datalen 价位表数据长度.
    virtual void OnHKSPTable(void* data, int datalen){};

    /// 系统运行状态.
    /// 
    /// @param type 状态类型
    /// @param data 状态数据.
    /// @param datalen 状态数据长度.
    virtual void OnSysState(BYTE type, void* data, int datalen){};
};

/// 行情系统服务接口.
/// 提供行情数据相关功能.
class GTA_API_EXPORT IGTAMarketServiceApi
{
public:
    /// 创建一个IGTAMarketServiceApi实例.
    /// 所有IGTAMarketServiceApi实例都必须通过本接口生成.
    /// 
    /// @return 失败返回NULL.
    static IGTAMarketServiceApi* CreateInstance();

    /// 释放一个IGTAMarketServiceApi实例.
    /// 该实例是通过CreateInstance生成的.
    /// 
    /// @param pInstance IGTAMarketServiceApi实例.
    static void ReleaseInstance(IGTAMarketServiceApi* pInstance);

    /// 初始化模块.
    /// 完成启动工作线程，初始化网络环境等操作.
    /// 
    /// @param cb 服务回调接口.
    /// @param snapshotFlag 快照标志，0不启用 1 启用.
    /// 
    /// @return 0成功，其余失败.
    virtual int Init(IGTAMarketServiceCallback* cb, int snapshotFlag) = 0;

    /// 停止模块.
    /// 模块提供的所有服务停止.
    virtual void Fini() = 0;    

    /// 连接市场行情服务器.
    /// 
    /// @param addr 服务器地址.
    /// @param port 服务器端口.
    /// @param timeout 连接超时（秒）.
    virtual void Connect(const char* addr, unsigned short port, unsigned int timeout = 10) = 0;

    /// 行情服务器验证用户.
    /// 连接成功后，认证模式下需要调用此函数先进行验证，非认证模式直接调用获取市场列表函数.
    /// 
    /// @param userID 用户ID，由认证服务器返回.
    virtual void Logon(int userID) = 0;

    /// 获取市场行情连接状态.
    /// 
    /// @return 连接状态.
    virtual NetState GetConnectionState() = 0;

    /// 断开与市场行情连接.连接断后后由回调通知.
    virtual void CloseConnection() = 0;

    /// 获取市场列表.
    virtual void GetMarketList() = 0;

    /// 获取市场个股列表.
    /// 
    /// @param mi 市场.
    virtual void GetStockList(MarketInfo* mi) = 0;

    /// 增加/取消订阅.
    /// 
    /// @param mdi 市场数据标志.
    /// @param dataType 数据类型，参见具体市场数据类型定义
    /// @param sm 订阅模式.
    /// @param mr 市场范围.
    /// @param codelist 个股列表，字符串形式，个股之间用','分隔,如果type是所有
    ///                 行情，传NULL.
    /// @param codelistLen 代码缓冲区长度.
    virtual void Subscribe(MarketDataInfo* mdi, 
                           SubscribeMode sm, MarketRange mr, 
                           const char* codelist, int codelistLen) = 0;

    /// 查询个股/市场快照.
    /// 
    /// @param mdi 市场数据标志.
    /// @param mr 市场范围.
    /// @param sds 快照源类型
    /// @param codelist 按个股查询快照，NULL表示不查询个股快照，字符串格式代码
    ///                 列表，代码之间用逗号分隔.
    /// @param codelistLen 代码缓冲区长度.
    virtual void QuerySnap(MarketDataInfo* mdi, MarketRange mr, SnapDataSource sds, 
                           const char* codelist, int codelistLen) = 0;

    /// 同步查询个股/市场快照.
    /// 
    /// @param mdi 市场数据标志.
    /// @param mr 市场范围.
    /// @param sds 快照源类型
    /// @param codelist 按个股查询快照，NULL表示不查询个股快照，字符串格式代码
    ///                 列表，代码之间用逗号分隔.
    /// @param codelistLen 代码缓冲区长度.
    ///
    /// @return IDataBuf* 快照数据.
    virtual IDataBuf* SyncQuerySnap(MarketDataInfo* mdi, MarketRange mr, SnapDataSource sds, 
                                    const char* codelist, int codelistLen) = 0;

    /// 同步获取香港SPTable数据.
    /// 
    /// @return 香港SPTable数据.
    virtual IDataBuf* SyncGetHKSPTable() = 0;

    virtual ~IGTAMarketServiceApi(){};
};

/// 数据下载回调接口.
/// 异步请求的数据下载接口的结果在此接口通知应用.
class IGTADataDownloadCallback
{
public:
    /// 通知下载的静态数据.    
    /// 
    /// @param result   连接结果标志 0成功，其余失败，详见失败代码表.
    /// @param mdi      市场数据标志
    /// @param data     数据，如果为NULL，表示单次请求回应数据结束
    /// @param datalen  数据长度
    virtual void OnData(unsigned char result, MarketDataInfo* mdi, 
                        void* data, int datalen){};
};

/// 数据下载接口.
/// 提供历史数据下载功能.
class GTA_API_EXPORT IGTADataDownloadApi
{
public:
    /// 创建一个IGTADataDownloadApi实例.
    /// 所有IGTADataDownloadApi实例都必须通过本接口生成.
    /// 
    /// @return 失败返回NULL.
    static IGTADataDownloadApi* CreateInstance();

    /// 释放一个IGTADataDownloadApi实例.
    /// 该实例是通过CreateInstance生成的.
    /// 
    /// @param pInstance IGTADataDownloadApi实例.
    static void ReleaseInstance(IGTADataDownloadApi* pInstance);

    /// 初始化模块.
    /// 完成启动工作线程，初始化网络环境等操作.
    /// 
    /// @param cb 服务回调接口.
    /// 
    /// @return 0成功，其余失败.
    virtual int Init(IGTADataDownloadCallback* cb) = 0;

    /// 停止模块.
    /// 模块提供的所有服务停止.
    virtual void Fini() = 0;

    /// 请求数据.
    /// 
    /// @param req 请求信息.
    virtual void RequestData(DataDownloadReq* req) = 0;

    virtual ~IGTADataDownloadApi(){};
};

#endif // GTA_MARKET_SERVICE_API_H_
