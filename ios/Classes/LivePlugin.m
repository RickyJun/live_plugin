#import "LivePlugin.h"
//#if __has_include(<live_plugin/live_plugin-Swift.h>)
//#import <live_plugin/live_plugin-Swift.h>
//#else
//// Support project import fallback if the generated compatibility header
//// is not copied when this plugin is created as a library.
//// https://forums.swift.org/t/swift-static-libraries-dont-copy-generated-objective-c-header/19816
//#import "live_plugin-Swift.h"
//#endif
@implementation LivePlugin
FlutterMethodChannel *channel;
LivePlugin *instance;
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
    instance = [[LivePlugin alloc] init];
    channel = [FlutterMethodChannel methodChannelWithName:@"live_plugin" binaryMessenger:[registrar messenger]];
    [registrar addMethodCallDelegate:instance channel:channel];
    //[SwiftLivePlugin registerWithRegistrar:registrar];
}

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
    if([call.method isEqualToString:@"init"]){
        
    }else{
        
    }
}
@end
