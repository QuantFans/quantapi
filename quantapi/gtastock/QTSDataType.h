//////////////////////////////////////////////////////////////////////////////
/// @file       QTSDataType.h
/// @brief      QTS数据格式定义
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_DATA_TYPE_H_
#define GTA_QTS_DATA_TYPE_H_

// 导出类宏定义
#ifdef _WIN32
#define _CDECL         __cdecl
#ifdef GTA_QTS_API_EXPORTS
#define GTA_API_EXPORT __declspec(dllexport)
#else
#define GTA_API_EXPORT __declspec(dllimport)
#endif
#else
#define _CDECL
#define GTA_API_EXPORT
#ifndef __stdcall
#define __stdcall
#endif
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/// 消息类型定义，值为unsigned int值
enum MsgType
{
    Msg_Unknown                 = 0x00000000,       ///< 错误的消息类型
    Msg_SSEL1_Static            = 0x00101000,       ///< 上交所L1静态数据
    Msg_SSEL1_Quotation         = 0x00101001,       ///< 上交所L1实时行情
    Msg_SSEL2_Static            = 0x00102000,       ///< 上交所L2静态数据 
    Msg_SSEL2_Quotation         = 0x00102001,       ///< 上交所L2实时行情 UA3202
    Msg_SSEL2_Transaction       = 0x00102002,       ///< 上交所L2逐笔成交 UA3201
    Msg_SSEL2_Index             = 0x00102003,       ///< 上交所L2指数行情 UA3113
    Msg_SSEL2_Auction           = 0x00102004,       ///< 上交所L2虚拟集合竞价 UA3107
    Msg_SSEL2_Overview          = 0x00102005,       ///< 上交所L2市场总览 UA3115
    Msg_SSEIOL1_Static          = 0x00103000,       ///< 上交所个股期权静态数据
    Msg_SSEIOL1_Quotation       = 0x00103001,       ///< 上交所个股期权实时行情 UA9002
    Msg_SZSEL1_Static           = 0x00201000,       ///< 深交所L1静态数据
    Msg_SZSEL1_Quotation        = 0x00201001,       ///< 深交所L1实时行情
    Msg_SZSEL2_Static           = 0x00202000,       ///< 深交所L2静态数据 UA101
    Msg_SZSEL2_Quotation        = 0x00202001,       ///< 深交所L2实时行情 UA103
    Msg_SZSEL2_Transaction      = 0x00202002,       ///< 深交所L2逐笔成交 UA202
    Msg_SZSEL2_Index            = 0x00202003,       ///< 深交所L2指数行情 UA104
    Msg_SZSEL2_Order            = 0x00202006,       ///< 深交所L2逐笔委托 UA201
    Msg_SZSEL2_Status           = 0x00202007,       ///< 深交所L2证券状态 UA102
    Msg_CFFEXL2_Static          = 0x00302000,       ///< 中金所L2静态数据
    Msg_CFFEXL2_Quotation       = 0x00302001,       ///< 中金所L2实时行情
    Msg_SHFEL1_Static           = 0x00401000,       ///< 上期所静态数据
    Msg_SHFEL1_Quotation        = 0x00401001,       ///< 上期所实时行情
    Msg_CZCEL1_Static           = 0x00501000,       ///< 郑商所静态数据
    Msg_CZCEL1_Quotation        = 0x00501001,       ///< 郑商所实时行情
    Msg_DCEL1_Static            = 0x00601000,       ///< 大商所L1静态数据
    Msg_DCEL1_Quotation         = 0x00601001,       ///< 大商所L1深度行情
    Msg_DCEL1_ArbiQuotation     = 0x00601008,       ///< 大商所L1套利深度行情
    Msg_DCEL2_Static            = 0x00602000,       ///< 大商所L2静态数据
    Msg_DCEL2_Quotation         = 0x00602001,       ///< 大商所L2最优深度行情
    Msg_DCEL2_ArbiQuotation     = 0x00602008,       ///< 大商所L2最优套利深度行情
    Msg_DCEL2_RealTimePrice     = 0x00602009,       ///< 大商所L2实时结算价
    Msg_DCEL2_OrderStatistic    = 0x0060200A,       ///< 大商所L2委托统计行情
    Msg_DCEL2_MarchPriceQty     = 0x0060200B,       ///< 大商所L2分价成交量行情
};
/// 数据分类，多个市场汇总后的分类
enum DataCategory
{
    Category_Unknown            =   -1,             ///< 错误消息分类
    Category_Static             = 0x00,             ///< 静态数据
    Category_Quotation          = 0x01,             ///< 实时行情
    Category_Transaction        = 0x02,             ///< 逐笔成交
    Category_Index              = 0x03,             ///< 指数行情
    Category_Auction            = 0x04,             ///< 虚拟集合竞价
    Category_Overview           = 0x05,             ///< 市场总览
    Category_Order              = 0x06,             ///< 逐笔委托
    Category_Status             = 0x07,             ///< 证券状态
    Category_ArbiQuotation      = 0x08,             ///< 套利深度行情
    Category_RealTimePrice      = 0x09,             ///< 实时结算价
    Category_OrderStatistic     = 0x0A,             ///< 委托统计行情
    Category_MarchPriceQty      = 0x0B,             ///< 分价成交量行情
};
/// 市场类型定义
enum MarketTag
{
    Market_Unknown         = 0,     ///< 错误市场
    Market_SSE             = 1,     ///< 上交所
    Market_SZSE            = 2,     ///< 深交所
    Market_CFFEX           = 3,     ///< 中金所
    Market_SHFE            = 4,     ///< 上期所
    Market_CZCE            = 5,     ///< 郑商所
    Market_DCE             = 6,     ///< 大商所
};
/// 网络状态定义.
enum ConnectState
{
    Connecting                  = 0,    ///< 正在连接
    Connected                   = 1,    ///< 已连接
    ConnectClosing              = 2,    ///< 正在关闭
    ConnectClosed               = 3,    ///< 已关闭
};

