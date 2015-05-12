/**
 * @file ctptrader.cpp
 * @brief 
 * @author wdj
 * @version 0.1
 * @date 2014-04-09
 */

#include "CtpTrader.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../util/log_assert.h"
#include "CtpTraderCallBack.h"
namespace QuantDigger {

using namespace std;

// 会话参数, 在OnRspUserLogin 函数中初始化

vector<CThostFtdcOrderField*> orderList; // 已经提交的报单, 无论是否撤销
vector<CThostFtdcTradeField*> tradeList; // 已经成交的报道

char MapDirection(char src, bool toOrig);
char MapOffset(char src, bool toOrig);
    
CtpTrader::CtpTrader(char* trade_front, CtpTraderCallBack *cbk_object) {
    LOG_ASSERT(trade_front && cbk_object);
    spi_ = cbk_object;
    api_ = CThostFtdcTraderApi::CreateFtdcTraderApi();
    api_->RegisterSpi(spi_);
    spi_->set_trader(this);
    locked_ = false;
    registerFront(trade_front, true);
    init();
    wait(true);      // 回调在init之后才会运行！
}

CtpTrader::~CtpTrader() {
    join();
    release();
}

void CtpTrader::registerFront(char *pszFrontAddress, bool syn) {
    if (syn) synLock();
    RegisterFront(pszFrontAddress);
}

void CtpTrader::login(const char *broker_id,
                      const char *user_id,
                      const char *password, bool syn) {
    if (syn) synLock();
    ReqUserLogin(broker_id, user_id, password);
    wait(syn);
}

void CtpTrader::logout(const char *broker_id, const char *user_id, bool syn) {
    if (syn) synLock();
    ReqUserLogout(broker_id, user_id);
    wait(syn);
}

void CtpTrader::settlementInfoConfirm(bool syn)
{
    if (syn) synLock();
    ReqSettlementInfoConfirm();
    wait(syn);
}

void CtpTrader::qryInstrument(const Contract &c, bool syn)
{
    if (syn) synLock();
    ReqQryInstrument(c.code.c_str());
    wait(syn);
}

void CtpTrader::qryDepthMarketData(const Contract &c, bool syn)
{
    if (syn) synLock();
    ReqQryDepthMarketData(c.code.c_str());
    wait(syn);
}

void CtpTrader::qryTradingAccount(bool syn)
{
    if (syn) synLock();
    ReqQryTradingAccount();
    wait(syn);
}


void CtpTrader::qryInvestorPosition(const char *instId, bool syn)
{
    if (syn) synLock();
    ReqQryInvestorPosition(instId);
    wait(syn);
}

void CtpTrader::orderInsert(const char *instId, 
                            char dir, 
                            const char *kpp, 
                            double price,   
                            int vol,
                            bool syn) {
    if (syn) synLock();
    ReqOrderInsert(instId, dir, kpp, price, vol);
    wait(syn);
}

void CtpTrader::orderAction(int orderSeq, bool syn)
{
    if (syn) synLock();
    ReqOrderAction(orderSeq);
    wait(syn);
}

void CtpTrader::qrySettlementInfo(const char *broker_id, 
                                  const char *investor_id, 
                                  const char* trading_day,
                                  bool syn) {
    if (syn) synLock();
    ReqQrySettlementInfo(broker_id, investor_id, trading_day);
    wait(syn);
}

// ---------------------------------------------------------------------------------------
void CtpTrader::ReqUserLogin(const char *broker_id, const char* user_id, const char *password)
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id); 
	strcpy(req.UserID, user_id); 
	strcpy(req.Password, password);
    strcpy(broker_id_, broker_id); 
    strcpy(user_id_, user_id); 
	int ret = api_->ReqUserLogin(&req, nextRequestId());
    cerr<<" sending | Logining..."<<((ret == 0) ? "Sucess" :"Failed") << endl;	
}

void CtpTrader::ReqUserLogout(const char *broker_id, const char *user_id) {
    CThostFtdcUserLogoutField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id); 
	strcpy(req.UserID, user_id); 
	int ret = api_->ReqUserLogout(&req, nextRequestId());
    cerr<<" sending | 窟僕曜竃..."<<((ret == 0) ? "撹孔" :"払移") << endl;	
}

