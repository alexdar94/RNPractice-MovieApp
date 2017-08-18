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

@protocol VOOSMPSphericalVideoView <NSObject>

/**
 * get rotate matrix.
 */
- (void) getRotation:(float[9]) rotateMatrix;


/**
 * get 360 video's fov(Field of View), which could be changed by user's gesture.
 * <p><ul>
 * <li>The fov will be used to scale the video.
 * <li>The bigger the fov, the smaller the image.
 * <li>Default fov is 65.
 * </p></ul>
 *
 * @return the fov if successfully
 */
@property (readwrite, assign, getter=getFOV) float FOV;

@end

