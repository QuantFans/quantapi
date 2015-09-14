//////////////////////////////////////////////////////////////////////////////
/// @file       QTSDataFieldDefine.h 
/// @brief      �����ඨ���ļ����������ݻ���ģ���࣬���ֶη����࣬�ֶ������ඨ��
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_DATA_FIELD_DEFINE_H_
#define GTA_QTS_DATA_FIELD_DEFINE_H_
#include <memory>
#include "QTSDataType.h"


/// ���ݻ���ģ�壬���ڹ����������ڴ�
template<class T> class GTA_API_EXPORT CDataBuffer 
{
public:
    /// ���캯��
    /// @param  bAutoDel    -- ��������ʱ�Զ�ɾ���ڴ��־
    CDataBuffer(bool bAutoDel = true)
        :m_DataBuffer(NULL),m_nSize(0),m_nStore(0),m_bAutoDel(bAutoDel){}
    virtual ~CDataBuffer()
    {
        if (NULL != m_DataBuffer && m_bAutoDel)
        {
            delete [] m_DataBuffer;
        }
    }

    /// ������ݣ����û����С
    void ReSize(int nSize)
    {
        m_nSize = nSize;
        if (nSize > m_nStore)
        {
            if (NULL != m_DataBuffer)
            {
                delete [] m_DataBuffer;
                m_DataBuffer = NULL;
            }
            m_nStore = nSize;
            m_DataBuffer = new T[nSize];
        }
        memset(m_DataBuffer, 0, sizeof(T) * m_nStore);
    }
    /// ���������׵�ַ
    operator T *()
    {
        return m_DataBuffer;
    }
    T& operator [](int nIndex)
    {
        return m_DataBuffer[nIndex];
    }
    int Size()
    {
        return m_nSize;
    }
private:
    CDataBuffer(const CDataBuffer<T>& other){}
    CDataBuffer& operator = (const CDataBuffer<T> &other){}
    T*      m_DataBuffer;       ///< ����ָ��
    int     m_nSize;            ///< ʵ�����ݴ�С
    int     m_nStore;           ///< ����������С
    bool    m_bAutoDel;         ///< �Զ�ɾ���ڴ��־��C�ӿ���Ҫ�����ڴ淵���û��������ӿڵ���ɾ���ڴ�
};

/// �ֶ���ֵ�洢�ṹ
class IFieldValue
{
public:
    ///���캯��
    IFieldValue(void* Data = NULL, FIELD_TYPE m_Type = Type_ERROR, FieldID FID = FID_ERROR, unsigned int len = 0);
    ~IFieldValue();

    /// ��ȡFieldIDֵ
    /// @return FieldIDֵ
    virtual FieldID GetFieldID() const;

    ///��ȡ�ֶε�����
    ///@return FieldType  --�����ֶε�����
    virtual FIELD_TYPE GetFieldType() const;

    /// ��ȡchar������ֵ
    /// @param  cValue  -- ������ֵ
    /// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
    virtual bool GetChar(char& cValue) const;

    /// ��ȡshort������ֵ
    /// @param  SValue  -- ������ֵ
    /// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
    virtual bool GetShort(short& sValue) const;

    /// ��ȡint������ֵ
    /// @param  nValue  -- ������ֵ
    /// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
    virtual bool GetInt(int& nValue) const;

    /// ��ȡunsigned int������ֵ
    /// @param  unValue  -- ������ֵ
    /// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
    virtual bool GetUInt(unsigned int& unValue) const;

    /// ��ȡ�ַ���������ֵ
    /// @param  pValue  -- �ַ�������
    /// @param  nSize   -- �ַ�����С����С��ʵ�ʴ�С���򷵻�ʵ�ʴ�С������ʧ��
    /// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
    virtual bool GetString(char* pValue, unsigned int& nSize) const;

    /// ��ȡlonglong�ַ�������ֵ
    /// @param  llValue -- ������ֵ
    /// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
    virtual bool GetLonglong(long long& llValue) const;

    /// ��ȡunsigned longlong�ַ�������ֵ
    /// @param  ullValue -- ������ֵ
    /// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
    virtual bool GetULonglong(unsigned long long& ullValue) const;

    /// ��ȡdouble������ֵ
    /// @param  dbValue -- ������ֵ
    /// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
    virtual bool GetDouble(double& dbValue) const;

    /// ��ȡfloat������ֵ
    /// @param  FValue -- ������ֵ
    /// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
    virtual bool GetFloat(float& FValue) const;

    /// ��ȡsequence������ֵ(50����������)
    /// @param  sqValue -- ������ֵ
    /// @param  len     -- ���鵵���� ���С��ʵ�ʵĵ���������ʵ�ʵ���������ʧ��
    /// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
    virtual bool GetSequence(unsigned int* sqValue, unsigned int &len) const;

private:    
    FieldID m_FildID;                   ///< �ֶ�ID    
    FIELD_TYPE m_Type;                        ///< �ֶ�����
    void* m_pData;                      ///< �ֶ�����
    unsigned int m_Strlen;              ///< �ַ������ȣ���������ַ�������ֵΪ0��
};


/// �������ݣ����ֶη������ݽṹ
class IQuotationData
{

public:
    virtual ~IQuotationData(){}

    /// �ֶθ���
    /// @return int     --  ��ǰ���ݽṹ�е��ֶθ���
    virtual int Count() const = 0;

    /// �����ֶ����ƻ�ȡ��ֵ
    /// @param  FID         -- �ֶ�ID��־
    /// @return IFieldValue -- �����ֶ�����
    virtual IFieldValue& GetFieldValue(FieldID FID) = 0;

    /// ˳���ȡ�����ֶ����ƻ�ȡ��ֵ�������±������
    /// @return IFieldValue -- �����ֶ�����
    virtual const IFieldValue& operator [](int nPos) = 0;

    /// ��˳���д��ʽ
    virtual IFieldValue* SetFirstPos() = 0;

    /// ��ȡ��ǰλ����ֵ
    virtual IFieldValue* GetCurPosValue() = 0;

    /// �Ƶ���һ���ֶ�
    virtual IFieldValue* SetNextPos() = 0;

    /// �������ݵ��������Ͷ���
    typedef IFieldValue*  Iterator;

    /// ������ʼλ��
    virtual Iterator begin() = 0;

    /// ���ݽ���λ�ã��˴�������
    virtual Iterator end() = 0;

};

/// �ͷ�IQuotationData���ݣ���ֹ��������ȵ��´���
void GTA_API_EXPORT DelIQuotationData(IQuotationData* pQuotationData);

struct CQuotationDataPtr
{
public:
    CQuotationDataPtr():m_pData(NULL){}
    ~CQuotationDataPtr()
    {
        if (m_pData!=NULL)
        {
            DelIQuotationData(m_pData);
            m_pData = NULL;
        }
    }

    ///��ʼ���ṹ��
    /// @param pData   --  ��װ���������ݵ����ݽṹ
    void Init(IQuotationData* pData)
    {
        m_pData = pData;
    }

    ///< ���ؽ����ò�������������������
    ///< @return  IQuotationData  --  ��������
    IQuotationData& operator*() const
    {
        return *m_pData;
    }

    ///< ����ָ�������
    ///< @return  IQuotationData*  --  �������ݵ�ָ��
    IQuotationData *operator->() const
    {
        return m_pData;
    }

private:
    IQuotationData* m_pData;    // �������ݵ����ݽṹ
};

#endif // GTA_QTS_DATA_FIELD_DEFINE_H_
