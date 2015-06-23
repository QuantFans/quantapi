/**
 * @file LtsTrader.cpp
 * @brief 
 * @author HonePhy
 * Copyright () 2014-2020 QuantDigger. All rights reserved.
 * @chanege-log 	
		2015-06-14 根据quantapi接口的调整做修改
 * @version 0.1
 * @date 2015-04-10
 */

#include "LtsTrader.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "../../util/log_assert.h"
#include "quantapi/mapping.h"
#include "quantapi/lts/LtsMapping.h"

namespace Global {
    tm g_today;   ///< 当日日期，在登入交易接口的时候被初始化。
} /* Global */

namespace QuantApi {

std::vector<CSecurityFtdcOrderField*> orderList; //已经报单列表
std::vector<CSecurityFtdcTradeField*> tradeList; //成交列表


LtsTrader::LtsTrader(char* trade_front) {
	LOG_ASSERT(trade_front);
	api_ = CSecurityFtdcTraderApi::CreateFtdcTraderApi();
	api_->RegisterSpi(this);
	locked_ = false;
	registerFront(trade_front, true);
	api_->Init();
	wait(true);
}

LtsTrader::~LtsTrader() {
    api_->Join();
    api_->Release();
}


int LtsTrader::login(const LogonInfo &info, bool syn) {
	if (syn) synLock();
	CSecurityFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, info.broker_id);
	strcpy(req.UserID, info.user_id);
	strcpy(req.Password, info.password);
	strcpy(broker_id_, broker_id_);
	strcpy(user_id_, user_id_);
	int ret = api_->ReqUserLogin(&req, nextRequestId());
	std::cout << "try login..." << ((ret == 0) ? "Sucess" : "Failed") << std::endl;
	wait(syn);
	return ret;
}

int LtsTrader::logout(const LogonInfo &info, bool syn) {
	if (syn) synLock();
	CSecurityFtdcUserLogoutField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);
	strcpy(req.UserID, user_id_);
	int ret = api_->ReqUserLogout(&req, nextRequestId());
	std::cout << "sending | logouting..." << ((ret == 0) ? "Sucess" : "Failed") << std::endl;
	wait(syn);
	return ret;
}

int LtsTrader::reqContract(const Contract &c, bool syn) {
	if (syn) synLock();
	CSecurityFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.InstrumentID, c.code.c_str());
	int ret = api_->ReqQryInstrument(&req, nextRequestId());
	std::cout << "sending | qry instrument..." << ((ret == 0) ? "Sucess" : "Failed") << std::endl;
	wait(syn);
	return ret;
}

int LtsTrader::reqTick(const Contract &c, bool syn) {
	if (syn) synLock();
	CSecurityFtdcQryDepthMarketDataField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.InstrumentID, c.code.c_str());
	int ret = api_->ReqQryDepthMarketData(&req, nextRequestId());
	std::cout << "sending | qry instrument marketData..." << ((ret == 0) ? "Sucess" : "Failed") << std::endl;
	wait(syn);
	return ret;
}

int LtsTrader::reqCaptial(bool syn) {
	if (syn) synLock();
	CSecurityFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);
	strcpy(req.InvestorID, user_id_);
	int ret = api_->ReqQryTradingAccount(&req, nextRequestId());
	std::cout << "sending | qry Trading account..." << ((ret == 0) ? "Sucess" : "Failed") << std::endl;
	wait(syn);
	return ret;
}

int LtsTrader::reqPosition(const Contract &contract, bool syn) {
	if (syn) synLock();
	CSecurityFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);
	strcpy(req.InvestorID, user_id_);
	strcpy(req.InstrumentID, contract.code.c_str());	
	int ret = api_->ReqQryInvestorPosition(&req, nextRequestId());
	std::cout << "sending | qry Investor position..." << ((ret == 0) ? "Sucess" : "Failed") << std::endl;;
	wait(syn);
	return ret;
}

