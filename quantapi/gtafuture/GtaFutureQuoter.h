/**
 * @file gtafuturequoter.h
 * @brief 
 * @author  HonePhy
 * @version 0.1
 * @date 2015-08-02
 */

#ifndef _GTAFUTUREQUOTER_H

#define _GTAFUTUREQUOTER_H
#include <atomic>
#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>
#include <quantapi/Quoter.h>
#include <quantapi/datastruct.h>

#include "GTAQTSInterface.h"
//#include "GTAMarketServiceApi.h" 

namespace QuantApi {


/**
* @brief GTA行情查询类
*
* 由两个GTA实例组成，一个发起请求，一个处理回调。
* 可通过锁来同步请求实例和回调实例来完成一个操作
*/
class GtaFutureQuoter : public Quoter, private IGTAMarketServiceCallback {

 public:

    GtaFutureQuoter(std::vector<std::pair<std::string, unsigned short>> trade_fronts);

    virtual ~GtaFutureQuoter();

    /** @brief 帐号登录。 */
    virtual int login(const LogonInfo &info, bool sync=true);

    /** @brief 帐号退出。 */
    virtual int logout(const LogonInfo &info,  bool sync);
     
    /**
      * @biref 获取股票列表
      * @param  market  -- 市场标识，以“,”分割多个市场标识，末尾必须以\0结束，不允许为NULL
      */
    virtual std::vector<Contract> getStockList(const char* market);


    /**
      * @biref 取得合约快照
      *
      * @合约列表Contract.code允许为空，exch_type不允许为空
      *  如果合约代码为空，则获取该市场的所有快照
      */
    virtual std::vector<TickData> querySnap(const std::vector<Contract> &contracts){

    }

    /**
     * @brief 订阅tick数据。    
     *
     * @param contracts 合约集合。
     * Contract.code允许为空，exch_type不允许为空,如果合约代码为空，则获取该市场的所有合约行情
     * @param sync 是否同步调用。
     *
     * @return 
     */
    virtual int reqTick(const std::vector<Contract> &contracts, bool sync);

    /**
     * @brief 取消tick数据订阅。
     *
     * @param contracts 合约集合。
     * Contract.code允许为空，exch_type不允许为空,如果合约代码为空，则获取该市场所有合约行情订阅
     * @param sync 是否同步调用。
     *
     * @return 
     */
	virtual int unReqTick(const std::vector<Contract> &contracts, bool sync){

    }

    /**
     * @brief 当前日期
     *
     * @note 只有登录成功后,才能得到正确的交易日。
     */
    virtual std::string getTradingDay()  { return "" ; }

protected:

    /** @brief tick数据到达回调函数。*/
    virtual void on_tick(const TickData &tick) { }

 private:


    inline void wait(bool towait) 
	{ 
		if(towait) 
		{
			std::unique_lock<std::mutex> lock(syn_flag_);
			locked_ = true;
			m_cond.wait(lock);
		}
	}

	inline void notify() {
        if (locked_)
        {
		std::unique_lock <std::mutex> lock(syn_flag_);
		locked_ = false;
		m_cond.notify_all();
        }
	}

    inline int nextRequestId() { return ++request_id_; }

    inline void set_front_id(int id) { front_id_ = id; }
    inline void set_session_id(int id) { session_id_ = id; }
    inline int session_id() { return session_id_; }
    inline int front_id(int id) { return front_id_; }


    // ---------------------- 回调函数 ------------------------------


    /// 通知行情连接结果.
    /// 
    /// @param reason 连接结果标志 0成功，其余失败，详见失败代码表.
    virtual void OnConnect(int reason);

    /// 通知行情断开.
    ///
    /// @param reason 错误码，详见失败代码表.
    virtual void OnConnectionFail(int reason){
        std::cout << "connectfial ret = " << reason << std::endl;
    }

    /// 登录结果.
    /// 
    /// @param userID 用户ID.
    /// @param result 登录结果，0成功过，其余失败.
    virtual void OnLogon(int userID, int result){

    }

	/// 通知市场列表数据.
    /// @param md 市场列表数据，包含cnt个MarketDesc.
    /// @param cnt 市场个数.
    virtual void OnMarketList(MarketDesc* md, int cnt);

    /// 通知市场个股列表.
    /// @param mi 市场.
    /// @param data 个股列表数据，代码之间以逗号分隔. 
    /// @param datalen 数据长度.
    virtual void OnStockList(MarketInfo* mi, void* data, int datalen);
    
    /// 增加/取消订阅操作结果.
    /// 
    /// @param mdi 市场数据标志
    /// @param result 操作结果 0成功 其余失败.
    virtual void OnSubscribe(MarketDataInfo* mdi, int result);

    /// 通知实时数据.
    /// @param mdi 市场数据标志.
    /// @param dataType 数据类型，参见具体市场数据类型定义
    /// @param data 行情数据，每个市场不同，由应用自行解析.
    /// @param datalen 数据长度
    virtual void OnRealData(MarketDataInfo* mdi, void* data, int datalen);

 private:
    int                 front_id_;	            ///< 前置编号
    int                 session_id_;	        ///< 会话编号

    IGTAQTSInterface    *api_;                  ///< 请求实例
    int                 request_id_;            ///< 会话编号
	
	std::mutex              syn_flag_;              ///< 同步
	std::atomic<bool>       locked_;                ///< 是否被锁住，用来决定解锁操作是否执行。
	std::condition_variable m_cond;					//条件变量

    std::vector<MarketDataInfo> mdis_;
};
    
} /* QuantDigger */
#endif 
