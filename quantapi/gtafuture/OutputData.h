///
/// @file    OutputData.h
/// @brief   下发数据结构
///

#ifndef _OUTPUT_DATA_H
#define _OUTPUT_DATA_H

// 用于连接V1.5版本分发服务使用，1.5和1.7分发服务上期所结构体不同
#define OLD_DISTRISERVER
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
typedef __int64            INT64;
typedef unsigned int UINT32, *PUINT32;
typedef unsigned long       ULONG;
typedef unsigned short      UINT16;
typedef unsigned char UINT8, *PUINT8;
#endif
#pragma pack(1)

/// 中金所股指期货行情输出结构. 
typedef struct _ZJS_Future_Output
{
    char    szStockNo[6];           ///< 期货代码 
    double  dChg;                   ///< 涨跌 
    double  dChgPct;                ///< 涨跌幅 
    double  dVolume;                ///< 当日总量 
    double  dAmount;                ///< 成交总金额 
    double  dLastTrade;             ///< 成交价 
    double  dLastVolume;            ///< 瞬量 
    double  dUpB;                   ///< 涨停价 
    double  dLowB;                  ///< 跌停价 
    double  dHigh;                  ///< 当日最高 
    double  dLow;                   ///< 当日最低 
    double  dYclose;                ///< 昨收 
    double  dOpen;                  ///< 开盘 
    double  dAvgPrice;              ///< 均价 
    double  dPriceGap;              ///< 檔差 
    double  dBuyprice1;             ///< 买价一 
    double  dBuyprice2;             ///< 买价二 
    double  dBuyprice3;             ///< 买价三 
    double  dBuyprice4;             ///< 买价四 
    double  dBuyprice5;             ///< 买价五 
    double  dBuyvol1;               ///< 买量一 
    double  dBuyvol2;               ///< 买量二 
    double  dBuyvol3;               ///< 买量三 
    double  dBuyvol4;               ///< 买量四 
    double  dBuyvol5;               ///< 买量五 
    double  dSellprice1;            ///< 卖价一 
    double  dSellprice2;            ///< 卖价二 
    double  dSellprice3;            ///< 卖价三 
    double  dSellprice4;            ///< 卖价四 
    double  dSellprice5;            ///< 卖价五 
    double  dSellvol1;              ///< 卖量一 
    double  dSellvol2;              ///< 卖量二 
    double  dSellvol3;              ///< 卖量三 
    double  dSellvol4;              ///< 卖量四 
    double  dSellvol5;              ///< 卖量五 
    double  dPreOpenInterest;       ///< 昨持仓量 
    double  dOpenInterest;          ///< 持仓量 
    double  dSettlementPrice;       ///< 今结算价
    char    szTradingDay[9];        ///< 交易日期 YYYYMMDD
    char    szUpdateTime[9];        ///< 更新时间 HH:MM:SS
    double  dPreSettlementPrice;    ///< 昨日结算价 
    // 新增字段
    char    szSettlementGroupID[9]; ///< 结算组代码
    int     nSettleID;              ///< 结算编号
    double  dClosePrice;            ///< 今收盘
    double  dPreDelta;              ///< 昨虚实度
    double  dCurrDelta;             ///< 今虚实度
    int     nUpdateMillisec;        ///< 最后修改毫秒
}ZJS_Future_Output;

/// 中金所股指期权行情输出结构. 
typedef struct _CFIO_Output
{
    char    szStockNo[31];          ///< 期权代码 
    int     dVolume;                ///< 当日总量 
    double  dAmount;                ///< 成交总金额 
    double  dLastTrade;             ///< 成交价
    double  dUpB;                   ///< 涨停价 
    double  dLowB;                  ///< 跌停价 
    double  dHigh;                  ///< 当日最高 
    double  dLow;                   ///< 当日最低 
    double  dYclose;                ///< 昨收 
    double  dOpen;                  ///< 开盘
    double  dPreOpenInterest;       ///< 昨持仓量 
    double  dOpenInterest;          ///< 持仓量 
    double  dSettlementPrice;       ///< 今结算价
    char    szTradingDay[9];        ///< 交易日期 YYYYMMDD
    char    szUpdateTime[9];        ///< 更新时间 HH:MM:SS
    int     nUpdateMillisec;        ///< 最后修改毫秒
    double  dPreSettlementPrice;    ///< 昨日结算价 
    char    szSettlementGroupID[9]; ///< 结算组代码
    int     nSettleID;              ///< 结算编号
    double  dClosePrice;            ///< 今收盘
    double  dPreDelta;              ///< 昨虚实度
    double  dCurrDelta;             ///< 今虚实度
    double  dBuyprice1;             ///< 买价一 
    int     dBuyvol1;               ///< 买量一 
    double  dBuyprice2;             ///< 买价二 
    int     dBuyvol2;               ///< 买量二 
    double  dBuyprice3;             ///< 买价三 
    int     dBuyvol3;               ///< 买量三 
    double  dBuyprice4;             ///< 买价四 
    int     dBuyvol4;               ///< 买量四 
    double  dBuyprice5;             ///< 买价五 
    int     dBuyvol5;               ///< 买量五 
    double  dSellprice1;            ///< 卖价一 
    int     dSellvol1;              ///< 卖量一 
    double  dSellprice2;            ///< 卖价二 
    int     dSellvol2;              ///< 卖量二 
    double  dSellprice3;            ///< 卖价三 
    int     dSellvol3;              ///< 卖量三 
    double  dSellprice4;            ///< 卖价四 
    int     dSellvol4;              ///< 卖量四 
    double  dSellprice5;            ///< 卖价五 
    int     dSellvol5;              ///< 卖量五 
}CFIO_Output;

/// 郑州商品期货行情输出结构. 
typedef struct _ZZ_Future_Output
{
    char    szInstrumentID[20];     ///< 合约编码 
    double  dPreClosePrice;         ///< 前收盘价格 
    double  dPreSettlePrice;        ///< 前结算价格 
    double  dOpenPrice;             ///< 开盘价 
    double  dBidPrice;              ///< 买入价格 
    DWORD   dwBidSize;              ///< 买入数量 
    double  dAskPrice;              ///< 卖出价 
    DWORD   dwAskSize;              ///< 卖出数量 
    double  dClosePrice;            ///< 最新价 
    DWORD   dwOpenInterest;         ///< 持仓量 
    double  dHighPrice;             ///< 最高价 
    double  dLowPrice;              ///< 最低价 
    double  dClosePrice2;           ///< 收盘价 
    double  dSettlePrice;           ///< 当日交割结算价 
    double  dClearPrice;            ///< 结算价 
    double  dAveragePrice;          ///< 均价 
    double  dListHighPrice;         ///< 历史最高成交价格 
    double  dListLowPrice;          ///< 历史最低成交价格 
    double  dUpperLimit;            ///< 涨停板 
    double  dLowerLimit;            ///< 跌停板 
    DWORD   dwTotalVolume;          ///< 总成交量 
    DWORD   dwTradingDate;          ///< 日期 
    DWORD   dwTradingTime;          ///< 时间 
    DWORD   dwTransaction;          ///< 成交笔数 
}ZZ_Future_Output;
#pragma pack()

/// 大连商品期货行情输出结构. 
typedef struct _DL_Future_Output
{
    WORD        wSize;
    BYTE        btQuotFlag;         ///< 1:BastQuot, 2:ArbiBastQuot 

    char        szTradingDate[8];   ///< 交易日期 
    char        szContractID[20];   ///< 合约号 
    UINT        nID;                ///< 事务编号 
    char        szContractName[40]; ///< 合约名称 
    double      dClosePrice;        ///< 最新价 
    double      dHighPrice;         ///< 最高价 
    double      dLowPrice;          ///< 最低价 
    UINT        nTotalVolum;        ///< 最新成交量 
    UINT        nPrevTotalVolume;   ///< 成交量 
    double      dTurnover;          ///< 成交额 
    UINT        nPrevOpenInterest;  ///< 初始持仓量 
    UINT        nOpenInterest;      ///< 持仓量 
    INT         nInterestChg;       ///< 持仓量变化 
    double      dClearPrice;        ///< 今结算价 
    double      dListLowPrice;      ///< 历史最低价 
    double      dListHighPrice;     ///< 历史最高价 
    double      dUpperLimit;        ///< 涨停板 
    double      dLowerLimit;        ///< 跌停板 
    double      dLastClearPrice;    ///< 上日结算价 
    double      dClosePrice3;       ///< 上日收盘价 
    double      dBidPrice;          ///< 申买价 
    UINT        nBidSize;           ///< 申买量 
    UINT        nBidImplyQty;       ///< 申买推导量 
    double      dAskPrice;          ///< 申卖价 
    UINT        nAskSize;           ///< 申卖量 
    UINT        nAskImplyQty;       ///< 申卖推导量 
    double      dAveragePrice;      ///< 当日均价 
    char        szTradingTime[12];  ///< 生成时间 
    double      dOpenPrice;         ///< 开盘价 
    double      dClosePrice2;       ///< 收盘价 
}DL_Future_Output;  //size:248

