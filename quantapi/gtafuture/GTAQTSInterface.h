//////////////////////////////////////////////////////////////////////////////
/// @file       GTAQTSInterface.h
/// @brief      行情接口定义，带自动重连功能
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    1.9.1
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_INTERFACE_H_
#define GTA_QTS_INTERFACE_H_

#include "GTAMarketServiceApi.h"

/// 行情系统服务接口.使用此接口时，不需要做重连和重新订阅<br>
/// 提供行情数据相关功能.
class GTA_API_EXPORT IGTAQTSInterface
{
public:
    virtual ~IGTAQTSInterface(){};
public:
    /// 创建一个实例.所有实例都必须通过本接口生成.
    /// @param Callback 服务回调接口.
    /// @return 失败返回NULL.
    static IGTAQTSInterface* CreateInstance(IGTAMarketServiceCallback* Callback);

    /// 释放一个实例,该实例是通过CreateInstance生成的.
    /// @param pInstance IGTAMarketServiceApi实例.
    static void ReleaseInstance(IGTAQTSInterface* pInstance);

    /// 注册行情服务器地址，可注册多个不同地址，实现高可用，连接顺序为顺序连接，断线时先重连当前使用地址
    /// @param pIP 服务器地址.
    /// @param uPort 服务器端口.
    virtual void RegisterService(const char* pIP, unsigned short uPort) = 0;

    /// 行情服务器验证用户.
    /// 连接成功后，认证模式下需要调用此函数先进行验证，非认证模式直接调用获取市场列表函数.
    /// @param userID 用户ID，由认证服务器返回.
    virtual void Logon(int userID) = 0;

    /// 连接服务器
    /// @return 返回false，未设置有效服务器地址，返回ture，开始进行连接
    virtual bool Connect() = 0;

    /// 设置与服务器发送心跳间隔，建议为10-20秒，调用Connect前设置
    /// @param uTimeout 发送心跳时长,单位秒
    virtual void SetTimeout(const unsigned int uTimeout = 10) = 0;

    /// 获取市场行情连接状态.
    /// @return 连接状态.
    virtual NetState GetConnectionState() = 0;
    /// 获取当前连接服务器地址
    /// @param pAddr    存放服务器地址的指针，内容为IP:Port，如192.168.1.1:8000
    /// @param nBufLen  pAddr缓存的长度
    virtual void GetConnectedAddr(char* pAddr, const int nBufLen) = 0;

    /// 获取市场列表.
    virtual void GetMarketList() = 0;

    /// 获取市场个股列表.
    /// @param mi 市场.
    virtual void GetStockList(MarketInfo* mi) = 0;

    /// 增加/取消订阅.
    /// @param mdi 市场数据标志.
    /// @param dataType 数据类型，参见具体市场数据类型定义
    /// @param sm 订阅模式.
    /// @param mr 市场范围.
    /// @param codelist 个股列表，字符串形式，个股之间用','分隔,如果type是所有行情，传NULL.
    /// @param codelistLen 代码缓冲区长度.
    virtual void Subscribe(MarketDataInfo* mdi, SubscribeMode sm, MarketRange mr, const char* codelist, int codelistLen) = 0;

    /// 查询个股/市场快照.
    /// @param mdi 市场数据标志.
    /// @param mr 市场范围.
    /// @param sds 快照源类型
    /// @param codelist 按个股查询快照，NULL表示不查询个股快照，字符串格式代码列表，代码之间用逗号分隔.
    /// @param codelistLen 代码缓冲区长度.
    virtual void QuerySnap(MarketDataInfo* mdi, MarketRange mr, SnapDataSource sds, const char* codelist, int codelistLen) = 0;

    /// 同步查询个股/市场快照.
    /// @param mdi 市场数据标志.
    /// @param mr 市场范围.
    /// @param sds 快照源类型
    /// @param codelist 按个股查询快照，NULL表示不查询个股快照，字符串格式代码列表，代码之间用逗号分隔.
    /// @param codelistLen 代码缓冲区长度.
    /// @return IDataBuf* 快照数据.
    virtual IDataBuf* SyncQuerySnap(MarketDataInfo* mdi, MarketRange mr, SnapDataSource sds, const char* codelist, int codelistLen) = 0;

    /// 同步获取香港SPTable数据.
    /// @return 香港SPTable数据.
    virtual IDataBuf* SyncGetHKSPTable() = 0;
};

#endif // GTA_QTS_INTERFACE_H_
