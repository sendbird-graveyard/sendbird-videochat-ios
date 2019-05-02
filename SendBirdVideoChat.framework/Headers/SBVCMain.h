//
//  SBVCMain.h
//  SendBirdVideoChat
//
//  Created by Jed Gyeong on 1/10/19.
//  Copyright © 2019 SendBird. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SendBirdSDK/SendBirdSDK.h>
#import <WebRTC/WebRTC.h>

#import "SBVCCall.h"
#import "SBVCCallOptions.h"
#import "SBVCVideoChatDelegate.h"
#import "SBVCVideoViewDelegate.h"

NS_ASSUME_NONNULL_BEGIN

@interface SBVCMain : NSObject<SBDChannelDelegate>

/**
 Configures SendBird Video Chat SDK.
 */
+ (void)config;

/**
 Gets the SDK version.

 @return The SDK version.
 */
+ (nonnull const NSString *)getSDKVersion;

/**
 *  Sets the log level. The log level is defined by `SBVCLogLevel`.
 *
 *  @param logLevel Log level.
 */
+ (void)setLogLevel:(SBVCLogLevel)logLevel;

/**
 Builds a call object for video chat from the push payload.

 @param payload The push payload.
 @return If the push payload is for the video chat and it has the call ID, then returns the call object. If not, returns nil. If the message that has the same message ID is received via websocket connection, then returns nil.
 */
+ (nullable SBVCCall *)buildCallFromNotification:(nonnull NSDictionary *)payload;

/**
 Builds a call instance from the user message. If the user message is not a signaling message for the video chat, returns nil.
 
 @param userMessage a user message object.
 @return If the user message is not a signaling message for the video chat, returns nil.
 */
+ (nullable SBVCCall *)buildCallFromUserMessage:(nonnull SBDUserMessage *)userMessage;

/**
 Determines the notificaion payload is a video chat or not. This method invokes the delegate methods of `SBVCVideoChatDelegate`.

 @param notificationPayload Push notification payload.
 @return If YES, the payload is for a video chat.
 */
+ (BOOL)handleNotification:(nonnull NSDictionary *)notificationPayload;

/**
 Gets a call instance with a call ID.

 @param callId Call identifier.
 @return If there is a call instance of the call Id, returns the call instance. If not, returns nil.
 */
+ (nullable SBVCCall *)getCallWithCallId:(nonnull NSString *)callId;

/**
 Gets an active call. The active call means the call that the caller starts or the callee accepts. Each device can have one active call at most.

 @return If there is an active call, then returns the call object. If not, returns nil.
 */
+ (nullable SBVCCall *)getActiveCall;

/**
 Sets dispatch queue for every completion handler and delegate. Default queue is the main queue.
 
 @param queue Dispatch queue for every completion handler and delegate.
 */
+ (void)setCompletionHandlerDelegateQueue:(dispatch_queue_t)queue;

/**
 Adds `SBVCVideoChatDelegate` with an identifier. The identifier has to be unique in the current app.

 @param delegate The instance that implements `SBVCVideoChatDelegate`.
 @param identifier The unique string.
 */
+ (void)addVideoChatDelegate:(id<SBVCVideoChatDelegate> _Nullable)delegate
                  identifier:(nonnull NSString *)identifier;

/**
 Removes `SBVCVideoChatDelegate` with an identifier.

 @param identifier The unique string.
 */
+ (void)removeVideoChatDelegateWithIdentifier:(nonnull NSString *)identifier;

/**
 Removes every `SBVCVideoChatDelegate`.
 */
+ (void)removeAllVideoChatDelegates;

/**
 Sets the `SBVCVideoViewDelegate`. The delegate has methods that returns the size of the remote video.
 If you use `SBVCMTLRemoteVideoView` for the remote view, you don't have to use this.
 However, if the device doesn't support Metal and you have to use `SBVCEAGLRemoteVideoView`, then implement the method and resize the remote view with the size that this method returns.
 
 @param delegate The instance that implements `SBVCVideoViewDelegate`.
 */
+ (void)setVideoViewDelegate:(nullable id<SBVCVideoViewDelegate>)delegate;

/**
 Removes `SBVCVideoViewDelegate`.
 */
+ (void)removeVideoViewDelegate;

/**
 Sets the timeout for the start call. If the callee doesn't answer the call for the timeout,

 @param timeout The timeout in seconds. The minumum value is 30 and the maximum value is 60. The default value is 30.
 */
+ (void)setStartCallTimeout:(NSInteger)timeout;

/**
 To establish the video chat, each peer exchanges signaling message. Some of the messages has to be rendered in the view.
 In order to determine that, every `SBDBaseMessage` object needs to be checked by this method.
 If the message is a regular chat message, returns `SBVCRenderingMessageTypeChat`.
 If the message is a start message or an end message of the video chat, returns `SBVCRenderingMessageTypeStart` or ``SBVCRenderingMessageTypeEnd`.
 If the message is for signaling and it is not required to be rendered in the view, returns `SBVCRenderingMessageTypeNotRender`.
 You should use this method in `channel:didReceiveMessage:` of `SBDChannelDelegate` not to add the message object to the message array.
 Also, you should use this in any methods to render message for `UITableView` or `UICollectionView`.
 
 @param message The `SBDBaseMessage` object.
 @return `SBVCRenderingMessageType` value.
 */
+ (SBVCRenderingMessageType)getRenderingMessageType:(nonnull SBDBaseMessage *)message;

/**
 Gets the cameras of the device.
 
 @return The array of the cameras.
 */
+ (nullable NSArray<AVCaptureDevice *> *)getCameraDeviceList;

/**
 Starts a video chat.

 @param audioOnly If this chat supports an audio call only, sets YES.
 @param options The options for the call.
 @param completionHandler The handler block to execute. Keep the `call` instance for the next signaling.
 */
+ (void)startCallWithAudioOnly:(BOOL)audioOnly
                       options:(nonnull SBVCCallOptions *)options
             completionHandler:(nullable void (^)(SBDError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