/// 上海商品期货行情输出结构. 
typedef struct _SH_SFX_Output
{
    char    TradingDay[9];          ///< 交易日 
    char    SettlementGroupID[9];   ///< 结算组代码 
    int     SettlementID;           ///< 结算编号 
    double  LastPrice;              ///< 最新价 
    double  PreSettlementPrice;     ///< 昨结算 
    double  PreClosePrice;          ///< 昨收盘 
    double  PreOpenInterest;        ///< 昨持仓量 
    double  OpenPrice;              ///< 今开盘 
    double  HighestPrice;           ///< 最高价 
    double  LowestPrice;            ///< 最低价 
    int     Volume;                 ///< 数量 
    double  Turnover;               ///< 成交金额 
    double  OpenInterest;           ///< 持仓量 
    double  ClosePrice;             ///< 今收盘 
    double  SettlementPrice;        ///< 今结算 
    double  UpperLimitPrice;        ///< 涨停板价 
    double  LowerLimitPrice;        ///< 跌停板价 
    double  PreDelta;               ///< 昨虚实度 
    double  CurrDelta;              ///< 今虚实度 
    char    UpdateTime[9];          ///< 最后修改时间 
    int     UpdateMillisec;         ///< 最后修改毫秒 
    char    InstrumentID[31];       ///< 合约代码 
    double  BidPrice1;              ///< 申买价一 
    int     BidVolume1;             ///< 申买量一 
    double  AskPrice1;              ///< 申卖价一 
    int     AskVolume1;             ///< 申卖量一 
    double  BidPrice2;              ///< 申买价二 
    int     BidVolume2;             ///< 申买量二 
    double  AskPrice2;              ///< 申卖价二 
    int     AskVolume2;             ///< 申卖量二 
    double  BidPrice3;              ///< 申买价三 
    int     BidVolume3;             ///< 申买量三 
    double  AskPrice3;              ///< 申卖价三 
    int     AskVolume3;             ///< 申卖量三 
    double  BidPrice4;              ///< 申买价四 
    int     BidVolume4;             ///< 申买量四     
    double  AskPrice4;              ///< 申卖价四     
    int     AskVolume4;             ///< 申卖量四 
    double  BidPrice5;              ///< 申买价五 
    int     BidVolume5;             ///< 申买量五 
    double  AskPrice5;              ///< 申卖价五 
    int     AskVolume5;             ///< 申卖量五 
    DWORD   dwTransaction;          ///< 成交笔数 
    char    ActionDay[9];           ///< 业务发生日期 YYYYMMDD
}SH_SFX_Output;

#pragma pack(1)
/// 香港行情输出结构. 
typedef struct _STSendTradeInfo
{
    char szStockCode[16];                           ///< 股票代码 
    char szStockName[64];                           ///< 股票名称 
    DWORD dwDate;                                   ///< YYYYMMDD 
    DWORD dwTime;                                   ///< HHMMSS 
    float fHighPrice;                               ///< 最高价 
    float fLowPrice;                                ///< 最低价 
    float fDifferencePrice;                         ///< 涨跌 
    float fDiffRate;                                ///< 涨跌率 
    float fPrice;                                   ///< 成交价 
    float fAveragePrice;                            ///< 均价 
    LONGLONG llLastVol;                             ///< 现手 
    float fOpenPrice;                               ///< 开盘价 
    float fClosePrice;                              ///< 收盘价 
    float fPreClosePrice;                           ///< 昨收价 
    LONGLONG llTotalMoney;                          ///< 开盘至今成交金额 
    LONGLONG llTotalAmount;                         ///< 开盘至今成交量 
    float fNominalPrice;                            ///< 现盘价 
    char cNominalPriceType;                         ///< 现盘价类型 
    float fIndicativeEquilibriumPrice;              ///< 参考平衡价格 
    LONGLONG llIndicativeEquilibriumVolume;         ///< 参考平衡成交量 
    char cPublicTradeType;                          ///< 交易类型 

    char cOrderSide;                                ///< 买卖方向 

    DWORD   Sv10;       ///< 卖量10
    DWORD   Sv9;        ///< 卖量9
    DWORD   Sv8;        ///< 卖量8
    DWORD   Sv7;        ///< 卖量7
    DWORD   Sv6;        ///< 卖量6
    DWORD   Sv5;        ///< 卖量5
    DWORD   Sv4;        ///< 卖量4
    DWORD   Sv3;        ///< 卖量3
    DWORD   Sv2;        ///< 卖量2
    DWORD   Sv1;        ///< 卖量1

    float   S10;        ///< 卖价10
    float   S9;         ///< 卖价9
    float   S8;         ///< 卖价8
    float   S7;         ///< 卖价7
    float   S6;         ///< 卖价6
    float   S5;         ///< 卖价5
    float   S4;         ///< 卖价4
    float   S3;         ///< 卖价3
    float   S2;         ///< 卖价2
    float   S1;         ///< 卖价1

    DWORD   Bv10;       ///< 买量10
    DWORD   Bv9;        ///< 买量9
    DWORD   Bv8;        ///< 买量8
    DWORD   Bv7;        ///< 买量7
    DWORD   Bv6;        ///< 买量6
    DWORD   Bv5;        ///< 买量5
    DWORD   Bv4;        ///< 买量4
    DWORD   Bv3;        ///< 买量3
    DWORD   Bv2;        ///< 买量2
    DWORD   Bv1;        ///< 买量1

    float   B10;        ///< 买价10
    float   B9;         ///< 买价9
    float   B8;         ///< 买价8
    float   B7;         ///< 买价7
    float   B6;         ///< 买价6
    float   B5;         ///< 买价5
    float   B4;         ///< 买价4
    float   B3;         ///< 买价3
    float   B2;         ///< 买价2
    float   B1;         ///< 买价1

    LONGLONG llVolumeSum;    ///< 自动对盘成交量  (PublicTradeType为' '值的累积成交量) 
    LONGLONG llAmountSum;    ///< 自动对盘成交额   每次自动对盘成交量*成交价 

#ifdef _WIN32
    _STSendTradeInfo()
    {
        memset(this, 0, sizeof(STSendTradeInfo));
    }
#endif
}STSendTradeInfo;

/// 香港初始化数据输出结构. 
typedef struct _STSendBaseStockInfo
{
    char  szStockCode[16];            ///< 股票代码 
    char  szStockName[64];            ///< 股票名称 
    char  szStockShortName[64];       ///< 股票简称 
    float fPreClosePrice;             ///< 昨收盘价 
    char  cPreCloseType;              ///< 昨收盘类型 
    long  lLotSize;                   ///< 每手股数 
    char  cShortSellFlag;             ///< 卖空标志 'Y' 'N' 
    char  cSuspensionFlag;            ///< 停牌标志 'Y' 'N' 
    char  cIntraDayShortsellingFlag;  ///< 隔天卖空标志 'Y' 'N' 
    char  cListingStatus;             ///< 上市状态 'L','D','P' 
    DWORD dwMarketCode;               ///< 市场代码 
    char  cInstrumentType;            ///< 1:‘BOND’,2:‘BWRT’3:‘EQTY’ 4:‘TRST’5:‘WRNT 
    WORD  wCurrencyUnit;              ///< 货币单位 
    char  szCurrencyCode[4];          ///< 货币代码 
    char  szSpreadTableCode[2];       ///< 价位表代码 
    char  szReserve[24];              ///< 保留 
#ifdef _WIN32
    _STSendBaseStockInfo() 
    {
        memset(this, 0, sizeof(STSendBaseStockInfo));
    }
#endif
}STSendBaseStockInfo;

