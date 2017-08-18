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

@protocol VOOSMPRTSPStatistics <NSObject>

/**
 * The cumulative number of RTP media packets that are received in this media track during this session.
 *
 * @return cumulative number of RTP media packets received in this media track during this session
 */
@property (readonly, assign, getter=getPacketReceived) int packetReceived;

/**
 * The cumulative number of RTP media packets that are previously received in this media track during this session.
 *
 * @return cumulative number of RTP media packets previously received in this media track during this session
 */
@property (readonly, assign, getter=getPacketDuplicated) int packetDuplicated;

/**
 * The cumulative number of RTP media packets that are lost for this media track type.
 *
 * @return cumulative number of RTP media packets lost for this media track type
 */
@property (readonly, assign, getter=getPacketLost) int packetLost;

/**
 * The cumulative number of RTP media packets that are sent to this media track during this session.
 *
 * @return cumulative number of RTP media packets sent in this media track during this session
 */
@property (readonly, assign, getter=getPacketSent) int packetSent;

/**
 * The average relative transit time between each two RTP packets of this media track type throughout the duration of the media session.
 *
 * @return average relative transit time between each two RTP packets of this media track type throughout the duration of the media session
 */
@property (readonly, assign, getter=getAverageJitter) int averageJitter;

/**
 * The average cumulative latency of all RTP media packets transmitted from the server to the client. Currently reserved only.
 *
 * @return average accumulating latency value
 */
@property (readonly, assign, getter=getAverageLatency) int averageLatency;

@end

