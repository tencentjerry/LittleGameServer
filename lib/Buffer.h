#pragma once

#include "base.h"


namespace lib
{

template<const uint32 SIZE>
class CRingBuffer
{
    const static uint32 BUF_SIZE = SIZE;
public:
    CRingBuffer()
    {
        static_assert( (BUF_SIZE & BUF_SIZE -1) == 0, "must power of 2"); //必须是2的幂次方
        Reset();      
    }

    ~CRingBuffer()
    {

    }

    void Reset()
    {
        m_uStartPtr = 0;
        m_uEndPtr = 0;
    }

    bool IsEmpty() const
    {
        return m_uStartPtr == m_uEndPtr;
    }

    uint32 GetUsedSize() const
    {
        return m_uEndPtr - m_uStartPtr;
    }

    uint32 GetFreeSize() const
    {
        return SIZE - GetUsedSize();
    }

    int PutData(const char* strBuf, size_t BufSize)
    {
        if(BufSize > GetFreeSize())
        {
            return -1;
        } 

        uint32 len = std::min(BufSize, BUF_SIZE - (m_uEndPtr & (BUF_SIZE -1))) ;

        memcpy(m_strBuffer + (m_uEndPtr & (BUF_SIZE -1)), strBuf, len);

        memcpy(m_strBuffer, strBuf + len, BufSize - len);

        m_uEndPtr += BufSize;

        return 0;
    }

    int GetData(char* strBuf, const size_t BufSize)
    {
        if(GetUsedSize() < BufSize)
        {
            return -1;
        }

        uint32 uLen = std::min(BufSize, (m_uStartPtr & (BUF_SIZE -1)));

        memcpy(strBuf, m_strBuffer + (m_uStartPtr & (BUF_SIZE -1)), uLen);

        memcpy(strBuf + uLen, m_strBuffer, BufSize - uLen);

        m_uStartPtr += BufSize;


        if(m_uStartPtr == m_uEndPtr)
        {
            m_uStartPtr = 0;
            m_uEndPtr = 0;
        }
        return 0;
    }

private:
    char m_strBuffer[BUF_SIZE];
    uint32 m_uStartPtr;
    uint32 m_uEndPtr;
};
}
