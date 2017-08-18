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
@interface VOOSMPVerificationInfo : NSObject
{
    VO_OSMP_SRC_VERIFICATION_FLAG _dataFlag;
    NSString* _verificationString;
    
    NSString* _responseString;
}

/**
* <p> Get the data flag. 
* <ul>
* <li>If the flag is 0, the data is the requested string; 
* <li>If the flag is 1, the data is the password; 
* <li>If the flag is 2, the data is customer data;
* <li>Other values are not supported.
* </ul></p>
*
* @return the dataFlag
*/
@property (readwrite, assign, getter=getDataFlag) VO_OSMP_SRC_VERIFICATION_FLAG dataFlag;

/**
 * Get the verification string.
 */
@property (readwrite, retain, getter=getVerificationString) NSString* verificationString;

/**
 * Get authentication response string.
 *
 * @return authentication response string (NSString)
 */
@property (readwrite, retain, getter=getResponseString) NSString* responseString;


/**
 * Initialize the verification info with values.
 *
 * @param dataFlag            [in] Set the data flag. If the flag is 0, the data is the requested string; If the flag is 1, the data is the password; If the flag is 2, the data is customer data; other values are not supported.
 * @param verificationString  [in] Set the verification string for the corresponding flag.
 *
 * @return  object if successful; nil if unsuccessful
 */
- (id) init:(VO_OSMP_SRC_VERIFICATION_FLAG)dataFlag verificationString:(NSString *)verificationString;

@end