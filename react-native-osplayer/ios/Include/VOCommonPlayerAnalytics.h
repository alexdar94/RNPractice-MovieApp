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

#ifndef SKIP_IN_MAIN_DOCUMENTATION
#import "VOOSMPAnalyticsFilter.h"
#import "VOOSMPAnalyticsInfo.h"
#endif

#import "VOOSMPAnalyticsExportListener.h"

#import "VOOSMPType.h"

@protocol VOCommonPlayerAnalytics <NSObject>

/**
 * Enable analytics display.
 *
 * <p><ul>
 * <li> To enable analytics display, this API must be called before calling the {@link VOCommonPlayerControl#open} method.
 * <li> This API should be called ASAP after calling the {VOCommonPlayerConfiguration#setPreAgreedLicense}.
 * <li> Call this API during playback to change the time of refreshing analytics display.
 * </ul></p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   time   [in] Time <seconds> to refresh the display, set to 0 to disable analytics display. Valid time should be greater than or equal to 3.
 *
 * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) enableAnalyticsDisplay:(int)time;


/**
 * Set display type of analytics.
 * <p>
 * This API must be called after calling {@link VOCommonPlayerAnalytics#enableAnalyticsDisplay}.
 * </p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   type   [in] The display type. The default is VO_OSMP_DISPLAY_NULL.
 *
 * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setAnalyticsDisplayType:(VO_OSMP_DISPLAY_TYPE)type;


/**
 * Enable Analytics Foundation.
 *
 * <p><ul>
 * <li> To enable Analytics Foundation, this API must be called before calling the {@link VOCommonPlayerControl#open} method.
 * <li> This API should be called ASAP after calling the {VOCommonPlayerConfiguration#setPreAgreedLicense}.
 * </ul></p>
 *
 * @param   enable [in] Enable/Disable; true to enable, false to disable(default).
 *
 * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) enableAnalyticsFoundation:(bool)enable;


/**
 * Set customer specified user ID for Analytics Foundation.
 * <p>
 * To set customer specified user ID, This API must be called after calling {@link VOCommonPlayerAnalytics#enableAnalyticsFoundation}.
 * </p>
 *
 * @param   cuid [in] The customer specified user ID
 *
 * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setAnalyticsFoundationCUID:(NSString *)cuid;

/**
 * Enable or disable Analytics Agent.
 *
 * <p><ul>
 * <li> To enable, this API must be called before calling the {@link VOCommonPlayerControl#open} method
 * <li> This API should be called ASAP after calling {@link VOCommonPlayerConfiguration#setPreAgreedLicense}
 * </ul></p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   enable [in] Enable/Disable; true to enable, false to disable(default).
 *
 * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
 *
 */
- (VO_OSMP_RETURN_CODE) enableAnalyticsAgent:(bool)enable;

/**
 * Set App ID for Analytics Agent.
 * <p>
 * To set the app ID, this API must be called after calling {@link VOCommonPlayerAnalytics#enableAnalyticsAgent}
 * </p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * Additional API assumption: Only after enableAnalyticsAgent is called.
 * </p>
 *
 * @param appID [in] App ID
 * @return {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setAnalyticsAgentAppID:(NSString *) appID;


/**
 * Set customer specified user ID for Analytics Agent.
 * <p>
 * To set the customer specified user ID, this API must be called after calling {@link VOCommonPlayerAnalytics#enableAnalyticsAgent}
 * </p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * Additional API assumption: Only after enableAnalyticsAgent is called.
 * </p>
 *
 * @param cuid [in] The customer specified user ID
 * @return {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setAnalyticsAgentCUID:(NSString *) cuid;



/**
 * Enable or disable location information in Analytics Foundation.
 * <p>
 * To enable the location information, this API must be called after calling {@link VOCommonPlayerAnalytics#enableAnalyticsFoundation}.
 * </p>
 *
 * @param enable [in] Enable/disable; true to enable, false to disable (default).
 *
 * @return {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableAnalyticsFoundationLocation:(bool)enable;

/**
 * Enable or disable logging of analytics events for realtime export.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param enable [in] Enable/disable; true to enable, false to disable (default).
 * @return {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableAnalyticsExport:(bool)enable;

/**
 * Add analytics info.
 * <p>
 * To set the customer specified user ID, this API must be called after calling {@link VOCommonPlayerAnalytics#enableAnalyticsExport}
 * </p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param key   [in] key of info.
 * @param value [in] value of info.
 *
 * @return {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) addAnalyticsInfo:(NSString*)key value:(NSString *) value;

/**
 * Get and flush logged analytics events.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED, VO_OSMP_STATE_SUSPENDED.
 * Additional API assumption: Only after enableAnalyticsExport is called.
 * </p>
 *
 * @return String representing analytics events as JSON array
 */
- (NSString *) getAnalyticsExportPacket;

/**
 * Set listener that will be notified when new analytics event is available.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * Additional API assumption: Only after enableAnalyticsExport is called.
 * </p>
 *
 * @param listener [in] Analytics event listener
 * @return {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setAnalyticsExportListener:(id <VOOSMPAnalyticsExportListener>) listener;

/**
 * Get video video frames per second (FPS) from analytics display.
 * <p> Need enable analytic display with {@link enableAnalyticsDisplay} </p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * Additional API assumption: Only after enableAnalyticsDisplay is called.
 * </p>
 *
 * @return  FPS; -1 if unsuccessful.
 */
- (float) getAnalyticsFPS;


/**
 * Set cache time and start analytics data collection.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param   cacheTime  [in] Time <seconds> to cache the analytics data.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableAnalytics:(int)cacheTime;


/**
 * Get current analytics data.
 *
 * <p>
 * valid states: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   filter   [in] Filters, specified as an {@link VOOSMPAnalyticsFilter} object,
 *                       to be applied to cached analytic data before being returned.
 *
 * @param   data     [out] Filtered analytics data. Refer to {@link VOOSMPAnalyticsInfo}.
 *
 * @return  A {@link VOOSMPAnalyticsInfo} object if successful; nil if unsuccessful
 */
- (id<VOOSMPAnalyticsInfo>) getAnalytics:(VOOSMPAnalyticsFilter *)filter;


/**
 * Get video decoding bitrate(bps) for each of the last 10 seconds.
 *
 * <p>
 * valid states: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return an array(NSNumber) of size 10 in which elements are the video
 *         decoding bitrates of each of the last 10 seconds.
 *         The bitrate information is arranged in the way that
 *         the smaller the array index is, the closer
 *         the bitrate is to the current time. That is,
 *         element 0 is the bitrate of the closest second
 *         before the current time; element 1 is the bitrate
 *         that is 1 second before element 0; element 2 is the
 *         bitrate that is 1 second before element 1, and so on.
 */
- (NSArray *) getVideoDecodingBitrate;


/**
 * Get audio decoding bitrate(bps) for each of the last 10 seconds.
 *
 * <p>
 * valid states: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return an array(NSNumber) of size 10 in which elements are the audio
 *         decoding bitrates of each of the last 10 seconds.
 *         The bitrate information is arranged in the way that
 *         the smaller the array index is, the closer
 *         the bitrate is to the current time. That is,
 *         element 0 is the bitrate of the closest second
 *         before the current time; element 1 is the bitrate
 *         that is 1 second before element 0; element 2 is the
 *         bitrate that is 1 second before element 1, and so on.
 */
- (NSArray *) getAudioDecodingBitrate;

@end
