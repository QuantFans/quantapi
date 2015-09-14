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

// �Ự����, ��OnRspUserLogin �����г�ʼ��

vector<CThostFtdcOrderField*> orderList; // �Ѿ��ύ�ı���, �����Ƿ���
vector<CThostFtdcTradeField*> tradeList; // �Ѿ��ɽ��ı���

int CtpTrader::request_id_ = 0;

CtpTrader::CtpTrader(char* trade_front):logger(Logger::getRootLogger()) {
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
    LOG4CXX_INFO(logger, std::string("registerFront:")+pszFrontAddress);
    api_->RegisterFront(pszFrontAddress);
	api_->Init();
	wait(sync);      // �ص���init֮��Ż����У�
}

void CtpTrader::qrySettlementInfo(const char *broker_id, 
                                  const char *investor_id, 
                                  const char* trading_day,
                                  bool sync) {
    CThostFtdcQrySettlementInfoField pQrySettlementInfo;
    memset(&pQrySettlementInfo, 0, sizeof(pQrySettlementInfo));
    strcpy(pQrySettlementInfo.BrokerID, broker_id);
    strcpy(pQrySettlementInfo.InvestorID, investor_id);
    strcpy(pQrySettlementInfo.TradingDay, trading_day);
    api_->ReqQrySettlementInfo(&pQrySettlementInfo, currentRequestId());
    wait(sync);
}

int CtpTrader::settlementInfoConfirm(const char* brokerId,
                                     const char* userId,
                                     const int   requestId,
                                     bool sync)
{
    CThostFtdcSettlementInfoConfirmField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, brokerId);
    strcpy(req.InvestorID, userId);
    int ret = api_->ReqSettlementInfoConfirm(&req, requestId);
	cerr << "Sending settlement info confirm.." << ((ret == 0) ? "sucess" : "failed") << endl;
    if (ret == 0)
    {
        LOG4CXX_INFO(logger, std::string("Sending settlement info confirm..success,id:")+userId);
    }
    else
    {
        LOG4CXX_ERROR(logger, std::string("Sending settlement info confirm..fialed,id:")+userId);
    }
    //wait(sync);
    return ret;
}


int CtpTrader::login(const LogonInfo &info,
        bool sync) {
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strcpy(broker_id_, info.broker_id);
    strcpy(user_id_, info.user_id);
    strcpy(req.BrokerID, info.broker_id); 
    strcpy(req.UserID, info.user_id); 
    strcpy(req.Password, info.password);
    int ret = api_->ReqUserLogin(&req, currentRequestId());
    if (ret == 0)
    {
        LOG4CXX_INFO(logger, std::string("Sending login request succ,id:")+info.user_id);
    }
    else
    {
        LOG4CXX_ERROR(logger, std::string("Sending login request fialed,id:")+info.user_id);
        return ret;
    }
    wait(sync);
    return ret;
}

int CtpTrader::logout(bool sync) {
    CThostFtdcUserLogoutField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_id_); 
    strcpy(req.UserID, user_id_); 
    int ret = api_->ReqUserLogout(&req, currentRequestId());
    if (ret == 0)
    {
        LOG4CXX_INFO(logger, std::string("Sending logout request succ,id:")+user_id_);
    }
    else
    {
        LOG4CXX_ERROR(logger, std::string("Sending lougut request fialed,id:")+user_id_);
        return ret;
    }
    wait(sync);
    return ret;
}

int CtpTrader::order(const Order &order, bool sync) 
{
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));	
    strcpy(req.BrokerID, broker_id_);  //Ӧ�õ�Ԫ����	
    strcpy(req.InvestorID, user_id_); //Ͷ���ߴ���	
    strcpy(req.InstrumentID, order.contract.code.c_str()); //��Լ����	

    sprintf(req.OrderRef, "%d", order.id.init_id);//��������
    req.Direction = Mapping::toCtpDirection(order.direction);  //��������	
    req.CombHedgeFlag[0] = Mapping::toCtpHedge(order.hedge_type);	  //���Ͷ���ױ���־	
    req.OrderPriceType = Mapping::toCtpPriceType(order.price_type); //�мۻ��޼�
    req.CombOffsetFlag[0] = Mapping::toCtpTradeSide(order.side); //��Ͽ�ƽ��־
    req.LimitPrice = order.price;	//�۸�
    req.VolumeTotalOriginal = order.volume;	///����		

    req.VolumeCondition = THOST_FTDC_VC_AV; //�ɽ�������:�κ�����
    req.MinVolume = 1;	//��С�ɽ���:1	
    req.ContingentCondition = THOST_FTDC_CC_Immediately;  //��������:����
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;	//ǿƽԭ��:��ǿƽ	
    req.IsAutoSuspend = 0;  //�Զ������־:��	
    req.UserForceClose = 0;   //�û�ǿ����־:��
    /// @todo ��������
    req.TimeCondition = THOST_FTDC_TC_GFD;  //��Ч������:������Ч
    //req.TimeCondition = THOST_FTDC_TC_IOC;//��Ч������:������ɣ�������

    int ret = api_->ReqOrderInsert(&req, currentRequestId());
    if (ret == 0)
    {
        LOG4CXX_INFO(logger, std::string("Sending order insert..success,id:")+user_id_);
    }
    else
    {
        LOG4CXX_ERROR(logger, std::string("Sending order insert..fialed,id:")+user_id_);
        return ret;
    }
    wait(sync);
    return ret;
}

