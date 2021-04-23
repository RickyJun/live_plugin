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
#import "Constants.h"

@interface LiveContaoller : NSObject<FlutterTexture,GPUImageInput,PixelBufferDelegate>
@property(readonly) RecordStatus recordStatus;
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


@property(assign, nonatomic) int64_t textureId;
@property(nonatomic, strong) void(^onError)(NSString *errorType,NSString *dec);
- (instancetype)initWithOption:(CGSize)videoSize fps:(CGFloat)fps bitrate:(CGFloat)bitrate rmptUrl:(NSString*)rmptUrl;

- (NSInteger)recordStatus;
//设置/切换滤镜
- (void)setHardVideoFilterByName:(NSString *)type;
//暂停
- (void)pauseRecord;
//恢复
- (void)resumeRecord;
//终止录像
- (NSString*)stopRecord;
//切换摄像头
- (void)swapCamera;
//摄像头焦距 [0.0f,1.0f]
- (void)setZoomByPercent:(CGFloat)targetPercent;
//摄像头开关闪光灯
- (void)toggleFlashLight;
// 推流过程中，重新设置帧率
- (void)reSetVideoFPS:(int32_t)fps;
//推流过程中，重新设置码率
- (void)reSetVideoBitrate:(NSString*)type;
//截图
- (void)takeScreenShot:(FlutterResult)result;
//镜像
- (void)setMirror:(BOOL)isEnableMirror;

@end