void CtpTrader::ReqSettlementInfoConfirm()
{
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);
	strcpy(req.InvestorID, user_id_);
	int ret = api_->ReqSettlementInfoConfirm(&req, nextRequestId());
	cerr<<" 请求 | 发送结算单确认..."<<((ret == 0)?"成功":"失败")<<endl;
}

void CtpTrader::ReqQryInstrument(const char *instId)
{
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
    strcpy(req.InstrumentID, instId);//为空表示查询所有合约
	int ret = api_->ReqQryInstrument(&req, nextRequestId());
	cerr<<" 请求 | 发送合约查询..."<<((ret == 0)?"成功":"失败")<<endl;
    cerr<<ret<<endl;
}

void CtpTrader::ReqQryDepthMarketData(const char *instId)
{
	CThostFtdcQryDepthMarketDataField req;
	memset(&req, 0, sizeof(req));
    strcpy(req.InstrumentID, instId);//为空表示查询所有合约
	int ret = api_->ReqQryDepthMarketData(&req, nextRequestId());
	cerr<<" 请求 | 发送合约报价查询..."<<((ret == 0)?"成功":"失败")<<endl;
}

void CtpTrader::ReqQryTradingAccount()
{
	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);
	strcpy(req.InvestorID, user_id_);
	int ret = api_->ReqQryTradingAccount(&req, nextRequestId());
	cerr<<" 请求 | 发送资金查询..."<<((ret == 0)?"成功":"失败")<<endl;

}

void CtpTrader::ReqQryInvestorPosition(const char *instId)
{
	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);
	strcpy(req.InvestorID, user_id_);
	strcpy(req.InstrumentID, instId);	
	int ret = api_->ReqQryInvestorPosition(&req, nextRequestId());
	cerr<<" 请求 | 发送持仓查询..."<<((ret == 0)?"成功":"失败")<<endl;
}

void CtpTrader::ReqOrderInsert(const char *instId, 
                               char dir, 
                               const char *kpp, 
                               double price,   
                               int vol) {
	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));	
	strcpy(req.BrokerID, broker_id_);  //应用单元代码	
	strcpy(req.InvestorID, user_id_); //投资者代码	
	strcpy(req.InstrumentID, instId); //合约代码	

//	strcpy(req.OrderRef, order_ref_);  //报单引用
//    int nextOrderRef = atoi(order_ref_);
//    sprintf(order_ref_, "%d", ++nextOrderRef);
  
    req.LimitPrice = price;	//价格
    if(0==req.LimitPrice){
        req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;//价格类型=市价
        req.TimeCondition = THOST_FTDC_TC_IOC;//有效期类型:立即完成，否则撤销
//        req.TimeCondition = THOST_FTDC_TC_GFD;  //有效期类型:当日有效
    }else{
        req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;//价格类型=限价	
        req.TimeCondition = THOST_FTDC_TC_GFD;  //有效期类型:当日有效
    }
    req.Direction = MapDirection(dir,true);  //买卖方向	
	req.CombOffsetFlag[0] = MapOffset(kpp[0],true); //组合开平标志:开仓
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;	  //组合投机套保标志	
	req.VolumeTotalOriginal = vol;	///数量		
	req.VolumeCondition = THOST_FTDC_VC_AV; //成交量类型:任何数量
	req.MinVolume = 1;	//最小成交量:1	
	req.ContingentCondition = THOST_FTDC_CC_Immediately;  //触发条件:立即
	
  //TThostFtdcPriceType	StopPrice;  //止损价
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;	//强平原因:非强平	
	req.IsAutoSuspend = 0;  //自动挂起标志:否	
	req.UserForceClose = 0;   //用户强评标志:否

	int ret = api_->ReqOrderInsert(&req, nextRequestId());
	cerr<<" 请求 | 发送报单..."<<((ret == 0)?"成功":"失败")<< endl;
}

