//
//  LiveContaoller.m
//  live_plugin
//
//  Created by wenwenjun on 2021/3/23.
//

#import "LiveContaoller.h"
#import <libkern/OSAtomic.h>
#import "GPUImageViewFlutterTexture.h"
@interface FLTFrameUpdater : NSObject
@property(nonatomic) int64_t textureId;
@property(nonatomic, weak, readonly) NSObject<FlutterTextureRegistry>* registry;
- (void)onDisplayLink:(CADisplayLink*)link;
@end

@implementation FLTFrameUpdater
- (FLTFrameUpdater*)initWithRegistry:(NSObject<FlutterTextureRegistry>*)registry {
  NSAssert(self, @"super init cannot be nil");
  if (self == nil) return nil;
  _registry = registry;
  return self;
}

- (void)onDisplayLink:(CADisplayLink*)link {
  [_registry textureFrameAvailable:_textureId];
}
@end
@interface LiveContaoller()
@property NSString *pathToMovie;
@property NSString *rmptUrl;
@property CVPixelBufferRef pixelBuffer;
@property NSObject<FlutterTextureRegistry>* registry;
@property (nonatomic, strong) GPUImageViewFlutterTexture *filterView;
@property FLTFrameUpdater* frameUpdater;
- (void)getErrorMsg:(NSException*)e method:(NSString*)method;
@end

@implementation LiveContaoller
#pragma mark--LiveContaoller 方法
- (void)getErrorMsg:(NSException*)e method:(NSString*)method{
    _onError([NSString  stringWithFormat:@"%@ err %@",method,e.name],[NSString stringWithFormat:@"msg:%@ cause:%@",e.reason,e.userInfo]);
}
- (instancetype)initWithOption:(CGSize)videoSize
fps:(CGFloat)fps
                       bitrate:(CGFloat)bitrate rmptUrl:(NSString*)rmptUrl  registry:(NSObject<FlutterTextureRegistry>*)registry
{
    self = [super init];
    if (self) {
        @try {
            _registry = registry;
            _textureId = [_registry registerTexture:self];
            _frameUpdater = [[FLTFrameUpdater alloc] initWithRegistry:_registry];
            _frameUpdater.textureId = _textureId;
            
            self.filterView = [[GPUImageViewFlutterTexture alloc] initWithFrame:CGRectMake(0, 0, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height) texture:self];
            self.filterView.backgroundColor = [UIColor lightGrayColor];
            self.rmptUrl = rmptUrl;
            NSString *fileName = [rmptUrl substringFromIndex:[rmptUrl rangeOfString:@"/" options:NSBackwardsSearch].location+1];
            //初始化session
            self.rtmpSession = [[VCRtmpSession alloc] initWithVideoSize:videoSize fps:fps bitrate:bitrate];
            [[GPUImageContext sharedFramebufferCache] purgeAllUnassignedFramebuffers];
            //初始化播放器
            self.videoCamera = [[GPUImageVideoCamera alloc] initWithSessionPreset:AVCaptureSessionPreset1280x720 cameraPosition:AVCaptureDevicePositionFront];
            self.videoCamera.outputImageOrientation = UIInterfaceOrientationPortrait;
            self.videoCamera.horizontallyMirrorFrontFacingCamera = NO;
            self.videoCamera.horizontallyMirrorRearFacingCamera = NO;
            //设置预览的屏幕尺寸
            AVCaptureSession* session = self.videoCamera.captureSession;
            AVCaptureVideoPreviewLayer* previewLayer;
            previewLayer = [AVCaptureVideoPreviewLayer layerWithSession:session];
            previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
            previewLayer.frame = [UIScreen mainScreen].bounds;
            //初始化编码器
            NSString *path = [NSString stringWithFormat:@"Documents/Movie%@%d.m4v",fileName,6];
            _pathToMovie = [NSHomeDirectory() stringByAppendingPathComponent:path];
            //_pathToMovie = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/Movie.m4v"];
            unlink([_pathToMovie UTF8String]); // If a file already exists, AVAssetWriter won't let you record new frames, so delete the old movie
            NSURL *movieURL = [NSURL fileURLWithPath:_pathToMovie];
            //self.movieWriter = [[GPUImageMovieWriterEx alloc] initWithMovieURL:movieURL size:CGSizeMake(360.0, 640.0)];
            self.movieWriter = [[GPUImageMovieWriterEx alloc] initWithMovieURL:movieURL size:videoSize];
            self.movieWriter.encodingLiveVideo = YES;
            self.movieWriter.pixelBufferdelegate = self;
            [self.videoCamera addTarget:self.movieWriter];
            [self.videoCamera addTarget:self.filterView];
        } @catch (NSException *exception) {
            [self getErrorMsg:exception method:@"initWithOption"];
        } @finally {
            
        }
        
    }
    return self;
}
- (void)dealloc
{
    
}
#pragma mark--视频基础控制
- (void)startRecord:(FlutterResult)result{
    //初始化_displayLink
    _textureId = self.filterView.textureId;
    //开始录制
    @try {
        [self.rtmpSession startRtmpSession:self.rmptUrl];
        [self.videoCamera startCameraCapture];
        [self.movieWriter startRecording];
        _recordStatus = RecordStatusRecording;
    } @catch (NSException *exception) {
        NSLog(@"%@", exception.reason);
    } @finally {
        
    }
    
}
- (void)recordStatus:(FlutterResult)result{
    
}

