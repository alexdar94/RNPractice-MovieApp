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

@protocol VOOSMPBuffer <NSObject>

/**
 * Get the buffer timestamp.
 *
 * @return  timestamp of buffer
 */
@property (readonly, assign, getter=getTimestamp) long long timestamp;


/**
 * Get the buffer size.
 *
 * @return  size of buffer
 */
@property (readonly, assign, getter=getBufferSize) int bufferSize;


/**
 * Get the buffer data.
 *
 * @return  buffer data
 */
@property (readonly, retain, getter=getBuffer) NSData* buffer;

@end
