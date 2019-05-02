//
//  SBVCBaseCall.h
//  SendBirdVideoChat
//
//  Created by Jed Gyeong on 3/1/19.
//  Copyright © 2019 SendBird. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SendBirdSDK/SendBirdSDK.h>
#import <WebRTC/WebRTC.h>

#import "SBVCCallUser.h"
#import "SBVCTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 This class describes each call. It has an identifier as a unique key.
 */
@interface SBVCBaseCall : NSObject

/**
 Call identifier.
 */
@property (strong, nonnull) NSString *callId;

/**
 Channel URL where the call is established.
 */
@property (strong, nonnull) NSString *channelUrl;

/**
 The message ID of a user message that is used for the signaling.
 */
@property (atomic) long long messageId;

/**
 The caller's object. It can be used for showing the caller's name on the screen of the callee.
 */
@property (strong, nullable, nonatomic, readonly) SBVCCallUser *caller;

/**
 The callee's object. It can be used for showing the callee's name on the screen of the caller.
 */
@property (strong, nullable, nonatomic, readonly) SBVCCallUser *callee;

/**
 The ender who ends the call.
 */
@property (strong, nullable, nonatomic, readonly, getter=getEnder) SBVCCallUser *ender;

/**
 If the call is ended, the type represents the reason why the call is ended.
 */
@property (nonatomic, readonly) SBVCEndType endType;

/**
 The period that the call lasted.
 */
@property (nonatomic, readonly) long long period;

/**
 The current user's role on the call.
 */
@property (nonatomic, readonly) SBVCRole myRole;

/**
 Returns the call is for audio only.

 @return If the call is for audio only, returns YES.
 */
- (BOOL)isAudioCall;

@end

NS_ASSUME_NONNULL_END
