#ifndef CTPMAPPING_H

#define CTPMAPPING_H
#include <quantapi/datastruct.h>
#include <quantapi/mapping.h>
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

inline Direction fromCtpDirection(const char direct)
{
	switch (direct)
	{
	case THOST_FTDC_D_Buy:
		return LONG;
	case THOST_FTDC_D_Sell:
		return SHORT;
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

inline PriceType fromCtpPriceType(const char priceType)
{
	switch (priceType)
	{
	case THOST_FTDC_OPT_LimitPrice:
		return kLimit;
	case THOST_FTDC_OPT_AnyPrice:
		return kMarket;
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

inline HedgeType fromCtpHedge(const char hedge)
{
	switch (hedge)
	{
	case THOST_FTDC_HF_Speculation:
		return kSpeculation;
	case THOST_FTDC_HF_Arbitrage:
		return kArbitrage;
	case THOST_FTDC_HF_Hedge:
		return kHedge;
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
		case kPingToday:
            return THOST_FTDC_OF_CloseToday;
        default:;
    }

}

inline TradeSide fromCtpTradeSide(const char side)
{
	switch (side)
	{
	case THOST_FTDC_OF_Open:
		return kKai;
	case THOST_FTDC_OF_Close:
		return kPing;
	case THOST_FTDC_OF_CloseToday:
		return kPingToday;
	default:;
	}
}

inline char toCtpPositionDate(PositionDate posDate)
{
	switch (posDate)
	{
	case psdToday:
		return THOST_FTDC_PSD_Today;
	case psdHistory:
		return THOST_FTDC_PSD_History;
	default:;
	}
}

inline PositionDate fromCtpPositionDate(const char posDate)
{
	switch (posDate)
	{
	case THOST_FTDC_PSD_Today:
		return psdToday;
	case THOST_FTDC_PSD_History:
		return psdHistory;
	default:;
	}
}

inline void toCtpContract(const CThostFtdcInstrumentField &cc, Contract *c) {
	c->code = cc.InstrumentID;
	c->exch_type = map2QDExchType(cc.ExchangeID);
	c->long_margin_ratio = cc.LongMarginRatio;
	c->price_tick = cc.PriceTick;
	c->short_margin_ratio = cc.ShortMarginRatio;
	c->volume_multiple = cc.VolumeMultiple;
}

inline void fromCtpCaptial(const CThostFtdcTradingAccountField &cc, Captial *c) {
	c->available = cc.Available;
	c->close_profit = cc.CloseProfit;
	c->commission = cc.Commission;
	c->curr_margin = cc.CurrMargin;
	c->equity = cc.Balance;
	c->frozen_margin = cc.FrozenMargin;
	c->position_profit = cc.PositionProfit;   
}


inline void fromCtpTransaction(const CThostFtdcTradeField &ctrans, Transaction *trans) {
	trans->contract.code = ctrans.InstrumentID;
	trans->contract.exch_type = map2QDExchType(ctrans.ExchangeID);
	char dt[19] = { 0 };
	strcpy(dt, ctrans.TradeDate);
	strcat(dt, ctrans.TradeTime);
	trans->datetime = Util::strDateTime2TimePoint(dt);
	trans->direction = fromCtpDirection(ctrans.Direction);
	trans->hedge_type = fromCtpHedge(ctrans.HedgeFlag);
	trans->id.init_id = atoi(ctrans.OrderRef);
	trans->id.order_id = atoi(ctrans.OrderSysID);
	trans->price = ctrans.Price;
//	通过上层应用中存放的orderList与该order中的OrderId和Contract成员比较找出相同Order，则可以对以下成员赋值。
//	trans->price_type = fromCtpPriceType 
	trans->side = fromCtpTradeSide(ctrans.OffsetFlag);
	trans->volume = ctrans.Volume;
    trans->trader_id = atoi(ctrans.TraderID);
}

// 被撤单回报调用。 
inline void fromCtpOrder(const CThostFtdcInputOrderActionField &corder, Order *order) {
	order->id.init_id = atoi(corder.OrderRef);
	order->id.order_id = atoi(corder.OrderSysID);
	order->contract.code = corder.InstrumentID;
	order->contract.exch_type = map2QDExchType(corder.ExchangeID);
	
	order->datetime = std::chrono::system_clock::now();

//	通过上层应用中存放的orderList与该order中的OrderId和Contract成员比较找出相同Order，则可以对以下成员赋值。
//	order->direction =  
//	order->hedge_type = 
//	order->price_type =
//	order->side =
	order->price = corder.LimitPrice;
}

// 被下单回报调用
inline void fromCtpOrder(const CThostFtdcOrderField &corder, Order *order) {
	order->id.init_id = atoi(corder.OrderRef);
	order->id.order_id = atoi(corder.OrderSysID);
	order->contract.code = corder.InstrumentID;
	order->contract.exch_type = map2QDExchType(corder.ExchangeID);
	char dt[19] = { 0 };
	strcpy(dt, corder.InsertDate);
	strcat(dt, corder.ActiveTime);
	order->datetime = Util::strDateTime2TimePoint(dt);
	order->direction = fromCtpDirection(corder.Direction);
	order->hedge_type = fromCtpHedge(corder.CombHedgeFlag[0]);
//	order->milliseconds = 
	order->price = corder.LimitPrice;
	order->price_type = fromCtpPriceType(corder.OrderPriceType);
	order->side = fromCtpTradeSide(corder.CombOffsetFlag[0]);
	order->volume = corder.VolumeTotalOriginal;
}

inline void fromCtpPosition(const CThostFtdcInvestorPositionField &cpos, Position *pos) {
	pos->contract.code = cpos.InstrumentID;
	pos->positionDate = fromCtpPositionDate(cpos.PositionDate);
	pos->direction = fromCtpDirection(cpos.PosiDirection);
	pos->hedge_type = fromCtpHedge(cpos.HedgeFlag);
	pos->margin_ratio = cpos.MarginRateByMoney;
	pos->use_margin = cpos.UseMargin;
	pos->volume = cpos.TodayPosition;
	pos->yd_volume = cpos.YdPosition;
    pos->profit = cpos.PositionProfit;
    pos->cost = cpos.PositionCost;
}

inline void fromCtpTick(const CThostFtdcDepthMarketDataField &ctick, TickData *tick) {
	tick->contract.code = ctick.InstrumentID;
	if (ctick.ExchangeID != NULL && ctick.ExchangeID[0] != '\0')
		tick->contract.exch_type = map2QDExchType(ctick.ExchangeID);
	tick->create_time = std::chrono::system_clock::now();
	char dt[20] = { 0 };
    int year = 0, month = 0, day = 0;
    sscanf(ctick.TradingDay, "%4d", &year);
    sscanf(ctick.TradingDay+4, "%2d", &month);
    sscanf(ctick.TradingDay+6, "%2d", &day);
    sprintf(dt,"%4d-%02d-%02d %8s",year,month,day,ctick.UpdateTime);
	tick->dt = Util::strDateTime2TimePoint(dt);
	tick->millisec = ctick.UpdateMillisec;
	tick->price = ctick.LastPrice;
	tick->volume = ctick.Volume;
    tick->total_price = ctick.Turnover;
    tick->pre_close = ctick.PreClosePrice;
    tick->average = ctick.AveragePrice;
    tick->open = ctick.OpenPrice;
    tick->high = ctick.HighestPrice;
    tick->low = ctick.LowestPrice;

    tick->buy01_price = ctick.BidPrice1;
    tick->buy01_volume = ctick.BidVolume1;
    tick->buy02_price = ctick.BidPrice2;
    tick->buy02_volume = ctick.BidVolume2;
    tick->buy03_price = ctick.BidPrice3;
    tick->buy03_volume = ctick.BidVolume3;
    tick->buy04_price = ctick.BidPrice4;
    tick->buy04_volume = ctick.BidVolume4;
    tick->buy05_price = ctick.BidPrice5;
    tick->buy05_volume = ctick.BidVolume5;

    tick->sell01_price = ctick.AskPrice1;
    tick->sell01_volume = ctick.AskVolume1;
    tick->sell02_price = ctick.AskPrice2;
    tick->sell02_volume = ctick.AskVolume2;
    tick->sell03_price = ctick.AskPrice3;
    tick->sell03_volume = ctick.AskVolume3;
    tick->sell04_price = ctick.AskPrice4;
    tick->sell04_volume = ctick.AskVolume4;
    tick->sell05_price = ctick.AskPrice5;
    tick->sell05_volume = ctick.AskVolume5;
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
