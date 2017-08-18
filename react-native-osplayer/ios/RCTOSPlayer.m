//
//  RCTOSPlayer.m
//  OSPlayerApp
//
//  Created by David Chen on 1/23/17.
//  Copyright © 2017 Facebook. All rights reserved.
//

#import "RCTOSPlayer.h"
#if __has_include(<React/RCTAssert.h>)
#import <React/RCTEventDispatcher.h>
#else
#import "RCTEventDispatcher.h"
#endif

static NSString *pDRMLibrary = @"voDRM_Verimatrix_AES128";
static NSString *pDRMApiName = @"voGetVerimatrixDRMAPI";

@implementation RCTOSPlayer
{
  RCTEventDispatcher *_eventDispatcher;
  RCTOSPlayerManager *_manager;
  
  float _volume;
  BOOL _muted;
  BOOL _paused;
  
  NSString *_DRMUniqueIdentifier;
  NSDictionary *_source;
  
  VOPlayer *_player;
  BOOL _playerSourceOpened;
  
  Float64 _progressUpdateInterval;
  NSTimer *_progressTimer;
}

- (instancetype)initWithEventDispatcher:(id)eventDispatcher Manager:(RCTOSPlayerManager *)manager
{
  if ((self = [super init])) {
    _eventDispatcher = eventDispatcher;
    _manager = manager;
    _volume = 1.0;
    _source = nil;
    _progressUpdateInterval = 0.250;
  }
  return self;
}

- (NSString*) DRMUniqueIdentifier
{
  
  return _DRMUniqueIdentifier;
}

- (void)setPlayerId:(NSNumber *)id
{
  _player = [_manager getPlayerWithId:id];
  
  [_player setView:(__bridge void *)(self)];
  
  [_player setOnEventDelegate:self];
  [_player setDRMLibrary:pDRMLibrary libApiName:pDRMApiName];
  
  NSString *licPath = [[NSBundle mainBundle] pathForResource:@"voVidDec.dat" ofType:nil];
  [_player setLicenseFilePath:licPath];
  //Manually set for now, but should be set via JS
  [_player setPreAgreedLicense:@"VISUALON-VERIMATRIX-VECTORWEBTV-1EB666E3E2764F518B54680BA64C40D4"];
  
  //Performance optimisations
  [_player setInitialBufferingTime:1000];
  [_player enableLowLatencyVideo:true];
  [_player setInitialBitrate:800000];
  
  //DRM Id
  _DRMUniqueIdentifier = [_player getDRMUniqueIdentifier];
  if (self.onPlayerInit) {
    //Return DRM ID
    self.onPlayerInit(@{
                        @"drmID": _DRMUniqueIdentifier,
                        @"target": self.reactTag
                        });
  }
  
  [self applySource];
  [self applyPlayback];
  [self applyModifiers];
}

- (void)setSrc:(NSDictionary *)source
{
  _source = source;
  [self applySource];
  
  __weak RCTOSPlayer *weakSelf = self;
  
  _progressTimer = [NSTimer scheduledTimerWithTimeInterval:_progressUpdateInterval target:weakSelf selector:@selector(sendProgressUpdate) userInfo:nil repeats:YES];
}

- (void)setPaused:(BOOL)paused
{
  _paused = paused;
  [self applyPlayback];
}

- (void)setMuted:(BOOL)muted
{
  _muted = muted;
  [self applyModifiers];
}

- (void)setVolume:(float)volume
{
  _volume = volume;
  [self applyModifiers];
}

- (void)setSeek:(float)seekTime
{
  long seekTimeInMilli = seekTime * 1000;
  [_player setPosition:seekTimeInMilli];
}

- (void)applySource {
  if (_source != nil) {
    NSString *drmString = [_source objectForKey:@"drm"];
    
    if (self.onVideoLoadStart) {
      //Start loading video
      self.onVideoLoadStart(@{@"target": self.reactTag});
    }
    
    if (drmString != nil) {
      VOOSMPVerificationInfo *infoDRM = [[VOOSMPVerificationInfo alloc] init:VO_OSMP_SRC_VERIFICATION_REQUEST_STRING verificationString:drmString];
      [_player setDRMVerificationInfo:infoDRM];
    }
    
    VO_OSMP_RETURN_CODE code = [_player open:[_source objectForKey:@"uri"] flag:VO_OSMP_FLAG_SRC_OPEN_ASYNC sourceType:VO_OSMP_SRC_AUTO_DETECT openParam:nil];
    if (code != VO_OSMP_ERR_NONE) {
      [self sendVideoErrorWithReturnCode:code];
    }
  }
}

