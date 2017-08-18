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
extern "C" {
#endif /* __cplusplus */
    
    /**
     * Enumeration of callback event IDs.
     * VO_OSMP_CB_EVENT_ID
     */
    typedef enum {
        /** This event is emitted when undefined behaviours occurs. */
        VO_OSMP_CB_ERROR                                   = 0X8000000C,
        /** This event is emitted when the end of the audio and video content has been decoded and rendered. */
        VO_OSMP_CB_PLAY_COMPLETE                           = 0X00000001,
        /** This event is emitted when the video stream starts buffering. */
        VO_OSMP_CB_VIDEO_START_BUFFER                      = 0X00000003,
        /** VThis event is emitted when the video stream stops buffering.  */
        VO_OSMP_CB_VIDEO_STOP_BUFFER                       = 0X00000004,
        /** This event is emitted when the audio stream starts buffering. */
        VO_OSMP_CB_AUDIO_START_BUFFER                      = 0X00000005,
        /** This event is emitted when the audio stream stops buffering. */
        VO_OSMP_CB_AUDIO_STOP_BUFFER                       = 0X00000006,
        /** @deprecated, Buffering time in source;  */
        VO_OSMP_CB_SRC_BUFFER_TIME                         = 0X00000007,
        /** Buffering time in the source. Use getValidBufferDuration to get the current buffering time.  */
        VO_OSMP_CB_SRC_BUFFERING_TIME                      = 0X00000007,
        /** This event is emitted when the engine starts rendering the data. */
        VO_OSMP_CB_SEEK_COMPLETE                           = 0X0000000D,
        /** This event is emitted when the video aspect ratio of the source has been changed; param1 is {@link VOOSMPType.VO_OSMP_ASPECT_RATIO}.*/
        VO_OSMP_CB_VIDEO_ASPECT_RATIO                      = 0X0000000E,
        /** This event is emitted when the video resolution of the source has been changed; param1 is video width (px), param2 is video height (px). */
        VO_OSMP_CB_VIDEO_SIZE_CHANGED                      = 0X0000000F,
        /** This event is emitted when the codec is not supported. param1 is <0: audio codec|1: video codec>. */
        VO_OSMP_CB_CODEC_NOT_SUPPORT                       = 0X80000010,
        /** This event is emitted when video codec deblock occurs; param1 is <0:disable|1:enable>. */
        VO_OSMP_CB_DEBLOCK                                 = 0X00000011,
        /** This event is to notify the hardware decoder is available; param1 is <0: error|1: available>. */
        VO_OSMP_CB_HW_DECODER_STATUS                       = 0X00000013,
        /** This event is to notify the authentication response information, for example, report information from server;
         *  param obj is String: (detailed information). */
        VO_OSMP_CB_AUTHENTICATION_RESPONSE                 = 0X00000014,
        /** This event is emitted when subtitle language info is parsed and is available. */
        VO_OSMP_CB_LANGUAGE_INFO_AVAILABLE                 = 0X00000015,
        /** This event is emitted when video rendering starts or AVPlayer status is ready to play.*/
		VO_OSMP_CB_VIDEO_RENDER_START                      = 0X00000016,
        /** This event is emitted when opening source completes. */
        VO_OSMP_CB_OPEN_SRC_COMPLETE                       = 0X00000017,
        /** This event is to notify SEI info; param1 is a {@link VOOSMPType.VO_OSMP_SEI_INFO_FLAG}, pObj is an object depending on param1 */
        VO_OSMP_CB_SEI_INFO                                = 0X00000019,
        /** This event is emitted when audio rendering is failed. */
        VO_OSMP_CB_AUDIO_RENDER_FAIL                       = 0X8000001A,
        /** This event is emitted only when PCM data output is enabled. pObj should be VOOSMPPCMBuffer */
        VO_OSMP_CB_PCM_OUTPUT                              = 0X0000001C,
        /** This event is emitted when license check is failed. */
        VO_OSMP_CB_LICENSE_FAIL                            = 0X8000001D,
        /** This event is emitted when audio rendering starts. */
        VO_OSMP_CB_AUDIO_RENDER_START                      = 0X00000021,
        /** This event is to notify the Bluetooth handset status; param1 is <0: bluetooth off|1: bluetooth on>.
         *  Not implemented on iOS.*/
        VO_OSMP_CB_BLUETOOTHHANDSET_CONNECTION             = 0x00001011,
        /** This event is emitted when playback performance analytics info is available; param obj is {@link VOOSMPAnalyticsInfo}. */
        VO_OSMP_CB_ANALYTICS_INFO                          = 0x00001021,
        /** This event is emitted when playback stops on both local and external devices. param1 is {@link VOOSMPType.VO_OSMP_OUTPUT_CONTROL_TYPE} */
        VO_OSMP_CB_OUTPUT_CONTROL_BLOCK_PLAYBACK           = 0x00000024,
        /** This event is emitted when sending output to external devices is blocked. param1 is a combination of output protocal type, {@link VOOSMPType.VO_OSMP_OUTPUT_CONTROL_TYPE}, param2 is control flag(0: disable, 1: enable) */
        VO_OSMP_CB_OUTPUT_CONTROL_BLOCK_OUTPUT             = 0x00000025,
        /** This event is emitted when output control changes the video resolution of the source. param1 is current mode (0: normal mode, 1: downgraded mode) */
        VO_OSMP_CB_OUTPUT_CONTROL_CHANGE_RESOLUTION        = 0x00000026,
        /** @deprecated, Resolution is downgraded , param1 is current mode (0: normal mode, 1: downgraded mode) */
        VO_OSMP_CB_OUTPUT_CONTROL_DOWNGRADE_RESOLUTION     = 0x00000026,
        /** This event is emitted when multiple player instances are not supported. */
        VO_OSMP_CB_MULTIPLE_INSTANCES_NOT_SUPPORTED        = 0X00000029,
        /** This event is emitted when screen-capture software is running in system. */
        VO_OSMP_CB_OUTPUT_CONTROL_CAPTURE_SOFTWARE_RUNNING = 0X0000002B,
        /** This event is emitted when the system goes sleep. For desktop, this event is only supported when playing. */
        VO_OSMP_CB_SUSPEND                                 = 0x00000030,
        /** This event is emitted when the system wakes up. For desktop, this event is only supported when playing. */
        VO_OSMP_CB_RESUME                                  = 0x00000031,
        /** This event is emitted when Airplay state been changed 
            obj is a NSNumber and the Bool value of it mean whether airplay is on/off  */
        VO_OSMP_CB_OUTPUT_ROUTE_AIRPLAY                    = 0x00000032,
        /** This event is emitted when the decoder is selected. param1 is video type. Refer to {@link VOOSMPType.VO_OSMP_DECODER_TYPE}*/
        VO_OSMP_CB_DECODER_TYPE                            = 0x00000033,
        /** This event is emitted when the results for a single image arrive; obj is {@link VOOSMPThumbnail} */
        VO_OSMP_CB_THUMBNAILS_REQUEST_UPDATE               = 0x00000034,
         /** This event is emitted when one request section finishes; param1 is the request startPosition, and param2 is  {@link VO_OSMP_THUMBNAILS_REQUEST_RESULT} */
        VO_OSMP_CB_THUMBNAILS_REQUEST_FINISH               = 0x00000035,
        /** This event is emitted when playState is changed, param1 is new state VO_OSMP_STATE* , param2 is old state VO_OSMP_STATE* */
        VO_OSMP_CB_PLAYSTATE_CHANGED                       = 0x00000036,
        /** This event is emitted when {@link VO_OSMP_PREFERENCE#VO_OSMP_PREF_SUBTITLE_TO_EVENT} is enabled. obj is a string about subtitle*/
        VO_OSMP_CB_SUBTITLE_INFO                           = 0x00000037,
        
        /**
         * Enumeration of source callback event IDs.
         */
        /** Reserved. Do not use. */
        VO_OSMP_SRC_CB_CONNECTING                          = 0X02000001,
        /** Reserved. Do not use.*/
        VO_OSMP_SRC_CB_CONNECTION_FINISHED                 = 0X02000002,
        /** This event is emitted when the source connection times out. */
        VO_OSMP_SRC_CB_CONNECTION_TIMEOUT                  = 0X82000003,
        /** Reserved. Do not use.*/
        VO_OSMP_SRC_CB_CONNECTION_LOSS                     = 0X82000004,
        /** This event is to notify the HTTP download status; param 1 is int (0 - 100) */
        VO_OSMP_SRC_CB_DOWNLOAD_STATUS                     = 0X02000005,
        /** This event is emitted when the source connection is failed. */
        VO_OSMP_SRC_CB_CONNECTION_FAIL                     = 0X82000006,
        /** This event is emitted when the source download is failed. */
        VO_OSMP_SRC_CB_DOWNLOAD_FAIL                       = 0X82000007,
        /** This event is emitted when an error occurs in DRM engine; param 1 is the error code passed from DRM engine. The player stops playback when receiving this event.  */
        VO_OSMP_SRC_CB_DRM_FAIL                            = 0X82000008,
        /** Reserved. Do not use. */
        VO_OSMP_SRC_CB_PLAYLIST_PARSE_ERR                  = 0X82000009,
        /** This event is emitted when the maximum number of connections was reached. This event is applicable to RTSP only. */
        VO_OSMP_SRC_CB_CONNECTION_REJECTED                 = 0X8200000A,
        /** This event is emitted when the bitrate has been changed; param1 is new bitrate <bps> */
        VO_OSMP_SRC_CB_BA_HAPPENED                         = 0X0200000B,
        /** This event is emitted when the player detects that device is rooted/jailbroken, and DRM is not secure.*/
        VO_OSMP_SRC_CB_DRM_NOT_SECURE                      = 0X0200000C,
        /** This event is emitted when the device uses A/V output device but the license does not support it. */
        VO_OSMP_SRC_CB_DRM_AV_OUT_FAIL                     = 0X8200000D,
        /** This event is emitted when the download is failed and is waiting to be recovered. */
        VO_OSMP_SRC_CB_DOWNLOAD_FAIL_WAITING_RECOVER       = 0X8200000E,
        /** This event is emitted when the download recovery is successful. */
        VO_OSMP_SRC_CB_DOWNLOAD_FAIL_RECOVER_SUCCESS       = 0X0200000F,
        /** This event is emitted when the source opening is completed; param1 is {@link VO_OSMP_RETURN_CODE} */
        VO_OSMP_SRC_CB_OPEN_FINISHED                       = 0X02000010,
        /** This event is emitted when the customer tag information is available inside source; param1 is  {@link VO_OSMP_SRC_CUSTOMERTAGID} and
         *  other params rely on param1.
         */
        VO_OSMP_SRC_CB_CUSTOMER_TAG                        = 0X02000020,
        /**  This event is to notify the streaming information; param1 is {@link VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT} and
         *  other params rely on param1.
         */
        VO_OSMP_SRC_CB_ADAPTIVE_STREAMING_INFO             = 0X02000030,
        /** Adaptive streaming error warning, param1 is {@link VO_OSMP_SRC_ADAPTIVE_STREAMING_ERROR_EVENT} and
         *  other params rely on param1.
         */
        VO_OSMP_SRC_CB_ADAPTIVE_STREAMING_ERROR            = 0X02000040,
        /** @deprecated, Adaptive streaming error warning, param1 is {@link VO_OSMP_SRC_ADAPTIVE_STREAMING_WARNING_EVENT} and
         *  other params will depend on param1
         */
        VO_OSMP_SRC_CB_ADAPTIVE_STREAM_WARNING             = 0X02000050,
        /** Adaptive streaming error warning, param1 is {@link VO_OSMP_SRC_ADAPTIVE_STREAMING_WARNING_EVENT} and
         *  other params will depend on param1
         */
        VO_OSMP_SRC_CB_ADAPTIVE_STREAMING_WARNING          = 0X02000050,
        /** This event is emitted when RTSP error occurs; param1 will be defined to {@link VO_OSMP_SRC_RTSP_ERROR} */
        VO_OSMP_SRC_CB_RTSP_ERROR                          = 0X02000060,
        /** Reserved. Do not use. */
        VO_OSMP_SRC_CB_SEEK_COMPLETE                       = 0X02000070,
        /** This event is emitted when the program info has been changed in source. */
        VO_OSMP_SRC_CB_PROGRAM_CHANGED                     = 0X02000071,
        /** This event is emitted when the program info has been reset in source. */
        VO_OSMP_SRC_CB_PROGRAM_RESET                       = 0X02000072,
        /** This event is emitted when seeking to the last chunk of play list.(NTS link without END tag needs change to live mode) */
        VO_OSMP_SRC_CB_ADAPTIVE_STREAMING_SEEK2LASTCHUNK   = 0X02000073,
        /** This event is emitted when the network is not available now, but there is still  some buffering data that can be played back. */
        VO_OSMP_SRC_CB_NOT_APPLICABLE_MEDIA                = 0X02000074,
        /** This event is to notify the current media position downloaded by the progressive download module; param1 is the position */
        VO_OSMP_SRC_CB_PD_DOWNLOAD_POSITION                = 0X02000075,
        /** This event is to notify the current buffering percent of the progressive download module;  param1 is the percent */
        VO_OSMP_SRC_CB_PD_BUFFERING_PERCENT                = 0X02000076,
        /** This event is emitted when updating source URL is completed; param1 is {@link VO_OSMP_CB_EVENT_ID} */
        VO_OSMP_SRC_CB_UPDATE_URL_COMPLETE                 = 0X02000077,
        /** This event is to notify the preferred audio language; pObj is (NSString *) of ISO 639-2 language code or null if none of the languages is matched. */
        VO_OSMP_SRC_CB_PREFERRED_AUDIO_LANGUAGE            = 0X02000078,
        /** This event is to notify the preferred subtitle language; pObj is (NSString *) of ISO 639-2 language code or null if none of the languages is matched. */
        VO_OSMP_SRC_CB_PREFERRED_SUBTITLE_LANGUAGE         = 0X02000079,

        /** This event is a warning message that notifies DRM error occurs. The player continues playback when receiving this event. param 1 is the error code passed from DRM engine.  */
        VO_OSMP_SRC_CB_DRM_WARNING                         = 0X0200007B,
        
        /** This event is emitted when starting HTTP download. Parameter obj is the URL (NSString *) */
        VO_OSMP_SRC_CB_IO_HTTP_START_DOWNLOAD              = 0X04000001,
        /** This event is emitted when HTTP download is failed. Parameter obj is {@link VOOSMPHTTPDownloadFailure} 
         *  Set HTTP information using API in VOCommonPlayerHTTPConfiguration*/
        VO_OSMP_SRC_CB_IO_HTTP_DOWNLOAD_FAIL               = 0X04000002,

        /** Max value definition */
        VO_OSMP_CB_EVENT_ID_MAX                            = 0xFFFFFFFF
    } VO_OSMP_CB_EVENT_ID;
    
    
    /**
     * Enumeration of callback sync event IDs.
     * VO_OSMP_CB_SYNC_EVENT_ID
     *
     * <p>
     * This event is sent from sub-thread, do not update UI or call other VisualOn's APIs in callback (except API listed in comments).
     * </p>
     *
     * @deprecated This enumeration will be removed in the future.
     */
    typedef enum {
        /** Max value definition */
        VO_OSMP_CB_SYNC_EVENT_ID_MAX                        = 0XFFFFFFFF
        
    } VO_OSMP_CB_SYNC_EVENT_ID;

    
    /**
     * Enumeration of source customer tag IDs. Used in {@link VO_OSMP_SRC_CB_CUSTOMER_TAG} callback.
     * This enumeration is param1.
     */
    typedef enum {
        /** Param2 is time stamp (ms), obj is NSData for TimedTag content.*/
        VO_OSMP_SRC_CUSTOMERTAGID_TIMEDTAG              = 0X00000001,
        
        /**
         * Param 2 is time stamp(ms), obj is DASH emsg box with JSON format string. Name list:
         * <p><ul>
         * <li> scheme_id_uri (string)
         * <li> message_data (Base64 encoded string)
         * <li> id (int)
         * </ul></p>
         */
        VO_OSMP_SRC_CUSTOMERTAG_DASH_EMSG_BOX           = 0X00000002,

        /** Max value definition */
        VO_OSMP_SRC_CUSTOMERTAGID_MAX                   = 0xFFFFFFFF
    } VO_OSMP_SRC_CUSTOMERTAGID;
    
    
    /**
     * Enumeration of available stream info events.
     * Used in {@link VO_OSMP_SRC_CB_ADAPTIVE_STREAMING_INFO} callback.
     */
    typedef enum {
        /** This event is emitted when bitrate has been changed. {@link VOCommonPlayerDelegate} callback param2 is new bitrate (bps). */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_BITRATE_CHANGE                   = 0x00000001,
        /** This event is emitted when media type has been changed. {@link VOCommonPlayerDelegate} callback param2 is {@link VO_OSMP_AVAILABLE_TRACK_TYPE}. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_MEDIATYPE_CHANGE                 = 0x00000002,
        /** This event is to notify the program type. {@link VOCommonPlayerDelegate} callback param2 is{@link VO_OSMP_SRC_PROGRAM_TYPE}. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_PROGRAM_TYPE                     = 0x00000003,
        /** This event is emitted when chunk download starts. {@link VOCommonPlayerDelegate} callback param obj is {@link VOOSMPChunkInfo},
         *  If the return value of this callback is {@link VO_OSMP_SRC_ERR_CHUNK_SKIP}, source must drop this chunk. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_CHUNK_BEGINDOWNLOAD              = 0x00000004,
        /** This event is to notify the chunk download is dropped. {@link VOCommonPlayerDelegate} callback param obj will be {@link VOOSMPChunkInfo}. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_CHUNK_DROPPED                    = 0x00000005,
        /** Chunk download OK. {@link VOCommonPlayerDelegate} callback param obj will be {@link VOOSMPChunkInfo}. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_CHUNK_DOWNLOADOK                 = 0x00000006,
        /** This event is emitted when Chunk download is completed, callback param obj will be {@link VOOSMPPlaylistData} */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_PLAYLIST_DOWNLOADOK              = 0x00000007,
        /** This event is emitted when program has been changed in source. When this event is received, you should get program info again. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_PROGRAM_CHANGE                   = 0x00000008,
        /** This event is emitted when chunk is supported. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_FILE_FORMATSUPPORTED             = 0x00000009,
        /** This event is to notify the live clip can be sought. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_LIVESEEKABLE                     = 0x0000000A,
        /** This event is emitted after open, callback param obj will be an NSArray of {@link VOOSMPSessionData} */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_SESSION_DATA                     = 0x0000000D,
        
        /** Max value definition */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_INFOEVENT_MAX                               = 0xFFFFFFFF
    } VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT;
    
    
    /**
     * Enumeration of available streaming error codes.
     * Used in {@link VO_OSMP_SRC_CB_ADAPTIVE_STREAMING_ERROR} callback
     */
    typedef enum {
        /** Reserved. Do not use. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_ERROR_EVENT_PLAYLIST_PARSEFAIL              = 0x00000001,
        /** Reserved. Do not use. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_ERROR_EVENT_PLAYLIST_UNSUPPORTED            = 0x00000002,
        /** This event is emitted when the sream is not supported. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_ERROR_EVENT_STREAMING_UNSUPPORTED           = 0x00000003,
        /** 
	 * <p>
     * If the download of master playlist is failed, this event is emitted immediately.<br>
     * If the download of media playlist is failed:<ul>
	 * <li> Live: this event will be emitted after two minutes. </li>
	 * <li> VOD:  this event will be emitted after HLS parser attempts to retry the download of total playsession (multiple playlists) five times. For every single playlist, the HLS parser attempts to retry the download four times. </li>
	 * </ul>
	 * If the download of media segment is failed:<ul>
	 * <li> Live: this event will be emitted after two minutes. </li>
	 * <li> VOD: every segment is retried for 3 times. This event will be emitted if continuous ten segments have been retried. </li>
	 * </ul>
     * </p>
		*/
        VO_OSMP_SRC_ADAPTIVE_STREAMING_ERROR_EVENT_STREAMING_DOWNLOADFAIL          = 0x00000004,
        /** This event is emitted when DRM error occurs.
            param 1 is  the error code passed from DRM engine. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_ERROR_EVENT_STREAMING_DRMLICENSEERROR       = 0x00000005,
        
        /** Max value definition */
        VO_OSMP_SRC_ADAPTIVESTREAMING_ERROR_EVENT_MAX                              = 0xFFFFFFFF
    } VO_OSMP_SRC_ADAPTIVE_STREAMING_ERROR_EVENT;
    
    /**
     * Enumeration of thumbnail request result.
     */
    typedef enum {
        VO_OSMP_THUMBNAILS_REQUEST_SUCCESS,
        VO_OSMP_THUMBNAILS_REQUEST_FAILED,
        VO_OSMP_THUMBNAILS_REQUEST_IGNORE
    } VO_OSMP_THUMBNAILS_REQUEST_RESULT;
    
    /**
     * Enumeration of available streaming warning events.
     * Used in {@link VO_OSMP_SRC_CB_ADAPTIVE_STREAMING_WARNING} callback.
     */
    typedef enum {
        /** This event is emitted when any chunk download is failed; {@link VOCommonPlayerDelegate} callback param obj will be {@link VOOSMPChunkInfo}. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_WARNING_EVENT_CHUNK_DOWNLOADERROR           = 0x00000001,
        /** This event is emitted when chunk format is not supported; {@link VOCommonPlayerDelegate} callback param obj will be {@link VOOSMPChunkInfo}. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_WARNING_EVENT_CHUNK_FILEFORMATUNSUPPORTED   = 0x00000002,
        /** This event is emitted when DRM error occurs; {@link VOCommonPlayerDelegate} callback param obj will be {@link VOOSMPChunkInfo}. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_WARNING_EVENT_CHUNK_DRMERROR                = 0x00000003,
        /** This event is emitted when playlist download is failed. {@link VOCommonPlayerDelegate} callback param obj will be {@link VOOSMPPlaylistData}. */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_WARNING_EVENT_PLAYLIST_DOWNLOADERROR        = 0x00000004,
        
        /** Max value definition */
        VO_OSMP_SRC_ADAPTIVE_STREAMING_WARNING_EVENT_MAX                           = 0xFFFFFFFF
    } VO_OSMP_SRC_ADAPTIVE_STREAMING_WARNING_EVENT;
    
    /**
     * Enumeration of available track types.
     * Used in {@link VO_OSMP_SRC_ADAPTIVE_STREAMING_INFO_EVENT_MEDIATYPE_CHANGE} callback.
     *
     */
    typedef enum {
        /** This event is emitted when only audio is available. */
        VO_OSMP_AVAILABLE_PUREAUDIO                   = 0x00000000,
        /** This event is emitted when only video is available. */
        VO_OSMP_AVAILABLE_PUREVIDEO                   = 0x00000001,
        /** This event is emitted when both audio and video are available.*/
        VO_OSMP_AVAILABLE_AUDIOVIDEO                  = 0x00000002,
        /** Max value definition    */
        VO_OSMP_AVAILABLE_MAX                         = 0xFFFFFFFF
    } VO_OSMP_AVAILABLE_TRACK_TYPE;
    
    /**
     * Enumeration of RTSP error
     */
    typedef enum
    {
        /** This event is emitted when connection is failed in RTSP.  */
        VO_OSMP_SRC_RTSP_ERROR_CONNECT_FAIL           = 0x00000001,
        /** This event is emitted when describe operation is failed in RTSP. */
        VO_OSMP_SRC_RTSP_ERROR_DESCRIBE_FAIL          = 0x00000002,
        /** This event is emitted when setup operation is failed in RTSP. */
        VO_OSMP_SRC_RTSP_ERROR_SETUP_FAIL             = 0x00000003,
        /** This event is emitted when play operation is failed in RTSP. */
        VO_OSMP_SRC_RTSP_ERROR_PLAY_FAIL              = 0x00000004,
        /** This event is emitted when pause operation is failed in RTSP. */
        VO_OSMP_SRC_RTSP_ERROR_PAUSE_FAIL             = 0x00000005,
        /** This event is emitted when option operation is failed in RTSP. */
        VO_OSMP_SRC_RTSP_ERROR_OPTION_FAIL            = 0x00000006,
        /** This event is emitted when socket error occurs in RTP channel of RTSP. */
        VO_OSMP_SRC_RTSP_ERROR_SOCKET_ERROR           = 0x00000007,
        /** This event is to notify HTTP error. */
        VO_OSMP_SRC_RTSP_ERROR_HTTP_ERROR             = 0x00000008,
        /** This event is to notify URL has been expired. */
        VO_OSMP_SRC_RTSP_ERROR_URL_EXPIRED            = 0x00000009,
        /** Max value definition    */
        VO_OSMP_SRC_RTSP_ERROR_MAX                    = 0xFFFFFFFF,
    } VO_OSMP_SRC_RTSP_ERROR;
 #ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


/**
 * Protocol for event process. Implement this delegation when it is required to receive event from the player.
 */
@protocol VOCommonPlayerDelegate <NSObject>

/**
 * Protocol to process events. Implement this listener to receive and manage events.
 *
 * @param nID    [out] Event type. Refer to {@link VO_OSMP_CB_EVENT_ID}.
 * @param param1 [out] First  parameter, specific to the event if needed.
 * @param param2 [out] Second parameter, specific to the event if needed.
 * @param obj    [out] Third  parameter, specific to the event if needed.
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) onVOEvent:(VO_OSMP_CB_EVENT_ID)nID param1:(int)param1 param2:(int)param2 pObj:(void *)pObj;

/**
 * Protocol to process synchronous events.  Implement this  listener to receive and manage synchronous events.
 *
 * @param id     [out] Event type. Refer to (@link VO_OSMP_CB_EVENT_ID}.
 * @param param1 [out] First  parameter, specific to the event if needed.
 * @param param2 [out] Second parameter, specific to the event if needed.
 * @param obj    [out] Third  parameter, specific to the event if needed.
 *
 * @return {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful.
 *
 * @deprecated This method will be removed in the future.
 */
@optional
- (VO_OSMP_RETURN_CODE) onVOSyncEvent:(VO_OSMP_CB_SYNC_EVENT_ID)nID param1:(int)param1 param2:(int)param2 pObj:(void *)pObj;

@end