int CtpTrader::reqTick(const Contract &c, bool sync)
{
    CThostFtdcQryDepthMarketDataField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.InstrumentID, c.code.c_str());//Ϊ�ձ�ʾ��ѯ���к�Լ
    int ret = api_->ReqQryDepthMarketData(&req, currentRequestId());
    if (ret == 0)
    {
        LOG4CXX_INFO(logger, "Sending contract tick request..success");
    }
    else
    {
        LOG4CXX_ERROR(logger, "Sending contract tick request..fialed");
        return ret;
    }
    wait(sync);
    return ret;
}

int CtpTrader::reqContract(Contract *c, bool sync)
{
    CThostFtdcQryInstrumentField req;
    memset(&req, 0, sizeof(req));
    // ���Ϊ�գ���ʾ��ѯ���к�Լ
    strcpy(req.InstrumentID, c->code.c_str());
    int ret = api_->ReqQryInstrument(&req, currentRequestId());
    /// @todo ���Լ����
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
    int ret = api_->ReqQryTradingAccount(&req, currentRequestId());
    if (ret == 0)
    {
        LOG4CXX_INFO(logger, std::string("Sending req account..success,id:")+user_id_);
    }
    else
    {
        LOG4CXX_ERROR(logger, std::string("Sending req account..fialed,id:")+user_id_);
        return ret;
    }
    wait(sync);
    return ret;
}

int CtpTrader::reqPosition(const Contract &contract, bool sync)
{
    CThostFtdcQryInvestorPositionField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_id_);
    strcpy(req.InvestorID, user_id_);
    strcpy(req.InstrumentID, contract.code.c_str());	
    int ret = api_->ReqQryInvestorPosition(&req, currentRequestId());
    if (ret == 0)
    {
        LOG4CXX_INFO(logger, std::string("Sending req Position..success,id:")+user_id_);
    }
    else
    {
        LOG4CXX_ERROR(logger, std::string("Sending req Position..fialed,id:")+user_id_);
        return ret;
    }
    wait(sync);
    return ret;
}

int CtpTrader::cancel_order(/*const char* brokerId, 
                            const char* userId,*/
                            const Order& order, 
                            bool sync)
{
    CThostFtdcInputOrderActionField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_id_);   //���͹�˾����	
    strcpy(req.InvestorID, user_id_); //Ͷ���ߴ���
    //strcpy(req.OrderRef, pOrderRef); //��������	
    //req.FrontID = frontId;           //ǰ�ñ��	
    //req.SessionID = sessionId;       //�Ự���
    strcpy(req.ExchangeID, mapFromQDExchType(order.contract.exch_type).c_str());
    sprintf(req.OrderSysID, "%d", order.id.order_id );
    //strcpy(req.OrderSysID, order.id.order_id);
    req.ActionFlag = THOST_FTDC_AF_Delete;  //������־ 

    int ret = api_->ReqOrderAction(&req, currentRequestId());
    if (ret == 0)
    {
        LOG4CXX_INFO(logger, std::string("Sending order cancel..success,id:")+user_id_);
    }
    else
    {
        LOG4CXX_ERROR(logger, std::string("Sending order cancel..fialed,id:")+user_id_);
        return ret;
    }
    wait(sync);
    return ret;

}

//void CtpTrader::PrintOrders(){
//    CThostFtdcOrderField* pOrder; 
//    for(unsigned int i=0; i<orderList.size(); i++){
//        pOrder = orderList[i];
//        cerr<<" ���� | ��Լ:"<<pOrder->InstrumentID
//            //        <<" ����:"<<MapDirection(pOrder->Direction,false)
//            <<" �۸�:"<<pOrder->LimitPrice
//            <<" ����:"<<pOrder->VolumeTotalOriginal
//            <<" ���:"<<pOrder->BrokerOrderSeq 
//            <<" �������:"<<pOrder->OrderSysID
//            <<" ״̬:"<<pOrder->StatusMsg<<endl;
//    }
//    //  sem.sem_v();
//}
//void CtpTrader::PrintTrades(){
//    CThostFtdcTradeField* pTrade;
//    for(unsigned int i=0; i<tradeList.size(); i++){
//        pTrade = tradeList[i];
//        cerr<<" �ɽ� | ��Լ:"<< pTrade->InstrumentID 
//            //        <<" ����:"<<MapDirection(pTrade->Direction,false)
//            <<" �۸�:"<<pTrade->Price
//            <<" ����:"<<pTrade->Volume
//            <<" �������:"<<pTrade->OrderSysID
//            <<" �ɽ����:"<<pTrade->TradeID<<endl;
//    }
//    //  sem.sem_v();
//}