/// 香港SP代码表数据输出结构. 
typedef struct _STSendSPTableInfo
{
    WORD  wSPCode;                  ///< Spread Table Code 
    char  spreadTableCode[2];       ///< Spread Table Code    X(2) 
    float priceFrom;                ///< Price From            B(4) 
    WORD  numberOfItems;            ///< Number of Items        B(2) 
    /// 代码表单项结构.
    struct STItemTable
    {
        float priceTo;              ///< Price To            B(4) 
        float SpreadValue;          ///< Spread Value        B(2) 
    };                   ///< Item Table (max 52) 
    // 后跟numberOfItems个STItemTable.
}STSendSPTableInfo;

/// 上海 Level1初始行情输出结构. 
typedef struct _SH_Level1_Output
{
    char    szStockNo[6];   ///< 股票代码 
    char    szName[8];      ///< 股票名称 
    char    szDate[9];      ///< 成交日期 
    char    szTime[9];      ///< 成交时间 
    float   fLasttrade;     ///< 成交价 
    double  dVolume;        ///< 当日总量 
    double  dAmount;        ///< 成交总金额 
    float   fpTrans;        ///< 成交笔数 
    float   fOpen;          ///< 开盘价格 
    float   fYClose;        ///< 昨收 
    float   fBuyprice1;     ///< 买价一 
    float   fBuyprice2;     ///< 买价二 
    float   fBuyprice3;     ///< 买价三 
    float   fBuyprice4;     ///< 买价四 
    float   fBuyprice5;     ///< 买价五 
    float   fBuyvol1;       ///< 买量一 
    float   fBuyvol2;       ///< 买量二 
    float   fBuyvol3;       ///< 买量三 
    float   fBuyvol4;       ///< 买量四 
    float   fBuyvol5;       ///< 买量五 
    float   fSellprice1;    ///< 卖价一 
    float   fSellprice2;    ///< 卖价二 
    float   fSellprice3;    ///< 卖价三 
    float   fSellprice4;    ///< 卖价四 
    float   fSellprice5;    ///< 卖价五 
    float   fSellvol1;      ///< 卖量一 
    float   fSellvol2;      ///< 卖量二 
    float   fSellvol3;      ///< 卖量三 
    float   fSellvol4;      ///< 卖量四 
    float   fSellvol5;      ///< 卖量五 
    float   fLow;           ///< 当日最低 
    float   fHigh;          ///< 当日最高 
    float   fPE;            ///< 市盈率p/e (price/earning) ratio ,  
}SH_Level1_Output, SH_Level1_Output_Ex;
/// 上海L2和上海L1共用的盘前数据结构. 
typedef struct _SH_L2_Reference_Output
{
    char    Symbol[10];                 ///< 证券名称 
    char    SecurityID[7];              ///< 证券代码 
    char    SecurityIDSource[5];        ///< 证券代码源 
    char    szSecurityAltID[7];         ///< 备选证券代码 
    char    szSecurityAltIDSource[4];   ///< 备选证券代码源 
    char    szCFICode[5];               ///< 证券类别 
    char    SecurityExchange[7];        ///< 交易所代码 
    char    SecuritySubType[5];         ///< 证券子类别 
    double  ContractMultiplier;         ///< 债券折合成回购标准券的比例  3dec 
    char    SecurityDesc[20];           ///< 证券描述 
    double  PreClosePx;                 ///< 昨收盘价 
    char    RoundLot[5];                ///< 交易单位 
    DWORD   InterestAccrualDate;        ///< 起息日 (20050708) 
    double  price;                      ///< 发行價 
    char    IndustryClassification[5];  ///< 行业种类 
    char    Currency[5];                ///< 币种 
    double  ShareFaceValue;             ///< 每股面值 
    UINT64  OutstandingShares;          ///< 总发行量 
    UINT64  PublicFloatShareQuantity;   ///< 流通股数 
    int     SecurityTradingStatus;      ///< 交易状态 
    char    CorporateAction[5];         ///< 除权除息标志 
    DWORD   MaturityDate;               ///< 到期/交割日 
    char    CouponRate[2];              ///< A = annually, H = half-yearly 
    DWORD   CouponPaymentDate;          ///< 付息日 
    DWORD   LastInterestPaymentDate;    ///< 上一次理论付息日 
    DWORD   NextInterestPaymentDate;    ///< 下一次理论付息日 
    double  ConversionPrice;            ///< 行权/转股价格 
    char    Residualmaturity[13];       ///< 剩余时间 
    double  AccruedInterestAmt;         ///< 应计利息 
    char    BondType[2];                ///< 债券类型 
    char    American_European[2];       ///< 美式/欧式 
    char    CallOrPut[2];               ///< Call/Put标志 
    char    Underlying[7];              ///< 基础证券,为基础证券代码 
    char    Issuer[20];                 ///< 发行机构 
    double  CVRatio;                    ///< 行权比例   4dec 
    double  _CouponRate;                ///< 票面利率   6dec 
    DWORD   ConversionPeriod;           ///< 行权时间 
    double  InterestRate;               ///< 当年利率  6dec 
    char    szStateID[8];               ///< 停牌标志 
    float   fUpperLmtPrc;               ///< 涨停价 
    float   fLowerLmtPrc;               ///< 跌停价 
}SH_L2_Reference_Output;

/// 深圳 Level1初始化信息输出结构. 
typedef struct  _SZ_Init_Output
{
    char   chDate[9];   ///< 成交日期 
    char   chTime[9];   ///< 成交时间 
    char   XXZQDM[6];   ///< 1证券代码 
    char   XXZQJC[8];   ///< 2证券简称 
    char   XXJCQZ[4];   ///< 3证券简称前缀 
    char   XXYWJC[20];  ///< 4英文简称 
    char   XXJCZQ[6];   ///< 5基础证券 
    char   XXISIN[12];  ///< 6ISIN 编码 
    char   XXHYZL[3];   ///< 7行业种类 
    char   XXHBZL[2];   ///< 8货币种类 
    float  XXMGMZ;      ///< 9每股面值 
    double XXZFXL;      ///< 10总发行量 
    double XXLTGS;      ///< 11流通股数 
    double XXSNLR;      ///< 12上年每股利润 
    double XXBNLR;      ///< 13本年每股利润 
    double XXLJJZ;      ///< 14基金份额累计净值 
    float  XXJSFL;      ///< 15经手费率 
    float  XXYHSL;      ///< 16印花税率 
    float  XXGHFL;      ///< 17过户费率 
    char   XXSSRQ[8];   ///< 18上市日期 
    char   XXQXRQ[8];   ///< 19债券起息日 
    char   XXDJRQ[8];   ///< 20到期/交割日 
    float  XXJYDW;      ///< 21交易单位 
    float  XXBLDW;      ///< 22买数量单位 
    float  XXSLDW;      ///< 23卖数量单位 
    double XXMBXL;      ///< 24每笔委托限量 
    float  XXJGDW;      ///< 25价格档位 
    float  XXJHCS;      ///< 26集合竞价限价参数 
    float  XXLXCS;      ///< 27连续竞价限价参数 
    float  XXXJXZ;      ///< 28限价参数性质 
    double XXZTJG;      ///< 29涨停价格 
    double XXDTJG;      ///< 30跌停价格 
    double XXJGSX;      ///< 31大宗交易价格上限2 
    double XXJGXX;      ///< 32大宗交易价格下限2 
    float  XXZHBL;      ///< 33债券折合比例 
    float  XXDBZSL;     ///< 34担保物折算率 
    char   XXRZBD;      ///< 35融资标的标志 
    char   XXRQBD;      ///< 36融券标的标志 
    char   XXCFBZ;      ///< 37成份股标志 
    char   XXZSBZ;      ///< 38做市商标志 
    char   XXSCDM[2];   ///< 39所属市场代码 
    char   XXZQLB[4];   ///< 40证券类别 
    char   XXZQJB;      ///< 41证券级别 
    char   XXZQZT;      ///< 42证券状态 
    char   XXJYLX;      ///< 43交易类型 
    char   XXJYJD;      ///< 44产品交易阶段 
    char   XXTPBZ;      ///< 45暂停交易标志 
    char   XXRZZT;      ///< 46融资交易状态 
    char   XXRQZT;      ///< 47融券交易状态 
    char   XXRQJX;      ///< 48融券卖出价格限制 
    char   XXWLTP;      ///< 49网络投票标志 
    char   XXYWZT[8];   ///< 50其他业务状态 
    char   XXGXSJ[6];   ///< 51记录更新时间 
    char   XXMARK[12];  ///< 52备用字段 
    char   XXBYBZ;      ///< 53备用标志 
}SZ_Init_Output;

