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

@protocol VOOSMPSessionData <NSObject>

/**
 * Get session data id
 *
 * @return session data id
 */
@property (readonly, retain, getter=getDataID) NSString* dataID;

/**
 * Get session data value
 *
 * @return value
 */
@property (readonly, retain, getter=getValue) NSString* value;

/**
 * Get session data uri
 *
 * @return uri
 */
@property (readonly, retain, getter=getURI) NSString* URI;

/**
 * Get session data language
 *
 * @return language
 */
@property (readonly, retain, getter=getLanguage) NSString* language;



@end