// ---------------------- �ص����� -----------------------------------
void CtpTrader::OnFrontConnected() {
    LOG4CXX_INFO(logger, "trader front connectd...");
	notify();
}

void CtpTrader::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if ( !IsErrorRspInfo(pRspInfo) && pRspUserLogin && bIsLast) {  
        // ����Ự����	
        set_logined(true);
        set_front_id(pRspUserLogin->FrontID);
        set_session_id(pRspUserLogin->SessionID);
        LOG4CXX_INFO(logger, std::string("OnResponse | UserLogin Succ...TradingDate")+pRspUserLogin->TradingDay);
        
        settlementInfoConfirm(pRspUserLogin->BrokerID, pRspUserLogin->UserID,
                nRequestID, false);
    }
    else if (bIsLast){
        OperateStatus ops;
        ops.brokerId = pRspUserLogin->BrokerID;
        ops.userId = pRspUserLogin->UserID;
        ops.status = pRspInfo->ErrorID;
        ops.errmsg = pRspInfo->ErrorMsg;
        ops.requestId = requestId2str(nRequestID);
        on_login(ops);
    }
}

void CtpTrader::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    if (bIsLast){
        notify();
        OperateStatus ops;
        ops.brokerId = pUserLogout->BrokerID;
        ops.userId = pUserLogout->UserID;
        ops.status = pRspInfo->ErrorID;
        ops.errmsg = pRspInfo->ErrorMsg;
        ops.requestId = requestId2str(nRequestID);
        on_logout(ops);
    }
}

void CtpTrader::OnRspSettlementInfoConfirm(
        CThostFtdcSettlementInfoConfirmField  *pSettlementInfoConfirm, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {	
    if( !IsErrorRspInfo(pRspInfo) && pSettlementInfoConfirm){
        LOG4CXX_INFO(logger, std::string("OnResponse SettlementInfo id:")
                + pSettlementInfoConfirm->InvestorID + ",time:"
                + pSettlementInfoConfirm->ConfirmDate + " " 
                + pSettlementInfoConfirm->ConfirmTime);
    }
    if(bIsLast){
        OperateStatus ops;
        ops.brokerId = pSettlementInfoConfirm->BrokerID;
        ops.userId = pSettlementInfoConfirm->InvestorID;
        ops.status = pRspInfo->ErrorID;
        ops.errmsg = pRspInfo->ErrorMsg;
        ops.requestId = requestId2str(nRequestID);
        on_login(ops);
		notify();
    }
}

void CtpTrader::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{ 	
    if ( !IsErrorRspInfo(pRspInfo) &&  pInstrument){
        Contract c;
        Mapping::toCtpContract(*pInstrument, &c);
        on_contract(c);
    }
    else {
        LOG4CXX_ERROR(logger, "OnRsp | QryInstrument faild");
    }
    if(bIsLast){
		notify();
    }
}

void CtpTrader::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData,
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    TickData tick;
    if (!IsErrorRspInfo(pRspInfo) && pDepthMarketData){
        Mapping::fromCtpTick(*pDepthMarketData, &tick);
    }
    if(bIsLast){
        OperateStatus ops;
        ops.status = pRspInfo->ErrorID;
        ops.errmsg = pRspInfo->ErrorMsg;
        ops.requestId = requestId2str(nRequestID);
        on_tick(ops,tick);
		notify();
    }
}

