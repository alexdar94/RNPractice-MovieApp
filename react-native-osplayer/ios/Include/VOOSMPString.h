/************************************************************************
VisualOn Proprietary
Copyright (c) 2012-2016, VisualOn, Inc. All Rights Reserved
 
All data and information contained in or disclosed by this document are 
confidential and proprietary information of VisualOn, Inc, and all rights 
therein are expressly reserved. By accepting this material, the recipient 
agrees that this material and the information contained therein are held 
in confidence and in trust. The material may only be used and/or disclosed 
as authorized in a license agreement controlling such use and disclosure.
 ************************************************************************/

#pragma once

#ifdef _METRO
#include "stdio.h"
#include "VOOSMPInterface.h"

class VOCommonPlayerAPI VOOSMPString
{
public:
    VOOSMPString(const char *str = "");
    VOOSMPString(const VOOSMPString &str);
    ~VOOSMPString();
    VOOSMPString& operator=(VOOSMPString rhs);
    
    friend bool operator==(const VOOSMPString&,const VOOSMPString&);
    friend bool operator!=(const VOOSMPString&,const VOOSMPString&);
    friend bool operator<(const VOOSMPString&,const VOOSMPString&);
    friend bool operator<=(const VOOSMPString&,const VOOSMPString&);
    friend bool operator>(const VOOSMPString&,const VOOSMPString&);
    friend bool operator>=(const VOOSMPString&,const VOOSMPString&);
    
    size_t length() const;
    bool empty() const;
    const char *c_str() const;
    void swap(VOOSMPString &rhs);
private:
    char *str_;
};
#else
#include <string>
typedef std::string VOOSMPString;
#endif