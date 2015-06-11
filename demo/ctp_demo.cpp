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
//   char quoter_trade_front[]="tcp://61.141.238.238:61213";
//  char trader_trade_front[]="tcp://61.141.238.238:61205";

    char quoter_trade_front[]="tcp://27.17.62.149:42213";
    char trader_trade_front[]="tcp://27.17.62.149:42205";

    Contract c;
//    c.code = "if1506" ;
    c.code = "" ;
    vector<Contract> clist;
    clist.push_back(c);

    std::cout<<"*********************************"<<std::endl;    
//    CtpQuoter *quoter = new CtpQuoter(quoter_trade_front);
    CtpTrader *trader = new CtpTrader(trader_trade_front);
//    LogonInfo info("8888", "001061", "001061");
    LogonInfo info("8888", "002546", "002546");

//    quoter->login(info, false);
    trader->login(info, false);


    Order order(OrderID(1), Contract('s', "if1506"), kKai, kDuo,
                0, 1, std::chrono::system_clock::now(), kSpeculation, kMarket);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<"------------------------"<<std::endl; 
//    quoter->subscribeMarketData(clist, false);
    trader->reqTick(c, false);
//    trader->order(order);
    std::this_thread::sleep_for(std::chrono::seconds(100));
    return 0;
}
