/**
 * @file threadsafe_stack.h
 * @brief 此类未经过测试！
 * @author wdj
 * @version 0.1
 * @date 2014-05-10
 */

#ifndef THREADSAFE_STACK_H

#define THREADSAFE_STACK_H
#include <memory>
#include <mutex>
#include <stack>

namespace QuantDigger {
namespace Util {
    
template<typename T>
class threadsafe_stack
{
    private:
        std::stack<T> data;
        mutable std::mutex m;
    public:
        threadsafe_stack(){}
        threadsafe_stack(const threadsafe_stack& other)
        {
            std::lock_guard<std::mutex> lock(other.m);
            data=other.data; 
        }
     //   threadsafe_stack& operator=(const threadsafe_stack&) = delete;
        void push(T new_value)
        {
            std::lock_guard<std::mutex> lock(m);
            data.push(new_value);
        }
        std::shared_ptr<T> pop()
        {
            std::lock_guard<std::mutex> lock(m);
            if(data.empty())
                return std::shared_ptr<T>();
            std::shared_ptr<T> const res(std::make_shared<T>(data.top())); 
            data.pop(); 
            return res;
        }
        bool pop(T& value)
        {
            std::lock_guard<std::mutex> lock(m);
            if(data.empty())
                return false;
            value=data.top();
            data.pop();
            return true;
        }
        bool empty() const
        {
            std::lock_guard<std::mutex> lock(m);
            return data.empty();
        }
};
} /* Util */
} /* QuantDigger */
#endif /* end of include guard: THREADSAFE_STACK_H */
