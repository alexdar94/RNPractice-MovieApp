#import "RCTOSPlayerManager.h"
#import "RCTOSPlayer.h"
#import "VOPlayer.h"
#if __has_include(<React/RCTAssert.h>)
#import <React/RCTBridge.h>
#else
#import "RCTBridge.h"
#endif

@implementation RCTOSPlayerManager
{
  NSMutableDictionary *_mPlayers;
  NSNumber *_mNextId;
}

RCT_EXPORT_MODULE()

- (id)init
{
  if ((self = [super init])) {
    _mPlayers = [NSMutableDictionary dictionary];
    _mNextId = @0;
  }
  return self;
}

- (UIView *)view
{
  return [[RCTOSPlayer alloc] initWithEventDispatcher:self.bridge.eventDispatcher Manager:self];
}

- (dispatch_queue_t)methodQueue
{
  return dispatch_get_main_queue();
}

RCT_REMAP_METHOD(createPlayer,
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
  VOPlayer *player = [[VOPlayer alloc] init:VO_OSMP_VOME2_PLAYER initParam:nil];
  NSNumber *id = [NSNumber numberWithInt:[_mNextId intValue] + 1];
  _mNextId = id;
  _mPlayers[id] = player;
  resolve(id);
}

RCT_EXPORT_METHOD(destroyPlayer:(NSNumber * _Nonnull)id)
{
  RCTLogInfo(@"DestroyPlayer RCT ObjC called");
  VOPlayer *player = _mPlayers[id];
  [player stop];
  [player close];
  RCTLogInfo(@"Destroying RCT player - %i",[player destroy]);
  [_mPlayers removeObjectForKey:id];  
}


RCT_EXPORT_METHOD(getPlayerCountWithResolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
  NSLog(@"getPlayerCount");
  resolve([NSNumber numberWithInteger:[_mPlayers count]]);
}

RCT_EXPORT_METHOD(reset)
{
  NSLog(@"reset");
  for (id key in _mPlayers) {
    VOPlayer *player = [_mPlayers objectForKey:key];
    [player destroy];
  }
  [_mPlayers removeAllObjects];
}

- (VOPlayer *)getPlayerWithId:(NSNumber *)id
{
  NSLog(@"getPlayer");
  return [_mPlayers objectForKey:id];
}

RCT_EXPORT_VIEW_PROPERTY(src, NSDictionary);
RCT_EXPORT_VIEW_PROPERTY(paused, BOOL);
RCT_EXPORT_VIEW_PROPERTY(muted, BOOL);
RCT_EXPORT_VIEW_PROPERTY(volume, float);
RCT_EXPORT_VIEW_PROPERTY(seek, float);
RCT_EXPORT_VIEW_PROPERTY(playerId, NSNumber);

RCT_EXPORT_VIEW_PROPERTY(onPlayerInit, RCTBubblingEventBlock);
RCT_EXPORT_VIEW_PROPERTY(onVideoLoadStart, RCTBubblingEventBlock);
RCT_EXPORT_VIEW_PROPERTY(onVideoLoad, RCTBubblingEventBlock);
RCT_EXPORT_VIEW_PROPERTY(onVideoProgress, RCTBubblingEventBlock);
RCT_EXPORT_VIEW_PROPERTY(onVideoSeekComplete, RCTBubblingEventBlock);
RCT_EXPORT_VIEW_PROPERTY(onVideoError, RCTBubblingEventBlock);
RCT_EXPORT_VIEW_PROPERTY(onReadyForDisplay, RCTBubblingEventBlock);

@end
