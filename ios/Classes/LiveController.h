//
//  LiveContaoller.h
//  live_plugin
//
//  Created by wenwenjun on 2021/3/23.
//

#import <Foundation/Foundation.h>
#import <Flutter/Flutter.h>
#import "GPUImageVideoCamera.h"
#import <GPUImageMovieWriterEx.h>
#import <videocore/api/iOS/VCRtmpSession.h>
#import "Constants.h"

typedef NS_ENUM(NSInteger,RecordStatus) {
    RecordStatusStop,
    RecordStatusRecording,
    RecordStatusPause
};
@interface LiveController : NSObject<FlutterTexture,PixelBufferDelegate>

//最新一帧数据
@property (nonatomic) CVPixelBufferRef volatile latestPixelBuffer;

@property(readonly) RecordStatus recordStatus;

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
- (instancetype)initWithOption:(CGSize)videoSize fps:(CGFloat)fps bitrate:(CGFloat)bitrate rmptUrl:(NSString*)rmptUrl registry:(NSObject<FlutterTextureRegistry>*)registry;

- (void)startRecord:(FlutterResult)result;
- (void)recordStatus:(FlutterResult)result;
//设置/切换滤镜
- (void)setHardVideoFilterByName:(FlutterResult)result :(NSString *)type;
//暂停
- (void)pauseRecord:(FlutterResult)result;
//恢复
- (void)resumeRecord:(FlutterResult)result;
//终止录像
- (NSString*)stopRecord:(FlutterResult)result;
//切换摄像头
- (void)swapCamera:(FlutterResult)result;
//摄像头焦距 [0.0f,1.0f]
- (void)setZoomByPercent:(FlutterResult)result :(NSNumber*)targetPercent;
//摄像头开关闪光灯
- (void)toggleFlashLight:(FlutterResult)result;
// 推流过程中，重新设置帧率
- (void)reSetVideoFPS:(FlutterResult)result :(NSNumber*)fps;
//推流过程中，重新设置码率
- (void)reSetVideoBitrate:(FlutterResult)result :(NSString*)type;
//截图
- (void)takeScreenShot:(FlutterResult)result;
//镜像
- (void)setMirror:(FlutterResult)result :(NSNumber*)isEnableMirror;

- (void)setLatestPixelBuffer:(CVPixelBufferRef)latestPixelBuffer;
@end


