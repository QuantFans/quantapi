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
* @brief CTP行情查询类
*
* 由两个CTP实例组成，一个发起请求，一个处理回调。
* 可通过锁来同步请求实例和回调实例来完成一个操作
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

	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	void init() { api_->Init(); }
	
	///等待接口线程结束运行
	///@return 线程退出代码
	int join() { return api_->Join(); }

	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	void release() { api_->Release(); }
	
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	const char *GetTradingDay() { api_->GetTradingDay(); };
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	void RegisterFront(char *pszFrontAddress);
	
	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterNameServer优先于RegisterFront
	void RegisterNameServer(char *pszNsAddress) { };
	
	///订阅行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	int SubscribeMarketData(char *ppInstrumentID[], int nCount);

	///退订行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	int UnSubscribeMarketData(char *ppInstrumentID[], int nCount);

	///用户登录请求
	void ReqUserLogin(const char *broker_id, const char *user_id, const char *password);

	///登出请求
	void ReqUserLogout(const char *broker_id, const char *user_id);

    inline int nextRequestId() { return ++request_id_; }

 public:
    int                 front_id_;	            ///< 前置编号
    int                 session_id_;	        ///< 会话编号
 private:
    CThostFtdcMdApi     *api_;                  ///< 请求实例
    CtpQuoterCallBack   *spi_;                  ///< 回调实例
    int                 request_id_;            ///< 会话编号
    std::mutex          syn_flag_;              ///< 与回调的同步信号。
    std::atomic<bool>   locked_;                 ///< 是否被锁住，用来决定解锁操作是否执行。
};
    
} /* QuantDigger */
#endif 
