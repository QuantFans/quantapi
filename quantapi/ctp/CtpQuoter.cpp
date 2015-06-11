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

tm g_today;   ///< �������ڣ��ڵ��뽻�׽ӿڵ�ʱ�򱻳�ʼ����
namespace QuantApi {
using namespace std;

CtpQuoter::CtpQuoter(char *trade_front) {
    assert(trade_front);
    api_ = CThostFtdcMdApi::CreateFtdcMdApi();
    api_->RegisterSpi(this);
    locked_ = false;
    registerFront(trade_front, true);
    std::cout<<"----<<std::endl;"<<std::endl;
    api_->Init(); // �ص���init֮��Ż����У�
    std::cout<<"----<<std::endl;" <<std::endl;
    wait(true);      
    std::cout<<"----<<std::endl;" <<std::endl;
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

int CtpQuoter::reqTick(const std::vector<Contract> &instruments, bool sync) {
    char **instrumentsL  = new char*[instruments.size()];
    for (int i = 0; i < instruments.size(); i++) {
        instrumentsL[i] = const_cast<char*>(instruments[i].code.c_str());
    }
    if (sync) synLock();
	int ret = api_->SubscribeMarketData(instrumentsL, instruments.size());
    delete [] instrumentsL;
    wait(sync);
    return ret;
}

int CtpQuoter::unReqTick(const std::vector<Contract> &instruments, bool sync) {
    char **instrumentsL  = new char*[instruments.size()];
    for (int i = 0; i < instruments.size(); i++) {
        instrumentsL[i] = const_cast<char*>(instruments[i].code.c_str());
    }
    if (sync) synLock();
	int ret = api_->UnSubscribeMarketData(instrumentsL, instruments.size());
    delete [] instrumentsL;
    wait(sync);
    return ret;
}

void CtpQuoter::on_tick(const TickData &tick) const {

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
//        cerr<<" ��Ӧ | ��¼�ɹ�...��ǰ������:"
//            <<pRspUserLogin->TradingDay<<endl
//            <<session_id()<<endl;
        cerr<<"OnRspUserLogin"<<std::endl;
        // ��¼��������
//        Util::ctpStrDate2Tm(pRspUserLogin->TradingDay, &g_today);
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
  if(bIsLast) synUnlock();
}

void CtpQuoter::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
                                   CThostFtdcRspInfoField *pRspInfo, 
                                   int nRequestID, 
                                   bool bIsLast) {
    if (!IsErrorRspInfo(pRspInfo)) {
//        cerr<<"��Ӧ | �������ݣ�"<<endl;
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
