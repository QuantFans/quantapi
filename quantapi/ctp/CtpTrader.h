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

namespace QuantApi {

/**
* @brief CTP������
*
* ������CTPʵ����ɣ�һ����������һ������ص���
* ��ͨ������ͬ������ʵ���ͻص�ʵ�������һ������
*/
class CtpTrader : public Trader, private CThostFtdcTraderSpi{
public:
   CtpTrader(char* trade_front);

   ~CtpTrader();

public:
    virtual int login(const LogonInfo &info, bool syn=true);
    virtual int logout(const LogonInfo &info,  bool syn);

    /** @brief �����ѯ��Լ */
	virtual int reqContract(Contract *c, bool syn=false);

    /// ��ѯ��Լ�����±���
	virtual int reqTick(const Contract &c, bool syn=false);

	///�����ѯ�ʽ��˻�
	virtual int reqCaptial(bool syn=false);

	///�����ѯͶ���ֲ߳�
	virtual int reqPosition(const char *instId, bool syn=false);


    /**
     * @brief  �µ�����
     *
     * @param order ί�к�Լ
     * @param syn �Ƿ�ͬ������
     */
    virtual int order(const Order &order, bool syn=false);

	///������������
	virtual int cancel_order(int orderSeq, bool syn=false);

    /**
     * @brief tick���ݵ���ص�������
     *
     * @param tick 
     */
    virtual void on_tick(const TickData &tick) const;
//
//    virtual void on_query() = 0;
//    virtual void on_contract() = 0;
//    virtual void on_captial() = 0;

//    virtual void query() = 0;

    virtual void on_cancel_order(Order order);

    virtual void on_order(Transaction trans);


	///Ͷ���߽�������ѯ
    virtual void qrySettlementInfo(const char *broker_id, 
                                   const char *investor_id, 
                                   const char* trading_day,
                                   bool syn=false);
	///Ͷ���߽�����ȷ��
	virtual void settlementInfoConfirm(bool syn=false);


    /// ע��ǰ�õ�ַ
    virtual void registerFront(char *pszFrontAddress, bool syn=false);

    inline void synUnlock() { if(locked_) syn_flag_.unlock(); }
    inline void wait(bool towait) { if(towait) { syn_flag_.lock(); syn_flag_.unlock(); }}

    //-------------------------------------------------------
 private:

    /// @todo onrspqry...
    void ReqQrySettlementInfo(const char *broker_id, 
                              const char *investor_id, 
                              const char* trading_day);

	void ReqSettlementInfoConfirm();


//------------------------------------------------------

    inline void set_front_id(int id) { 
        front_id_ = id;
    }

    inline void set_session_id(int id) { 
        session_id_ = id;
    }
    inline int session_id() {
        return session_id_;
    }
    inline int front_id(int id) {
        return front_id_;
    }

private:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	/// ��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ���߽�����ȷ����Ӧ
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    /// ���µĺ�Լ����
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ�ʽ��˻���Ӧ
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���ֲ߳���Ӧ
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������������Ӧ
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	virtual void OnFrontDisconnected(int nReason);
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///����¼��������Ӧ
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///����֪ͨ
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);
	///�ɽ�֪ͨ
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

	/// �Ƿ��յ��ɹ�����Ӧ
	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);


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
    int                     request_id_;            ///< �Ự���
    std::mutex              syn_flag_;              ///< ͬ���ź�
    std::atomic<bool>       locked_;                 ///< �Ƿ���ס�������������������Ƿ�ִ�С�

};

} /* QuantDigger */

#endif /* end of include guard: CTPTRADER_H */
