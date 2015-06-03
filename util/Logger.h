#ifndef _OPENCOG_LOGGER_H
#define _OPENCOG_LOGGER_H

#include <string>

#include <cstdarg>
#include <thread>
#include <mutex>
#include <sstream>
#include <cstdio>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>

namespace QuantDigger
{
namespace Util {
template<typename Data>
class concurrent_queue
{
    private:
        std::deque<Data> the_queue;
        mutable std::mutex the_mutex;
        std::condition_variable the_condition_variable;
        bool is_canceled;

    public:
        concurrent_queue() : the_queue(), the_mutex(), the_condition_variable(), is_canceled(false) {}
        struct Canceled{};
        void push(Data const& data)
        {
            std::unique_lock<std::mutex> lock(the_mutex);
            if (is_canceled) throw Canceled();
            the_queue.push_back(data);
            lock.unlock();
            the_condition_variable.notify_one();
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            if (is_canceled) throw Canceled();
            return the_queue.empty();
        }

        unsigned int size() const
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            return the_queue.size();
        }

        bool try_get(Data& value)
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            if (is_canceled) throw Canceled();
            if (the_queue.empty())
            {
                return false;
            }

            value = the_queue.front();
            return true;
        }

        // The code originally had a wait_and_pop() primitive.
        // Unfortunately, this will race against the empty() primitive.
        // The correct solution is to wait_and_get the value, do things
        // with the value, and then, only when done working with the value,
        // should one pop. Doing things this way will allow the empty()
        // function to correctly report the state of the work queue.
        void wait_and_get(Data& value)
        {
            std::unique_lock<std::mutex> lock(the_mutex);
            the_condition_variable.wait(lock,[this]{
                    if (is_canceled) 
                        throw Canceled();
                    return !the_queue.empty();
            });
            value = the_queue.front();
        }

        void pop()
        {
            std::lock_guard<std::mutex> lk(the_mutex);
            if(the_queue.empty())
                return;
            the_queue.pop_front();
        }

        void cancel_reset()
        {
            std::lock_guard<std::mutex> lk(the_mutex);
            is_canceled = false;
        }

        void cancel()
        {
            std::unique_lock<std::mutex> lock(the_mutex);
            /// @todo 用标志变量取代异常
            // 让读取此队列的线程函数发生异常，退出。
            if (is_canceled) 
                throw Canceled();
            is_canceled = true;
            lock.unlock();
            the_condition_variable.notify_all();
        }

};

/**
 * @brief 日志类，可以选择同步或者异步记录日志。
 *
 * 如果连续写的话，异步写入可能因为同步锁而更慢，但很少会发生连续不段的写入。
 */
class Logger
{
    void copy(const Logger&);
public:
    // WARNING: if you change the levels don't forget to update
    // levelStrings[] in Logger.cc
    enum Level { NONE, ERROR, WARN, INFO, DEBUG, FINE, BAD_LEVEL = 255 };

    
    /**
     * @brief 低于指定级别的消息将会被写入文件的末尾。
     *
     * @param async 异步标志: true表示异步，否则同步。
     * @param fileName 文件名
     * @param level  级别  
     * @param print_time 是否显示时间戳
     */
    Logger(bool async = false, const std::string &fileName = "quantdigger.log",
           Level level = INFO, bool print_time = true);

    Logger(const Logger&)=delete;
    Logger& operator=(const Logger& log)=delete;

    ~Logger();

    // logging接口
    void log  (Level level, const char *, ...);
    void error(const char *, ...);
    void warn (const char *, ...);
    void info (const char *, ...);
    void debug(const char *, ...);
    void fine (const char *, ...);


    /** Convert from 'enum' (int) to 'string' and vice-versa */
    static const Level getLevelFromString(const std::string&);
    static const char* getLevelString(const Level);

    /**
     * Reset the level of messages which will be logged. Every message with
     * log-level lower than or equals to newLevel will be logged.
     */
    void set_level(Level new_level) { current_level_ = new_level; };

    /**
     * Get the current log level that determines which messages will be
     * logged: Every message with log-level lower than or equals to returned
     * level will be logged.
     */
    Level level() const { return current_level_; }

    /**
     * Set the level of messages which should be logged with back trace. 
     * Every message with log-level lower than or equals to the given argument
     * will have back trace.
     */
    void set_btrace_level(Level new_level) { btrace_level_ =  new_level; };

    /**
     * Get the current back trace log level that determines which messages
     * should be logged with back trace. 
     */
    Level btrace_level() const { return btrace_level_; };

    /**
     * Reset the flag that indicates whether a timestamp is to be prefixed
     * in every message or not.
     */
    void set_print_time(bool flag) { print_time_ = flag; }

    /**
     * Reset the flag that indicates whether the log messages should be
     * printed to the stdout or not.
     */
    void set_print_stdout(bool flag) { print_stdout_ = flag; };

    /**
     * Set the main logger to print only
     * error level log on stdout (useful when one is only interested
     * in printing cassert logs)
     */
    void setPrintErrorLevelStdout();
   

private:
    /**
     * Log a message into log file (passed in constructor) if and only
     * if passed level is lower than or equal to the current log level
     * of this Logger instance.
     */
    void log(Level level, const std::string &txt);

    /**
     * Log a message (printf style) into log file (passed in constructor)
     * if and only if passed level is lower than or equals to the current
     * log level of this Logger instance.
     *
     * You may use these methods as any printf-style call, eg: 
     * fine("Count = %d", count)
     */
    void logva(Level level, const char *, va_list args);

    void writeMsg(std::string &msg);

    /** @brief Enable logging messages */
    void enableLogging() { log_enabled_ = true; };

    /** @brief Disable logging messages. */
    void disableLogging() { log_enabled_ = false; }
    
    void flush();
public:
    /** 
     * Methods to check if a given log level is enabled. This is useful for
     * avoiding unnecessary code for logger. For example: 
     * if (isDebugEnabled())  debug(...);
     */
    bool isEnabled(Level level) const { return level <= current_level_; }
    bool isErrorEnabled() const { return ERROR <= current_level_; }
    bool isWarnEnabled() const { return WARN <= current_level_; }
    bool isInfoEnabled() const { return INFO <= current_level_; }
    bool isDebugEnabled() const { return DEBUG <= current_level_; }
    bool isFineEnabled() const { return FINE <= current_level_; }


private:

    std::string         file_name_;             ///< 输出文件
    Level               current_level_;         ///< 控制logging的等级
    Level               btrace_level_;          ///< 控制输出栈路线的等级
    bool                print_time_;            ///< 是否输出时间戳
    bool                log_enabled_;           ///< 是否输出
    bool                print_stdout_;          ///< 是否输出到终端
    std::mutex          file_locker_;
    FILE                *f;
    bool                is_writing_;            ///< 决定是否开启唯一的记录线程
    bool                async_;

    /** @brief This thread does all writing of log messages */
    std::thread       write_thread_;

    /** @brief Queue for log messages */
    concurrent_queue<std::string*> pendingMessagesToWrite;

    void startWriteLoop();
    void stopWriteLoop();
    void writingLoop();

}; // class

// singleton instance (following Meyer's design pattern)
// logger()函数返回的才是singleton
Logger& logger();

} /* Util */
} 

#endif // _OPENCOG_LOGGER_H
