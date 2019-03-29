//
//  SBVCCall.h
//  SendBirdVideoChat
//
//  Created by Jed Gyeong on 3/1/19.
//  Copyright © 2019 SendBird. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SendBirdSDK/SendBirdSDK.h>
#import <WebRTC/WebRTC.h>

#import "SBVCBaseCall.h"
#import "SBVCCallOptions.h"
#import "SBVCLocalVideoView.h"
#import "SBVCRemoteVideoView.h"
#import "SBVCTypes.h"

NS_ASSUME_NONNULL_BEGIN


/**
 This class is a subclass of `SBVCBaseCall`. The methods to manipulate a call are included.
 */
@interface SBVCCall : SBVCBaseCall

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability"
- (nonnull instancetype)init;
#pragma clang diagnostic pop

/**
 Accepts a call. It has to be called with the call object that the `didReceiveStartCall:` delegate method of `SBVCVideoChatDelegate` returns.
 The completion handler returns error only. If you need a call object, then implement `didSendAcceptFromCall:` delegate method of `SBVCVideoChatDelegate`.
 
 @param options The options for the call.
 @param completionHandler The handler block to execute.
 */
- (void)acceptWithOptions:(nonnull SBVCCallOptions *)options
            completionHandler:(nullable void (^)(SBDError * _Nullable error))completionHandler;

/**
 Ends a call. The completion handler returns error only. If you need a call object, then implement `didSendEndCall:` delegate method of `SBVCVideoChatDelegate`.

 @param completionHandler The handler block to execute.
 */
- (void)endWithCompletionHandler:(nullable void (^)(SBDError * _Nullable error))completionHandler;

/**
 Sets the local video view. The client has to set the local video view as soon as the start call is completed and the view is ready.

 @param localVideoView The local video view object.
 */
- (void)setLocalVideoView:(nonnull SBVCLocalVideoView *)localVideoView;

/**
 Sets the remote video view. The client has to set the remote video view as soon as the start call is completed and the view is ready.

 @param remoteVideoView The remote video view object.
 */
- (void)setRemoteVideoView:(nonnull SBVCRemoteVideoView *)remoteVideoView;

#pragma mark - Device control

/**
 Starts a video. It is available when the call is a video call. The opponent can see the current user.
 */
- (void)startVideo;

/**
 Stops a video. It is available when the call is a video call. The opponent can't see the current user.
 */
- (void)stopVideo;

/**
 Mutes a microphone. The opponent can hear the current user.
 */
- (void)muteMicrophone;

/**
 Unmutes a mircophone. The opponent can't hear the current user.
 */
- (void)unmuteMicrophone;

/**
 Turns on a speaker. It doesn't affect the mute state of the microphone.
 */
- (void)turnOnSpeaker;

/**
 Turns off a speaker. It doesn't affect the mute state of the microphone.
 */
- (void)turnOffSpeaker;

/**
 Switches the camera. It switches the front camera and the back camera.
 */
- (void)switchCamera;

@end

NS_ASSUME_NONNULL_END
