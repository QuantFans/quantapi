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
#include "../TradeDataStruct.h"
#include "ThostFtdcMdApi.h" 
namespace QuantDigger {
class CtpQuoterCallBack;

/**
* @brief CTP�����ѯ��
*
* ������CTPʵ����ɣ�һ����������һ������ص���
* ��ͨ������ͬ������ʵ���ͻص�ʵ�������һ������
*/
class CtpQuoter : public Quoter{
 public:
    CtpQuoter(char *trade_front, CtpQuoterCallBack *cbk_object);
    virtual ~CtpQuoter();

 public:
	virtual void registerFront(char *pszFrontAddress, bool syn);
    virtual void login(const char *broker_id, const char *user_id, const char *password, bool syn);
    virtual void logout(const char *broker_id, const char *user_id, bool syn);
    virtual void subscribeMarketData(const std::vector<Contract> &instruments, bool syn);
	virtual void unsubscribeMarketData(const std::vector<Contract> &instruments, bool syn);
        
    inline void synUnlock() { if(locked_) { syn_flag_.unlock(); locked_ = false; }}
    inline void wait(bool towait) { if(towait) { synLock(); synUnlock(); }}
 private:

    inline void synLock() { syn_flag_.lock(); locked_ = true;}

	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	void init() { api_->Init(); }
	
	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	int join() { return api_->Join(); }

	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	void release() { api_->Release(); }
	
	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	const char *GetTradingDay() { api_->GetTradingDay(); };
	
	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
	void RegisterFront(char *pszFrontAddress);
	
	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
	///@remark RegisterNameServer������RegisterFront
	void RegisterNameServer(char *pszNsAddress) { };
	
	///�������顣
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	///@remark 
	int SubscribeMarketData(char *ppInstrumentID[], int nCount);

	///�˶����顣
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	///@remark 
	int UnSubscribeMarketData(char *ppInstrumentID[], int nCount);

	///�û���¼����
	void ReqUserLogin(const char *broker_id, const char *user_id, const char *password);

	///�ǳ�����
	void ReqUserLogout(const char *broker_id, const char *user_id);

    inline int nextRequestId() { return ++request_id_; }

 public:
    int                 front_id_;	            ///< ǰ�ñ��
    int                 session_id_;	        ///< �Ự���
 private:
    CThostFtdcMdApi     *api_;                  ///< ����ʵ��
    CtpQuoterCallBack   *spi_;                  ///< �ص�ʵ��
    int                 request_id_;            ///< �Ự���
    std::mutex          syn_flag_;              ///< ��ص���ͬ���źš�
    std::atomic<bool>   locked_;                 ///< �Ƿ���ס�������������������Ƿ�ִ�С�
};
    
} /* QuantDigger */
#endif 
