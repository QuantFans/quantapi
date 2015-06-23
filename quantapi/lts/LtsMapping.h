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

inline char toLtsPriceType(PriceType deal){
    switch(deal) {
        case kLimit:
			return SECURITY_FTDC_OPT_LimitPrice;
        case kMarket:
			return SECURITY_FTDC_OPT_AnyPrice;
        default:;
    }
}


inline char toLtsHedge(HedgeType hedge){
    switch(hedge) {
        case kSpeculation:
			return SECURITY_FTDC_HF_Speculation;	//Ͷ��
//        case kArbitrage:
//            return THOST_FTDC_HF_Arbitrage;	Lts�ӿ���û������
        case kHedge:
			return SECURITY_FTDC_HF_Hedge;			//�ױ�
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
			return SECURITY_FTDC_OF_CloseToday;
        default:;
    }

}

inline void toLtsContract(const CSecurityFtdcInstrumentField &cc, Contract *c) {
	c->code = cc.InstrumentID;
	c->exch_type = map2QDExchType(cc.ExchangeID);
//	c->long_margin_ratio ��ͷ��֤��   //lts�ĺ�Լ�ṹû���������ֶ�
//	c->short_margin_ratio ��ͷ��֤��
	c->price_tick = cc.PriceTick;
	c->volume_multiple = cc.VolumeMultiple;

//        cerr<<" ��Ӧ | ��Լ:"<<pInstrument->InstrumentID
//            <<" ������:"<<pInstrument->DeliveryMonth
//            <<" ��ͷ��֤����:"<<pInstrument->LongMarginRatio
//            <<" ����������:"<<pInstrument->ExchangeID
//            <<" ��ͷ��֤����:"<<pInstrument->ShortMarginRatio<<endl;    
}

inline void fromLtsCaptial(const CSecurityFtdcTradingAccountField &cc, Captial *c) {
	c->available = cc.Available;
//	c->close_profit =     //lts ���ʽ��˻�û��ƽ��ӯ��
	c->commission = cc.Commission;
	c->curr_margin = cc.CurrMargin;
	c->equity = cc.Balance;
	c->frozen_margin = cc.FrozenMargin;
//	c->position_profit   //lst ���ʽ��˻�û�гֲ�ӯ��

//        cerr<<" ��Ӧ | Ȩ��:"<<cc.Balance
//            <<" ����:"<<cc.Available   
//            <<" ��֤��:"<<cc.CurrMargin
//            <<" ƽ��ӯ��:"<<cc.CloseProfit
//            <<" �ֲ�ӯ��"<<cc.PositionProfit
//            <<" ������:"<<cc.Commission
//            <<" ���ᱣ֤��:"<<cc.FrozenMargin
//            << endl;    
}


inline void fromLtsTransaction(const CSecurityFtdcTradeField &ctrans, Transaction *trans) {
//	trans->contract 
//	ctrans.
//  CThostFtdcTradeField* trade = new CThostFtdcTradeField();
//  memcpy(trade,  pTrade, sizeof(CThostFtdcTradeField));
//  cerr<<" �ر� | �����ѳɽ�...�ɽ����:"<<trade->TradeID<<endl;
  
}

// �������ر����á� 
inline void fromLtsOrder(const CSecurityFtdcInputOrderActionField &corder, Order *order) {

//    cerr<< " ��Ӧ | �����ɹ�..."
//      << "������:"<<corder.ExchangeID
//      <<" �������:"<<corder.OrderSysID<<endl;
}

// ���µ��ر�����
inline void fromLtsOrder(const CSecurityFtdcOrderField &corder, Order *order) {

//    cerr<< " ��Ӧ | �����ɹ�..."
//      << "������:"<<corder.ExchangeID
//      <<" �������:"<<corder.OrderSysID<<endl;
}

inline void fromLtsPosition(const CSecurityFtdcInvestorPositionField &cpos, Position *pos) {
	std::cerr << " ��Ӧ | ��Լ:" << cpos.InstrumentID
		//      <<" ����:"<<MapDirection(pInvestorPosition->PosiDirection-2,false)
		<< " �ֲܳ�:" << cpos.Position
		<< " ���:" << cpos.YdPosition
		<< " ���:" << cpos.TodayPosition << std::endl;
//      <<" �ֲ�ӯ��:"<<cpos.PositionProfit
 //     <<" ��֤��:"<<cpos.UseMargin<<std::endl;
}

