#include "GtaFutureQuoter.h" 
#include "QutoSvrDefine.h" 
namespace QuantApi {

GtaFutureQuoter::GtaFutureQuoter(std::vector<std::pair<std::string, unsigned short>> trade_fronts)
{
    api_ = IGTAQTSInterface::CreateInstance(this);
    int size = trade_fronts.size();
    for (int i = 0; i < size; i++)
    {
        std::pair<std::string, unsigned short>  front =  trade_fronts[i];
        api_->RegisterService(front.first.c_str(), front.second);
    }

    api_->Connect();
    wait(true);
}

GtaFutureQuoter::~GtaFutureQuoter()
{
    //IGTAQTSInterface::ReleaseInstance(api_);  
}

int GtaFutureQuoter::login(const LogonInfo &info, bool sync)
{
    return 0;
}

int GtaFutureQuoter::logout(const LogonInfo &info,  bool sync)
{
    return 0;
}

std::vector<Contract> GtaFutureQuoter::getStockList(const char* market)
{
    std::vector<Contract> vec;
    api_->GetMarketList();
//    wait(true);
//    printf("market = %d\n", mdis_[5].mi.market);
//    api_->GetStockList(&mdis_[5].mi);

    MarketDataInfo mdi;
    mdi.mi.market = SHFX_Market;
    mdi.mi.source = L1_Quotation;
    mdi.type = Static_Data;
    std::cout << "query"  << std::endl;
    /// 增加/取消订阅.
    /// @param mdi 市场数据标志.
    /// @param dataType 数据类型，参见具体市场数据类型定义
    /// @param sm 订阅模式.
    /// @param mr 市场范围.
    /// @param codelist 个股列表，字符串形式，个股之间用','分隔,如果type是所有行情，传NULL.
    /// @param codelistLen 代码缓冲区长度.
    //api_->Subscribe(&mdi, SUBSCRIBE_MODE_SUBSCRIBE, MARKET_RANGE_ALL, NULL, 0);
    
    //std::cout << buf->GetBuf() << std::endl;
    std::cout << "1111"  << std::endl;
    wait(true);
    return vec;
}

int GtaFutureQuoter::reqTick(const std::vector<Contract> &contracts, bool sync)
{
    
    /// 增加/取消订阅.
    /// @param mdi 市场数据标志.
    /// @param dataType 数据类型，参见具体市场数据类型定义
    /// @param sm 订阅模式.
    /// @param mr 市场范围.
    /// @param codelist 个股列表，字符串形式，个股之间用','分隔,如果type是所有行情，传NULL.
    /// @param codelistLen 代码缓冲区长度.
    for (int i = 0; i < mdis_.size(); i++ )
    {
        
    api_->Subscribe(&mdis_[i], SUBSCRIBE_MODE_SUBSCRIBE, MARKET_RANGE_ALL, NULL , 0);
    }
}

//--------------------------
void GtaFutureQuoter::OnConnect(int reason)
{
    std::cout << "connect ret = " << reason << std::endl;
    notify();
}

void GtaFutureQuoter::OnMarketList(MarketDesc* mds, int cnt)
{   
    mdis_.clear();
    std::cout << "cnt = "  << cnt << std::endl;
    for (int i = 0; i < cnt; i++)
    {
        if (mds[i].mi.market != ZZFX_Market && mds[i].mi.market != DLFX_Market && mds[i].mi.market != SHFX_Market)
            continue;
        MarketDataInfo mdi;
        mdi.mi.source = mds[i].mi.source;
        mdi.mi.market = mds[i].mi.market;
        mdi.type = mds[i].dataTypes[0];
        mdis_.push_back(mdi);
        printf("marketinfo.source = %d, marketinfo.market = %d, desc = %s, dataTypeSize = %d\n",mdi.mi.source, mdi.mi.market, mds[i].desc, mds[i].dataTypeSize);
        for (int j = 0; j < mds[i].dataTypeSize; j++)
        {
            mdi.type = mds[i].dataTypes[j];
            printf("    \t md.type = %d\n", mdi.type);
            mdis_.push_back(mdi);
        }
        printf("=================================================\n");
    }
    notify();
    /*
    std::cout << "marketinfo.source = " << md->mi.source << std::endl;
    std::cout << "marketinfo.market = " << md->mi.market << std::endl;
    std::cout << "dataTypeSize = "  << md->dataTypeSize << std::endl;
    std::cout << "dataTypes = "  << md->dataTypes << std::endl;
    std::cout << "desc = " << md->desc << std::endl;
    */
}

void GtaFutureQuoter::OnStockList(MarketInfo* mi, void* data, int datalen)
{
    char* code_list = new char[datalen+1];
    memset(code_list, 0, datalen+1);
    memcpy(code_list, data, datalen);
    printf("datalen = %d\n", datalen );
    printf("marketinfo.source = %d, marketinfo.market = %d\n",mi->source, mi->market);
    printf("%s\n", code_list);
    
}

void GtaFutureQuoter::OnSubscribe(MarketDataInfo* mdi, int result)
{
    std::cout << "Subscribe ret = "  << result << std::endl;
}

void GtaFutureQuoter::OnRealData(MarketDataInfo* mdi, void* data, int datalen)
{
    std::cout << "datalen = " << datalen  << std::endl;
}

}
