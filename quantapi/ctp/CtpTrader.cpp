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
#include "CtpMapping.h" 
namespace QuantApi {

using namespace std;

// 会话参数, 在OnRspUserLogin 函数中初始化

vector<CThostFtdcOrderField*> orderList; // 已经提交的报单, 无论是否撤销
vector<CThostFtdcTradeField*> tradeList; // 已经成交的报道

CtpTrader::CtpTrader(char* trade_front) {
    LOG_ASSERT(trade_front);
    api_ = CThostFtdcTraderApi::CreateFtdcTraderApi();
    api_->RegisterSpi(this);
    locked_ = false;
    registerFront(trade_front, true);    
}

CtpTrader::~CtpTrader() {
    api_->Join();
    api_->Release();
}

void CtpTrader::registerFront(char *pszFrontAddress, bool sync) {
    api_->RegisterFront(pszFrontAddress);
	api_->Init();
	wait(sync);      // 回调在init之后才会运行！
    cerr<<"registerFront..."<<endl;
}

void CtpTrader::qrySettlementInfo(const char *broker_id, 
                                  const char *investor_id, 
                                  const char* trading_day,
                                  bool sync) {
    std::cerr<<"settle"<<std::endl;
    CThostFtdcQrySettlementInfoField pQrySettlementInfo;
    memset(&pQrySettlementInfo, 0, sizeof(pQrySettlementInfo));
    strcpy(pQrySettlementInfo.BrokerID, broker_id);
    strcpy(pQrySettlementInfo.InvestorID, investor_id);
    strcpy(pQrySettlementInfo.TradingDay, trading_day);
    api_->ReqQrySettlementInfo(&pQrySettlementInfo, nextRequestId());
    wait(sync);
}

int CtpTrader::settlementInfoConfirm(bool sync)
{
    CThostFtdcSettlementInfoConfirmField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_id_);
    strcpy(req.InvestorID, user_id_);
    int ret = api_->ReqSettlementInfoConfirm(&req, nextRequestId());
	cerr << "Sending settlement info confirm.." << ((ret == 0) ? "sucess" : "failed") << endl;
    wait(sync);
    return ret;
}


int CtpTrader::login(const LogonInfo &info,
        bool sync) {
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, info.broker_id); 
    strcpy(req.UserID, info.user_id); 
    strcpy(req.Password, info.password);
    strcpy(broker_id_, info.broker_id); 
    strcpy(user_id_, info.user_id); 
    int ret = api_->ReqUserLogin(&req, nextRequestId());
	cerr << " sending | Logining..." << ((ret == 0) ? "Sucess" : "Failed") << endl;
    wait(sync);
    settlementInfoConfirm();
    return ret;
}

int CtpTrader::logout(const LogonInfo &info, bool sync) {
    CThostFtdcUserLogoutField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, info.broker_id); 
    strcpy(req.UserID, info.user_id); 
    int ret = api_->ReqUserLogout(&req, nextRequestId());
	cerr << " sending | Logout..." << ((ret == 0) ? "Sucess" : "Failed") << endl;
    wait(sync);
    return ret;
}

int CtpTrader::order(const Order &order, bool sync) {
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));	
    strcpy(req.BrokerID, broker_id_);  //应用单元代码	
    strcpy(req.InvestorID, user_id_); //投资者代码	
    strcpy(req.InstrumentID, order.contract.code.c_str()); //合约代码	

    sprintf(req.OrderRef, "%d", order.id.init_id);//报单引用
    req.Direction = Mapping::toCtpDirection(order.direction);  //买卖方向	
    req.CombHedgeFlag[0] = Mapping::toCtpHedge(order.hedge_type);	  //组合投机套保标志	
    req.OrderPriceType = Mapping::toCtpPriceType(order.price_type); //市价或限价
    req.CombOffsetFlag[0] = Mapping::toCtpTradeSide(order.side); //组合开平标志
    req.LimitPrice = order.price;	//价格
    req.VolumeTotalOriginal = order.volume;	///数量		

    req.VolumeCondition = THOST_FTDC_VC_AV; //成交量类型:任何数量
    req.MinVolume = 1;	//最小成交量:1	
    req.ContingentCondition = THOST_FTDC_CC_Immediately;  //触发条件:立即
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;	//强平原因:非强平	
    req.IsAutoSuspend = 0;  //自动挂起标志:否	
    req.UserForceClose = 0;   //用户强评标志:否
    /// @todo 区分两者
    req.TimeCondition = THOST_FTDC_TC_GFD;  //有效期类型:当日有效
    //req.TimeCondition = THOST_FTDC_TC_IOC;//有效期类型:立即完成，否则撤销

    int ret = api_->ReqOrderInsert(&req, nextRequestId());
	std::cout << "\n=======发送下单请求,结果:"<< ret << "============" << std::endl;
    wait(sync);
    return ret;
}

