/**
 * @file QuoterCallBackBase.h
 * @brief 
 * @author wdj
 * @version 0.1
 * @date 2014-05-04
 */
#ifndef _QuoterCallBackBase_H

#define _QuoterCallBackBase_H
#include <cassert>
#include "Quoter.h"
namespace QuantDigger {
/**
* @brief 行情回调类的基类。
*
* 实现的接口：修改发起类的状态如是否已经登录等。
*/
class QuoterCallBackBase {
public:
 QuoterCallBackBase() :state_(NULL) { }
 virtual ~QuoterCallBackBase() { }

protected:
 void set_state(Quoter *t) {
     state_ = t;
 }

 void set_logined(bool b){
    assert(state_);
    state_->set_logined(b);
 };

private:
 Quoter *state_;
};
} /* QuantDigger */


#endif /* end of include guard: _QuoterCallBackBase_H */