/// 深圳 Level1初始行情输出结构. 
typedef struct _SZ_Level1_Output
{
    char    szStockNo[6];   ///< 股票代码 
    char    szName[8];      ///< 股票名称 
    char    szDate[9];      ///< 成交日期 
    char    szTime[9];      ///< 成交时间 
    float   fLasttrade;     ///< 成交价 
    double  dVolume;        ///< 当日总量 
    double  dAmount;        ///< 成交总金额 
    float   fpTrans;        ///< 成交笔数 
    float   fOpen;          ///< 开盘价格 
    float   fYClose;        ///< 昨收 
    float   fBuyprice1;     ///< 买价一 
    float   fBuyprice2;     ///< 买价二 
    float   fBuyprice3;     ///< 买价三 
    float   fBuyprice4;     ///< 买价四 
    float   fBuyprice5;     ///< 买价五 
    float   fBuyvol1;       ///< 买量一 
    float   fBuyvol2;       ///< 买量二 
    float   fBuyvol3;       ///< 买量三 
    float   fBuyvol4;       ///< 买量四 
    float   fBuyvol5;       ///< 买量五 
    float   fSellprice1;    ///< 卖价一 
    float   fSellprice2;    ///< 卖价二 
    float   fSellprice3;    ///< 卖价三 
    float   fSellprice4;    ///< 卖价四 
    float   fSellprice5;    ///< 卖价五 
    float   fSellvol1;      ///< 卖量一 
    float   fSellvol2;      ///< 卖量二 
    float   fSellvol3;      ///< 卖量三 
    float   fSellvol4;      ///< 卖量四 
    float   fSellvol5;      ///< 卖量五 
    float   fLow;           ///< 当日最低 
    float   fHigh;          ///< 当日最高 
    float   fPE;            ///< 市盈率p/e (price/earning) ratio ,  
    float   PE1;            ///< 市盈率1(HQSYL1) 
    double  HQJSD1;         ///< 价格升跌1 
    double  HQJSD2;         ///< 价格升跌2 
    double  HQHYCC;         ///< 合约持仓量 
}SZ_Level1_Output;

/// 外汇实时数据输出. 
typedef struct _FOREX_Contract_Output
{
    char szExchangeID[4];         ///< 外汇ID 
    char cDataType;               ///< 数据类型 
    char cDataGategory;           ///< 数据种类（静态，盘中，盘后） 
    char cDataMode;               ///< 数据模式 
    char szRemarkData[5];         ///< 备注 
    char szSymbolCode[7];         ///< 代码 
    char szTermType[2];           ///< 期限类型 
    char szKoreaTradingDate[8];   ///< 韩国交易日期 
    char szKoreaTradingTime[6];   ///< 韩国交易时间 
    char szTradingDate[8];        ///< 交易日期 
    char szTradingTime[6];        ///< 交易时间 
    float fOpenPrice;             ///< 开盘价 
    float fHighPrice;             ///< 最高价 
    float fLowPrice;              ///< 最低价 
    float fClosePrice;            ///< 收盘价 
    float fChangePrice;           ///< 兑换价     
    float fChangeRate;            ///< 兑换率 
    float fBidPrice1;             ///< 出价 
    char szBidTime[6];            ///< 出价时间 
    float fAskPrice1;             ///< 问价 
    char szAskTime[6];            ///< 问价时间 
    char szContributorCode[4];    ///< 成交代码  
}FOREX_Contract_Output;

/// 上海L2行情价位信息 
typedef struct  _PriceLevel
{
    double size;      ///< 量 
    float  px;        ///< 价 
    int    numOrders; ///< 实际的总委托笔数 
}PriceLevel;

/// UA3202 上海L2市场行情
typedef struct _SH_L2_MarketData
{
    char    MessageType[7];                      ///< 消息类型 
    int     DataTimeStamp;                       ///< 时间 HHMMSS
    int     DataStatus;                          ///< 
    char    SecurityID[7];                       ///< 证券代码 
    float   PreClosePx;                          ///< 昨收盘价 
    float   OpenPx;                              ///< 开盘价 
    float   HighPx;                              ///< 最高价 
    float   LowPx;                               ///< 最低价 
    float   LastPx;                              ///< 现价 
    float   ClosePx;                             ///< 今日收盘价格 
    char    InstrumentStatus[8];                 ///< 当前品种状态 
    PriceLevel vecBidPriceLevel[10];             ///< vecBidPriceLevel 
    PriceLevel vecOfferPriceLevel[10];           ///< vecOfferPriceLevel 
    int         NumTrades;                       ///< 成交笔数 
    double      TotalVolumeTrade;                ///< 成交总量 
    double      TotalValueTrade;                 ///< 成交总金额 
    double      TotalBidQty;                     ///< 委托买入总量 
    float       WeightedAvgBidPx;                ///< 加权平均委买价格  
    float       AltWeightedAvgBidPx;             ///< 债券加权平均委买价格 
    double      TotalOfferQty;                   ///< 委托卖出总量 
    float       WeightedAvgOfferPx;              ///< 加权平均委卖价格 
    float       AltWeightedAvgOfferPx;           ///< 债券加权平均委卖价格 
    float       IOPV;                            ///< IOPV净值估值 
#ifndef OLD_DISTRISERVER
    int         ETFBuyNumber;                    //ETF申购笔数------------new
    double      ETFBuyAmount;                    //ETF申购数量
    double      ETFBuyMoney;                     //ETF申购金额
    int         ETFSellNumber;                   //ETF赎回笔数
    double      ETFSellAmount;                   //ETF赎回数量
    double      ETFSellMoney;                    //ETF赎回金额   // new
#endif
    float       YieldToMaturity;                 ///< 到期收益率 
    double      TotalWarrantExecQty;             ///< 权证执行的总数量 
    double      WarlowerPx;                      ///< 权证跌停价格 
    double      WarUpperPx;                      ///< 权证涨停价格 
#ifndef OLD_DISTRISERVER
    int         WithdrawBuyNumber;               //买入撤单笔数------------new
    double      WithdrawBuyAmount;               //买入撤单数量
    double      WithdrawBuyMoney;                //买入撤单金额
    int         WithdrawSellNumber;              //卖入撤单笔数
    double      WithdrawSellAmount;              //卖入撤单数量
    double      WithdrawSellMoney;               //卖入撤单金额
    int         TotalBidNumber;                  //买入总笔数
    int         TotalOfferNumber;                //卖出总笔数
    int         BidTradeMaxDuration;             //买入委托成交最大等待时间
    int         OfferTradeMaxDuration;           //卖入委托成交最大等待时间
    int         NumBidOrders;                    //买方委托价位数
    int         NumOfferOrders;                  //卖方委托价位数  //new
#endif
}SH_L2_MarketData;

/// 委托队列，从UA3202衍生
typedef struct _SH_L2_OrderQueue
{
    char        MessageType[7];     ///< 消息类型 
    int         DataTimeStamp;      ///< 时间 
    int         DataStatus;         ///< DataStatus 
    char        SecurityID[7];      ///< 证券代码 

    // 委买订单队列
    float       BidPrice;           ///< 价格 
    int         BidNumOrders;       ///< 总委托笔数 
    double      BidOrders[50];      ///< 委托队列 

    // 委卖订单队列
    float       OfferPrice;         ///< 价格 
    int         OfferNumOrders;     ///< 总委托笔数 
    double      OfferOrders[50];    ///< 委托队列 
}SH_L2_OrderQueue;

/// UA3107虚拟集合竞价 
typedef struct _SH_L2_VirtualAuctionPrice
{
    char    MessageType[7];     ///< 消息类型 
    int     DataTimeStamp;      ///< 时间 
    int     DataStatus;         ///< DataStatus 
    char    SecurityID[7];      ///< 证券代码 
    float   Price;              ///< 虚拟开盘参考价格 
    double  VirtualAuctionQty;  ///< 虚拟匹配量 
    double  LeaveQty;           ///< 虚拟未匹配量 
    char    Side[2];            ///< 买卖方向 
}SH_L2_VirtualAuctionPrice;

