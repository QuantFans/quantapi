/**
 * @brief   ����Э��ͷ���壬���鹫�����ֶ���
 */
#ifndef GTA_QUTO_SVR_DEFINE_H
#define GTA_QUTO_SVR_DEFINE_H
#ifdef _WIN32
#include <windows.h>
#else
typedef unsigned char      BYTE;
typedef unsigned short int WORD;
typedef unsigned int       DWORD;
typedef unsigned int       UINT;
typedef long long          LONGLONG;
typedef long long          __int64;
typedef unsigned long long UINT64;
typedef int                INT;
#endif

#define GTA_QTS_VERSION     2           // �汾����
//wCommandType
const WORD CT_Request           = 0;        //��ʶ��������
const WORD CT_Response          = 1;        //��ʶ��Ӧ����
const WORD CT_Initiative        = 2;        //��������

//wCommand
const WORD CD_Logon             = 0;        //����
const WORD CD_Logout            = 1;        //�ǳ�
const WORD CD_StateData         = 2;        //��̬����
const WORD CD_RealData          = 3;        //��������
const WORD CD_MarketList        = 4;        //�г��б�
const WORD CD_CodeList          = 5;        //�г������б�
const WORD CD_File              = 6;        //��ȡXXX�ļ�
const WORD CD_QuotSnap          = 7;        //�������
const WORD CD_StaticSnap        = 8;        //��̬���ݿ���
const WORD CD_ClientConnect     = 9;        //�ն�����
const WORD CD_ClientDisConnect  = 10;        //�ն˶���
const WORD CD_ListenInfo        = 11;        //������Ϣ
const WORD CD_ReConnect         = 12;        //����
const WORD CD_Heartbeat         = 13;        //����
const WORD CD_SPTable           = 14;        //��ۼ�λ������
const WORD CD_DL_StateData      = 15;        //���ؾ�̬��������
const WORD CD_DL_RealData       = 16;        //����������������

//btTransferType
const BYTE TR_Single            = 0;        //����
const BYTE TR_Multi             = 1;        //���

const BYTE S_Fail               = 0;
const BYTE S_Start              = 1;
const BYTE S_Continue           = 2;
const BYTE S_End                = 3;

//btCountry
const BYTE CN_Area              = 1;        //�й�

//btSource
const BYTE None_Type            = 0;
const BYTE L1_Quotation         = 1;        //Level1����
const BYTE L2_Quotation         = 2;        //Level2����

//btMarket
const BYTE SZ_Market            = 1;        //�����г�
const BYTE SH_Market            = 2;        //�Ϻ��г�
const BYTE HK_Market            = 3;        //����г�
const BYTE CFX_Market           = 4;        //�н�����ָ�ڻ�
const BYTE ZZFX_Market          = 5;        //֣����Ʒ�ڻ�
const BYTE DLFX_Market          = 6;        //������Ʒ�ڻ�
const BYTE SHFX_Market          = 7;        //�Ϻ���Ʒ�ڻ�
const BYTE FOREX_Market         = 8;        // ���
const BYTE SHIO_Market          = 9;        // ������Ȩ
const BYTE CFIO_Market          = 10;        // �н�����Ȩ

//btType
const BYTE Stock_Type           = 1;        //��Ʊ
const BYTE Future_Type          = 2;        //�ڻ�
const BYTE Option_Type          = 3;        //��Ȩ
const BYTE Bond_Type            = 4;        //ծȯ
const BYTE FX_Type              = 5;        //���
const BYTE Warrants_Type        = 6;        //Ȩ֤
const BYTE Fund_Type            = 7;        //����
const BYTE Industry_Type        = 8;        //ָ��
const BYTE Repo_Type            = 9;        //
const BYTE Convertible_Type     = 10;        //

//btDataClass
const BYTE RealTime_Info        = 1;        //ʵʱ��Ϣ
const BYTE Batch_Info           = 2;        //��ʼ����Ϣ
const BYTE Recovery_Info        = 3;        //�̺�����
const BYTE HK_SP_Info           = 4;        //���۱�

//btDataType
const BYTE Static_Data          = 0;            //��̬����
const BYTE Quotations_Data      = 1;            //��������
const BYTE RemainQty_Data       = 2;            //
const BYTE Index_Data           = 3;            //ָ������
const BYTE OrderQueue           = 4;            //UA3111
const BYTE OrderRanking         = 5;            //UA3103
const BYTE TransRankingByIndustry   = 6;    //UA3104
const BYTE SingleOrderCanRanking    = 7;    //UA3105
const BYTE ConOrderCancelRanking    = 8;    //UA3106
const BYTE VirtualAuctionPrice      = 9;    //UA3107
const BYTE Index                    = 10;    //UA3113
const BYTE NGTS_MarketOverview      = 11;    //UA3115
const BYTE NGTS_Transaction         = 12;    //UA3101
//const BYTE GD_6301_Data             = 13;   //�̶�����UA6301  
//const BYTE GD_6302_Data             = 14;   //�̶�����UA6302
//const BYTE GD_Static_Data           = 15;   //�̶�����       
const BYTE DFX_MBLQuot              = 13;       // �����������
const BYTE DFX_ArbiMBLQuot          = 14;       // �����������
const BYTE DFX_RealTimePrice        = 15;       // ʵʱ�����
const BYTE DFX_OrderStatistic       = 16;       // ί��ͳ��
const BYTE DFX_MarchPriceQty        = 17;       // �ּ۳ɽ���

//SZbtDataType  ����L2
const BYTE SzStockInfo              = 1;             //UA101
const BYTE SzStockStatus            = 2;             //UA102
const BYTE SzSnapshot               = 3;             //UA103
const BYTE SzIndex                  = 4;             //UA104
const BYTE SzOrder                  = 5;             //UA201
const BYTE SzTrade                  = 6;             //UA202
const BYTE SzBulletin               = 7;             //UA401


#pragma pack(1)
typedef struct _Common_Head
{
    WORD    wLength;            //���ݰ����ȣ����������ֶγ���
    BYTE    btVersion;          //�汾��
    WORD    wCommandType;       //��������: ���������������ݣ���Ӧ����
    WORD    wCommand;           //����: �������������(��֤�����ĵȱ�ʶ)
    BYTE    btTransferType;     //���Ϊ������仹�ǵ�������
}Common_Head;   //��������ͷ

typedef struct _Quotation_Head
{
    WORD    wProcessLayer;      // ��ʶ�ĸ��������
    BYTE    btCountry;          // �г�������ʶ
    BYTE    btSource;           // ������ȣ�l1, l2��
    BYTE    btMarket;           // �г���ʶ (SZ,SH,HK,CFX)
    BYTE    btType;             // Ʒ��(STOCK, Futures, Option, Bond, FX....)
    BYTE    btDataClass;        // ����(RealTime, Batch)
    BYTE    btDataType;         // ��������(Contract, RemainQty, Index .....)+++--

}Quotation_Head;    //������幫������

#define MAX_SNAPDATABUFFER  60000
#pragma pack()


#endif //GTA_QUTO_SVR_DEFINE_H
