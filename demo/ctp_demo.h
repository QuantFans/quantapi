#include <iostream>
#include <quantapi/ctp/CtpQuoter.h>
#include <quantapi/ctp/CtpTrader.h>
#include <quantapi/datastruct.h>
#include <vector>
#include <thread>
#include <chrono>

using namespace QuantApi;
using namespace std;

/**
* @brief 接口实例   
*/
class MyCtpTrader : public CtpTrader{
 public:
	 MyCtpTrader(char *front) :CtpTrader(front) { };
	 virtual ~MyCtpTrader() { }

    virtual void on_tick(const TickData &tick) { 
        std::cout<<"*********************************"<<std::endl;    
        std::cout<<tick.price<<std::endl;
        std::cout<<"*********************************"<<std::endl;    
    }
	
	static char front[];
	static LogonInfo logonInfo;
	
 private:
    /* data */
};

char MyCtpTrader::front[]="tcp://180.168.146.181:10000";
LogonInfo MyCtpTrader::logonInfo("0081", "01095", "WANGDJ1985");

class MyCtpQuoter : public CtpQuoter {
public:
	MyCtpQuoter(char *front) :CtpQuoter(front) {};
	virtual ~MyCtpQuoter(){}

	virtual void on_tick(const TickData &tick) {
		std::cout << "*********************************" << std::endl;
		std::cout << Util::formatTime(tick.dt) <<"==>" << tick.contract.code << "==" <<  tick.price << std::endl;
		std::cout << "*********************************" << std::endl;
	}
	static char front[];
	static LogonInfo logonInfo;

};

char MyCtpQuoter::front[] = "tcp://180.168.146.181:10100";
LogonInfo MyCtpQuoter::logonInfo("0081", "01095", "WANGDJ1985");

