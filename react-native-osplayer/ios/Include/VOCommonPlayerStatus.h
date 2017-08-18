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

@protocol VOCommonPlayerStatus <NSObject>

/**
 * Get the player engine type.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return Player engine type, refer to {@link VO_OSMP_PLAYER_ENGINE}
 */
- (VO_OSMP_PLAYER_ENGINE) getPlayerType;


/**
 * Get the player status.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED, VO_OSMP_STATE_SUSPENDED.
 * </p>
 *
 * @return  player status. Refer to {@link VO_OSMP_STATUS}
 *
 * @deprecated This method is replaced by {@link getPlayerState}
 *
 */
- (VO_OSMP_STATUS) getPlayerStatus;

/**
 * Get the player state.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_STOPPED, VO_OSMP_STATE_PAUSED, VO_OSMP_STATE_SUSPENDED.
 * </p>
 *
 * @return  player status. Refer to {@link VO_OSMP_STATE}
  */
- (VO_OSMP_STATE) getPlayerState;


/**
 * Check if the stream can be paused.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  true if the stream can be paused
 */
- (bool) canBePaused;

/**
 * Check if the stream contains I-Frame.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return true if current stream contains I-Frame, else return false.
 */
- (BOOL) canPlayIframeOnly;


/**
 * Check if the opened data source is a live streaming.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return true if the data source is opened, is a streaming source and is a live streaming
 */
- (bool) isLiveStreaming;


/**
 * Get current playback position.
 *
 * <p>The returned value of getPosition is 0 until the SDK receives either the {@link VO_OSMP_CB_VIDEO_RENDER_START} callback 
 *    or the {@link VO_OSMP_CB_AUDIO_RENDER_START} callback.<ul>
 * <li> VOD: returns current playback position.
 * <li> Live streaming: relies on {@link VOCommonPlayerConfiguration#enableLiveStreamingDVRPosition:}
 *  <ol>
 *  <li>Enabled: returns 0 when playing at the live head. A negative position represents the offset into the DVR window with respect to live head
 *  <li>Disabled: returns the offset with respect to the beginning of the playback
 * </ul></p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  the position <ms>; -1 if unsuccessful
 */
- (long) getPosition;


/**
 * Get minimum position.
 *
 * <p><ul>
 * <li> For VOD: returns 0
 * <li> For Live: returns (getMaxPosition - DVR window size)
 * </ul></p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return The position (ms); -1 if unsuccessful
 */
- (long) getMinPosition;


/**
 * Get maximum position.
 *
 * <p><ul>
 * <li> VOD: returns the duration
 * <li> Live: relies on {@link VOCommonPlayerConfiguration#enableLiveStreamingDVRPosition:}
 *  <ol>
 *  <li>Enabled: always returns 0, which represents the live playhead
 *  <li>Disabled: returns the offset between the live playhead and the beginning of the playback
 * </ul></p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *	
 * @return The position (ms); -1 if unsuccessful
 */
- (long) getMaxPosition;


/**
 * Get the UTC position of current playback.
 *
 * <p>
 * valid states: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  the position <ms>; -1 if unsuccessful
 */
- (long long) getUTCPosition;


/**
 * Get duration of the stream.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  current stream duration <ms>; 0 if source is a live stream
 */
- (long) getDuration;


/**
 * Get the screen display brightness.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return Current display brightness (percent)
 */
- (int) getScreenBrightness;


/**
 * Get unique identifier of the device.
 * To get the UID, this method should be called after calling {@link VOCommonPlayerConfiguration#setDRMLibrary}.
 * Note that UID is only changed if the SDK is reinstalled. 
 * The application upgrade will not lead to the change of UID. 
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @return  unique identifier is successful; nil if unsuccessful
 */
- (NSString *) getDRMUniqueIdentifier;


/**
 * Get version information of a module.
 * <p>
 * The OSMP+ SDK is currently built using the same version for all modules.
 * Pass VO_OSMP_MODULE_TYPE_SDK instead of passing a module as an argument. 
 * </p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   module [in] module type.
 *
 * @return  version information of the given module
 */
- (NSString*) getVersion:(VO_OSMP_MODULE_TYPE)module;

/**
 * Get playback volume.
 *
 * @return playback volume
 */
- (float) getVolume;

/**
 * Get the download status.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   trackType [in] the track type {@link VO_OSMP_SOURCE_STREAMTYPE}
 *
 * @return download status of the given track type,  VO_OSMP_SS_MAX for error return
 */
- (VO_OSMP_DOWNLOAD_STATUS) getDownloadStatus:(VO_OSMP_SOURCE_STREAMTYPE)trackType;


/**
 * Get the valid buffer duration (in ms).
 *
 * <p>
 * valid states: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return Valid buffer duration, -1 for error return
 */
- (int) getValidBufferDuration;


/**
 * Get the SEI info.
 *
 * <p>
 * valid states: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * Additional API assumption: Only after enableSEI is called.
 * </p>
 *
 * @param   time [in] the time stamp of SEI to be obtained
 * @param   flag [in] the type flag of SEI info {@link VO_OSMP_SEI_INFO_FLAG}
 *
 * @return  the object according to flag if successful
 */
- (id) getSEIInfo:(long long)time flag:(VO_OSMP_SEI_INFO_FLAG)flag;


/**
 * Get the connection status of output control.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   type [in] the type flag of output control {@link VO_OSMP_OUTPUT_CONTROL_TYPE}
 *
 * @return  the status of connection
 */
- (BOOL) isOutputControlActive:(VO_OSMP_OUTPUT_CONTROL_TYPE)type;


/**
 * Get the enforce status of output control.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   type [in] the type flag of output control {@link VO_OSMP_OUTPUT_CONTROL_TYPE}
 *
 * @return  the status of enforce
 */
- (BOOL) isOutputControlEnforce:(VO_OSMP_OUTPUT_CONTROL_TYPE)type;


/**
 * Get the value from specified ID. Use this method only based on recommendations by VisualOn.
 *
 * @param   paramID  [in] Parameter id.
 * @param   pObj     [out] Returned parameter value; relies on parameter id.
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) getParameter:(int)paramID pObj:(void *)pObj;

@end
