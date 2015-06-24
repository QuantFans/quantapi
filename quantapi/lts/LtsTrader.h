/**
 * @file LtsTrader.h
 * @brief 
 * @author HonePhy
 * Copyright () 2014-2020 QuantDigger. All rights reserved.
 * @chanege-log	 	
		2015-06-14 根据quantapi接口的调整做修改
 * @version 0.1
 * @date 2015-04-10
 */
#ifndef LTSTRADER_H

#define LTSTRADER_H
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <quantapi/Trader.h>
#include "SecurityFtdcUserApiDataType.h"
#include "SecurityFtdcTraderApi.h"
#include "SecurityFtdcUserApiStruct.h"

namespace QuantApi {
	

class LtsTrader : public Trader, private CSecurityFtdcTraderSpi {
public:
	LtsTrader(char* trade_front);

	~LtsTrader();

public:
	virtual int login(const LogonInfo &info, bool syn=false);
	
	virtual int logout(const LogonInfo &info, bool syn=false);

	///请求查询合约
	virtual int reqContract(const Contract &c, bool syn=false);

	///查询合约的最新报价
	virtual int reqTick(const Contract &c, bool syn=false);

	///请求查询资金账户
	virtual int reqCaptial(bool syn=false);

	///请求查询投资者持仓
	virtual int reqPosition(const Contract &contract, bool syn = false);

	/**
     * @brief  下单请求,开仓或平仓
     */
	virtual int order(const Order &order, bool syn=false);

	/** @brief 撤单操作请求 */
	virtual int cancel_order(int orderSeq, bool sync=false);

 protected:
    /** @brief tick数据到达回调函数。*/
    virtual void on_tick(const TickData &tick) { }
    
    /** @brief 撤单回调 */
    virtual void on_cancel_order(Order order) { }

    /** @brief 报单到达交易所回调 */
    virtual void on_order(const Order &order) { }

    /** @brief 报单成交回调 */
    virtual void on_transaction(const Transaction &tans) { }

    /** @brief 合约查询回调 */
    virtual void on_contract(const Contract &contract) { }

    /** @brief 资金查询回调 */
    virtual void on_captial(const Captial &cap) { }

    /** @brief 持仓查询回调 */
    virtual void on_position(const Position &pos) { }

    //----------------------以上方法由回调线程调用，作为模版方法，可以用于子类继承重写作为不同用途----------------------------	

private:

	///投资者结算结果查询
	virtual void qrySettlementInfo(const char *broker_id,
								   const char *investor_id,
								   const char *trading_day,
								   bool syn=false);
	///投资者结算结果确认
	virtual void settlementInfoConfirm(bool syn=false);

	///注册前置地址
	virtual void registerFront(char *pszFrontAdderss, bool syn=false);

//	inline void synUnlock() { if(locked_) syn_flag_.unlock();}
	
//	inline void synLock() { syn_flag_.lock(); locked_ = true; }
	
	inline int nextRequestId() { return ++request_id_; }
	
	inline void notify() {
		std::unique_lock <std::mutex> lock(syn_flag_);
		locked_ = false;
		m_cond.notify_all();
	}

	inline void wait(bool towait) { 
		if(towait) { 
			std::unique_lock<std::mutex> lock(syn_flag_);
			locked_ = true;
			m_cond.wait(lock);
		}
	}

	inline void set_front_id(int id) { front_id_ = id; }

    inline void set_session_id(int id) { session_id_ = id; }

    inline int session_id() { return session_id_; }

    inline int front_id(int id) { return front_id_; }
	
private:
	//----------------------继承自CSecurityFtdcTraderSpi的回调方法实现-----
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	virtual void OnFrontDisconnected(int nReason);
	
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	virtual void OnHeartBeatWarning(int nTimeLapse);
	
	///错误应答
	virtual void OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);	
	
	/// 登录请求响应
	virtual void OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单录入请求响应
	virtual void OnRspOrderInsert(CSecurityFtdcInputOrderField *pInputOrder, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///报单操作请求响应
	virtual void OnRspOrderAction(CSecurityFtdcInputOrderActionField *pInputOrderAction, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///请求查询合约响应
	virtual void OnRspQryInstrument(CSecurityFtdcInstrumentField *pInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CSecurityFtdcInvestorPositionField *pInvestorPosition, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CSecurityFtdcTradingAccountField *pTradingAccount, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///投资者结算结果确认响应
	//virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
    ///请求查询行情响应
	virtual void OnRspQryDepthMarketData(CSecurityFtdcDepthMarketDataField *pDepthMarketData, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单通知
	virtual void OnRtnOrder(CSecurityFtdcOrderField *pOrder);
	///成交通知
	virtual void OnRtnTrade(CSecurityFtdcTradeField *pTrade);

	/// 是否收到成功的响应
	bool IsErrorRspInfo(CSecurityFtdcRspInfoField *pRspInfo);

private:
	int							front_id_;			///< 前置编号
	int							session_id_;		///< 会话编号

	TSecurityFtdcBrokerIDType	broker_id_;			///< 公司代码
	TSecurityFtdcInvestorIDType	user_id_;		///< 投资者代码
	int							order_ref_;			///< 订单编号
	CSecurityFtdcTraderApi		*api_;				///< 请求实例
	int                     	request_id_;            ///< 会话编号

	std::mutex              syn_flag_;              ///< 同步
	std::atomic<bool>       locked_;                ///< 是否被锁住，用来决定解锁操作是否执行。
	std::condition_variable m_cond;					//条件变量
};	

} /* QuantDigger */

#endif /* end of include guard: LTSTRADER_H */
