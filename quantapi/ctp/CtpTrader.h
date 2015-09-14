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
#include <condition_variable>
#include <sstream>
#include <log4cxx/logger.h>
#include "../Trader.h" 
#include "ThostFtdcUserApiDataType.h" 
#include "ThostFtdcTraderApi.h" 

using namespace log4cxx;
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

    /**
     * @brief  下单请求
     *
     * @param info 登录信息
     * @param sync 是否同步调用
     */
    virtual int login(const LogonInfo &info, bool sync=false);

    /** @brief 退出。 */
    virtual int logout(bool sync=false);

    /** @brief 请求查询合约 */
	virtual int reqContract(Contract *c, bool sync=false);

    /** @brief 查询合约的最新报价 */
	virtual int reqTick(const Contract &c, bool sync=false);

    /** @brief 请求查询资金账户 */
	virtual int reqCaptial(bool sync=false);

    /** @brief 请求查询投资者持仓 */
	virtual int reqPosition(const Contract &contract, bool sync=false);

    /** @brief 下单，开仓或平仓。 */
    virtual int order(const Order &order, bool sync=false);

    /** @brief 撤单操作请求 */
	virtual int cancel_order(const Order& order, 
                             bool sync=false);

    inline virtual std::string nextRequestId() {
        std::ostringstream ss;
        ss << "ctp." << (++request_id_);
        return ss.str();
    }

    inline std::string requestId2str(int requestId) {
        std::ostringstream ss;
        ss << "ctp." << requestId;
        return ss.str();
    }
 
    inline virtual std::string api() const  {
        return "ctp";
    }

    inline virtual std::string userId() const {
        return user_id_;
    }

 protected:
    /** @brief 登陆的回调函数。*/
    virtual void on_login(const OperateStatus& ops){ }

    /** @brief 登出的回调函数。*/
    virtual void on_logout(const OperateStatus& ops){ }

    /** @brief tick数据到达回调函数。*/
    virtual void on_tick(const OperateStatus& ops, const TickData &tick) { }
    
    /** @brief 撤单回调 */
    virtual void on_cancel_order(const OperateStatus& ops, Order order) { }

    /** @brief 报单到达交易所回调 */
    virtual void on_order(const OperateStatus& ops, const Order &order) { }

    /** @brief 报单成交回调 */
    virtual void on_transaction(const Transaction &tans) { }

    /** @brief 合约查询回调 */
    virtual void on_contract(const Contract &contract) { }

    /** @brief 资金查询回调 */
    virtual void on_captial(const OperateStatus& ops, const Captial &cap) { }

    /** @brief 持仓查询回调 */
    virtual void on_position(const OperateStatus& ops, const Position &pos) { }

    //-------------------------------------------------------
 private:

	///投资者结算结果查询
    virtual void qrySettlementInfo(const char *broker_id, 
                                   const char *investor_id, 
                                   const char* trading_day,
                                   bool sync=false);
	///投资者结算结果确认
	virtual int settlementInfoConfirm(const char* brokerId, 
                                      const char* userId, 
                                      const int   requestId,
                                      bool sync=false);

    /// 注册前置地址
    virtual void registerFront(char *pszFrontAddress, bool sync=false);


	inline void notify() {
        if (locked_){
		    std::unique_lock <std::mutex> lock(syn_flag_);
		    locked_ = false;
		    m_cond.notify_all();
        }
	}

    inline void wait(bool towait) 
	{ 
		if(towait) 
		{ 
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
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();

	/// 登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

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

    inline int currentRequestId() { return request_id_; }

 private:
    int                     front_id_;	            ///< 前置编号
    int                     session_id_;	        ///< 会话编号
    TThostFtdcBrokerIDType  broker_id_;		        ///< 公司代码
    TThostFtdcUserIDType    user_id_;		        ///< 投资者代码

    static int              request_id_;            ///< 会话编号
    int                     order_ref_;             ///< 订单编号
    CThostFtdcTraderApi     *api_;                  ///< 请求实例

    std::mutex              syn_flag_;              ///< 同步
    std::atomic<bool>       locked_;                ///< 是否被锁住，用来决定解锁操作是否执行。
	std::condition_variable m_cond;					//条件变量

    LoggerPtr logger;
};

} /* QuantDigger */

#endif /* end of include guard: CTPTRADER_H */