//设置/切换滤镜
- (void)setHardVideoFilterByName:(FlutterResult)result type:(NSString *)type{
    if(type == nil){
        return;
    }
    @try {
        if([[_videoCamera targets] containsObject:self.filterView]){
            [_videoCamera removeTarget:self.filterView];
        }
        if(_filter != nil){
            [_filter removeAllTargets];
            [_videoCamera removeTarget:_filter];
        }
        _filter = [Filters getFilterByType:type];
        if(_filter != nil){
            [_filter addTarget:self.filterView];
            [_videoCamera addTarget:_filter];
        }
    } @catch (NSException *exception) {
        [self getErrorMsg:exception method:@"setHardVideoFilterByName"];
    } @finally {
        
    }
    
}
- (NSString*)stopRecord:(FlutterResult)result{
    @try {
        [self.rtmpSession endRtmpSession];
        [self.videoCamera stopCameraCapture];
        [self.movieWriter cancelRecording];
        [self.videoCamera removeTarget:self.filterView];
        [self.videoCamera removeTarget:self.movieWriter];
        _recordStatus = RecordStatusStop;
        return _pathToMovie;
    } @catch (NSException *exception) {
        [self getErrorMsg:exception method:@"stopRecord"];
        return nil;
    } @finally {
        
    }
    
}
- (void)swapCamera:(FlutterResult)result{
    [self.videoCamera rotateCamera];
}
- (void)pauseRecord:(FlutterResult)result{
    [self.videoCamera pauseCameraCapture];
    _recordStatus = RecordStatusPause;

}
- (void)resumeRecord:(FlutterResult)result{
    [self.videoCamera resumeCameraCapture];
    _recordStatus = RecordStatusRecording;
}
#pragma mark--视频其他控制
//摄像头焦距 [0.0f,1.0f]
- (void)setZoomByPercent:(FlutterResult)result targetPercent:(CGFloat)targetPercent{
    [self.videoCamera.inputCamera setVideoZoomFactor:targetPercent];
}
//摄像头开关闪光灯
- (void)toggleFlashLight:(FlutterResult)result {
    AVCaptureFlashMode mode = self.videoCamera.inputCamera.flashMode == AVCaptureFlashModeOn?AVCaptureFlashModeOff:AVCaptureFlashModeOn;
    [self.videoCamera.inputCamera setFlashMode:mode];
}
// 推流过程中，重新设置帧率
- (void)reSetVideoFPS:(FlutterResult)result fps:(int32_t)fps{
    [self.videoCamera setFrameRate:fps];
}
//推流过程中，重新设置码率
- (void)reSetVideoBitrate:(FlutterResult)result  type:(NSString*)type{
    [self.videoCamera.captureSession setSessionPreset:[Bitrates getBitrateByType:type]];
}
#pragma mark--帧输出
- (void)setLatestPixelBuffer:(CVPixelBufferRef)latestPixelBuffer{
    @try {
        if(latestPixelBuffer == nil){
            return;
        }
        CVPixelBufferRef old = _latestPixelBuffer;
        while (!OSAtomicCompareAndSwapPtrBarrier(old, latestPixelBuffer, (void**)&_latestPixelBuffer)) {
            old = _latestPixelBuffer;
        }
        [_frameUpdater onDisplayLink:nil];
    } @catch (NSException *exception) {
        NSLog(@"setLatestPixelBuffer error =====%@",exception.reason);
    }
}
//截图
- (void)takeScreenShot:(FlutterResult)result{
    
    //取_latestPixelBuffer转UIimage
    //保存Image到本地
    //返回path
}
/**
    * 镜像
    * @param isEnableMirror   是否启用镜像功能 总开关
    *  isEnablePreviewMirror  是否开启预览镜像
    * isEnableStreamMirror   是否开启推流镜像
*/
- (void)setMirror:(FlutterResult)result isEnableMirror:(BOOL)isEnableMirror{
    if([self.videoCamera isFrontFacingCameraPresent]){
        [self.videoCamera setHorizontallyMirrorFrontFacingCamera:isEnableMirror];
        
    }else{
        [self.videoCamera setHorizontallyMirrorRearFacingCamera:isEnableMirror];
    }
}
#pragma mark--视频数据处理回调（PixelBufferDelegate）
-(void)PixelBufferCallback:(CVPixelBufferRef)pixelFrameBuffer{
//    unsigned long ulLen = CVPixelBufferGetDataSize(pixelFrameBuffer);
//    unsigned long iWidth = CVPixelBufferGetWidth(pixelFrameBuffer);
//    unsigned long iHeight = CVPixelBufferGetHeight(pixelFrameBuffer);
//    int iFormatType = CVPixelBufferGetPixelFormatType(pixelFrameBuffer);
//    NSLog(@"PixelBufferCallback: %lu X %lu, formattype=%d, ulLen=%lu", iWidth, iHeight, iFormatType, ulLen);
    //推送到服务端
    @try {
        if(self.rtmpSession){
            [self.rtmpSession PutBuffer:pixelFrameBuffer];
        }
    } @catch (NSException *exception) {
        NSLog(@"PixelBufferCallback=======%@",exception.reason);
    } @finally {
        
    }
}
#pragma mark--FlutterTexture 方法
- (CVPixelBufferRef _Nullable)copyPixelBuffer {
    return _latestPixelBuffer;
}

@end
