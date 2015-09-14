/////////////////////////////////////////////////////////////////////////////////////////
// @file：CfxUdpStruct.h
// 描    述：中金所UDP发送数据结构定义
// 作    者：mars.zippo
// 创建日期：2014-03-20
// 版    本：v1.0.0
// 修改  者：
// 修改日期：
// 修改内容：
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef GTA_CFX_UDP_STRUCT_H
#define GTA_CFX_UDP_STRUCT_H

/// 中金所深度市场行情
struct CFfexFtdcDepthMarketData
{
    char    szTradingDay[9];        ///< 交易日
    char    szSettlementGroupID[9]; ///< 结算组代码
    int     nSettlementID;          ///< 结算编号
    double  dLastPrice;             ///< 最新价
    double  dPreSettlementPrice;    ///< 昨结算
    double  dPreClosePrice;         ///< 昨收盘
    double  dPreOpenInterest;       ///< 昨持仓量
    double  dOpenPrice;             ///< 今开盘
    double  dHighestPrice;          ///< 最高价
    double  dLowestPrice;           ///< 最低价
    int     nVolume;                ///< 数量
    double  dTurnover;              ///< 成交金额
    double  dOpenInterest;          ///< 持仓量
    double  dClosePrice;            ///< 今收盘
    double  dSettlementPrice;       ///< 今结算
    double  dUpperLimitPrice;       ///< 涨停板价    
    double  dLowerLimitPrice;       ///< 跌停板价
    double  dPreDelta;              ///< 昨虚实度
    double  dCurrDelta;             ///< 今虚实度    
    char    szUpdateTime[9];        ///< 最后修改时间    
    int     nUpdateMillisec;        ///< 最后修改毫秒    
    char    szInstrumentID[31];     ///< 合约代码    
    double  dBidPrice1;             ///< 申买价一
    int     nBidVolume1;            ///< 申买量一
    double  dAskPrice1;             ///< 申卖价一
    int     nAskVolume1;            ///< 申卖量一
    double  dBidPrice2;             ///< 申买价二
    int     nBidVolume2;            ///< 申买量二
    double  dAskPrice2;             ///< 申卖价二
    int     nAskVolume2;            ///< 申卖量二
    double  dBidPrice3;             ///< 申买价三
    int     nBidVolume3;            ///< 申买量三
    double  dAskPrice3;             ///< 申卖价三
    int     nAskVolume3;            ///< 申卖量三
    double  dBidPrice4;             ///< 申买价四
    int     nBidVolume4;            ///< 申买量四
    double  dAskPrice4;             ///< 申卖价四
    int     nAskVolume4;            ///< 申卖量四
    double  dBidPrice5;             ///< 申买价五
    int     nBidVolume5;            ///< 申买量五
    double  dAskPrice5;             ///< 申卖价五
    int     nAskVolume5;            ///< 申卖量五
};


#endif
