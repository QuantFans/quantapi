/**
 * @file gtafuturequoter.h
 * @brief 
 * @author  HonePhy
 * @version 0.1
 * @date 2015-08-02
 */

#ifndef _GTAFUTUREQUOTER_H

#define _GTAFUTUREQUOTER_H
#include <atomic>
#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>
#include <quantapi/Quoter.h>
#include <quantapi/datastruct.h>

#include "GTAQTSInterface.h"
//#include "GTAMarketServiceApi.h" 

namespace QuantApi {


/**
* @brief GTA�����ѯ��
*
* ������GTAʵ����ɣ�һ����������һ������ص���
* ��ͨ������ͬ������ʵ���ͻص�ʵ�������һ������
*/
class GtaFutureQuoter : public Quoter, private IGTAMarketServiceCallback {

 public:

    GtaFutureQuoter(std::vector<std::pair<std::string, unsigned short>> trade_fronts);

    virtual ~GtaFutureQuoter();

    /** @brief �ʺŵ�¼�� */
    virtual int login(const LogonInfo &info, bool sync=true);

    /** @brief �ʺ��˳��� */
    virtual int logout(const LogonInfo &info,  bool sync);
     
    /**
      * @biref ��ȡ��Ʊ�б�
      * @param  market  -- �г���ʶ���ԡ�,���ָ����г���ʶ��ĩβ������\0������������ΪNULL
      */
    virtual std::vector<Contract> getStockList(const char* market);


    /**
      * @biref ȡ�ú�Լ����
      *
      * @��Լ�б�Contract.code����Ϊ�գ�exch_type������Ϊ��
      *  �����Լ����Ϊ�գ����ȡ���г������п���
      */
    virtual std::vector<TickData> querySnap(const std::vector<Contract> &contracts){

    }

    /**
     * @brief ����tick���ݡ�    
     *
     * @param contracts ��Լ���ϡ�
     * Contract.code����Ϊ�գ�exch_type������Ϊ��,�����Լ����Ϊ�գ����ȡ���г������к�Լ����
     * @param sync �Ƿ�ͬ�����á�
     *
     * @return 
     */
    virtual int reqTick(const std::vector<Contract> &contracts, bool sync);

    /**
     * @brief ȡ��tick���ݶ��ġ�
     *
     * @param contracts ��Լ���ϡ�
     * Contract.code����Ϊ�գ�exch_type������Ϊ��,�����Լ����Ϊ�գ����ȡ���г����к�Լ���鶩��
     * @param sync �Ƿ�ͬ�����á�
     *
     * @return 
     */
	virtual int unReqTick(const std::vector<Contract> &contracts, bool sync){

    }

    /**
     * @brief ��ǰ����
     *
     * @note ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ����ա�
     */
    virtual std::string getTradingDay()  { return "" ; }

protected:

    /** @brief tick���ݵ���ص�������*/
    virtual void on_tick(const TickData &tick) { }

 private:


    inline void wait(bool towait) 
	{ 
		if(towait) 
		{
			std::unique_lock<std::mutex> lock(syn_flag_);
			locked_ = true;
			m_cond.wait(lock);
		}
	}

	inline void notify() {
        if (locked_)
        {
		std::unique_lock <std::mutex> lock(syn_flag_);
		locked_ = false;
		m_cond.notify_all();
        }
	}

    inline int nextRequestId() { return ++request_id_; }

    inline void set_front_id(int id) { front_id_ = id; }
    inline void set_session_id(int id) { session_id_ = id; }
    inline int session_id() { return session_id_; }
    inline int front_id(int id) { return front_id_; }


    // ---------------------- �ص����� ------------------------------


    /// ֪ͨ�������ӽ��.
    /// 
    /// @param reason ���ӽ����־ 0�ɹ�������ʧ�ܣ����ʧ�ܴ����.
    virtual void OnConnect(int reason);

    /// ֪ͨ����Ͽ�.
    ///
    /// @param reason �����룬���ʧ�ܴ����.
    virtual void OnConnectionFail(int reason){
        std::cout << "connectfial ret = " << reason << std::endl;
    }

    /// ��¼���.
    /// 
    /// @param userID �û�ID.
    /// @param result ��¼�����0�ɹ���������ʧ��.
    virtual void OnLogon(int userID, int result){

    }

	/// ֪ͨ�г��б�����.
    /// @param md �г��б����ݣ�����cnt��MarketDesc.
    /// @param cnt �г�����.
    virtual void OnMarketList(MarketDesc* md, int cnt);

    /// ֪ͨ�г������б�.
    /// @param mi �г�.
    /// @param data �����б����ݣ�����֮���Զ��ŷָ�. 
    /// @param datalen ���ݳ���.
    virtual void OnStockList(MarketInfo* mi, void* data, int datalen);
    
    /// ����/ȡ�����Ĳ������.
    /// 
    /// @param mdi �г����ݱ�־
    /// @param result ������� 0�ɹ� ����ʧ��.
    virtual void OnSubscribe(MarketDataInfo* mdi, int result);

    /// ֪ͨʵʱ����.
    /// @param mdi �г����ݱ�־.
    /// @param dataType �������ͣ��μ������г��������Ͷ���
    /// @param data �������ݣ�ÿ���г���ͬ����Ӧ�����н���.
    /// @param datalen ���ݳ���
    virtual void OnRealData(MarketDataInfo* mdi, void* data, int datalen);

 private:
    int                 front_id_;	            ///< ǰ�ñ��
    int                 session_id_;	        ///< �Ự���

    IGTAQTSInterface    *api_;                  ///< ����ʵ��
    int                 request_id_;            ///< �Ự���
	
	std::mutex              syn_flag_;              ///< ͬ��
	std::atomic<bool>       locked_;                ///< �Ƿ���ס�������������������Ƿ�ִ�С�
	std::condition_variable m_cond;					//��������

    std::vector<MarketDataInfo> mdis_;
};
    
} /* QuantDigger */
#endif 
