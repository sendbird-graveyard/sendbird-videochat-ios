//
//  SBVCDeviceUtils.h
//  SendBirdVideoChat
//
//  Created by Jed Gyeong on 1/16/19.
//  Copyright © 2019 SendBird. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WebRTC/WebRTC.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Private
@interface SBVCDeviceUtils : NSObject

+ (nullable NSArray<RTCVideoCodecInfo *> *)availableVideoCodecs;

@end

NS_ASSUME_NONNULL_END
