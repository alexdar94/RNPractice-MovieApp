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
#import "VOOSMPVerificationInfo.h"
#import "VOOSMPImageData.h"
#import "VOOSMPSphericalVideoView.h"

@protocol VOCommonPlayerConfiguration <NSObject>

/**
 * Set contents of license file.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   data  [in] Contents of the license file in a Byte array.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 * <pre>To set contents of license file, this API must be called before calling the {@link VOCommonPlayerControl#open} method.</pre>
 */
- (VO_OSMP_RETURN_CODE) setLicenseContent:(NSData *)data;


/**
 * Set the location of the license file.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   path  [in] Location of the license file.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 * <pre>To set the location of license file, this API must be called before calling the {@link VOCommonPlayerControl#open} method.</pre>
 */
- (VO_OSMP_RETURN_CODE) setLicenseFilePath:(NSString *)path;


/**
 * Set pre-agreed license string.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   str   [in] Pre-agreed license string.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful.
 *
 * <pre>To set pre-agreed license string, this API must be called before calling the {@link VOCommonPlayerControl#open} method.</pre>
 */
- (VO_OSMP_RETURN_CODE) setPreAgreedLicense:(NSString *)str;


/**
 * Enable/Disable deblock. This is valid for H.264 and Real video. Enabled is set by default. 
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   value  [in] Enable/Disable; true to enable deblock (default), false to disable deblock.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) enableDeblock:(bool) value;


/**
 * Set the location of device capability file. The device capability file contains device-specific display sizes and bitrates to optimize performance. An example of cap.xml file is included with the SamplePlayer project.
 * This API only works when {@link VOCommonPlayerConfiguration#enableCPUAdaptation} is enabled. 
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   filename  [in] Location of device capability file.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful; error code if unsuccessful
 *
 * <pre>To set the location of capability file, this API should be called before calling the {@link VOCommonPlayerControl#open:flag:sourceType:openParam:} method.</pre>
 *
 */
- (VO_OSMP_RETURN_CODE) setDeviceCapabilityByFile:(NSString *)filename;


/**
 * Set the initial bitrate.
 * The player selects the closest stream at or below that number. If none is available,
 * the player selects the closest one above that number.
 * If an initial bitrate is not set, the player follows the streaming protocol specification.
 * If the behavior is undefined in the protocol being used, the player selects a stream based on definitions in cap.xml,
 * orders in the manifest file, and so on.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * default value: -1.
 * </p>
 *
 * @param   bitrate  [in] Bitrate <bps>.
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 * <p>To set the initial bitrate, this API must be called before calling the {@link VOCommonPlayerControl#open:flag:sourceType:openParam:} method.</p>
 *
 */
- (VO_OSMP_RETURN_CODE) setInitialBitrate:(int) bitrate;


/**
 * Set video display area.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param mode [in] Zoom mode. Refer to {@link VO_OSMP_ZOOM_MODE}.
 *
 * @param rect [in] The rectangular area of the video to be displayed. This argument is only used when the zoom mode is {@link VO_OSMP_ZOOM_ZOOMIN}. The rectangular area is expressed in terms of video pixel dimensions. When the video size is changed (e.g. due to a dynamic resolution switching), the player automatically adjusts the dimensions of the displayed rectangle according to the video scaling factor.
 *
 * This API cannot be implemented on Mac OS.
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) setZoomMode:(VO_OSMP_ZOOM_MODE)mode rect:(Rect)rect;


/**
 * Enable the position definition based on live streaming DVR window. 
 * This function is enabled by default. Set the value of this function to false to make Enter NTS work.
 * <p>
 * When enabled:
 * <p><ul>
 * <li> {@link VOCommonPlayerStatus#getPosition} returns 0 when playing at the live head. A negative position represents
 *      the offset into the DVR window with respect to live head
 * <li> {@link VOCommonPlayerStatus#getMaxPosition} always returns 0 that represents the live head
 * <li> {@link VOCommonPlayerStatus#getMinPosition} returns (getMaxPosition - DVR window size)
 * </ul></p>
 *
 * When disabled:
 * <p><ul>
 * <li> {@link VOCommonPlayerStatus#getPosition} returns the offset with respect to the beginning of the playback
 * <li> {@link VOCommonPlayerStatus#getMaxPosition} returns the offset between the live head and the beginning of the playback
 * <li> {@link VOCommonPlayerStatus#getMinPosition} returns (getMaxPosition - DVR window size)
 * </ul></p>
 * </p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   value  [in] Enable/Disable; true to enable(default), false to disable.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableLiveStreamingDVRPosition:(bool)enable;


/**
 * Set DRM Library name and API name.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param libName    [in] DRM library name.
 * @param libApiName [in] API name for exporting DRM library.
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful .
 *
 * <p>To set DRM library name and API name, this API must be called before calling the {@link VOCommonPlayerControl#open:flag:sourceType:openParam:} method.</p>
 * <p> If it is required to set the unique identifier or verification information, ensure that you call {@link VOCommonPlayerConfiguration#setDRMUniqueIdentifer} or {@link VOCommonPlayerConfiguration#setDRMVerificationInfo} after calling this API. </p>
 * <p> Meanwhile, ensure that {@link VOCommonPlayerConfiguration#setDRMUniqueIdentifer} is followed by {@link VOCommonPlayerConfiguration#setDRMVerificationInfo} if you need to set both functions.</p>
 */
