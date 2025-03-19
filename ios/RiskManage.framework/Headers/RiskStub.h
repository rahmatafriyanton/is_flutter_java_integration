//
//  RiskManage.h
//  RiskManage
//
//  Created by bigdog on 2018/12/17.
//  Copyright © 2018年 appsec. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for RiskManage.
FOUNDATION_EXPORT double BCERiskManageVersionNumber;

//! Project version string for RiskManage.
FOUNDATION_EXPORT const unsigned char BCERiskManageVersionString[];

NS_ASSUME_NONNULL_BEGIN

////online structure
typedef NSURLSessionAuthChallengeDisposition (^BCERiskURLSessionDidReceiveAuthenticationChallengeBlock)
(NSURLSession * __nullable session,
 NSURLAuthenticationChallenge * __nullable challenge,
 NSURLCredential * _Nullable __autoreleasing * _Nullable credential);

typedef enum{
    kRiskCheckTypeUdid,
    kRiskCheckTypeDevInfo,
    kRiskCheckTypeApkInfo,
    kRiskCheckTypeStartInfo,
    kRiskCheckTypeStart,
    kRiskCheckTypeCrash,
    kRiskCheckTypeEmulator,
    kRiskCheckTypeLocation,
    kRiskCheckTypeRoot,
    kRiskCheckTypeHostFraud,
    kRiskCheckTypeDevices_Reuse,
    kRiskCheckTypeInject,
    kRiskCheckTypeDebugger,
    kRiskCheckTypeHttpProxy,
    kRiskCheckTypeVpnProxy,
    kRiskCheckTypeGamePlugin,
    kRiskCheckTypeSpeed,
    kRiskCheckTypeEnvCheck,
    kRiskCheckTypeGyroscope,
    kRiskCheckTypeMultiMessage,
    kRiskCheckTypeScreenSharing,
    kRiskCheckTypeUnknown,
    kRiskCheckTypeRiskEvent
} BCERiskCheckType;
typedef void (^BCECallBack)(NSDictionary * _Nullable dictionary,BCERiskCheckType modularType);

////offline structure
typedef enum {
    kRiskEventUdid, //0
    kRiskEventRoot,
    kRiskEventEmulator,
    kRiskEventInject,
    kRiskEventDebug,
    kRiskEventHttpProxy,
    kRiskEventRiskFrame,
    kRiskEventRiskEvent
} BCERiskEvent;

typedef enum {
    kRiskActionMessage, // just tip
    kRiskActionMessageThenQuit, // tip and close
    kRiskActionMessageWithoutClose, // tip and no close button
    kRiskActionQuitOrMessage, //
    kRiskActionQuit // close
} BCERiskAction;

typedef void (^BCERiskEventHandler)(NSDictionary * _Nullable data, BCERiskEvent riskType);

@interface BCEAlertContext : NSObject
@property (readonly) NSString* message;
@property (readonly) NSString* title;
@property (readonly) BCERiskAction action;
@end

@interface RiskStub : NSObject

+ (void)initAppsecEverisk:(NSString *_Nonnull)key;


+ (NSInteger)initAppsecEveriskWithKey:(NSString *_Nonnull)key;


+ (NSInteger)initAppsecEveriskWithKey:(NSString *_Nonnull)key withDataCallback:(BCECallBack _Nullable)listener;

+ (void)registerServiceWithDataBlock:(BCECallBack _Nullable )listener;


+ (void)appEnterBackground;


+ (void)appEnterForeground;


+ (BOOL)addExtraUserData:(NSString *_Nonnull)key withUserDatavalue:(NSString *_Nonnull)value;


//+ (BOOL)addExtraUserData:(NSDictionary *_Nonnull)jsonData;

/// @param value userid
//+ (BOOL)addExtraUserID:(NSString *_Nonnull)value;


/// @param jsonData
/// @return
//+ (BOOL)addExtraUserIDWithDictionary:(NSDictionary *_Nonnull)jsonData;


+ (NSString *)getEveriskVersion;


+ (NSString *)getEveriskSdkVersion;


+ (void)enableAppsecLog;


+ (NSString *_Nullable)getEveriskUdid;


+ (NSDictionary *_Nullable)getEveriskToken;


+ (void)addUrl:(NSArray * _Nonnull )downloadUrls withBusinessUrl:(NSArray*_Nonnull)businessUrls;


/// @param enabled YES open，NO close，default YES
+ (void)setScreenSharingCheckerEnabled:(BOOL)enabled;

+ (void)setEventResponseEnable:(BOOL)enabled;

+ (void) handleEvent:(NSDictionary*)command;

+ (void)setUserID:(NSString*)userId;


+ (void)registerAlertActionHandler:(void (^)(BCEAlertContext * context))handler;

@property (readwrite, nonatomic, copy) BCERiskURLSessionDidReceiveAuthenticationChallengeBlock _Nullable sessionDidReceiveAuthenticationChallenge;





////offline feature


+ (void)initOfflineAppsecEveriskFromBundle;


+ (void)initOfflineAppsecEveriskFromBundleWithDataCallback:(BCERiskEventHandler)handler;


+ (void)registerOfflineEventHandler:(BCERiskEventHandler)handler;

+ (void)addFilterStrings:(NSArray*)strings;


+ (NSDictionary *_Nullable)getEnvInfo;

////inner usage
+ (RiskStub *_Nullable)sharedManager;
@end

NS_ASSUME_NONNULL_END
