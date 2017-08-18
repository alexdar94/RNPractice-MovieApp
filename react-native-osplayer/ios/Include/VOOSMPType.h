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

#ifndef __VO_OSMP_TYPE_H__
#define __VO_OSMP_TYPE_H__

#ifdef _IOS
#define EXPORT_API __attribute__((visibility("default")))
#else
#define EXPORT_API
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    
    /**
     * Enumeration of return codes.
     */
    typedef enum {
        /** No error */
        VO_OSMP_ERR_NONE                              = 0X00000000,
        /** Reserved. Do not use. */
        VO_OSMP_ERR_EOS                               = 0X00000001,
        /** Reserved. Do not use. */
        VO_OSMP_ERR_RETRY                             = 0X00000002,
        /** Reserved. Do not use. */
        VO_OSMP_ERR_FORMAT_CHANGE                     = 0X00000003,
        /** Reserved. Do not use. */
        VO_OSMP_ERR_VIDEO                             = 0X80000004,
        /** Reserved. Do not use. */
        VO_OSMP_ERR_AUDIO                             = 0X80000005,
        /** Out of memory occurs. */
        VO_OSMP_ERR_OUTMEMORY                         = 0X80000006,
        /** The pointer is invalid.  */
        VO_OSMP_ERR_POINTER                           = 0X80000007,
        /** Parameter id is invalid.  */
        VO_OSMP_ERR_PARAMID                           = 0X80000008,
        /** The status is incorrect. */
        VO_OSMP_ERR_STATUS                            = 0X80000009,
        /** The function is not implemented. */
        VO_OSMP_ERR_IMPLEMENT                         = 0X8000000A,
        /** Reserved. Do not use. */
        VO_OSMP_ERR_SMALLSIZE                         = 0X8000000B,
        /** Reserved. Do not use. */
        VO_OSMP_ERR_OUT_OF_TIME                       = 0X8000000C,
        /** Reserved. Do not use. */
        VO_OSMP_ERR_WAIT_TIME                         = 0X8000000D,
        /** Undefined behaviours occurs. */
        VO_OSMP_ERR_UNKNOWN                           = 0X8000000E,
        /** JNI cannot be used on iOS platform. */
        VO_OSMP_ERR_JNI                               = 0X8000000F,
        /** License check is failed. */
        VO_OSMP_ERR_LICENSE_FAIL                      = 0X80000011,
        /** Error occurs when authorizing HTTPS Certification. */
        VO_OSMP_ERR_HTTPS_CA_FAIL                     = 0X80000012,
        /** Argument is invalid. */
        VO_OSMP_ERR_ARGS                              = 0X80000013,
        /** Multiple player instances mode is not supported. */
        VO_OSMP_ERR_MULTIPLE_INSTANCES_NOT_SUPPORTED  = 0X80000014,
        /** Failed to obtain the content URL to open */
        VO_OSMP_ERR_CONTENT_URL_FAILED                = 0X80000015,
        /** Object is not initialized. */
        VO_OSMP_ERR_UNINITIALIZE                      = 0X80000101,
        
        
        /** Open source operation is failed. */
        VO_OSMP_SRC_ERR_OPEN_SRC_FAIL                 = 0X81000001,
        /** Content is encrypted, and further operations are required. */
        VO_OSMP_SRC_ERR_CONTENT_ENCRYPT               = 0X81000002,
        /** Play mode is not supported. */
        VO_OSMP_SRC_ERR_PLAYMODE_UNSUPPORT            = 0X81000003,
        /** The source file data has errors. */
        VO_OSMP_SRC_ERR_ERROR_DATA                    = 0X81000004,
        /** Seek operation is failed or is not supported. */
        VO_OSMP_SRC_ERR_SEEK_FAIL                     = 0X81000005,
        /** Source file format is not supported. */
        VO_OSMP_SRC_ERR_FORMAT_UNSUPPORT              = 0X81000006,
        /** Reserved. Do not use.*/
        VO_OSMP_SRC_ERR_TRACK_NOTFOUND                = 0X81000007,
        /** Reserved. Do not use. */
        VO_OSMP_SRC_ERR_NO_DOWNLOAD_OP                = 0X81000008,
        /** Reserved. Do not use. */
        VO_OSMP_SRC_ERR_NO_LIB_OP                     = 0X81000009,
        /** Reserved. Do not use. */
        VO_OSMP_SRC_ERR_OUTPUT_NOTFOUND               = 0X8100000A,
        /** Reserved. Do not use. */
        VO_OSMP_SRC_ERR_CHUNK_SKIP                    = 0X8100000B,
        /** DIVX is not supported by the source. */
        VO_OSMP_SRC_ERR_DIVXUNSUPPORTED               = 0X8100000D,
        /** The link causes failed, maybe download(checked by ErrorHandler) or other situation. */
        VO_OSMP_SRC_ERR_LINK_FAIL                     = 0X8100000E,
        /** the chunk get drm error */
        VO_OSMP_SRC_ERR_DRM_FAIL                      = 0X8100000F,
        /** Failed to download playlist */ 
        VO_OSMP_SRC_ERR_PLAYLIST_DOWNLOAD_FAIL        = 0X81000010,
        /** Cannot recognize the type of playlist (HLS, SS, DASH) */
        VO_OSMP_SRC_ERR_INVALID_PLAYLIST_TYPE         = 0X81000011,
        /** Manifest has some errors */
        VO_OSMP_SRC_ERR_MANIFEST_PARSE_FAIL           = 0X81000012,
        /** The source object is not initialized. */
        VO_OSMP_SRC_ERR_SRC_UNINITIALIZE              = 0X80001001,
        
        /** Max value definition */
        VO_OSMP_RETURN_CODE_MAX                       = 0xFFFFFFFF,
    } VO_OSMP_RETURN_CODE;
    
    
    /**
     * Enumeration for render type
     * VO_OSMP_RENDER_TYPE
     */
    typedef enum {
        /** Native window render,for Android platform only */
        VO_OSMP_RENDER_TYPE_NATIVE_WINDOW             = 0x00000001,
        /** Native Surface render,for Android platform only */
        VO_OSMP_RENDER_TYPE_NATIVE_SURFACE            = 0x00000004,
        /** Use DirectDraw render,for Windows platform only */
        VO_OSMP_RENDER_TYPE_DDRAW                     = 0x00000007,
        /** Use GDI render,for Windows platform only */
        VO_OSMP_RENDER_TYPE_GDI                       = 0x00000008,
        /** Use Direct 3D render,for Windows platform only */
        VO_OSMP_RENDER_TYPE_D3D                       = 0x0000000A,
        
        /**Max value definition */
        VO_OSMP_RENDER_TYPE_MAX                       = 0xFFFFFFFF,
    } VO_OSMP_RENDER_TYPE;
    
    
    /**
     * Enumeration of open source flags. Used in {@link VOCommonPlayerControl#open} function.
     * VO_OSMP_SRC_FLAG
     *
     */
    typedef enum {
        /**
         * @deprecated This enum will be removed in 2017 Jun.
         * Please use VO_OSMP_FLAG_SRC_OPEN_ASYNC to replace VO_OSMP_FLAG_SRC_OPEN_SYNC.
         */
        VO_OSMP_FLAG_SRC_OPEN_SYNC                    = 0X00000010,
        
        /** 
         * Open source in asynchronous mode. Used in {@link VOCommonPlayerControl#open} function.
         *  The open function is returned immediately after the call.
         *  Getting the {@link VO_OSMP_SRC_CB_OPEN_FINISHED} event indicates the open operation is completed. 
         */
        VO_OSMP_FLAG_SRC_OPEN_ASYNC                   = 0X00000020,
        
        /**
         * Open source with function pointer of push buffer. Used in {@link VOCommonPlayerControl#openSource} function.
         * Source type is VOOSMPSetPushBufferPrototype.
         */
        VO_OSMP_FLAG_SRC_PUSH_BUFFER_FUNCTION         = 0X00000040,
        
        /** Max value definition */
        VO_OSMP_FLAG_SRC_MAX                          = 0xFFFFFFFF,
    } VO_OSMP_SRC_FLAG;
    
    
    /**
     * Enumeration of the status of the player.
     * VO_OSMP_STATUS
     */
    typedef enum {
        /** Download is currently stalled.*/
        VO_OSMP_DOWNLOAD_STALL                        = 0x00000000,
        /** Download is currently in progress.*/
        VO_OSMP_DOWNLOAD_PROGRESS                     = 0x00000001,
        /** Download is currently suspended.*/
        VO_OSMP_DOWNLOAD_SUSPEND                      = 0x00000002,
        /** Max value definition */
        VO_OSMP_DOWNLOAD_MAX                          = 0XFFFFFFFF,
    } VO_OSMP_DOWNLOAD_STATUS;
    
    
    /**
     * Enumeration used to define the possible source stream type.
     * VO_OSMP_SOURCE_STREAMTYPE
     */
    typedef enum {
        VO_OSMP_SS_NONE                               = 0X00000000,
        /** The source stream is audio.  */
        VO_OSMP_SS_AUDIO                              = 0X00000001,
        /** The source stream is video.  */
        VO_OSMP_SS_VIDEO                              = 0X00000002,
        /** Subtitle track & closed caption*/
        VO_OSMP_SS_SUBTITLE                           = 0X00000009,
        /** Max value definition */
        VO_OSMP_SS_MAX                                = 0XFFFFFFFF,
    } VO_OSMP_SOURCE_STREAMTYPE;
    
    
    /**
     * Enumeration of the status of the player.
     * VO_OSMP_STATUS
     */
    typedef enum {
        /** Currently initializing */
        VO_OSMP_STATUS_INITIALIZING                   = 0X00000000,
        /** Currently loading      */
        VO_OSMP_STATUS_LOADING                        = 0X00000001,
        /** Currently running      */
        VO_OSMP_STATUS_PLAYING                        = 0X00000002,
        /** Currently paused       */
        VO_OSMP_STATUS_PAUSED                         = 0X00000003,
        /** Currently stopped      */
        VO_OSMP_STATUS_STOPPED                        = 0X00000004,
        /** Max value definition   */
        VO_OSMP_STATUS_MAX                            = 0xFFFFFFFF,
    } VO_OSMP_STATUS;
    
    
    /**
     * Enumeration of zoom modes.
     * VO_OSMP_ZOOM_MODE
     */
    typedef enum {
        /** Letter box mode    */
        VO_OSMP_ZOOM_LETTERBOX                        = 0X00000001,
        /** Pan scan mode      */
        VO_OSMP_ZOOM_PANSCAN                          = 0X00000002,
        /** Fit to window mode */
        VO_OSMP_ZOOM_FITWINDOW                        = 0X00000003,
        /** Original size mode */
        VO_OSMP_ZOOM_ORIGINAL                         = 0X00000004,
        /** Zoom in with the window mode */
        VO_OSMP_ZOOM_ZOOMIN                           = 0x00000005,
        /** Max value definition    */
        VO_OSMP_ZOOM_MAX                              = 0xFFFFFFFF,
    } VO_OSMP_ZOOM_MODE;
    
    
    /**
     * Enumeration of source formats.
     * VO_OSMP_SRC_SRC_FORMAT
     */
    typedef enum {
        /** Detect the source format automatically (default) */
        VO_OSMP_SRC_AUTO_DETECT                       = 0X00000000,
        /** Local MP4 file */
        VO_OSMP_SRC_FFLOCAL_MP4                       = 0X00000001,
        /** RTSP streaming */
        VO_OSMP_SRC_FFSTREAMING_RTSP                  = 0X08000100,
        /** Session description */
        VO_OSMP_SRC_FFSTREAMING_SDP                   = 0X08000200,
        /** HTTP Live streaming */
        VO_OSMP_SRC_FFSTREAMING_HLS                   = 0X08000400,
        /** Silverlight Smooth Streaming */
        VO_OSMP_SRC_FFSTREAMING_SSSTR                 = 0X08000800,
        /** DASH streaming */
        VO_OSMP_SRC_FFSTREAMING_DASH                  = 0X08001000,
        /** PD streaming */
        VO_OSMP_SRC_FFSTREAMING_HTTPPD                = 0X08002000,
        /** Push PD streaming */
        VO_OSMP_SRC_FFSTREAMING_PUSHPD                = 0X08010000,
        /** Max value definition */
        VO_OSMP_SRC_FFMOVIE_MAX                       = 0xFFFFFFFF,
    } VO_OSMP_SRC_FORMAT;
    
    
    /**
     * Enumeration of aspect ratios.
     * VO_OSMP_ASPECT_RATIO
     */
    typedef enum {
        /** @deprecated Same as VO_OSMP_RATIO_ORIGINAL and will be removed in the future */
        VO_OSMP_RATIO_00                              = 0X00000000,
        /** Ratio of Width and Height is 1 : 1    */
        VO_OSMP_RATIO_11                              = 0X00000001,
        /** Ratio of Width and Height is 4 : 3    */
        VO_OSMP_RATIO_43                              = 0X00000002,
        /** Ratio of Width and Height is 16 : 9   */
        VO_OSMP_RATIO_169                             = 0X00000003,
        /** Ratio of Width and Height is 2 : 1    */
        VO_OSMP_RATIO_21                              = 0X00000004,
        /** Ratio of Width and Height is 2.33 : 1 */
        VO_OSMP_RATIO_2331                            = 0X00000005,
        
        /** Use aspect ratio value from video frame.
         *  If frame does not contain this value, behavior is same as VO_OSMP_RATIO_ORIGINAL
         */
        VO_OSMP_RATIO_AUTO                            = 0X00000006,
        /** Use video original ratio of yuv, width: height */
        VO_OSMP_RATIO_ORIGINAL                        = 0X00000000,
        
        /** Max value definition */
        VO_OSMP_RATIO_MAX                             = 0xFFFFFFFF,
    } VO_OSMP_ASPECT_RATIO;
    
    
    /**
     * Enumeration of player engine types.
     * VO_OSMP_PLAYER_ENGINE
     */
    typedef enum {        
        /** VisualOn media framework engine */
        VO_OSMP_VOME2_PLAYER                          = 0X00000000,
        
        /** OpenMAX AL engine. This type is for Android platform only */
        VO_OSMP_OMXAL_PLAYER                          = 0X00000001,
        
        /** AVPlayer engine.
         * <p><ul>
         * <li> This type is for iOS platform only.
         * <li> It supports H.264 video decoder and AAC audio decoder.
         * <li> Once using this enum, {@link VO_OSMP_DECODER_TYPE} of {@link VOOSMPOpenParam} will be ignored.
         * </ul></p>
         */
        VO_OSMP_AV_PLAYER                             = 0X00000002,
        
        /** Auto switch player type.
         * <p><ul>
         * <li> This type is for iOS platform only.
         * <li> Once using this enum, {@link VO_OSMP_DECODER_TYPE} of {@link VOOSMPOpenParam} will be ignored.
         * </ul></p>
         */
        VO_OSMP_AUTO_PLAYER                           = 0X00001000,
        
        /** Max value definition */
        VO_OSMP_PLAYER_ENGINE_MAX                     = 0xFFFFFFFF,
    } VO_OSMP_PLAYER_ENGINE;
    
    
    /**
     * Enumeration of program types.
     * VO_OSMP_SRC_PROGRAM_TYPE
     */
    typedef enum {
        /** The source is a live streaming. */
        VO_OSMP_SRC_PROGRAM_TYPE_LIVE                 = 0X00000000,
        /** The source is a VOD. */
        VO_OSMP_SRC_PROGRAM_TYPE_VOD                  = 0X00000001,
        /** The source is unknown.*/
        VO_OSMP_SRC_PROGRAM_TYPE_UNKNOWN              = 0X000000FF,
        /** Max value definition */
        VO_OSMP_SRC_PROGRAM_TYPE_MAX                  = 0xFFFFFFFF,
    } VO_OSMP_SRC_PROGRAM_TYPE;
    
    /**
     * Enumeration of thumbnails preference.
     * VO_OSMP_THUMBNAILS_PREFERENCE
     */
    typedef enum {
        /** Request thumbnails from left to right*/
        VO_OSMP_THUMBNAILS_LEFT_TO_RIGHT              = 0X00000000
    } VO_OSMP_THUMBNAILS_PREFERENCE;    

    /**
     * Enumeration used to define RTSP connection type.
     * VO_OSMP_RTSP_CONNECTION_TYPE
     */
    typedef enum
    {
        /** Set connection type to automatic. UDP will be attempted before TCP */
        VO_OSMP_RTSP_CONNECTION_AUTOMATIC             = 0X00000000,
        /** Set connection type to TCP */
        VO_OSMP_RTSP_CONNECTION_TCP                   = 0X00000001,
        /** Set connection type to UDP (disable TCP) */
        VO_OSMP_RTSP_CONNECTION_UDP                   = 0X00000002,
        /** Max value definition */
        VO_OSMP_RTSP_CONNECTION_MAX                   = 0xFFFFFFFF,
    }VO_OSMP_RTSP_CONNECTION_TYPE;
    
    
    /**
     * Enumeration of the verification flag.
     * VO_OSMP_SRC_VERIFICATION_FLAG
     */
    typedef enum {
        /** The verification data is the requested string. */
        VO_OSMP_SRC_VERIFICATION_REQUEST_STRING       = 0X00000000,
        /** The verification data is username:password */
        VO_OSMP_SRC_VERIFICATION_USERNAME_PASSWORD    = 0X00000001,
        /** The verification data is customer data */
        VO_OSMP_SRC_VERIFICATION_CUSTOMER_DATA        = 0X00000002,
        /** Max value definition */
        VO_OSMP_SRC_VERIFICATION_MAX                  = 0xFFFFFFFF,
    } VO_OSMP_SRC_VERIFICATION_FLAG;
    
    /**
     * Enumeration of decoder type.
     * VO_OSMP_DECODER_TYPE
     */
    typedef enum
    {
        /** Invalid decoder type */
        VO_OSMP_DEC_NONE                              = 0X00000000,
        
        /** Software video decoder, For Android, iOS and PNACL */
        VO_OSMP_DEC_VIDEO_SW                          = 0X00000001,
        /** IOMX video decoder, For Android */
        VO_OSMP_DEC_VIDEO_IOMX                        = 0X00000002,
        /** MediaCodec video decoder, For Android */
        VO_OSMP_DEC_VIDEO_MEDIACODEC                  = 0X00000004,
        /** OSMP+ automatically selects hardware type. For Android, iOS and PNACL */
        VO_OSMP_DEC_VIDEO_HARDWARE_AUTO_SELECTED      = 0X00000100,

        /** Software audio decoder, For Android*/
        VO_OSMP_DEC_AUDIO_SW                          = 0X00100000,
        /** MediaCodec audio decoder, For Android*/
        VO_OSMP_DEC_AUDIO_MEDIACODEC                  = 0X00200000,
        
        /**Max value definition */
        VO_OSMP_DECODER_TYPE_MAX                      = 0xFFFFFFFF,
    } VO_OSMP_DECODER_TYPE;
    
    /**
     * Enumeration of the module type.
     * VO_OSMP_MODULE_TYPE
     */
    typedef enum {
        /** The whole OSMP+ SDK */
        VO_OSMP_MODULE_TYPE_SDK                       = 0x00000000,
        /** The version of DRM vendor A */
        VO_OSMP_MODULE_TYPE_DRM_VENDOR_A              = 0x00000001,
        /** The version of post process video module */
        VO_OSMP_MODULE_TYPE_SEI_POST_PROCESS_VIDEO    = 0x00000002,
        /** Max value definition */
        VO_OSMP_MODULE_TYPE_MAX                       = 0xFFFFFFFF,
    } VO_OSMP_MODULE_TYPE;
    
    /**
     * Enumeration of SEI info
     * VO_OSMP_SEI_INFO_FLAG
     */
    typedef enum {
        /** No need to process any SEI info. */
        VO_OSMP_FLAG_SEI_NONE                       = 0x00000000,
        
        /** Need process PIC Timing info; obj param refer to {@link VOOSMPSEIPicTiming}*/
        VO_OSMP_FLAG_SEI_PIC_TIMING                 = 0x00000001,
        
        /** Need process User data unregistered info; obj param refer to {@link VOOSMPSEIUserDataUnregistered}*/
        VO_OSMP_SEI_INFO_USER_DATA_UNREGISTERED     = 0x00000002,
        
        /** Max value definition */
        VO_OSMP_FLAG_SEI_MAX  = 0xFFFFFFFF
        
    } VO_OSMP_SEI_INFO_FLAG;
    
    
    /**
     * Enumeration for output control type
     */
    typedef enum
    {
        /** Unknown type */
        VO_OSMP_OUTPUT_CONTROL_TYPE_UNKNOWN              = 0x00000001,
        /** HDCP */
        VO_OSMP_OUTPUT_CONTROL_TYPE_HDCP                 = 0x00000002,
        /** Anti mirroring */
        VO_OSMP_OUTPUT_CONTROL_TYPE_ANTI_MIRRORING       = 0x00000004,
        /** Digital CIT */
        VO_OSMP_OUTPUT_CONTROL_TYPE_CIT_DIGITAL          = 0x00000008,
        /** Analog CIT */
        VO_OSMP_OUTPUT_CONTROL_TYPE_CIT_ANALOG           = 0x00000010,
        /** DOT */
        VOO_SMP_OUTPUT_CONTROL_TYPE_DOT                  = 0x00000020,
        /** Dwight cavendish */
        VO_OSMP_OUTPUT_CONTROL_TYPE_DWIGHT_CAVENDISH     = 0x00000040,
        /** ACP */
        VO_OSMP_OUTPUT_CONTROL_TYPE_ACP                  = 0x00000080,
        /** CGMS A */
        VO_OSMP_OUTPUT_CONTROL_TYPE_CGMS_A               = 0x00000100,
        /** HDMI */
        VO_OSMP_OUTPUT_CONTROL_TYPE_HDMI                 = 0x00000200,
        /** HDMI and HDCP */
        VO_OSMP_OUTPUT_CONTROL_TYPE_ALL_DISPLAY          = 0x00000400,
        
        /** Max value definition */
        VO_OSMP_OUTPUT_CONTROL_TYPE_MAX = 0xFFFFFFFF

    }VO_OSMP_OUTPUT_CONTROL_TYPE;
    
    /**
     * Enumeration of the audio codec type.
     * VO_OSMP_AUDIO_CODEC_TYPE
     */
    typedef enum {
        /** Unknown audio codec */
        VO_OSMP_AUDIO_CODEC_UNKNOWN          = 0x00000000,
        /** DTS */
        VO_OSMP_AUDIO_CODEC_DTS              = 0x00000016,
        /** Dolby */
        VO_OSMP_AUDIO_CODEC_DOLBY            = 0x00000017,
        
        /** Max value definition */
        VO_OSMP_AUDIO_CODEC_MAX              = 0xFFFFFFFF,
    }VO_OSMP_AUDIO_CODEC_TYPE;
    
    /**
     * Enum for analytic display type
     */
    typedef enum {
        /** Disable analytics display */
        VO_OSMP_DISPLAY_NULL     = 0x00000000,
        /** Display player KPIs info */
        VO_OSMP_DISPLAY_PLAYER   = 0x00000001,
        /** Display source KPIs info */
        VO_OSMP_DISPLAY_SOURCE   = 0x00000002,
        /** Display render KPIs info */
        VO_OSMP_DISPLAY_RENDER   = 0x00000003,
    } VO_OSMP_DISPLAY_TYPE;
    
    typedef struct {
        short top;
        short left;
        short bottom;
        short right;
    }VO_OSMP_RECT;
    
    /**
    * Enumeration for audio effect type
    */
    typedef enum {
        /** speaker */
        VO_OSMP_AUDIO_EFFECT_ENDPOINT_SPEAKER   = 0x00000001,
        /** headphone */
        VO_OSMP_AUDIO_EFFECT_ENDPOINT_HEADPHONE = 0x00000002,
        /** bluetooth */
        VO_OSMP_AUDIO_EFFECT_ENDPOINT_BLUETOOTH = 0x00000003,
        /** none */
        VO_OSMP_AUDIO_EFFECT_ENDPOINT_OFF       = 0x00000004,
    } VO_OSMP_AUDIO_EFFECT_ENDPOINT_TYPE;
    
    
    /**
     * Enumeration of DRM key expired status.
     */
    typedef enum {
        /** The key is not expired, however, it's allowed to continue with download/playback.*/
        VO_OSMP_DRM_KEY_VALID                   = 0x00000000,
        /** The Key is expired. The app needs user confirmation to continue with download/playback.*/
        VO_OSMP_DRM_KEY_EXPIRED_YES             = 0x00000001,
        /** The key value is not prepared and retry is needed. The app needs user confirmation to continue with download/playback.*/
        VO_OSMP_DRM_KEY_EXPIRED_NOT_PREPARE     = 0x00000002,
        /** Error occurs during key checking. The app needs user confirmation to continue with download/playback. */
        VO_OSMP_DRM_KEY_EXPIRED_ERROR           = 0x00000003,
        /** Key is not found. The app needs user confirmation to continue with download.
         * <p><ul>
         * <li> First download.
         * <li> Key expired and be deleted auto.
         * </ul></p>
         */
        VO_OSMP_DRM_KEY_NOT_FOUND               = 0x00000004,
        /** Clear content, however, it's allowed to continue with download/playback. */
        VO_OSMP_DRM_KEY_CLEAR_CONTENT           = 0x00000005,
        /** This feature is now supported, however, it's allowed to continue with download/playback. */
        VO_OSMP_DRM_KEY_UNSUPPORTED             = 0x00000006,
        /** DRM haven't been loaded, however, it's allowed to continue with download/playback. */
        VO_OSMP_DRM_KEY_LIB_NOT_LOADED          = 0x00000007, 
        /** Max value definition */
        VO_OSMP_DRM_KEY_EXPIRED_MAX             = 0xFFFFFFFF,
    } VO_OSMP_DRM_KEY_EXPIRED_STATUS;
    
    /**
     * Enumeration of horizontal position.
     */
    typedef enum {
        /** default */
        VO_OSMP_HORIZONTAL_DEFAULT              = 0x00000000,
        /** left */
        VO_OSMP_LEFT                            = 0x00000001,
        /** center */
        VO_OSMP_CENTER                          = 0x00000002,
        /** right */
        VO_OSMP_RIGHT                           = 0x00000003,
        
        /** Max value definition */
        VO_OSMP_HORIZONTAL_MAX                  = 0xFFFFFFFF,
    } VO_OSMP_HORIZONTAL;
    
    
    /**
     * Enumeration of vertical position.
     */
    typedef enum {
        /** default */
        VO_OSMP_VERTICAL_DEFAULT                = 0x00000000,
        /** top */
        VO_OSMP_TOP                             = 0x00000001,
        /** middle */
        VO_OSMP_MIDDLE                          = 0x00000002,
        /** bottom */
        VO_OSMP_BOTTOM                          = 0x00000003,
        
        /** Max value definition */
        VO_OSMP_VERTICAL_MAX                    = 0xFFFFFFFF,
    } VO_OSMP_VERTICAL;
    
    /**
     * Enumeration of HDCP policy
     */
    typedef enum{
        /** Do not check HDCP policy. */
        VO_OSMP_HDCP_NO_CHECK                   = 0x00000001,
        /** Downgrade resolution if HDCP is not present. */
        VO_OSMP_HDCP_NON_COMPLIANT_DOWNRES      = 0x00000002,
        /** Block mirroring if HDCP is not present. */
        VO_OSMP_HDCP_NON_COMPLIANT_BLOCK        = 0x00000003,
        
        /** Max value definition */
        VO_OSMP_HDCP_MAX                        = 0xFFFFFFFF,
    }VO_OSMP_HDCP_POLICY;
    
    /**
     * Enumeration of playback preference.
     */
    typedef enum {
        /** Keep last frame when switching to next link.*/
        VO_OSMP_PREF_STOP_KEEP_LAST_FRAME               = 0x00000001,
        /** Do not keep last frame when switching to next link.*/
        VO_OSMP_PREF_NO_STOP_KEEP_LAST_FRAME            = 0x00000002,
        /** Seek to new position precisely. */
        VO_OSMP_PREF_SEEK_PRECISE                       = 0x00000003,
        /** Do not seek to the requested position precisely for better playback performance. This function is only available for streaming V2 that is a beta feature undergoing testing. Contact VisualOn application engineers for details.*/
        VO_OSMP_PREF_NO_SEEK_PRECISE                    = 0x00000004,
        /** Change to the selected audio track a period of time after committing. */
        VO_OSMP_PREF_NO_SELECT_AUDIO_SWITCH_IMMEDIATELY = 0x00000005,
        /** Change to the selected audio track immediately after committing. Default. */
        VO_OSMP_PREF_SELECT_AUDIO_SWITCH_IMMEDIATELY    = 0x00000006,
        /** Load the video with better resolution as soon as possible after performing seek operation. */
        VO_OSMP_PREF_BA_START_DEFAULT = 0x00000007,
        /** Load the video as soon as possible after performing seek operation. */
        VO_OSMP_PREF_BA_START_FAST = 0x00000008,
        /** Decoding multiple frames at the same time helps reduce the required time for starting playback. */
        VO_OSMP_PREF_DECODE_1ST_FRAME_NORMAL = 0x00000009,
        /** Decoding the first frame in a moment helps reduce the required time for displaying the first frame. */
        VO_OSMP_PREF_DECODE_1ST_FRAME_ASAP = 0x0000000A,
        
        /** Don't stay awake when playback, default. */
        VO_OSMP_PREF_PLAYBACK_NO_STAY_AWAKE = 0x0000000B,
        /** Stay awake when playback. To enable stay awake, this API must be called before calling the {@link VOCommonPlayerControl#start} method*/
        VO_OSMP_PREF_PLAYBACK_STAY_AWAKE    = 0x0000000C,
        
        /** Disable low resolution enhancement of SEI post process video. Default. */
        VO_OSMP_PREF_SEI_POST_PROCESS_LOW_RES_ENHANCEMENT_OFF = 0x0000000D,
        /** Enable low resolution enhancement of SEI post process video. */
        VO_OSMP_PREF_SEI_POST_PROCESS_LOW_RES_ENHANCEMENT_ON  = 0x0000000E,
        
        /** Change to the selected subtitle track a period of time after committing. */
        VO_OSMP_PREF_NO_SELECT_SUBTITLE_SWITCH_IMMEDIATELY = 0x00000010,
        /** Change to the selected subtitle track immediately after commiting. Default. */
        VO_OSMP_PREF_SELECT_SUBTITLE_SWITCH_IMMEDIATELY    = 0x00000011,
        
        /** Default I-Frame playback mode with multiple speed, the playback setting is based on original timestamp and the speed. */
        VO_OSMP_PREF_IFRAME_ONLY_DEFAULT_FPS   = 0x00001001,
        /** For customized MPEG-DASH content with RIDX I-Frame information. DASH module drops some Iframes by the rule for only 4 frames are played per second. */
        VO_OSMP_PREF_IFRAME_ONLY_4_FPS         = 0x00001002,
        
        
        /** Set use IPV6 as prior for http connection. Default. */
        VO_OSMP_PREF_CONNECTION_IPV6_PRIOR     = 0x00010001,
        /** Set use IPV4 as prior for http connection. */
        VO_OSMP_PREF_CONNECTION_IPV4_PRIOR     = 0x00010002,
        /** Set automatic selection, try both and use the first one on success */
        VO_OSMP_PREF_CONNECTION_IPV4_IPV6_AUTO = 0x00010003,
        
        /** Set HTTP download failure callback without payload */
        VO_OSMP_PREF_HTTP_DOWNLOAD_FAILURE_CB_WITHOUT_PAYLOAD = 0x00010004,
        /** Set HTTP download failure callback with payload */
        VO_OSMP_PREF_HTTP_DOWNLOAD_FAILURE_CB_WITH_PAYLOAD    = 0x00010005,

        /** Set to display subtitle */
        VO_OSMP_PREF_SUBTITLE_TO_DISPLAY       = 0x00010006,
        /** Set to hide subtitle, but return the subtitle as a string instead through {@link VO_OSMP_CB_EVENT_ID#VO_OSMP_CB_SUBTITLE_INFO}. Only support WebVTT at present.*/
        VO_OSMP_PREF_SUBTITLE_TO_EVENT		   = 0x00010007,
        /** Set to disable BA limited by view size */
        VO_OSMP_PREF_NO_BA_LIMIT_BY_VIEW_SIZE  = 0x00010008,
        /** Set to enable BA limited by view size */
        VO_OSMP_PREF_BA_LIMIT_BY_VIEW_SIZE     = 0x00010009,
        
        /** Max value definition */
        VO_OSMP_PREF_MAX                                = 0xFFFFFFFF,
        
    } VO_OSMP_PREFERENCE;

    /**
    * Enumeration of player state
    */
    typedef enum{
        /** Currently uninitialized */
        VO_OSMP_STATE_UNINITIALIZED     = 0x00000000,
        /** Currently initialized */
        VO_OSMP_STATE_INITIALIZED       = 0x00000001,
        /** Currently opening */
        VO_OSMP_STATE_OPENING           = 0x00000002,
        /** Currently opened */
        VO_OSMP_STATE_OPENED            = 0x00000003,
        /** Currently running */
        VO_OSMP_STATE_PLAYING           = 0x00000004,
        /** Currently paused */
        VO_OSMP_STATE_PAUSED            = 0x00000005,
        /** Currently stopped.
         * <p><ul>
         * <li> Need call {@link close} at this state.
         * <li> Will be changed to VO_OSMP_STATE_INITIALIZED once {@link close} is called.
         * </ul></p>
         */
        VO_OSMP_STATE_STOPPED           = 0x00000006,
        /** Currently suspended */
        VO_OSMP_STATE_SUSPENDED         = 0x00000007,
        /** Currently destroyed */
        VO_OSMP_STATE_DESTROYED         = 0x00000008,
        /** Max value definition */
        VO_OSMP_STATE_MAX               = 0x00000009,
        
    }VO_OSMP_STATE;
    

     /**
    * Enumeration of streaming error type
    */
    typedef enum{
        /** no error */
        VO_OSMP_STREAMING_ERROR_NONE                    = 0x00000000,
        //http
        /** http IO has connection error */
        VO_OSMP_STREAMING_IO_CONNECTION_FAIL            = 0x00000001,
        /** Server response too large*/
        VO_OSMP_STREAMING_IO_RESPONSE_TOOLARGE          = 0x00000002,
        /** Timeout when getting the reponse */
        VO_OSMP_STREAMING_IO_GET_RESPONSE_TIMEOUT       = 0x00000003,
        /** Failure of reading data from the socket */
        VO_OSMP_STREAMING_IO_READ_DATA_ERROR            = 0x00000004,
        /** Out of memory */
        VO_OSMP_STREAMING_IO_OUT_OF_MEMORY              = 0x00000005,
        /** Redirection url error */
        VO_OSMP_STREAMING_IO_REDIRECT_BAD_URL           = 0x00000006,
        /** Redirection response without location field */
        VO_OSMP_STREAMING_IO_REDIRECT_URL_MISSING       = 0x00000007,
        /** DNS lookup failure */
        VO_OSMP_STREAMING_IO_DNS_ERROR                  = 0x00000008,
        /** http respone error,e.g. 4xx, 5xx... 
        * Use {@link getErrorCode} to get the HTTP error code
        */
        VO_OSMP_STREAMING_IO_HTTP_ERROR                 = 0x00000009,
        //drm
        /** It is a fatal error. The drm type set from JSON cannot be matched for playback, e.g. user hopes to use playready as decryption mode, but the content does not contain any playready drm information. The suggested operation is to stop drm operating. */
        VO_OSMP_STREAMING_DRM_NOT_SUPPORTED             = 0x00000030,
        /** It is a fatal error. VO has not provided license for selected drm type, e.g. user hopes to use playready as decryption mode, but VO has no license for playready decryption. The suggested operation is to stop drm operating. */
        VO_OSMP_STREAMING_DRM_NO_SDK_LICENSE            = 0x00000031,
        /** It is a fatal error. The drm handle is empty during any function call, e.g. no-key has been found for decryption. The suggested operation is to stop drm operating. */
        VO_OSMP_STREAMING_DRM_HANDLE_NULL_POINTER       = 0x00000032,
        /** It is a warning. The content has no license to output via external connection. It should notify user to disconnect external connection. The suggested operation is to retry or drop data. */
        VO_OSMP_STREAMING_DRM_VIDEO_OUTPUT_FORBIDDEN    = 0x00000033,
        /** It is a fatal error. Some errors occurred during drm initialization, e.g. device provision failure (e.g. rooted device), related module locading failure, etc. The suggested operation is to stop drm operating. */
        VO_OSMP_STREAMING_DRM_INIT_FAIL                 = 0x00000034,
        /** It is a fatal error. Some errors occurred during drm-key operation, e.g. register-key failure, acquire-rights failure, no drm-key rights, etc. The suggested operation is to stop drm operating. */
        VO_OSMP_STREAMING_DRM_KEY_FAIL                  = 0x00000035,
        /** It is a fatal error. Some errors occurred during content decryption, e.g. decyption failure. The suggested operation is to stop drm operating. */
        VO_OSMP_STREAMING_DRM_DECRYPT_FAIL              = 0x00000036,
        /** It is a fatal error. Some error occurred during drm un-initialization. e.g. drm engine un-initialization, unregister-key, etc. The suggested operation is to stop drm operating. */
        VO_OSMP_STREAMING_DRM_UNINIT_FAIL               = 0x00000037,

        /** un-defined error */
        VO_OSMP_STREAMING_ERROR_UNKNOWN                  = 0x00000060,
    }VO_OSMP_STREAMING_ERROR_TYPE;


    
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif // __VO_OSMP_TYPE_H__


