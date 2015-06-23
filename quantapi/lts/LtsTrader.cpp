/**
 * @file LtsTrader.cpp
 * @brief 
 * @author HonePhy
 * Copyright () 2014-2020 QuantDigger. All rights reserved.
 * @chanege-log 	
		2015-06-14 ����quantapi�ӿڵĵ������޸�
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
    tm g_today;   ///< �������ڣ��ڵ��뽻�׽ӿڵ�ʱ�򱻳�ʼ����
} /* Global */

namespace QuantApi {

std::vector<CSecurityFtdcOrderField*> orderList; //�Ѿ������б�
std::vector<CSecurityFtdcTradeField*> tradeList; //�ɽ��б�


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
	strcpy(req.BrokerID, broker_id_);  									//Ӧ�õ�Ԫ����	
	strcpy(req.InvestorID, user_id_); 									//Ͷ���ߴ���	
	strcpy(req.InstrumentID, order.contract.code.c_str()); 				//��Լ����
	
	sprintf(req.OrderRef, "%d", order.id.init_id);						//��������
	req.Direction = Mapping::toLtsDirection(order.direction);  			//�������� Ҫ�޸�
	req.CombHedgeFlag[0] = Mapping::toLtsHedge(order.hedge_type);		//���Ͷ���ױ���־	
	req.OrderPriceType = Mapping::toLtsPriceType(order.price_type);		//�۸�����=�мۻ��޼�
	req.CombOffsetFlag[0] = Mapping::toLtsTradeSide(order.side);		//��Ͽ�ƽ��־:����
	
	sprintf(req.LimitPrice, "%f", order.price); 								//�۸�
	req.VolumeTotalOriginal = order.volume;										//����	
	
	req.VolumeCondition = SECURITY_FTDC_VC_AV; 							//�ɽ�������:�κ�����
	req.MinVolume = 1;													//��С�ɽ���:1	
	
	req.ContingentCondition = SECURITY_FTDC_CC_Immediately;  			//��������:����
	req.ForceCloseReason = SECURITY_FTDC_FCC_NotForceClose;				//ǿƽԭ��:��ǿƽ
	
	req.IsAutoSuspend = 0;												//�Զ������־:��	
	req.UserForceClose = 0;   											//�û�ǿ����־:��
    
	if (0 == order.price){
        req.TimeCondition = SECURITY_FTDC_TC_IOC;						//��Ч������:������ɣ�������
    }else{
        req.TimeCondition = SECURITY_FTDC_TC_GFD;  						//��Ч������:������Ч
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
		std::cerr <<" ���� | ����������."<< std::endl; 
		return 0;
	} 

	CSecurityFtdcInputOrderActionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id_);   //���͹�˾����	
	strcpy(req.InvestorID, user_id_); //Ͷ���ߴ���
	//strcpy(req.OrderRef, pOrderRef); //��������	
	//req.FrontID = frontId;           //ǰ�ñ��	
	//req.SessionID = sessionId;       //�Ự���
    strcpy(req.ExchangeID, orderList[i]->ExchangeID);
   // strcpy(req.OrderSysID, orderList[i]->OrderSysID); Lts���޴��ֶ�
	req.ActionFlag = SECURITY_FTDC_AF_Delete;  //������־ 

	int ret = api_->ReqOrderAction(&req, nextRequestId());
	std::cout << " ���� | ���ͳ���..." <<((ret == 0)?"�ɹ�":"ʧ��") << std::endl;
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

//----------------------�̳���CSecurityFtdcTraderSpi�Ļص�����ʵ��-------
///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void LtsTrader::OnFrontConnected() {
	std::cout << " trader front connectd..." << std::endl;
	synUnlock();
}

///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
void LtsTrader::OnFrontDisconnected(int nReason) {
	std::cerr << " ��Ӧ | �����ж�..."
		<< " reason=" << nReason << std::endl;
}

///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
void LtsTrader::OnHeartBeatWarning(int nTimeLapse) {
	std::cerr << " ��Ӧ | ������ʱ����..."
		<< " TimerLapse = " << nTimeLapse << std::endl;
}

///����Ӧ��
void LtsTrader::OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	IsErrorRspInfo(pRspInfo);
	if (bIsLast) synUnlock();
}

/// ��¼������Ӧ
void LtsTrader::OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, 
			CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!IsErrorRspInfo(pRspInfo) && pRspUserLogin) {
		set_logined(true);
		set_front_id(pRspUserLogin->FrontID);
		set_session_id(pRspUserLogin->SessionID);
		std::cout << " ��Ӧ | �û���¼�ɹ�...��ǰ������:"
			<< pRspUserLogin->TradingDay << std::endl;
	}
	if (bIsLast) synUnlock();
}

///����¼��������Ӧ
void LtsTrader::OnRspOrderInsert(CSecurityFtdcInputOrderField *pInputOrder, 
			CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!IsErrorRspInfo(pRspInfo) && pInputOrder){
		std::cout << "��Ӧ | �����ύ�ɹ�...��������:" 
			<< pInputOrder->OrderRef << std::endl;
	}
}

///��������������Ӧ
void LtsTrader::OnRspOrderAction(CSecurityFtdcInputOrderActionField *pInputOrderAction, 
			CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!IsErrorRspInfo(pRspInfo) && pInputOrderAction)
	{
		Order order;
        Mapping::fromLtsOrder(*pInputOrderAction, &order);
        // ������Ӧ
        on_cancel_order(order);
	}
	if (bIsLast) synUnlock();
}

///�����ѯ��Լ��Ӧ
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

///�����ѯͶ���ֲ߳���Ӧ
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

///�����ѯ�ʽ��˻���Ӧ
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

///Ͷ���߽�����ȷ����Ӧ
//void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

///�����ѯ������Ӧ
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

///����֪ͨ
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
	std::cout << " �ر� | �������ύ...���:" << pOrder->BrokerOrderSeq << std::endl;
}

///�ɽ�֪ͨ
void LtsTrader::OnRtnTrade(CSecurityFtdcTradeField *pTrade) {
    Transaction trans;
    Mapping::fromLtsTransaction(*pTrade, &trans);
    //
    on_transaction(trans);
    std::cout<<" Response | deal,  order id:"<<pTrade->OrderSysID<< std::endl;  // �ɽ�����е��ֶΣ�
    synUnlock();
}

bool LtsTrader::IsErrorRspInfo(CSecurityFtdcRspInfoField *pRspInfo)
{
	// ���ErrorID != 0, ˵���յ��˴������Ӧ
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (ret){
		std::cerr << " Error: | " << pRspInfo->ErrorMsg << std::endl;
	}
	return ret;
}

} /* QuantDigger */
