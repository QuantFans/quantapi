#include "Logger.h"
#include <cstring>
#include <chrono>
#include <iostream>
#include <sstream>
#include <cstring>
#include <stdarg.h>
#include "Functions.h"
#include "log_assert.h" 
/// @todo define WIN32 in cmake
#ifdef WIN32
#else
    #include <cxxabi.h>
    #include <execinfo.h>                           // for print backtrace
#endif
#define TRACE_INFO " (" __FILE__ ":" TOSTRING(__LINE__) ")"


using namespace Util;
using namespace std::chrono;

// 如果输出消息长度超过它，将被截断。
#define MAX_PRINTF_STYLE_MESSAGE_SIZE (1<<15)
const char* levelStrings[] = {"NONE", "ERROR", "WARN", "INFO", "DEBUG", "FINE"};

/**
 * @brief 输出调用栈
 *
 * @param oss
 */
static void prt_backtrace(std::ostringstream& oss)
{
#ifdef WIN32
    return;
#else
    const int BT_BUFSZ = 50;
	void *bt_buf[BT_BUFSZ];
	int stack_depth = backtrace(bt_buf, BT_BUFSZ);
	char **syms = backtrace_symbols(bt_buf, stack_depth);

	// Start printing at a bit into the stack, so as to avoid recording
	// the logger functions in the stack trace.
	oss << "\tStack Trace:\n";
	for (int i=2; i < stack_depth; i++)
	{
		// Most things we'll print are mangled C++ names,
		// So demangle them, get them to pretty-print.
		char * begin = strchr(syms[i], '(');
		char * end = strchr(syms[i], '+');
		if (!(begin && end) || end <= begin)
		{
			// Failed to pull apart the symbol names
            oss << "\t" << i << ": " << syms[i] << "\n";
		}
		else
		{
			*begin = 0x0;
			oss << "\t" << i << ": " << syms[i] << " ";
			*begin = '(';
			size_t sz = 250;
			int status;
			char *fname = (char *) malloc(sz);
			*end = 0x0;
			char *rv = abi::__cxa_demangle(begin+1, fname, &sz, &status);
			*end = '+';
			if (rv) fname = rv; // might have re-alloced
			oss << "(" << fname << " " << end << std::endl;
			free(fname);
		}
	}
	oss << std::endl;
	free(syms);
#endif
}

Logger::Logger(bool async, const std::string &fname, Logger::Level level, bool print_time)
{
    file_name_.assign(fname);
    current_level_ = level;
    print_time_ = print_time;
    print_stdout_ = false;
    log_enabled_ = true;
    if ((f = fopen(file_name_.c_str(), "a")) == NULL)
    {
        fprintf(stderr, "[ERROR] Unable to open log file \"%s\"\n",
                file_name_.c_str());
        file_locker_.unlock();
        disableLogging();
        return;
    }
    else
        enableLogging();
    async_ = async; 
    if (async_) {
        is_writing_ = false;
        startWriteLoop();
    }
}

Logger::~Logger()
{
    // Wait for queue to empty
    if (async_) {
        flush();
        stopWriteLoop();
    }
    if (f != NULL) 
        fclose(f);
}

void Logger::startWriteLoop()
{
    if (!is_writing_)
    {
        is_writing_ = true;
        write_thread_ = std::thread(&Logger::writingLoop, this);
    }
}

void Logger::stopWriteLoop()
{
    pendingMessagesToWrite.cancel();
    // rejoin thread
    write_thread_.join();
    is_writing_ = false;
}

void Logger::writingLoop()
{
    try
    {
        while(true)
        {
            // Must not pop until *after* the message has been written,
            // as otherwise, the flush() call will race with the write,
            // causing flush to report an empty queue, even though the
            // message has not actually been written yet.
            std::string* msg;
            pendingMessagesToWrite.wait_and_get(msg);
            writeMsg(*msg);
            pendingMessagesToWrite.pop();
            delete msg;
        }
    }
    catch (concurrent_queue< std::string* >::Canceled &e)
    {
        return;
    }
}

