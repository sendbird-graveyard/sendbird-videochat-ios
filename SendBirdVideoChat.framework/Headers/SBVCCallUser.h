//
//  SBVCCallUser.h
//  SendBirdVideoChat
//
//  Created by Jed Gyeong on 3/5/19.
//  Copyright © 2019 SendBird. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This class represents a caller and a callee.
 */
@interface SBVCCallUser : NSObject<NSCopying>

/**
 The user ID of the call user.
 */
@property (strong, nonnull) NSString *userId;

/**
 The nickname of the call user.
 */
@property (strong, nonnull) NSString *nickname;

/**
 The profile image URL of the call user.
 */
@property (strong, nonnull) NSString *profileUrl;

/**
 If YES, the call user uses audio.
 */
@property (atomic) BOOL isAudioEnabled;

/**
 If YES, the call user uses video.
 */
@property (atomic) BOOL isVideoEnabled;

@end

NS_ASSUME_NONNULL_END