int LtsTrader::order(const Order &order, bool syn) {
	if (syn) synLock();
	CSecurityFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));	
	strcpy(req.BrokerID, broker_id_);  									//应用单元代码	
	strcpy(req.InvestorID, user_id_); 									//投资者代码	
	strcpy(req.InstrumentID, order.contract.code.c_str()); 				//合约代码
	
	sprintf(req.OrderRef, "%d", order.id.init_id);						//报单引用
	req.Direction = Mapping::toLtsDirection(order.direction);  			//买卖方向 要修改
	req.CombHedgeFlag[0] = Mapping::toLtsHedge(order.hedge_type);		//组合投机套保标志	
	req.OrderPriceType = Mapping::toLtsPriceType(order.price_type);		//价格类型=市价或限价
	req.CombOffsetFlag[0] = Mapping::toLtsTradeSide(order.side);		//组合开平标志:开仓
	
	sprintf(req.LimitPrice, "%f", order.price); 								//价格
	req.VolumeTotalOriginal = order.volume;										//数量	
	
	req.VolumeCondition = SECURITY_FTDC_VC_AV; 							//成交量类型:任何数量
	req.MinVolume = 1;													//最小成交量:1	
	
	req.ContingentCondition = SECURITY_FTDC_CC_Immediately;  			//触发条件:立即
	req.ForceCloseReason = SECURITY_FTDC_FCC_NotForceClose;				//强平原因:非强平
	
	req.IsAutoSuspend = 0;												//自动挂起标志:否	
	req.UserForceClose = 0;   											//用户强评标志:否
    
	if (0 == order.price){
        req.TimeCondition = SECURITY_FTDC_TC_IOC;						//有效期类型:立即完成，否则撤销
    }else{
        req.TimeCondition = SECURITY_FTDC_TC_GFD;  						//有效期类型:当日有效
    }

	int ret = api_->ReqOrderInsert(&req, nextRequestId());
	std::cout << "sending | Order Insert..." << ((ret == 0) ? "Sucess" : "Failed") << std::endl;
	wait(syn);
	return ret;
}

int LtsTrader::cancel_order(int orderSeq, bool syn) {
	if (syn) synLock();
	bool found=false; 
	unsigned int i=0;
	for(i=0;i<orderList.size();i++)
	{
		if(orderList[i]->BrokerOrderSeq == orderSeq)
		{ 
			found = true;
			break;
		}
	}
	if(!found)
	{
		std::cerr <<" 请求 | 报单不存在."<< std::endl; 
		return 0;
	} 

	CSecurityFtdcInputOrderActionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);   //经纪公司代码	
	strcpy(req.InvestorID, user_id_); //投资者代码
	//strcpy(req.OrderRef, pOrderRef); //报单引用	
	//req.FrontID = frontId;           //前置编号	
	//req.SessionID = sessionId;       //会话编号
    strcpy(req.ExchangeID, orderList[i]->ExchangeID);
   // strcpy(req.OrderSysID, orderList[i]->OrderSysID); Lts中无此字段
	req.ActionFlag = SECURITY_FTDC_AF_Delete;  //操作标志 

	int ret = api_->ReqOrderAction(&req, nextRequestId());
	std::cout << " 请求 | 发送撤单..." <<((ret == 0)?"成功":"失败") << std::endl;
	wait(syn);
	return ret;
}

void LtsTrader::qrySettlementInfo(const char *broker_id, 
                                  const char *investor_id, 
                                  const char* trading_day,
                                  bool syn) {
	if (syn) synLock();
	//do nothing 
	wait(syn);
}

//-----------------------------------------------------
void LtsTrader::settlementInfoConfirm(bool syn) {
	if (syn) synLock();
	//do nothing;
	wait(syn);
}

void LtsTrader::registerFront(char *pszFrontAddress, bool syn) {
	if (syn)
		synLock();
	api_->RegisterFront(pszFrontAddress);
}

//----------------------继承自CSecurityFtdcTraderSpi的回调方法实现-------
///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void LtsTrader::OnFrontConnected() {
	std::cout << " trader front connectd..." << std::endl;
	synUnlock();
}

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
void LtsTrader::OnFrontDisconnected(int nReason) {
	std::cerr << " 响应 | 连接中断..."
		<< " reason=" << nReason << std::endl;
}

///心跳超时警告。当长时间未收到报文时，该方法被调用。
void LtsTrader::OnHeartBeatWarning(int nTimeLapse) {
	std::cerr << " 响应 | 心跳超时警告..."
		<< " TimerLapse = " << nTimeLapse << std::endl;
}

///错误应答
void LtsTrader::OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	IsErrorRspInfo(pRspInfo);
	if (bIsLast) synUnlock();
}

