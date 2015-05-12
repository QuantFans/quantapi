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
 * @brief CTP�������ݻص��ࡣ
 * 
 * ����һЩCTP��ص�״̬��Ϣ�ĸ���, ��ͨ�������ͷ�����ͬ����
 * ���Ҫʵ���ض��Ĺ��ܣ���Ҫ����������ʵ�֣�����CtpQuoterCallBackForEngine��
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
