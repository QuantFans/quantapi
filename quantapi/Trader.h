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
#include "datastruct.h" 
namespace QuantApi {
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
    /**
     * @brief  下单请求
     *
     * @param info 登录信息
     * @param sync 是否同步调用
     */
    virtual int login(const LogonInfo &info, bool sync=true) = 0;

    /** @brief 退出。 */
    virtual int logout(const LogonInfo &info,  bool sync) = 0;

    /** @brief 请求查询合约 */
	virtual int reqContract(Contract *c, bool sync=false) = 0;

    /** @brief 查询合约的最新报价 */
	virtual int reqTick(const Contract &c, bool sync=false) = 0;

    /** @brief 请求查询资金账户 */
	virtual int reqCaptial(bool sync=false) = 0;

    /** @brief 请求查询投资者持仓 */
	virtual int reqPosition(const Contract &contract, bool sync=false) = 0;

    /** @brief 下单，开仓或平仓。 */
    virtual int order(const Order &order, bool sync=false) = 0;

    /** @brief 撤单操作请求 */
	virtual int cancel_order(int orderSeq, bool sync=false) = 0;

 protected:

    /** @brief tick数据到达回调函数。*/
    virtual void on_tick(const TickData &tick) = 0;
    
    /** @brief 撤单回调 */
    virtual void on_cancel_order(Order order) = 0;

    /** @brief 报单到达交易所回调 */
    virtual void on_order(const Order &order) = 0;

    /** @brief 报单成交回调 */
    virtual void on_transaction(const Transaction &tans) = 0;

    /** @brief 合约查询回调 */
    virtual void on_contract(const Contract &contract) = 0;

    /** @brief 资金查询回调 */
    virtual void on_captial(const Captial &cap) = 0;

    /** @brief 持仓查询回调 */
    virtual void on_position(const Position &pos) = 0;

 protected:
     void set_logined(bool b){
        logined_.store(b);
     };

 private:
    std::atomic<bool>   logined_;
};


} /* QuantDigger*/
#endif /* end of include guard: TRADER_H */
