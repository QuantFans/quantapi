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
    /** @brief �ʺŵ�¼�� */
    virtual int login(const LogonInfo &info, bool sync=true) = 0;
    /** @brief �ʺ��˳��� */
    virtual int logout(const LogonInfo &info,  bool sync) = 0;
     
    /**
     * @brief ����tick���ݡ�    
     *
     * @param instruments ��Լ���ϡ�
     * @param sync �Ƿ�ͬ�����á�
     *
     * @return 
     */
    virtual int reqTick(const std::vector<Contract> &instruments, bool sync) = 0;

    /**
     * @brief ȡ��tick���ݶ��ġ�
     *
     * @param instruments ��Լ��ϡ�
     * @param sync �Ƿ�ͬ�����á�
     *
     * @return 
     */
	virtual int unReqTick(const std::vector<Contract> &instruments, bool sync) = 0;

    /**
     * @brief tick���ݵ���ص�������
     *
     * @param tick 
     */
    virtual void on_tick(const TickData &tick) const = 0;
    /**
     * @brief ��ǰ����
     *
     * @note ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ����ա�
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
