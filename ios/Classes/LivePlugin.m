#import "LivePlugin.h"
#import "LiveContaoller.h"
//#if __has_include(<live_plugin/live_plugin-Swift.h>)
//#import <live_plugin/live_plugin-Swift.h>
//#else
//// Support project import fallback if the generated compatibility header
//// is not copied when this plugin is created as a library.
//// https://forums.swift.org/t/swift-static-libraries-dont-copy-generated-objective-c-header/19816
//#import "live_plugin-Swift.h"
//#endif
#define SuppressPerformSelectorLeakWarning(Stuff) \
    do { \
        _Pragma("clang diagnostic push") \
        _Pragma("clang diagnostic ignored \"-Warc-performSelector-leaks\"") \
        Stuff; \
        _Pragma("clang diagnostic pop") \
    } while (0)
@implementation LivePlugin
FlutterMethodChannel *channel;
LivePlugin *instance;
LiveContaoller *liveController;

+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
    instance = [[LivePlugin alloc] init];
    instance.registrarTextures = registrar.textures;
    channel = [FlutterMethodChannel methodChannelWithName:@"live_plugin" binaryMessenger:[registrar messenger]];
    [registrar addMethodCallDelegate:instance channel:channel];
    //[SwiftLivePlugin registerWithRegistrar:registrar];
}

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
    if([call.method isEqualToString:@"initLiveConfig"]){
        NSDictionary *args = call.arguments;
        liveController = [[LiveContaoller alloc] initWithOption: CGSizeMake([[args objectForKey:@"videoWidth"] floatValue] ,[[args objectForKey:@"videoHeight"] floatValue]) fps:[[args objectForKey:@"fps"] floatValue]  bitrate:[[args objectForKey:@"bitrate"] floatValue]];
        liveController.textureId = [_registrarTextures registerTexture:liveController];
        liveController.onFrameAvailable = ^{
            [self->_registrarTextures textureFrameAvailable:liveController.textureId];
        };
        liveController.onError = ^(NSString *errorType,NSString *dec){
            NSDictionary *errorMsg = [[NSDictionary alloc] init];
            [errorMsg setValue:@"errorType" forKey:errorType];
            [errorMsg setValue:@"dec" forKey:dec];
            [channel invokeMethod:@"error" arguments:errorMsg];
        };
        if(liveController.textureId){
            NSDictionary *res = [[NSDictionary alloc] init];
            [res setValue:@(liveController.textureId) forKey:@"textureId"];
            result(res);
        }
    }else if([call.method isEqual:@"takeScreenShot"]){
        [liveController takeScreenShot:result];
    }else if([call.method isEqual:@"close"]){
        liveController = nil;
    }else{
        SEL method = NSSelectorFromString(call.method);
        if(method != nil && [liveController respondsToSelector:method]){
            SuppressPerformSelectorLeakWarning([liveController performSelector:method withObject:call.arguments]);
        }
    }
}
@end
