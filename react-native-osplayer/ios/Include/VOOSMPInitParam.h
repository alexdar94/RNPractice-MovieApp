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
@interface VOOSMPInitParam : NSObject
{
    id          _context;
    NSString*   _libraryPath;
}


/**
 * Application context.
 */
@property (readwrite, retain, getter=getContext) id context;


/**
 * Library directory path.
 */
@property (readwrite, retain, getter=getLibraryPath) NSString* libraryPath;


/**
 * Initialize a filter with values.
 *
 * @return	object if successful; nil if unsuccessful
 */
- (id) init;

@end
