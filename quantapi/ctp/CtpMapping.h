#ifndef CTPMAPPING_H

#define CTPMAPPING_H
#include <quantapi/datastruct.h>
#include "ThostFtdcUserApiDataType.h" 
#include <iostream>

namespace QuantApi {
    
namespace Mapping {
using namespace std;
    
inline char toCtpDirection(Direction direct){
    switch(direct) {
        case LONG:
            return THOST_FTDC_D_Buy;
        case SHORT:
            return THOST_FTDC_D_Sell;
        default:;
    }
}

inline char toCtpPriceType(PriceType deal){
    switch(deal) {
        case kLimit:
            return THOST_FTDC_OPT_LimitPrice;
        case kMarket:
            return THOST_FTDC_OPT_AnyPrice;
        default:;
    }
}


inline char toCtpHedge(HedgeType hedge){
    switch(hedge) {
        case kSpeculation:
            return THOST_FTDC_HF_Speculation;
        case kArbitrage:
            return THOST_FTDC_HF_Arbitrage;
        case kHedge:
            return THOST_FTDC_HF_Hedge;
        default:;
    }
}

inline char toCtpTradeSide(TradeSide side) {
    switch(side) {
        case kBuy:
        case kShort:
        case kKai:
            return THOST_FTDC_OF_Open;
        case kCover:
        case kSell:
        case kPing:
            return THOST_FTDC_OF_Close;
        case kCoverToday:
        case kSellToday:
            return THOST_FTDC_OF_CloseToday;
        default:;
    }

}

inline void toCtpContract(const CThostFtdcInstrumentField &cc, Contract *c) {
//        cerr<<" 响应 | 合约:"<<pInstrument->InstrumentID
//            <<" 交割月:"<<pInstrument->DeliveryMonth
//            <<" 多头保证金率:"<<pInstrument->LongMarginRatio
//            <<" 交易所代码:"<<pInstrument->ExchangeID
//            <<" 空头保证金率:"<<pInstrument->ShortMarginRatio<<endl;    
}

inline void fromCtpCaptial(const CThostFtdcTradingAccountField &cc, Captial *c) {
        cerr<<" 响应 | 权益:"<<cc.Balance
            <<" 可用:"<<cc.Available   
            <<" 保证金:"<<cc.CurrMargin
            <<" 平仓盈亏:"<<cc.CloseProfit
            <<" 持仓盈亏"<<cc.PositionProfit
            <<" 手续费:"<<cc.Commission
            <<" 冻结保证金:"<<cc.FrozenMargin
            << endl;    
}


inline void fromCtpTransaction(const CThostFtdcTradeField &ctrans, Transaction *trans) {
//  CThostFtdcTradeField* trade = new CThostFtdcTradeField();
//  memcpy(trade,  pTrade, sizeof(CThostFtdcTradeField));
//  cerr<<" 回报 | 报单已成交...成交编号:"<<trade->TradeID<<endl;
  
}

// 被撤单回报调用。 
inline void fromCtpOrder(const CThostFtdcInputOrderActionField &corder, Order *order) {
//    cerr<< " 响应 | 撤单成功..."
//      << "交易所:"<<corder.ExchangeID
//      <<" 报单编号:"<<corder.OrderSysID<<endl;
}

// 被下单回报调用
inline void fromCtpOrder(const CThostFtdcOrderField &corder, Order *order) {
//    cerr<< " 响应 | 撤单成功..."
//      << "交易所:"<<corder.ExchangeID
//      <<" 报单编号:"<<corder.OrderSysID<<endl;
}

inline void fromCtpPosition(const CThostFtdcInvestorPositionField &cpos, Position *pos) {
    cerr<<" 响应 | 合约:"<<cpos.InstrumentID
//      <<" 方向:"<<MapDirection(pInvestorPosition->PosiDirection-2,false)
      <<" 总持仓:"<<cpos.Position
      <<" 昨仓:"<<cpos.YdPosition 
      <<" 今仓:"<<cpos.TodayPosition
      <<" 持仓盈亏:"<<cpos.PositionProfit
      <<" 保证金:"<<cpos.UseMargin<<endl;
}

inline void fromCtpTick(const CThostFtdcDepthMarketDataField &ctick, TickData *tick) {
    cout<<"contract: "<<ctick.InstrumentID<<endl
        <<"update time: "<<string(ctick.UpdateTime)<<endl
        <<"update milliseconds: "<<ctick.UpdateMillisec<<endl
        <<"buy 1: "<<ctick.BidPrice1 <<endl    
        <<"trading day: "<<(ctick.TradingDay)<<endl;
//	///交易日
//	TThostFtdcDateType	TradingDay;
//	///合约代码
//	TThostFtdcInstrumentIDType	InstrumentID;
//	///交易所代码
//	TThostFtdcExchangeIDType	ExchangeID;
//	///合约在交易所的代码
//	TThostFtdcExchangeInstIDType	ExchangeInstID;
//	///最新价
//	TThostFtdcPriceType	LastPrice;
//	///上次结算价
//	TThostFtdcPriceType	PreSettlementPrice;
//	///昨收盘
//	TThostFtdcPriceType	PreClosePrice;
//	///昨持仓量
//	TThostFtdcLargeVolumeType	PreOpenInterest;
//	///今开盘
//	TThostFtdcPriceType	OpenPrice;
//	///最高价
//	TThostFtdcPriceType	HighestPrice;
//	///最低价
//	TThostFtdcPriceType	LowestPrice;
//	///数量
//	TThostFtdcVolumeType	Volume;
//	///成交金额
//	TThostFtdcMoneyType	Turnover;
//	///持仓量
//	TThostFtdcLargeVolumeType	OpenInterest;
//	///今收盘
//	TThostFtdcPriceType	ClosePrice;
//	///本次结算价
//	TThostFtdcPriceType	SettlementPrice;
//	///涨停板价
//	TThostFtdcPriceType	UpperLimitPrice;
//	///跌停板价
//	TThostFtdcPriceType	LowerLimitPrice;
//	///昨虚实度
//	TThostFtdcRatioType	PreDelta;
//	///今虚实度
//	TThostFtdcRatioType	CurrDelta;
//	///最后修改时间
//	TThostFtdcTimeType	UpdateTime;
//	///最后修改毫秒
//	TThostFtdcMillisecType	UpdateMillisec;
//	///申买价一
//	TThostFtdcPriceType	BidPrice1;
//	///申买量一
//	TThostFtdcVolumeType	BidVolume1;
//	///申卖价一
//	TThostFtdcPriceType	AskPrice1;
//	///申卖量一
//	TThostFtdcVolumeType	AskVolume1;
//	///申买价二
//	TThostFtdcPriceType	BidPrice2;
//	///申买量二
//	TThostFtdcVolumeType	BidVolume2;
//	///申卖价二
//	TThostFtdcPriceType	AskPrice2;
//	///申卖量二
//	TThostFtdcVolumeType	AskVolume2;
//	///申买价三
//	TThostFtdcPriceType	BidPrice3;
//	///申买量三
//	TThostFtdcVolumeType	BidVolume3;
//	///申卖价三
//	TThostFtdcPriceType	AskPrice3;
//	///申卖量三
//	TThostFtdcVolumeType	AskVolume3;
//	///申买价四
//	TThostFtdcPriceType	BidPrice4;
//	///申买量四
//	TThostFtdcVolumeType	BidVolume4;
//	///申卖价四
//	TThostFtdcPriceType	AskPrice4;
//	///申卖量四
//	TThostFtdcVolumeType	AskVolume4;
//	///申买价五
//	TThostFtdcPriceType	BidPrice5;
//	///申买量五
//	TThostFtdcVolumeType	BidVolume5;
//	///申卖价五
//	TThostFtdcPriceType	AskPrice5;
//	///申卖量五
//	TThostFtdcVolumeType	AskVolume5;
//	///当日均价
//	TThostFtdcPriceType	AveragePrice;
}

/////投机
//#define THOST_FTDC_HF_Speculation '1'
/////套利
//#define THOST_FTDC_HF_Arbitrage '2'
/////套保
//#define THOST_FTDC_HF_Hedge '3'


} /* Mapping */
} /* QuantApi */
#endif /* end of include guard: CTPMAPPING_H */
