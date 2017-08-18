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

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
    
    /**
     * Enumeration of HDMI connection status
     */
    typedef enum {
        /** HDMI state is changed to disconnected.  */
        VO_OSMP_HDMISTATE_DISCONNECT = 0,
        /** HDMI state is changed to connected.     */
        VO_OSMP_HDMISTATE_CONNECT    = 1,
        /** The player cannot detect HDMI connection state. */
        VO_OSMP_HDMISTATE_UNKNOWN    = 2,
        
        VO_OSMP_HDMISTATE_MAX        = 0X7FFFFFFF
    } VO_OSMP_HDMI_CONNECTION_STATUS;
    
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

@protocol onHDMIConnectionChangeDelegate;


@protocol VOCommonPlayerHDMI <NSObject>

/**
 * Enable/disable HDMI connection detection.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   value [in] Enable/disable; true to enable HDMI detection, false to disable.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) enableHDMIDetection:(bool)value;

/**
 * Check if HDMI connection detection is supported.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  true if HDMI connection detection is supported, false if not supported
 */
- (bool) isHDMIDetectionSupported;

/**
 * Check if HDMI is connected.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  HDMI connection state, refer to {@link VO_OSMP_HDMI_CONNECTION_STATUS }
 */
- (VO_OSMP_HDMI_CONNECTION_STATUS) getHDMIStatus;

/**
 * Set a delegation for getting HDMI Connection change callback.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   listener [in] Listener, an onHDMIConnectionChangeListener instance.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setOnHDMIConnectionChangeDelegate:(id <onHDMIConnectionChangeDelegate>)delegate;

@end

@protocol onHDMIConnectionChangeDelegate<NSObject>
/**
 * Listener for getting HDMI state change event.
 *
 * @param   nID [in] Event ID type, refer to {@link VO_OSMP_HDMI_CONNECTION_STATUS }
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) onHDMIStateChangeEvent:(VO_OSMP_HDMI_CONNECTION_STATUS)nID;

@end

