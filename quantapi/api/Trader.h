/**
 * @file Trader.h
 * @brief 交易类接口
 * @author wdj
 * @version 0.1
 * @date 2014-05-04
 */

#ifndef TRADER_H 

#define TRADER_H
#include <atomic>
#include "TradeDataStruct.h" 
namespace QuantDigger {
/**
* @brief 交易发起类的基类。
*
* 不同的交易接口如恒生、CTP通过继承它来实现功能。
* @note 同步标志为真时只有在单线程的时候才能正常工作。所以设置同步标志为真的时候需要一个而外的锁，避免并发调用。 
*/
class Trader {
 public:
    Trader() {
        set_logined(false);
    }
    virtual ~Trader() { }
    virtual void login(const char *broker_id, const char *user_id, const char *password, bool syn) = 0;
    virtual void logout(const char *broker_id, const char *user_id, bool syn) = 0;
	///投资者结算结果查询
    virtual void qrySettlementInfo(const char *broker_id, 
                                   const char *investor_id, 
                                   const char* trading_day,
                                   bool syn) = 0;
	///投资者结算结果确认
	virtual void settlementInfoConfirm(bool syn) = 0;
	///请求查询合约
	virtual void qryInstrument(const Contract &c, bool syn) = 0;
    /// 查询合约的最新报价
	virtual void qryDepthMarketData(const Contract &c, bool syn) = 0;
	///请求查询资金账户
	virtual void qryTradingAccount(bool syn) = 0;
	///请求查询投资者持仓
	virtual void qryInvestorPosition(const char *instId, bool syn) = 0;
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
                             bool syn) = 0;
	///撤单操作请求
	virtual void orderAction(int orderSeq, bool syn) = 0;

    /// 注册前置地址
    virtual void registerFront(char *pszFrontAddress, bool syn) = 0;

 private:
    friend class TraderCallBackBase;
     void set_logined(bool b){
        logined_.store(b);
     };

 private:
    std::atomic<bool>   logined_;
};


} /* QuantDigger*/
#endif /* end of include guard: TRADER_H */
