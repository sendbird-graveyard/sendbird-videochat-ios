//
//  SBVCVideoViewDelegate.h
//  SendBirdVideoChat
//
//  Created by Jed Gyeong on 2/26/19.
//  Copyright © 2019 SendBird. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBVCRemoteVideoView.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Delegate that detects the change of the remote view's size.
 */
@protocol SBVCVideoViewDelegate <NSObject>

@optional

/**
 A callback when the remote video view's size is changed. The client has to update the view's size when this delegate is invoked.

 @param videoView The remote video view.
 @param size The size of the remote video view.
 */
- (void)remoteVideoView:(nonnull SBVCRemoteVideoView *)videoView didChangeVideoSize:(CGSize)size;


@end

NS_ASSUME_NONNULL_END
