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
#include <condition_variable>
#include <sstream>
#include <log4cxx/logger.h>
#include "../Trader.h" 
#include "ThostFtdcUserApiDataType.h" 
#include "ThostFtdcTraderApi.h" 

using namespace log4cxx;
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

    /**
     * @brief  �µ�����
     *
     * @param info ��¼��Ϣ
     * @param sync �Ƿ�ͬ������
     */
    virtual int login(const LogonInfo &info, bool sync=false);

    /** @brief �˳��� */
    virtual int logout(bool sync=false);

    /** @brief �����ѯ��Լ */
	virtual int reqContract(Contract *c, bool sync=false);

    /** @brief ��ѯ��Լ�����±��� */
	virtual int reqTick(const Contract &c, bool sync=false);

    /** @brief �����ѯ�ʽ��˻� */
	virtual int reqCaptial(bool sync=false);

    /** @brief �����ѯͶ���ֲ߳� */
	virtual int reqPosition(const Contract &contract, bool sync=false);

    /** @brief �µ������ֻ�ƽ�֡� */
    virtual int order(const Order &order, bool sync=false);

    /** @brief ������������ */
	virtual int cancel_order(const Order& order, 
                             bool sync=false);

    inline virtual std::string nextRequestId() {
        std::ostringstream ss;
        ss << "ctp." << (++request_id_);
        return ss.str();
    }

    inline std::string requestId2str(int requestId) {
        std::ostringstream ss;
        ss << "ctp." << requestId;
        return ss.str();
    }
 
    inline virtual std::string api() const  {
        return "ctp";
    }

    inline virtual std::string userId() const {
        return user_id_;
    }

 protected:
    /** @brief ��½�Ļص�������*/
    virtual void on_login(const OperateStatus& ops){ }

    /** @brief �ǳ��Ļص�������*/
    virtual void on_logout(const OperateStatus& ops){ }

    /** @brief tick���ݵ���ص�������*/
    virtual void on_tick(const OperateStatus& ops, const TickData &tick) { }
    
    /** @brief �����ص� */
    virtual void on_cancel_order(const OperateStatus& ops, Order order) { }

    /** @brief �������ｻ�����ص� */
    virtual void on_order(const OperateStatus& ops, const Order &order) { }

    /** @brief �����ɽ��ص� */
    virtual void on_transaction(const Transaction &tans) { }

    /** @brief ��Լ��ѯ�ص� */
    virtual void on_contract(const Contract &contract) { }

    /** @brief �ʽ��ѯ�ص� */
    virtual void on_captial(const OperateStatus& ops, const Captial &cap) { }

    /** @brief �ֲֲ�ѯ�ص� */
    virtual void on_position(const OperateStatus& ops, const Position &pos) { }

    //-------------------------------------------------------
 private:

	///Ͷ���߽�������ѯ
    virtual void qrySettlementInfo(const char *broker_id, 
                                   const char *investor_id, 
                                   const char* trading_day,
                                   bool sync=false);
	///Ͷ���߽�����ȷ��
	virtual int settlementInfoConfirm(const char* brokerId, 
                                      const char* userId, 
                                      const int   requestId,
                                      bool sync=false);

    /// ע��ǰ�õ�ַ
    virtual void registerFront(char *pszFrontAddress, bool sync=false);


	inline void notify() {
        if (locked_){
		    std::unique_lock <std::mutex> lock(syn_flag_);
		    locked_ = false;
		    m_cond.notify_all();
        }
	}

    inline void wait(bool towait) 
	{ 
		if(towait) 
		{ 
			std::unique_lock<std::mutex> lock(syn_flag_);
			locked_ = true;
			m_cond.wait(lock);
		}
	}

    inline void set_front_id(int id) { front_id_ = id; }

    inline void set_session_id(int id) { session_id_ = id; }

    inline int session_id() { return session_id_; }

    inline int front_id(int id) { return front_id_; }

private:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	/// ��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

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

    inline int currentRequestId() { return request_id_; }

 private:
    int                     front_id_;	            ///< ǰ�ñ��
    int                     session_id_;	        ///< �Ự���
    TThostFtdcBrokerIDType  broker_id_;		        ///< ��˾����
    TThostFtdcUserIDType    user_id_;		        ///< Ͷ���ߴ���

    static int              request_id_;            ///< �Ự���
    int                     order_ref_;             ///< �������
    CThostFtdcTraderApi     *api_;                  ///< ����ʵ��

    std::mutex              syn_flag_;              ///< ͬ��
    std::atomic<bool>       locked_;                ///< �Ƿ���ס�������������������Ƿ�ִ�С�
	std::condition_variable m_cond;					//��������

    LoggerPtr logger;
};

} /* QuantDigger */

#endif /* end of include guard: CTPTRADER_H */