void CtpTrader::OnRspQryTradingAccount(
        CThostFtdcTradingAccountField *pTradingAccount, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{ 
    Captial cap;
    if (!IsErrorRspInfo(pRspInfo) &&  pTradingAccount){
        Mapping::fromCtpCaptial(*pTradingAccount, &cap);
    }
    if(bIsLast){
        OperateStatus ops;
        ops.brokerId = pTradingAccount->BrokerID;
        ops.userId = pTradingAccount->AccountID;
        if (pRspInfo){
            ops.status = pRspInfo->ErrorID;
            ops.errmsg = pRspInfo->ErrorMsg;
        }
        else
        {
            ops.status = 0;
        }
        ops.requestId = requestId2str(nRequestID);
        on_captial(ops,cap);
		notify();
    }
}

void CtpTrader::OnRspQryInvestorPosition(
        CThostFtdcInvestorPositionField *pInvestorPosition, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{ 
    Position pos;
    pos.islast = bIsLast;
    if( !IsErrorRspInfo(pRspInfo) &&  pInvestorPosition ){
        Mapping::fromCtpPosition(*pInvestorPosition, &pos);
    }
    OperateStatus ops;
    ops.brokerId = pInvestorPosition->BrokerID;
    ops.userId = pInvestorPosition->InvestorID;
    ops.status = pRspInfo->ErrorID;
    ops.errmsg = pRspInfo->ErrorMsg;
    ops.requestId = requestId2str(nRequestID);

    if(bIsLast){
        on_position(ops, pos);
		notify();
    }
}

//����ʧ�ܲŻ�ִ�дλص�
void CtpTrader::OnRspOrderAction(
        CThostFtdcInputOrderActionField *pInputOrderAction, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
    Order order;
    if (!IsErrorRspInfo(pRspInfo) && pInputOrderAction){
        Mapping::fromCtpOrder(*pInputOrderAction, &order);
    }

    OperateStatus ops;
    ops.status = pRspInfo->ErrorID;
    ops.errmsg = pRspInfo->ErrorMsg;
    ops.requestId = requestId2str(nRequestID);
    
    if(bIsLast)
    {
        // ������Ӧ
        on_cancel_order(ops, order);
		notify();
    }
}

//����¼��ʧ�ܲŻ�ִ�д˻ص�
void CtpTrader::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Order order;
    if( !IsErrorRspInfo(pRspInfo) && pInputOrder ){
		cerr << "Response | order insert sucess, reference::" << pInputOrder->OrderRef << endl
			<< "						borkerId::" << pInputOrder->BrokerID << endl
			<< "						direction::" << pInputOrder->Direction << endl;
    }
    OperateStatus ops;
    ops.status = pRspInfo->ErrorID;
    ops.errmsg = pRspInfo->ErrorMsg;
    ops.requestId = requestId2str(nRequestID);
	
    if (bIsLast){
        on_order(ops, order);
		notify();
    }
}

///�����ر����������ر�
void CtpTrader::OnRtnOrder(CThostFtdcOrderField *pOrder)
{	
    std::cout << "Order Rtn" << std::endl;
    cerr<<" Response | order arrive exchange"<< endl
        << "--------order id::"<<pOrder->BrokerOrderSeq<<endl
		<< "--------borkerId::" << pOrder->BrokerID << endl
		<< "-------direction::" << pOrder->Direction << endl
		<< "-------reference::" << pOrder->OrderRef << endl
        << "----------userid::" << pOrder->UserID << endl
        << "-----investor_id::" << pOrder->InvestorID << endl
        << "------OrderSysID::" << pOrder->OrderSysID << endl
        << "------InsertDate::" << pOrder->InsertDate << endl
        << "----InstrumentID::" << pOrder->InstrumentID << endl
        << "------TradingDay::" << pOrder->TradingDay << endl
        << "-----OrderStatus::" << pOrder->OrderStatus << endl
        << "========================================================"<<endl ;
    
    Order order;
    Mapping::fromCtpOrder(*pOrder, &order);
    OperateStatus op;
    op.status = 0;
    op.requestId = "" ;

    if (pOrder->OrderStatus == 'a' )
        return;

    else if (pOrder->OrderStatus == THOST_FTDC_OST_NoTradeQueueing )
        on_order(op, order);
    else if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled)
        on_cancel_order(op, order);

}

///�ɽ�֪ͨ
void CtpTrader::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    Transaction trans;
    Mapping::fromCtpTransaction(*pTrade, &trans);
    //
    on_transaction(trans);
    cerr<<" Response | deal,  order id:"<<pTrade->OrderSysID<<endl;  // �ɽ�����е��ֶΣ�
	notify();
}

void CtpTrader::OnFrontDisconnected(int nReason)
{
    // ϵͳ���Զ�������
    cerr<<" OnRsponse | disconnected..." 
        << " reason=" << nReason << endl;
}

void CtpTrader::OnHeartBeatWarning(int nTimeLapse)
{
    // ��ʱ��û�յ����ģ��ᱻ���á�
    cerr<<" OnRsponse | Missing heartBeat Warning..." 
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
    // ���ErrorID != 0, ˵���յ��˴������Ӧ
    bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
    if (ret){
        
        cerr<<" Error: | ErrorID = " << pRspInfo->ErrorID << ", ErrorMsg = " <<pRspInfo->ErrorMsg<<endl;
    }
    return ret;
}

} /* QuantApi */
