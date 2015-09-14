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
    /**
     * @brief  �µ�����
     *
     * @param info ��¼��Ϣ
     * @param sync �Ƿ�ͬ������
     */
    virtual int login(const LogonInfo &info, bool sync=false) = 0;

    /** @brief �˳��� */
    virtual int logout(bool sync=false) = 0;

    /** @brief �����ѯ��Լ */
	virtual int reqContract(Contract *c, bool sync=false) = 0;

    /** @brief ��ѯ��Լ�����±��� */
	virtual int reqTick(const Contract &c, bool sync=false) = 0;

    /** @brief �����ѯ�ʽ��˻� */
	virtual int reqCaptial(bool sync=false) = 0;

    /** @brief �����ѯ����ί��*/
	virtual int orderToday(bool sync=false) { }

    /** @brief �����ѯ���ճɽ�*/
	virtual int transToday(bool sync=false) { }

    /** @brief �����ѯͶ���ֲ߳� */
	virtual int reqPosition(const Contract &contract, bool sync=false) = 0;

    /** @brief �µ������ֻ�ƽ�֡� */
    virtual int order(const Order &order, bool sync=false) = 0;

    /** @brief ������������ */
	virtual int cancel_order(int orderSeq, bool sync=false) = 0;

    virtual std::string api() const = 0;

    virtual std::string userId() const = 0;

 protected:
    /** @brief ��½�Ļص�������*/
    virtual void on_login(const OperateStatus& ops) = 0;

    /** @brief �ǳ��Ļص�������*/
    virtual void on_logout(const OperateStatus& ops) = 0;


    /** @brief tick���ݵ���ص�������*/
    virtual void on_tick(const OperateStatus& ops, const TickData &tick) = 0;
    
    /** @brief �����ص� */
    virtual void on_cancel_order(const OperateStatus& ops, Order order) = 0;

    /** @brief �������ｻ�����ص� */
    virtual void on_order(const OperateStatus& ops, const Order &order) = 0;

    /** @brief �����ɽ��ص� */
    virtual void on_transaction(const Transaction &tans) = 0;

    /** @brief ��Լ��ѯ�ص� */
    virtual void on_contract(const Contract &contract) = 0;

    /** @brief �ʽ��ѯ�ص� */
    virtual void on_captial(const OperateStatus& ops, const Captial &cap) = 0;

    /** @brief �ֲֲ�ѯ�ص� */
    virtual void on_position(const OperateStatus& ops, const Position &pos) = 0;

 protected:
     void set_logined(bool b){
        logined_.store(b);
     };

 private:
    std::atomic<bool>   logined_;
};


} /* QuantDigger*/
#endif /* end of include guard: TRADER_H */
