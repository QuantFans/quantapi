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
	wait(sync);      // �ص���init֮��Ż����У�
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

    int ret = api_->ReqOrderInsert(&req, nextRequestId());
	std::cout << "\n=======�����µ�����,���:"<< ret << "============" << std::endl;
    wait(sync);
    return ret;
}

int CtpTrader::reqTick(const Contract &c, bool sync)
{
    CThostFtdcQryDepthMarketDataField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.InstrumentID, c.code.c_str());//Ϊ�ձ�ʾ��ѯ���к�Լ
    int ret = api_->ReqQryDepthMarketData(&req, nextRequestId());
	cerr << " ���� | ���ͺ�Լ���۲�ѯ..." << ((ret == 0) ? "�ɹ�" : "ʧ��") << endl;
    wait(sync);
    return ret;
}

int CtpTrader::reqContract(Contract *c, bool sync)
{
    CThostFtdcQryInstrumentField req;
    memset(&req, 0, sizeof(req));
    // ���Ϊ�գ���ʾ��ѯ���к�Լ
    strcpy(req.InstrumentID, c->code.c_str());
    int ret = api_->ReqQryInstrument(&req, nextRequestId());
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
    int ret = api_->ReqQryTradingAccount(&req, nextRequestId());
    wait(sync);
    cerr<<" ���� | �����ʽ��ѯ..."<<((ret == 0)?"�ɹ�":"ʧ��")<<endl;
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
    cerr<<" ���� | ���ͳֲֲ�ѯ..."<<((ret == 0)?"�ɹ�":"ʧ��")<<endl;
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
    if(!found) {cerr<<" ���� | ����������."<<endl; return 0;} 

    CThostFtdcInputOrderActionField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_id_);   //���͹�˾����	
    strcpy(req.InvestorID, user_id_); //Ͷ���ߴ���
    //strcpy(req.OrderRef, pOrderRef); //��������	
    //req.FrontID = frontId;           //ǰ�ñ��	
    //req.SessionID = sessionId;       //�Ự���
    strcpy(req.ExchangeID, orderList[i]->ExchangeID);
    strcpy(req.OrderSysID, orderList[i]->OrderSysID);
    req.ActionFlag = THOST_FTDC_AF_Delete;  //������־ 

    int ret = api_->ReqOrderAction(&req, nextRequestId());
    wait(sync);
    cerr<< " ���� | ���ͳ���..." <<((ret == 0)?"�ɹ�":"ʧ��") << endl;
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
    cout<<" trader front connectd..."<<endl;
	notify();
}

void CtpTrader::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if ( !IsErrorRspInfo(pRspInfo) && pRspUserLogin ) {  
        // ����Ự����	
        set_logined(true);
        set_front_id(pRspUserLogin->FrontID);
        set_session_id(pRspUserLogin->SessionID);
        cerr<<" ��Ӧ | �û���¼�ɹ�...��ǰ������:"
            <<pRspUserLogin->TradingDay<<endl;     
    }
    if(bIsLast)
		notify();
}

void CtpTrader::OnRspSettlementInfoConfirm(
        CThostFtdcSettlementInfoConfirmField  *pSettlementInfoConfirm, 
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {	
    if( !IsErrorRspInfo(pRspInfo) && pSettlementInfoConfirm){
        cerr<<" ��Ӧ | ���㵥..."<<pSettlementInfoConfirm->InvestorID
            <<"...<"<<pSettlementInfoConfirm->ConfirmDate
            <<" "<<pSettlementInfoConfirm->ConfirmTime<<">...ȷ��"<<endl;
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
        // ������Ӧ
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

///�����ر�
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
    cerr<<" ��Ӧ | �����ж�..." 
        << " reason=" << nReason << endl;
}

void CtpTrader::OnHeartBeatWarning(int nTimeLapse)
{
    // ��ʱ��û�յ����ģ��ᱻ���á�
    cerr<<" ��Ӧ | ������ʱ����..." 
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
        cerr<<" Error: | "<<pRspInfo->ErrorMsg<<endl;
    }
    return ret;
}

} /* QuantApi */
