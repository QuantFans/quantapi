/**
 * @file ctptrader.h
 * @brief 
 * @author wdj
 * @version 0.1
 * @date 2014-04-09
 */
#ifndef CTPTRADER_H

#define CTPTRADER_H
#include <atomic>
#include <mutex>
#include "../Trader.h" 
#include "ThostFtdcUserApiDataType.h" 
#include "ThostFtdcTraderApi.h" 

namespace QuantDigger {
class CtpTraderCallBack;

/**
* @brief CTP������
*
* ������CTPʵ����ɣ�һ����������һ������ص���
* ��ͨ������ͬ������ʵ���ͻص�ʵ�������һ������
*/
class CtpTrader : public Trader {
public:
   CtpTrader(char* trade_front, CtpTraderCallBack *cbk_object);

   ~CtpTrader();

public:
    virtual void login(const char *broker_id, const char *user_id, const char *password, bool syn=false);
    virtual void logout(const char *broker_id, const char *user_id, bool syn=false);

	///Ͷ���߽�������ѯ
    virtual void qrySettlementInfo(const char *broker_id, 
                                   const char *investor_id, 
                                   const char* trading_day,
                                   bool syn=false);
	///Ͷ���߽�����ȷ��
	virtual void settlementInfoConfirm(bool syn=false);

	///�����ѯ��Լ
	virtual void qryInstrument(const Contract &c, bool syn=false);

    /// ��ѯ��Լ�����±���
	virtual void qryDepthMarketData(const Contract &c, bool syn=false);

	///�����ѯ�ʽ��˻�
	virtual void qryTradingAccount(bool syn=false);

	///�����ѯͶ���ֲ߳�
	virtual void qryInvestorPosition(const char *instId, bool syn=false);
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
                             bool syn=false);
	///������������
	virtual void orderAction(int orderSeq, bool syn=false);

    /// ע��ǰ�õ�ַ
    virtual void registerFront(char *pszFrontAddress, bool syn=false);

    inline void synUnlock() { if(locked_) syn_flag_.unlock(); }
    inline void wait(bool towait) { if(towait) { syn_flag_.lock(); syn_flag_.unlock(); }}

private:
	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	void init() { api_->Init(); }

	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	int join() { return api_->Join(); }

	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	void release() { api_->Release(); }

    // ����ΪCTP�ж�Ӧ�ĺ�������
	void ReqUserLogin(const char *broker_id, const char *userId, const char *passwd);

	void ReqUserLogout(const char *broker_id, const char *user_id);
    /// @todo onrspqry...
    void ReqQrySettlementInfo(const char *broker_id, 
                              const char *investor_id, 
                              const char* trading_day);

	void ReqSettlementInfoConfirm();

	void ReqQryInstrument(const char *instId);

	void ReqQryDepthMarketData(const char *instId);

	void ReqQryTradingAccount();

	void ReqQryInvestorPosition(const char *instId);

    void ReqOrderInsert(const char *instId, 
                        char dir, 
                        const char *kpp, 
                        double price,   
                        int vol);

	void ReqOrderAction(int orderSeq);
    void RegisterFront(char *pszFrontAddress);

 protected:
    inline void synLock() { syn_flag_.lock(); locked_ = true;}
    inline int nextRequestId() { return ++request_id_; }
    void PrintOrders();
    void PrintTrades();

 public:
    int                     front_id_;	            ///< ǰ�ñ��
    int                     session_id_;	        ///< �Ự���
 private:
    TThostFtdcBrokerIDType  broker_id_;		        ///< ��˾����
    TThostFtdcUserIDType    user_id_;		        ///< Ͷ���ߴ���
    int                     order_ref_;             ///< �������
    CThostFtdcTraderApi     *api_;                  ///< ����ʵ��
    CtpTraderCallBack       *spi_;                  ///< �ص�ʵ��
    int                     request_id_;            ///< �Ự���
    std::mutex              syn_flag_;              ///< ͬ���ź�
    std::atomic<bool>       locked_;                 ///< �Ƿ���ס�������������������Ƿ�ִ�С�

};

} /* QuantDigger */

#endif /* end of include guard: CTPTRADER_H */
