/////////////////////////////////////////////////////////////////////////////////////////
// @file��CfxUdpStruct.h
// ��    �����н���UDP�������ݽṹ����
// ��    �ߣ�mars.zippo
// �������ڣ�2014-03-20
// ��    ����v1.0.0
// �޸�  �ߣ�
// �޸����ڣ�
// �޸����ݣ�
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef GTA_CFX_UDP_STRUCT_H
#define GTA_CFX_UDP_STRUCT_H

/// �н�������г�����
struct CFfexFtdcDepthMarketData
{
    char    szTradingDay[9];        ///< ������
    char    szSettlementGroupID[9]; ///< ���������
    int     nSettlementID;          ///< ������
    double  dLastPrice;             ///< ���¼�
    double  dPreSettlementPrice;    ///< �����
    double  dPreClosePrice;         ///< ������
    double  dPreOpenInterest;       ///< ��ֲ���
    double  dOpenPrice;             ///< ����
    double  dHighestPrice;          ///< ��߼�
    double  dLowestPrice;           ///< ��ͼ�
    int     nVolume;                ///< ����
    double  dTurnover;              ///< �ɽ����
    double  dOpenInterest;          ///< �ֲ���
    double  dClosePrice;            ///< ������
    double  dSettlementPrice;       ///< �����
    double  dUpperLimitPrice;       ///< ��ͣ���    
    double  dLowerLimitPrice;       ///< ��ͣ���
    double  dPreDelta;              ///< ����ʵ��
    double  dCurrDelta;             ///< ����ʵ��    
    char    szUpdateTime[9];        ///< ����޸�ʱ��    
    int     nUpdateMillisec;        ///< ����޸ĺ���    
    char    szInstrumentID[31];     ///< ��Լ����    
    double  dBidPrice1;             ///< �����һ
    int     nBidVolume1;            ///< ������һ
    double  dAskPrice1;             ///< ������һ
    int     nAskVolume1;            ///< ������һ
    double  dBidPrice2;             ///< ����۶�
    int     nBidVolume2;            ///< ��������
    double  dAskPrice2;             ///< �����۶�
    int     nAskVolume2;            ///< ��������
    double  dBidPrice3;             ///< �������
    int     nBidVolume3;            ///< ��������
    double  dAskPrice3;             ///< ��������
    int     nAskVolume3;            ///< ��������
    double  dBidPrice4;             ///< �������
    int     nBidVolume4;            ///< ��������
    double  dAskPrice4;             ///< ��������
    int     nAskVolume4;            ///< ��������
    double  dBidPrice5;             ///< �������
    int     nBidVolume5;            ///< ��������
    double  dAskPrice5;             ///< ��������
    int     nAskVolume5;            ///< ��������
};


#endif
