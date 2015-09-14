/**
 * @file gtastockuoter.h
 * @brief 
 * @author  HonePhy
 * @version 0.1
 * @date 2015-07-30
 */

#ifndef _GTAQUOTER_H

#define _GTAQUOTER_H
#include <atomic>
#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>
#include "../Quoter.h" 
#include "../datastruct.h"
#include "GTAQTSInterfaceEx.h" 

namespace QuantApi {


/**
* @brief GTA行情查询类
*
* 由两个GTA实例组成，一个发起请求，一个处理回调。
* 可通过锁来同步请求实例和回调实例来完成一个操作
*/
class GtaStockQuoter : public Quoter, private IGTAQTSCallbackEx {

 public:

    GtaStockQuoter(std::vector<std::pair<std::string, unsigned short>> fronts);

    virtual ~GtaStockQuoter();

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
    virtual std::vector<TickData> querySnap(const std::vector<Contract> &contracts);

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
     * @brief 订阅指数tick数据。    
     *
     * @param contracts 合约集合。
     * Contract.code允许为空，exch_type不允许为空,如果合约代码为空，则获取该市场的所有合约行情
     * @param sync 是否同步调用。
     *
     * @return 
     */
    virtual int reqIndexTick(const std::vector<Contract> &contracts, bool sync);

    /**
     * @brief 取消tick数据订阅。
     *
     * @param contracts 合约集合。
     * Contract.code允许为空，exch_type不允许为空,如果合约代码为空，则获取该市场所有合约行情订阅
     * @param sync 是否同步调用。
     *
     * @return 
     */
	virtual int unReqTick(const std::vector<Contract> &contracts, bool sync);

    /**
     * @brief 当前日期
     *
     * @note 只有登录成功后,才能得到正确的交易日。
     */
    virtual std::string getTradingDay()  { return "" ; }

protected:

    /** @brief tick数据到达回调函数。*/
    virtual void on_tick(const TickData &tick) {
        /*
        std::cout << tick.contract.code << std::endl 
            << tick.contract.exch_type << std::endl
            << tick.price << std::endl
            << tick.volume << std::endl
            << tick.total_price << std::endl;
        */
    }

 private:

    int subscribe(const DataCategory category, const std::vector<Contract>& contracts);

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


    /// 登陆状态返回
    /// @param  errCode  -- 失败原因(用户过期、重复登陆)用户需对这两个进行处理
    virtual void OnLoginState( RetCode errCode);

    /// 连接状态返回，连接成功/失败
    /// @param  msgType      -- 消息类型
    /// @param  errCode     -- 失败原因，成功时返回0
    virtual void OnConnectionState(MsgType msgType, RetCode errCode);

    /// 会话标志失效（即在API中已经没有使用）
    /// @param  pSessionTag    -- 会话标志
    virtual void OnSessionTagInvalid(void* pSessionTag){}

    /// 订阅数据实时回调接口
    /// @param  msgCategory -- 返回的数据分类
    /// @param  RealData    -- 实时数据
    /// @param  pSessionTag -- 订阅数据时传入的用户标志
    virtual void OnSubscribe(const DataCategory msgCategory, IQuotationData& RealData, void*  pSessionTag);


 private:
    int                 front_id_;	            ///< 前置编号
    int                 session_id_;	        ///< 会话编号

    IGTAQTSApiEx        *api_;                  ///< 请求实例
    int                 request_id_;            ///< 会话编号
	
	std::mutex              syn_flag_;              ///< 同步
	std::atomic<bool>       locked_;                ///< 是否被锁住，用来决定解锁操作是否执行。
	std::condition_variable m_cond;					//条件变量
};
    
} /* QuantDigger */
#endif 
