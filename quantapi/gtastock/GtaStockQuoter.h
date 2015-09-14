/**
 * @file gtastockuoter.h
 * @brief 
 * @author  HonePhy
 * @version 0.1
 * @date 2015-07-30
 */

#ifndef _GTAQUOTER_H

#define _GTAQUOTER_H
#include <atomic>
#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>
#include "../Quoter.h" 
#include "../datastruct.h"
#include "GTAQTSInterfaceEx.h" 

namespace QuantApi {


/**
* @brief GTA�����ѯ��
*
* ������GTAʵ����ɣ�һ����������һ������ص���
* ��ͨ������ͬ������ʵ���ͻص�ʵ�������һ������
*/
class GtaStockQuoter : public Quoter, private IGTAQTSCallbackEx {

 public:

    GtaStockQuoter(std::vector<std::pair<std::string, unsigned short>> fronts);

    virtual ~GtaStockQuoter();

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
    virtual std::vector<TickData> querySnap(const std::vector<Contract> &contracts);

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
     * @brief ����ָ��tick���ݡ�    
     *
     * @param contracts ��Լ���ϡ�
     * Contract.code����Ϊ�գ�exch_type������Ϊ��,�����Լ����Ϊ�գ����ȡ���г������к�Լ����
     * @param sync �Ƿ�ͬ�����á�
     *
     * @return 
     */
    virtual int reqIndexTick(const std::vector<Contract> &contracts, bool sync);

    /**
     * @brief ȡ��tick���ݶ��ġ�
     *
     * @param contracts ��Լ���ϡ�
     * Contract.code����Ϊ�գ�exch_type������Ϊ��,�����Լ����Ϊ�գ����ȡ���г����к�Լ���鶩��
     * @param sync �Ƿ�ͬ�����á�
     *
     * @return 
     */
	virtual int unReqTick(const std::vector<Contract> &contracts, bool sync);

    /**
     * @brief ��ǰ����
     *
     * @note ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ����ա�
     */
    virtual std::string getTradingDay()  { return "" ; }

protected:

    /** @brief tick���ݵ���ص�������*/
    virtual void on_tick(const TickData &tick) {
        /*
        std::cout << tick.contract.code << std::endl 
            << tick.contract.exch_type << std::endl
            << tick.price << std::endl
            << tick.volume << std::endl
            << tick.total_price << std::endl;
        */
    }

 private:

    int subscribe(const DataCategory category, const std::vector<Contract>& contracts);

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


    /// ��½״̬����
    /// @param  errCode  -- ʧ��ԭ��(�û����ڡ��ظ���½)�û�������������д���
    virtual void OnLoginState( RetCode errCode);

    /// ����״̬���أ����ӳɹ�/ʧ��
    /// @param  msgType      -- ��Ϣ����
    /// @param  errCode     -- ʧ��ԭ�򣬳ɹ�ʱ����0
    virtual void OnConnectionState(MsgType msgType, RetCode errCode);

    /// �Ự��־ʧЧ������API���Ѿ�û��ʹ�ã�
    /// @param  pSessionTag    -- �Ự��־
    virtual void OnSessionTagInvalid(void* pSessionTag){}

    /// ��������ʵʱ�ص��ӿ�
    /// @param  msgCategory -- ���ص����ݷ���
    /// @param  RealData    -- ʵʱ����
    /// @param  pSessionTag -- ��������ʱ������û���־
    virtual void OnSubscribe(const DataCategory msgCategory, IQuotationData& RealData, void*  pSessionTag);


 private:
    int                 front_id_;	            ///< ǰ�ñ��
    int                 session_id_;	        ///< �Ự���

    IGTAQTSApiEx        *api_;                  ///< ����ʵ��
    int                 request_id_;            ///< �Ự���
	
	std::mutex              syn_flag_;              ///< ͬ��
	std::atomic<bool>       locked_;                ///< �Ƿ���ס�������������������Ƿ�ִ�С�
	std::condition_variable m_cond;					//��������
};
    
} /* QuantDigger */
#endif 
