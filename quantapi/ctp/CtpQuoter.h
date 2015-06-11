/**
 * @file ctpquoter.h
 * @brief 
 * @author wdj
 * @version 0.1
 * @date 2014-04-09
 */

#ifndef _CTPQUOTER_H

#define _CTPQUOTER_H
#include <atomic>
#include <vector>
#include <string>
#include <mutex>
#include "../Quoter.h" 
#include "../datastruct.h"
#include "ThostFtdcMdApi.h" 
namespace QuantApi {
class CtpQuoterCallBack;

/**
* @brief CTP�����ѯ��
*
* ������CTPʵ����ɣ�һ����������һ������ص���
* ��ͨ������ͬ������ʵ���ͻص�ʵ�������һ������
*/
class CtpQuoter : public Quoter, private CThostFtdcMdSpi{
 public:
    CtpQuoter(char *trade_front);
    virtual ~CtpQuoter();

 public:

    /** @brief �ʺŵ�¼�� */
    virtual int login(const LogonInfo &info, bool sync=true);

    /** @brief �ʺ��˳��� */
    virtual int logout(const LogonInfo &info,  bool sync);
     
    /**
     * @brief ����tick���ݡ�    
     *
     * @param instruments ��Լ���ϡ�
     * @param sync �Ƿ�ͬ�����á�
     *
     * @return 
     */
    virtual int reqTick(const std::vector<Contract> &instruments, bool sync);

    /**
     * @brief ȡ��tick���ݶ��ġ�
     *
     * @param instruments ��Լ��ϡ�
     * @param sync �Ƿ�ͬ�����á�
     *
     * @return 
     */
	virtual int unReqTick(const std::vector<Contract> &instruments, bool sync);

    /**
     * @brief tick���ݵ���ص�������
     *
     * @param tick 
     */
    virtual void on_tick(const TickData &tick) const;
    /**
     * @brief ��ǰ����
     *
     * @note ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ����ա�
     * @return 
     */
    virtual std::string getTradingDay()  { api_->GetTradingDay(); }
        

 private:

    inline void synLock() { syn_flag_.lock(); locked_ = true;}
    inline void synUnlock() { if(locked_) { syn_flag_.unlock(); locked_ = false; }}
    inline void wait(bool towait) { if(towait) { synLock(); synUnlock(); }}

	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
	///@remark RegisterNameServer������RegisterFront
	void RegisterNameServer(char *pszNsAddress) { };

	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
	void registerFront(char *pszFrontAddress, bool sync);
	
    inline int nextRequestId() { return ++request_id_; }

 private:
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
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                                CThostFtdcRspInfoField *pRspInfo, 
                                int nRequestID, 
                                bool bIsLast);

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, 
                                 CThostFtdcRspInfoField *pRspInfo, 
                                 int nRequestID, 
                                 bool bIsLast);

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������Ӧ��
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
                                    CThostFtdcRspInfoField *pRspInfo, 
                                    int nRequestID, 
                                    bool bIsLast);

	///ȡ����������Ӧ��
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                      CThostFtdcRspInfoField *pRspInfo, 
                                      int nRequestID, 
                                      bool bIsLast);

	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

 protected:

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


public:
    /**
     * @brief �Ƿ��Ǵ���Ļص���Ӧ��
     *
     * ����Ǵ���ģ����������ԭ��
     */
	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
private:

    TThostFtdcBrokerIDType broker_id_;
    TThostFtdcUserIDType user_id_;

 public:
    int                 front_id_;	            ///< ǰ�ñ��
    int                 session_id_;	        ///< �Ự���
 private:
    CThostFtdcMdApi     *api_;                  ///< ����ʵ��
    int                 request_id_;            ///< �Ự���
    std::mutex          syn_flag_;              ///< ��ص���ͬ���źš�
    std::atomic<bool>   locked_;                 ///< �Ƿ���ס�������������������Ƿ�ִ�С�
};
    
} /* QuantDigger */
#endif 
