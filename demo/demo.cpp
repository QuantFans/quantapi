#include <iostream>
#include <quantapi/datastruct.h>
#include <vector>
#include <thread>
#include <chrono>

#include "ctp_demo.h"
#include "lts_demo.h"

using namespace QuantApi;
using namespace std;

void md(const vector<Contract>& clist)
{
//	Quoter *quoter = new MyCtpQuoter(MyCtpQuoter::front);
//	quoter->login(MyCtpQuoter::logonInfo, true);
	
	Quoter *quoter = new MyLtsQuoter(MyLtsQuoter::front);
	quoter->login(MyLtsQuoter::logonInfo, true);

	quoter->reqTick(clist, true);
	std::this_thread::sleep_for(std::chrono::seconds(20));
	quoter->unReqTick(clist, true);
	std::this_thread::sleep_for(std::chrono::seconds(20));

//	quoter->logout(MyCtpQuoter::logonInfo, true);

	quoter->logout(MyLtsQuoter::logonInfo, true);
}

void td(Contract& c)
{
	Trader *trader = new MyCtpTrader(MyCtpTrader::front);
	trader->login(MyCtpTrader::logonInfo, true);

	Order order(OrderID(1), c, kKai, LONG,
		0, 1, std::chrono::system_clock::now(), kSpeculation, kMarket);

	trader->reqContract(&c, true);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	trader->order(order, true);

	trader->reqTick(c, true);

	std::this_thread::sleep_for(std::chrono::seconds(60));

	trader->logout(MyCtpTrader::logonInfo, true);
}

int main(int argc, const char *argv[])
{

    // 期权
//    char quoter_front[]="tcp://27.17.62.149:42213";
//    char trader_front[]="tcp://27.17.62.149:42205";
    

    Contract c;
    //c.code = "ru1509" ;
	c.code = "10000031";
	c.exch_type = '5';
    vector<Contract> clist;
    clist.push_back(c);

    std::cout<<"*********************************"<<std::endl;    
	md(clist);
    return 0;
}
