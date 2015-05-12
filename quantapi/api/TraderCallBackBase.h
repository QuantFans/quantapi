/**
 * @file TraderCallBackBase.h
 * @brief 
 * @author wdj
 * @version 0.1
 * @date 2014-05-04
 */
#ifndef _TraderCallBackBase_H

#define _TraderCallBackBase_H
#include "Trader.h"
#include <cassert>
namespace QuantDigger {
/**
* @brief 交易回调类的基类。
*
* 实现的接口：修改发起类的状态如是否已经登录等。
*/
class TraderCallBackBase {
public:
 TraderCallBackBase() :state_(NULL) { }
 virtual ~TraderCallBackBase() { }

protected:
 void set_state(Trader *t) {
     state_ = t;
 }

 void set_logined(bool b){
    assert(state_);
    state_->set_logined(b);
 };

private:
 Trader *state_;
};
} /* QuantDigger */


#endif /* end of include guard: _TraderCallBackBase_H */
