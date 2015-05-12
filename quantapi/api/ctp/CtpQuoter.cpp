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
#include "CtpQuoterCallBack.h"

tm g_today;   ///< 当日日期，在登入交易接口的时候被初始化。
namespace QuantDigger {
using namespace std;

CtpQuoter::CtpQuoter(char *trade_front, CtpQuoterCallBack *cbk_object) {
    assert(trade_front && cbk_object);
    spi_ = cbk_object;
    api_ = CThostFtdcMdApi::CreateFtdcMdApi();
    api_->RegisterSpi(spi_);
    spi_->set_quoter(this);
    locked_ = false;
    registerFront(trade_front, true);
    init();
    wait(true);      // 回调在init之后才会运行！
};

CtpQuoter::~CtpQuoter(){ 
    join();
    release();
};

void CtpQuoter::registerFront(char *pszFrontAddress, bool syn) {
    if (syn) synLock();
    RegisterFront(pszFrontAddress);
}

void CtpQuoter::login(const char *broker_id,
                      const char *user_id,
                      const char *password,
                      bool syn) {
    if (syn) synLock();
    ReqUserLogin(broker_id, user_id, password);
    wait(syn);
}

void CtpQuoter::logout(const char *broker_id, const char *user_id, bool syn) {
    if (syn) synLock();
    ReqUserLogout(broker_id, user_id);
    wait(syn);
}

void CtpQuoter::subscribeMarketData(const std::vector<Contract> &instruments, bool syn) {
    char **instrumentsL  = new char*[instruments.size()];
    for (int i = 0; i < instruments.size(); i++) {
        instrumentsL[i] = const_cast<char*>(instruments[i].code.c_str());
    }
    if (syn) synLock();
    SubscribeMarketData(instrumentsL,  instruments.size());
    wait(syn);
    delete [] instrumentsL;
}

void CtpQuoter::unsubscribeMarketData(const std::vector<Contract> &instruments, bool syn) {
    char **instrumentsL  = new char*[instruments.size()];
    for (int i = 0; i < instruments.size(); i++) {
        instrumentsL[i] = const_cast<char*>(instruments[i].code.c_str());
    }
    if (syn) synLock();
    UnSubscribeMarketData(instrumentsL,  instruments.size());
    wait(syn);
    delete [] instrumentsL;
}

// ---------------------------------------------------------------------------------------
void CtpQuoter::ReqUserLogin(const char *broker_id, const char* user_id, const char *password)
{
  
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id); 
	strcpy(req.UserID, user_id); 
	strcpy(req.Password, password);
	int ret = api_->ReqUserLogin(&req, nextRequestId());
    cerr<<" sending | 窟僕鞠村..."<<((ret == 0) ? "撹孔" :"払移") << endl;	
}

void CtpQuoter::ReqUserLogout(const char *broker_id, const char *user_id) {
    CThostFtdcUserLogoutField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, broker_id); 
	strcpy(req.UserID, user_id); 
	int ret = api_->ReqUserLogout(&req, nextRequestId());
    cerr<<" sending | 窟僕曜竃..."<<((ret == 0) ? "撹孔" :"払移") << endl;	
}

int CtpQuoter::UnSubscribeMarketData(char *ppInstrumentID[], int nCount) {
	int ret = api_->UnSubscribeMarketData(ppInstrumentID, nCount);
    if(0 == ret)
        cout<<"SubscribeMarketData sucess"<<endl;
    else
        cout<<"SubscribeMarketData error"<<endl;
	return ret;
}

int CtpQuoter::SubscribeMarketData(char *ppInstrumentID[], int nCount) {
	int ret = api_->SubscribeMarketData(ppInstrumentID, nCount);
    if(0 == ret)
        cout<<"SubscribeMarketData sucess"<<endl;
    else
        cout<<"SubscribeMarketData error"<<endl;
	return ret;
}

void CtpQuoter::RegisterFront(char *pszFrontAddress) {
    api_->RegisterFront(pszFrontAddress);
    cerr<<"Register Front..."<<endl;
}

} /* QuantDigger */