- (VO_OSMP_RETURN_CODE) setDRMLibrary:(NSString *)libName libApiName:(NSString *)libApiName;


/**
 * Set the DRM adapter.
 *
 * This Api is for special customer which need to wrapper DRM themselves, need contact VisualOn before using it
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   adapter  [in] DRM adapter
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setDRMAdapter:(void *)adapter;


/**
 * Set the verification information to start DRM verification.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   info   [in] Verification information. {@link VOOSMPVerificationInfo}
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 * <p>To set the DRM verification information, <ul>
 * <li> This API must be called before calling the {@link VOCommonPlayerControl#open} method.
 * <li> This API must be called after calling the {@link VOCommonPlayerConfiguration#setDRMLibrary} method.
 * <li> This API must be called after calling the {@link VOCommonPlayerConfiguration#setDRMAdapter} method.
 * </ul></p>
 */
- (VO_OSMP_RETURN_CODE) setDRMVerificationInfo:(VOOSMPVerificationInfo *)info;

/**
 * Set the DRM file path
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * Additional API assumption: Must be called before setDRMVerificationInfo.
 * </p>
 *
 * @param filePath [in] file path
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) setDRMFilePath:(NSString *)filePath;

/**
 * Set unique identifier of the device.
 *
 * @param   string [in] Unique identifier string
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 * @deprecated use new function {@link VOCommonPlayerStatus#getDRMUniqueIdentifier}
 */
- (VO_OSMP_RETURN_CODE) setDRMUniqueIdentifier:(NSString *)string;

/**
 * Enable/Disable drm offline mode.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   enable  [in] Enable/Disable; true to enable, false to disable.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) enableDRMOfflineMode:(bool)enable;

/**
 * Add configuration for specail features.
 *
 * @param Json [in] Configuration string.
 *
 * @return {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful.
 *
 */
- (VO_OSMP_RETURN_CODE)addConfiguration:(NSString *)configString;

/**
 * Set the initial buffering time before starting playback.
 *
 * @param   time [in] buffering time <milliseconds>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 * @deprecated This method is replaced by {@link setInitialBufferingTime:} and will be removed in the future.
 
 */
- (VO_OSMP_RETURN_CODE) setInitialBufferTime:(int)time;

/**
 * Set the initial buffering time before starting playback.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * default value: 4000ms.
 * </p>
 *
 * @param   time [in] buffering time <milliseconds>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setInitialBufferingTime:(int)time;


/**
 * Set the maximum buffering time for playback.
 *
 * @param   time [in] buffering time (milliseconds)
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 * @deprecated This method is replaced by {@link setMaxBufferingTime:} and will be removed in the future.
 */
- (VO_OSMP_RETURN_CODE) setMaxBufferTime:(int)time;


/**
 * Set the maximum buffering time for playback.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * default value: 40000ms.
 * </p>
 *
 * @param   time [in] buffering time (milliseconds)
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setMaxBufferingTime:(int)time;


/**
 * Set the buffering time when re-buffering is needed during playback.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * default value: 5000ms.
 * </p>
 *
 * @param   time [in] buffering time (milliseconds)
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) setPlaybackBufferingTime:(int)time;


/**
 * Set the buffering time for continuous playback when re-buffering is needed.
 *
 * @param   time [in] buffering time (milliseconds)
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful.
 *
 * @deprecated This method is replaced by {@link VOCommonPlayerConfiguration#setPlaybackBufferingTime:} and will be removed in the future.
 */
