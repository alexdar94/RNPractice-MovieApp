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
#import "VOOSMPRTSPPort.h"
#ifndef SKIP_IN_MAIN_DOCUMENTATION
#import "VOOSMPRTSPStatistics.h"
#endif

@protocol VOCommonPlayerRTSPConfiguration <NSObject>


/**
 * Set RTSP connection type. The default value is {@link VO_OSMP_RTSP_CONNECTION_AUTOMATIC}.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   type   [in] Connection type. {@link VO_OSMP_RTSP_CONNECTION_TYPE}
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setRTSPConnectionType:(VO_OSMP_RTSP_CONNECTION_TYPE)type;


/**
 * Set the port number for RTSP connection.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   portNum   [in] port number
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setRTSPConnectionPort:(VOOSMPRTSPPort *)portNum;


/**
 * Get the RTSP module statistics.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  a {@link VOOSMPRTSPStatistics} object if successful; nil if failed
 */
- (id<VOOSMPRTSPStatistics>) getRTSPStatistics;


/**
 * Enable RTSP over HTTP tunnelling. RTSP over HTTP tunnelling is disabled by default.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   enable  [in] Enable/Disable; true to enable, false to disable(default).
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableRTSPOverHTTP:(bool)enable;


/**
 * Set the port number for RTSP over HTTP tunnelling.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   portNum   [in] port number
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setRTSPOverHTTPConnectionPort:(int)portNum;


/**
 * Set maximum socket errors while receiving data from the server before event {@link VO_OSMP_SRC_CB_RTSP_ERROR} (with parameter {@link VO_OSMP_SRC_RTSP_ERROR_SOCKET_ERROR}) is issued.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   count [in] maximum RTSP socket errors, default is 20000
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setRTSPMaxSocketErrorCount:(int)count;


/**
 * Set RTSP connection timeout.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   time [in] RTSP connection timeout (in seconds), default is 10 seconds
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setRTSPConnectionTimeout:(int)time;

@end