/// UA3113指数行情 
typedef struct _SH_L2_Index
{
    char    MessageType[7];     ///< 消息类型 
    int     DataTimeStamp;      ///< 时间 
    int     DataStatus;         ///< DataStatus 
    char    SecurityID[7];      ///< 证券代码 
    double  PreCloseIndex;      ///< 前收盘指数 
    double  OpenIndex;          ///< 今开盘指数 
    double  Turnover;           ///< 参与计算相应指数的成交金额 
    double  HighIndex;          ///< 最高指数 
    double  LowIndex;           ///< 最低指数 
    double  LastIndex;          ///< 最新指数 
    int     TradeTime;          ///< 成交时间 
    double  TotalVolumeTraded;  ///< 成交量 
    double  CloseIndex;         ///< 今日收盘指数 
}SH_L2_Index;

/// UA3115市场总览 
typedef struct _SH_L2_NGTS_MarketOverview
{
    char MessageType[7]; ///< 消息类型 
    int  DataTimeStamp;  ///< 时间 
    int  DataStatus;     ///< DataStatus 
    char SecurityID[7];  ///< 证券代码 
    int  OrigTime;       ///< 更新时间 
    int  OrigDate;       ///< 更新日期 
}SH_L2_NGTS_MarketOverview;

/// UA3201逐笔成交 
typedef struct _SH_L2_NGTS_Transaction
{
    char    MessageType[7]; ///< 消息类型 
    int     DataStatus;     ///< DataStatus 
    int     TradeIndex;     ///< 成交序号 
    int     TradeChannel;   ///< 成交通道 
    char    SecurityID[7];  ///< 证券代码 
    int     TradeTime;      ///< 成交时间（百分之一秒） 
    float   TradePrice;     ///< 成交价格(元) 
    float   TradeQty;       ///< 成交数量 股票：股 权证：份 债券：张 
    double  TradeMoney;     ///< 成交金额(元) 
#ifndef OLD_DISTRISERVER
    INT64   TradeBuyNo;     /// 买方订单号
    INT64   TradeSellNo;    /// 卖方订单号
    char    TradeBSFlag[6]; /// 内外盘标志 new
#endif
}SH_L2_NGTS_Transaction;

//=============个股期权==========================
/// UA9502 上交所个股期权静态数据
typedef struct _SHIO_Static_Output
{
    //RFStreamID; // 参考数据类型 C5 参考数据类型标识符，取值 RF301表示期权基础信息
    char        SecurityID[8];              ///< 期权合约的产品代码 C8 合约期权产品代码，8位字符
    char        ContractID[19];             ///< 期权合约代码 C19 
    char        SecuritySymbol[20];         ///< 期权合约简称 C20
    char        UnderlyingSecurityID[6];    ///< 标的证券代码 C6
    char        UnderlyingSymbol[8];        ///< 基础证券证券名称 C8
    char        UnderlyingType[3];          ///< 标的证券类型C3 EBS – ETF， ASH – A股
    char        OptionType;                 ///< 欧式美式 C1 若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A”
    char        CallOrPut;                  ///< 认购认沽 C1 认购，则本字段为“C”；若为认沽，则本字段为“P”
    __int64     ContractMultiplierUnit;     ///< 合约单位 N11  经过除权除息调整后的合约单位, 一定是整数
    double      ExercisePrice;              ///< 期权行权价 N11(4) 经过除权除息调整后的期权行权价，右对齐，精确到厘
    int         StartDate;                  ///< 首个交易日 C8 期权首个交易日,YYYYMMDD
    int         EndDate;                    ///< 最后交易日 C8 期权最后交易日/行权日，YYYYMMDD
    int         ExerciseDate;               ///< 期权行权日 C8 期权行权日，YYYYMMDD
    int         DeliveryDate;               ///< 行权交割日 C8 行权交割日，默认为行权日的下一个交易日，YYYYMMDD
    int         ExpireDate;                 ///< 期权到期日 C8 期权到期日，YYYYMMDD
    char        UpdateVersion;              ///< 合约版本号 C1 期权合约的版本号。新挂合约是’1’
    __int64     TotalLongPosition;          ///< 当前合约未平仓数 N12 单位是 （张）
    double      SecurityClosePx;            ///< 合约前收盘价 N11(4) 昨日收盘价，如遇除权除息则为调整后的收盘价格（上市首日的文件中，填写参考价格），右对齐，精确到厘
    double      SettlPrice;                 ///< 合约前结算价 N11(4) 昨日结算价，右对齐，单位：元
    double      UnderlyingClosePx;          ///< 标的证券前收盘 N11(4) 期权标的证券除权除息调整后的前收盘价格，右对齐，单位：元
    char        PriceLimitType;             ///< 涨跌幅限制类型 C1 ‘N’表示交易规则3.4.13规定的有涨跌幅限制类型或者权证管理办法第22条规定 ‘R’表示交易规则3.4.15和3.4.16规定的无涨跌幅限制类型
    double      DailyPriceUpLimit;          ///< 涨幅上限价格 N11(4) 当日期权涨停价格，精确到厘
    double      DailyPriceDownLimit;        ///< 跌幅下限价格 N11(4) 当日期权跌停价格，精确到厘
    double      MarginUnit;                 ///< 单位保证金 N16(2) 当日持有一张合约所需要的保证金数量，精确到分
    double      MarginRatioParam1;          ///< 保证金计算比例参数一 N6(2) 保证金计算参数，单位：%
    double      MarginRatioParam2;          ///< 保证金计算比例参数二 N6(2) 保证金计算参数，单位：%
    __int64     RoundLot;                   ///< 整手数 N12 一手等于几张合约
    __int64     LmtOrdMinFloor;             ///< 单笔限价申报下限 N12 单笔限价申报的申报张数下限。
    __int64     LmtOrdMaxFloor;             ///< 单笔限价申报上限 N12 单笔限价申报的申报张数上限。
    __int64     MktOrdMinFloor;             ///< 单笔市价申报下限 N12 单笔市价申报的申报张数下限。
    __int64     MktOrdMaxFloor;             ///< 单笔市价申报上限 N12 单笔市价申报的申报张数上限。
    double      TickSize;                   ///< 最小报价单位 N11(4) 单位元,精确到0.1厘
    char        SecurityStatususFlag[8];    ///< 期权合约状态信息标签 C8 该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。<br>
                                             /// 第1位：‘0’表示可开仓，‘1’表示限制卖出开仓（包括备兑开仓）和买入开仓。<br>
                                             /// 第2位：‘0’表示未连续停牌，‘1’表示连续停牌。<br>
                                             /// 第3位：‘0’表示未临近到期日，‘1’表示距离到期日不足10个交易日。<br>
                                             /// 第4位：‘0’表示近期未做调整，‘1’表示最近10个交易日内合约发生过调整。<br>
                                             /// 第5位：‘A’表示当日新挂牌的合约，‘E’表示存续的合约，‘D’表示当日摘牌的合约。
}SHIO_Static_Output;

/// 上交所个股期权价位信息
typedef struct 
{
    __int64     Size;   ///< 量
    double      Px;     ///< 价，精度4位小数
}PriceLevel_IO_Output;    

#define SHIO_LEVEL_1  5
#define SHIO_LEVEL_2  10

/// 上交所个股期权L1数据
typedef struct SHIO_Data_Output
{
    char                    SecurityID[8];                  ///< 合约代码
    int                     DataTimeStamp;                  ///< 数据生成时间 143025表示 14:30:25
    double                  PreSettlPrice;                  ///< 昨结算价，精度4位小数
    double                  SettlPrice;                     ///< 今结算价，精度4位小数
    double                  OpenPx;                         ///< 开盘价，精度4位小数
    double                  HighPx;                         ///< 最高价，精度4位小数
    double                  LowPx;                          ///< 最低价，精度4位小数
    double                  LastPx;                         ///< 现价，精度4位小数
    double                  AuctionPrice;                   ///< 波动性中断参考价，精度4位小数
    __int64                 AuctionQty;                     ///< 波动性中断集合竞价虚拟匹配量
    __int64                 Position;                       ///< 持仓量
    int                     NoBidPriceLevel;                ///< 买盘价位数量
    PriceLevel_IO_Output    BidPriceLv[SHIO_LEVEL_1];       ///< 申买量
    int                     NoOfferPriceLevel;              ///< 卖盘价位数量
    PriceLevel_IO_Output    OfferPriceLv[SHIO_LEVEL_1];     ///< 申卖量
    __int64                 TotalVolumeTrade;               ///< 成交量
    double                  TotalValueTrade;                ///< 成交额，精度2位
    char                    TradingPhaseCode[8];            ///< 交易状态
    __int64                 PacketTime;                     ///< Step包头中时间，交易所为YYYYMMDD-HH:MM:SS,转换后时间为YYYYMMDDHHMMSSMMM,如20140121100559111为2014-01-21 10:05:59.111
    double                  ClosePrice;                     ///< 收盘价

}SHIO_L1_Output;