void Logger::flush()
{
    while (!pendingMessagesToWrite.empty())
    {
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Logger::writeMsg(std::string &msg)
{
    LOG_ASSERT(f);
    file_locker_.lock();
    // write to file
    fprintf(f, "%s", msg.c_str());
    fflush(f);
    file_locker_.unlock();
    // write to stdout
    if (print_stdout_) {
        std::cout << msg;
        std::cout.flush();
    }
}

//Logger::Logger(const Logger& log)
//{
//    copy(log);
//}
//
//Logger& Logger::operator=(const Logger& log)
//{
//    if (async_) {
//        this->stopWriteLoop();
//        pendingMessagesToWrite.cancel_reset();
//    } else {
//        this->copy(log);
//        return *this;
//    }
//}
//
//void Logger::copy(const Logger& log)
//{
//    file_locker_.lock();
//    file_name_.assign(log.file_name_);
//    current_level_ = log.current_level_;
//    btrace_level_ = log.btrace_level_;
//    print_time_ = log.print_time_;
//    print_stdout_ = log.print_stdout_;
//    log_enabled_ = log.log_enabled_;
//    f = log.f;
//    async_ = log.async_;
//    file_locker_.unlock();
//    if (async_) {
//        startWriteLoop();
//    }
//}

void Logger::setPrintErrorLevelStdout() {
    set_print_stdout(true);
    set_level(Logger::ERROR);
}

void Logger::log(Logger::Level level, const std::string &txt)
{
    static const unsigned int max_queue_size_allowed = 1024;
    std::ostringstream oss;
    // 时间
    if (print_time_)
    {
        char timestamp[20];
        memset(timestamp, 0, 20);
        formatTime(system_clock::now(), timestamp);
        oss << timestamp;
    }
    // 级别 + 消息内容
    oss << "[" << getLevelString(level) << "] " << txt;
//    oss << "<" << TRACE_INFO << ">";
    oss <<  std::endl;
    // 栈路线
    if (level <= btrace_level_) {
        prt_backtrace(oss);
    }
    // 
    if (async_) {
        pendingMessagesToWrite.push(new std::string(oss.str()));
        // If the queue gets too full, block until it's flushed to file or
        // stdout
        if (pendingMessagesToWrite.size() > max_queue_size_allowed)
            flush();
    } else {
        std::string temp = oss.str();
        writeMsg(temp);
    }
}

void Logger::logva(Logger::Level level, const char *fmt, va_list args)
{
    char buffer[MAX_PRINTF_STYLE_MESSAGE_SIZE];
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    std::string msg = buffer;
    log(level, msg);
}

void Logger::log(Logger::Level level, const char *fmt, ...)
{
    va_list args; va_start(args, fmt); logva(level, fmt, args); va_end(args);
}

void Logger::error(const char *fmt, ...)
{
    if (log_enabled_ && ERROR <= current_level_) {
        va_list args; va_start(args, fmt); logva(ERROR, fmt, args); va_end(args);
    }
}

void Logger::warn(const char *fmt, ...)
{
    if (log_enabled_ && WARN <= current_level_) {
        va_list args; va_start(args, fmt); logva(WARN,  fmt, args); va_end(args);
    }
}

void Logger::info(const char *fmt, ...)
{
    if (log_enabled_ && INFO <= current_level_) {
        va_list args; va_start(args, fmt); logva(INFO,  fmt, args); va_end(args);
    }
}

void Logger::debug(const char *fmt, ...)
{
    if (log_enabled_ && DEBUG <= current_level_) {
        va_list args; va_start(args, fmt); logva(DEBUG, fmt, args); va_end(args);
    }
}

void Logger::fine(const char *fmt, ...)
{
    if (log_enabled_ && FINE <= current_level_) {
        va_list args; va_start(args, fmt); logva(FINE,  fmt, args); va_end(args);
    }
}

const char* Logger::getLevelString(const Logger::Level level)
{
    if (level >= BAD_LEVEL)
        return "Bad level";
    else
        return levelStrings[level];
}

const Logger::Level Logger::getLevelFromString(const std::string& levelStr)
{
    unsigned int nLevels = sizeof(levelStrings) / sizeof(levelStrings[0]);
    for (unsigned int i = 0; i < nLevels; ++i) {
        if (std::string(levelStrings[i]) ==  levelStr)
            return (Logger::Level) i;
    }
    return BAD_LEVEL;
}

// create and return the single instance
Logger& Util::logger()
{
    // 唯一的同步记录器
    static Logger instance(false);
    instance.set_print_stdout(true);
    instance.set_btrace_level(Logger::ERROR);
    return instance;
}
