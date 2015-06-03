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
 * @brief �����ѯ������Ļ��ࡣ
 *
 * ��ͬ�Ľ��׽ӿ��������CTPͨ���̳�����ʵ�ֹ��ܡ�
 * @note ͬ����־Ϊ��ʱֻ���ڵ��̵߳�ʱ�����������������������ͬ����־Ϊ���ʱ����Ҫһ��������������Ⲣ�����á� 
 */
class Quoter{
 public:
    Quoter() {
        set_logined(false);
    }
    virtual ~Quoter(){ }
    virtual void login(const char *broker_id, const char *user_id, const char *password, bool syn) = 0;
    virtual void logout(const char *broker_id, const char *user_id, bool syn) = 0 ;
    /** @brief ���ĺ�ԼƷ�� */
    virtual void subscribeMarketData(const std::vector<Contract> &instruments, bool syn) = 0;
    /** @brief ȡ�����ĺ�ԼƷ�� */
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
