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

char MapOffset(char src, bool toOrig);
    
CtpTrader::CtpTrader(char* trade_front) {
    LOG_ASSERT(trade_front);
    api_ = CThostFtdcTraderApi::CreateFtdcTraderApi();
    api_->RegisterSpi(this);
    locked_ = false;
    registerFront(trade_front, true);
    api_->Init();
    wait(true);      // �ص���init֮��Ż����У�
}

CtpTrader::~CtpTrader() {
    api_->Join();
    api_->Release();
}

void CtpTrader::registerFront(char *pszFrontAddress, bool syn) {
    if (syn) synLock();
    RegisterFront(pszFrontAddress);
}

int CtpTrader::login(const LogonInfo &info,
                      bool syn) {
    if (syn) synLock();
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, info.broker_id); 
	strcpy(req.UserID, info.user_id); 
	strcpy(req.Password, info.password);
    strcpy(broker_id_, info.broker_id); 
    strcpy(user_id_, info.user_id); 
	int ret = api_->ReqUserLogin(&req, nextRequestId());
    wait(syn);
    settlementInfoConfirm();
    cerr<<" sending | Logining..."<<((ret == 0) ? "Sucess" :"Failed") << endl;	
    return ret;
}

int CtpTrader::logout(const LogonInfo &info, bool syn) {
    if (syn) synLock();
    CThostFtdcUserLogoutField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, info.broker_id); 
	strcpy(req.UserID, info.user_id); 
	int ret = api_->ReqUserLogout(&req, nextRequestId());
    wait(syn);
    cerr<<" sending | �߃W�׸Y..."<<((ret == 0) ? "���" :"�B��") << endl;	
    return ret;
}

void CtpTrader::settlementInfoConfirm(bool syn)
{
    if (syn) synLock();
    ReqSettlementInfoConfirm();
    wait(syn);
}

int CtpTrader::order(const Order &order, bool syn) {
    if (syn) synLock();
	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));	
	strcpy(req.BrokerID, broker_id_);  //Ӧ�õ�Ԫ����	
	strcpy(req.InvestorID, user_id_); //Ͷ���ߴ���	
	strcpy(req.InstrumentID, order.contract.code.c_str()); //��Լ����	

    sprintf(req.OrderRef, "%d", order.id.init_id);//��������
    req.Direction = Mapping::toCtpDirection(order.direction);  //��������	
	req.CombHedgeFlag[0] = Mapping::toCtpHedge(order.hedge_type);	  //���Ͷ���ױ���־	
    req.OrderPriceType = Mapping::toCtpDealType(order.deal_type); //�мۻ��޼�
    req.LimitPrice = order.price;	//�۸�
	req.VolumeTotalOriginal = order.volume;	///����		

	req.CombOffsetFlag[0] = THOST_FTDC_OF_Open; //��Ͽ�ƽ��־:����
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
    wait(syn);
    std::cout<<"----------------"<<std::endl;
    std::cout<<req.OrderRef<<std::endl;
    std::cout<<"----------------"<<std::endl;
    return ret;
}

int CtpTrader::reqTick(const Contract &c, bool syn)
{
    if (syn) synLock();
	CThostFtdcQryDepthMarketDataField req;
	memset(&req, 0, sizeof(req));
    strcpy(req.InstrumentID, c.code.c_str());//Ϊ�ձ�ʾ��ѯ���к�Լ
	int ret = api_->ReqQryDepthMarketData(&req, nextRequestId());
    wait(syn);
	cerr<<" ���� | ���ͺ�Լ���۲�ѯ..."<<((ret == 0)?"�ɹ�":"ʧ��")<<endl;
    return ret;
}

int CtpTrader::reqContract(Contract *c, bool syn)
{
    if (syn) synLock();
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
    // ���Ϊ�գ���ʾ��ѯ���к�Լ
    strcpy(req.InstrumentID, c->code.c_str());
	int ret = api_->ReqQryInstrument(&req, nextRequestId());
    wait(syn);
    return ret;
}

int CtpTrader::reqCaptial(bool syn)
{
    if (syn) synLock();
	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);
	strcpy(req.InvestorID, user_id_);
	int ret = api_->ReqQryTradingAccount(&req, nextRequestId());
    wait(syn);
	cerr<<" ���� | �����ʽ��ѯ..."<<((ret == 0)?"�ɹ�":"ʧ��")<<endl;
    return ret;
}

