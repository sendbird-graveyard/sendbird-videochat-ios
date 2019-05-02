//
//  SBVCTypes.h
//  SendBirdVideoChat
//
//  Created by Jed Gyeong on 2/6/19.
//  Copyright © 2019 SendBird. All rights reserved.
//

#ifndef SBVCTypes_h
#define SBVCTypes_h

FOUNDATION_EXTERN const NSErrorDomain NSErrorDomainSendBirdVideoChat;

typedef NS_ENUM(NSUInteger, SBVCCameraPosition) {
    SBVCCameraPositionUnspecified = 0,
    SBVCCameraPositionFront = 1,
    SBVCCameraPositionBack = 2,
};

typedef NS_ENUM(NSUInteger, SBVCEndType) {
    SBVCEndTypeNone = 0,
    SBVCEndTypeUnknown = 1,
    SBVCEndTypeEnd = 2,
    SBVCEndTypeCancel = 3,
    SBVCEndTypeDecline = 4,
    SBVCEndTypeTimeout = 5,
};

/**
 SendBird VideoChat error codes.

 - SBVCErrorUnknown: Unknown error occured.
 - SBVCErrorSendBirdConnectionRequired: SendBird connection is required.
 - SBVCErrorSendBirdRequired: Reserved for JavaScript SDK.
 - SBVCErrorInvalidAction: Invalid action.
 - SBVCErrorAcceptingFail: Cannot accept call.
 - SBVCErrorInvalidParameter: Invalid parameter.
 - SBVCErrorUnsuitableChannel: The channel is not suitable.
 - SBVCErrorAlreadyCameraSwitching: Reserved for Android SDK.
 - SBVCErrorAlreadyCallGoingOn: Error code from server.
 */
typedef NS_ENUM(NSUInteger, SBVCErrorCode) {
    SBVCErrorUnknown =                          820000,
    SBVCErrorSendBirdConnectionRequired =       820100,
    SBVCErrorSendBirdRequired =                 820130,
    SBVCErrorInvalidAction =                    820200,
    SBVCErrorAcceptingFail =                    820300,
    SBVCErrorInvalidParameter =                 820400,
    SBVCErrorUnsuitableChannel =                820401,
    SBVCErrorAlreadyCameraSwitching =           820510,
    SBVCErrorNotSupportedPlatform =             820620,
    SBVCErrorAlreadyCallGoingOn =               900600,
};

typedef NS_ENUM(NSInteger, SBVCRole) {
    SBVCRoleNone = 0,
    SBVCRoleCaller = 1,
    SBVCRoleCallee = 2,
};

typedef NS_ENUM(NSInteger, SBVCLogLevel) {
    SBVCLogLevelNone = 0,
    SBVCLogLevelError = 1,
    SBVCLogLevelWarning = 2,
    SBVCLogLevelInfo = 3,
};

typedef NS_ENUM(NSInteger, SBVCRenderingMessageType) {
    SBVCRenderingMessageTypeChat = 0,
    SBVCRenderingMessageTypeStart = 1,
    SBVCRenderingMessageTypeEnd = 2,
    SBVCRenderingMessageTypeNotRender = 3,
};

#endif /* SBVCTypes_h */