- (VO_OSMP_RETURN_CODE) setAnewBufferingTime:(int)time __attribute__((deprecated));


/**
 * Enable/Disable playback of the audio stream. Enable is set by default.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   value  [in] Enable/Disable; true to enable, false to disable.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) enableAudioStream:(bool) value;


/**
 * Enable/Disable playback of the video stream. Enable is set by default.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   value  [in] Enable/Disable; true to enable, false to disable.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) enableVideoStream:(bool) value;


/**
 * Enable/Disable immediate video rendering with low latency.
 * This function is only applicable to video-only streams. Disable is set by default.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * Additional API assumption: Only for RTSP.
 * </p>
 *
 * @param   value  [in] Enable/Disable; true to enable, false to disable.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) enableLowLatencyVideo:(bool) value;


/**
 * Enable/Disable audio effect. Disable is set by default.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   value  [in] Enable/Disable; true to enable, false to disable.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) enableAudioEffect:(bool) value;


/**
 * Enable/Disable PCM data output. Disable is set by default.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   value  [in] Enable/Disable; true to enable PCM data output, false to disable (default).
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) enablePCMOutput:(bool) value;


/**
 * Set audio playback speed.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   speed  [in] speed multiplier with respect to realtime playback. Default is 1.0.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) setAudioPlaybackSpeed:(float)speed;

/**
 * Set I-Frame only mode.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * default disabled.
 * </p>
 *
 * @param enable    [in] I-Frame mode enabled or disabled.
 * @param speed    [in] I-Frame mode speed rate.
 * @return {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) setPlayIFrameOnly:(BOOL)enable Speed:(float)speed;


/**
 * Set the presentation delay time for a live streaming source.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * default value: -1.
 * </p>
 *
 * @param   time [in] presentation delay time (milliseconds) for a live streaming source with respective to current time
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setPresentationDelay:(int)time;


/**
 * Enable/Disable processing SEI information.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   flag [in] the flag {@link VO_OSMP_SEI_INFO_FLAG}. Set to VO_OSMP_SEI_INFO_NONE to disable processing SEI information or any other flags to enable.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableSEI:(VO_OSMP_SEI_INFO_FLAG)flag;

/**
 * Indicate to post process video data with SEI
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param value [in] Enable/disable process; true to enable, false to disable(default).
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) enableSEIPostProcessVideo:(bool)value;

/**
 * Set the number of retry attempts in progressive download module when network connection fails.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   times [in] the number of retry attempts. Default is 2. Setting this value to -1 to continue retrying until {@link VOCommonPlayerControl#stop} be called.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setPDConnectionRetryCount:(int)times;


/**
 * Enable/disable CPU adaptation; CPU adaptation is enabled by default. 
 * When CPU adaptation is enabled, the player will adapt to a lower bitrate automatically if high CPU loading happens and frame drops.  
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   value  [in] Enable/Disable; true to enable, false to disable.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) enableCPUAdaptation:(bool)value;


/**
 * Set upper/lower bitrate threshold for adaptation.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param upper [in] Maximum bitrate that the adaptation cannot exceed (bps) in addition to the constraint defined in the device capability file {@link VOCommonPlayerControl#setDeviceCapabilityByFile}.
 * <p><ul>
 * <li> If the value is 0, the maximum bitrate is constrained by the device capability file if it is specified. Otherwise the maximum bitrate is unconstrained.
 * <li> If the value is not 0 and the device capability file is not specified, it defines the maximum bitrate threshold
 * <li> If the value is not 0 and the device capability file is specified, the maximum bitrate threshold is defined as min(upper, max bitrate in device capability file)
 * </ul><p>
 * @param lower [in] Minimum bitrate that the adaptation cannot drop below (bps).
 * <p><ul>
 * <li> If the value is 0, the minimum threshold is unconstrained
 * <li> If the value is not 0, it defines the minimum bitrate threshold that adaptation cannot drop below.
 * </ul><p>
 * @return {@link VO_OSMP_ERR_NONE} if successful.
 *
 * <p> It is recommended to call this API before calling the {@link VOCommonPlayerControl#open:flag:sourceType:openParam:} method. However if it is necessary to set the bitrate threshold during playback, call this API when needed, then the player might have a little delay and starts downloading for playback with the defined bitrate.</p>
 *
 */
