#if __has_include(<React/RCTAssert.h>)
#import <React/RCTViewManager.h>
#else
#import "RCTViewManager.h"
#endif
#import "VOPlayer.h"

@interface RCTOSPlayerManager : RCTViewManager

- (VOPlayer *_Nonnull)getPlayerWithId:( NSNumber * _Nonnull )id;

@end
