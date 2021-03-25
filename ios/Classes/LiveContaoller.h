//
//  LiveContaoller.h
//  live_plugin
//
//  Created by wenwenjun on 2021/3/23.
//

#import <Foundation/Foundation.h>
#import <Flutter/Flutter.h>
#import "GPUImage/Headers/GPUImageOutput.h"
#import "GPUImage/Headers/GPUImageVideoCamera.h"
#import "GPUImage/Headers/GPUImageMovieWriterEx.h"
#import "RtmpLivePushSDK/VideoCore/api/iOS/VCRtmpSession.h"
#import "Filters.h"
@interface LiveContaoller : NSObject<FlutterTexture,GPUImageInput,PixelBufferDelegate>
//最新帧可用回调
@property(nonatomic, copy) void (^onFrameAvailable)(void);
//最新一帧数据
@property(readonly) CVPixelBufferRef volatile latestPixelBuffer;
//播放控制器
@property (atomic, strong) GPUImageVideoCamera *videoCamera;
//滤镜
@property (atomic, strong) GPUImageOutput<GPUImageInput> *filter;
//编码后的输出代理
@property (nonatomic, strong) GPUImageMovieWriterEx *movieWriter;
//推流seesion
@property (nonatomic, strong) VCRtmpSession* rtmpSession;
- (int64_t)getTextureId;
- (void)startRecord;
- (void)stopRecord;
- (void)swapCamera;
- (void)setHardVideoFilterByName:(NSString *)type;
@end


