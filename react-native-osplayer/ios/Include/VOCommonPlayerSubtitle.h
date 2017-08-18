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

@protocol VOCommonPlayerSubtitle <NSObject>


/**
 * Set file/URL path for external subtitles (for example, smi, srt files, etc.).
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   filePath [in] Full path/URL (including “http://”) of the external subtitle file.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitlePath:(NSString *)filePath;


/**
 * Enable/disable subtitles display; Analytics display is disabled by default.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   value [in] Enable/disable; true to enable (show) subtitles, false to disable (hide) subtitles.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableSubtitle:(bool)value;


/**
 * Set subtitle font color.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   color [in] Font color (0x00RRGGBB) of subtitle text.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleFontColor:(int)color;


/**
 * Set he opacity rate of subtitle font color.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   alpha [in] Font color opacity rate. The valid range is 0 to 100, from transparent to opaque.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleFontOpacity:(int)alpha;


/**
 * Set subtitle font size scale.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   scale [in] Font size scale for subtitle text (percent). 50 is half of the default size, and 200 is twice of the default size.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleFontSizeScale:(int)scale;

/**
 * Set subtitle image size scale.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   scale [in] Image size scale for subtitle image (percent). 50 is half of the default size, and 200 is twice the default size.
 *
 * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleImageSizeScale:(int)scale;


/**
 * Set the background color of subtitle font.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   color [in] Subtitle font background color (0x00RRGGBB).
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleFontBackgroundColor:(int)color;


/**
 * Set the background color opacity rate of subtitle font.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   alpha [in] Subtitle font background color opacity rate. The valid range is 0 to 100, from transparent to opaque.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleFontBackgroundOpacity:(int)alpha;


/**
 * Set window background color.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   color [in] Subtitle window background color (0x00RRGGBB).
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleWindowBackgroundColor:(int)color;


/**
 * Set the opacity rate of window background color.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   alpha [in] Subtitle window background color opacity rate. The valid range is 0 to 100, from transparent to opaque.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleWindowBackgroundOpacity:(int)alpha;


/**
 * Enable/Disable subtitle font italics.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   enable [in] Enable/Disable; true to enable subtitle font italics.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleFontItalic:(bool)enable;


/**
 * Enable/Disable subtitle font bold.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   enable [in] Enable/Disable; true to enable subtitle font bold.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleFontBold:(bool)enable;


/**
 * Enable/Disable subtitle font underlined.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   enable [in] Enable/Disable; true to enable subtitle font underline.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleFontUnderline:(bool)enable;


/**
 * Set subtitle font name.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   name [in] Font name for subtitle text.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleFontName:(NSString *)name;


/**
 * Set subtitle font edge type.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   type [in] Edge type of subtitle font. Valid values are 0:NONE, 1:RAISED, 2:DEPRESSED, 3:UNIFORM, 4:LEFT_DROP_SHADOW, 5:RIGHT_DROP_SHADOW.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleFontEdgeType:(int)type;


/**
 * Set subtitle font edge color.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   color [in] Font edge color (0x00RRGGBB) of subtitle text.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleFontEdgeColor:(int)color;


/**
 * Set the opacity rate of subtitle font edge color.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param   alpha [in] Edge color opacity rate of subtitle font. The valid range is 0 to 100, from transparent to opaque.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) setSubtitleFontEdgeOpacity:(int)alpha;


/**
 * Set the subtitle bounding box, which overrides the subtitle settings from parser.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param topPercent    [in] Set the top position using percent based on the top display edge of video screen.
 * @param leftPercent   [in] Set the left position using percent based on the left display edge of video screen.
 * @param bottomPercent [in] Set the bottom position using percent based on the top display edge of video screen.
 * @param rightPercent  [in] Set the right position using percent based on the left display edge of video screen.
 * <p>
 *   The valid value is from 0 to 100. The parameter value will be ignored sometimes, such as:
 *   The topPercent is ignored if the gravity isn't top and subtitle exceeds the bounding box.
 * </p>
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) setSubtitleBoundingBox:(int)topPercent leftPercent:(int)leftPercent bottomPercent:(int)bottomPercent rightPercent:(int)rightPercent;


/**
 * Set the gravity of the bounding box.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param horizontal [in] horizontal position of the gravity Refer to (@link VO_OSMP_HORIZONTAL). 
 * @param vertical   [in] vertical position of the gravity. Refer to (@link VO_OSMP_VERTICAL).
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) setSubtitleGravity:(VO_OSMP_HORIZONTAL)horizontal vertical:(VO_OSMP_VERTICAL)vertical;

/**
 * Set character sets to be trimmed from the beginning or end of subtitle.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param trimChars    [in]  The character sets to be trimmed.
 * This argument is not a prefix or suffix of substring; Instead all combinations of its values are trimmed.
 * @return {@link VO_OSMP_ERR_NONE} if successful.
 */
- (VO_OSMP_RETURN_CODE) setSubtitleTrim:(NSString *) trimChars;


/**
 * Reset all parameters to their default values. Subtitles will be presented as specified in the subtitle stream.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) resetSubtitleParameter;


/**
 * Enable/Disable the automatic adjustment for subtitle position/font size. Automatic adjustment of subtitle is disabled by default.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param  value[in] Enable/Disable the automatic adjustment for subtitle position/font size. true (Enabled): Uses the font size and location set by VisualOn. false (Disabled): Uses the font size and location from source file.
 *
 * @return  {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) enableSubtitleAutoAdjustment:(bool)value;


/**
 * Preview subtitle by sending some sample text to be rendered.
 *
 * <p>
 * valid states: VO_OSMP_STATE_INITIALIZED, VO_OSMP_STATE_OPENING, VO_OSMP_STATE_OPENED, VO_OSMP_STATE_PLAYING, VO_OSMP_STATE_PAUSED.
 * </p>
 *
 * @param sampleText [in] text for previewing current subtitle settings
 * @param view [in] view to which the sample text is being rendered
 *
 * To preview the subtitle, this API must be called in main thread.
 *
 * @return {@link VO_OSMP_ERR_NONE} if successful
 */
- (VO_OSMP_RETURN_CODE) previewSubtitle:(NSString *)sampleText view:(id)view;

@end
