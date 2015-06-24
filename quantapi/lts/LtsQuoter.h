/**
 * @file LtsQuoter.h
 * @brief 
 * @author HonePhy
 * Copyright () 2014-2020 QuantDigger. All rights reserved.
 * @chanege-log	 	
		2015-06-14 根据quantapi接口的调整做修改
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

	
	/** @brief 帐号登录。 */
    virtual int login(const LogonInfo &info, bool syn);
	
	/** @brief 帐号登录。 */
    virtual int logout(const LogonInfo &info, bool syn);
	
	/**
     * @brief 订阅tick数据。    
     *
     * @param contracts 合约集合。
     * @param sync 是否同步调用。
     *
     * @return 
    */
    virtual int reqTick(const std::vector<Contract> &contracts, bool syn);

    /**
     * @brief 取消tick数据订阅。
     *
     * @param contracts 合约集合。
     * @param sync 是否同步调用。
     *
     * @return 
     */
	virtual int unReqTick(const std::vector<Contract> &contracts, bool syn);
    
    /**
     * @brief 当前日期
     *
     * @note 只有登录成功后,才能得到正确的交易日。
     */
    virtual std::string getTradingDay()  { return api_->GetTradingDay(); }

protected:

    /** @brief tick数据到达回调函数。*/
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
	
	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterNameServer优先于RegisterFront
	void RegisterNameServer(char *pszNsAddress) { };

    
	// ---------------------- 回调函数 ------------------------------
	
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse);
	

	///登录请求响应
	virtual void OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin,
                                CSecurityFtdcRspInfoField *pRspInfo, 
                                int nRequestID, 
                                bool bIsLast);

	///登出请求响应
	virtual void OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, 
                                 CSecurityFtdcRspInfoField *pRspInfo, 
                                 int nRequestID, 
                                 bool bIsLast);

	///错误应答
	virtual void OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///订阅行情应答
	virtual void OnRspSubMarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, 
                                    CSecurityFtdcRspInfoField *pRspInfo, 
                                    int nRequestID, 
                                    bool bIsLast);

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument,
                                      CSecurityFtdcRspInfoField *pRspInfo, 
                                      int nRequestID, 
                                      bool bIsLast);

	///深度行情通知
	virtual void OnRtnDepthMarketData(CSecurityFtdcDepthMarketDataField *pDepthMarketData);
	
	/// 是否收到成功的响应
	bool IsErrorRspInfo(CSecurityFtdcRspInfoField *pRspInfo);

 private:
    int                 front_id_;	            ///< 前置编号
    int                 session_id_;	        ///< 会话编号
	
    CSecurityFtdcMdApi  *api_;                  ///< 请求实例
    int                 request_id_;            ///< 会话编号

	std::mutex              syn_flag_;              ///< 同步
	std::atomic<bool>       locked_;                ///< 是否被锁住，用来决定解锁操作是否执行。
	std::condition_variable m_cond;					//条件变量
};


} /* QuantDigger */

#endif