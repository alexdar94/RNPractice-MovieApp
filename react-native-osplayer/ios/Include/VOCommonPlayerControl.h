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

#import "VOCommonPlayerDelegate.h"

#import "VOOSMPInitParam.h"
#import "VOOSMPOpenParam.h"
#import "VOOSMPType.h"
#import "VOOSMPImageData.h"
#import "VOOSMPAnalyticsFilter.h"

@protocol VOCommonPlayerControl <NSObject>


#pragma mark Player initialization

/**
 * Initialize a player instance.
 * <pre>This function must be called first to start a session.</pre>
 *
 * <p>
 * Valid state: Uninitialization.
 * Additional API assumption: Change State to VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   playEngineType  [in] Refer to {@link VO_OSMP_PLAYER_ENGINE}.
 * @param   initParam       [in] Currently unused, should be set to nil.
 * @return  player object if successful; nil if unsuccessful
 */
- (id) init:(VO_OSMP_PLAYER_ENGINE)playEngineType initParam:(VOOSMPInitParam *)initParam;

/**
 * Set surface view for video playback. Ensure that this API is called after calling {@link VOCommonPlayerControl#init}.
 * <p>It is NOT recommended to change the UIView(iOS)/CALayer(Mac OS) or its parent node during playback. If change of the UIView(iOS)/CALayer(Mac OS) or its parent node is needed during playback, it is recommended to perform the following steps:
 * <ol>
 * <li>Call {@link VOCommonPlayerControl#suspend}.</li>
 * <li>Change the UIView(iOS)/CALayer(Mac OS) or its parent node. Ensure that the change operation is completed before proceeding with next step.</li>
 * <li>Call {@link VOCommonPlayerControl#resume} with the new UIView(iOS)/CALayer(Mac OS).</li>
 * </ol></p>
 *
 * <p>
 * Valid state: Initialization.
 * </p>
 *
 * @param   view  [in] The UIView(iOS)/CALayer(Mac OS) to render video. Do not add other sub views in this view.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setView:(void*) view;


/**
 * Set dimensions (rect) of the video display.
 *
 * <p>
 * VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param Rect [in] The rectangle of view to display.
 *
 * @deprecated This method is replaced by {@link VOCommonPlayerControl#notifyViewSizeChanged} and will be removed in future.
 *  Modify the size of NSView directly to change the display area.
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) setDisplayArea:(Rect)rect;


/**
 * Notify the player that the view size has been changed.
 * <pre>This API should be called when the change of view size is done.</pre>
 *
 * <p>
 * VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) notifyViewSizeChanged;


#pragma mark Data source initialization

/**
 * Open a media source.
 *
 * @param   url             [in] Source file description (for example, an URL or a file descriptor, etc).
 * @param   flag            [in] The flag for opening media source. Refer to {@link VO_OSMP_SRC_FLAG}.
 * @param   sourceType      [in] Source format. Refer to {@link VO_OSMP_SRC_FORMAT}. Default value is {@link VO_OSMP_SRC_AUTO_DETECT}.
 * @param   openParam       [in] Parameters for opening a source. Refer to {@link VOOSMPOpenParam}. Valid fields depend on the value.
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) open:(NSString *)url flag:(VO_OSMP_SRC_FLAG)flag sourceType:(VO_OSMP_SRC_FORMAT)sourceType openParam:(VOOSMPOpenParam *)openParam;


/**
 * Open a media source.
 *
 * <p>
 * Valid state: Initialization.
 * Additional API assumption: Change State to VO_OSMP_STATE_OPENING.
 * </p>
 *
 * @param   source          [in] Source pointer. The type depends on the flag.
 * @param   flag            [in] The flag for opening media source. Set as {@link VO_OSMP_FLAG_SRC_PUSH_BUFFER_FUNCTION} at present.
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) openSource:(void *)source flag:(VO_OSMP_SRC_FLAG)flag;


/**
 * Close a media source. Framework is still available.
 *
 * <p>
 * Valid state: Opening, Ready, and Stop.
 * Additional API assumption: Change State to VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) close;


#pragma mark Runtime control

/**
 * Start playback.
 *
 * <p>
 * Valid state: Ready.
 * Additional API assumption: Change State to VO_OSMP_STATE_PLAYING.
 * </p>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) start;


/**
 * Pause playback.
 *
 * <p>
 * Valid state: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * Additional API assumption: Change State to VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) pause;


/**
 * Stop playback.
 *
 * <p>
 * Valid state: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * Additional API assumption: Change State to VO_OSMP_STATE_STOPPED.
 * </p>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) stop;


/**
 * Perform the seek operation.
 * <p>
 * For VOD and NTS streams, the seek operation cannot be performed until the player open completes.
 * For live stream, the seek operation cannot be performed until the player gets the VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_LIVESEEKABLE callback event.
 * </p>
 *
 * <p>
 * Valid state: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * Additional API assumption: Recommend to call less than 10 times per second to reduce performance impact.
 * </p>
 *
 * @param   msec [in] Requested seek position <ms>.
 * @return  position after seek operation; -1 if unsuccessful
 */
- (long) setPosition:(long)msec;


/**
 * Seek by UTC time.
 *
 * @param   msec [in] the requested  seek position (ms).
 * @return  Position after seek operation; -1 if seek failed.
 * @deprecated This method will be removed in future.
 */
