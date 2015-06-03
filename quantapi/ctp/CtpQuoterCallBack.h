/**
 * @file CtpQuoterCallBack.h
 * @brief 
 * @author wdj
 * @version 0.1
 * @date 2014-04-10
 */

#ifndef _CTPQUOTERCALLBACK_H_
#define _CTPQUOTERCALLBACK_H_

#include <mutex>
#include <string.h>
#include "../QuoterCallBackBase.h"
#include "../../util/log_assert.h"
#include "CtpQuoter.h"
namespace QuantDigger {
    
/**
 * @brief CTP交易数据回调类。
 * 
 * 负责一些CTP相关的状态信息的更新, 及通过解锁和发起类同步。
 * 如果要实现特定的功能，需要在其子类中实现，比如CtpQuoterCallBackForEngine。
 */
class CtpQuoterCallBack : public CThostFtdcMdSpi, public QuoterCallBackBase {
 public:
    CtpQuoterCallBack() :quoter_(NULL) { }
    inline void set_quoter(CtpQuoter *q) { 
        quoter_ = q; 
        set_state(q);
    }

 protected:
    inline void set_front_id(int id) { 
        LOG_ASSERT(quoter_);
        quoter_->front_id_ = id;
    }

    inline void set_session_id(int id) { 
        LOG_ASSERT(quoter_);
        quoter_->session_id_ = id;
    }
    inline int session_id() {
        LOG_ASSERT(quoter_);
        return quoter_->session_id_;
    }
    inline int front_id(int id) {
        LOG_ASSERT(quoter_);
        return quoter_->front_id_;
    }
    inline void synUnlock() {
        LOG_ASSERT(quoter_);
        quoter_->synUnlock(); 
    }

 private:
    CtpQuoter *quoter_;
};

} /* QuantDigger */
#endif