int CtpTrader::reqTick(const Contract &c, bool sync)
{
    CThostFtdcQryDepthMarketDataField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.InstrumentID, c.code.c_str());//为空表示查询所有合约
    int ret = api_->ReqQryDepthMarketData(&req, nextRequestId());
	cerr << " 请求 | 发送合约报价查询..." << ((ret == 0) ? "成功" : "失败") << endl;
    wait(sync);
    return ret;
}

int CtpTrader::reqContract(Contract *c, bool sync)
{
    CThostFtdcQryInstrumentField req;
    memset(&req, 0, sizeof(req));
    // 如果为空，表示查询所有合约
    strcpy(req.InstrumentID, c->code.c_str());
    int ret = api_->ReqQryInstrument(&req, nextRequestId());
    /// @todo 多合约处理
    //    Mapping::fromCtpContract(*req, c);
    wait(sync);
    return ret;
}

int CtpTrader::reqCaptial(bool sync)
{
    CThostFtdcQryTradingAccountField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_id_);
    strcpy(req.InvestorID, user_id_);
    int ret = api_->ReqQryTradingAccount(&req, nextRequestId());
    wait(sync);
    cerr<<" 请求 | 发送资金查询..."<<((ret == 0)?"成功":"失败")<<endl;
    return ret;
}

int CtpTrader::reqPosition(const Contract &contract, bool sync)
{

    //if (sync) synLock();
    CThostFtdcQryInvestorPositionField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_id_);
    strcpy(req.InvestorID, user_id_);
    strcpy(req.InstrumentID, contract.code.c_str());	
    int ret = api_->ReqQryInvestorPosition(&req, nextRequestId());
    wait(sync);
    cerr<<" 请求 | 发送持仓查询..."<<((ret == 0)?"成功":"失败")<<endl;
    return ret;
}

int CtpTrader::cancel_order(int orderSeq, bool sync)
{
    //if (sync) synLock();

    bool found=false;
    unsigned int i=0;
    for(i=0;i<orderList.size();i++){
        if(orderList[i]->BrokerOrderSeq == orderSeq){
            found = true;
            break;
        }
    }
    if(!found) {cerr<<" 请求 | 报单不存在."<<endl; return 0;} 

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
    wait(sync);
    cerr<< " 请求 | 发送撤单..." <<((ret == 0)?"成功":"失败") << endl;
    return ret;

}

//void CtpTrader::PrintOrders(){
//    CThostFtdcOrderField* pOrder; 
//    for(unsigned int i=0; i<orderList.size(); i++){
//        pOrder = orderList[i];
//        cerr<<" 报单 | 合约:"<<pOrder->InstrumentID
//            //        <<" 方向:"<<MapDirection(pOrder->Direction,false)
//            <<" 价格:"<<pOrder->LimitPrice
//            <<" 数量:"<<pOrder->VolumeTotalOriginal
//            <<" 序号:"<<pOrder->BrokerOrderSeq 
//            <<" 报单编号:"<<pOrder->OrderSysID
//            <<" 状态:"<<pOrder->StatusMsg<<endl;
//    }
//    //  sem.sem_v();
//}
//void CtpTrader::PrintTrades(){
//    CThostFtdcTradeField* pTrade;
//    for(unsigned int i=0; i<tradeList.size(); i++){
//        pTrade = tradeList[i];
//        cerr<<" 成交 | 合约:"<< pTrade->InstrumentID 
//            //        <<" 方向:"<<MapDirection(pTrade->Direction,false)
//            <<" 价格:"<<pTrade->Price
//            <<" 数量:"<<pTrade->Volume
//            <<" 报单编号:"<<pTrade->OrderSysID
//            <<" 成交编号:"<<pTrade->TradeID<<endl;
//    }
//    //  sem.sem_v();
//}

// ---------------------- 回调函数 -----------------------------------
void CtpTrader::OnFrontConnected() {
    cout<<" trader front connectd..."<<endl;
	notify();
}

void CtpTrader::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if ( !IsErrorRspInfo(pRspInfo) && pRspUserLogin ) {  
        // 保存会话参数	
        set_logined(true);
        set_front_id(pRspUserLogin->FrontID);
        set_session_id(pRspUserLogin->SessionID);
        cerr<<" 响应 | 用户登录成功...当前交易日:"
            <<pRspUserLogin->TradingDay<<endl;     
    }
    if(bIsLast)
		notify();
}

