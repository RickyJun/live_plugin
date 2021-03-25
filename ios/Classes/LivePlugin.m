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
        liveController = [[LiveContaoller alloc] init];
        liveController.textureId = [_registrarTextures registerTexture:liveController];
        liveController.onFrameAvailable = ^{
            [self->_registrarTextures textureFrameAvailable:liveController.textureId];
        };
    }else if([call.method isEqualToString:@"setHardVideoFilter"]){
        //设置视频滤镜
        
    }else{
        SEL method = NSSelectorFromString(call.method);
        if(method != nil && [liveController respondsToSelector:method]){
            SuppressPerformSelectorLeakWarning([liveController performSelector:method]);
        }
    }
}
@end
