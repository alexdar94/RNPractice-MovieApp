/************************************************************************
VisualOn Proprietary
Copyright (c) 2016, VisualOn Incorporated. All Rights Reserved

VisualOn, Inc., USA

All data and information contained in or disclosed by this document are
confidential and proprietary information of VisualOn, and all rights
therein are expressly reserved. By accepting this material, the
recipient agrees that this material and the information contained
therein are held in confidence and in trust. The material may only be
used and/or disclosed as authorized in a license agreement controlling
such use and disclosure.
************************************************************************/

#import <Foundation/Foundation.h>

#import "VOOSMPSphericalVideoView.h"

@interface VOOSMPSphericalVideoViewImpl : NSObject <VOOSMPSphericalVideoView>
{
}

@property (readwrite, assign, getter=getFOV) float FOV;

/**
 * Roll angle.
 */
@property (readonly, assign, getter=getRoll) float roll;


/**
 * Sensor roll angle.
 */
@property (readwrite, assign) float sensorRoll;


/**
 * Touch heading angle.
 */
@property (readwrite, assign) float touchHeading;


/**
 * Touch pitch angle.
 */
@property (readwrite, assign) float touchPitch;


/**
 * Touch scale. Not supported.
 */
@property (readwrite, assign) float touchRoll;


/**
 * Update orientation.
 */
- (void) updateOrientation:(int) orientation;


/**
 * Start sensor.
 */
- (void) start;


/**
 * Stop sensor.
 */
- (void) stop;

@end
