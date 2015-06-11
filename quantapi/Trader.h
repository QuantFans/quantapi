/**
 * @file Trader.h
 * @brief ������ӿ�
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
* @brief ���׷�����Ļ��ࡣ
*
* ��ͬ�Ľ��׽ӿ��������CTPͨ���̳�����ʵ�ֹ��ܡ�
* @note ͬ����־Ϊ��ʱֻ���ڵ��̵߳�ʱ�����������������������ͬ����־Ϊ���ʱ����Ҫһ��������������Ⲣ�����á� 
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