/// 登录请求响应
void LtsTrader::OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, 
			CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!IsErrorRspInfo(pRspInfo) && pRspUserLogin) {
		set_logined(true);
		set_front_id(pRspUserLogin->FrontID);
		set_session_id(pRspUserLogin->SessionID);
		std::cout << " 响应 | 用户登录成功...当前交易日:"
			<< pRspUserLogin->TradingDay << std::endl;
	}
	if (bIsLast) synUnlock();
}

///报单录入请求响应
void LtsTrader::OnRspOrderInsert(CSecurityFtdcInputOrderField *pInputOrder, 
			CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!IsErrorRspInfo(pRspInfo) && pInputOrder){
		std::cout << "响应 | 报单提交成功...报单引用:" 
			<< pInputOrder->OrderRef << std::endl;
	}
}

///报单操作请求响应
void LtsTrader::OnRspOrderAction(CSecurityFtdcInputOrderActionField *pInputOrderAction, 
			CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!IsErrorRspInfo(pRspInfo) && pInputOrderAction)
	{
		Order order;
        Mapping::fromLtsOrder(*pInputOrderAction, &order);
        // 撤单响应
        on_cancel_order(order);
	}
	if (bIsLast) synUnlock();
}

///请求查询合约响应
void LtsTrader::OnRspQryInstrument(CSecurityFtdcInstrumentField *pInstrument, 
			CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!IsErrorRspInfo(pRspInfo) && pInstrument)
	{
        Contract c;
        Mapping::toLtsContract(*pInstrument, &c);
        on_contract(c);
	}
	if (bIsLast) synUnlock();
}

///请求查询投资者持仓响应
void LtsTrader::OnRspQryInvestorPosition(CSecurityFtdcInvestorPositionField *pInvestorPosition,
			CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!IsErrorRspInfo(pRspInfo) && pInvestorPosition)
	{
        Position pos;
        Mapping::fromLtsPosition(*pInvestorPosition, &pos);
        on_position(pos);
	}
	if (bIsLast) synUnlock();
}

///请求查询资金账户响应
void LtsTrader::OnRspQryTradingAccount(CSecurityFtdcTradingAccountField *pTradingAccount, 
			CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!IsErrorRspInfo(pRspInfo) && pTradingAccount)
	{
        Captial cap;
        Mapping::fromLtsCaptial(*pTradingAccount, &cap);
        on_captial(cap);
	}
	if (bIsLast) synUnlock();
}

///投资者结算结果确认响应
//void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

///请求查询行情响应
void LtsTrader::OnRspQryDepthMarketData(CSecurityFtdcDepthMarketDataField *pDepthMarketData, 
			CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!IsErrorRspInfo(pRspInfo) && pDepthMarketData)
	{
        TickData tick;
        Mapping::fromLtsTick(*pDepthMarketData, &tick);
        on_tick(tick);
	}
	if (bIsLast) synUnlock();
}

///报单通知
void LtsTrader::OnRtnOrder(CSecurityFtdcOrderField *pOrder) {
/*
	CSecurityFtdcOrderField* order = new CSecurityFtdcOrderField();
	memcpy(order, pOrder, sizeof(CSecurityFtdcOrderField));
	bool founded = false;    unsigned int i = 0;
	for (i = 0; i<orderList.size(); i++){
		if (orderList[i]->BrokerOrderSeq == order->BrokerOrderSeq) {
			founded = true;    
			break;
		}
	}
	if (founded)
		orderList[i] = order;
	else
		orderList.push_back(order);
*/
    Order order;
    Mapping::fromLtsOrder(*pOrder, &order);
    //
    on_order(order);
	std::cout << " 回报 | 报单已提交...序号:" << pOrder->BrokerOrderSeq << std::endl;
}

///成交通知
void LtsTrader::OnRtnTrade(CSecurityFtdcTradeField *pTrade) {
    Transaction trans;
    Mapping::fromLtsTransaction(*pTrade, &trans);
    //
    on_transaction(trans);
    std::cout<<" Response | deal,  order id:"<<pTrade->OrderSysID<< std::endl;  // 成交后才有的字段？
    synUnlock();
}

bool LtsTrader::IsErrorRspInfo(CSecurityFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (ret){
		std::cerr << " Error: | " << pRspInfo->ErrorMsg << std::endl;
	}
	return ret;
}

} /* QuantDigger */