//============上海固定收益行情===================================
typedef struct _SH_L2_6301_Data
{
    char    MessageType[7];             ///< 消息类型
    int     DataTimestamp;              ///< 行情服务器时间
    int     DataStatus;                 ///< 
    int     TradeIndex;                 ///< 成交序号        
    int     TradeChannel;               ///< 成交通道
    char    SecurityID[7];              ///< 证券代码
    char    Symbol[60];                 ///< 证券简称
    int     TradeDate;                  ///< 成交日期
    int     TradeTime;                  ///< 成交时间
    float   TradeNetPrice;              ///< 成交净价
    float   AccruedInterestAmt;         ///< 应计利息
    float   TradeFullPrice;             ///< 成交全价
    float   YieldToMaturity;            ///< 到期收益率
    INT64   TradeQty;                   ///< 成交数量
    INT64   TradeMoney;                 ///< 成交金额
    char    TradeMethod[2];             ///< 成交方式

}SH_L2_6301_Data;

typedef struct _STOrderQueue
{
    INT64   OrderNo;                    ///< 订单编号
    int     AuctionTime;                ///< 报价时间
    char    Auctioneer[20];             ///< 报价方
    INT64   OrderQty;                   ///< 数量
    float   YieldToMaturity;            ///< 到期收益率
}STOrderQueue;

typedef struct _SH_L2_6302_Data
{
    char            MessageType[7];     ///< 消息类型
    int             DataTimeStamp;      ///< 行情服务器时间
    int             DataStatus;         ///< 
    char            SecurityID[7];      ///< 证券代码
    char            Symbol[60];         ///< 证券简称
    int             ImageStatus;        ///< 快照类型
    int             TradeTime;          ///< 成交时间
    float           PreClosePx;         ///< 昨收盘价
    float           PreWeightedAvgPx;   ///< 昨日加权平均价
    float           OpenPx;             ///< 开盘价
    float           HighPx;             ///< 最高价
    float           LowPx;              ///< 最低价
    float           LastPx;             ///< 现价
    float           WeightedAvgPx;      ///< 当日加权平均价
    INT64           TotalNumTrades;     ///< 当日总成交笔数
    INT64           TotalVolumeTrade;   ///< 成交总量
    INT64           TotalValueTrade;    ///< 成交总金额
    float           PreCloseYield;      ///< 昨日收盘收益率
    float           PreWeightedAvgYield;///< 昨日加权平均收益率
    float           OpenYield;          ///< 当日开盘收益率
    float           HighYield;          ///< 当日最高收益率
    float           LowYield;           ///< 当日最低收益率
    float           LastYield;          ///< 当日最新收益率
    float           WeightedAvgYield;   ///< 当日加权平均收益率
    float           AccruedInterestAmt; ///< 应计利息
    PriceLevel      vecBidLevels[10];   ///< 十档买行情
    STOrderQueue    vecBidQueue[50];    ///< 买一队列
    PriceLevel      vecOfferLevels[10]; ///< 十档卖行情
    STOrderQueue    vecOfferQueue[50];  ///< 卖一队列
}SH_L2_6302_Data;

typedef struct _SH_L2_GdStatic
{
    char    SecurityID[7];              ///< 证券代码
    char    Symbol[16];                 ///< 证券名称        
    char    TradePro[3];                ///< 交易产品
    char    Property[2];                ///< 证券属性
    char    Status[2];                  ///< 证券状态
    char    PledgeCode[7];              ///< 质押券代码
    char    OpenTime[7];                ///< 开盘时间
    char    CloseTime[7];               ///< 收盘时间
    char    IssueStyle[2];              ///< 证券发行方式
    INT64   Par;                        ///< 证券面额
    INT64   Price;                      ///< 发行价格
    char    InterestStyle[2];           ///< 利息类型
    char    PayFre[2];                  ///< 利息频率
    INT64   FaceInterset;               ///< 票面利率
    INT64   BaseInterest;               ///< 基本利率
    INT64   BaseMargin;                 ///< 基本利差
    int     DueTime;                    ///< 期限
    int     IssueTotal;                 ///< 实际发行总量
    char    OpenDate[9];                ///< 发行开始日期
    char    CloseDate[9];               ///< 发行结束日期
    char    ListedDate[9];              ///< 上市日期
    char    DueDate[9];                 ///< 到期日期
    char    BondStyle[2];               ///< 国债类型
    char    IssueMethod[2];             ///< 发行方法
    char    SFKSC[2];                   ///< 是否跨市场
    char    NFZK[2];                    ///< 是否做空
    INT64   ZZKED;                      ///< 总做空额度
    INT64   JYSZKED;                    ///< 交易商做空额度
    INT64   ClosePrice;                 ///< 上日收盘价
    INT64   PreWeightedPrice;           ///< 上日加权平均价
}SH_L2_GdStatic;


//==============深圳L2============================
/// 深交所L2价位信息
typedef struct _SZ_PriceLevel
{
    int     Size;
    float   Px;
}SZ_PriceLevel;


/// 深圳L2行情数据
typedef struct _SZ_L2_Snapshot
{
    int             DataTimeStamp;          ///< 时间 HHMMSSMMM
    char            SecurityID[7];          ///< 证券代码
    float           PreClosePx;             ///< 昨收盘价
    float           OpenPx;                 ///< 开盘价 
    float           HighPx;                 ///< 最高价 
    float           LowPx;                  ///< 最低价
    float           LastPx;                 ///< 最近价
    double          TotalVolumeTrade;       ///< 成交总量
    double          TotalValueTrade;        ///< 成交总金额 
    UINT64          TotalLongPosition;      ///< 合约持仓量
    float           PERatio1;               ///< 市盈率1
    float           PERatio2;               ///< 市盈率2
    char            EndOfDayMaker[2];       ///< 闭市标志    
    INT64           TotalOfferQty;          ///< 委托卖出总量
    double          WeightedAvgOfferPx;     ///< 加权平均卖出价格
    int             NumTrades;              ///< 成交笔数
    SZ_PriceLevel   vecBidPriceLevel[10];   ///< 10档委买价位
    UINT32          BidNumOrders;           ///<
    UINT32          BidNoOrders;            ///< 买价位揭示委托笔数
    UINT32          BidS01OrderQty[50];     ///< 买一价委托量
    UINT64          TotalBidQty;            ///< 委托买入总量
    double          WeightedAvgBidPx;       ///< 加权平均买入价格 
    SZ_PriceLevel   vecOfferPriceLevel[10]; ///< 10档委卖价位
    UINT32          OfferNumOrdes;          ///<
    UINT32          OfferNoOrders;          ///< 卖价位揭示委托笔数
    UINT32          OfferS01OrderQty[50];   ///< 卖一价委托量
}SZ_L2_Snapshot;

/// Index指数快照
typedef struct _SZ_L2_Index
{
    int         DataTimeStamp;              ///< 时间
    char        SecurityID[7];              ///< 证券代码
    double      PreCloseIndex;              ///< 前收盘指数
    double      OpenIndex;                  ///< 今开盘指数
    double      Turnover;                   ///< 参与计算相应指数的成交金额
    double      HighIndex;                  ///< 最高指数
    double      LowIndex;                   ///< 最低指数
    double      LastIndex;                  ///< 最新指数
    INT64       NumTrades;                  ///< 参与计算相应指数的成交笔数
    INT64       TotalVolumeTraded;          ///< 参与计算相应指数的交易数量
    char        EndOfDayMaker[2];           ///< 闭市标志
}SZ_L2_Index;

