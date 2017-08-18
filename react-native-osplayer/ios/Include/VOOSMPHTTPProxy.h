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

#import <Foundation/Foundation.h>
#import "VOOSMPType.h"

EXPORT_API
@interface VOOSMPHTTPProxy : NSObject
{
    NSString *  _proxyHost;
    int         _proxyPort;
}

/**
 * Proxy server host name or IP address. Set as "" to clear.
 */
@property (readwrite, retain, getter=getProxyHost) NSString * proxyHost;

/**
 * Proxy server port number. Set as 0 to clear.
 */
@property (readwrite, assign, getter=getProxyPort) int proxyPort;

/**
 * Initialize VOOSMPHTTPProxy with values.
 *
 * @param  proxyHost   [in] Server host name or IP address, must not be nil.
 *
 * @param  proxyPort   [in] Proxy server port number, must not be nil.
 */
- (id) init:(NSString *)proxyHost proxyPort:(int)proxyPort;

@end
