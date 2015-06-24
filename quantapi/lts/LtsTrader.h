/**
 * @file LtsTrader.h
 * @brief 
 * @author HonePhy
 * Copyright () 2014-2020 QuantDigger. All rights reserved.
 * @chanege-log	 	
		2015-06-14 ����quantapi�ӿڵĵ������޸�
 * @version 0.1
 * @date 2015-04-10
 */
#ifndef LTSTRADER_H

#define LTSTRADER_H
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <quantapi/Trader.h>
#include "SecurityFtdcUserApiDataType.h"
#include "SecurityFtdcTraderApi.h"
#include "SecurityFtdcUserApiStruct.h"

namespace QuantApi {
	

class LtsTrader : public Trader, private CSecurityFtdcTraderSpi {
public:
	LtsTrader(char* trade_front);

	~LtsTrader();

public:
	virtual int login(const LogonInfo &info, bool syn=false);
	
	virtual int logout(const LogonInfo &info, bool syn=false);

	///�����ѯ��Լ
	virtual int reqContract(const Contract &c, bool syn=false);

	///��ѯ��Լ�����±���
	virtual int reqTick(const Contract &c, bool syn=false);

	///�����ѯ�ʽ��˻�
	virtual int reqCaptial(bool syn=false);

	///�����ѯͶ���ֲ߳�
	virtual int reqPosition(const Contract &contract, bool syn = false);

	/**
     * @brief  �µ�����,���ֻ�ƽ��
     */
	virtual int order(const Order &order, bool syn=false);

	/** @brief ������������ */
	virtual int cancel_order(int orderSeq, bool sync=false);

 protected:
    /** @brief tick���ݵ���ص�������*/
    virtual void on_tick(const TickData &tick) { }
    
    /** @brief �����ص� */
    virtual void on_cancel_order(Order order) { }

    /** @brief �������ｻ�����ص� */
    virtual void on_order(const Order &order) { }

    /** @brief �����ɽ��ص� */
    virtual void on_transaction(const Transaction &tans) { }

    /** @brief ��Լ��ѯ�ص� */
    virtual void on_contract(const Contract &contract) { }

    /** @brief �ʽ��ѯ�ص� */
    virtual void on_captial(const Captial &cap) { }

    /** @brief �ֲֲ�ѯ�ص� */
    virtual void on_position(const Position &pos) { }

    //----------------------���Ϸ����ɻص��̵߳��ã���Ϊģ�淽����������������̳���д��Ϊ��ͬ��;----------------------------	

private:

	///Ͷ���߽�������ѯ
	virtual void qrySettlementInfo(const char *broker_id,
								   const char *investor_id,
								   const char *trading_day,
								   bool syn=false);
	///Ͷ���߽�����ȷ��
	virtual void settlementInfoConfirm(bool syn=false);

	///ע��ǰ�õ�ַ
	virtual void registerFront(char *pszFrontAdderss, bool syn=false);

//	inline void synUnlock() { if(locked_) syn_flag_.unlock();}
	
//	inline void synLock() { syn_flag_.lock(); locked_ = true; }
	
	inline int nextRequestId() { return ++request_id_; }
	
	inline void notify() {
		std::unique_lock <std::mutex> lock(syn_flag_);
		locked_ = false;
		m_cond.notify_all();
	}

	inline void wait(bool towait) { 
		if(towait) { 
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
	//----------------------�̳���CSecurityFtdcTraderSpi�Ļص�����ʵ��-----
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	virtual void OnFrontDisconnected(int nReason);
	
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	virtual void OnHeartBeatWarning(int nTimeLapse);
	
	///����Ӧ��
	virtual void OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);	
	
	/// ��¼������Ӧ
	virtual void OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����¼��������Ӧ
	virtual void OnRspOrderInsert(CSecurityFtdcInputOrderField *pInputOrder, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///��������������Ӧ
	virtual void OnRspOrderAction(CSecurityFtdcInputOrderActionField *pInputOrderAction, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CSecurityFtdcInstrumentField *pInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���ֲ߳���Ӧ
	virtual void OnRspQryInvestorPosition(CSecurityFtdcInvestorPositionField *pInvestorPosition, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///�����ѯ�ʽ��˻���Ӧ
	virtual void OnRspQryTradingAccount(CSecurityFtdcTradingAccountField *pTradingAccount, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///Ͷ���߽�����ȷ����Ӧ
	//virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
    ///�����ѯ������Ӧ
	virtual void OnRspQryDepthMarketData(CSecurityFtdcDepthMarketDataField *pDepthMarketData, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����֪ͨ
	virtual void OnRtnOrder(CSecurityFtdcOrderField *pOrder);
	///�ɽ�֪ͨ
	virtual void OnRtnTrade(CSecurityFtdcTradeField *pTrade);

	/// �Ƿ��յ��ɹ�����Ӧ
	bool IsErrorRspInfo(CSecurityFtdcRspInfoField *pRspInfo);

private:
	int							front_id_;			///< ǰ�ñ��
	int							session_id_;		///< �Ự���

	TSecurityFtdcBrokerIDType	broker_id_;			///< ��˾����
	TSecurityFtdcInvestorIDType	user_id_;		///< Ͷ���ߴ���
	int							order_ref_;			///< �������
	CSecurityFtdcTraderApi		*api_;				///< ����ʵ��
	int                     	request_id_;            ///< �Ự���

	std::mutex              syn_flag_;              ///< ͬ��
	std::atomic<bool>       locked_;                ///< �Ƿ���ס�������������������Ƿ�ִ�С�
	std::condition_variable m_cond;					//��������
};	

} /* QuantDigger */

#endif /* end of include guard: LTSTRADER_H */
