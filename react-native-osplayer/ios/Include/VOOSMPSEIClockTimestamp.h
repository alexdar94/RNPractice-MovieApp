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

/**
 * Protocol of Picture timing as defined in ISO/IEC 14496-10:2005 (E) Annex D 2.2.
 */
@protocol VOOSMPSEIClockTimestamp <NSObject>

/**
 * Get the clock_timestamp_flag information.
 *
 * @return clock_timestamp_flag
 */
@property (readonly, assign, getter=getClockTimestampFlag) int clockTimestampFlag;

/**
 * Get the ct_type information. 
 *
 * @return ct_type
 */
@property (readonly, assign, getter=getCtType) int ctType;

/**
 * Get the nuit_field_based_flag information. 
 *
 * @return nuit_field_based_flag
 */
@property (readonly, assign, getter=getNuitFieldBasedFlag) int nuitFieldBasedFlag;

/**
 * Get the counting_type information.
 *
 * @return counting_type
 */
@property (readonly, assign, getter=getCountingType) int countingType;

/**
 * Get the full_timestamp_flag information.
 *
 * @return full_timestamp_flag
 */
@property (readonly, assign, getter=getFullTimestampFlag) int fullTimestampFlag;

/**
 * Get the discontinuity_flag information.
 *
 * @return discontinuity_flag
 */
@property (readonly, assign, getter=getDiscontinuityFlag) int discontinuityFlag;

/**
 * Get the cnt_dropped_flag information.
 *
 * @return cnt_dropped_flag
 */
@property (readonly, assign, getter=getCountDroppedFlag) int countDroppedFlag;

/**
 * Get n_frames information.
 *
 * @return n_frames
 */
@property (readonly, assign, getter=getFrames) int frames;

/**
 * Get the seconds_value information.
 *
 * @return seconds_value
 */
@property (readonly, assign, getter=getSecondsValue) int secondsValue;

/**
 * Get the minutes_value information.
 *
 * @return minutes_value
 */
@property (readonly, assign, getter=getMinutesValue) int minutesValue;

/**
 * Get the hours_value information.
 *
 * @return hours_value
 */
@property (readonly, assign, getter=getHoursValue) int hoursValue;

/**
 * Get the seconds_flag information.
 *
 * @return seconds_flag
 */
@property (readonly, assign, getter=getSecondsFlag) int secondsFlag;

/**
 * Get the minutes_flag information.
 *
 * @return minutes_flag
 */
@property (readonly, assign, getter=getMinutesFlag) int minutesFlag;

/**
 * Get the hours_flag information.
 *
 * @return hours_flag
 */
@property (readonly, assign, getter=getHoursFlag) int hoursFlag;

/**
 * Get the time_offset information.
 *
 * @return time_offset
 */
@property (readonly, assign, getter=getTimeOffset) int timeOffset;


@end

