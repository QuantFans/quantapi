/**
 * @file LtsQuoter.cpp
 * @brief 
 * @author HonePhy
 * Copyright () 2014-2020 QuantDigger. All rights reserved.
 * @chanege-log
		2015-06-14 ����quantapi�ӿڵĵ������޸�
 * @version 0.1
 * @date 2015-04-16
 */
 
#include <ctime>
#include <cassert>
#include <mutex>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdio>
#include <quantapi/mapping.h>
#include <quantapi/lts/LtsMapping.h>
#include "LtsQuoter.h"
#include "../../util/Functions.h" 

namespace Global {
    tm g_today;   ///< �������ڣ��ڵ��뽻�׽ӿڵ�ʱ�򱻳�ʼ����
} /* Global */

namespace QuantApi {

LtsQuoter::LtsQuoter(char *trade_front) {
    assert(trade_front);
    api_ = CSecurityFtdcMdApi::CreateFtdcMdApi();
    api_->RegisterSpi(this);
    locked_ = false;
    registerFront(trade_front, true);
}

LtsQuoter::~LtsQuoter(){ 
    api_->Join();
    api_->Release();
}

void LtsQuoter::registerFront(char *pszFrontAddress, bool syn) {
    api_->RegisterFront(pszFrontAddress);
	api_->Init(); // �ص���init֮��Ż����У�
	wait(syn);
    std::cout<<"Register Front..."<<std::endl;
}

int LtsQuoter::login(const LogonInfo &info, bool syn) {
	CSecurityFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, info.broker_id); 
	strcpy(req.UserID, info.user_id); 
	strcpy(req.Password, info.password);
	int ret = api_->ReqUserLogin(&req, nextRequestId());
    std::cout<<" sending | ReqUserLogin..."<<((ret == 0) ? "Success" :"Failed") << std::endl;
    wait(syn);
	return ret;
}

int LtsQuoter::logout(const LogonInfo &info, bool syn) {
    CSecurityFtdcUserLogoutField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, info.broker_id); 
	strcpy(req.UserID, info.user_id); 
	int ret = api_->ReqUserLogout(&req, nextRequestId());
    std::cout<<" sending | ReqUserLogout..."<<((ret == 0) ? "Success" :"Failed") << std::endl;
    wait(syn);
	return ret;
}

int LtsQuoter::reqTick(const std::vector<Contract> &contracts, bool syn) {
    char **contractsL  = new char*[contracts.size()];
	char *pExchageID = NULL;
    for (int i = 0; i < contracts.size(); i++) {
        contractsL[i] = const_cast<char*>(contracts[i].code.c_str());
		pExchageID = const_cast<char*>(mapFromQDExchType(contracts[i].exch_type).c_str());
    }
	int ret = api_->SubscribeMarketData(contractsL, contracts.size(), "SSE");
	delete [] contractsL;
    wait(syn);
    return ret;
}

int LtsQuoter::unReqTick(const std::vector<Contract> &contracts, bool syn) {
    char **contractsL  = new char*[contracts.size()];
	char *pExchageID = NULL;
    for (int i = 0; i < contracts.size(); i++) {
        contractsL[i] = const_cast<char*>(contracts[i].code.c_str());
		pExchageID = const_cast<char*>(mapFromQDExchType(contracts[i].exch_type).c_str());
    }
    int ret = api_->UnSubscribeMarketData(contractsL, contracts.size(), "SSE");
	delete [] contractsL;
    wait(syn);
    return ret;
}

// ---------------------------------------------------------------------------------------
void LtsQuoter::OnHeartBeatWarning(int nTimeLapse) {
}

void LtsQuoter::OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, 
							   CSecurityFtdcRspInfoField *pRspInfo,
                               int nRequestID, 
                               bool bIsLast) {
    if ( !IsErrorRspInfo(pRspInfo) && pRspUserLogin ) {  
        // ����Ự����	
//        set_logined(true);
        set_front_id(pRspUserLogin->FrontID);
        set_session_id(pRspUserLogin->SessionID);
        std::cout <<" ��Ӧ | ��¼�ɹ�...��ǰ������:"
            <<pRspUserLogin->TradingDay<<std::endl
            <<session_id()<<std::endl;
        // ��¼��������
		Util::strDate2Tm(pRspUserLogin->TradingDay, &Global::g_today);
    }
    if(bIsLast) notify();
}

void LtsQuoter::OnRspError(CSecurityFtdcRspInfoField *pRspInfo, 
                           int nRequestID, 
                           bool bIsLast) {
  if(bIsLast) notify();
}

bool LtsQuoter::IsErrorRspInfo(CSecurityFtdcRspInfoField *pRspInfo) {
	// ���ErrorID != 0, ˵���յ��˴������Ӧ
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
  if (ret){
    std::cerr<<" Error | "<<pRspInfo->ErrorMsg<<std::endl;
  }
	return ret;
}

void LtsQuoter::OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, 
                                CSecurityFtdcRspInfoField *pRspInfo, 
                                int nRequestID, 
                                bool bIsLast) {
  if(bIsLast) notify();
}

void LtsQuoter::OnRspUnSubMarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument,
                                     CSecurityFtdcRspInfoField *pRspInfo,
                                     int nRequestID,bool bIsLast) {
  if(bIsLast) notify();
}

void LtsQuoter::OnRspSubMarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, 
                                   CSecurityFtdcRspInfoField *pRspInfo, 
                                   int nRequestID, 
                                   bool bIsLast) {
    if (!IsErrorRspInfo(pRspInfo)) {
        std::cout<<"��Ӧ | �������ݣ�"<<std::endl;
    } else {
        std::cerr<<"************"<<std::endl;
    }
  if(bIsLast) notify();
}

void LtsQuoter::OnFrontConnected() {
	std::cout<<" quoter front connectd..."<<std::endl;
    notify();
}

void LtsQuoter::OnFrontDisconnected(int nReason) {
	std::cerr<<" ��Ӧ | �����ж�..." 
	  << " reason=" << nReason << std::endl;
}

void LtsQuoter::OnRtnDepthMarketData(CSecurityFtdcDepthMarketDataField *pDepthMarketData) {
    TickData tick;
    Mapping::fromLtsTick(*pDepthMarketData, &tick);
    on_tick(tick);
}

} /* QuantDigger */