void CtpTrader::ReqOrderAction(int orderSeq)
{
  bool found=false; unsigned int i=0;
  for(i=0;i<orderList.size();i++){
    if(orderList[i]->BrokerOrderSeq == orderSeq){ found = true; break;}
  }
  if(!found){cerr<<" 请求 | 报单不存在."<<endl; return;} 

	CThostFtdcInputOrderActionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);   //经纪公司代码	
	strcpy(req.InvestorID, user_id_); //投资者代码
	//strcpy(req.OrderRef, pOrderRef); //报单引用	
	//req.FrontID = frontId;           //前置编号	
	//req.SessionID = sessionId;       //会话编号
    strcpy(req.ExchangeID, orderList[i]->ExchangeID);
    strcpy(req.OrderSysID, orderList[i]->OrderSysID);
	req.ActionFlag = THOST_FTDC_AF_Delete;  //操作标志 

	int ret = api_->ReqOrderAction(&req, nextRequestId());
	cerr<< " 请求 | 发送撤单..." <<((ret == 0)?"成功":"失败") << endl;
}

void CtpTrader::PrintOrders(){
  CThostFtdcOrderField* pOrder; 
  for(unsigned int i=0; i<orderList.size(); i++){
    pOrder = orderList[i];
    cerr<<" 报单 | 合约:"<<pOrder->InstrumentID
        <<" 方向:"<<MapDirection(pOrder->Direction,false)
        <<" 开平:"<<MapOffset(pOrder->CombOffsetFlag[0],false)
        <<" 价格:"<<pOrder->LimitPrice
        <<" 数量:"<<pOrder->VolumeTotalOriginal
        <<" 序号:"<<pOrder->BrokerOrderSeq 
        <<" 报单编号:"<<pOrder->OrderSysID
        <<" 状态:"<<pOrder->StatusMsg<<endl;
  }
//  sem.sem_v();
}
void CtpTrader::PrintTrades(){
  CThostFtdcTradeField* pTrade;
  for(unsigned int i=0; i<tradeList.size(); i++){
    pTrade = tradeList[i];
    cerr<<" 成交 | 合约:"<< pTrade->InstrumentID 
        <<" 方向:"<<MapDirection(pTrade->Direction,false)
        <<" 开平:"<<MapOffset(pTrade->OffsetFlag,false) 
        <<" 价格:"<<pTrade->Price
        <<" 数量:"<<pTrade->Volume
        <<" 报单编号:"<<pTrade->OrderSysID
        <<" 成交编号:"<<pTrade->TradeID<<endl;
  }
//  sem.sem_v();
}


void CtpTrader::ReqQrySettlementInfo(const char *broker_id, 
                                     const char *investor_id, 
                                     const char* trading_day) {
    std::cerr<<"settle"<<std::endl;
    CThostFtdcQrySettlementInfoField pQrySettlementInfo;
	memset(&pQrySettlementInfo, 0, sizeof(pQrySettlementInfo));
    strcpy(pQrySettlementInfo.BrokerID, broker_id);
    strcpy(pQrySettlementInfo.InvestorID, investor_id);
    strcpy(pQrySettlementInfo.TradingDay, trading_day);
    api_->ReqQrySettlementInfo(&pQrySettlementInfo, nextRequestId());
}


void CtpTrader::RegisterFront(char *pszFrontAddress) {
    api_->RegisterFront(pszFrontAddress);
    cerr<<"銭俊住叟念崔..."<<endl;
}

char MapDirection(char src, bool toOrig=true){
  if(toOrig){
    if('b'==src||'B'==src){src='0';}else if('s'==src||'S'==src){src='1';}
  }else{
    if('0'==src){src='B';}else if('1'==src){src='S';}
  }
  return src;
}
char MapOffset(char src, bool toOrig=true){
  if(toOrig){
    if('o'==src||'O'==src){src='0';}
    else if('c'==src||'C'==src){src='1';}       ///< 平昨 
    else if('j'==src||'J'==src){src='3';}       ///< 平今
  }else{
    if('0'==src){src='O';}
    else if('1'==src){src='C';}
    else if('3'==src){src='J';}
  }
  return src;
}

} /* QuantDigger */