- (VO_OSMP_RETURN_CODE) setBitrateThreshold:(int)upper lower:(int)lower;


/**
 * Set the maximum number of retry attempts to download a corresponding segment from a
 * different bitrate due to DRM errors, server issues, or unsupported media format.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED..
 * </p>
 *
 * @param times [in] Maximum number of retry attempts. The default is 0.
 * @return {@link VO_OSMP_ERR_NONE} if successful.
 *
 * <pre>To set the maximum retry times, this API must be called before calling the {@link VOCommonPlayerControl#open:flag:sourceType:openParam:} method.</pre>
 *
 */
- (VO_OSMP_RETURN_CODE) setSegmentDownloadRetryCount:(int) times;


/**
 * Enable/Disable loading Dolby libraries. Enable is set by default.
 *
 * @param   value  [in] Enable/Disable; true to enable, false to disable.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 * @deprecated This method is replaced by {@link VOCommonPlayerConfiguration#enableAudioDecoderLibrary:} and will be removed in the future.
 */
- (VO_OSMP_RETURN_CODE) enableDolbyLibrary:(bool) value;


/**
 * Enable/Disable loading audio decoder libraries. Enable is set by default. Disable loading an audio library is usually required when the device or application does not have a proper license in place to use the library.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   type  [in] Audio decoder type {@link VO_OSMP_AUDIO_CODEC_TYPE} .
 * @param   value  [in] Enable/Disable; true to enable, false to disable.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) enableAudioDecoderLibrary:(VO_OSMP_AUDIO_CODEC_TYPE) type value:(bool) value;


/**
 * Set endpoint of audio effect.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   type  [in] Endpoint type {@link VO_OSMP_AUDIO_EFFECT_ENDPOINT_TYPE} .
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) setAudioEffectEndpointType:(VO_OSMP_AUDIO_EFFECT_ENDPOINT_TYPE)type;

/**
 * Reserved. Do not use it except for recommendations by VisualOn. 
 *
 * @param   msg  [in] Message.
 *
 * @return  string of return value
 *
 */
- (NSString *) sendAudioEffectMessage:(NSString *)msg;

/**
 * Set the HDCP policy.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param policyType    [in] HDCP policy type. {@link VO_OSMP_HDCP_POLICY} .
 * @return      {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) setHDCPPolicy:(VO_OSMP_HDCP_POLICY) policyType;

/**
 * Set URL query string, the query string should be in the format of "key1=value&key2=value".
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   string  [in] query string.
 *
 * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful.
 *
 */
- (VO_OSMP_RETURN_CODE) setURLQueryString:(NSString *)string;

/**
 * Enable anti-mirror. Disable is set by default.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   enable  [in] Enable/Disable; true to enable, false to disable(default).
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableAntiMirror:(bool) enable;

/**
 * Enable card board video.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   enable  [in] Enable/Disable; true to enable, false to disable(default).
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableCardBoardVideo:(bool)enable;

/**
 * Enable spherical video.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   enable  [in] Enable/Disable; true to enable, false to disable(default).
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableSphericalVideo:(bool)enable;

/**
 * Enable cubemap video.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   enable  [in] Enable/Disable; true to enable, false to disable(default).
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableCubemapVideo:(bool)enable;

/**
 * Set spherical video view.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   view  [in] {@link VOOSMPSphericalVideoView}.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSphericalVideoView:(id<VOOSMPSphericalVideoView>) view;


/**
 * Set the value for a specified ID. This method should only be used on recommendation by VisualOn.
 *
 * @param   paramID  [in] Parameter id.
 * @param   pObj     [in] Parameter value; relies on parameter id.
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setParameter:(int)paramID pObj:(void *)pObj;

 /**
  * * Enable client DVR feature. This needs to be called before start()
  * * @param   timeLimit        [in] Time limit (in ms) of history.
  * * @param   storageLimit   [in] Storage limit (in byte) of history.
  * * @return  {@link VO_OSMP_ERR_NONE} if successful.
  */
- (VO_OSMP_RETURN_CODE) enableClientSideDVR:(long long)timeLimit storage:(long long)storageLimit;

 /**
  * * Disable client DVR feature. This needs to be called before start()
  * * @return  {@link VO_OSMP_ERR_NONE} if successful.
  */
- (VO_OSMP_RETURN_CODE) disableClientSideDVR;

@end

