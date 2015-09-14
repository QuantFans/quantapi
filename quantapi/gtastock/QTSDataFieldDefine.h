//////////////////////////////////////////////////////////////////////////////
/// @file       QTSDataFieldDefine.h 
/// @brief      数据类定义文件，包括数据缓存模板类，按字段访问类，字段数据类定义
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_DATA_FIELD_DEFINE_H_
#define GTA_QTS_DATA_FIELD_DEFINE_H_
#include <memory>
#include "QTSDataType.h"


/// 数据缓存模板，用于管理返回数据内存
template<class T> class GTA_API_EXPORT CDataBuffer 
{
public:
    /// 构造函数
    /// @param  bAutoDel    -- 对象析构时自动删除内存标志
    CDataBuffer(bool bAutoDel = true)
        :m_DataBuffer(NULL),m_nSize(0),m_nStore(0),m_bAutoDel(bAutoDel){}
    virtual ~CDataBuffer()
    {
        if (NULL != m_DataBuffer && m_bAutoDel)
        {
            delete [] m_DataBuffer;
        }
    }

    /// 清空数据，重置缓存大小
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
    /// 返回数据首地址
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
    T*      m_DataBuffer;       ///< 数据指针
    int     m_nSize;            ///< 实际数据大小
    int     m_nStore;           ///< 缓存容量大小
    bool    m_bAutoDel;         ///< 自动删除内存标志，C接口需要保留内存返回用户，单独接口调用删除内存
};

/// 字段数值存储结构
class IFieldValue
{
public:
    ///构造函数
    IFieldValue(void* Data = NULL, FIELD_TYPE m_Type = Type_ERROR, FieldID FID = FID_ERROR, unsigned int len = 0);
    ~IFieldValue();

    /// 获取FieldID值
    /// @return FieldID值
    virtual FieldID GetFieldID() const;

    ///获取字段的类型
    ///@return FieldType  --返回字段的类型
    virtual FIELD_TYPE GetFieldType() const;

    /// 获取char类型数值
    /// @param  cValue  -- 返回数值
    /// @return true -- 正确返回数据， false -- 数据类型错误
    virtual bool GetChar(char& cValue) const;

    /// 获取short类型数值
    /// @param  SValue  -- 返回数值
    /// @return true -- 正确返回数据， false -- 数据类型错误
    virtual bool GetShort(short& sValue) const;

    /// 获取int类型数值
    /// @param  nValue  -- 返回数值
    /// @return true -- 正确返回数据， false -- 数据类型错误
    virtual bool GetInt(int& nValue) const;

    /// 获取unsigned int类型数值
    /// @param  unValue  -- 返回数值
    /// @return true -- 正确返回数据， false -- 数据类型错误
    virtual bool GetUInt(unsigned int& unValue) const;

    /// 获取字符串类型数值
    /// @param  pValue  -- 字符串内容
    /// @param  nSize   -- 字符串大小，如小于实际大小，则返回实际大小并返回失败
    /// @return true -- 正确返回数据， false -- 数据类型错误
    virtual bool GetString(char* pValue, unsigned int& nSize) const;

    /// 获取longlong字符类型数值
    /// @param  llValue -- 返回数值
    /// @return true -- 正确返回数据， false -- 数据类型错误
    virtual bool GetLonglong(long long& llValue) const;

    /// 获取unsigned longlong字符类型数值
    /// @param  ullValue -- 返回数值
    /// @return true -- 正确返回数据， false -- 数据类型错误
    virtual bool GetULonglong(unsigned long long& ullValue) const;

    /// 获取double类型数值
    /// @param  dbValue -- 返回数值
    /// @return true -- 正确返回数据， false -- 数据类型错误
    virtual bool GetDouble(double& dbValue) const;

    /// 获取float类型数值
    /// @param  FValue -- 返回数值
    /// @return true -- 正确返回数据， false -- 数据类型错误
    virtual bool GetFloat(float& FValue) const;

    /// 获取sequence类型数值(50档行情这种)
    /// @param  sqValue -- 返回数值
    /// @param  len     -- 行情档数， 如果小于实际的档数，返回实际档数并返回失败
    /// @return true -- 正确返回数据， false -- 数据类型错误
    virtual bool GetSequence(unsigned int* sqValue, unsigned int &len) const;

private:    
    FieldID m_FildID;                   ///< 字段ID    
    FIELD_TYPE m_Type;                        ///< 字段类型
    void* m_pData;                      ///< 字段数据
    unsigned int m_Strlen;              ///< 字符串长度（如果不是字符串，则值为0）
};


/// 行情数据，按字段返回数据结构
class IQuotationData
{

public:
    virtual ~IQuotationData(){}

    /// 字段个数
    /// @return int     --  当前数据结构中的字段个数
    virtual int Count() const = 0;

    /// 根据字段名称获取数值
    /// @param  FID         -- 字段ID标志
    /// @return IFieldValue -- 返回字段内容
    virtual IFieldValue& GetFieldValue(FieldID FID) = 0;

    /// 顺序读取根据字段名称获取数值，重载下标操作符
    /// @return IFieldValue -- 返回字段内容
    virtual const IFieldValue& operator [](int nPos) = 0;

    /// 按顺序读写方式
    virtual IFieldValue* SetFirstPos() = 0;

    /// 获取当前位置数值
    virtual IFieldValue* GetCurPosValue() = 0;

    /// 移到下一个字段
    virtual IFieldValue* SetNextPos() = 0;

    /// 访问数据迭代器类型定义
    typedef IFieldValue*  Iterator;

    /// 数据起始位置
    virtual Iterator begin() = 0;

    /// 数据结束位置，此处无数据
    virtual Iterator end() = 0;

};

/// 释放IQuotationData数据，防止跨编译器等导致错误
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

    ///初始化结构体
    /// @param pData   --  封装有行情数据的数据结构
    void Init(IQuotationData* pData)
    {
        m_pData = pData;
    }

    ///< 重载解引用操作符，返回行情数据
    ///< @return  IQuotationData  --  行情数据
    IQuotationData& operator*() const
    {
        return *m_pData;
    }

    ///< 重载指向操作符
    ///< @return  IQuotationData*  --  行情数据的指针
    IQuotationData *operator->() const
    {
        return m_pData;
    }

private:
    IQuotationData* m_pData;    // 行情数据的数据结构
};

#endif // GTA_QTS_DATA_FIELD_DEFINE_H_
