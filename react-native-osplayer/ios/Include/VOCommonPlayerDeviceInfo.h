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

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
    
    /**
     * Enumeration device OS types.
     */
    
    typedef enum {
        /** iOS platform */
        VO_OSMP_DEVICE_INFO_OS_IOS       = 0,
        
        /** Mac OS X */
        VO_OSMP_DEVICE_INFO_OS_OSX       = 1,
        
        /** Android platform */
        VO_OSMP_DEVICE_INFO_OS_ANDROID   = 2,
        
        /** Max value definition */
        VO_OSMP_DEVICE_INFO_OS_MAX       = 0X7FFFFFFF
    } VO_OSMP_DEVICE_INFO_OS_TYPE;
    
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

@protocol VOCommonPlayerDeviceInfo <NSObject>

/**
 * Get the number of CPU cores.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  the number of CPU cores; -1 if get failed
 */
- (int) getNumberOfCores;


/**
 * Check if Neon is available.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  true if neon is available, false if not available
 */
- (bool) hasNeon;


/**
 * Get the maximum frequency of the CPU.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  maximum frequency of CPU; -1 if get failed
 */
- (long) getMaxCPUFrequency;


/**
 * Get OS Type.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  OS type {@link VO_OSMP_DEVICE_INFO_OS_TYPE}.
 */
- (VO_OSMP_DEVICE_INFO_OS_TYPE) getOSType;


/**
 * Get the OS version (the system version).
 * e.g. iOS: @"4.0"
 *      OS X: @"10.7.5"
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  OS version (NSString); nil if get failed
 */
- (NSString *) getOSVersion;


/**
 * Get the device model name.
 * e.g. @"iPhone2,1", @"iPhone4,1", @"iPod2,1", @"iPad1,1", @"iPad2,1"...
 *      @"MacBookPro8,2"...
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  device model (NString); nil if get failed
 */
- (NSString *) getDeviceModel;

@end


