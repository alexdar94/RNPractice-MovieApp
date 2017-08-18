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
@interface VOOSMPRTSPPort : NSObject
{
    int        _audioConnectionPort;
    int        _videoConnectionPort;
}

/** 
 * Audio connection port.
 */
@property (readwrite, assign, getter=getAudioConnectionPort) int audioConnectionPort;

/**
 * Video connection port.
 */
@property (readwrite, assign, getter=getVideoConnectionPort) int videoConnectionPort;

/**
 * Initialize RTSP port with values.
 *
 * @param audioConnectionPort   [in] audio connection port.
 * @param videoConnectionPort   [in] video connection port.
 *
 * @return	object if successful; nil if unsuccessful
 */
- (id) init:(int)audioConnectionPort videoConnectionPort:(int)videoConnectionPort;

@end