int CtpTrader::reqPosition(const char *instId, bool syn)
{
    if (syn) synLock();
	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);
	strcpy(req.InvestorID, user_id_);
	strcpy(req.InstrumentID, instId);	
	int ret = api_->ReqQryInvestorPosition(&req, nextRequestId());
    wait(syn);
	cerr<<" ���� | ���ͳֲֲ�ѯ..."<<((ret == 0)?"�ɹ�":"ʧ��")<<endl;
    return ret;
}

int CtpTrader::cancel_order(int orderSeq, bool syn)
{
    if (syn) synLock();

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
    wait(syn);
    cerr<< " ���� | ���ͳ���..." <<((ret == 0)?"�ɹ�":"ʧ��") << endl;
    return ret;

}


void CtpTrader::on_tick(const TickData &tick) const {

}
//
//    virtual void on_query() = 0;
//    virtual void on_contract() = 0;
//    virtual void on_captial() = 0;

//    virtual void query() = 0;

void CtpTrader::on_cancel_order(Order order) {

}

void CtpTrader::on_order(Transaction trans) {

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

void CtpTrader::ReqSettlementInfoConfirm()
{
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);
	strcpy(req.InvestorID, user_id_);
	int ret = api_->ReqSettlementInfoConfirm(&req, nextRequestId());
	cerr<<" ���� | ���ͽ��㵥ȷ��..."<<((ret == 0)?"�ɹ�":"ʧ��")<<endl;
}

void CtpTrader::PrintOrders(){
  CThostFtdcOrderField* pOrder; 
  for(unsigned int i=0; i<orderList.size(); i++){
    pOrder = orderList[i];
    cerr<<" ���� | ��Լ:"<<pOrder->InstrumentID
//        <<" ����:"<<MapDirection(pOrder->Direction,false)
        <<" ��ƽ:"<<MapOffset(pOrder->CombOffsetFlag[0],false)
        <<" �۸�:"<<pOrder->LimitPrice
        <<" ����:"<<pOrder->VolumeTotalOriginal
        <<" ���:"<<pOrder->BrokerOrderSeq 
        <<" �������:"<<pOrder->OrderSysID
        <<" ״̬:"<<pOrder->StatusMsg<<endl;
  }
//  sem.sem_v();
}
void CtpTrader::PrintTrades(){
  CThostFtdcTradeField* pTrade;
  for(unsigned int i=0; i<tradeList.size(); i++){
    pTrade = tradeList[i];
    cerr<<" �ɽ� | ��Լ:"<< pTrade->InstrumentID 
//        <<" ����:"<<MapDirection(pTrade->Direction,false)
        <<" ��ƽ:"<<MapOffset(pTrade->OffsetFlag,false) 
        <<" �۸�:"<<pTrade->Price
        <<" ����:"<<pTrade->Volume
        <<" �������:"<<pTrade->OrderSysID
        <<" �ɽ����:"<<pTrade->TradeID<<endl;
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
    cerr<<"�E��ס�����..."<<endl;
}

char MapOffset(char src, bool toOrig=true){
  if(toOrig){
    if('o'==src||'O'==src){src='0';}
    else if('c'==src||'C'==src){src='1';}       ///< ƽ�� 
    else if('j'==src||'J'==src){src='3';}       ///< ƽ��
  }else{
    if('0'==src){src='O';}
    else if('1'==src){src='C';}
    else if('3'==src){src='J';}
  }
  return src;
}
// ---------------------------------------------------------------
void CtpTrader::OnFrontConnected() {
	cout<<" trader front connectd..."<<endl;
    synUnlock();
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
  if(bIsLast) synUnlock();
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
    if(bIsLast) synUnlock();
}

void CtpTrader::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, 
         CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{ 	
    if ( !IsErrorRspInfo(pRspInfo) &&  pInstrument){
        cerr<<" ��Ӧ | ��Լ:"<<pInstrument->InstrumentID
            <<" ������:"<<pInstrument->DeliveryMonth
            <<" ��ͷ��֤����:"<<pInstrument->LongMarginRatio
            <<" ����������:"<<pInstrument->ExchangeID
            <<" ��ͷ��֤����:"<<pInstrument->ShortMarginRatio<<endl;    
    }
    if(bIsLast) synUnlock();
}

void CtpTrader::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData,
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!IsErrorRspInfo(pRspInfo) && pDepthMarketData){
        TickData tick;
        Mapping::fromCtpTick(*pDepthMarketData, &tick);
        on_tick(tick);
    }
    if(bIsLast) synUnlock();
}

