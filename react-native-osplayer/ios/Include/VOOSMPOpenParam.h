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
#import "VOOSMPDrmLicenseManager.h"

EXPORT_API
@interface VOOSMPOpenParam : NSObject
{
    long                         _fileSize;
    long long                    _duration;
    int                          _decoderType;
    id<VOOSMPDrmLicenseManager>  _drmLicenseManager;
}

/**
 * Actual file size.
 */
@property (readwrite, assign, getter=getFileSize) long fileSize;


/**
 * Actual duration(ms).
 */
@property (readwrite, assign, getter=getDuration) long long duration;

/**
 * decoderType audio and video decoder types (bitwise-OR of values of {@link VO_OSMP_DECODER_TYPE}). It must have one audio decoder type and one video decoder type. Default is VO_OSMP_DEC_VIDEO_SW | VO_OSMP_DEC_AUDIO_SW

 */
@property (readwrite, assign, getter=getDecoderType) int decoderType;

/**
 * Drm License Manager
 */
@property (readwrite, retain, getter=getDrmLicenseManager) id<VOOSMPDrmLicenseManager> drmLicenseManager;


/**
 * Init an object.
 *
 * @return	object if successful; nil if unsuccessful
 */
- (id) init;

@end
