/************************************************************************
 VisualOn Proprietary
 Copyright (c) 2014, VisualOn Incorporated. All Rights Reserved
 
 VisualOn, Inc., 4675 Stevens Creek Blvd, Santa Clara, CA 95051, USA
 
 All data and information contained in or disclosed by this document are
 confidential and proprietary information of VisualOn, and all rights
 therein are expressly reserved. By accepting this material, the
 recipient agrees that this material and the information contained
 therein are held in confidence and in trust. The material may only be
 used and/or disclosed as authorized in a license agreement controlling
 such use and disclosure.
 ************************************************************************/

#ifndef voAnalyticsAPI_h
#define voAnalyticsAPI_h

#import <Foundation/Foundation.h>

//-----------------------------------------------------------------//
//                          DECLARRATIONS                          //
//-----------------------------------------------------------------//
typedef NS_ENUM (NSUInteger, VAIStringType) {
    VAIModel,
    VAIOs,
    VAIOsVersion, // os, os version
    VAIAppVersion,
    VAICUID,
    VAIVideoURL,
    VAIVideoName
};

typedef NS_ENUM (NSUInteger, VAIPlayerError) {
    VAIPlayerHttpError,
    VAIPlayerDrmError,
    VAIPlayerCodecError,
    VAIPlayerOtherError
};

typedef NS_ENUM (NSUInteger, VAINumberType) {
    VAIVideoLength,
    VAIPlayingBitrate,
    VAIBytesDownloaded,
    VAIDownloadTime
};

typedef NS_ENUM (NSUInteger, VAIPlayerState) {
    Idle, Opening, Playing, Buffering, Seeking, Paused, Stopped, Suspended
};


//-----------------------------------------------------------------//
//                      interface of VAI                           //
//-----------------------------------------------------------------//
@interface VAI : NSObject
+ (VAI*) sharedInstance;
- (void) configure:(NSString*) url withUUID:(NSString*)uuid key:(NSString*)cid;
- (void) setString:(VAIStringType)type value:(NSString*)value;
- (void) setNumber:(VAINumberType)type value:(double)number;
- (void) setPlayerState:(VAIPlayerState)state;
- (void) addPlayerError:(VAIPlayerError)type error:(NSString*)msg;
- (void) setCustomMetric:(int)index value:(double)nubmer;
- (void) setCustomDimention:(int)index value:(NSString*)value;
@end

//-----------------------------------------------------------------//
//                      callback function                          //
//-----------------------------------------------------------------//
@protocol VAIPollResponder <NSObject>
- (void) onPolling;
@end
// done sep os osv
// configure url
// stringtype, numbertype, pollresponder

#endif /* voAnalyticsAPI_h */
