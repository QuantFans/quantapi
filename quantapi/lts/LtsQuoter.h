/**
 * @file LtsQuoter.h
 * @brief 
 * @author HonePhy
 * Copyright () 2014-2020 QuantDigger. All rights reserved.
 * @chanege-log	 	
		2015-06-14 ����quantapi�ӿڵĵ������޸�
 * @version 0.1
 * @date 2015-04-16
 */
 
#ifndef QUANTDIGGER_LTS_LTSQUOTER_H
#define QUANTDIGGER_LTS_LTSQUOTER_H

#include <atomic>
#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>
#include <quantapi/Quoter.h>
#include <quantapi/datastruct.h>
#include "SecurityFtdcMdApi.h"

namespace QuantApi {

class LtsQuoter : public Quoter, private CSecurityFtdcMdSpi{
 
 public:
    LtsQuoter(char *trade_front);
    virtual ~LtsQuoter();

 public:

	
	/** @brief �ʺŵ�¼�� */
    virtual int login(const LogonInfo &info, bool syn);
	
	/** @brief �ʺŵ�¼�� */
    virtual int logout(const LogonInfo &info, bool syn);
	
	/**
     * @brief ����tick���ݡ�    
     *
     * @param contracts ��Լ���ϡ�
     * @param sync �Ƿ�ͬ�����á�
     *
     * @return 
    */
    virtual int reqTick(const std::vector<Contract> &contracts, bool syn);

    /**
     * @brief ȡ��tick���ݶ��ġ�
     *
     * @param contracts ��Լ���ϡ�
     * @param sync �Ƿ�ͬ�����á�
     *
     * @return 
     */
	virtual int unReqTick(const std::vector<Contract> &contracts, bool syn);
    
    /**
     * @brief ��ǰ����
     *
     * @note ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ����ա�
     */
    virtual std::string getTradingDay()  { return api_->GetTradingDay(); }

protected:

    /** @brief tick���ݵ���ص�������*/
    virtual void on_tick(const TickData &tick) { }	

private:
    
	inline void wait(bool towait) { 
		if(towait) { 
			std::unique_lock<std::mutex> lock(syn_flag_);
			locked_ = true;
			m_cond.wait(lock);
		}
	}

	inline void notify() {
		std::unique_lock <std::mutex> lock(syn_flag_);
		locked_ = false;
		m_cond.notify_all();
	}
	
	inline int nextRequestId() { return ++request_id_; }
	
	inline void set_front_id(int id) { front_id_ = id; }
    inline void set_session_id(int id) { session_id_ = id; }
    inline int session_id() { return session_id_; }
    inline int front_id(int id) { return front_id_; }
	
	virtual void registerFront(char *pszFrontAddress, bool syn);
	
	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
	///@remark RegisterNameServer������RegisterFront
	void RegisterNameServer(char *pszNsAddress) { };

    
	// ---------------------- �ص����� ------------------------------
	
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse);
	

	///��¼������Ӧ
	virtual void OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin,
                                CSecurityFtdcRspInfoField *pRspInfo, 
                                int nRequestID, 
                                bool bIsLast);

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, 
                                 CSecurityFtdcRspInfoField *pRspInfo, 
                                 int nRequestID, 
                                 bool bIsLast);

	///����Ӧ��
	virtual void OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������Ӧ��
	virtual void OnRspSubMarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, 
                                    CSecurityFtdcRspInfoField *pRspInfo, 
                                    int nRequestID, 
                                    bool bIsLast);

	///ȡ����������Ӧ��
	virtual void OnRspUnSubMarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument,
                                      CSecurityFtdcRspInfoField *pRspInfo, 
                                      int nRequestID, 
                                      bool bIsLast);

	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CSecurityFtdcDepthMarketDataField *pDepthMarketData);
	
	/// �Ƿ��յ��ɹ�����Ӧ
	bool IsErrorRspInfo(CSecurityFtdcRspInfoField *pRspInfo);

 private:
    int                 front_id_;	            ///< ǰ�ñ��
    int                 session_id_;	        ///< �Ự���
	
    CSecurityFtdcMdApi  *api_;                  ///< ����ʵ��
    int                 request_id_;            ///< �Ự���

	std::mutex              syn_flag_;              ///< ͬ��
	std::atomic<bool>       locked_;                ///< �Ƿ���ס�������������������Ƿ�ִ�С�
	std::condition_variable m_cond;					//��������
};


} /* QuantDigger */

#endif