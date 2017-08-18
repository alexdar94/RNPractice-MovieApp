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

@protocol VOOSMPAssetIndex <NSObject>

/**
 * Get the index of the current video track. Valid value is from 0 to {@link VOCommonPlayerAssetSelection#getVideoCount} - 1.
 *
 * {@link VO_OSMP_ASSET_AUTO_SELECTED} indicates auto-select.
 */
@property (readonly, assign, getter=getVideoIndex) int videoIndex;

/**
 * Get the index of the current audio track. Valid value is from 0 to {@link VOCommonPlayerAssetSelection#getAudioCount} - 1.
 */
@property (readonly, assign, getter=getAudioIndex) int audioIndex;

/**
 * Get the index of the current subtitle track. Valid value is from 0 to {@link VOCommonPlayerAssetSelection#getSubtitleCount} - 1.
 */
@property (readonly, assign, getter=getSubtitleIndex) int subtitleIndex;

@end


@protocol VOOSMPAssetProperty <NSObject>

/**
 * Get the number of asset (track) properties.
 *
 * @return    number of properties
 */
- (int) getPropertyCount;

/**
 * Get the property key value by index.
 *
 * @param     index [in] The index of property. Valid value is from 0 to {@link VOOSMPAssetProperty#getPropertyCount} - 1.
 *
 * @return    key value (NSString). Supported property keys are specific to the asset type (video, audio, or subtitle) and include:
 *                   @"description" (audio, subtitle, and video)
 *                   @"language" (audio and subtitle)
 *                   @"codec" (audio and video)
 *                   @"bitrate" (audio and video)
 *                   @"width" (video only)
 *                   @"height" (video only)
 *                   @"type" (subtitle for HLS only)
 
 */
- (NSString*) getKey:(int)index;

/**
 * Get the property value by index.
 *
 * @param     index [in] The index of property. Valid value is from 0 to {@link VOOSMPAssetProperty#getPropertyCount} - 1.
 *
 * @return    property value (NSString)
 */
- (id) getValue:(int)index;

@end

/**
 * This index indicates that a track is selected automatically.
 */
const static int VO_OSMP_ASSET_AUTO_SELECTED = -1;

/**
 * This index indicates that no track has been selected for a specific type.
 */
const static int VO_OSMP_ASSET_NOT_SELECTED  = -2;


@protocol VOCommonPlayerAssetSelection <NSObject>

/**
 * Get the number of available video tracks.
 * <p>
 * A video track is referred to as a combination of
 * bitrate and camera angle (combination of internal stream
 * and video track).
 * </p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return    number of available video tracks; -1 if unsuccessful
 */
- (int) getVideoCount;


/**
 * Get the number of available audio tracks.
 * <p>
 * An audio track is referred to as a combination of
 * language and codec type. An audio track may have
 * multiple audio bitrates. The final playback bitrate
 * relies on the selected video track.
 * </p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return    number of available audio tracks; -1 if unsuccessful.
 */
- (int) getAudioCount;


/**
 * Get the number of available subtitle tracks.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return    number of available subtitle tracks; -1 if unsuccessful
 */
- (int) getSubtitleCount;


/**
 * Select video track using its index. selectVideo(-1) enables automatic bitrate adaptation.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param     index [in] The index of video track. This value is valid from 0 to {@link VOCommonPlayerAssetSelection#getVideoCount} - 1.
 *            Use {@link VO_OSMP_ASSET_AUTO_SELECTED} to indicate auto-select.
 *            The availability of video tracks relies on the current selection of
 *            uncommitted audio and subtitle tracks.
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) selectVideo:(int)index;


/**
 * Select audio track using its index.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param     index [in] Index of audio track. This value is valid from 0.
 *            The availability of audio tracks relies on the current selection of
 *            uncommitted video and subtitle tracks.
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) selectAudio:(int)index;


/**
 * Select subtitle track using its index.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param     index [in] Index of subtitle track. This value is valid from 0.
 *            The availability of subtitle selections relies on the current
 *            selection of uncommitted video and audio selections.
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) selectSubtitle:(int)index;


/**
 * Check if specified video track is available.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param     index [in] Index of video track. This value is valid from 0 to {@link VOCommonPlayerAssetSelection#getVideoCount} - 1.
 *            The availability of video track relies on the current selection of
 *            uncommitted audio and subtitle tracks.
 *
 * @return    true if specified video stream is available; false if not
 */
