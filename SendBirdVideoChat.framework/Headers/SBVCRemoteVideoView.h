//
//  SBVCRemoteVideoView.h
//  SendBirdVideoChat
//
//  Created by Jed Gyeong on 3/13/19.
//  Copyright © 2019 SendBird. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WebRTC/WebRTC.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The video view to show the remote user.
 */
#if defined(__aarch64__)
@interface SBVCRemoteVideoView : RTCMTLVideoView

@end
#else
@interface SBVCRemoteVideoView : RTCEAGLVideoView

@property(nonatomic) UIViewContentMode videoContentMode;

@end
#endif

NS_ASSUME_NONNULL_END
