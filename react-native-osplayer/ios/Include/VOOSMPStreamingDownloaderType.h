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
#import "VOOSMPDrmLicenseManager.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    
    /**
     * Enumeration of callback event IDs.
     * VO_OSMP_CB_STREAMING_DOWNLOADER_EVENT_ID
     * <p>
     * This event is sent from sub-thread. Do not update UI or call other OSMP+ APIs in callback, except for API listed in comments.
     * </p>
     */
    typedef enum {
        /** Open complete, param2 is manifest content byte size, param obj is manifest content. */
        VO_OSMP_CB_STREAMING_DOWNLOADER_OPEN_COMPLETE            =  0X10000001,
        /** This event is emitted when download of manifest file is successful. pObj is the url of the local manifest (NSString *) */
        VO_OSMP_CB_STREAMING_DOWNLOADER_MANIFEST_OK              =  0X10000002,
        /** This event is emitted when download of all contents is completed. */
        VO_OSMP_CB_STREAMING_DOWNLOADER_END                      =  0X10000004,
        /** This event is emitted when program information has been changed.*/
        VO_OSMP_CB_STREAMING_DOWNLOADER_PROGRAM_INFO_CHANGE      =  0X10000005,
        /** This event is emitted when manifest file is updated. pObj is {@link VOOSMPStreamingDownloaderProgressInfo} */
        VO_OSMP_CB_STREAMING_DOWNLOADER_MANIFEST_UPDATE          =  0X10000006,
        /**
         * @deprecated This enum will be removed in the future.
         * Set authentication information {@link VOCommonPlayerConfiguration#setDRMVerificationInfo} before open.
         **/
        VO_OSMP_CB_STREAMING_DOWNLOADER_SYNC_AUTHENTICATION_DRM_SERVER_INFO  = 0X10000007,
        /** download starts */
        VO_OSMP_CB_STREAMING_DOWNLOADER_START_DOWNLOADING        =  0X10000008,

        /** This event is emitted when download of manifest file is failed. */
        VO_OSMP_CB_STREAMING_DOWNLOADER_DOWNLOAD_MANIFEST_FAIL   =  0X90000001,
        /** This event is emitted when write operation to manifest file is failed. pObj is the fail reason (NSString *) */
        VO_OSMP_CB_STREAMING_DOWNLOADER_WRITE_MANIFEST_FAIL      =  0X90000002,
        /** This event is emitted when download of chunk file is failed. */
        VO_OSMP_CB_STREAMING_DOWNLOADER_DOWNLOAD_CHUNK_FAIL      =  0X90000003,
        /** This event is emitted when write operation to chunk file is failed. pObj is the fail reason (NSString *) */
        VO_OSMP_CB_STREAMING_DOWNLOADER_WRITE_CHUNK_FAIL         =  0X90000004,
        /** This event is emitted when disk is full. */
        VO_OSMP_CB_STREAMING_DOWNLOADER_DISK_FULL                =  0X90000005,
        /** This event is emitted when manifest generation is failed.*/
        VO_OSMP_CB_STREAMING_DOWNLOADER_GENERATE_MANIFEST_FAIL   =  0X90000006,
        /** This event is emitted when live stream is not supported. */
        VO_OSMP_CB_STREAMING_DOWNLOADER_LIVE_STREAM_NOT_SUPPORT  =  0X90000007,
        /** This event is emitted when stream on local disk is not supported.*/
        VO_OSMP_CB_STREAMING_DOWNLOADER_LOCAL_STREAM_NOT_SUPPORT =  0X90000008,
        
        /** This event is emitted when playlist initialization is failed. */
        VO_OSMP_CB_STREAMING_DOWNLOADER_LOCAL_PLAYLIST_INIT_FAIL =  0X90000009,
        /** This event is emitted when license check is failed. */
        VO_OSMP_CB_STREAMING_DOWNLOADER_LISENCE_CHECK_FAIL       =  0X9000000A,
        /** This event is emitted when IO initialization is failed. */
        VO_OSMP_CB_STREAMING_DOWNLOADER_INIT_IO_FAIL             =  0X9000000B,
        /** This event is emitted when the status switch is failed. */
        VO_OSMP_CB_STREAMING_DOWNLOADER_SWITCH_STATUS_FAIL       =  0X9000000C,
        /** This event is emitted when the status check is failed. */
        VO_OSMP_CB_STREAMING_DOWNLOADER_CHECK_STATUS_FAIL        =  0X9000000D,
        /** This event is emitted when Download Manager fails to create the folder. pObj is the fail reason (NSString *) */
        VO_OSMP_CB_STREAMING_DOWNLOADER_CREATE_FOLDER_FAIL       =  0X90000010,
        /** notify drm engine err */
        VO_OSMP_CB_STREAMING_DOWNLOADER_DRM_FAIL                 =  0XCBE00003,
        /** notify drm key ready */
        VO_OSMP_CB_STREAMING_DOWNLOADER_DRM_KEY_READY            =  0XCB000017,
        
        /** Max value definition */
        VO_OSMP_CB_STREAMING_DOWNLOADER_EVENT_ID_MAX             =  0xFFFFFFFF
    } VO_OSMP_CB_STREAMING_DOWNLOADER_EVENT_ID;
    
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


EXPORT_API
@interface VOOSMPStreamingDownloaderInitParam : NSObject
{
    NSString*                    _libraryPath;
}

/**
 * Set the path of working directory.
 */
@property (readwrite, retain, getter=getLibraryPath) NSString* libraryPath;

/**
 * Initialize filter with values.
 *
 * @return	object if successful; nil if unsuccessful
 */
- (id) init;

@end

@interface VOOSMPStreamingDownloaderOpenParam : NSObject
{
    id<VOOSMPDrmLicenseManager>  _drmLicenseManager;
}

/**
 * Set the Drm license manager
 */

@property (readwrite, retain, getter=getDrmLicenseManager) id<VOOSMPDrmLicenseManager> drmLicenseManager;

/**
 * Set download directory
 */

@property (readwrite, retain) NSString *downloadDir;

@end

@protocol VOOSMPStreamingDownloaderProgressInfo <NSObject>

/**
 * Get duration (millisecond) of stream that has been downloaded.
 */
@property (readwrite, assign, getter=getDownloadedStreamDuration) int downloadedStreamDuration;


/**
 * Get total duration (millisecond) of stream.
 */
@property (readwrite, assign, getter=getTotalStreamDuration) int totalStreamDuration;


/**
 * Initialize progress information with values.
 *
 * @param downloadedStreamDuration   [in] Duration of stream that is downloaded. The units are ms.
 * @param totalStreamDuration   [in] Total duration of stream. The units are ms.
 *
 * @return	object if successful; nil if unsuccessful
 */
- (id) init:(int)downloadedStreamDuration totalStreamDuration:(int)totalStreamDuration;

@end

/**
 * Protocol for event process. Implement this delegation to receive event from Download Manager.
 */
@protocol VOOSMPStreamingDownloaderDelegate <NSObject>

/**
 * Protocol for processing events. Implement the listener to receive and manage events.
 *
 * @param nID    [out] Event type. Refer to {@link VO_OSMP_CB_STREAMING_DOWNLOADER_EVENT_ID}.
 * @param param1 [out] First  parameter, specific to the event if needed.
 * @param param2 [out] Second parameter, specific to the event if needed.
 * @param obj    [out] Third  parameter, specific to the event if needed.
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) onVOStreamingDownloaderEvent:(VO_OSMP_CB_STREAMING_DOWNLOADER_EVENT_ID)nID param1:(int)param1 param2:(int)param2 pObj:(void *)pObj;


@end





