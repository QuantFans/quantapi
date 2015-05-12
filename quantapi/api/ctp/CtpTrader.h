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

namespace QuantDigger {
class CtpTraderCallBack;

/**
* @brief CTP交易类
*
* 由两个CTP实例组成，一个发起请求，一个处理回调。
* 可通过锁来同步请求实例和回调实例来完成一个操作
*/
class CtpTrader : public Trader {
public:
   CtpTrader(char* trade_front, CtpTraderCallBack *cbk_object);

   ~CtpTrader();

public:
    virtual void login(const char *broker_id, const char *user_id, const char *password, bool syn=false);
    virtual void logout(const char *broker_id, const char *user_id, bool syn=false);

	///投资者结算结果查询
    virtual void qrySettlementInfo(const char *broker_id, 
                                   const char *investor_id, 
                                   const char* trading_day,
                                   bool syn=false);
	///投资者结算结果确认
	virtual void settlementInfoConfirm(bool syn=false);

	///请求查询合约
	virtual void qryInstrument(const Contract &c, bool syn=false);

    /// 查询合约的最新报价
	virtual void qryDepthMarketData(const Contract &c, bool syn=false);

	///请求查询资金账户
	virtual void qryTradingAccount(bool syn=false);

	///请求查询投资者持仓
	virtual void qryInvestorPosition(const char *instId, bool syn=false);
    /**
     * @brief  下单请求
     *
     * @param instId 合约编号
     * @param dir 交易方向
     * @param kpp 开平仓标志
     * @param price 价格
     * @param vol 成交量
     */
    virtual void orderInsert(const char *instId, 
                             char dir, 
                             const char *kpp, 
                             double price,   
                             int vol,
                             bool syn=false);
	///报单操作请求
	virtual void orderAction(int orderSeq, bool syn=false);

    /// 注册前置地址
    virtual void registerFront(char *pszFrontAddress, bool syn=false);

    inline void synUnlock() { if(locked_) syn_flag_.unlock(); }
    inline void wait(bool towait) { if(towait) { syn_flag_.lock(); syn_flag_.unlock(); }}

private:
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	void init() { api_->Init(); }

	///等待接口线程结束运行
	///@return 线程退出代码
	int join() { return api_->Join(); }

	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	void release() { api_->Release(); }

    // 以下为CTP中对应的函数集合
	void ReqUserLogin(const char *broker_id, const char *userId, const char *passwd);

	void ReqUserLogout(const char *broker_id, const char *user_id);
    /// @todo onrspqry...
    void ReqQrySettlementInfo(const char *broker_id, 
                              const char *investor_id, 
                              const char* trading_day);

	void ReqSettlementInfoConfirm();

	void ReqQryInstrument(const char *instId);

	void ReqQryDepthMarketData(const char *instId);

	void ReqQryTradingAccount();

	void ReqQryInvestorPosition(const char *instId);

    void ReqOrderInsert(const char *instId, 
                        char dir, 
                        const char *kpp, 
                        double price,   
                        int vol);

	void ReqOrderAction(int orderSeq);
    void RegisterFront(char *pszFrontAddress);

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
    CtpTraderCallBack       *spi_;                  ///< 回调实例
    int                     request_id_;            ///< 会话编号
    std::mutex              syn_flag_;              ///< 同步信号
    std::atomic<bool>       locked_;                 ///< 是否被锁住，用来决定解锁操作是否执行。

};

} /* QuantDigger */

#endif /* end of include guard: CTPTRADER_H */
