//
//  LiveContaoller.h
//  live_plugin
//
//  Created by wenwenjun on 2021/3/23.
//

#import <Foundation/Foundation.h>
#import <Flutter/Flutter.h>
#import "GPUImage/Headers/GPUImageOutput.h"

@interface LiveContaoller : NSObject<FlutterTexture,GPUImageInput>
@property(nonatomic, copy) void (^onFrameAvailable)();
@property(readonly) CVPixelBufferRef volatile latestPixelBuffer;
@end


