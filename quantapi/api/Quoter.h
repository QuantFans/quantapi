/**
 * @file quoter.h
 * @brief 
 * @author wdj
 * @version 0.1
 * @date 2014-04-10
 */

#ifndef _QUOTER_H_

#define _QUOTER_H_
#include <vector>
#include <string>
#include <atomic>
#include "TradeDataStruct.h" 
namespace QuantDigger {
    
/**
 * @brief 行情查询发起类的基类。
 *
 * 不同的交易接口如恒生、CTP通过继承它来实现功能。
 * @note 同步标志为真时只有在单线程的时候才能正常工作。所以设置同步标志为真的时候需要一个而外的锁，避免并发调用。 
 */
class Quoter{
 public:
    Quoter() {
        set_logined(false);
    }
    virtual ~Quoter(){ }
    virtual void login(const char *broker_id, const char *user_id, const char *password, bool syn) = 0;
    virtual void logout(const char *broker_id, const char *user_id, bool syn) = 0 ;
    /** @brief 订阅合约品种 */
    virtual void subscribeMarketData(const std::vector<Contract> &instruments, bool syn) = 0;
    /** @brief 取消订阅合约品种 */
	virtual void unsubscribeMarketData(const std::vector<Contract> &instruments, bool syn) = 0;
 private:
    friend class QuoterCallBackBase;
    void set_logined(bool b){
        logined_.store(b);
    };

 private:
    std::atomic<bool>   logined_;
};

} /* QuantDigger */
#endif /* end of include guard: _QUOTER_H_ */