inline void fromLtsTick(const CSecurityFtdcDepthMarketDataField &ctick, TickData *tick) {
    std::cout<<"contract: "<<ctick.InstrumentID<<std::endl
        <<"update time: "<<std::string(ctick.UpdateTime)<<std::endl
        <<"update milliseconds: "<<ctick.UpdateMillisec<<std::endl
        <<"buy 1: "<<ctick.BidPrice1 <<std::endl    
        <<"trading day: "<<(ctick.TradingDay)<<std::endl;
//	///������
//	TThostFtdcDateType	TradingDay;
//	///��Լ����
//	TThostFtdcInstrumentIDType	InstrumentID;
//	///����������
//	TThostFtdcExchangeIDType	ExchangeID;
//	///��Լ�ڽ������Ĵ���
//	TThostFtdcExchangeInstIDType	ExchangeInstID;
//	///���¼�
//	TThostFtdcPriceType	LastPrice;
//	///�ϴν����
//	TThostFtdcPriceType	PreSettlementPrice;
//	///������
//	TThostFtdcPriceType	PreClosePrice;
//	///��ֲ���
//	TThostFtdcLargeVolumeType	PreOpenInterest;
//	///����
//	TThostFtdcPriceType	OpenPrice;
//	///��߼�
//	TThostFtdcPriceType	HighestPrice;
//	///��ͼ�
//	TThostFtdcPriceType	LowestPrice;
//	///����
//	TThostFtdcVolumeType	Volume;
//	///�ɽ����
//	TThostFtdcMoneyType	Turnover;
//	///�ֲ���
//	TThostFtdcLargeVolumeType	OpenInterest;
//	///������
//	TThostFtdcPriceType	ClosePrice;
//	///���ν����
//	TThostFtdcPriceType	SettlementPrice;
//	///��ͣ���
//	TThostFtdcPriceType	UpperLimitPrice;
//	///��ͣ���
//	TThostFtdcPriceType	LowerLimitPrice;
//	///����ʵ��
//	TThostFtdcRatioType	PreDelta;
//	///����ʵ��
//	TThostFtdcRatioType	CurrDelta;
//	///����޸�ʱ��
//	TThostFtdcTimeType	UpdateTime;
//	///����޸ĺ���
//	TThostFtdcMillisecType	UpdateMillisec;
//	///�����һ
//	TThostFtdcPriceType	BidPrice1;
//	///������һ
//	TThostFtdcVolumeType	BidVolume1;
//	///������һ
//	TThostFtdcPriceType	AskPrice1;
//	///������һ
//	TThostFtdcVolumeType	AskVolume1;
//	///����۶�
//	TThostFtdcPriceType	BidPrice2;
//	///��������
//	TThostFtdcVolumeType	BidVolume2;
//	///�����۶�
//	TThostFtdcPriceType	AskPrice2;
//	///��������
//	TThostFtdcVolumeType	AskVolume2;
//	///�������
//	TThostFtdcPriceType	BidPrice3;
//	///��������
//	TThostFtdcVolumeType	BidVolume3;
//	///��������
//	TThostFtdcPriceType	AskPrice3;
//	///��������
//	TThostFtdcVolumeType	AskVolume3;
//	///�������
//	TThostFtdcPriceType	BidPrice4;
//	///��������
//	TThostFtdcVolumeType	BidVolume4;
//	///��������
//	TThostFtdcPriceType	AskPrice4;
//	///��������
//	TThostFtdcVolumeType	AskVolume4;
//	///�������
//	TThostFtdcPriceType	BidPrice5;
//	///��������
//	TThostFtdcVolumeType	BidVolume5;
//	///��������
//	TThostFtdcPriceType	AskPrice5;
//	///��������
//	TThostFtdcVolumeType	AskVolume5;
//	///���վ���
//	TThostFtdcPriceType	AveragePrice;
}

/////Ͷ��
//#define THOST_FTDC_HF_Speculation '1'
/////����
//#define THOST_FTDC_HF_Arbitrage '2'
/////�ױ�
//#define THOST_FTDC_HF_Hedge '3'


} /* Mapping */
} /* QuantApi */
#endif /* end of include guard: LTSMAPPING_H */
