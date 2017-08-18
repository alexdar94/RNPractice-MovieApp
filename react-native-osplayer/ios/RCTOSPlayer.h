#import <UIKit/UIKit.h>
#import "VOCommonPlayerDelegate.h"
#import "VOPlayer.h"
#import "RCTOSPlayerManager.h"

@class RCTEventDispatcher;

@interface RCTOSPlayer : UIView <VOCommonPlayerDelegate>

@property (nonatomic, copy) RCTBubblingEventBlock onPlayerInit;
@property (nonatomic, copy) RCTBubblingEventBlock onVideoLoadStart;
@property (nonatomic, copy) RCTBubblingEventBlock onVideoLoad;
@property (nonatomic, copy) RCTBubblingEventBlock onVideoProgress;
@property (nonatomic, copy) RCTBubblingEventBlock onVideoSeekComplete;
@property (nonatomic, copy) RCTBubblingEventBlock onVideoError;
@property (nonatomic, copy) RCTBubblingEventBlock onReadyForDisplay;

- (instancetype)initWithEventDispatcher:(RCTEventDispatcher *)eventDispatcher Manager:(RCTOSPlayerManager *)manager NS_DESIGNATED_INITIALIZER;

@end
