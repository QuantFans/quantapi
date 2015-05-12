/**
 * @file CtpTraderCallBack.h
 * @brief 
 * @author wdj
 * @version 0.1
 * @date 2014-04-10
 */

#ifndef _CtpTraderCallBack_H_
#define _CtpTraderCallBack_H_
#include <mutex>
#include "ThostFtdcTraderApi.h" 
#include "CtpTrader.h" 
#include "../TraderCallBackBase.h" 
#include "../../util/log_assert.h"
namespace QuantDigger {
    

/**
 * @brief CTP交易回调类。
 * 
 * 负责一些CTP相关的状态信息的更新, 及通过解锁和发起类同步。
 * 如果要实现特定的功能，需要在其子类中实现，比如CtpTraderCallBackForEngine。
 */
class CtpTraderCallBack : public CThostFtdcTraderSpi, public TraderCallBackBase {
 public:
    CtpTraderCallBack() :trader_(NULL) { }
    inline void set_trader(CtpTrader *q) { 
        trader_ = q; 
        set_state(q);
    }
 protected:
    inline void set_front_id(int id) { 
        LOG_ASSERT(trader_);
        trader_->front_id_ = id;
    }

    inline void set_session_id(int id) { 
        LOG_ASSERT(trader_);
        trader_->session_id_ = id;
    }
    inline int session_id() {
        LOG_ASSERT(trader_);
        return trader_->session_id_;
    }
    inline int front_id(int id) {
        LOG_ASSERT(trader_);
        return trader_->front_id_;
    }
    inline void synUnlock() {
        LOG_ASSERT(trader_);
        trader_->synUnlock(); 
    }


 private:
    CtpTrader *trader_;

};

} /* QuantDigger */
#endif
