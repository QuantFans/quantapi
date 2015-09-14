//////////////////////////////////////////////////////////////////////////////
/// @file       QTSStruct.h 
/// @brief      数据消息结构体定义文件
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_STRUCT_H_
#define GTA_QTS_STRUCT_H_
#include "QTSDataType.h"


#define DESTDLG_FILE        1      ///< TestDlg文件格式
#define HIGH_FREQUENCY      2      ///< 高频文件格式

#pragma pack(8)


/// 买卖档位信息，含价、量、笔数3个信息
struct  BuySellLevelInfo3
{
    double              Price;                  ///< 价格,3位小数
    unsigned long long  Volume;                 ///< 量
    unsigned int        TotalOrderNo;           ///< 委托笔数
};
/// 买卖档位信息，含价、量信息
struct  BuySellLevelInfo
{
    double              Price;                  ///< 价格,3位小数
    unsigned long long  Volume;                 ///< 量
};

#define LEVEL_ONE   1               ///< 一档行情
#define LEVEL_FIVE  5               ///< 五档行情
#define LEVEL_TEN   10              ///< 十档行情
#define SETTLE_LEN  10              ///< 结算组代码长度
#define ORDER_LEVEL_FIFTY   50      ///< 50笔委托

/// 上交所静态数据
struct SSEL1_Static
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 上交所L1实时行情
struct SSEL1_Quotation
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};

