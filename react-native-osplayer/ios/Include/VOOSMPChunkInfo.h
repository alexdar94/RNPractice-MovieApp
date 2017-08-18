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

@protocol VOOSMPChunkInfo <NSObject>

/**
 * Get the type of this chunk.
 *
 * @return chunk type
 */
@property (readonly, assign, getter=getType) int type;

/**
 * Get the root URL of manifest. It must be filled by parser.
 *
 * @return root URL
 */
@property (readonly, retain, getter=getRootURL) NSString* rootURL;

/**
 * Get the URL of this chunk. It can be a relative URL.
 *
 * @return chunk URL
 */
@property (readonly, retain, getter=getURL) NSString* URL;

/**
 * Get the starting offset time of this chunk. The units of ( startTime / timeScale * 1000 ) are ms.
 *
 * @return starting offset time of this chunk
 */
@property (readonly, assign, getter=getStartTime) long startTime;

/**
 * Get the duration of this chunk. The units of ( duration / timeScale * 1000 ) are ms.
 *
 * @return duration of this chunk
 */
@property (readonly, assign, getter=getDuration) long duration;

/**
 * Get the time scale of this chunk.
 *
 * @return time scale of this chunk
 */
@property (readonly, assign, getter=getTimeScale) long timeScale;

/**
 * Get the error code of this chunk.
 *
 * @return error code
 */
@property (readonly, assign, getter=getErrorCode) int errorCode;

/**
 * Get the error type of this chunk.
 *
 * @return error type
 */
@property (readonly, assign,getter=getErrorType) VO_OSMP_STREAMING_ERROR_TYPE errorType;

@end