/// Trade逐笔成交
typedef struct _SZ_L2_Trade
{
    UINT32      SetNo;                      ///< 证券集代号
    UINT32      RecNo;                      ///< 成交索引
    UINT32      BuyOrderRecNo;              ///< 买方委托索引
    UINT32      SellOrderRecNo;             ///< 卖方委托索引
    char        SecurityID[7];              ///< 证券代码
    float       Price;                      ///< 成交价格
    UINT32      TradeQty;                   ///< 成交数量
    char        FunctionCode[4];            ///< 成交代码
    char        OrderKind[4];               ///< 成交类别
    int         TradeTime;                  ///< 成交时间
}SZ_L2_Trade;

/// 逐笔委托
typedef struct _SZ_L2_Order
{
    UINT32      SetNo;                      ///< 证券集代号
    UINT32      RecNo;                      ///< 委托索引
    char        SecurityID[7];              ///< 证券代码
    float       Price;                      ///< 委托价格
    UINT32      OrderQty;                   ///< 委托数量
    char        OrderKind[4];               ///< 委托类别
    char        FunctionCode[4];            ///< 委托代码
    int         OrderEntryTime;             ///< 委托时间
}SZ_L2_Order;

/// StockInfo证券信息
typedef struct _SZ_L2_StockInfo
{    
    UINT32      RecNo;                      ///< 记录索引
    char        SecurityID[7];              ///< 证券代码
    char        Symbol[20];                 ///< 证券名称
    char        SecurityDesc[20];           ///< 证券描述
    char        UnderlyingSecurityID[7];    ///< 基础证券代码
    char        SecurityIDSource[5];        ///< 证券代码源
    //UINT32    NoSecurityAltID;            ///< 备选证券代码
    //char      SecurityAltID[7];           ///< 备选证券代码
    //char      SecurityAltIDSource[12];    ///< 备选证券代码源TODO:未知字符大小
    char        IndustryClassification[5];  ///< 行业种类
    char        Currency[5];                ///< 币种
    float       ShareFaceValue;             ///< 每股面值
    UINT64      OutstandingShares;          ///< 总发行量
    UINT64      PublicFloatShareQuantity;   ///< 流通股数
    float       PreviousYearProfitPerShare; ///< 上年每股利润
    float       CurrentYearProfitPerShare;  ///< 本年每股利润
    UINT32      NAV;                        ///< 基金T-1日累计净值
    UINT32      NoMiscFees;                 ///< 杂项费用类别数
    UINT32      IssueDate;                  ///< 发行日期
    char        BondType[2];                ///< 债券类型
    float       CouponRate;                 ///< 票面利率
    float       ConversionPrice;            ///< 行权价格
    char        AorEType[2];                ///< 美式/欧式/百慕大式
    char        CallOrPut[2];               ///< Call/Put标志
    char        WarrantClearingType[2];     ///< 权证结算方式
    UINT        CVRatio;                    ///< 行权比例
    UINT        ConversionBeginDate;        ///< 行权开始日期
    UINT        ConversionEndDate;          ///< 行权结束日期
    UINT        InterestAccrualDate;        ///< 起息日
    UINT        MaturityDate;               ///< 到期交割日
    UINT        RoundLot;                   ///< 交易单位
    UINT        BidLotSize;                 ///< 买数量单位
    UINT        AskLotSize;                 ///< 卖数量单位
    UINT        MaxFloor;                   ///< 每笔限量
    char        TradeMethod[2];             ///< 交易方式
    float       PriceTickSize;              ///< 价格档位
    char        PriceLimitType[7];          ///< 限价参数类型 不确定几个字节
    float       AuctionPriceLimit;          ///< 集合竞价限价参数
    float       ContinuousTradePriceLimit;  ///< 连续竞价限价参数
    float       DailyPriceUpLimit;          ///< 涨幅价格
    float       DailyPriceDownLimit;        ///< 跌幅价格
    float       DailyPriceUpLimit2;         ///< 除当日交易最高价外的价格限制
    float       DailyPriceDownLimit2;       ///< 除当日交易最低价外的价格限制
    UINT        ContractMultiplier;         ///< 债券折合回购标准券比例
    float       GageRate;                   ///< 担保品折算率
    char        CrdBuyUnderlying[2];        ///< 融资买入标的
    char        CrdSellUnderlying[2];       ///< 融券卖出标的
    UINT        NoIndicesParticipated;      ///< 所属指数数量
    //char      ParticipatingindexID[7];    ///< 所属指数 不确定字节个数
    char        MarketMakerFlag[2];         ///< 做市商标志
    char        SecurityExchange[5];        ///< 交易所代码
    char        CFICode[5];                 ///< 证券类别
    char        SecuritySubType[5];         ///< 证券子类别(A, B)
    char        SecurityProperties[2];      ///< 证券属性
    UINT        SecurityTradingStatus;      ///< 交易状态
    char        CorporateAction[2];         ///< 除权除息标志
    char        TradingMechanism[2];        ///< 产品交易类型
    char        CrdPriceCheckType[2];       ///< 提价检查方式
    char        NetVotingFlag[2];           ///< 网络投票标志
    char        ShrstrurefmFlag[2];         ///< 股改状态标志
    char        OfferingFlag[2];            ///< 是否处于要约收购期、是否处于转股期（可转债）、否处于行权期（权证）
}SZ_L2_StockInfo;

/// 证券状态
typedef struct _SZ_L2_StockStatus
{
    char        SecurityID[7];              ///< 证券代码
    char        SecurityPreName[4];         ///< 证券简称前缀
    char        TradingPhaseCode[9];        ///< 证券竞价状态
    char        CrdBuyStatus[2];            ///< 当前融资买入开放状态
    char        CrdSellStatus[2];           ///< 当前融券卖出开放状态
    char        SubScribeStatus[2];         ///< 是否允许申购
    char        RedemptionStatus[2];        ///< 是否允许赎回
    char        WarrantCreated[2];          ///< 当日是否有创设发生
    char        WarrantDropped[2];          ///< 当日是否有注销发生
}SZ_L2_StockStatus;


//=================================大连商品level2==============================================================
/// 直接市场最优行情域
typedef struct _DLL2_BestQuot
{
    char        szTradingDate[8];           ///< 交易日期
    char        szContractID[20];           ///< 合约号
    UINT        nTID;                       ///< 事务编号
    char        szContractName[40];         ///< 合约名称
    double      dLastPrice;                ///< 最新价
    double      dHighPrice;                 ///< 最高价
    double      dLowPrice;                  ///< 最低价
    UINT        nTotalVolum;                ///< 最新成交量
    UINT        nPrevTotalVolume;           ///< 成交量
    double      dTurnover;                  ///< 成交额
    UINT        nPrevOpenInterest;          ///< 初始持仓量
    UINT        nOpenInterest;              ///< 持仓量
    INT         nInterestChg;               ///< 持仓量变化
    double      dClearPrice;                ///< 今结算价
    double      dListLowPrice;              ///< 历史最低价
    double      dListHighPrice;             ///< 历史最高价
    double      dUpperLimit;                ///< 涨停板
    double      dLowerLimit;                ///< 跌停板
    double      dLastClearPrice;            ///< 上日结算价
    double      dLastClose;               ///< 上日收盘价
    double      dBidPrice;                  ///< 最高买
    UINT        nBidSize;                   ///< 申买量
    UINT        nBidImplyQty;               ///< 申买推导量
    double      dAskPrice;                  ///< 最低卖
    UINT        nAskSize;                   ///< 申卖量
    UINT        nAskImplyQty;               ///< 申卖推导量
    double      dAveragePrice;              ///< 当日均价
    char        szTradingTime[12];          ///< 生成时间
    double      dOpenPrice;                 ///< 开盘价
    double      dClosePrice;               ///< 收盘价
}DLL2_BestQuot;    //size:264

