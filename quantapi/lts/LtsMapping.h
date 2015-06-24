/**
 * @file LtsMapping.h
 * @brief 
 * @author HonePhy
 * Copyright () 2014-2020 QuantDigger. All rights reserved.
 * @chanege-log	 	
 * @version 0.1
 * @date 2015-06-15
 */
 
#ifndef LTSMAPPING_H

#define LTSMAPPING_H

#include <quantapi/datastruct.h>
#include <quantapi/mapping.h>
#include <iostream>
#include "SecurityFtdcUserApiDataType.h"
#include "SecurityFtdcUserApiStruct.h"

namespace QuantApi {

namespace Mapping {
    
inline char toLtsDirection(Direction direct){
    switch(direct) {
        case LONG:
			return SECURITY_FTDC_D_Buy;
        case SHORT:
			return SECURITY_FTDC_D_Sell;
        default:;
    }
}

inline Direction fromLtsDirection(const char direct)
{
	switch (direct)
	{
	case SECURITY_FTDC_D_Buy:
		return LONG;
	case SECURITY_FTDC_D_Sell:
		return SHORT;
	default:;
	}
}

inline char toLtsPriceType(PriceType deal){
    switch(deal) {
        case kLimit:
			return SECURITY_FTDC_OPT_LimitPrice;
        case kMarket:
			return SECURITY_FTDC_OPT_AnyPrice;
        default:;
    }
}

inline PriceType fromLtsPriceType(const char priceType)
{
	switch (priceType)
	{
	case SECURITY_FTDC_OPT_LimitPrice:
		return kLimit;
	case SECURITY_FTDC_OPT_AnyPrice:
		return kMarket;
	default:;
	}
}


inline char toLtsHedge(HedgeType hedge){
    switch(hedge) {
        case kSpeculation:
			return SECURITY_FTDC_HF_Speculation;	//投机
//        case kArbitrage:
//            return THOST_FTDC_HF_Arbitrage;	Lts接口中没有套利
        case kHedge:
			return SECURITY_FTDC_HF_Hedge;			//套保
        default:;
    }
}

inline HedgeType fromLtsHedge(const char hedge)
{
	switch (hedge)
	{
	case SECURITY_FTDC_HF_Speculation:
		return kSpeculation;
//	case THOST_FTDC_HF_Arbitrage:
//		return kArbitrage;
	case SECURITY_FTDC_HF_Hedge:
		return kHedge;
	default:;
	}
}

inline char toLtsTradeSide(TradeSide side) {
    switch(side) {
        case kBuy:
        case kShort:
        case kKai:
			return SECURITY_FTDC_OF_Open;
        case kCover:
        case kSell:
        case kPing:
			return SECURITY_FTDC_OF_Close;
        case kCoverToday:
        case kSellToday:
		case kPingToday:
			return SECURITY_FTDC_OF_CloseToday;
        default:;
    }
}

inline TradeSide fromLtsTradeSide(const char side)
{
	switch (side)
	{
	case SECURITY_FTDC_OF_Open:
		return kKai;
	case SECURITY_FTDC_OF_Close:
		return kPing;
	case SECURITY_FTDC_OF_CloseToday:
		return kPingToday;
	default:;
	}
}

inline char toLtsPositionDate(PositionDate posDate)
{
	switch (posDate)
	{
	case psdToday:
		return SECURITY_FTDC_PSD_Today;
	case psdHistory:
		return SECURITY_FTDC_PSD_History;
	default:;
	}
}

inline PositionDate fromLtsPositionDate(const char posDate)
{
	switch (posDate)
	{
	case SECURITY_FTDC_PSD_Today:
		return psdToday;
	case SECURITY_FTDC_PSD_History:
		return psdHistory;
	default:;
	}
}

inline void toLtsContract(const CSecurityFtdcInstrumentField &cc, Contract *c) {
	c->code = cc.InstrumentID;
	c->exch_type = map2QDExchType(cc.ExchangeID);
//	c->long_margin_ratio 多头保证金   //lts的合约结构没有这两个字段,pdf中有这个两个字段的说明
//	c->short_margin_ratio 空头保证金
	c->price_tick = cc.PriceTick;
	c->volume_multiple = cc.VolumeMultiple;
}

inline void fromLtsCaptial(const CSecurityFtdcTradingAccountField &cc, Captial *c) {
	c->available = cc.Available;
//	c->close_profit =     //lts 的资金账户没有平仓盈亏
	c->commission = cc.Commission;
	c->curr_margin = cc.CurrMargin;
	c->equity = cc.Balance;
	c->frozen_margin = cc.FrozenMargin;
//	c->position_profit   //lst 的资金账户没有持仓盈亏   
}


inline void fromLtsTransaction(const CSecurityFtdcTradeField &ctrans, Transaction *trans) {
	trans->contract.code = ctrans.InstrumentID;
	trans->contract.exch_type = map2QDExchType(ctrans.ExchangeID);
	char dt[19] = { 0 };
	strcpy(dt, ctrans.TradeDate);
	strcat(dt, ctrans.TradeTime);
	trans->datetime = Util::strDateTime2TimePoint(dt);
	trans->direction = fromLtsDirection(ctrans.Direction);
	trans->hedge_type = fromLtsHedge(ctrans.HedgeFlag);
	trans->id.init_id = atoi(ctrans.OrderRef);
	trans->id.order_id = atoi(ctrans.OrderSysID);
	trans->price = atof(ctrans.Price);
	//	通过上层应用中存放的orderList与该order中的OrderId和Contract成员比较找出相同Order，则可以对以下成员赋值。
	//	trans->price_type = fromCtpPriceType 
	trans->side = fromLtsTradeSide(ctrans.OffsetFlag);
	trans->volume = ctrans.Volume;
}

// 被撤单回报调用。 
inline void fromLtsOrder(const CSecurityFtdcInputOrderActionField &corder, Order *order) {
	order->id.init_id = atoi(corder.OrderRef);
//	order->id.order_id = atoi(corder.OrderSysID);
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
inline void fromLtsOrder(const CSecurityFtdcOrderField &corder, Order *order) {
	order->id.init_id = atoi(corder.OrderRef);
	order->id.order_id = atoi(corder.OrderSysID);
	order->contract.code = corder.InstrumentID;
	order->contract.exch_type = map2QDExchType(corder.ExchangeID);
	char dt[19] = { 0 };
	strcpy(dt, corder.InsertDate);
	strcat(dt, corder.ActiveTime);
	order->datetime = Util::strDateTime2TimePoint(dt);
	order->direction = fromLtsDirection(corder.Direction);
	order->hedge_type = fromLtsHedge(corder.CombHedgeFlag[0]);
	//	order->milliseconds = 
	order->price = atof(corder.LimitPrice);
	order->price_type = fromLtsPriceType(corder.OrderPriceType);
	order->side = fromLtsTradeSide(corder.CombOffsetFlag[0]);
	order->volume = corder.VolumeTotalOriginal;
}

inline void fromLtsPosition(const CSecurityFtdcInvestorPositionField &cpos, Position *pos) {
	pos->contract.code = cpos.InstrumentID;
	pos->contract.exch_type = map2QDExchType(cpos.ExchangeID);
	pos->direction = fromLtsDirection(cpos.PosiDirection);
	pos->hedge_type = fromLtsHedge(cpos.HedgeFlag);
//	pos->margin_ratio = 保证金率如何计算?
	pos->positionDate = fromLtsPositionDate(cpos.PositionDate);
	pos->use_margin = cpos.ExchangeMargin;
	pos->volume = cpos.TodayPosition;
	pos->yd_volume = cpos.YdPosition;
}

inline void fromLtsTick(const CSecurityFtdcDepthMarketDataField &ctick, TickData *tick) {
	tick->contract.code = ctick.InstrumentID;
	if (ctick.ExchangeID != NULL && ctick.ExchangeID[0] != '\0')
		tick->contract.exch_type = map2QDExchType(ctick.ExchangeID);
	tick->create_time = std::chrono::system_clock::now();
	char dt[19] = { 0 };
	strcpy(dt, ctick.TradingDay);
	strcat(dt, ctick.UpdateTime);
	tick->dt = Util::strDateTime2TimePoint(dt);
	tick->millisec = ctick.UpdateMillisec;
	tick->price = ctick.LastPrice;
	tick->volume = ctick.Volume;
}

} /* Mapping */
} /* QuantApi */
#endif /* end of include guard: LTSMAPPING_H */
