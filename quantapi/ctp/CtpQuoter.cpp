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

namespace Global {
    tm g_today;   ///< 当日日期，在登入交易接口的时候被初始化。
} /* Global */

namespace QuantApi {
using namespace std;

CtpQuoter::CtpQuoter(char *trade_front) {
    assert(trade_front);
    api_ = CThostFtdcMdApi::CreateFtdcMdApi();
    api_->RegisterSpi(this);
    locked_ = false;
    registerFront(trade_front, true);
    api_->Init(); // 回调在init之后才会运行！
    wait(true);      
};

CtpQuoter::~CtpQuoter(){ 
    api_->Join();
    api_->Release();
};

void CtpQuoter::registerFront(char *pszFrontAddress, bool sync) {
    if (sync) synLock();
    api_->RegisterFront(pszFrontAddress);
}

int CtpQuoter::login(const LogonInfo &info, bool sync) {
    if (sync) synLock();
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, info.broker_id); 
	strcpy(req.UserID, info.user_id); 
	strcpy(req.Password, info.password);
	int ret = api_->ReqUserLogin(&req, nextRequestId());
    cerr<<"try login..."<<((ret == 0) ? "sucessed" :"failed") << endl;	
    wait(sync);
}

int CtpQuoter::logout(const LogonInfo &info, bool sync) {
    if (sync) synLock();
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
    if (sync) synLock();
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
    if (sync) synLock();
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
        // 保存会话参数	
//        set_logined(true);
        set_front_id(pRspUserLogin->FrontID);
        set_session_id(pRspUserLogin->SessionID);
        cerr<<"OnRspUserLogin"<<std::endl;
        // 记录当期日期
        Util::strDate2Tm(pRspUserLogin->TradingDay, &Global::g_today);
    }
    if(bIsLast) synUnlock();
}

void CtpQuoter::OnRspError(CThostFtdcRspInfoField *pRspInfo, 
                           int nRequestID, 
                           bool bIsLast) {
  if(bIsLast) synUnlock();
}

void CtpQuoter::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, 
                                CThostFtdcRspInfoField *pRspInfo, 
                                int nRequestID, 
                                bool bIsLast) {
  if(bIsLast) synUnlock();
}

void CtpQuoter::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                     CThostFtdcRspInfoField *pRspInfo,
                                     int nRequestID,bool bIsLast) {

    //取消订阅行情应答, 待实现
    if(bIsLast) synUnlock();
}

void CtpQuoter::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
                                   CThostFtdcRspInfoField *pRspInfo, 
                                   int nRequestID, 
                                   bool bIsLast) {
    if (!IsErrorRspInfo(pRspInfo)) {
        // 数据订阅成功， 待实现。
        cerr<<"OnRspSubMarketData"<<endl;
    } else {
        cerr<<"************"<<endl;
    }
  if(bIsLast) synUnlock();
}

void CtpQuoter::OnFrontConnected() {
	cerr<<" quoter front connectd..."<<endl;
    synUnlock();
}

void CtpQuoter::OnFrontDisconnected(int nReason) {
	cerr<<" 响应 | 连接中断..." 
	  << " reason=" << nReason << endl;
}


bool CtpQuoter::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo) {
	// 如果ErrorID != 0, 说明收到了错误的响应
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
  if (ret){
    cerr<<" Error | "<<pRspInfo->ErrorMsg<<endl;
  }
	return ret;
}


} /* QuantDigger */
