#include "ThreadPool.h" 
using namespace QuantDigger::Util;
work_stealing_queue* ThreadPool::local_work_queue; 
unsigned ThreadPool::my_index;
