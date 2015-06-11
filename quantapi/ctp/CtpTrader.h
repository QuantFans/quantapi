/**
 * @file ctptrader.h
 * @brief 
 * @author wdj
 * @version 0.1
 * @date 2014-04-09
 */
#ifndef CTPTRADER_H

#define CTPTRADER_H
#include <atomic>
#include <mutex>
#include "../Trader.h" 
#include "ThostFtdcUserApiDataType.h" 
#include "ThostFtdcTraderApi.h" 

namespace QuantApi {

/**
* @brief CTP交易类
*
* 由两个CTP实例组成，一个发起请求，一个处理回调。
* 可通过锁来同步请求实例和回调实例来完成一个操作
*/
class CtpTrader : public Trader, private CThostFtdcTraderSpi{
public:
   CtpTrader(char* trade_front);

   ~CtpTrader();

public:
    virtual int login(const LogonInfo &info, bool syn=true);
    virtual int logout(const LogonInfo &info,  bool syn);

    /** @brief 请求查询合约 */
	virtual int reqContract(Contract *c, bool syn=false);

    /// 查询合约的最新报价
	virtual int reqTick(const Contract &c, bool syn=false);

	///请求查询资金账户
	virtual int reqCaptial(bool syn=false);

	///请求查询投资者持仓
	virtual int reqPosition(const char *instId, bool syn=false);


    /**
     * @brief  下单请求
     *
     * @param order 委托合约
     * @param syn 是否同步调用
     */
    virtual int order(const Order &order, bool syn=false);

	///撤单操作请求
	virtual int cancel_order(int orderSeq, bool syn=false);

    /**
     * @brief tick数据到达回调函数。
     *
     * @param tick 
     */
    virtual void on_tick(const TickData &tick) const;
//
//    virtual void on_query() = 0;
//    virtual void on_contract() = 0;
//    virtual void on_captial() = 0;

//    virtual void query() = 0;

    virtual void on_cancel_order(Order order);

    virtual void on_order(Transaction trans);


	///投资者结算结果查询
    virtual void qrySettlementInfo(const char *broker_id, 
                                   const char *investor_id, 
                                   const char* trading_day,
                                   bool syn=false);
	///投资者结算结果确认
	virtual void settlementInfoConfirm(bool syn=false);


    /// 注册前置地址
    virtual void registerFront(char *pszFrontAddress, bool syn=false);

    inline void synUnlock() { if(locked_) syn_flag_.unlock(); }
    inline void wait(bool towait) { if(towait) { syn_flag_.lock(); syn_flag_.unlock(); }}

    //-------------------------------------------------------
 private:

    /// @todo onrspqry...
    void ReqQrySettlementInfo(const char *broker_id, 
                              const char *investor_id, 
                              const char* trading_day);

	void ReqSettlementInfoConfirm();


//------------------------------------------------------

    inline void set_front_id(int id) { 
        front_id_ = id;
    }

    inline void set_session_id(int id) { 
        session_id_ = id;
    }
    inline int session_id() {
        return session_id_;
    }
    inline int front_id(int id) {
        return front_id_;
    }

private:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();

	/// 登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///投资者结算结果确认响应
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    /// 最新的合约报价
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单操作请求响应
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	virtual void OnFrontDisconnected(int nReason);
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///报单录入请求响应
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///报单通知
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);
	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

	/// 是否收到成功的响应
	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);


 protected:
    inline void synLock() { syn_flag_.lock(); locked_ = true;}
    inline int nextRequestId() { return ++request_id_; }
    void PrintOrders();
    void PrintTrades();

 public:
    int                     front_id_;	            ///< 前置编号
    int                     session_id_;	        ///< 会话编号
 private:
    TThostFtdcBrokerIDType  broker_id_;		        ///< 公司代码
    TThostFtdcUserIDType    user_id_;		        ///< 投资者代码
    int                     order_ref_;             ///< 订单编号
    CThostFtdcTraderApi     *api_;                  ///< 请求实例
    int                     request_id_;            ///< 会话编号
    std::mutex              syn_flag_;              ///< 同步信号
    std::atomic<bool>       locked_;                 ///< 是否被锁住，用来决定解锁操作是否执行。

};

} /* QuantDigger */

#endif /* end of include guard: CTPTRADER_H */