- (bool) isVideoAvailable:(int)index;


/**
 * Check if specified audio track is available.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param     index [in] Index of audio track. This value is valid from 0 to {@link VOCommonPlayerAssetSelection#getAudioCount} - 1.
 *            The availability of audio tracks relies on the current selection of
 *            uncommitted video and subtitle tracks.
 *
 * @return    true if specified video stream is available; false if not
 */
- (bool) isAudioAvailable:(int)index;


/**
 * Check if specified subtitle track is available.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param     index [in] Index of subtitle track. This value is valid from 0 to {@link VOCommonPlayerAssetSelection#getSubtitleCount} - 1.
 *            The availability of subtitle tracks relies on the current selection of
 *            uncommitted video and audio tracks.
 *
 * @return    true if specified video stream is available; false if not
 */
- (bool) isSubtitleAvailable:(int)index;


/**
 * Commit all current asset selections. If any asset type is not selected, the player uses the asset type of track that is being played.
 * This operation removes all current selections after being committed.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * Additional API assumption: Async call. For audo and subtitle, it will call setPosition() to flush out current selection. For video, it keeps playing current streams without flush, until find switch point of new stream. 		
 * </p>
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) commitSelection;


/**
 * Clear all current uncommitted selections.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) clearSelection;


/**
 * Get the properties of specified video track.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param    index  [in] Index of video track property. This value is valid from 0 to {@link VOOSMPAssetProperty#getPropertyCount} - 1.
 *
 * @return   a {@link VOOSMPAssetProperty} object if successful or nil if failed.
 *           Returned object holds a list of key-value pairs where both key and value are
 *           of NSString* type. <br>
 *           Supported property keys are:
 *                   @"description"
 *                   @"codec"
 *                   @"bitrate"
 *                   @"width"
 *                   @"height"
 */
- (id<VOOSMPAssetProperty>) getVideoProperty:(int)index;


/**
 * Get the properties of specified audio track.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param    index  [in] Index of audio track property. This value is valid from 0 to {@link VOOSMPAssetProperty#getPropertyCount} - 1.
 *
 * @return   a {@link VOOSMPAssetProperty} object if successful or nil if failed.
 *           Returned object holds a list of key-value pairs where both key and value are
 *           of NSString* type.
 *           Supported property keys are:
 *                   @"description"
 *                   @"language"
 *                   @"codec"
 *                   @"bitrate"
 *                   @"channelcount"
 */
- (id<VOOSMPAssetProperty>) getAudioProperty:(int)index;


/**
 * Get the properties of specified subtitle track.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param     index [in] Index of subtitle track property. This value is valid from 0.
 *
 * @return    a {@link VOOSMPAssetProperty} object if successful or nil if failed.
 *            Returned object holds a list of key-value pairs where both key and value are of NSString* type. <br>
 *            Supported property keys are:
 *                   @"description"
 *                   @"language"
 *                   @"type"
 *
 * <p> The value of "type" is one of the following: Undefined, CC608, CC708, TTML, SSTTML, WEBVTT, DVB, SRT, SMI, LRC, SMPTETT, or ENVIVO.  </p>
 */
- (id<VOOSMPAssetProperty>) getSubtitleProperty:(int)index;


/**
 * Get the actual indices of video/audio/subtitle tracks that are being played.
 * If a track is being played, its index is returned through VOOSMPAssetIndex.
 * If no track of a specific type (mostly likely subtitle) is being played, the corresponding index in VOOSMPAssetIndex is set to {@link VO_OSMP_ASSET_NOT_SELECTED}.
 *
 * <p>
 * valid states: VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return   a {@link VOOSMPAssetIndex} object if successful or nil if failed. Returns
 *           the actual indices of video/audio/subtitle tracks that are being played.
 */
