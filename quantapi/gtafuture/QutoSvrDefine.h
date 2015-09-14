/**
 * @brief   公共协议头定义，行情公共部分定义
 */
#ifndef GTA_QUTO_SVR_DEFINE_H
#define GTA_QUTO_SVR_DEFINE_H
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

#define GTA_QTS_VERSION     2           // 版本定义
//wCommandType
const WORD CT_Request           = 0;        //标识请求命令
const WORD CT_Response          = 1;        //标识回应命令
const WORD CT_Initiative        = 2;        //主动发送

//wCommand
const WORD CD_Logon             = 0;        //登入
const WORD CD_Logout            = 1;        //登出
const WORD CD_StateData         = 2;        //静态数据
const WORD CD_RealData          = 3;        //行情数据
const WORD CD_MarketList        = 4;        //市场列表
const WORD CD_CodeList          = 5;        //市场代码列表
const WORD CD_File              = 6;        //获取XXX文件
const WORD CD_QuotSnap          = 7;        //行情快照
const WORD CD_StaticSnap        = 8;        //静态数据快照
const WORD CD_ClientConnect     = 9;        //终端连接
const WORD CD_ClientDisConnect  = 10;        //终端断连
const WORD CD_ListenInfo        = 11;        //监听信息
const WORD CD_ReConnect         = 12;        //重连
const WORD CD_Heartbeat         = 13;        //心跳
const WORD CD_SPTable           = 14;        //香港价位表请求
const WORD CD_DL_StateData      = 15;        //下载静态数据请求
const WORD CD_DL_RealData       = 16;        //下载行情数据请求

//btTransferType
const BYTE TR_Single            = 0;        //单包
const BYTE TR_Multi             = 1;        //多包

const BYTE S_Fail               = 0;
const BYTE S_Start              = 1;
const BYTE S_Continue           = 2;
const BYTE S_End                = 3;

//btCountry
const BYTE CN_Area              = 1;        //中国

//btSource
const BYTE None_Type            = 0;
const BYTE L1_Quotation         = 1;        //Level1行情
const BYTE L2_Quotation         = 2;        //Level2行情

//btMarket
const BYTE SZ_Market            = 1;        //深圳市场
const BYTE SH_Market            = 2;        //上海市场
const BYTE HK_Market            = 3;        //香港市场
const BYTE CFX_Market           = 4;        //中金所股指期货
const BYTE ZZFX_Market          = 5;        //郑州商品期货
const BYTE DLFX_Market          = 6;        //大连商品期货
const BYTE SHFX_Market          = 7;        //上海商品期货
const BYTE FOREX_Market         = 8;        // 外汇
const BYTE SHIO_Market          = 9;        // 个股期权
const BYTE CFIO_Market          = 10;        // 中金所期权

//btType
const BYTE Stock_Type           = 1;        //股票
const BYTE Future_Type          = 2;        //期货
const BYTE Option_Type          = 3;        //期权
const BYTE Bond_Type            = 4;        //债券
const BYTE FX_Type              = 5;        //外汇
const BYTE Warrants_Type        = 6;        //权证
const BYTE Fund_Type            = 7;        //基金
const BYTE Industry_Type        = 8;        //指数
const BYTE Repo_Type            = 9;        //
const BYTE Convertible_Type     = 10;        //

//btDataClass
const BYTE RealTime_Info        = 1;        //实时信息
const BYTE Batch_Info           = 2;        //初始化信息
const BYTE Recovery_Info        = 3;        //盘后数据
const BYTE HK_SP_Info           = 4;        //报价表

//btDataType
const BYTE Static_Data          = 0;            //静态数据
const BYTE Quotations_Data      = 1;            //行情数据
const BYTE RemainQty_Data       = 2;            //
const BYTE Index_Data           = 3;            //指数数据
const BYTE OrderQueue           = 4;            //UA3111
const BYTE OrderRanking         = 5;            //UA3103
const BYTE TransRankingByIndustry   = 6;    //UA3104
const BYTE SingleOrderCanRanking    = 7;    //UA3105
const BYTE ConOrderCancelRanking    = 8;    //UA3106
const BYTE VirtualAuctionPrice      = 9;    //UA3107
const BYTE Index                    = 10;    //UA3113
const BYTE NGTS_MarketOverview      = 11;    //UA3115
const BYTE NGTS_Transaction         = 12;    //UA3101
//const BYTE GD_6301_Data             = 13;   //固定收益UA6301  
//const BYTE GD_6302_Data             = 14;   //固定收益UA6302
//const BYTE GD_Static_Data           = 15;   //固定收益       
const BYTE DFX_MBLQuot              = 13;       // 最优深度行情
const BYTE DFX_ArbiMBLQuot          = 14;       // 套利深度行情
const BYTE DFX_RealTimePrice        = 15;       // 实时结算价
const BYTE DFX_OrderStatistic       = 16;       // 委托统计
const BYTE DFX_MarchPriceQty        = 17;       // 分价成交量

//SZbtDataType  深圳L2
const BYTE SzStockInfo              = 1;             //UA101
const BYTE SzStockStatus            = 2;             //UA102
const BYTE SzSnapshot               = 3;             //UA103
const BYTE SzIndex                  = 4;             //UA104
const BYTE SzOrder                  = 5;             //UA201
const BYTE SzTrade                  = 6;             //UA202
const BYTE SzBulletin               = 7;             //UA401


#pragma pack(1)
typedef struct _Common_Head
{
    WORD    wLength;            //数据包长度，不包括本字段长度
    BYTE    btVersion;          //版本号
    WORD    wCommandType;       //命令类型: 例如区分请求数据，回应数据
    WORD    wCommand;           //命令: 具体的请求类型(认证，订阅等标识)
    BYTE    btTransferType;     //标记为多包传输还是单包传输
}Common_Head;   //公共报文头

typedef struct _Quotation_Head
{
    WORD    wProcessLayer;      // 标识哪个服务程序
    BYTE    btCountry;          // 市场地区标识
    BYTE    btSource;           // 行情深度（l1, l2）
    BYTE    btMarket;           // 市场标识 (SZ,SH,HK,CFX)
    BYTE    btType;             // 品种(STOCK, Futures, Option, Bond, FX....)
    BYTE    btDataClass;        // 类型(RealTime, Batch)
    BYTE    btDataType;         // 行情类型(Contract, RemainQty, Index .....)+++--

}Quotation_Head;    //行情包体公共部分

#define MAX_SNAPDATABUFFER  60000
#pragma pack()


#endif //GTA_QUTO_SVR_DEFINE_H
