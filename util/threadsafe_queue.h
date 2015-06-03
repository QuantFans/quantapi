/**
 * @file threadsafe_queue.h
 * @brief 线层安全队列，支持多对多模式
 * @author wdj
 * @version 0.1
 * @date 2014-05-10
 */

#ifndef THREADSAFE_QUENE_H

#define THREADSAFE_QUENE_H
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

namespace QuantDigger {
namespace Util {
    
    
template<typename T>
class threadsafe_queue
{
 private:
    mutable std::mutex mut; 
    std::queue<T> data_queue;
    std::condition_variable data_cond;
 public:
    threadsafe_queue()
    {}
    threadsafe_queue(threadsafe_queue const& other)
    {
        std::lock_guard<std::mutex> lk(other.mut);
        data_queue=other.data_queue;
    }
    void push(T new_value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_queue.push(new_value);
        lk.unlock();
        data_cond.notify_one();
    }
    void wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        value=data_queue.front();
        data_queue.pop();
    }

    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return false;
        value=data_queue.front();
        data_queue.pop();
        return true;
    }
    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }
    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};
} /* Util */
} /* QuantDigger */

#endif /* end of include guard: THREADSAFE_QUENE_H */
