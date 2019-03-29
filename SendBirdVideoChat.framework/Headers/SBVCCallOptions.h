//
//  SBVCCallOptions.h
//  SendBirdVideoChat
//
//  Created by Jed Gyeong on 1/10/19.
//  Copyright © 2019 SendBird. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SendBirdSDK/SendBirdSDK.h>
#import <WebRTC/WebRTC.h>

#import "SBVCLocalVideoView.h"
#import "SBVCTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 This class represents the options to start and to accept a call.
 */
@interface SBVCCallOptions : NSObject

/**
 Initializes the object with the channel URL where the call exists.

 @param channelUrl The channel URL.
 @return SBVCCallOptions object.
 */
- (nonnull instancetype)initWithChannelUrl:(nonnull NSString *)channelUrl;


/**
 Channel URL. The messages for calling will be exchanged in the channel.
 */
@property (strong, nonnull) NSString *channelUrl;

/**
 The local video view. The view shows the current user's video.
 */
@property (weak, nullable) SBVCLocalVideoView *localVideoView;

/**
 The remote video view. The view shows the opponent's video.
 */
@property (weak, nullable) __kindof UIView<RTCVideoRenderer> *remoteVideoView;

/**
 If YES, the current user's microphone is turned on.
 */
@property (atomic, assign) BOOL audioEnabled;

/**
 If YES, the current user's camera is turned on.
 */
@property (atomic, assign) BOOL videoEnabled;

/**
 The resoultion of the current user's video. The opponent receives the video with this resolution. The default value is 1080 as width and 1920 as height.
 */
@property (atomic, assign) CGSize resolution;

/**
 The FPS of the current user's video. The defaule value is 30.
 */
@property (atomic, assign) NSInteger videoFps;

/**
 The default camera position. It can be a front camera or a back camera. When the call starts or accepts, the camera is used. The default value is `SBVCCameraPositionFront`.
 */
@property (atomic, assign) SBVCCameraPosition defaultCameraPosition;

@end

NS_ASSUME_NONNULL_END
