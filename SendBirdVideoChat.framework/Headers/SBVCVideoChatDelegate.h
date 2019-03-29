//
//  SBVCVideoChatDelegate.h
//  SendBirdVideoChat
//
//  Created by Jed Gyeong on 1/14/19.
//  Copyright © 2019 SendBird. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBVCCall.h"
#import "SBVCRemoteVideoView.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Delegate that detects the video chat events.
 */
@protocol SBVCVideoChatDelegate <NSObject>

@optional

/**
 A callback when the current user sent a start call to the callee. This is invoked when the [`startCallWithAudioOnly:options:completionHandler:`](../Classes/SBVCMain.html#//api/name/startCallWithAudioOnly:options:completionHandler:) of `SBVCMain` class succeeded only.

 @param call The call object. This has to be used for the next signaling.
 @param message The message object. It can be used for rendering in a view.
 */
- (void)didSendStartCall:(nonnull SBVCCall *)call withMessage:(nonnull SBDUserMessage *)message;

/**
 A callback when the current user received a start call from the caller. If you need to render the view for starting call, then use the message object in [`channel:didReceiveMessage:`](https://docs.sendbird.com/ref/ios/Protocols/SBDChannelDelegate.html#//api/name/channel:didReceiveMessage:) of [`SBDChannelDelegate`](https://docs.sendbird.com/ref/ios/Protocols/SBDChannelDelegate.html)

 @param call The call object.
 */
- (void)didReceiveStartCall:(nonnull SBVCCall *)call;

/**
 A callback when the current user sent an accept call to the caller for the call. This is invoked when the [`acceptWithOptions:completionHandler:`](../Classes/SBVCCall.html#//api/name/acceptWithOptions:completionHandler:) of `SBVCCall` instance successed only.
 
 @param call The call object.
 */
- (void)didSendAcceptCall:(nonnull SBVCCall *)call;

/**
 A callback when the current user received an accept call from the caller.
 
 @param call The call object.
 */
- (void)didReceiveAcceptCall:(nonnull SBVCCall *)call;

/**
 A callback when the current user sent an end call to the caller for the call.
 The current user can send an end call explicitly with the [`endWithCompletionHandler:`](../Classes/SBVCCall.html#//api/name/endWithCompletionHandler:) of `SBVCCall` instance.
 The SDK can send an end call implicitly when a timeout and an exception occured inside.

 @param call The call object. This can't be used for the other signaling.

 @param message The message object. It can be used for rendering in a view.
 */
- (void)didSendEndCall:(nonnull SBVCCall *)call message:(nonnull SBDUserMessage *)message;

/**
 A callback when the current user received an end call from the caller or the server. If you need to render the view for ending call, then use the message object in [`channel:didReceiveMessage:`](https://docs.sendbird.com/ref/ios/Protocols/SBDChannelDelegate.html#//api/name/channel:didReceiveMessage:) of [`SBDChannelDelegate`](https://docs.sendbird.com/ref/ios/Protocols/SBDChannelDelegate.html)

 @param call The call object. This can't be used for the other signaling.
 */
- (void)didReceiveEndCall:(nonnull SBVCCall *)call;

/**
 A callback when the connection for the video chat is established.

 @param call The call object.
 */
- (void)didConnectCall:(nonnull SBVCCall *)call;

/**
 A callback when the opponent changes the audio state.

 @param call The call object. The caller or the callee in the call object has the new value for the audio state. The current user's role has to be checked.
 */
- (void)didOpponentAudioStateChange:(nonnull SBVCCall *)call;

/**
 A callback when the opponent changes the video state.
 
 @param call The call object. The caller or the callee in the call object has the new value for the video state. The current user's role has to be checked.
 */
- (void)didOpponentVideoStateChange:(nonnull SBVCCall *)call;

@end

NS_ASSUME_NONNULL_END