/// 最优报价委托数量行情域
#define DLL2_BEST_ORDER_LEVEL 10
typedef struct _DLL2_BestOrder
{
    double      dBestBuyOrderPrice;                     ///< 买价格
    union{
        UINT    BestBuyOrderQty[DLL2_BEST_ORDER_LEVEL]; ///< 买委托量
        struct{
        UINT    nBestBuyOrderQtyOne;                    ///< 买委托量1
        UINT    nBestBuyOrderQtyTwo;                    ///< 买委托量2
        UINT    nBestBuyOrderQtyThree;                  ///< 买委托量3
        UINT    nBestBuyOrderQtyFour;                   ///< 买委托量4
        UINT    nBestBuyOrderQtyFive;                   ///< 买委托量5
        UINT    nBestBuyOrderQtySix;                    ///< 买委托量6
        UINT    nBestBuyOrderQtySeven;                  ///< 买委托量7
        UINT    nBestBuyOrderQtyEight;                  ///< 买委托量8
        UINT    nBestBuyOrderQtyNine;                   ///< 买委托量9
        UINT    nBestBuyOrderQtyTen;                    ///< 买委托量10
        };
    };
    double      dBestSellOrderPrice;                    ///< 卖价格
    union{
        UINT    BestSellOrderQty[DLL2_BEST_ORDER_LEVEL];///< 卖委托量
        struct
        {
        UINT    nBestSellOrderQtyOne;                   ///< 卖委托量1
        UINT    nBestSellOrderQtyTwo;                   ///< 卖委托量2
        UINT    nBestSellOrderQtyThree;                 ///< 卖委托量3
        UINT    nBestSellOrderQtyFour;                  ///< 卖委托量4
        UINT    nBestSellOrderQtyFive;                  ///< 卖委托量5
        UINT    nBestSellOrderQtySix;                   ///< 卖委托量6
        UINT    nBestSellOrderQtySeven;                 ///< 卖委托量7
        UINT    nBestSellOrderQtyEight;                 ///< 卖委托量8
        UINT    nBestSellOrderQtyNine;                  ///< 卖委托量9
        UINT    nBestSellOrderQtyTen;                   ///< 卖委托量10
        };
    };
    char        szGenTime[12];                          ///< 生成时间
}DLL2_BestOrder;
/// 期权参数域
typedef struct _DLL2_OptPara
{
    char        TradeDate[8];               ///< 交易日期
    char        ContractID[20];             ///< 期权合约号
    double      Delta;                      ///< delta
    double      Gamma;                      ///< gama
    double      Rho;                        ///< rho
    double      Theta;                      ///< theta
    double      Vega;                       ///< vega
}DLL2_OptPara;
/// 深度行情域
typedef struct _DLL2_MBLQuotPara
{
    double      OrderPrice;                 ///< 价格
    UINT        OrderQty;                   ///< 委托量
    UINT        ImplyQty;                   ///< 推导量
    UINT        BsFlag;                     ///< 买卖标志
    char        GenTime[12];                ///< 生成时间
}DLL2_MBLQuotPara;

/// 大商所L2深度行情数量
#define DLL2_MBLQUOT_LEVEL 5
/// 大商所L2期权参数数量
#define DLL2_OPTPARA_LEVEL 10

/// 深度行情
typedef struct _DLL2_MBLQuot_Output
{
    DLL2_BestQuot       BestQuot;                           ///< 直接市场最优行情域
    DLL2_BestOrder      BestOrder;                          ///< 最优报价委托数量行情域
    int                 MBLQuotBuyNum;                      ///< 深度行情买数量
    DLL2_MBLQuotPara    MBLQuotBuy[DLL2_MBLQUOT_LEVEL];     ///< 买深度行情域
    int                 MBLQuotSellNum;                     ///< 深度行情卖数量
    DLL2_MBLQuotPara    MBLQuotSell[DLL2_MBLQUOT_LEVEL];    ///< 卖深度行情域
}DLL2_MBLQuot_Output;

/// 套利最优行情域
typedef struct _DLL2_ArbiBestQuot
{
    char            szTradeDate[8];         ///< 交易日期
    char            szArbiContractID[80];   ///< 套利合约号
    UINT            nTID;                   ///< 事务编号
    double          dLastPrice;             ///< 最新价
    double          dLowPrice;              ///< 最低价
    double          dHighPrice;             ///< 最高价
    double          dListLowPrice;          ///< 历史最低价
    double          dListHighPrice;         ///< 历史最高价
    double          dUpperLimit;            ///< 涨停板
    double          dLowerLimit;            ///< 跌停板
    double          dBidPrice;              ///< 最高买
    UINT            nBidSize;               ///< 申买量
    double          dAskPrice;              ///< 最低卖
    UINT            nAskSize;               ///< 申卖量
    char            szGenTime[8];           ///< 生成时间
}DLL2_ArbiBestQuot;    //size:189

/// 套利深度行情
typedef struct _DLL2_ArbiMBLQuot_Output
{
    DLL2_ArbiBestQuot   ArbiBestQuot;                       ///< 套利最优行情域
    DLL2_BestOrder      BestOrder;                          ///< 最优报价委托数量行情
    int                 MBLQuotBuyNum;                      ///< 深度行情买数量
    DLL2_MBLQuotPara    MBLQuotBuy[DLL2_MBLQUOT_LEVEL];     ///< 买深度行情域
    int                 MBLQuotSellNum;                     ///< 深度行情卖数量
    DLL2_MBLQuotPara    MBLQuotSell[DLL2_MBLQUOT_LEVEL];    ///< 卖深度行情域
}DLL2_ArbiMBLQuot_Output;

/// 实时结算价行情
typedef struct _DLL2_RealTimePrice_Output 
{
    char        szContractID[80];       ///< 合约号
    double      dRealTimePrice;         ///< 实时结算价
}DLL2_RealTimePrice_Output;

/// 委托统计行情
typedef struct _DLL2_OrderStatistic_Output
{
    char        szContractID[80];               ///< 合约号
    UINT        nTotalBuyOrderNum;              ///< 买委托总量
    UINT        nTotalSellOrderNum;             ///< 卖委托总量
    double      dWeightedAverageBuyOrderPrice;  ///< 加权平均委买价格
    double      dWeightedAverageSellOrderPrice; ///< 加权平均委卖价格
}DLL2_OrderStatistic_Output;

/// 分价成交量
typedef struct _DLL2_PriceQty
{
    double      dPrice;                         ///< 价格
    UINT        nPriceBOQty;                    ///< 买开数量
    UINT        nPriceBEQty;                    ///< 买平数量
    UINT        nPriceSOQty;                    ///< 卖开数量
    UINT        nPriceSEQty;                    ///< 卖平数量
}DLL2_PriceQty;

#define DLL2_MARCH_PRICE_QTY_LEVEL 5
/// 分价成交量行情
typedef struct _DLL2_MarchPriceQty_Output
{
    char        szContractID[80];                               ///< 合约号
    union{
        DLL2_PriceQty   PriceQty[DLL2_MARCH_PRICE_QTY_LEVEL];   ///< 五笔分价成交量信息
        struct
        {
            double      dPriceOne;                      ///< 价格
            UINT        nPriceOneBOQty;                 ///< 买开数量
            UINT        nPriceOneBEQty;                 ///< 买平数量
            UINT        nPriceOneSOQty;                 ///< 卖开数量
            UINT        nPriceOneSEQty;                 ///< 卖平数量
            double      dPriceTwo;                      ///< 价格
            UINT        nPriceTwoBOQty;                 ///< 买开数量
            UINT        nPriceTwoBEQty;                 ///< 买平数量
            UINT        nPriceTwoSOQty;                 ///< 卖开数量
            UINT        nPriceTwoSEQty;                 ///< 卖平数量
            double      dPriceThree;                    ///< 价格
            UINT        nPriceThreeBOQty;               ///< 买开数量
            UINT        nPriceThreeBEQty;               ///< 买平数量
            UINT        nPriceThreeSOQty;               ///< 卖开数量
            UINT        nPriceThreeSEQty;               ///< 卖平数量
            double      dPriceFour;                     ///< 价格
            UINT        nPriceFourBOQty;                ///< 买开数量
            UINT        nPriceFourBEQty;                ///< 买平数量
            UINT        nPriceFourSOQty;                ///< 卖开数量
            UINT        nPriceFourSEQty;                ///< 卖平数量
            double      dPriceFive;                     ///< 价格
            UINT        nPriceFiveBOQty;                ///< 买开数量
            UINT        nPriceFiveBEQty;                ///< 买平数量
            UINT        nPriceFiveSOQty;                ///< 卖开数量
            UINT        nPriceFiveSEQty;                ///< 卖平数量
        };
    };
}DLL2_MarchPriceQty_Output;

#pragma pack()
#endif