/// 返回值含义列表
enum RetCode
{
    Ret_Error                   = -1,   ///< 失败
    Ret_Success                 = 0,    ///< 成功
    Ret_NoAddress               = 1,    ///< 请先设置行情服务器地址
    Ret_NoPermission            = 2,    ///< 没有权限，请联系客服
    Ret_ParamInvalid            = 3,    ///< 参数无效
    Ret_AccountError            = 4,    ///< 帐号或密码错误
    Ret_AccountOutDate          = 5,    ///< 帐号不在有效期内
    Ret_ConnectFail             = 6,    ///< 连接失败
    Ret_LoginRepeat             = 7,    ///< 帐号重复登录
    Ret_OutTime                 = 8,    ///< 超时
    Ret_CloseConnect            = 9,    ///< 连接断开
};

/// 字段ID定义
enum FieldID
{
    FID_ERROR                   = 0,            ///< 错误字段定义，字段已到结尾
    FID_AltSymbol1              = 1000,         ///< 备选代码. 
    FID_AltSymbol2              = 1001,         ///< 备选代码. 
    FID_AltSymbol3              = 1002,         ///< 备选代码. 
    FID_AltSymbolNo             = 1003,         ///< 备选代码个数. 
    FID_AltSymbolSource1        = 1004,         ///< 备选代码源. 
    FID_AltSymbolSource2        = 1005,         ///< 备选代码源. 
    FID_AltSymbolSource3        = 1006,         ///< 备选代码源. 
    FID_AuctionOpenPrice        = 1007,         ///< 虚拟开盘参考价. 
    FID_AuctionPriceLimit       = 1008,         ///< 集合竞价限价参数. 3 位小数
    FID_AuctionVolume           = 1009,         ///< 虚拟匹配量. 
    FID_BlockPriceDownLmt       = 1010,         ///< 无涨跌停大宗次底价. 3 位小数
    FID_BlockPriceUpLmt         = 1011,         ///< 无涨跌停大宗次顶价. 3 位小数
    FID_BondType                = 1012,         ///< 债券类型. B = 企业债券，C = 国债，V = 可转债
    FID_BondWtAvgBuyPrice       = 1013,         ///< 债券加权平均委买价. （元）
    FID_BondWtAvgSellPrice      = 1014,         ///< 债券加权平均委卖价. 
    FID_BuyLevelNo              = 1015,         ///< 买盘价位数. "沪深L2实时行情：10档行情，不足时补空；上交所个股期权实时行情：五档:总是5，空档位用0填充。"
    FID_BuyLevelQueue           = 1016,         ///< 买1档队列. 高频数据保存，先存订单数量,只有一档有此数据，50档，不足时补空
    FID_BuyOrderID              = 1017,         ///< 买方委托索引. 从 1 开始计数，0 表示无对应委托
    FID_BuyOrderNo              = 1018,         ///< 买方委托价位数. 
    FID_BuyPrice01              = 1019,         ///< 申买价. 3 位小数
    FID_BuyPrice02              = 1020,         ///< 申买价. 3 位小数
    FID_BuyPrice03              = 1021,         ///< 申买价. 3 位小数
    FID_BuyPrice04              = 1022,         ///< 申买价. 3 位小数
    FID_BuyPrice05              = 1023,         ///< 申买价. 3 位小数
    FID_BuyPrice06              = 1024,         ///< 申买价. 3 位小数
    FID_BuyPrice07              = 1025,         ///< 申买价. 3 位小数
    FID_BuyPrice08              = 1026,         ///< 申买价. 3 位小数
    FID_BuyPrice09              = 1027,         ///< 申买价. 3 位小数
    FID_BuyPrice10              = 1028,         ///< 申买价. 3 位小数
    FID_BuyRecID                = 1029,         ///< 买方订单号. 
    FID_BuySellFlag             = 1030,         ///< 内外盘标志. B – 外盘,主动买;S – 内盘,主动卖;N – 未知
    FID_BuyVolume01             = 1031,         ///< 申买量. 
    FID_BuyVolume02             = 1032,         ///< 申买量. 
    FID_BuyVolume03             = 1033,         ///< 申买量. 
    FID_BuyVolume04             = 1034,         ///< 申买量. 
    FID_BuyVolume05             = 1035,         ///< 申买量. 
    FID_BuyVolume06             = 1036,         ///< 申买量. 
    FID_BuyVolume07             = 1037,         ///< 申买量. 
    FID_BuyVolume08             = 1038,         ///< 申买量. 
    FID_BuyVolume09             = 1039,         ///< 申买量. 
    FID_BuyVolume10             = 1040,         ///< 申买量. 
    FID_BuyVolumeUnit           = 1041,         ///< 买数量单位. 买订单的申报数量必须是该字段的整数倍。
    FID_CallOrPut               = 1042,         ///< 认购认沽. C = Call，P = Put
    FID_CFICode                 = 1043,         ///< 证券类别. "上交所：’E'表示股票；‘EU’表示基金；‘D’表示债券；‘RWS’表示权证；‘FF’表示期货。
                                                ///< 深交所：CFICode和SecuritySubType两个字段确定了不同的证券类别，CFICode的取值为MRI，EU，ES，D，DC。"
    FID_OutstandingShare        = 1044,         ///< 流通股数. 
    FID_CloseFlag               = 1045,         ///< 闭市标志. Y = 闭市，N = 开市
    FID_ClosePrice              = 1046,         ///< 今收盘价. 
    FID_ContractID              = 1047,         ///< 合约交易代码 . 合约交易代码17位，按以下顺序编写：1、第1至第6位为数字，取标的证券代码，如工商银行601398，取“601398”；2、第7位为C(Call)或者P(Put)，分别表示认购期权或者认沽期权；3、第8、9位表示到期年份；4、第10、11位表示到期月份；5、第12位期初设为“M”，表示月份合约。当合约首次调整后，“M”修改为 “A”，以表示该合约被调整过一次，如发生第二次调整，则“A”修改为“B”、“M”修改为 “A”，以此类推；6、第13至17位表示期权行权价格.留两位备用
    FID_ContractMultiplier      = 1048,         ///< 债券折合回购标准券比例. 2 位小数
    FID_ContractMultiplierUnit  = 1049,         ///< 合约单位 . 经过除权除息调整后的合约单位, 一定是整数 
    FID_ContTradePriceLmt       = 1050,         ///< 连续竞价限价参数. 3 位小数
    FID_ConversionBeginDate     = 1051,         ///< 行权开始日. 
    FID_ConversionEndDate       = 1052,         ///< 行权结束日. 
    FID_ConversionPrice         = 1053,         ///< 行权价格. 3 位小数
    FID_ConversionRatio         = 1054,         ///< 行权比例. 4 位小数
    FID_CouponRate              = 1055,         ///< 票面利率. 6 位小数
    FID_CrdBuyStatus            = 1056,         ///< 当前融资开放状态. Y = 开放,N = 暂停
    FID_CrdBuyUnderlying        = 1057,         ///< 融资标的标志. "上交所：’T‘表示是融资标的证券；’F‘表示不是融资标的证券。
                                                ///< 深交所：Y= 是，N= 否"
    FID_CrdPriceCheckType       = 1058,         ///< 提价检查方式. 
                                                ///< 0 = 对融券卖出委托价格不限制；
                                                ///< 1 = 要求融券卖出申报价格不低于最近价；
                                                ///< 2 = 要求融券卖出申报价格不低于昨收价
    FID_CrdSellStatus           = 1059,         ///< 当前融券开放状态. Y = 开放,N = 暂停
    FID_CrdSellUnderlying       = 1060,         ///< 融券标的标志. "上交所：’T‘表示是融券标的证券；’F‘表示不是融券标的证券。
                                                ///< 深交所：Y= 是，N= 否"
    FID_Currency                = 1061,         ///< 币种. CNY = 人民币，HKD = 港币
    FID_DeliveryDate            = 1062,         ///< 行权交割日. 行权交割日，默认为行权日的下一个交易日，YYYYMMDD
    FID_EndDate                 = 1063,         ///< 最后交易日 . 期权最后交易日/行权日，YYYYMMDD 
    FID_ETFBuyAmount            = 1064,         ///< ETF 申购金额. 
    FID_ETFBuyNo                = 1065,         ///< ETF 申购笔数. 
    FID_ETFBuyVolume            = 1066,         ///< ETF 申购数量. 
    FID_ETFSellAmount           = 1067,         ///< ETF 赎回金额. 
    FID_ETFSellNo               = 1068,         ///< ETF 赎回笔数. 
    FID_ETFSellVolume           = 1069,         ///< ETF 赎回数量. 
    FID_ExerciseDate            = 1070,         ///< 期权行权日 . 期权行权日，YYYYMMDD 
    FID_ExercisePrice           = 1071,         ///< 期权行权价 . 经过除权除息调整后的期权行权价，右对齐，精确到厘;行权价格调整采取四舍五入方式，股票保留两位小数，ETF保留三位小数。
    FID_ExpireDate              = 1072,         ///< 期权到期日 . 期权到期日，YYYYMMDD 
    FID_GageRate                = 1073,         ///< 担保品折算率. 2 位小数
    FID_HighPrice               = 1074,         ///< 最高价. 4位小数
    FID_IndustryType            = 1075,         ///< 行业种类. 
    FID_InterestAccrualDate     = 1076,         ///< 起息日. 
    FID_InterruptAuctionPrice   = 1077,         ///< 波动性中断参考价. 4 decimal places
    FID_InterruptAuctionVolume  = 1078,         ///< 波动性中断虚拟匹配量. 虚拟集合竞价过程中，若期权期货的价格波动性太大，则需要中断一段时间，中断结束后，继续使用这一数据作为虚拟匹配量
    FID_IOPV                    = 1079,         ///< ETF 净值估值. 
    FID_ISINCode                = 1080,         ///< ISIN代码. 
    FID_IssueDate               = 1081,         ///< 发行日期. 
    FID_IssuedVolume            = 1082,         ///< 总发行量. 
    FID_LastPrice               = 1083,         ///< 现价. 4位小数
    FID_LeaveVolume             = 1084,         ///< 虚拟未匹配量. 
    FID_ListingDate             = 1085,         ///< 上市日期. 在上交所首日交易日期，YYYYMMDD
    FID_LmtOrdCeiling           = 1086,         ///< 限价申报上限 . 单笔限价申报的申报张数上限。 
    FID_LmtOrdFloor             = 1087,         ///< 限价申报下限 . 单笔限价申报的申报张数下限。 
    FID_LowPrice                = 1088,         ///< 最低价. 4位小数
    FID_MarginRatioParam1       = 1089,         ///< 保证金计算参数一 . 保证金计算参数，单位：% 
    FID_MarginRatioParam2       = 1090,         ///< 保证金计算参数二 . 保证金计算参数，单位：% 
    FID_MarginUnit              = 1091,         ///< 单位保证金 . 当日持有一张合约所需要的保证金数 量，精确到分 
    FID_MarketMakerFlag         = 1095,         ///< 做市商标志. Y = 有做市商，N = 无做市商
    FID_MarketTime              = 1099,         ///< 市场时间. 百分之一秒
    FID_MarketType              = 1100,         ///< 市场种类. ‘ASHR’表示A股市场；‘BSHR’表示B股市场；‘CSHR‘表示国际版市场。
    FID_MaturityDate            = 1101,         ///< 到期交割日. 
    FID_MaxBuyDuration          = 1102,         ///< 买入成交最大等待时间. 
    FID_DeclareVolumeCeiling    = 1103,         ///< 申报量上限. 申报数量上限
    FID_MaxSellDuration         = 1104,         ///< 卖出成交最大等待时间. 
    FID_MessageID               = 1105,         ///< 消息序号. 
    FID_DeclareVolumeFloor      = 1106,         ///< 申报量下限. 申报数量下限
    FID_MktOrdCeiling           = 1111,         ///< 市价申报上限 . 单笔市价申报的申报张数上限。 
    FID_MktOrdFloor             = 1112,         ///< 市价申报下限 . 单笔市价申报的申报张数下限。 
    FID_NameUnderlying          = 1113,         ///< 基础证券名称 . 
    FID_NAV                     = 1114,         ///< 基金T-1日累计净值. 4 位小数
    FID_NetVotingFlag           = 1115,         ///< 网络投票标志. Y = 当日有相关网络投票，N = 当日无相关网络投票
    FID_NonTradableNo           = 1116,         ///< 非流通股数. 预留
    FID_OfferingFlag            = 1117,         ///< 收购（转股、行权）标志. Y= 是，N= 否
    FID_OpenPrice               = 1118,         ///< 开盘价. 4位小数
    FID_OptionType              = 1119,         ///< 行权类型. A= 美式，E = 欧式，B = 百慕大式
    FID_LocalTimeStamp          = 1120,         ///< 采集时间. 国泰安内部加的采集时间，用于测延时，精确到毫秒
    FID_OrderCode               = 1121,         ///< 委托代码. 
    FID_OrderPrice              = 1122,         ///< 委托价格. 3位小数
    FID_OrderType               = 1123,         ///< 委托类别. 
    FID_OrderVolume             = 1124,         ///< 委托数量. 
    FID_PacketTimeStamp         = 1125,         ///< 包头时间. 国泰安内部加的包头时间，用于测延时，精确到毫秒
    FID_ParValue                = 1128,         ///< 每股面值. 3 位小数
    FID_PERatio1                = 1129,         ///< 市盈率 1. 2 位小数，股票：价格/上年每股利润，债券：每百元应计利息
    FID_PERatio2                = 1130,         ///< 市盈率 2. 2 位小数股票：价格/本年每股利润债券：到期收益率基金：每百份的 IOPV 或净值权证：溢价率
    FID_PreClosePrice           = 1131,         ///< 昨收价. 3位小数；前收盘价格（如有除权除息，为除权除息后的收盘价）；对于货币市场基金实时申赎，取值为0.010
    FID_PreClosePriceUnderlying = 1132,         ///< 标的昨收价 . 期权标的证券除权除息调整后的前收盘价格，右对齐，单位：元 
    FID_PreSettlePrice          = 1133,         ///< 昨结算. 昨日结算价，右对齐，单位：元 ；4 decimal places
    FID_PreYearEPS              = 1134,         ///< 上年每股利润. 4 位小数
    FID_PriceDownLimit          = 1135,         ///< 跌幅价格. 3 位小数
    FID_TickSize                = 1136,         ///< 最小报价单位. "申报价格的最小变动单位
                                                ///< 上交所个股期权：单位元，精确到0.1厘"
    FID_PriceLimitType          = 1137,         ///< 限价参数类型. 0：8517/8518 字段为价格
    FID_UpDownLimitType         = 1138,         ///< 涨跌幅限制类型. ‘N’表示交易规则3.4.13规定的有涨跌幅限制类型或者权证管理办法第22条规定；‘R'表示交易规则3.4.15和3.4.16规定的无涨跌幅限制类型；’S‘表示回购涨跌幅控制类型。
    FID_PriceUpLimit            = 1139,         ///< 涨幅价格. 对于N类型涨跌幅限制的产品，该字段当日不会更改，基于前收盘价（已首日上市交易产品为发行价）计算；对于R类型五涨跌幅限制的产品，该字段取开盘时基于参考价格计算的上限价格。3 位小数
    FID_RecID                   = 1140,         ///< 业务索引. 从 1 开始，按 TradeChannel连续
    FID_RedemptionStatus        = 1141,         ///< 赎回（回售）标志. Y= 是,N= 否
    FID_RoundLot                = 1142,         ///< 整手数 . 交易单位（一手等于几张合约）
    FID_SecurityEN              = 1143,         ///< 英文证券名称. 
    FID_SecurityExchange        = 1144,         ///< 交易所代码. XSHE = 深圳证券交易所，不下发
    FID_SecurityName            = 1145,         ///< 证券名称. 
    FID_SecurityNo              = 1146,         ///< 证券数量. 
    FID_SecurityPhaseTag        = 1147,         ///< 交易状态.  该字段为4 位字符串，左起每位表示特定的含义，无定义则填空格。第1 位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示连续交易时段，‘B’表示休市时段，‘E’表示闭市时段，‘V’表示波动性中断，‘P’表示临时停牌。第2 位：‘0’表示未连续停牌，‘1’表示连续停牌。
    FID_SecurityStatus          = 1148,         ///< 产品状态标识. 第0位对应：‘N’表示首日上市；第1位对应：‘D’表示除权；第2位对应：‘R'表示除息；第3位对应：‘D‘表示国内主板正常交易产品，‘S’表示风险警示产品，‘P’表示退市整理产品。
    FID_SecurityStatusFlag      = 1149,         ///< 期权合约状态. 该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。第1位：‘0’表示可开仓，‘1’表示限制卖出开仓（包括备兑开仓）和买入开仓。第2位：‘0’表示未连续停牌，‘1’表示连续停牌。第3位：‘0’表示未临近到期日，‘1’表示距离到期日不足10个交易日。第4位：‘0’表示近期未做调整，‘1’表示最近10个交易日内合约发生过调整。第5位：‘A’表示当日新挂牌的合约，‘E’表示存续的合约，‘D’表示当日摘牌的合约。
    FID_SecuritySubType         = 1150,         ///< 证券子类别. "上交所：自定义详细证券类别
                                                ///< 深交所：SecuritySubType和CFICode确定了不同的证券类别，取值范围为：N/A（空值发布），A，B,AR，BR，G，O，R，AN，AS。"
    FID_SecurityTag             = 1151,         ///< 成交证券简称前缀. 4 位字符串
    FID_SecurityTypeID          = 1152,         ///< 证券属性. N = 正常，S = ST 股，P = PT 股，T = 代办转让证券，L = 上市开放型基金（LOF），O = 仅揭示净值的开放式基金，F = 非交易型开放式基金，E = ETF
    FID_SellLevelNo             = 1153,         ///< 卖盘价位数. "上交所个股期权实时行情：五档:总是5，空档位用0填充；
                                                ///< 深交所L2实时行情、上交所L2实时行情：10档行情，不足时补空"
    FID_SellLevelQueue          = 1154,         ///< 卖1档队列. 高频数据保存，先存订单数量,只有一档有此数据，50档，不足时补空
    FID_SellOrderID             = 1155,         ///< 卖方委托索引. 从 1 开始计数，0 表示无对应委托
    FID_SellOrderNo             = 1156,         ///< 卖方委托价位数. 
    FID_SellPrice01             = 1157,         ///< 申卖价. 3 位小数
    FID_SellPrice02             = 1158,         ///< 申卖价. 3 位小数
    FID_SellPrice03             = 1159,         ///< 申卖价. 3 位小数
    FID_SellPrice04             = 1160,         ///< 申卖价. 3 位小数
    FID_SellPrice05             = 1161,         ///< 申卖价. 3 位小数
    FID_SellPrice06             = 1162,         ///< 申卖价. 3 位小数
    FID_SellPrice07             = 1163,         ///< 申卖价. 3 位小数
    FID_SellPrice08             = 1164,         ///< 申卖价. 3 位小数
    FID_SellPrice09             = 1165,         ///< 申卖价. 3 位小数
    FID_SellPrice10             = 1166,         ///< 申卖价. 3 位小数
    FID_SellRecID               = 1167,         ///< 卖方订单号. 
    FID_SellVolume01            = 1168,         ///< 申卖量. 
    FID_SellVolume02            = 1169,         ///< 申卖量. 
    FID_SellVolume03            = 1170,         ///< 申卖量. 
    FID_SellVolume04            = 1171,         ///< 申卖量. 
    FID_SellVolume05            = 1172,         ///< 申卖量. 
    FID_SellVolume06            = 1173,         ///< 申卖量. 
    FID_SellVolume07            = 1174,         ///< 申卖量. 
    FID_SellVolume08            = 1175,         ///< 申卖量. 
    FID_SellVolume09            = 1176,         ///< 申卖量. 
    FID_SellVolume10            = 1177,         ///< 申卖量. 
    FID_SellVolumeUnit          = 1178,         ///< 卖数量单位. 卖数量单位
    FID_SetID                   = 1179,         ///< 证券集代号. 
    FID_SetNo                   = 1180,         ///< 产品集编号. 取值范围从1到999,。用来表明产品的一种分组方式，用于在多主机间记性负载均衡分配。该值在一个交易日内不会变化。
    FID_SettlePrice             = 1181,         ///< 结算价. 4 decimal places
    FID_ShrstrurefmFlag         = 1182,         ///< 股改标志. Y = 已经完成股改，N = 尚未完成股改
    FID_Side                    = 1183,         ///< 买卖方向. 0=无未匹配量，买卖两边的未匹配量都为 0;1=买方有未匹配量，卖方未匹配量=0;2=卖方有未匹配量，买方未匹配量=0
    FID_StartDate               = 1184,         ///< 首个交易日 . 期权首个交易日,YYYYMMDD (年*10000+月*100+日)
    FID_StatusID                = 1185,         ///< 交易状态. 
                                                ///< 2 = 停牌（Trading Halt），
                                                ///< 3 = 恢复（Resume），
                                                ///< 101 = 首日上市，
                                                ///< 102 = 增发新股，
                                                ///< 103 = 正常状态，
                                                ///< 104 = 上网定价发行，
                                                ///< 105 = 上网竞价发行，
                                                ///< 106 = 国债挂牌分销，
                                                ///< 107 = 长期停牌
    FID_SubScribeStatus         = 1186,         ///< 申购（转债、行权）标志. Y= 是,N= 否
    FID_Symbol                  = 1187,         ///< 证券代码. 
    FID_SymbolSource            = 1188,         ///< 证券代码源. 4 = ISIN,102 = 深圳证券交易所
    FID_SymbolUnderlying        = 1189,         ///< 基础证券代码. 
    FID_TradeAmount             = 1190,         ///< 成交金额. 成交金额
    FID_Time                    = 1191,         ///< 数据生成时间(毫秒). 143025001 表示 14:30:25.001
    FID_TotalAmount             = 1192,         ///< 成交总额. 元
    FID_TotalBuyNo              = 1193,         ///< 买入总笔数. 
    FID_TotalBuyOrderVolume     = 1195,         ///< 委托买入总量. 股票：股;权证：份;债券：手
    FID_TotalLongPosition       = 1196,         ///< 合约未平仓数 . 单位是 （张） 
    FID_TotalNo                 = 1197,         ///< 成交笔数. 
    FID_TotalPosition           = 1198,         ///< 持仓量. 
    FID_TotalSellNo             = 1199,         ///< 卖出总笔数. 
    FID_TotalSellOrderVolume    = 1201,         ///< 委托卖出总量. 
    FID_TotalVolume             = 1202,         ///< 成交总量. "上交所L2实时行情：股票：股;权证：份;债券：手；
                                                ///< 上交所个股期权：Trade volume of this security.如果期权合约的产品代码为“00000000”，则表示行情日期，格式为YYYYMMDD"
    FID_TotalWarrantExecVol     = 1203,         ///< 权证执行总量. 
    FID_TradableMarketNo        = 1204,         ///< 可流通已上市数量. 预留
    FID_TradableNo              = 1205,         ///< 可流通未上市数量. 预留
    FID_TradeChannel            = 1206,         ///< 成交通道. 
    FID_TradeCode               = 1207,         ///< 成交代码. 
    FID_TradeDate               = 1208,         ///< 市场日期. 
    FID_TradeMethod             = 1209,         ///< 交易方法. 1 = 有涨跌价，2 = 有涨跌幅，3 = 无涨跌停
    FID_TradePrice              = 1210,         ///< 成交价格. 3 位小数
    FID_TradeStage              = 1211,         ///< 证券竞价状态. 
                                                ///< 0 = 开市前,
                                                ///< 1 = 开盘集合竞价,
                                                ///< 2 = 连续竞价阶段,
                                                ///< 3 = 盘中临时停市,
                                                ///< 4 = 收盘集合竞价,
                                                ///< 5 = 集中竞价闭市,
                                                ///< 6 = 协议转让结束,
                                                ///< 7 = 闭市
    FID_TradeStatus             = 1212,         ///< 当前品种交易状态. 
    FID_TradeTime               = 1213,         ///< 成交时间. 143025006 表示14:30:25.006
    FID_TradeType               = 1214,         ///< 成交类别. 
    FID_TradeVolume             = 1215,         ///< 成交数量. 股票：股;权证：份;债券：张
    FID_TradingMechanism        = 1216,         ///< 产品交易类型. G = 集中竞价交易，N = 集中竞价交易+协议交易，O = 完全协议转让，空格 = 其他类型
    FID_UnderlyingType          = 1217,         ///< 标的证券类型 . EBS – ETF， ASH – A股 
    FID_Version                 = 1218,         ///< 合约版本号 . 期权合约的版本号。新挂合约是’1’ 
    FID_WarrantClearingType     = 1219,         ///< 权证结算方式. S = 证券结算，C = 现金结算
    FID_WarrantCreated          = 1220,         ///< 创设发生标志. Y= 是,N= 否
    FID_WarrantDownLimit        = 1221,         ///< 权证跌停价. （元）
    FID_WarrantDropped          = 1222,         ///< 注销发生标志. Y= 是,N= 否
    FID_WarrantUpLimit          = 1223,         ///< 权证涨停价. （元）
    FID_WithdrawBuyAmount       = 1224,         ///< 买入撤单额. 
    FID_WithdrawBuyNo           = 1225,         ///< 买入撤单笔数. 
    FID_WithdrawBuyVolume       = 1226,         ///< 买入撤单量. 
    FID_WithdrawSellAmount      = 1227,         ///< 卖出撤单额. 
    FID_WithdrawSellNo          = 1228,         ///< 卖出撤单笔数. 
    FID_WithdrawSellVolume      = 1229,         ///< 卖出撤单量. 
    FID_WtAvgBuyPrice           = 1230,         ///< 加权平均委买价. 3 位小数（元）
    FID_WtAvgSellPrice          = 1231,         ///< 加权平均委卖价. 3 位小数（元）
    FID_XDAmount                = 1232,         ///< 除息金额. 每股分红金额
    FID_XRRatio                 = 1233,         ///< 除权比例. 每股送股比例；对于国债预发行产品，为保证金比例。
    FID_XRXDFlag                = 1234,         ///< 除权除息标志. A = 除股息，B = 除分配，C = 除权，D = 新股，E = 除利息，N = 正常
    FID_YearEPS                 = 1235,         ///< 本年每股利润. 4 位小数
    FID_YTM                     = 1236,         ///< 债券到期收益率. 
    FID_ParticipateIndexNo      = 1237,         ///< 所属指数数量. 
    FID_ParticipateIndex01      = 1238,         ///< 所属指数. 不下发
    FID_ParticipateIndex02      = 1239,         ///< 所属指数. 不下发
    FID_ParticipateIndex03      = 1240,         ///< 所属指数. 不下发
    FID_MiscFeeNo               = 1241,         ///< 杂费类别数. 
    FID_MiscFeeAmount1          = 1242,         ///< 杂费额. 6 位小数
    FID_MiscFeeType1            = 1243,         ///< 杂费类别. 4 = 经手费，5 = 印花税，13 = 过户费
    FID_MiscFeeUnit1            = 1244,         ///< 杂费单位. 
    FID_MiscFeeAmount2          = 1245,         ///< 杂费额. 6 位小数
    FID_MiscFeeType2            = 1246,         ///< 杂费类别. 4 = 经手费，5 = 印花税，13 = 过户费
    FID_MiscFeeUnit2            = 1247,         ///< 杂费单位. 
    FID_MiscFeeAmount3          = 1248,         ///< 杂费额. 6 位小数
    FID_MiscFeeType3            = 1249,         ///< 杂费类别. 4 = 经手费，5 = 印花税，13 = 过户费
    FID_MiscFeeUnit3            = 1250,         ///< 杂费单位. 
    FID_TotalBuyOrderNo01       = 1251,         ///< 买一档总委托笔数. 深交所L2行情快照：为 0 表示不揭示
    FID_TotalBuyOrderNo02       = 1252,         ///< 买二档总委托笔数. 深交所L2行情快照：为 0 表示不揭示
    FID_TotalBuyOrderNo03       = 1253,         ///< 买三档总委托笔数. 深交所L2行情快照：为 0 表示不揭示
    FID_TotalBuyOrderNo04       = 1254,         ///< 买四档总委托笔数. 深交所L2行情快照：为 0 表示不揭示
    FID_TotalBuyOrderNo05       = 1255,         ///< 买五档总委托笔数. 深交所L2行情快照：为 0 表示不揭示
    FID_TotalBuyOrderNo06       = 1256,         ///< 买六档总委托笔数. 深交所L2行情快照：为 0 表示不揭示
    FID_TotalBuyOrderNo07       = 1257,         ///< 买七档总委托笔数. 深交所L2行情快照：为 0 表示不揭示
    FID_TotalBuyOrderNo08       = 1258,         ///< 买八档总委托笔数. 深交所L2行情快照：为 0 表示不揭示
    FID_TotalBuyOrderNo09       = 1259,         ///< 买九档总委托笔数. 深交所L2行情快照：为 0 表示不揭示
    FID_TotalBuyOrderNo10       = 1260,         ///< 买十档总委托笔数. 深交所L2行情快照：为 0 表示不揭示
    FID_TotalSellOrderNo01      = 1261,         ///< 卖一档总委托笔数. 为 0 表示不揭示
    FID_TotalSellOrderNo02      = 1262,         ///< 卖二档总委托笔数. 为 0 表示不揭示
    FID_TotalSellOrderNo03      = 1263,         ///< 卖三档总委托笔数. 为 0 表示不揭示
    FID_TotalSellOrderNo04      = 1264,         ///< 卖四档总委托笔数. 为 0 表示不揭示
    FID_TotalSellOrderNo05      = 1265,         ///< 卖五档总委托笔数. 为 0 表示不揭示
    FID_TotalSellOrderNo06      = 1266,         ///< 卖六档总委托笔数. 为 0 表示不揭示
    FID_TotalSellOrderNo07      = 1267,         ///< 卖七档总委托笔数. 为 0 表示不揭示
    FID_TotalSellOrderNo08      = 1268,         ///< 卖八档总委托笔数. 为 0 表示不揭示
    FID_TotalSellOrderNo09      = 1269,         ///< 卖九档总委托笔数. 为 0 表示不揭示
    FID_TotalSellOrderNo10      = 1270,         ///< 卖十档总委托笔数. 为 0 表示不揭示
    FID_SellLevelQueueNo01      = 1271,         ///< 卖一档揭示委托笔数. 为 0 表示不揭示
    FID_BuyLevelQueueNo01       = 1272,         ///< 买一档揭示委托笔数. 为 0 表示不揭示
    FID_PreTotalPosition        = 1092,         ///< 昨持仓量
    FID_PreDelta                = 1093,         ///< 昨虚实度
    FID_Delta                   = 1094,         ///< 今虚实度
    FID_SettleGroupID           = 1096,         ///< 结算组代码
    FID_SettleID                = 1097          ///< 结算编号
};

///消息结构体的字段类型
enum FIELD_TYPE{    
   Type_ERROR       = 0,           ///< 未知类型
   Type_Char        = 1,           ///< char
   Type_Short       = 2,           ///< short
   Type_Int         = 3,           ///< int
   Type_UInt        = 4,           ///< unsigned int
   Type_Longlong    = 5,           ///< long long 
   Type_ULonglong   = 6,           ///< unsigned long long 
   Type_String      = 7,           ///< string 字符串
   Type_Double      = 8,           ///< double
   Type_Sequence    = 9,           ///< queue 队列
};

/// 数据结构字段长度定义
#define SYMBOL_LEN          20     ///< 代码长度
#define SECURITY_NAME_LEN   20     ///< 证券名称长度
#define SECURITY_EN_LEN     24     ///< 英文证券简称
#define MARKET_TAG_LEN      10     ///< 市场标志长度
#define TIMEOUT_DEFAULT     3      ///< 默认设置超时时长

#endif // GTA_QTS_DATA_TYPE_H_
