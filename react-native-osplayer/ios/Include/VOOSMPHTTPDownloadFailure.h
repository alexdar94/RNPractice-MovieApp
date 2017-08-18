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


/**
 * Enumeration of causes for HTTP failures.
 * VO_OSMP_HTTP_DOWNLOAD_FAILURE_REASON
 */
typedef enum {
    /** HTTP connection is failed. */
    VO_OSMP_HTTP_CONNECT_FAILED               = 0x00000000,
    
    /** HTTP is failed to get response, or response cannot be parsed or is too large. */
    VO_OSMP_HTTP_INVALID_RESPONSE             = 0x00000001,
    
    /** HTTP 4xx error */
    VO_OSMP_HTTP_CLIENT_ERROR                 = 0x00000002,
    
    /** HTTP 5xx error */
    VO_OSMP_HTTP_SERVER_ERROR                 = 0x00000003,
    
    /** Max value */
    VO_OSMP_HTTP_DOWNLOAD_FAILURE_REASON_MAX  = 0xFFFFFFFF
    
} VO_OSMP_HTTP_DOWNLOAD_FAILURE_REASON;


@protocol VOOSMPHTTPDownloadFailure <NSObject>

/**
 * Get the URL of HTTP download failure.
 *
 * @return  URL
 */
@property (readonly, retain, getter=getURL) NSString* URL;

/**
 * Get the reason of HTTP download failure.
 *
 * @return  reason of HTTP download failure
 */
@property (readonly, assign, getter=getReason) VO_OSMP_HTTP_DOWNLOAD_FAILURE_REASON reason;

/**
 * Get the response string of HTTP download failure if the failure reason is VO_OSMP_HTTP_CLIENT_ERROR or VO_OSMP_HTTP_SERVER_ERROR.
 * It is nil for other failure reasons.
 * 
 * @return  The response string of HTTP download failure from HTTP server. 
 * For example:
 * HTTP/1.1 403 Forbidden
 * Transfer-Encoding: chunked
 * Date: Fri, 18 Sep 2015 10:37:42 GMT
 * Server: visualon.com
 * socket :14
 */
@property (readonly, retain, getter=getResponse) NSString* response;

/**
 * Get the responsePayload of HTTP download failure.
 *
 * @return responsePayload
 */
@property (readonly, retain, getter=getResponsePayload) NSData *responsePayload;

@end