- (id<VOOSMPAssetIndex>) getPlayingAsset;


/**
 * Get the current track selection of video/audio/subtitle.
 * If a track is selected automatically, the corresponding index in VOOSMPAssetIndex is set to {@link VO_OSMP_ASSET_AUTO_SELECTED}.
 * If a track is being manually selected, its index is returned through VOOSMPAssetIndex.
 * If no track of a specific type is being selected automatically/manually, the corresponding index in VOOSMPAssetIndex is set to {@link VO_OSMP_ASSET_NOT_SELECTED}.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return   a {@link VOOSMPAssetIndex} object if successful or nil if failed. Returned
 *           object holds the current index values of the selected video, audio, and subtitle tracks.
 */
- (id<VOOSMPAssetIndex>) getCurrentSelection;


/**
 * Set the default audio language.
 *
 * @param     type [in] Language type following definition of ISO 639-2.
 * For example, "fre" represents French.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 *
 * @deprecated This method is replaced by {@link VOCommonPlayerAssetSelection#setPreferredAudioLanguage:} and will be removed in the future.
 *
 */
- (VO_OSMP_RETURN_CODE) setDefaultAudioLanguage:(NSString*)type;


/**
 * Set the default subtitle language.
 *
 * @param     type [in] Language type following definition of ISO 639-2.
 * For example, "fre" represents French.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 *
 * @deprecated This method is replaced by {@link VOCommonPlayerAssetSelection#setPreferredSubtitleLanguage:} and will be removed in the future.
 *
 */
- (VO_OSMP_RETURN_CODE) setDefaultSubtitleLanguage:(NSString*)type;


/**
 * Set the preferred audio language. Inactive for {@link VOOSMPStreamingDownloader}
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param     languageList [in] a list of preferred audio language using ISO 639-1 and ISO 639-2 code. For example, "fr" and "fra" represent French. Based on the order of languages specified in the list, the player selects the first available language in the stream. If the list is empty, the player selects it based on the streaming specification.
 *
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setPreferredAudioLanguage:(NSArray*)languageList;


/**
 * Set the preferred subtitle language. Inactive for {@link VOOSMPStreamingDownloader}
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED.
 * </p>
 *
 * @param     languageList [in] a list of preferred subtitle language using ISO 639-2 code. For example, "fre" represents French.  Based on the order of languages specified in the list, the player selects the first available language in the stream. If the list is empty, the player selects it based on the streaming specification.
 *
 * @return    {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setPreferredSubtitleLanguage:(NSArray*)languageList;

@optional
/**
 * Check if thumbnail is available.
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return    true if thumbnail is available; false if not.
 */
- (bool) isThumbnailAvailable;

/**
 * Captures one or more thumbnail images asynchronously from the current movie.
 *
 * <p>
 * This method processes each thumbnail request separately and asynchronously.
 * <ol>
 * <li>When the results for a single image arrive, the player posts a VO_OSMP_CB_THUMBNAILS_REQUEST_UPDATE event. </li>
 * <li>When the request finishes, the player posts a VO_OSMP_CB_THUMBNAILS_REQUEST_FINISH event. </li>
 * <li>SDK drops old requests which hasn’t started processing in case of new request. </li>
 * </ol>
 * </p>
 *
 * <p>
 * valid states: VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param     startPosition [in] start position.
 *
 * @param     endPosition [in] end position.
 *
 * @param     preference  [in] {@link VO_OSMP_THUMBNAILS_PREFERENCE}
 *
 * @param     minInterval  [in] minimum interval of post thumbnail images, set as -1 to use default interval
 *
 * @return    {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) requestThumbnails:(int)startPosition endPosition:(int) endPosition preference:(VO_OSMP_THUMBNAILS_PREFERENCE)preference minInterval:(int)minInterval;

@end


