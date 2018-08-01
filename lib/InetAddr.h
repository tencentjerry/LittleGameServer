#pragma once

#include "type_define.h"

namespace lib
{

struct STAddrInfo
{
    STAddrInfo()
    {
    
    }
    
    void CopyTo(struct sockaddr& stAddr) const
    {
        return;
    }

    char m_szAddr[24];
    uint16 m_uPort;
};
}