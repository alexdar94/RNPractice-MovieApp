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
#import "VOOSMPStreamingDownloaderType.h"
#import "VOCommonPlayerAssetSelection.h"
#import "VOOSMPVerificationInfo.h"

@protocol VOOSMPStreamingDownloader <VOCommonPlayerAssetSelection>

/**
 * Initialize a player instance.
 * <pre>This function must be called first to start a session.</pre>
 *
 * @param   delegate  [in] Refer to {@link VOOSMPStreamingDownloaderDelegate}
 * @param   initParam [in] Refer to {@link VOOSMPStreamingDownloaderInitParam}
 * @return  player object if successful; nil if unsuccessful
 */
- (id) init:(id<VOOSMPStreamingDownloaderDelegate>)delegate initParam:(VOOSMPStreamingDownloaderInitParam*)initParam;

/**
 * Open a media source.
 *
 * @param   url             [in] Source file description (for example, an URL or a file descriptor, etc.)
 * @param   flag            [in] Flag for opening a media source
 * @param   localDir        [in] Directory in which content files are saved
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) open:(NSString *)url flag:(unsigned int)flag localDir:(NSString *)localDir;

/**
 * Open a media source.
 *
 * @param   url             [in] Source file description (for example, an URL or a file descriptor, etc.)
 * @param   flag            [in] Flag for opening a media source
 * @param   localDir        [in] Directory in which content files are saved
 * @param   openParam       [in] Refer to {@link VOOSMPStreamingDownloaderOpenParam}
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) open:(NSString *)url flag:(unsigned int)flag localDir:(NSString *)localDir openParam:(VOOSMPStreamingDownloaderOpenParam *)openParam;


/**
 * Close a media source.
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) close;


/**
 * Start downloading the content.
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) start;


/**
 * Stop downloading the content.
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) stop;


/**
 * Pause the content download.
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) pause;


/**
 * Resume the content download.
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) resume;


/**
 * Set the information to start DRM verification.
 *
 * @param   info   [in] Verification information. 
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setDRMVerificationInfo:(VOOSMPVerificationInfo *)info;


/**
 * Set unique identifier of the device.
 *
 * @param   string [in] Unique identifier string
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 *
 * @deprecated This method will be removed in future.
 */
- (VO_OSMP_RETURN_CODE) setDRMUniqueIdentifier:(NSString *)string;


/**
 * Set DRM Library name and API name
 *
 * @param libName    [in] DRM library name
 * @param libApiName [in] API name for exporting DRM library
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful
 *
 * <p>To set DRM library name and API name, this API must be called before calling the {@link VOCommonPlayerControl#open:flag:sourceType:openParam:} method</p>
 */
- (VO_OSMP_RETURN_CODE) setDRMLibrary:(NSString *)libName libApiName:(NSString *)libApiName;


/**
 * Get duration of stream downloaded so far, and total duration of stream.
 *
 * @return {@link VOOSMPStreamingDownloaderProgressInfo} object if successful; nil if unsuccessful
 */
- (id<VOOSMPStreamingDownloaderProgressInfo>) getDuration;


/**
 * Check if the downloaded DRM key of current link is expired.
 * <p>
 * To get the status of downloaded DRM key, this API must be called after calling the {@link VOCommonPlayerControl#open:flag:sourceType:openParam:} method.
 * </p>
 *
 * @return DRM key expired status, refer to {@link VO_OSMP_DRM_KEY_EXPIRED_STATUS}.
 */
- (VO_OSMP_DRM_KEY_EXPIRED_STATUS) getDRMKeyExpiredStatus;


/**
 * Delete content that has been downloaded.
 *
 * @param URL [in] source file description (for example, a URL or a file descriptor)
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) deleteContent:(NSString*)URL;

/**
 * Get unique identifier of the device.
 * <p>
 * To get the UID, this method should be called after calling {@link VOOSMPStreamingDownloader#setDRMLibrary}.
 * Note that UID is only changed if the SDK is reinstalled.
 * The application upgrade will not lead to the change of UID.
 * </p>
 *
 * @return  unique identifier is successful; nil if unsuccessful
 */
- (NSString *) getDRMUniqueIdentifier;

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
 * Get DRM license info
 *
 * @return the string contains return code and DRM license info, as {"Return value":"value","Remaining Time":"360000"}.
 * <p> And "value" will be the following </p>
 * <p><ul>
 * <li>"Success", get license info successfully
 * <li>"Stored License not found", can't find local stored license
 * <li>"Clear Content", it's clear Content
 * <li>"DRM Lib not loaded", can't load drm lib
 * <li>"Unsupported", the stream type or the feature unsupported
 * <li>"Error", some error happen
 * </p></ul>
 * <p> This API should be called after player receive {@link VO_OSMP_CB_STREAMING_DOWNLOADER_EVENT_ID#VO_OSMP_CB_STREAMING_DOWNLOADER_OPEN_COMPLETE}. </p>
 */
- (NSString *)getDRMLicenseInfo;

/**
 * Renew DRM license
 *
 * <p>
 * This is an async API. It will always return immediately. Once the renew license is done, it will send the event:
 * <li>If it is successful, it will callback the event {@link VO_OSMP_CB_STREAMING_DOWNLOADER_EVENT_ID#VO_OSMP_CB_STREAMING_DOWNLOADER_DRM_KEY_READY}
 * <li>If it is faild, it will callback the event {@link VO_OSMP_CB_STREAMING_DOWNLOADER_EVENT_ID#VO_OSMP_CB_STREAMING_DOWNLOADER_DRM_FAIL} and the param1 will be the internal error code
 * </p>
 */
- (VO_OSMP_RETURN_CODE)renewDRMLicense;

/**
 * set HTTP header.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param headerName  [in] Set-Cookie: to set cookie;  User-Agent: to set user agent; Del-Cookies: to clear all cookies.
 *
 * @param headerValue [in] Corresponding value of 'headerName'.
 *
 * <p>If headerName is 'Set-Cookie', headerValue should be a string, for example:<ul>
 * <li> For http link:  cookie name=Test; domain=visualon.com; path=/; expires=2147483647;
 * <li> For https link: cookie name=Test; domain=visualon.com; path=/; expires=2147483647; secure=false;
 * </ul></p>
 *
 * <p>If headerName is 'User-Agent', headerValue should be a string that describes the user agent. </p>
 * <p>The default user agent strings for Android, iOS, and Windows are: <ul>
 * <li> Android: VisualOn OSMP+ Player(Android)
 * <li> iOS:     VisualOn OSMP+ Player(iOS)
 * <li> Windows: VisualOn OSMP+ Player(Windows)
 * </ul></p>
 *
 * <p>If headerName is 'Del-Cookies', headerValue should be "".</p>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setHTTPHeader:(NSString *)headerName headerValue:(NSString *)headerValue;

@end