void CtpTrader::OnRspQryTradingAccount(
    CThostFtdcTradingAccountField *pTradingAccount, 
   CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{ 
    if (!IsErrorRspInfo(pRspInfo) &&  pTradingAccount){
        cerr<<" ��Ӧ | Ȩ��:"<<pTradingAccount->Balance
            <<" ����:"<<pTradingAccount->Available   
            <<" ��֤��:"<<pTradingAccount->CurrMargin
            <<" ƽ��ӯ��:"<<pTradingAccount->CloseProfit
            <<" �ֲ�ӯ��"<<pTradingAccount->PositionProfit
            <<" ������:"<<pTradingAccount->Commission
            <<" ���ᱣ֤��:"<<pTradingAccount->FrozenMargin
            << endl;    
    }
  if(bIsLast) synUnlock();
}

void CtpTrader::OnRspQryInvestorPosition(
    CThostFtdcInvestorPositionField *pInvestorPosition, 
    CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{ 
  if( !IsErrorRspInfo(pRspInfo) &&  pInvestorPosition ){
    cerr<<" ��Ӧ | ��Լ:"<<pInvestorPosition->InstrumentID
//      <<" ����:"<<MapDirection(pInvestorPosition->PosiDirection-2,false)
      <<" �ֲܳ�:"<<pInvestorPosition->Position
      <<" ���:"<<pInvestorPosition->YdPosition 
      <<" ���:"<<pInvestorPosition->TodayPosition
      <<" �ֲ�ӯ��:"<<pInvestorPosition->PositionProfit
      <<" ��֤��:"<<pInvestorPosition->UseMargin<<endl;
  }
  if(bIsLast) synUnlock();
}

void CtpTrader::OnRspOrderAction(
      CThostFtdcInputOrderActionField *pInputOrderAction, 
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
  if (!IsErrorRspInfo(pRspInfo) && pInputOrderAction){
    Order order;
    Mapping::fromCtpOrder(*pInputOrderAction, &order);
    // 
    on_cancel_order(order);
  }

  if(bIsLast) synUnlock();
}

void CtpTrader::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, 
          CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  if( !IsErrorRspInfo(pRspInfo) && pInputOrder ){
       cerr<<"��Ӧ | �����ύ�ɹ�...��������:"<<pInputOrder->OrderRef<<endl;  
       cerr<<"ccc...."<<std::endl;
  }
  //if(bIsLast) synUnlock();
}

///�����ر�
void CtpTrader::OnRtnOrder(CThostFtdcOrderField *pOrder)
{	
  CThostFtdcOrderField* order = new CThostFtdcOrderField();
  memcpy(order,  pOrder, sizeof(CThostFtdcOrderField));
  bool founded=false;    unsigned int i=0;
//  for(i=0; i<orderList.size(); i++){
//    if(orderList[i]->BrokerOrderSeq == order->BrokerOrderSeq) {
//      founded=true;    break;
//    }
//  }
//  if(founded) 
//      orderList[i]= order;   
//  else 
//      orderList.push_back(order);
  cerr<<" �ر� | �������ύ...���:"<<order->BrokerOrderSeq<<endl;
}

///�ɽ�֪ͨ
void CtpTrader::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
  Transaction trans;
  Mapping::fromCtpTransaction(*pTrade, &trans);
  //
  on_order(trans);
  synUnlock();
}

void CtpTrader::OnFrontDisconnected(int nReason)
{
	cerr<<" ��Ӧ | �����ж�..." 
	  << " reason=" << nReason << endl;
}
		
void CtpTrader::OnHeartBeatWarning(int nTimeLapse)
{
	cerr<<" ��Ӧ | ������ʱ����..." 
	  << " TimerLapse = " << nTimeLapse << endl;
}

void CtpTrader::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	IsErrorRspInfo(pRspInfo);
    if(bIsLast) synUnlock();
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
