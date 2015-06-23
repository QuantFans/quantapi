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
class MyTrader : public CtpTrader{
 public:
    MyTrader(char *front):CtpTrader(front) { };
    virtual ~MyTrader() { }

    virtual void on_tick(const TickData &tick) { 
        std::cout<<"*********************************"<<std::endl;    
        std::cout<<tick.price<<std::endl;
        std::cout<<"*********************************"<<std::endl;    
    }
 private:
    /* data */
};

class MyQuoter : public CtpQuoter {
public:
	MyQuoter(char *front) :CtpQuoter(front) {};
	virtual ~MyQuoter(){}

	virtual void on_tick(const TickData &tick) {
		std::cout << "*********************************" << std::endl;
		std::cout << tick.contract.code << "==" <<  tick.price << std::endl;
		std::cout << "*********************************" << std::endl;
	}
};

int main(int argc, const char *argv[])
{

    // 期权
//    char quoter_front[]="tcp://27.17.62.149:42213";
//    char trader_front[]="tcp://27.17.62.149:42205";
     
    char trader_front[]="tcp://180.168.146.181:10000";
    char quoter_front[]="tcp://180.168.146.181:10100";

    Contract c;
    c.code = "ru1509" ;
    vector<Contract> clist;
    clist.push_back(c);

    std::cout<<"*********************************"<<std::endl;    

	MyQuoter *quoter = new MyQuoter(quoter_front);
//    MyTrader *trader = new MyTrader(trader_front);

	//    LogonInfo info("8888", "001061", "001061");
    LogonInfo info("0081", "01095", "WANGDJ1985");


	quoter->login(info, true);
//    trader->login(info, true);


    Order order(OrderID(1), c, kKai, LONG,
                0, 1, std::chrono::system_clock::now(), kSpeculation, kMarket);

	    

	quoter->reqTick(clist, true);

	//trader->reqContract(&c, true);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	//trader->order(order, true);

	//trader->reqTick(c, true);

    std::this_thread::sleep_for(std::chrono::seconds(60));
//	trader->logout(info,true);
	quoter->unReqTick(clist, true);
	quoter->logout(info,true);
    return 0;
}
