#pragma once

#include "base.h"


namespace lib
{
class CBuffer
{
public:
    CBuffer()
    {

    }

    ~CBuffer()
    {

    }

    void Print();
    
private:
    std::vector<char> m_stBuffer;

};
}
