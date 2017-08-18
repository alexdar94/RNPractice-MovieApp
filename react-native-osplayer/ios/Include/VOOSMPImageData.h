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

@protocol VOOSMPImageData <NSObject>

typedef enum
{
    /** The data is RGBA32 format. */
    VO_OSMP_IMAGE_RGBA32 = 0,
    
    /** Max value definition */
    VO_OSMP_IMAGE_MAX    = 0xFFFFFFFF
}VO_OSMP_IMAGE_TYPE;

/**
 * Get the image type.
 *
 * @return  image type
 */
@property (readonly, assign, getter=getImageType) VO_OSMP_IMAGE_TYPE imageType;

/**
 * Get the width of image.
 *
 * @return  width of image
 */
@property (readonly, assign, getter=getImageWidth) int imageWidth;

/**
 * Get the height of image.
 *
 * @return  height of image
 */
@property (readonly, assign, getter=getImageHeight) int imageHeight;

/**
 * Get size of image
 *
 * @return  size of image
 */
@property (readonly, assign, getter=getImageSize) int imageSize;

/**
 * Get the image data. Data content relies on {@link VO_OSMP_IMAGE_TYPE}.
 *
 * @return  image data
 */
@property (readonly, retain, getter=getBuffer) NSData* imageData;


@end
