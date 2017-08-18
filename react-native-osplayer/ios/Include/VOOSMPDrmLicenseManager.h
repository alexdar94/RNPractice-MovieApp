/************************************************************************
 VisualOn Proprietary
 Copyright (c) 2012-2015, VisualOn, Inc. All Rights Reserved
 
 All data and information contained in or disclosed by this document are
 confidential and proprietary information of VisualOn, Inc, and all rights
 therein are expressly reserved. By accepting this material, the recipient
 agrees that this material and the information contained therein are held
 in confidence and in trust. The material may only be used and/or disclosed
 as authorized in a license agreement controlling such use and disclosure.
 ************************************************************************/

#import <Foundation/Foundation.h>

const static NSString *DRM_TYPE = @"DRM_TYPE";

const static int PLAYREADY = 1;
const static int WIDEVINE  = 2;

@protocol VOOSMPDrmLicenseManager <NSObject>

/**
 * add preference dictionary object to a list
 *
 */
- (void)addPreference:(NSDictionary *)preferenceDict;

/**
 * get a list of preference dictionary objects
 *
 */
- (NSArray *)getPreference;

/**
 * get VenderID
 *
 */
- (NSString *)getVenderID;

/**
 * get Context
 *
 */
- (long)getContext;

@end