void CtpTrader::OnRspSettlementInfoConfirm(
        CThostFtdcSettlementInfoConfirmField  *pSettlementInfoConfirm, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {	
    if( !IsErrorRspInfo(pRspInfo) && pSettlementInfoConfirm){
        cerr<<" 响应 | 结算单..."<<pSettlementInfoConfirm->InvestorID
            <<"...<"<<pSettlementInfoConfirm->ConfirmDate
            <<" "<<pSettlementInfoConfirm->ConfirmTime<<">...确认"<<endl;
        //       char a[5] = "0";
        //    ReqOrderInsert("ru1405", 's', a, 0, 1);
    }
    if(bIsLast)
		notify();
}

void CtpTrader::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{ 	
    if ( !IsErrorRspInfo(pRspInfo) &&  pInstrument){
        Contract c;
        Mapping::toCtpContract(*pInstrument, &c);
        on_contract(c);
    }
    if(bIsLast)
		notify();
}

void CtpTrader::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData,
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!IsErrorRspInfo(pRspInfo) && pDepthMarketData){
        TickData tick;
        Mapping::fromCtpTick(*pDepthMarketData, &tick);
        on_tick(tick);
    }
    if(bIsLast)
		notify();
}

void CtpTrader::OnRspQryTradingAccount(
        CThostFtdcTradingAccountField *pTradingAccount, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{ 
    if (!IsErrorRspInfo(pRspInfo) &&  pTradingAccount){
        Captial cap;
        Mapping::fromCtpCaptial(*pTradingAccount, &cap);
        on_captial(cap);
    }
    if(bIsLast)
		notify();
}

void CtpTrader::OnRspQryInvestorPosition(
        CThostFtdcInvestorPositionField *pInvestorPosition, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{ 
    if( !IsErrorRspInfo(pRspInfo) &&  pInvestorPosition ){
        Position pos;
        Mapping::fromCtpPosition(*pInvestorPosition, &pos);
        on_position(pos);
    }
    if(bIsLast)
		notify();
}

void CtpTrader::OnRspOrderAction(
        CThostFtdcInputOrderActionField *pInputOrderAction, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
    if (!IsErrorRspInfo(pRspInfo) && pInputOrderAction){
        Order order;
        Mapping::fromCtpOrder(*pInputOrderAction, &order);
        // 撤单响应
        on_cancel_order(order);
    }

    if(bIsLast)
		notify();
}

void CtpTrader::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if( !IsErrorRspInfo(pRspInfo) && pInputOrder ){
		cerr << "Response | order insert sucess, reference::" << pInputOrder->OrderRef << endl
			<< "						borkerId::" << pInputOrder->BrokerID << endl
			<< "						direction::" << pInputOrder->Direction << endl;
    }

	if (bIsLast)
		notify();
}

///报单回报
void CtpTrader::OnRtnOrder(CThostFtdcOrderField *pOrder)
{	
    Order order;
    Mapping::fromCtpOrder(*pOrder, &order);

    on_order(order);

    cerr<<" Response | order arrive exchange, order id::"<<pOrder->BrokerOrderSeq<<endl
		<< "							borkerId::" << pOrder->BrokerID << endl
		<< "							direction::" << pOrder->Direction << endl
		<< "							reference::" << pOrder->OrderRef << endl;

	notify();
}

///成交通知
void CtpTrader::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    Transaction trans;
    Mapping::fromCtpTransaction(*pTrade, &trans);
    //
    on_transaction(trans);
    cerr<<" Response | deal,  order id:"<<pTrade->OrderSysID<<endl;  // 成交后才有的字段？
	notify();
}

void CtpTrader::OnFrontDisconnected(int nReason)
{
    // 系统会自动重连。
    cerr<<" 响应 | 连接中断..." 
        << " reason=" << nReason << endl;
}

void CtpTrader::OnHeartBeatWarning(int nTimeLapse)
{
    // 长时间没收到报文，会被调用。
    cerr<<" 响应 | 心跳超时警告..." 
        << " TimerLapse = " << nTimeLapse << endl;
}

void CtpTrader::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    IsErrorRspInfo(pRspInfo);
    if(bIsLast)
		notify();
}

bool CtpTrader::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
    // 如果ErrorID != 0, 说明收到了错误的响应
    bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
    if (ret){
        cerr<<" Error: | "<<pRspInfo->ErrorMsg<<endl;
    }
    return ret;
}

} /* QuantApi */
