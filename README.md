# SendBird VideoChat for iOS

[![Platform](https://img.shields.io/badge/platform-iOS-orange.svg)](https://github.com/smilefam/sendbird-videochat-ios)
[![Languages](https://img.shields.io/badge/Language-Objective--C-orange.svg)](https://github.com/smilefam/sendbird-videochat-ios)
![CocoaPods](https://img.shields.io/badge/CocoaPods-compatible-red.svg)
[![Commercial License](https://img.shields.io/badge/license-Commercial-brightgreen.svg)](https://github.com/smilefam/sendbird-videochat-ios/blob/master/LICENSE.md)

SendBird `VideoChat` is an add-on to your application that enables users to make video and audio calls. SendBird `VideoChat` is available through [WebRTC](https://webrtc.org/). 

Note: This is a beta version and is not yet open to all users. If you would like to try SendBird `VideoChat`, contact our [sales support](https://help.sendbird.com/hc/en-us/requests/new) for more information. 

## Contents

- [How to set and initialize `VideoChat`](#how-to-set-and-initialize-videochat)
    - [Prerequisites](#prerequisites)
    - [CocoaPods](#cocoapods)
    - [Carthage](#carthage)
    - [`AppDelegate.h` and `AppDelegate.m` in the application](#appdelegateh-and-appdelegatem-in-the-application)
- [Restrictions](#restrictions)
- [Making video and audio calls](#making-video-and-audio-calls)
    - [`startCallWithAudioOnly:...`](#startcallwithaudioonly)
    - [Registering/unregistering an event delegate](#registeringunregistering-an-event-delegate)
    - [Timeout for `startCallWithAudioOnly:...`](#timeout-for-startcallwithaudioonly)
    - [Getting a `SBVCCall` instance](#getting-a-sbvccall-instance)
    - [Identifying the type of a message](#identifying-the-type-of-a-message)
    - [Starting a call from a PushKit notification](#starting-a-call-from-a-pushkit-notification)
- [Classes](#classes)
    - [`SBVCVideoChatDelegate`](#sbvcvideochatdelegate)
    - [`SBVCLocalVideoView`](#sbvclocalvideoview)
    - [`SBVCRemoteVideoView`](#sbvcremotevideoview)
    - [`SBVCCallOptions`](#sbvccalloptions)
    - [`SBVCCall`](#sbvccall)
    - [`SBVCCallUser`](#sbvccalluser)
    - [`SBVCErrorCode`](#sbvcerrorcode)
- [Change Log](https://github.com/smilefam/sendbird-videochat-ios/blob/master/CHANGELOG.md)
- [License](https://github.com/smilefam/sendbird-videochat-ios/blob/master/LICENSE.md)

## How to set and initialize `VideoChat`

The following shows how to install SendBird `VideoChat` framework via `CocoaPods` or `Carthage` and how to initialize it in your application.   

### Prerequisites

* iOS 9.0 or higher
* [SendBirdSDK framework](https://github.com/smilefam/sendbird-ios-framework) v3.0.133 or higher
* [Git Large File Storage](https://git-lfs.github.com/)
* [WebRTC framework](https://github.com/smilefam/sendbird-webrtc-ios)
* [CocoaPods](https://cocoapods.org/) or [Carthage](https://github.com/Carthage/Carthage)
* Real devices. **The iOS simulator is not supported.**

### CocoaPods

Add the lines below to your `Podfile` file at the target of your project directory.

```
pod 'SendBirdSDK'
pod 'SendBirdWebRTC', :git => 'https://github.com/smilefam/SendBird-WebRTC-iOS.git', :tag => 'v1.0'
pod 'SendBirdVideoChat'
```

Install SendBirdVideoChat framework through CocoaPods.

```
pod install
```

Now you can see installed SendBirdVideoChat framework by inspecting `YOUR_PROJECT.xcworkspace`.

### Carthage

Add the lines below to your `Cartfile`

```
github "smilefam/sendbird-webrtc-ios.git"
github "smilefam/sendbird-ios-framework"
github "smilefam/sendbird-videochat-ios"
```

Install the frameworks through Carthage.

```
carthage update
```

Go to your Xcode project's "General" settings. Open `<YOUR_XCODE_PROJECT_DIRECTORY>/Carthage/Build/iOS` in Finder and drag `WebRTC.framework`, `SendBirdSDK.framework`, and `SendBirdVideoChat.framework` to the "Embedded Binaries" section in Xcode. Make sure `Copy items if needed` is selected and click `Finish`.

### `AppDelegate.h` and `AppDelegate.m` in the application

To initialize `SendBirdVideoChat` framework, Add the lines below to your `AppDelegate.m` file.

```objectivec
// AppDelegate.h

#import <SendBirdSDK/SendBirdSDK.h>
#import <SendBirdVideoChat/SendBirdVideoChat.h>
#import <WebRTC/WebRTC.h>

// ...
```

```objectivec
// AppDelegate.m
#import "AppDelegate.h"

// ...

@interface AppDelegate ()

// ...

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  // ...

  [SBVCMain config]

  // ...
}

```

## Restrictions

There are a few restrictions that apply to the beta version of SendBird `VideoChat`.  

- It is only available in a `normal`, `private` group channel settings. (non-super and non-public)
- It only supports video and audio calls between two users.   
- To start video and audio calls, the two users must be connected to SendBird server.  
- In the same channel, you can't start a new, separate video or audio call.  

> Warning: Don't call the `removeAllChannelDelegates` of SendBird iOS SDK. It will not only remove delegates already added, but also remove delegates managed by `SendBirdVideoChat`.  

## Making video and audio calls

You can make video and audio calls between two users using the `SendBirdVideoChat`'s methods.   

### `startCallWithAudioOnly:...`  

The `startCallWithAudioOnly:options:completionHandler:` sends a video or audio call request to SendBird server with specified options. This function requires the `audioOnly` and `options` parameters.   

- **audioOnly**: determines whether to enable an audio only in the call or both a video and an audio. 
- **options**: specifies the call settings with a `SBVCCallOptions` instance. For more information on the settings, see the [SBVCCallOptions](#-SBVCCallOptions). 

```objectivec
[SBVCMain startCallWithAudioOnly:isAudioOnly options:options completionHandler:^(SBDError * _Nullable error) {

}];
```

If the server accepts the request and notify a callee of it, a caller receives a success callback through the `SBVCVideoChatDelegate`'s `didSendStartCall:withMessage:`. And the callee also receives a notification about the request through the `SBVCVideoChatDelegate`'s `didReceiveStartCall:`.  

### Registering/unregistering an event delegate

Like the SendBird SDKs, the `SBVCVideoChatDelegate` has its own event delegate. The `SBVCVideoChatDelegate` supports various methods which receive events callbacks from SendBird server. You can create, register, and implement the delegate method in your application. Then your application will be notified of events happening in video and audio calls. 

```objectivec
// YourViewController.h
#import <SendBirdVideoChat/SendBirdVideoChat.h>

@interface YourViewController : UIViewController<SBVCVideoChatDelegate>

// ...

@end
```

```objectivec
// YourViewController.m
#import "YourViewController.h"

@implementation YourViewController

// ...

- (void)viewDidLoad {
  // ..

  [SBVCMain addVideoChatDelegate:self identifier:IDENTIFIER];
  
  // ..
}

#pragma mark - SBVCVideoChatDelegate
- (void)didSendStartCall:(SBVCCall *)call withMessage:(SBDUserMessage *)message {

}

- (void)didReceiveStartCall:(SBVCCall *)call {

}

- (void)didSendAcceptCall:(SBVCCall *)call {

}

- (void)didReceiveAcceptCall:(SBVCCall *)call {

}

- (void)didSendEndCall:(SBVCCall *)call message:(SBDUserMessage *)message {

}

- (void)didReceiveEndCall:(nonnull SBVCCall *)call {

}

- (void)didConnectCall:(SBVCCall *)call {

}

- (void)didOpponentAudioStateChange:(nonnull SBVCCall *)call {

}

- (void)didOpponentVideoStateChange:(nonnull SBVCCall *)call {

}

// ...

// If you unregister SBVCVideoChatDelegate, use as follows.  
// [SBVCMain removeVideoChatDelegateWithIdentifier:IDENTIFIER];
// [SBVCMain removeAllVideoChatDelegates];

@end
```

### Timeout for `startCallWithAudioOnly:...`

If a callee doesn't respond to a call request from a caller during 30 seconds (by default), the `SendBirdVideoChat` automatically closes the call. A timeout value can be set between 30 and 60 seconds.  

```objectivec
[SBVCMain setStartCallTimeout:40];
```

### Getting a `SBVCCall` instance  

The `SendBirdVideoChat` provides a `SBVCCall` class which has its own properties and methods that represent a specific video or audio call. For more information on the object, see the [`SBVCCall`](#-SBVCCall). 

- **getActiveCall**: retrieves the current `SBVCCall` instance in progress.  
- **getCallWithCallId:**: retrieves the `SBVCCall` instance by a passed call ID.   
- **buildCallFromNotification:**: with the `SendBird` payload in a push notificaiton message, creates and returns a new 'SBVCCall' instance.  
- **buildCallFromUserMessage:**: with a passed `SBDUserMessage` object which requests a video or audio call, creates and returns a new `SBVCCall` instance.  

```objectivec
SBVCCall *activeCall = [SBVCMain getActiveCall];
SBVCCall *call = [SBVCMain getCallWithCallId:CALL_ID];
SBVCCall *call = [SBVCMain buildCallFromNotification:payload.dictionaryPayload];
SBVCCall *call = [SBVCMain buildCallFromUserMessage:userMessage];
```

### Identifying the type of a message

Using the `getRenderingMessageType:`, you can identify the type of a passed message and determine how to render your chat view based on the message. The method returns one of the following four values:  

- **SBVCRenderingMessageTypeChat**: returned if a message is one of `SBDUserMessage`, `SBDFileMessage`, and `SBDAdminMessage` as the SendBird SDK's `SBDBaseMessage`.    
- **SBVCRenderingMessageTypeStart**: the call request message.   
- **SBVCRenderingMessageTypeEnd**: the call close message.   
- **SBVCRenderingMessageTypeNotRender**: a message that does not need to be rendered on the chat view.  

```objectivec
SBVCRenderingMessageType renderingType = [SBVCMain getRenderingMessageType:message];
```

### Starting a call from a PushKit notification

To receive the notificion for VideoChat, the client has to implement `PushKit`. Upon receiving a `PushKit` notification, the system automatically launches your app if it isn't running. The `PushKit` generates a different device token with the user notification. To register the `PushKit` device token, use [`registerDevicePushKitToken:unique:completionHandler:`](https://docs.sendbird.com/ref/ios/Classes/SBDMain.html#//api/name/registerDevicePushKitToken:unique:completionHandler:) in [`SBDMain`](https://docs.sendbird.com/ref/ios/Classes/SBDMain.html).

If your app runs on iOS 10 or higher, you can use CallKit that provides the system-calling UI for your app and helps the app integrate with the system. See [`CallKit`](https://developer.apple.com/documentation/callkit?language=objc) and [`Enhancing VoIP Apps with CallKit at WWDC 2016`](https://developer.apple.com/videos/play/wwdc2016/230/) for more information.

If your app runs on iOS 9 or lower, you have to use a local notification to inform the incoming call to a user.

```objectivec
// AppDelegate.h
#import <PushKit/PushKit.h>
#import <SendBirdVideoChat/SendBirdVideoChat.h>

@interface AppDelegate : UIResponder <PKPushRegistryDelegate, SBVCVideoChatDelegate>

// ...

@end
```

```objectivec
// AppDelegate.m

@interface AppDelegate ()

@property (strong, nullable) PKPushRegistry *pushRegistry;

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  // ...

  [SBVCMain addVideoChatDelegate:self identifier:IDENTIFIER];

  // ...

  self.pushRegistry = [[PKPushRegistry alloc] initWithQueue:dispatch_get_main_queue()];
  self.pushRegistry.delegate = self;
  self.pushRegistry.desiredPushTypes = [NSSet setWithObject:PKPushTypeVoIP];

  // ...

}

- (void)pushRegistry:(PKPushRegistry *)registry didUpdatePushCredentials:(PKPushCredentials *)pushCredentials 
             forType:(PKPushType)type {
  [SBDMain registerDevicePushKitToken:pushCredentials.token unique:YES completionHandler:^(SBDPushTokenRegistrationStatus status, SBDError * _Nullable error) {
    // ...
  }];
}

// PKPushRegistryDelegate for iOS 10.x or lower.
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload
             forType:(PKPushType)type {
  if (@available(iOS 10.0, *)) {
    if (@available(iOS 11.0, *)) {
      // Do nothing.
      // This method is not called in iOS 11 or higher.
    }
    else {
      if ([SBDMain getCurrentUser] == nil) {
        // Keep the payload globally.
        // Start CallKit after connecting to SendBird is completed.
      }
      else {
        if (![SBVCMain handleNotification:payload.dictionaryPayload]) {
          // Do something if the push payload isn't for SendBird VideoChat.
        }
      }
    }
  }
  else {
    // iOS 9.x or lower
    if ([SBVCMain isStartCallNotification:payload.dictionaryPayload]) {
      // Schedule the local notification for incoming call.
    }
    else {
      if ([SBVCMain handleNotification:payload.dictionaryPayload]) {
        if ([SBVCMain isEndCallNotification:payload.dictionaryPayload]) {
          // Schedule the local notification for ending call.
        }
      }
    }
  }
}

// PKPushRegistryDelegate for iOS 11 or higher
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload
             forType:(PKPushType)type withCompletionHandler:(void(^)(void))completion API_AVAILABLE(ios(11.0)) {
  if ([SBDMain getCurrentUser] == nil) {
    // Keep the payload globally.
    // Start CallKit after connecting to SendBird is completed.
  }
  else {
    if (![SBVCMain handleNotification:payload.dictionaryPayload]) {
      // Do something if the push payload isn't for SendBird VideoChat.
    }
  }
}

// SBVCVideoChatDelegate methods.
// This delegate method is called by `handleNotification:`.
- (void)didReceiveStartCall:(SBVCCall *)call {
  if (@available(iOS 10.0, *)) {
    // Display incoming call via CallKit.
  }
}

@end
```

## Classes

### `SBVCVideoChatDelegate`

The `SBVCVideoChatDelegate` supports various methods which receive events delegate methods from SendBird server. If the delegate is registered and implemented in your application, events happening in video and audio calls are notified to the application through the methods.
The following are provided with the `SBVCVideoChatDelegate`:

1. **odidSendStartCall:withMessage:**
- Called when a caller's video or audio call request is successfully accepted by SendBird server from the `startCallWithAudioOnly:options:completionHandler:`. (At the caller's application) 
- **call**: a `SBVCCall` instance which contains the current call status.  
- **message**: a `SBDUserMessage` instance which contains the text sent with the call request.  
2. **didReceiveStartCall:**
- Called when a callee receives a video or audio call request. (At the callee's application)  
- **call**: a `SBVCCall` instance which contains the current call status.  
3. **didSendAcceptCall:**
- Called when a callee has accepted a video or audio call request using the `acceptWithOptions:completionHandler:` and SendBird server confirms the acceptance. (At the callee's application)      
- **call**: a `SBVCCall` instance which contains the current call status.  
4. **didReceiveAcceptCall:**
- Called when TURN server starts a video or audio call delivery between a caller and callee. (At the caller's application)    
- **call**: a `SBVCCall` instance which contains the current call status.  
5. **didSendEndCall:message:**
- Called when a call close request has been sent to SendBird server using the `endWithCompletionHandler:` and the server successfully accepts the request. (At the application which sent the close request)  
- **call**: a `SBVCCall` instance which contains the current call status.  
- **message**: a `UserMessage` instance which contains the text sent with the call close request.  
6. **didReceiveEndCall:**
- Called when a call has been closed from the opponent's request. (At the application which receives the close request)    
- **call**: a `SBVCCall` instance which contains the current call status.  
7. **didConnectCall:**
- Called when caller and callee are connected via SendBird server and can communicate with each other. (at both applications)   
- **call**: a `SBVCCall` instance which contains the current call status.  
8. **didOpponentAudioStateChange:**
- Called when the audio state of either a caller or callee has been changed. (Notifies the opposite application)    
- **call**: a `SBVCCall` instance which contains the current call status.  
9. **didOpponentVideoStateChange:**
- Called when the video state of either a caller or callee has been changed. (Notifies the opposite application) 
- **call**: a `SBVCCall` instance which contains the current call status.  

### `SBVCLocalVideoView`

The `SBVCLocalVideoView` supports the methods for local video chat view.

### `SBVCRemoteVideoView`

The `SBVCRemoteVideoView` supports the methods for remote video chat view.

### `SBVCCallOptions`  

The `SBVCCallOptions` is a class that users use to request calls with the `startCallWithAudioOnly:options:completionHandler:` or to accept calls with the `acceptWithOptions:completionHandler:`. The items of `SBVCCallOptions` are:

- **initWithChannelUrl:** (required): specifies the URL of the channel to send a call request.   
- **localVideoView**: specifies the `SBVCLocalVideoView` to render the current user's chat view. 
- **remoteVideoView**: specifies the `SBVCRemoteVideoView` to render the opponent's chat view. 
- **videoEnabled**: determines whether to use video in the `SBVCCall`. This value is only accepted in a video call.  
- **audioEnabled**: determines whether to use audio in the `SBVCCall`.
- **resolution**: specifies the width and the height of the video. This value is only effective in a video call.      
- **videoFps**: specifies the frame rate of the video. This value is only effective in a video call.    
- **defaultCameraPosition**: specifies the default camera. Try to set the front camera if `YES`.

```objectivec
SBVCOptions *options = [[SBVCOptions alloc] initWithChannelUrl:CHANNEL_URL];
options.videoEnabled = DEFAULT_VIDEO_ENABLED;
options.audioEnabled = DEFAULT_AUDIO_ENABLED;
options.resolution = CGSizeMake(720, 1280);
options.videoFps = 30;
options.defaultCameraPosition = SBVCCameraPositionFront; // or SBVCCameraPositionBack
options.localVideoView = localVideoView;
options.remoteVideoView = remoteVideoView;
```

### `SBVCCall`

Through a `SBVCCall` instance, you can make actions of a video or audio call. It also contains up-to-date information of the call.  

- **callId**: retrieves the unique ID that distinguishes each call.  
- **channelUrl**: retrieves the URL of the channel of your video or audio call.  
- **messageId**: retrieves the ID of a message which containing information about the `SBVCCall`.  
- **isAudioCall**: checks if the `SBVCCall` is an audio call.  
- **caller**: retrieves information of the `Caller`, the one who makes the call.  
- **callee**: retrieves information of the `Callee`, the one who receives the call.  
- **getEnder**: retrieves information of the `Caller` or `Callee`, the one who ends the call.   
- **endType**: specifies that the `SBVCCall` has ended. This has one of the following values.   
    - **SBVCEndTypeNone**: it's not ended yet.  
    - **SBVCEndTypeCancel**: the `endWithCompletionHandler:`called by the `Caller` before `Callee` accepts the `SBVCCall`.   
    - **SBVCEndTypeDecline**: the `endWithCompletionHandler:` called by the `Callee` without accepting the `SBVCCall`.  
    - **SBVCEndTypeEnd**: a `Caller` or `Callee` ended the video or audio call after the connection.   
    - **SBVCEndTypeTimeout**: the `Call` was closed when a `Callee` didn't respond to a call request. 
    - **SBVCEndTypeUnknown**: the `Call` was closed for unknown reasons.   
- **period**: retrieves the length of time in unix timestamp for `Call`.    
- **myRole**: retrieves the role on the `Call` as a `SBVCRoleCaller` or `SBVCRoleCallee`.
- **acceptWithOptions:completionHandler:**: the `Callee` accepts the `SBVCCall`.    
- **endWithCompletionHandler:**: close the `SBVCCall`.    
- **startVideo**: calls the `didOpponentVideoStateChange:` delegate method that you registered to start video streaming on the `SBVCCall`.       
- **stopVideo**: calls the `didOpponentVideoStateChange:` handler that you registered to stop video streaming on the `SBVCCall`.     
- **muteMicrophone**: calls the `didOpponentAudioStateChange:` handler that you registered to start audio streaming on the `SBVCCall`.      
- **unmuteMicrophone**: calls the `didOpponentAudioStateChange:` handler that you registered to stop audio streaming on the `SBVCCall`.      

```objectivec
- (void)didSendStartCall:(SBVCCall *)call withMessage:(SBDUserMessage *)message {
  // Cancel call
  [call endWithCompletionHandler:^(SBDError * _Nullable error) {

  }
}

- (void)didReceiveStartCall:(SBVCCall *)call {
  // Decline a call
  [call endWithCompletionHandler:^(SBDError * _Nullable error) {

  }
}

- (void)didConnectCall:(SBVCCall *)call {
  // End call
  [call endWithCompletionHandler:^(SBDError * _Nullable error) {

  }
}
```

```objectivec
SBVCCall *call = [SBVCMain getActiveCall];
[call startVideo];
[call stopVideo];
[call muteMicrophone];
[call unmuteMicrophone];
```

### `SBVCCallUser`

`SBVCCallUser` can be identified as a `Caller` or `Callee`. The `Caller` is the one who requests a call and the `Callee` is the one who receives a call request.   

- **userId**: retrieve the user ID of the `Caller` or `Callee`.  
- **nickname**: retrieve the nickname of the `Caller` or `Callee`.  
- **profileUrl**: retrieve the profile URL of the `Caller` or `Callee`.  
- **isAudioEnabled**: indicates whether the `Caller` or `Callee` is using audio.  
- **isVideoEnabled**: indicates whether the `Caller` or `Callee` is using video.  

### `SBVCErrorCode`

The [`SBDError`](https://docs.sendbird.com/ref/ios/Classes/SBDError.html) is returned in the event of an error in `SendBirdVideoChat`.  

```objectivec
typedef NS_ENUM(NSUInteger, SBVCErrorCode ) {
   SBVCErrorUnknown = 820000,
   SBVCErrorSendBirdConnectionRequired = 820100,
   SBVCErrorSendBirdRequired = 820130,
   SBVCErrorInvalidAction = 820200,
   SBVCErrorAcceptingFail = 820300,
   SBVCErrorInvalidParameter = 820400,
   SBVCErrorUnsuitableChannel = 820401,
   SBVCErrorAlreadyCameraSwitching = 820510,
   SBVCErrorAlreadyCallGoingOn = 900600,
};
```
