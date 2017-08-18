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
#import "VOOSMPHTTPProxy.h"

@protocol VOCommonPlayerHTTPConfiguration <NSObject>


/**
 * Set the information to start HTTP verification.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   info   [in] Verification information. {@link VOOSMPVerificationInfo}
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) setHTTPVerificationInfo:(VOOSMPVerificationInfo *)info;


/**
 * set HTTP header.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param headerName  [in] Set-Cookie: to set cookie;  User-Agent: to set user agent; Del-Cookies: to clear all cookies; custom headers can also be set.
 *
 * @param headerValue [in] Corresponding value of 'headerName'.
 *
 * <p>If headerName is 'Set-Cookie', headerValue should be a string, for example:<ul>
 * <li> For http link:  cookie name=Test; domain=visualon.com; path=/; expires=2147483647;
 * <li> For https link: cookie name=Test; domain=visualon.com; path=/; expires=2147483647; secure=false;
 * </ul></p>
 *
 * <p>If headerName is 'User-Agent', headerValue should be a string that describes the user agent. </p>
 * <p>The default user agent strings for Android, iOS, and Windows are: <ul>
 * <li> Android: VisualOn OSMP+ Player(Android)
 * <li> iOS:     VisualOn OSMP+ Player(iOS)
 * <li> Windows: VisualOn OSMP+ Player(Windows)
 * </ul></p>
 *
 * <p>If headerName is 'Del-Cookies', all cookies are deleted when headerValue is "". An individual cookie can also be deleted (only one deleted at one time) by specifying the cookie name, domain and path in the headerValue.</p>
 *
 * <p>Tips of using setHTTPHeader API to set cookies:</p>
 * <p><ul><li>The first letter of reserved keywords must be in upper case, such as "Expires", "Max-Age", "Domain", "Path", "Secure" and "HttpOnly".</li>
 * <li>Http header name must be "Set-Cookie".Cookie value must contain "Domain" attribute.</li>
 * <li>"Secure=false" is an incorrect syntax (no need to add "=false"). If the cookie value has "Secure" attribute, it means this cookie is only used in "HTTPS" request. Otherwise, it means this cookie is used in "HTTP" and "HTTPS" requests.
 * <li>Path value must follow the RFC description.</li>
 * <li>The domain and the host of URL must be matched.</li>
 * <li>Multiple cookies can be set. For example, name1=Test1; Domain=A.com; Path=/; Expires=2147483647;name2=Test2; Domain=B.com; Path=/; Expires=2147483647</li>
 * </ul></p>
 *
 * <p>Note:</p>
 * <p>On Android, iOS and PPAPI, when playing back the next URL, the lastly set custom HTTP header will be used for all HTTP requests if the player is not closed and destroyed and the customer does not update the custom HTTP header.</p>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setHTTPHeader:(NSString *)headerName headerValue:(NSString *)headerValue;


/**
 * Set the HTTP proxy.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   proxy   [in] proxy settings  {@link VOOSMPHTTPProxy}
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setHTTPProxy:(VOOSMPHTTPProxy *)proxy;


/**
 * Set HTTP connection retry timeout.
 *
 * Make sure to set the timeout before calling open(). The setting is applicable only after data source has been opened successfully.
 *
 * <p>
 * Valid state: VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param time [in] interval, in seconds, in which the player attempts to re-establish the HTTP connection. The default is 120 seconds. Setting the value to -1 disables the timeout so that the player keeps retrying, until the connection is established again
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setHTTPRetryTimeout:(int)time;


/**
 * Enable/Disable sending HTTP request with gzip.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   enable  [in] Enable/Disable; true to enable, false to disable(default).
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableHTTPGzipRequest:(bool)enable;

@end

