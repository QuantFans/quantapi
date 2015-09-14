/**
 * @file ctpquoter.cpp
 * @brief 
 * @author wdj
 * @version 0.1
 * @date 2014-04-09
 */

#include "CtpQuoter.h"
#include <ctime>
#include <cassert>
#include <mutex>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdio>

#include "CtpMapping.h" 
#include "../../util/Functions.h" 
/*
namespace Global {
    tm g_today;   ///< �������ڣ��ڵ��뽻�׽ӿڵ�ʱ�򱻳�ʼ����
} /* Global */

namespace QuantApi {
using namespace std;

CtpQuoter::CtpQuoter(char *trade_front):logger(Logger::getRootLogger()) {
    assert(trade_front);
    api_ = CThostFtdcMdApi::CreateFtdcMdApi();
    api_->RegisterSpi(this);
    locked_ = false;
    registerFront(trade_front, true);
};

CtpQuoter::~CtpQuoter(){ 
    api_->Join();
    api_->Release();
};

void CtpQuoter::registerFront(char *pszFrontAddress, bool sync) {
    api_->RegisterFront(pszFrontAddress);
	api_->Init(); // �ص���init֮��Ż����У�
	wait(sync);
}

int CtpQuoter::login(const LogonInfo &info, bool sync) {
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, info.broker_id); 
	strcpy(req.UserID, info.user_id); 
	strcpy(req.Password, info.password);
	int ret = api_->ReqUserLogin(&req, nextRequestId());
    cerr<<"try login..."<<((ret == 0) ? "sucessed" :"failed") << endl;	
    wait(sync);
	return ret;
}

int CtpQuoter::logout(const LogonInfo &info, bool sync) {
    CThostFtdcUserLogoutField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, info.broker_id); 
	strcpy(req.UserID, info.user_id); 
	int ret = api_->ReqUserLogout(&req, nextRequestId());
    cerr<<"try logout..."<<((ret == 0) ? "sucessed" :"failed") << endl;	
    wait(sync);
    return ret;
}

int CtpQuoter::reqTick(const std::vector<Contract> &contracts, bool sync) {
    char **contractsL  = new char*[contracts.size()];
    for (int i = 0; i < contracts.size(); i++) {
        contractsL[i] = const_cast<char*>(contracts[i].code.c_str());
    }
	int ret = api_->SubscribeMarketData(contractsL, contracts.size());
    delete [] contractsL;
    wait(sync);
    return ret;
}

int CtpQuoter::unReqTick(const std::vector<Contract> &contracts, bool sync) {
    char **contractsL  = new char*[contracts.size()];
    for (int i = 0; i < contracts.size(); i++) {
        contractsL[i] = const_cast<char*>(contracts[i].code.c_str());
    }
	int ret = api_->UnSubscribeMarketData(contractsL, contracts.size());
    delete [] contractsL;
    wait(sync);
    return ret;
}

// --------------------------- call back -------------------------------------------------

void CtpQuoter::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
        TickData tick;
        Mapping::fromCtpTick(*pDepthMarketData, &tick);
        on_tick(tick);
}

void CtpQuoter::OnHeartBeatWarning(int nTimeLapse) {
}

void CtpQuoter::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, 
                               CThostFtdcRspInfoField *pRspInfo, 
                               int nRequestID, 
                               bool bIsLast) {
    if ( !IsErrorRspInfo(pRspInfo) && pRspUserLogin ) {  
        // ����Ự����	
//        set_logined(true);
        set_front_id(pRspUserLogin->FrontID);
        set_session_id(pRspUserLogin->SessionID);
        cerr<<"OnRspUserLogin"<<std::endl;
        // ��¼��������
        //Util::strDate2Tm(pRspUserLogin->TradingDay, &Global::g_today);
    }
    if(bIsLast) notify();
}

void CtpQuoter::OnRspError(CThostFtdcRspInfoField *pRspInfo, 
                           int nRequestID, 
                           bool bIsLast) {
	if (bIsLast) notify();
}

void CtpQuoter::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, 
                                CThostFtdcRspInfoField *pRspInfo, 
                                int nRequestID, 
                                bool bIsLast) {
	if (bIsLast) notify();
}

void CtpQuoter::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                     CThostFtdcRspInfoField *pRspInfo,
                                     int nRequestID,bool bIsLast) {

    //ȡ����������Ӧ��, ��ʵ��
	if (bIsLast) notify();
}

void CtpQuoter::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
                                   CThostFtdcRspInfoField *pRspInfo, 
                                   int nRequestID, 
                                   bool bIsLast) {
    if (!IsErrorRspInfo(pRspInfo)) {
        // ���ݶ��ĳɹ��� ��ʵ�֡�
        cout<<"OnRspSubMarketData succ"<<endl;
    } else {
        cout<<"OnRspSubMarketData fail"<<endl;
    }
	if (bIsLast) notify();
}

void CtpQuoter::OnFrontConnected() {
    LOG4CXX_INFO(logger, "quoter front connected...");
	notify();
}

void CtpQuoter::OnFrontDisconnected(int nReason) {
    LOG4CXX_ERROR(logger, "quoter front disconnected...");
	cerr<<" ��Ӧ | �����ж�..." 
	  << " reason=" << nReason << endl;
}


bool CtpQuoter::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo) {
	// ���ErrorID != 0, ˵���յ��˴������Ӧ
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
  if (ret){
    cerr<<" Error | "<<pRspInfo->ErrorMsg<<endl;
  }
	return ret;
}


} /* QuantDigger */
