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

// �Ự����, ��OnRspUserLogin �����г�ʼ��

vector<CThostFtdcOrderField*> orderList; // �Ѿ��ύ�ı���, �����Ƿ���
vector<CThostFtdcTradeField*> tradeList; // �Ѿ��ɽ��ı���

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
    wait(true);      // �ص���init֮��Ż����У�
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
    cerr<<" sending | �߃W�׸Y..."<<((ret == 0) ? "���" :"�B��") << endl;	
}

void CtpTrader::ReqSettlementInfoConfirm()
{
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);
	strcpy(req.InvestorID, user_id_);
	int ret = api_->ReqSettlementInfoConfirm(&req, nextRequestId());
	cerr<<" ���� | ���ͽ��㵥ȷ��..."<<((ret == 0)?"�ɹ�":"ʧ��")<<endl;
}

void CtpTrader::ReqQryInstrument(const char *instId)
{
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
    strcpy(req.InstrumentID, instId);//Ϊ�ձ�ʾ��ѯ���к�Լ
	int ret = api_->ReqQryInstrument(&req, nextRequestId());
	cerr<<" ���� | ���ͺ�Լ��ѯ..."<<((ret == 0)?"�ɹ�":"ʧ��")<<endl;
    cerr<<ret<<endl;
}

void CtpTrader::ReqQryDepthMarketData(const char *instId)
{
	CThostFtdcQryDepthMarketDataField req;
	memset(&req, 0, sizeof(req));
    strcpy(req.InstrumentID, instId);//Ϊ�ձ�ʾ��ѯ���к�Լ
	int ret = api_->ReqQryDepthMarketData(&req, nextRequestId());
	cerr<<" ���� | ���ͺ�Լ���۲�ѯ..."<<((ret == 0)?"�ɹ�":"ʧ��")<<endl;
}

void CtpTrader::ReqQryTradingAccount()
{
	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);
	strcpy(req.InvestorID, user_id_);
	int ret = api_->ReqQryTradingAccount(&req, nextRequestId());
	cerr<<" ���� | �����ʽ��ѯ..."<<((ret == 0)?"�ɹ�":"ʧ��")<<endl;

}

void CtpTrader::ReqQryInvestorPosition(const char *instId)
{
	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);
	strcpy(req.InvestorID, user_id_);
	strcpy(req.InstrumentID, instId);	
	int ret = api_->ReqQryInvestorPosition(&req, nextRequestId());
	cerr<<" ���� | ���ͳֲֲ�ѯ..."<<((ret == 0)?"�ɹ�":"ʧ��")<<endl;
}

void CtpTrader::ReqOrderInsert(const char *instId, 
                               char dir, 
                               const char *kpp, 
                               double price,   
                               int vol) {
	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));	
	strcpy(req.BrokerID, broker_id_);  //Ӧ�õ�Ԫ����	
	strcpy(req.InvestorID, user_id_); //Ͷ���ߴ���	
	strcpy(req.InstrumentID, instId); //��Լ����	

//	strcpy(req.OrderRef, order_ref_);  //��������
//    int nextOrderRef = atoi(order_ref_);
//    sprintf(order_ref_, "%d", ++nextOrderRef);
  
    req.LimitPrice = price;	//�۸�
    if(0==req.LimitPrice){
        req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;//�۸�����=�м�
        req.TimeCondition = THOST_FTDC_TC_IOC;//��Ч������:������ɣ�������
//        req.TimeCondition = THOST_FTDC_TC_GFD;  //��Ч������:������Ч
    }else{
        req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;//�۸�����=�޼�	
        req.TimeCondition = THOST_FTDC_TC_GFD;  //��Ч������:������Ч
    }
    req.Direction = MapDirection(dir,true);  //��������	
	req.CombOffsetFlag[0] = MapOffset(kpp[0],true); //��Ͽ�ƽ��־:����
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;	  //���Ͷ���ױ���־	
	req.VolumeTotalOriginal = vol;	///����		
	req.VolumeCondition = THOST_FTDC_VC_AV; //�ɽ�������:�κ�����
	req.MinVolume = 1;	//��С�ɽ���:1	
	req.ContingentCondition = THOST_FTDC_CC_Immediately;  //��������:����
	
  //TThostFtdcPriceType	StopPrice;  //ֹ���
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;	//ǿƽԭ��:��ǿƽ	
	req.IsAutoSuspend = 0;  //�Զ������־:��	
	req.UserForceClose = 0;   //�û�ǿ����־:��

	int ret = api_->ReqOrderInsert(&req, nextRequestId());
	cerr<<" ���� | ���ͱ���..."<<((ret == 0)?"�ɹ�":"ʧ��")<< endl;
}

void CtpTrader::ReqOrderAction(int orderSeq)
{
  bool found=false; unsigned int i=0;
  for(i=0;i<orderList.size();i++){
    if(orderList[i]->BrokerOrderSeq == orderSeq){ found = true; break;}
  }
  if(!found){cerr<<" ���� | ����������."<<endl; return;} 

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
	cerr<< " ���� | ���ͳ���..." <<((ret == 0)?"�ɹ�":"ʧ��") << endl;
}

void CtpTrader::PrintOrders(){
  CThostFtdcOrderField* pOrder; 
  for(unsigned int i=0; i<orderList.size(); i++){
    pOrder = orderList[i];
    cerr<<" ���� | ��Լ:"<<pOrder->InstrumentID
        <<" ����:"<<MapDirection(pOrder->Direction,false)
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
        <<" ����:"<<MapDirection(pTrade->Direction,false)
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
    else if('c'==src||'C'==src){src='1';}       ///< ƽ�� 
    else if('j'==src||'J'==src){src='3';}       ///< ƽ��
  }else{
    if('0'==src){src='O';}
    else if('1'==src){src='C';}
    else if('3'==src){src='J';}
  }
  return src;
}

} /* QuantDigger */