/// 上交所L2静态数据
struct SSEL2_Static
{
    int                 LocalTimeStamp;                     ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;                    ///< 数据包头时间YYYYMMDDHHMMSSMMM
    int                 Time;                               ///< 数据生成时间，标识接口中本记录更新时间HHMMSSMMM
    char                Symbol[SYMBOL_LEN];                 ///< 证券代码, 
    char                ISINCode[12];                       ///< ISIN代码, 
    char                SecurityName[SECURITY_NAME_LEN];    ///< 证券名称, 
    char                SecurityEN[SECURITY_EN_LEN];        ///< 英文证券名称, 
    char                SymbolUnderlying[SYMBOL_LEN];       ///< 基础证券代码, 
    char                MarketType[6];                      ///< 市场种类, ‘ASHR’表示A股市场；‘BSHR’表示B股市场；‘CSHR‘表示国际版市场。
    char                CFICode[6];                         ///< 证券类别, ’E'表示股票；‘EU’表示基金；‘D’表示债券；‘RWS’表示权证；‘FF’表示期货。
    char                SecuritySubType[6];                 ///< 证券子类别, 自定义详细证券类别
    char                Currency[5];                        ///< 币种, CNY = 人民币，HKD = 港币
    long long           TradableMarketNo;                   ///< 可流通已上市数量, 预留
    long long           TradableNo;                         ///< 可流通未上市数量, 预留
    long long           NonTradableNo;                      ///< 非流通股数, 预留
    int                 ListingDate;                        ///< 上市日期, 在上交所首日交易日期，YYYYMMDD
    unsigned int        SetNo;                              ///< 产品集编号, 取值范围从1到999,。用来表明产品的一种分组方式，用于在多主机间记性负载均衡分配。该值在一个交易日内不会变化。
    unsigned int        BuyVolumeUnit;                      ///< 买数量单位, 买订单的申报数量必须是该字段的整数倍。
    unsigned int        SellVolumeUnit;                     ///< 卖数量单位, 卖订单的申报数量必须是该字段的整数倍。
    unsigned int        DeclareVolumeFloor;                 ///< 申报量下限, 申报数量下限
    unsigned int        DeclareVolumeCeiling;               ///< 申报量上限, 申报数量上限
    double              PreClosePrice;                      ///< 昨收价, 3位小数；前收盘价格（如有除权除息，为除权除息后的收盘价）；对于货币市场基金实时申赎，取值为0.010
    double              TickSize;                           ///< 最小报价单位, 申报价格的最小变动单位
    char                UpDownLimitType;                    ///< 涨跌幅限制类型, ‘N’表示交易规则3.4.13规定的有涨跌幅限制类型或者权证管理办法第22条规定；‘R'表示交易规则3.4.15和3.4.16规定的无涨跌幅限制类型；’S‘表示回购涨跌幅控制类型。
    double              PriceUpLimit;                       ///< 涨幅价格, 对于N类型涨跌幅限制的产品，该字段当日不会更改，基于前收盘价（已首日上市交易产品为发行价）计算；对于R类型五涨跌幅限制的产品，该字段取开盘时基于参考价格计算的上限价格。
    double              PriceDownLimit;                     ///< 跌幅价格, 计算方式参考涨幅上限价格
    double              XRRatio;                            ///< 除权比例, 每股送股比例；对于国债预发行产品，为保证金比例。
    double              XDAmount;                           ///< 除息金额, 每股分红金额
    char                CrdBuyUnderlying;                   ///< 融资标的标志, ’T‘表示是融资标的证券；’F‘表示不是融资标的证券。
    char                CrdSellUnderlying;                  ///< 融券标的标志, ’T‘表示是融拳标的证券；’F‘表示不是融券标的证券。
    char                SecurityStatus[20];                 ///< 产品状态标识, 第0位对应：‘N’表示首日上市；第1位对应：‘D’表示除权；第2位对应：‘R'表示除息；第3位对应：‘D‘表示国内主板正常交易产品，‘S’表示风险警示产品，‘P’表示退市整理产品。
};
/// 上交所L2实时行情
struct SSEL2_Quotation
{
    int                 LocalTimeStamp;         ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;        ///< 数据包头时间YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< 数据生成时间, 最新订单时间（毫秒）;143025001 表示 14:30:25.001
    char                Symbol[SYMBOL_LEN];     ///< 证券代码, 
    double              PreClosePrice;          ///< 昨收价, 
    double              OpenPrice;              ///< 开盘价, 
    double              HighPrice;              ///< 最高价, 
    double              LowPrice;               ///< 最低价, 
    double              LastPrice;              ///< 现价, 
    double              ClosePrice;             ///< 今收盘价, 
    char                TradeStatus[6];         ///< 当前品种交易状态, 
    unsigned long long  TotalNo;                ///< 成交笔数, 
    unsigned long long  TotalVolume;            ///< 成交总量, 股票：股;权证：份;债券：手
    double              TotalAmount;            ///< 成交总额, （元）
    unsigned long long  TotalBuyOrderVolume;    ///< 委托买入总量, 股票：股;权证：份;债券：手
    double              WtAvgBuyPrice;          ///< 加权平均委买价, （元）
    double              BondWtAvgBuyPrice;      ///< 债券加权平均委买价, （元）
    unsigned long long  TotalSellOrderVolume;   ///< 委托卖出总量, 
    double              WtAvgSellPrice;         ///< 加权平均委卖价, （元）
    double              BondWtAvgSellPrice;     ///< 债券加权平均委卖价, 
    double              IOPV;                   ///< ETF 净值估值, 
    int                 ETFBuyNo;               ///< ETF 申购笔数, 
    long long           ETFBuyVolume;           ///< ETF 申购量, 
    double              ETFBuyAmount;           ///< ETF 申购额, 
    int                 ETFSellNo;              ///< ETF 赎回笔数, 
    long long           ETFSellVolume;          ///< ETF 赎回量, 
    double              ETFSellAmount;          ///< ETF 赎回额, 
    double              YTM;                    ///< 债券到期收益率, 
    long long           TotalWarrantExecVol;    ///< 权证执行的总数量, 
    double              WarrantDownLimit;       ///< 权证跌停价格, （元）
    double              WarrantUpLimit;         ///< 权证涨停价格, （元）
    int                 WithdrawBuyNo;          ///< 买入撤单笔数, 
    long long           WithdrawBuyVolume;      ///< 买入撤单量, 
    double              WithdrawBuyAmount;      ///< 买入撤单额, 
    int                 WithdrawSellNo;         ///< 卖出撤单笔数, 
    long long           WithdrawSellVolume;     ///< 卖出撤单量, 
    double              WithdrawSellAmount;     ///< 卖出撤单额, 
    int                 TotalBuyNo;             ///< 买入总笔数, 
    int                 TotalSellNo;            ///< 卖出总笔数, 
    int                 MaxBuyDuration;         ///< 买入成交最大等待时间, 
    int                 MaxSellDuration;        ///< 卖出成交最大等待时间, 
    int                 BuyOrderNo;             ///< 买方委托价位数, 
    int                 SellOrderNo;            ///< 卖方委托价位数, 
    unsigned int        SellLevelNo;            ///< 卖盘价位数量, 10档行情，不足时补空
    union
    {
        BuySellLevelInfo3    SellLevel[LEVEL_TEN];          ///< 十档卖行情
        struct
        {
                double              SellPrice01;            ///< 申卖价, 
                unsigned long long  SellVolume01;           ///< 申卖量, 
                unsigned int        TotalSellOrderNo01;     ///< 卖出总委托笔数, 
                double              SellPrice02;            ///< 申卖价, 
                unsigned long long  SellVolume02;           ///< 申卖量, 
                unsigned int        TotalSellOrderNo02;     ///< 卖出总委托笔数, 
                double              SellPrice03;            ///< 申卖价, 
                unsigned long long  SellVolume03;           ///< 申卖量, 
                unsigned int        TotalSellOrderNo03;     ///< 卖出总委托笔数, 
                double              SellPrice04;            ///< 申卖价, 
                unsigned long long  SellVolume04;           ///< 申卖量, 
                unsigned int        TotalSellOrderNo04;     ///< 卖出总委托笔数, 
                double              SellPrice05;            ///< 申卖价, 
                unsigned long long  SellVolume05;           ///< 申卖量, 
                unsigned int        TotalSellOrderNo05;     ///< 卖出总委托笔数, 
                double              SellPrice06;            ///< 申卖价, 
                unsigned long long  SellVolume06;           ///< 申卖量, 
                unsigned int        TotalSellOrderNo06;     ///< 卖出总委托笔数, 
                double              SellPrice07;            ///< 申卖价, 
                unsigned long long  SellVolume07;           ///< 申卖量, 
                unsigned int        TotalSellOrderNo07;     ///< 卖出总委托笔数, 
                double              SellPrice08;            ///< 申卖价, 
                unsigned long long  SellVolume08;           ///< 申卖量, 
                unsigned int        TotalSellOrderNo08;     ///< 卖出总委托笔数, 
                double              SellPrice09;            ///< 申卖价, 
                unsigned long long  SellVolume09;           ///< 申卖量, 
                unsigned int        TotalSellOrderNo09;     ///< 卖出总委托笔数, 
                double              SellPrice10;            ///< 申卖价, 
                unsigned long long  SellVolume10;           ///< 申卖量, 
                unsigned int        TotalSellOrderNo10;     ///< 卖出总委托笔数, 
        };
    };
    unsigned int        SellLevelQueueNo01;                 ///< 卖一档揭示委托笔数, 为 0 表示不揭示
    unsigned int        SellLevelQueue[ORDER_LEVEL_FIFTY];  ///< 卖1档队列, 高频数据保存，先存订单数量,只有一档有此数据，50档，不足时补空
    unsigned int        BuyLevelNo;                         ///< 买盘价位数量, 10档行情，不足时补空
    union
    {
        BuySellLevelInfo3    BuyLevel[LEVEL_TEN];           ///< 十档买行情
        struct
        {
            double              BuyPrice01;                 ///< 申买价, 
            unsigned long long  BuyVolume01;                ///< 申买量, 股票：股;权证：份;债券：手
            unsigned int        TotalBuyOrderNo01;          ///< 买入总委托笔数, 
            double              BuyPrice02;                 ///< 申买价, 
            unsigned long long  BuyVolume02;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo02;          ///< 买入总委托笔数, 
            double              BuyPrice03;                 ///< 申买价, 
            unsigned long long  BuyVolume03;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo03;          ///< 买入总委托笔数, 
            double              BuyPrice04;                 ///< 申买价, 
            unsigned long long  BuyVolume04;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo04;          ///< 买入总委托笔数, 
            double              BuyPrice05;                 ///< 申买价, 
            unsigned long long  BuyVolume05;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo05;          ///< 买入总委托笔数, 
            double              BuyPrice06;                 ///< 申买价, 
            unsigned long long  BuyVolume06;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo06;          ///< 买入总委托笔数, 
            double              BuyPrice07;                 ///< 申买价, 
            unsigned long long  BuyVolume07;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo07;          ///< 买入总委托笔数, 
            double              BuyPrice08;                 ///< 申买价, 
            unsigned long long  BuyVolume08;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo08;          ///< 买入总委托笔数, 
            double              BuyPrice09;                 ///< 申买价, 
            unsigned long long  BuyVolume09;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo09;          ///< 买入总委托笔数, 
            double              BuyPrice10;                 ///< 申买价, 
            unsigned long long  BuyVolume10;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo10;          ///< 买入总委托笔数, 
        };
    };
    unsigned int        BuyLevelQueueNo01;                  ///< 买一档揭示委托笔数, 为 0 表示不揭示
    unsigned int        BuyLevelQueue[ORDER_LEVEL_FIFTY];   ///< 买1档队列, 高频数据保存，先存订单数量,只有一档有此数据，50档，不足时补空

};
/// 上交所L2指数行情
struct SSEL2_Index
{
    int                 LocalTimeStamp;         ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;        ///< 数据包头时间YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< 数据生成时间(毫秒), 143025000 表示 14:30:25000
    int                 TradeTime;              ///< 成交时间(毫秒),
    char                Symbol[SYMBOL_LEN];     ///< 证券代码, 
    double              PreClosePrice;          ///< 昨收价, 
    double              OpenPrice;              ///< 开盘价, 
    double              TotalAmount;            ///< 成交总额, 
    double              HighPrice;              ///< 最高价, 
    double              LowPrice;               ///< 最低价, 
    double              LastPrice;              ///< 现价, 
    unsigned long long  TotalVolume;            ///< 成交总量, 手
    double              ClosePrice;             ///< 今收盘价, 
};
/// 上交所L2逐笔成交
struct SSEL2_Transaction
{
    int                 LocalTimeStamp;         ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;        ///< 数据包头时间YYYYMMDDHHMMSSMMM
    int                 TradeTime;              ///< 成交时间(毫秒), 14302506 表示14:30:25.06
    unsigned int        RecID;                  ///< 业务索引, 从 1 开始，按 TradeChannel连续
    int                 TradeChannel;           ///< 成交通道, 
    char                Symbol[SYMBOL_LEN];     ///< 证券代码, 
    double              TradePrice;             ///< 成交价格, 
    unsigned int        TradeVolume;            ///< 成交数量, 股票：股;权证：份;债券：张
    double              TradeAmount;            ///< 成交金额, 
    long long           BuyRecID;               ///< 买方订单号, 
    long long           SellRecID;              ///< 卖方订单号, 
    char                BuySellFlag;            ///< 内外盘标志, B – 外盘,主动买;S – 内盘,主动卖;N – 未知
};
/// 上交所L2虚拟集合竞价
struct SSEL2_Auction
{
    int                 LocalTimeStamp;         ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;        ///< 数据包头时间YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< 数据生成时间, 143025001 表示 14:30:25.001
    char                Symbol[SYMBOL_LEN];     ///< 证券代码, 
    double              OpenPrice;              ///< 虚拟开盘参考价, 
    long long           AuctionVolume;          ///< 虚拟匹配量, 
    long long           LeaveVolume;            ///< 虚拟未匹配量, 
    char                Side;                   ///< 买卖方向, 0=无未匹配量，买卖两边的未匹配量都为 0;1=买方有未匹配量，卖方未匹配量=0;2=卖方有未匹配量，买方未匹配量=0
};
/// 上交所L2市场总览
struct SSEL2_Overview
{
    int                 LocalTimeStamp;         ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;        ///< 数据包头时间YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< 数据生成时间, 143025001 表示 14:30:25.001
    char                Symbol[SYMBOL_LEN];     ///< 证券代码, 
    int                 MarketTime;             ///< 市场时间, 百分之一秒
    int                 TradeDate;              ///< 市场日期, 
};

