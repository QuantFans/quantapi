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
#include "TradeDataStruct.h" 
namespace QuantDigger {
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
    virtual void login(const char *broker_id, const char *user_id, const char *password, bool syn) = 0;
    virtual void logout(const char *broker_id, const char *user_id, bool syn) = 0;
	///Ͷ���߽�������ѯ
    virtual void qrySettlementInfo(const char *broker_id, 
                                   const char *investor_id, 
                                   const char* trading_day,
                                   bool syn) = 0;
	///Ͷ���߽�����ȷ��
	virtual void settlementInfoConfirm(bool syn) = 0;
	///�����ѯ��Լ
	virtual void qryInstrument(const Contract &c, bool syn) = 0;
    /// ��ѯ��Լ�����±���
	virtual void qryDepthMarketData(const Contract &c, bool syn) = 0;
	///�����ѯ�ʽ��˻�
	virtual void qryTradingAccount(bool syn) = 0;
	///�����ѯͶ���ֲ߳�
	virtual void qryInvestorPosition(const char *instId, bool syn) = 0;
    /**
     * @brief  �µ�����
     *
     * @param instId ��Լ���
     * @param dir ���׷���
     * @param kpp ��ƽ�ֱ�־
     * @param price �۸�
     * @param vol �ɽ���
     */
    virtual void orderInsert(const char *instId, 
                             char dir, 
                             const char *kpp, 
                             double price,   
                             int vol,
                             bool syn) = 0;
	///������������
	virtual void orderAction(int orderSeq, bool syn) = 0;

    /// ע��ǰ�õ�ַ
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
