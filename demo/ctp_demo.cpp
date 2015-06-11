#include <iostream>
#include <quantapi/ctp/CtpQuoter.h>
#include <quantapi/ctp/CtpTrader.h>
#include <quantapi/datastruct.h>
#include <vector>
#include <thread>
#include <chrono>

using namespace QuantApi;
using namespace std;


int main(int argc, const char *argv[])
{

    // 期权
//    char quoter_front[]="tcp://27.17.62.149:42213";
//    char trader_front[]="tcp://27.17.62.149:42205";
     
    char trader_front[]="tcp://180.168.146.181:10000";
    char quoter_front[]="tcp://180.168.146.181:10100";

    Contract c;
    c.code = "jd1604" ;
    vector<Contract> clist;
    clist.push_back(c);

    std::cout<<"*********************************"<<std::endl;    
    CtpQuoter *quoter = new CtpQuoter(quoter_front);
    CtpTrader *trader = new CtpTrader(trader_front);
//    LogonInfo info("8888", "001061", "001061");
    LogonInfo info("0081", "01095", "WANGDJ1985");

    quoter->login(info, false);
    trader->login(info, false);


    Order order(OrderID(1), Contract('s', "if1506"), kKai, kDuo,
                0, 1, std::chrono::system_clock::now(), kSpeculation, kMarket);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<"------------------------"<<std::endl; 
    quoter->reqTick(clist, false);
    trader->reqTick(c, false);
//    trader->order(order);
    std::this_thread::sleep_for(std::chrono::seconds(100));
    return 0;
}