/// 上交所个股期权静态数据
struct SSEIOL1_Static
{
    int                 LocalTimeStamp;                     ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;                    ///< 数据包头时间YYYYMMDDHHMMSSMMM
    char                Symbol[SYMBOL_LEN];                 ///< 证券代码（合约代码）, 合约期权产品代码，8位字符;唯一标示
    char                ContractID [19];                    ///< 合约交易代码 , 合约交易代码17位，按以下顺序编写：1、第1至第6位为数字，取标的证券代码，如工商银行601398，取“601398”；2、第7位为C(Call)或者P(Put)，分别表示认购期权或者认沽期权；3、第8、9位表示到期年份；4、第10、11位表示到期月份；5、第12位期初设为“M”，表示月份合约。当合约首次调整后，“M”修改为 “A”，以表示该合约被调整过一次，如发生第二次调整，则“A”修改为“B”、“M”修改为 “A”，以此类推；6、第13至17位表示期权行权价格.留两位备用
    char                SecurityName[SECURITY_NAME_LEN];    ///< 期权合约简称（证券名称） , 
    char                SymbolUnderlying[SYMBOL_LEN];       ///< 基础证券代码, 
    char                NameUnderlying[SECURITY_NAME_LEN];  ///< 基础证券名称 , 
    char                UnderlyingType [5];                 ///< 标的证券类型 , EBS – ETF， ASH – A股 
    char                OptionType;                         ///< 行权类型, 若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A” 
    char                CallOrPut;                          ///< 认购认沽 , 认购，则本字段为“C”；若为认沽，则本字段为“P” 
    long long           ContractMultiplierUnit;             ///< 合约单位 , 经过除权除息调整后的合约单位, 一定是整数 
    double              ExercisePrice;                      ///< 期权行权价 , 经过除权除息调整后的期权行权价，右对齐，精确到厘;行权价格调整采取四舍五入方式，股票保留两位小数，ETF保留三位小数。
    int                 StartDate;                          ///< 首个交易日 , 期权首个交易日,YYYYMMDD (年*10000+月*100+日)
    int                 EndDate;                            ///< 最后交易日 , 期权最后交易日/行权日，YYYYMMDD 
    int                 ExerciseDate;                       ///< 期权行权日 , 期权行权日，YYYYMMDD 
    int                 DeliveryDate;                       ///< 行权交割日, 行权交割日，默认为行权日的下一个交易日，YYYYMMDD
    int                 ExpireDate;                         ///< 期权到期日 , 期权到期日，YYYYMMDD 
    char                Version;                            ///< 合约版本号 , 期权合约的版本号。新挂合约是’1’ 
    unsigned int        TotalLongPosition;                  ///< 合约未平仓数 , 单位是 （张） 
    double              PreClosePrice;                      ///< 昨收价, 昨日收盘价，如遇除权除息则为调整后的收盘价格（上市首日的文件中，填写参考价格），右对齐，精确到厘 
    double              PreSettlePrice;                     ///< 昨结算, 昨日结算价，右对齐，单位：元 
    double              PreClosePriceUnderlying;            ///< 标的昨收价, 期权标的证券除权除息调整后的前收盘价格，右对齐，单位：元 
    char                UpDownLimitType;                    ///< 涨跌幅限制类型 , ‘N’表示交易规则3.4.13规定的有涨跌幅限制类型或者权证管理办法第22条规定 ‘R’表示交易规则3.4.15和3.4.16规定的无涨跌幅限制类型 
    double              PriceUpLimit;                       ///< 涨幅价格, 当日期权涨停价格，精确到厘 
    double              PriceDownLimit;                     ///< 跌幅价格, 当日期权跌停价格，精确到厘 
    double              MarginUnit;                         ///< 单位保证金 , 当日持有一张合约所需要的保证金数 量，精确到分 
    double              MarginRatioParam1;                  ///< 保证金计算参数一 , 保证金计算参数，单位：% 
    double              MarginRatioParam2;                  ///< 保证金计算参数二 , 保证金计算参数，单位：% 
    unsigned int        RoundLot;                           ///< 整手数 , 一手等于几张合约 
    long long           LmtOrdFloor;                        ///< 限价申报下限 , 单笔限价申报的申报张数下限。 
    long long           LmtOrdCeiling;                      ///< 限价申报上限 , 单笔限价申报的申报张数上限。 
    long long           MktOrdFloor;                        ///< 市价申报下限 , 单笔市价申报的申报张数下限。 
    long long           MktOrdCeiling;                      ///< 市价申报上限 , 单笔市价申报的申报张数上限。 
    double              TickSize;                           ///< 最小报价单位, 单位：元（精确到0.1厘）
    char                SecurityStatusFlag[8];              ///< 期权合约状态, 该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
                                                            ///< 第1位：‘0’表示可开仓，‘1’表示限制卖出开仓（包括备兑开仓）和买入开仓。
                                                            ///< 第2位：‘0’表示未连续停牌，‘1’表示连续停牌。
                                                            ///< 第3位：‘0’表示未临近到期日，‘1’表示距离到期日不足10个交易日。
                                                            ///< 第4位：‘0’表示近期未做调整，‘1’表示最近10个交易日内合约发生过调整。
                                                            ///< 第5位：‘A’表示当日新挂牌的合约，‘E’表示存续的合约，‘D’表示当日摘牌的合约。
};
/// 上交所个股期权实时行情
struct SSEIOL1_Quotation
{
    int                 LocalTimeStamp;         ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;        ///< 数据包头时间YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< 数据生成时间, 143025001表示 14:30:25.001;如果期权合约的产品代码为“00000000”，则表示行情时间，格式为HHMMSSMMM;有成交时才会变化
    char                Symbol[SYMBOL_LEN];     ///< 合约代码（证券代码）, 期权合约的产品代码;唯一标示
    double              PreSettlePrice;         ///< 昨结算, 4 decimal places
    double              SettlePrice;            ///< 结算价, 4 decimal places
    double              OpenPrice;              ///< 开盘价, 4 decimal places
    double              HighPrice;              ///< 最高价 , 4 decimal places
    double              LowPrice;               ///< 最低价, 4 decimal places
    double              LastPrice;              ///< 现价, 4 decimal places
    double              ClosePrice;             ///< 收盘价
    double              AuctionPrice;           ///< 波动性中断参考价, 4 decimal places
    long long           AuctionVolume;          ///< 波动性中断虚拟匹配量, 
    unsigned long long  TotalPosition;          ///< 持仓量, 
    unsigned int        SellLevelNo;            ///< 卖盘价位数量, 五档:总是5，空档位用0填充
    union
    {
        BuySellLevelInfo    SellLevel[LEVEL_FIVE];      ///< 五档卖行情
        struct  
        {
            double              SellPrice01;            ///< 申卖价, 当10069<5时，补足5  档，即：不知的填充为0
            unsigned long long  SellVolume01;           ///< 申卖量, 当10069<5时，补足5  档，即：不知的填充为0
            double              SellPrice02;            ///< 申卖价, 当10069<5时，补足5  档，即：不知的填充为0
            unsigned long long  SellVolume02;           ///< 申卖量, 当10069<5时，补足5  档，即：不知的填充为0
            double              SellPrice03;            ///< 申卖价, 当10069<5时，补足5  档，即：不知的填充为0
            unsigned long long  SellVolume03;           ///< 申卖量, 当10069<5时，补足5  档，即：不知的填充为0
            double              SellPrice04;            ///< 申卖价, 当10069<5时，补足5  档，即：不知的填充为0
            unsigned long long  SellVolume04;           ///< 申卖量, 当10069<5时，补足5  档，即：不知的填充为0
            double              SellPrice05;            ///< 申卖价, 当10069<5时，补足5  档，即：不知的填充为0
            unsigned long long  SellVolume05;           ///< 申卖量, 当10069<5时，补足5  档，即：不知的填充为0
        };
    };
    unsigned int            BuyLevelNo;                  ///< 买盘价位数量, 五档:总是5，空档位用0填充
    union
    {
        BuySellLevelInfo    BuyLevel[LEVEL_FIVE];        ///< 五档买行情
        struct  
        {
            double              BuyPrice01;             ///< 申买价, 当10068<5时，补足5档，即：不知的填充为0
            unsigned long long  BuyVolume01;            ///< 申买量, 当10068<5时，补足5档，即：不知的填充为0
            double              BuyPrice02;             ///< 申买价, 当10068<5时，补足5档，即：不知的填充为0
            unsigned long long  BuyVolume02;            ///< 申买量, 当10068<5时，补足5档，即：不知的填充为0
            double              BuyPrice03;             ///< 申买价, 当10068<5时，补足5档，即：不知的填充为0
            unsigned long long  BuyVolume03;            ///< 申买量, 当10068<5时，补足5档，即：不知的填充为0
            double              BuyPrice04;             ///< 申买价, 当10068<5时，补足5档，即：不知的填充为0
            unsigned long long  BuyVolume04;            ///< 申买量, 当10068<5时，补足5档，即：不知的填充为0
            double              BuyPrice05;             ///< 申买价, 当10068<5时，补足5档，即：不知的填充为0
            unsigned long long  BuyVolume05;            ///< 申买量, 当10068<5时，补足5档，即：不知的填充为0
        };
    };
    unsigned long long  TotalVolume;            ///< 成交总量, Trade volume of this security.如果期权合约的产品代码为“00000000”，则表示行情日期，格式为YYYYMMDD
    double              TotalAmount;            ///< 成交金额, 2 decimal places
    char                SecurityPhaseTag[8];    ///< 交易状态,  该字段为4 位字符串，左起每位表示特定的含义，无定义则填空格。第1 位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示连续交易时段，‘B’表示休市时段，‘E’表示闭市时段，‘V’表示波动性中断，‘P’表示临时停牌。第2 位：‘0’表示未连续停牌，‘1’表示连续停牌。
};

