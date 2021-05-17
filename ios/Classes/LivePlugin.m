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
    channel = [FlutterMethodChannel methodChannelWithName:@"live_rtmp" binaryMessenger:[registrar messenger]];
    [registrar addMethodCallDelegate:instance channel:channel];
    //[SwiftLivePlugin registerWithRegistrar:registrar];
}

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
    if([call.method isEqualToString:@"initLiveConfig"]){
        @try {
            NSDictionary *args = call.arguments;
            CGFloat videoWidth = [[args valueForKey:@"videoWidth"] floatValue];
            NSString *rtmpUrl = [args valueForKey:@"rmptUrl"];
            liveController = [[LiveContaoller alloc] initWithOption:CGSizeMake(videoWidth,[[args valueForKey:@"videoHeight"] floatValue]) fps:[[args valueForKey:@"fps"] floatValue] bitrate:[[args valueForKey:@"bitrate"] floatValue] rmptUrl:rtmpUrl registry:self->_registrarTextures];
            [liveController startRecord:result];
            liveController.onError = ^(NSString *errorType,NSString *dec){
                NSDictionary *errorMsg = [[NSDictionary alloc] init];
                [errorMsg setValue:@"errorType" forKey:errorType];
                [errorMsg setValue:@"dec" forKey:dec];
                [channel invokeMethod:@"error" arguments:errorMsg];
            };
            NSDictionary *res = [[NSMutableDictionary alloc] init];
            [res setValue:@(liveController.textureId) forKey:@"textureId"];
            result(res);
        } @catch (NSException *exception) {
            result(@"error!");
        }
    }else if([call.method isEqual:@"close"]){
        liveController = nil;
    }else{
        SEL method = NSSelectorFromString(call.method);
        if(method != nil && [liveController respondsToSelector:method]){
            if(call.arguments == nil){
                SuppressPerformSelectorLeakWarning([liveController performSelector:method withObject:result]);
            }else{
                SuppressPerformSelectorLeakWarning([liveController performSelector:method withObject:result withObject:call.arguments]);
            }
            
        }
    }
}
@end
