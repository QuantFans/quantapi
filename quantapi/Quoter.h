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
#include "datastruct.h" 
namespace QuantApi {
    
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
    /** @brief 帐号登录。 */
    virtual int login(const LogonInfo &info, bool sync=true) = 0;
    /** @brief 帐号退出。 */
    virtual int logout(const LogonInfo &info,  bool sync) = 0;
     
    /**
     * @brief 订阅tick数据。    
     *
     * @param instruments 合约集合。
     * @param sync 是否同步调用。
     *
     * @return 
     */
    virtual int reqTick(const std::vector<Contract> &instruments, bool sync) = 0;

    /**
     * @brief 取消tick数据订阅。
     *
     * @param instruments 合约结合。
     * @param sync 是否同步调用。
     *
     * @return 
     */
	virtual int unReqTick(const std::vector<Contract> &instruments, bool sync) = 0;

    /**
     * @brief tick数据到达回调函数。
     *
     * @param tick 
     */
    virtual void on_tick(const TickData &tick) const = 0;
    /**
     * @brief 当前日期
     *
     * @note 只有登录成功后,才能得到正确的交易日。
     * @return 
     */
    virtual std::string getTradingDay() = 0;


 private:
    void set_logined(bool b){
        logined_.store(b);
    };

 private:
    std::atomic<bool>   logined_;
};

} /*  QuantApi */
#endif /* end of include guard: _QUOTER_H_ */