/// 深交所静态数据
struct SZSEL1_Static
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 深交所L1实时行情
struct SZSEL1_Quotation
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 杂项费用信息
struct MiscFeeInfo
{
    short               MiscFeeType;            ///< 杂项费用类别
    unsigned int        MiscFeeUnit;            ///< 杂项费用单位
    double              MiscFeeAmount;          ///< 杂项费用金额,6位小数
};
/// 备选证券信息
struct AltSymbolInfo
{
    char                AltSymbol[SYMBOL_LEN];  ///< 备选证券代码
    char                AltSymbolSource[5];     ///< 备选证券代码源
};
/// 深交所L2静态数据
struct SZSEL2_Static
{
    int                 LocalTimeStamp;                     ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;                    ///< 数据包头时间YYYYMMDDHHMMSSMMM
    unsigned int        RecID;                              ///< 记录索引
    char                Symbol[SYMBOL_LEN];                 ///< 证券代码
    char                SecurityName[SECURITY_NAME_LEN];    ///< 证券名称
    char                SecurityEN[SECURITY_EN_LEN];        ///< 证券英文简称
    char                SymbolUnderlying[SYMBOL_LEN];       ///< 基础证券代码
    char                SymbolSource[5];                    ///< 证券代码源
    unsigned int        AltSymbolNo;                        ///< 备选证券代码个数
    union
    {
        AltSymbolInfo   AltSymbol[3];           ///< 备选证券代码信息
        struct
        {
            char        AltSymbol1[SYMBOL_LEN]; ///< 备选证券代码
            char        AltSymbolSource1[5];    ///< 备选证券代码源
            char        AltSymbol2[SYMBOL_LEN]; ///< 备选证券代码
            char        AltSymbolSource2[5];    ///< 备选证券代码源
            char        AltSymbol3[SYMBOL_LEN]; ///< 备选证券代码
            char        AltSymbolSource3[5];    ///< 备选证券代码源
        };
    };
    char                IndustryType[5];        ///< 行业种类
    char                Currency[5];            ///< 币种
    double              ParValue;               ///< 每股面值,3位小数
    unsigned long long  IssuedVolume;           ///< 总发行量
    unsigned long long  OutstandingShare;       ///< 流通股数
    double              PreYearEPS;             ///< 上年每股利润,4位小数
    double              YearEPS;                ///< 本年每股利润,4位小数
    double              NAV;                    ///< 基金T-1日累计净值,4位小数
    unsigned int        MiscFeeNo;              ///< 杂项费用类别数
    union
    {
        MiscFeeInfo         MiscFee[3];         ///< 杂项费信息
        struct
        {
            short               MiscFeeType1;               ///< 杂项费用类别
            unsigned int        MiscFeeUnit1;               ///< 杂项费用单位
            double              MiscFeeAmount1;             ///< 杂项费用金额,6位小数
            short               MiscFeeType2;               ///< 杂项费用类别
            unsigned int        MiscFeeUnit2;               ///< 杂项费用单位
            double              MiscFeeAmount2;             ///< 杂项费用金额,6位小数
            short               MiscFeeType3;               ///< 杂项费用类别
            unsigned int        MiscFeeUnit3;               ///< 杂项费用单位
            double              MiscFeeAmount3;             ///< 杂项费用金额,6位小数
        };
    };
    int                 IssueDate;              ///< 发行日期YYYYMMDD,如20140821为2014年8月21日
    char                BondType;               ///< 债券类型
    double              CouponRate;             ///< 票面利率,6位小数
    double              ConversionPrice;        ///< 行权价格,3位小数
    char                OptionType;             ///< 美式/欧式/百慕大式
    char                CallOrPut;              ///< Call/Put标志
    char                WarrantClearingType;    ///< 权证结算方式
    double              ConversionRatio;        ///< 行权比例,4位小数
    int                 ConversionBeginDate;    ///< 行权开始日期YYYYMMDD,如20140821为2014年8月21日
    int                 ConversionEndDate;      ///< 行权结束日期YYYYMMDD,如20140821为2014年8月21日
    int                 InterestAccrualDate;    ///< 起息日YYYYMMDD,如20140821为2014年8月21日
    int                 MaturityDate;           ///< 到期交割日YYYYMMDD,如20140821为2014年8月21日
    unsigned int        RoundLot;               ///< 交易单位
    unsigned int        BuyVolumeUnit;          ///< 买数量单位
    unsigned int        SellVolumeUnit;         ///< 卖数量单位
    unsigned int        DeclareVolumeCeiling;   ///< 每笔限量
    char                TradeMethod;            ///< 交易方法
    double              TickSize;               ///< 价格档位,3位小数
    char                PriceLimitType;         ///< 限价参数类型
    double              AuctionPriceLimit;      ///< 集合竞价限价参数,3位小数
    double              ContTradePriceLmt;      ///< 连续竞价限价参数,3位小数
    double              PriceUpLimit;           ///< 涨幅价格,3位小数
    double              PriceDownLimit;         ///< 跌幅价格,3位小数
    double              BlockPriceUpLmt;        ///< 无涨跌停证券大宗交易除当日交易最高价外的价格限制,3位小数
    double              BlockPriceDownLmt;      ///< 无涨跌停证券大宗交易除当日交易最低价外的价格限制,3位小数
    double              ContractMultiplier;     ///< 债券折合回购标准券比例,3位小数
    double              GageRate;               ///< 担保品折算率,2位小数
    char                CrdBuyUnderlying;       ///< 融资买入标的
    char                CrdSellUnderlying;      ///< 融券卖出标的
    unsigned int        ParticipateIndexNo;    ///< 所属指数数量
    char                MarketMakerFlag;        ///< 做市商标志
    char                CFICode[6];             ///< 证券类别
    char                SecuritySubType[6];     ///< 证券子类别
    char                SecurityTypeID;         ///< 证券属性
    unsigned int        StatusID;               ///< 交易状态
    char                XRXDFlag;               ///< 除权除息标志
    char                TradingMechanism;       ///< 产品交易类型
    char                CrdPriceCheckType;      ///< 提价检查方式
    char                NetVotingFlag;          ///< 网络投票标志
    char                ShrstrurefmFlag;        ///< 股改状态标志
    char                OfferingFlag;           ///< 是否处于要约收购期、是否处于转股期（可转债）、是否处于行权期（权证）  
};
/// 深交所L2证券状态
struct SZSEL2_Status
{
    int                 LocalTimeStamp;         ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;        ///< 数据包头时间YYYYMMDDHHMMSSMMM
    char                Symbol[SYMBOL_LEN];     ///< 证券代码
    char                SecurityTag[5];         ///< 成交证券简称前缀
    char                TradeStage;             ///< 证券竞价状态
    char                CrdBuyStatus;           ///< 当前融资买入开放状态
    char                CrdSellStatus;          ///< 当前融券卖出开放状态
    char                SubScribeStatus;        ///< 是否允许申购（开放基金）、或允许转股（可转债）或允许行权（权证）
    char                RedemptionStatus;       ///< 是否允许赎回（开放基金）、或允许回售（可转债）
    char                WarrantCreated;         ///< 当日是否有创设发生
    char                WarrantDropped;         ///< 当日是否有注销发生
};
/// 深交所L2实时行情
struct SZSEL2_Quotation
{
    int                 LocalTimeStamp;         ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;        ///< 数据包头时间YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< 数据生成时间HHMMSSMMM，对应tag10178
    char                Symbol[SYMBOL_LEN];     ///< 证券代码
    double              PreClosePrice;          ///< 昨日收盘价,3位小数
    double              OpenPrice;              ///< 开盘价,3位小数
    double              HighPrice;              ///< 最高价,3位小数
    double              LowPrice;               ///< 最低价,3位小数
    double              LastPrice;              ///< 现价,3位小数
    unsigned long long  TotalNo;                ///< 成交笔数
    unsigned long long  TotalVolume;            ///< 成交总量
    double              TotalAmount;            ///< 成交总金额,3位小数
    unsigned long long  TotalPosition;          ///< 合约持仓量
    double              PERatio1;               ///< 市盈率 1,2位小数
    double              PERatio2;               ///< 市盈率 2,2位小数
    char                CloseFlag;              ///< 闭市标志
    unsigned long long  TotalSellOrderVolume;   ///< 委托卖出总量（有效竞价范围内）
    double              WtAvgSellPrice;         ///< 加权平均卖出价格（有效竞价范围内）,3位小数
    unsigned int        SellLevelNo;            ///< 申卖档位数（价格由低至高）
    union
    {
        BuySellLevelInfo3    SellLevel[LEVEL_TEN];       ///< 十档卖行情
        struct
        {
            double              SellPrice01;            ///< 申卖价,3位小数
            unsigned long long  SellVolume01;           ///< 申卖量
            unsigned int        TotalSellOrderNo01;     ///< 卖价位总委托笔数
            double              SellPrice02;            ///< 申卖价
            unsigned long long  SellVolume02;           ///< 申卖量
            unsigned int        TotalSellOrderNo02;     ///< 卖价位总委托笔数
            double              SellPrice03;            ///< 申卖价
            unsigned long long  SellVolume03;           ///< 申卖量
            unsigned int        TotalSellOrderNo03;     ///< 卖价位总委托笔数
            double              SellPrice04;            ///< 申卖价
            unsigned long long  SellVolume04;           ///< 申卖量
            unsigned int        TotalSellOrderNo04;     ///< 卖价位总委托笔数
            double              SellPrice05;            ///< 申卖价
            unsigned long long  SellVolume05;           ///< 申卖量
            unsigned int        TotalSellOrderNo05;     ///< 卖价位总委托笔数
            double              SellPrice06;            ///< 申卖价
            unsigned long long  SellVolume06;           ///< 申卖量
            unsigned int        TotalSellOrderNo06;     ///< 卖价位总委托笔数
            double              SellPrice07;            ///< 申卖价
            unsigned long long  SellVolume07;           ///< 申卖量
            unsigned int        TotalSellOrderNo07;     ///< 卖价位总委托笔数
            double              SellPrice08;            ///< 申卖价
            unsigned long long  SellVolume08;           ///< 申卖量
            unsigned int        TotalSellOrderNo08;     ///< 卖价位总委托笔数
            double              SellPrice09;            ///< 申卖价
            unsigned long long  SellVolume09;           ///< 申卖量
            unsigned int        TotalSellOrderNo09;     ///< 卖价位总委托笔数
            double              SellPrice10;            ///< 申卖价
            unsigned long long  SellVolume10;           ///< 申卖量
            unsigned int        TotalSellOrderNo10;     ///< 卖价位总委托笔数
        };
    };
    unsigned int        SellLevelQueueNo01;                 ///< 卖一档揭示委托笔数
    unsigned int        SellLevelQueue[ORDER_LEVEL_FIFTY];  ///< 卖一档委托数量，50笔，不足补0
    unsigned long long  TotalBuyOrderVolume;                ///< 委托买入总量（有效竞价范围内）
    double              WtAvgBuyPrice;                      ///< 加权平均买入价格（有效竞价范围内）,3位小数
    unsigned int        BuyLevelNo;                         ///< 申买档位数（价格由高至低）
    union
    {
        BuySellLevelInfo3    BuyLevel[LEVEL_TEN];       ///< 十档买行情
        struct
        {
            double              BuyPrice01;             ///< 申买价,3位小数
            unsigned long long  BuyVolume01;            ///< 申买量
            unsigned int        TotalBuyOrderNo01;      ///< 买价位总委托笔数
            double              BuyPrice02;             ///< 申买价
            unsigned long long  BuyVolume02;            ///< 申买量
            unsigned int        TotalBuyOrderNo02;      ///< 买价位总委托笔数
            double              BuyPrice03;             ///< 申买价
            unsigned long long  BuyVolume03;            ///< 申买量
            unsigned int        TotalBuyOrderNo03;      ///< 买价位总委托笔数
            double              BuyPrice04;             ///< 申买价
            unsigned long long  BuyVolume04;            ///< 申买量
            unsigned int        TotalBuyOrderNo04;      ///< 买价位总委托笔数
            double              BuyPrice05;             ///< 申买价
            unsigned long long  BuyVolume05;            ///< 申买量
            unsigned int        TotalBuyOrderNo05;      ///< 买价位总委托笔数
            double              BuyPrice06;             ///< 申买价
            unsigned long long  BuyVolume06;            ///< 申买量
            unsigned int        TotalBuyOrderNo06;      ///< 买价位总委托笔数
            double              BuyPrice07;             ///< 申买价
            unsigned long long  BuyVolume07;            ///< 申买量
            unsigned int        TotalBuyOrderNo07;      ///< 买价位总委托笔数
            double              BuyPrice08;             ///< 申买价
            unsigned long long  BuyVolume08;            ///< 申买量
            unsigned int        TotalBuyOrderNo08;      ///< 买价位总委托笔数
            double              BuyPrice09;             ///< 申买价
            unsigned long long  BuyVolume09;            ///< 申买量
            unsigned int        TotalBuyOrderNo09;      ///< 买价位总委托笔数
            double              BuyPrice10;             ///< 申买价
            unsigned long long  BuyVolume10;            ///< 申买量
            unsigned int        TotalBuyOrderNo10;      ///< 买价位总委托笔数
        };
    };
    unsigned int        BuyLevelQueueNo01;                  ///< 买一档揭示委托笔数
    unsigned int        BuyLevelQueue[ORDER_LEVEL_FIFTY];   ///< 买一档委托数量，50笔，不足补0
};
/// 深交所L2指数行情
struct SZSEL2_Index
{
    int                 LocalTimeStamp;         ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;        ///< 数据包头时间YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< 数据生成时间HHMMSSMMM，对应tag10178
    char                Symbol[SYMBOL_LEN];     ///< 证券代码
    double              PreClosePrice;          ///< 前收盘指数,4位小数
    double              OpenPrice;              ///< 今开盘指数,4位小数
    double              HighPrice;              ///< 最高指数,4位小数
    double              LowPrice;               ///< 最低指数,4位小数
    double              LastPrice;              ///< 最新指数,4位小数
    double              TotalAmount;            ///< 参与计算相应指数的成交金额,3位小数
    unsigned long long  TotalNo;                ///< 参与计算相应指数的成交笔数
    unsigned long long  TotalVolume;            ///< 参与计算相应指数的交易数量
    char                CloseFlag;              ///< 闭市标志
};
/// 深交所L2逐笔委托
struct SZSEL2_Order
{
    int                 LocalTimeStamp;         ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;        ///< 数据包头时间YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< 委托时间HHMMSSMMM，对应tag8500
    unsigned int        SetID;                  ///< 证券集代号
    unsigned int        RecID;                  ///< 委托索引
    char                Symbol[SYMBOL_LEN];     ///< 证券代码
    double              OrderPrice;             ///< 委托价格,3位小数
    unsigned int        OrderVolume;            ///< 委托数量
    char                OrderType;              ///< 委托类别
    char                OrderCode;              ///< 委托代码
};
/// 深交所L2逐笔成交
struct SZSEL2_Transaction
{
    int                 LocalTimeStamp;         ///< 数据接收时间HHMMSSMMM
    long long           PacketTimeStamp;        ///< 数据包头时间YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< 成交时间HHMMSSMMM，对应tag10013
    unsigned int        SetID;                  ///< 证券集代号
    unsigned int        RecID;                  ///< 成交索引
    unsigned int        BuyOrderID;             ///< 买方委托索引
    unsigned int        SellOrderID;            ///< 卖方委托索引
    char                Symbol[SYMBOL_LEN];     ///< 证券代码
    double              TradePrice;             ///< 成交价格,3位小数
    unsigned int        TradeVolume;            ///< 成交数量
    char                TradeCode;              ///< 成交代码
    char                TradeType;              ///< 成交类别
};
/// 中金所L2实时行情
struct CFFEXL2_Quotation
{
    int                 LocalTimeStamp;              ///< 本地时间 
    int                 TradeDate;                   ///< 成交日期 YYYYMMDD 统一为交易归属日期，后续交易所均遵循此原则
    int                 Time;                        ///< 数据生成时间 两个字段合成一个：HHMMSSMMM
    char                Symbol[SYMBOL_LEN];          ///< 证券代码
    double              PreClosePrice;               ///< 昨收价 指数有效小数位为2位，国债有效小数位为3位
    double              PreSettlePrice;              ///< 昨结算 指数有效小数位为2位，国债有效小数位为3位
    double              OpenPrice;                   ///< 开盘价 指数有效小数位为2位，国债有效小数位为3位
    double              HighPrice;                   ///< 最高价 指数有效小数位为2位，国债有效小数位为3位
    double              LowPrice;                    ///< 最低价 指数有效小数位为2位，国债有效小数位为3位
    double              TradePrice;                  ///< 最新价 指数有效小数位为2位，国债有效小数位为3位
    double              ClosePrice;                  ///< 收盘价 指数有效小数位为2位，国债有效小数位为3位
    double              SettlePrice;                 ///< 结算价 指数有效小数位为2位，国债有效小数位为3位
    double              PriceUpLimit;                ///< 涨停价 指数有效小数位为2位，国债有效小数位为3位
    double              PriceDownLimit;              ///< 跌停价 指数有效小数位为2位，国债有效小数位为3位
    unsigned long long  PreTotalPosition;            ///< 昨持仓量
    unsigned long long  TotalPosition;               ///< 持仓量
    double              PreDelta;                    ///< 昨虚实度 前一日对冲值
    double              Delta;                       ///< 今虚实度 对冲值：期权价格变化/期货价格变化
    char                SettleGroupID[SETTLE_LEN];   ///< 结算组代码
    unsigned int        SettleID;                    ///< 结算编号
    unsigned long long  TotalVolume;                 ///< 总成交量
    double              TotalAmount;                 ///< 总成交额 有效小数位为3位
    union
    {
        BuySellLevelInfo    SellLevel[LEVEL_FIVE];   ///< 五档卖行情
        struct
        {
            double              SellPrice01;         ///< 卖价一 指数有效小数位为2位，国债有效小数位为3位
            unsigned long long  SellVolume01;        ///< 卖量一
            double              SellPrice02;         ///< 卖价二 指数有效小数位为2位，国债有效小数位为3位
            unsigned long long  SellVolume02;        ///< 卖量二
            double              SellPrice03;         ///< 卖价三 指数有效小数位为2位，国债有效小数位为3位
            unsigned long long  SellVolume03;        ///< 卖量三
            double              SellPrice04;         ///< 卖价四 指数有效小数位为2位，国债有效小数位为3位
            unsigned long long  SellVolume04;        ///< 卖量四
            double              SellPrice05;         ///< 卖价五 指数有效小数位为2位，国债有效小数位为3位
            unsigned long long  SellVolume05;        ///< 卖量五
        };
    };
    union
    {
        BuySellLevelInfo    BuyLevel[LEVEL_FIVE];    ///< 五档买行情
        struct
        {
            double              BuyPrice01;          ///< 买价一 指数有效小数位为2位，国债有效小数位为3位
            unsigned long long  BuyVolume01;         ///< 买量一
            double              BuyPrice02;          ///< 买价二 指数有效小数位为2位，国债有效小数位为3位
            unsigned long long  BuyVolume02;         ///< 买量二
            double              BuyPrice03;          ///< 买价三 指数有效小数位为2位，国债有效小数位为3位
            unsigned long long  BuyVolume03;         ///< 买量三
            double              BuyPrice04;          ///< 买价四 指数有效小数位为2位，国债有效小数位为3位
            unsigned long long  BuyVolume04;         ///< 买量四
            double              BuyPrice05;          ///< 买价五 指数有效小数位为2位，国债有效小数位为3位
            unsigned long long  BuyVolume05;         ///< 买量五
        };
    };
};
/// 中金所L2静态数据
typedef CFFEXL2_Quotation CFFEXL2_Static;
/// 郑商所静态数据
struct CZCEL1_Static
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 郑商所实时行情
struct CZCEL1_Quotation
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 大商所静态数据
struct DCEL1_Static
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 大商所L1深度行情
struct DCEL1_Quotation
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 大商所L1套利深度行情
struct DCEL1_ArbiQuotation
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 大商所L2静态数据
struct DCEL2_Static
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 大商所L2最优深度行情
struct DCEL2_Quotation
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 大商所L2最优套利深度行情
struct DCEL2_ArbiQuotation
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 大商所L2实时结算价
struct DCEL2_RealTimePrice
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 大商所L2委托统计行情
struct DCEL2_OrderStatistic
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 大商所L2分价成交量行情
struct DCEL2_MarchPriceQty
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};
/// 上期所静态数据
struct SHFEL1_Static
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码
};

/// 上期所实时行情
struct SHFEL1_Quotation
{
    char    Symbol[SYMBOL_LEN];     ///< 证券代码

};

/// 证券代码
struct StockSymbol
{
    char    Symbol[SYMBOL_LEN + MARKET_TAG_LEN];        ///< 查询个股列表返回的股票代码，带市场标志
};

/// 服务器地址
struct ServerState
{
    MsgType msgType;            ///< 消息类型
    char    IP[16];             ///< 服务器地址，127.0.0.1
    unsigned short   Port;      ///< 端口
    bool    Connected;          ///< 连接状态，true-连接中，false-未连接
};

#pragma pack()





#endif // GTA_QTS_STRUCT_H_