- (void)applyModifiers {
  [_player setVolume:_volume];
  
  if (_muted) {
    [_player mute];
  } else {
    [_player unmute];
  }
}

- (void)applyPlayback {
  VO_OSMP_STATUS playerStatus = [_player getPlayerStatus];
  
  if (_paused && playerStatus == VO_OSMP_STATUS_PLAYING) {
    [_player pause];
  } else if (!_paused && playerStatus != VO_OSMP_STATUS_PLAYING) {
    VO_OSMP_RETURN_CODE code = [_player start];
    if (code != VO_OSMP_ERR_NONE) {
      [self sendVideoErrorWithReturnCode:code];
    }
  }
}

- (NSNumber *)getDuration {
  long duration = [_player getDuration] / 1000;
  return @(duration);
}

- (NSNumber *)getPosition {
  long position = [_player getPosition] / 1000;
  return @(position);
}


- (VO_OSMP_RETURN_CODE)onVOEvent:(VO_OSMP_CB_EVENT_ID)nID param1:(int)param1 param2:(int)param2 pObj:(void *)pObj
{
  
  switch (nID) {
    case VO_OSMP_CB_ERROR:
    case VO_OSMP_SRC_CB_CONNECTION_FAIL:
    case VO_OSMP_SRC_CB_DOWNLOAD_FAIL:
    case VO_OSMP_SRC_CB_DRM_FAIL:
    case VO_OSMP_SRC_CB_PLAYLIST_PARSE_ERR:
    case VO_OSMP_SRC_CB_CONNECTION_REJECTED:
    case VO_OSMP_SRC_CB_DRM_NOT_SECURE:
    case VO_OSMP_SRC_CB_DRM_AV_OUT_FAIL:
    case VO_OSMP_CB_LICENSE_FAIL:
      [self sendVideoErrorWithEventId:nID];
      break;
    case VO_OSMP_SRC_CB_OPEN_FINISHED:
      if (param1 != VO_OSMP_ERR_NONE) {
        [self sendVideoErrorWithReturnCode:nID];
        break;
      }
      [self applyPlayback];
      if (self.onVideoLoad) {
        self.onVideoLoad(@{
                           @"src": [_source objectForKey:@"uri"],
                           @"duration": [self getDuration],
                           @"target": self.reactTag
                           });
      }
      break;
      
    case VO_OSMP_CB_VIDEO_RENDER_START:
      if (self.onReadyForDisplay) {
        self.onReadyForDisplay(@{@"target": self.reactTag});
      }
      break;
      
    case VO_OSMP_CB_SEEK_COMPLETE:
      if (self.onVideoSeekComplete) {
        self.onVideoSeekComplete(@{@"target": self.reactTag});
      }
      break;
      
    default:
      break;
  }
  
  return VO_OSMP_ERR_NONE;
}

- (void)sendProgressUpdate
{
  if (_player == nil || [_player getPlayerStatus] != VO_OSMP_STATUS_PLAYING) {
    return;
  }
  
  if (self.onVideoProgress) {
    self.onVideoProgress(@{
                           @"src": [_source objectForKey:@"uri"],
                           @"duration": [self getDuration],
                           @"currentTime": [self getPosition],
                           @"target": self.reactTag
                           });
  }
}

- (void)sendVideoErrorWithReturnCode:(VO_OSMP_RETURN_CODE)code
{
  if (self.onVideoError) {
    self.onVideoError(@{
                        @"code": @(code),
                        @"type": @"VO_OSMP_RETURN_CODE",
                        @"target": self.reactTag
                        });
  }
}

- (void)sendVideoErrorWithEventId:(VO_OSMP_CB_EVENT_ID)eventId
{
  if (self.onVideoError) {
    self.onVideoError(@{
                        @"code": @(eventId),
                        @"type": @"VO_OSMP_CB_EVENT_ID",
                        @"target": self.reactTag
                        });
  }
}

- (void)layoutSubviews
{
  [super layoutSubviews];
  [_player notifyViewSizeChanged];
}

- (void)removeFromSuperview
{
  _player = nil;
  _eventDispatcher = nil;
  [[NSNotificationCenter defaultCenter] removeObserver:self];
  if (_progressTimer) {
    [_progressTimer invalidate];
    _progressTimer = nil;
  }
  [super removeFromSuperview];
}

@end