- (long long) setUTCPosition:(long long)msec;


/**
 * Set playback volume.
 *
 * <p>
 * VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   value [in] A value of 0.0f indicates silence; a value of 1.0f indicates no attenuation.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setVolume:(float)value;


/**
 * Mute the audio.
 *
 * <p>
 * VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) mute;


/**
 * Unmute the audio.
 *
 * <p>
 * VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) unmute;


/**
 * Suspend the player.
 * <pre>The application layer should invoke this method on receiving notification when moving to background.</pre>
 *
 * <p>
 * VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * Additional API assumption: Change State to VO_OSMP_STATE_SUSPENDED. When system calls onPause() in Android and applicationWillResignActive() in iOS are received, applications must call suspend(). In plug-in solutions, since Java Script cannot detect suspend event, player engine calls suspend() automatically when the events are received and then issues VOOSMP_CB_SUSPEND event. Examples of events suspend() called automatically are PBT_APMSUSPEND in Windows and NSWorkspaceWillSleepNotification in Mac. Additionally in Android, suspend() calls pause() when software codec is used, but it calls stop() when hardware codec is used due to render surface, which is linked to hardware codec directly and needs to be destroyed. If application calls getPlayerStatus(), it will return different status. Suspend with "keepAudio" is not supported.
 * </p>
 *
 * @param keepAudio [in] Keep/pause audio. true for continuing to play audio, false to pause both video and audio.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful; error code if unsuccessful
 */
- (VO_OSMP_RETURN_CODE) suspend:(bool)keepAudio;


/**
 * Resume the player.
 * <pre>The application layer should invoke this method on receiving notification when moving to foreground.</pre>
 *
 * <p>
 * Valid state: Suspend.
 * Additional API assumption: In plug-in solutions, since Java Script cannot detect resume event, player engine calls resume() automatically when the events are received and then issues VOOSMP_CB_RESUME event. Examples of events suspend called automatically are PBT_APMRESUMESUSPEND and PBT_APMRESUMEAUTOMATIC in Windows and NSWorkspaceDidWakeNotification in Mac.
 * </p>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful; error code if unsuccessful
 */
- (VO_OSMP_RETURN_CODE) resume;


/**
 * Set aspect ratio of video.
 *
 * <p>
 * VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   ar  [in] Aspect ratio. Refer to {@link VO_OSMP_ASPECT_RATIO}.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful; error code if unsuccessful
 */
- (VO_OSMP_RETURN_CODE) setVideoAspectRatio:(VO_OSMP_ASPECT_RATIO)ar;


/**
 * Redraw the video.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) redrawVideo;


/**
 * Set the delegation to handle SDK events. Events are posted by sub-thread to {@link VOCommonPlayerDelegate#onVOEvent:param1:param2:pObj:}.
 *
 * <p>
 * Valid state: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   delegate [in] Event handler instance.
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setOnEventDelegate:(id <VOCommonPlayerDelegate>)delegate;


/**
 * Set screen display brightness.
 *
 * <p>
 * VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param brightness [in] Display brightness percentage. The valid range is from 0 to 100.
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setScreenBrightness:(int)brightness;


/**
 * Start periodic SEI data notifications.
 *
 * <p>
 * Valid state: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   interval [in] Time interval <ms> between two SEI data notifications.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) startSEINotification:(int)interval;


/**
 * Stop periodic SEI data notifications.
 *
 * <p>
 * Valid state: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) stopSEINotification;


/**
 * Capture a video image, only supported by {@link VO_OSMP_VOME2_PLAYER}. This feature is currently disabled.
 *
 * @return  video image data
 */
- (id<VOOSMPImageData>) captureVideoImage;


/**
 * Update a media source.
 *
 * <p>
 * Valid state: VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   url             [in] Source file description (for example, an URL or a file descriptor, etc.)
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful
 *
 * * <pre>To update media source, this API must be called after calling the {@link VOCommonPlayerControl#open:flag:sourceType:openParam:} method.</pre>
 *
 */
- (VO_OSMP_RETURN_CODE) updateSourceURL:(NSString *)url;


/**
 * Start periodic analytics data notifications. With each notification, analytics data of the past "interval" ms is provided.
 *
 * <p>
 * Valid state: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   interval [in] Time interval <ms> between two analytics data notifications.
 * @param   filter   [in] Filters, specified as an {@link VOOSMPAnalyticsFilter} object, to be applied to cached analytic data.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) startAnalyticsNotification:(int)interval filter:(VOOSMPAnalyticsFilter *)filter;


/**
 * Stop periodic analytics data notifications.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) stopAnalyticsNotification;

/**
 * Set preference for playback.
 *
 * <p>
 * Valid state: Initialization.
 * </p>
 *
 * @param preference [in]  Refer to {@link VO_OSMP_PREFERENCE}.
 *
 * {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) setPreference:(VO_OSMP_PREFERENCE) preference;

/**
 * Delete the player instance at the engine level. App still needs to consider the memory management of objective-C.
 *
 * <p>
 * Valid state: Initialization.
 * Additional API assumption: Change State to VO_OSMP_STATE_DESTROYED.
 * </p>
 *
 * {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) destroy;


@end

