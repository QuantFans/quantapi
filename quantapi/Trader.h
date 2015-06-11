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

    virtual int login(const LogonInfo &info, bool syn) = 0;
    virtual int logout(const LogonInfo &info,  bool syn) = 0 ;
	virtual int reqContract(Contract *c, bool syn=false) = 0;
//    virtual void order() = 0;
//    virtual void cancel_order() = 0;
//    virtual void query() = 0;
//    virtual void req_tick() = 0;
//    virtual void req_position() = 0;
//    virtual void req_contract() = 0;
//    virtual void req_captial() = 0;
//
//    virtual void on_query() = 0;
//    virtual void on_tick() = 0;
//    virtual void on_contract() = 0;
//    virtual void on_captial() = 0;
//    virtual void on_order() = 0;
//    virtual void on_cancel_order() = 0;

 protected:
     void set_logined(bool b){
        logined_.store(b);
     };

 private:
    std::atomic<bool>   logined_;
};


} /* QuantDigger*/
#endif /* end of include guard: TRADER_H */
