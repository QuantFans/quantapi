#include "GtaStockQuoter.h" 
#include "GtaStockMapping.h" 
#include <quantapi/mapping.h>
#include <log4cxx/logger.h>


namespace QuantApi {
using namespace Mapping;
using namespace log4cxx;
LoggerPtr logger(Logger::getRootLogger());

static std::string contracts2string(const std::vector<Contract>& contracts)
{
    std::ostringstream ss;
    int count = contracts.size();
    for (int i = 0; i < count; i++)
    {
        if (contracts[i].code == "")
            ss << "*.";
        else
            ss << contracts[i].code << "." ;
        ss << mapFromQDExchType(contracts[i].exch_type);
        if (i < count-1)
            ss << ",";
    }
    return ss.str();
}

GtaStockQuoter::GtaStockQuoter(std::vector<std::pair<std::string, unsigned short>> trade_fronts)
{
    api_ = IGTAQTSApiEx::CreateInstance(*this);
    locked_ = false;

    int size = trade_fronts.size();
    for (int i = 0; i < size; i++)
    {
        std::pair<std::string, unsigned short>  front = trade_fronts[i];
        api_->RegisterService(front.first.c_str(), front.second);
    }
    api_->SetTimeout(120);
}


GtaStockQuoter::~GtaStockQuoter()
{
    IGTAQTSApiEx::ReleaseInstance(api_);
}


int GtaStockQuoter::login(const LogonInfo &info, bool sync)
{
    return api_->Login(info.user_id, info.password);
}

int GtaStockQuoter::logout(const LogonInfo &info,  bool sync)
{
    return 0;
}

std::vector<Contract> GtaStockQuoter::getStockList(const char* market)
{
    char* market_tag = const_cast<char*>(market);
    std::vector<Contract> contracts;
    CDataBuffer<StockSymbol> list;
    api_->GetStockList(market_tag,list);
    int cnt = list.Size();
    
    for (int i = 0; i < cnt; i++)
    {
        std::vector<std::string> c = Util::split(list[i].Symbol, '.');
        Contract contract(map2QDExchType(c[1].c_str()), c[0]);
        contract.volume_multiple = 100;
        contracts.push_back(contract);
    }
    return contracts;
}

std::vector<TickData> GtaStockQuoter::querySnap(const std::vector<Contract> &contracts)
{
    std::string codes = contracts2string(contracts);
    std::vector<TickData> vec;
    CDataBuffer<CQuotationDataPtr> lst;
    RetCode code = api_->QuerySnap(Category_Quotation, const_cast<char*>(codes.c_str()), lst);
    int cnt = lst.Size();
    for (int i = 0; i< cnt; i++)
    {
        IQuotationData& quo_data = *lst[i];
        TickData tick;
        fromGtaStockTick(quo_data, &tick);
        vec.push_back(tick);
    }
    return vec;
}

int GtaStockQuoter::reqTick(const std::vector<Contract> &contracts, bool sync)
{   
    //std::string codes = contracts2string(contracts);
    //return api_->Subscribe(Category_Quotation, const_cast<char*>(codes.c_str()),(void*)"111");
    
    return subscribe(Category_Quotation, contracts);

}

int GtaStockQuoter::reqIndexTick(const std::vector<Contract> &contracts, bool sync)
{
    return subscribe(Category_Index, contracts);
}

int GtaStockQuoter::subscribe(const DataCategory category, const std::vector<Contract>& contracts)
{
    std::string codes = contracts2string(contracts);
    return api_->Subscribe(category, const_cast<char*>(codes.c_str()), (void*)"1111");
}

int GtaStockQuoter::unReqTick(const std::vector<Contract> &contracts, bool sync)
{
    std::string codes = contracts2string(contracts);
    return api_->UnsubscribeByCategory(Category_Quotation, const_cast<char*>(codes.c_str()));
}

// ---------------------- 回调函数 ------------------------------


void GtaStockQuoter::OnLoginState( RetCode errCode)
{
    if (errCode != 0)
        std::cout << "login fail error code = " << errCode << std::endl;
    else
        std::cout << "login succ"  << std::endl;
}

void GtaStockQuoter::OnConnectionState(MsgType msgType, RetCode errCode)
{
    std::cout << "On ConnectState msgType = " << msgType << ", errcode = " << errCode << std::endl; 
}

void GtaStockQuoter::OnSubscribe(const DataCategory msgCategory, IQuotationData& RealData, void*  pSessionTag)
{
    char* session = static_cast<char*>(pSessionTag);
    //std::cout << "On Subscribe session = " << session << ", msgCategory = " << msgCategory << std::endl;
    if (strcmp(session, "1111") == 0 && 
            (msgCategory == Category_Quotation || msgCategory == Category_Index))
    {
//        LOG4CXX_DEBUG(logger, "Quoter deal begin");
        TickData tick;
        fromGtaStockTick(RealData, &tick);
        on_tick(tick);
//        LOG4CXX_DEBUG(logger, "Quoter deal   end");
    }
}

}
