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
* @brief ���׻ص���Ļ��ࡣ
*
* ʵ�ֵĽӿڣ��޸ķ������״̬���Ƿ��Ѿ���¼�ȡ�
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
