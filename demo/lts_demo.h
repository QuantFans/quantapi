#include <iostream>
#include <quantapi/lts/LtsQuoter.h>
#include <quantapi/lts/LtsTrader.h>
#include <quantapi/datastruct.h>
#include <vector>
#include <thread>
#include <chrono>

/**
* @brief ½Ó¿ÚÊµÀý   
*/
class MyLtsTrader : public LtsTrader{
 public:
	 MyLtsTrader(char *front) :LtsTrader(front) { };
	 virtual ~MyLtsTrader() { }

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

char MyLtsTrader::front[]="tcp://211.144.195.163:44505";
LogonInfo MyLtsTrader::logonInfo("2011", "020000000059", "123321");


class MyLtsQuoter : public LtsQuoter {
public:
	MyLtsQuoter(char *front) :LtsQuoter(front) {};
	virtual ~MyLtsQuoter(){}

	virtual void on_tick(const TickData &tick) {
		std::cout << "*********************************" << std::endl;
		std::cout << Util::formatTime(tick.dt) <<"==>" << tick.contract.code << "==" <<  tick.price << std::endl;
		std::cout << "*********************************" << std::endl;
	}
	
	static char front[];
	static LogonInfo logonInfo;
};

char MyLtsQuoter::front[]="tcp://211.144.195.163:44513";
LogonInfo MyLtsQuoter::logonInfo("2011", "020000000059", "123");