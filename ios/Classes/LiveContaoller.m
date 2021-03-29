//
//  LiveContaoller.m
//  live_plugin
//
//  Created by wenwenjun on 2021/3/23.
//

#import "LiveContaoller.h"
#import <libkern/OSAtomic.h>
typedef NS_ENUM(NSInteger,RecordStatus) {
    RecordStatusStop,
    RecordStatusRecording,
    RecordStatusPause
};
@interface LiveContaoller()
@property NSString *pathToMovie;
@property NSString *rmptUrl;

@end

@implementation LiveContaoller

#pragma mark--LiveContaoller 方法

- (instancetype)initWithOption:(CGSize)videoSize
fps:(CGFloat)fps
                       bitrate:(CGFloat)bitrate rmptUrl:(NSString*)rmptUrl
{
    self = [super init];
    if (self) {
        self.rmptUrl = rmptUrl;
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
        _pathToMovie = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/Movie.m4v"];
        unlink([_pathToMovie UTF8String]); // If a file already exists, AVAssetWriter won't let you record new frames, so delete the old movie
        NSURL *movieURL = [NSURL fileURLWithPath:_pathToMovie];
        self.movieWriter = [[GPUImageMovieWriterEx alloc] initWithMovieURL:movieURL size:CGSizeMake(360.0, 640.0)];
        self.movieWriter.encodingLiveVideo = YES;
        self.movieWriter.pixelBufferdelegate = self;
        [self.videoCamera addTarget:self.movieWriter];
        [self.videoCamera addTarget:self];
    }
    return self;
}
- (void)dealloc
{
    if(_latestPixelBuffer != nil){
        CFRelease(_latestPixelBuffer);
    }
}
#pragma mark--视频基础控制
- (int)startRecord{
    @try {
        //[self.rtmpSession startRtmpSession:@"rtmp://192.168.1.104/live/123456"];
        [self.rtmpSession startRtmpSession:self.rmptUrl];
        [self.videoCamera startCameraCapture];
        [self.movieWriter startRecording];
        _recordStatus = RecordStatusRecording;
        return 0;
    } @catch (NSException *exception) {
        _onError(exception.name,exception.reason);
        return -1;
    }
}

//设置/切换滤镜
- (void)setHardVideoFilterByName:(NSString *)type{
    if(type == nil){
        return;
    }
    if([[_videoCamera targets] containsObject:self]){
        [_videoCamera removeTarget:self];
    }
    if(_filter != nil){
        [_filter removeAllTargets];
        [_videoCamera removeTarget:_filter];
    }
    _filter = [Filters getFilterByType:type];
    if(_filter != nil){
        [_filter addTarget:self];
        [_videoCamera addTarget:_filter];
    }
}
- (NSString*)stopRecord{
    [self.rtmpSession endRtmpSession];
    [self.videoCamera stopCameraCapture];
    [self.movieWriter cancelRecording];
    [self.videoCamera removeTarget:self];
    [self.videoCamera removeTarget:self.movieWriter];
    _recordStatus = RecordStatusStop;
    return _pathToMovie;
}
- (void)swapCamera{
    [self.videoCamera rotateCamera];
}
- (void)pauseRecord{
    [self.videoCamera pauseCameraCapture];
    _recordStatus = RecordStatusPause;
}
- (void)resumeRecord{
    [self.videoCamera resumeCameraCapture];
    _recordStatus = RecordStatusRecording;
}
#pragma mark--视频其他控制
//摄像头焦距 [0.0f,1.0f]
- (void)setZoomByPercent:(CGFloat)targetPercent{
    [self.videoCamera.inputCamera setVideoZoomFactor:targetPercent];
}
//摄像头开关闪光灯
- (void)toggleFlashLight{
    AVCaptureFlashMode mode = self.videoCamera.inputCamera.flashMode == AVCaptureFlashModeOn?AVCaptureFlashModeOff:AVCaptureFlashModeOn;
    [self.videoCamera.inputCamera setFlashMode:mode];
}
// 推流过程中，重新设置帧率
- (void)reSetVideoFPS:(int32_t)fps{
    [self.videoCamera setFrameRate:fps];
}
//推流过程中，重新设置码率
- (void)reSetVideoBitrate:(NSString*)type{
    [self.videoCamera.captureSession setSessionPreset:[Bitrates getBitrateByType:type]];
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
- (void)setMirror:(BOOL)isEnableMirror{
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
    if(self.rtmpSession){
        [self.rtmpSession PutBuffer:pixelFrameBuffer];
    }
}
#pragma mark--FlutterTexture 方法
- (CVPixelBufferRef _Nullable)copyPixelBuffer {
    CVPixelBufferRef pixelBufferRef = _latestPixelBuffer;
    //并发处理，线程安全
    while (!OSAtomicCompareAndSwapPtrBarrier(pixelBufferRef, nil, (void**)&_latestPixelBuffer)) {
        pixelBufferRef = _latestPixelBuffer;
    }
    return pixelBufferRef;
}
#pragma mark--GPUImageInput 方法
- (BOOL)enabled {
    return true;
}

- (void)endProcessing {
    
}

- (CGSize)maximumOutputSize {
    return [UIScreen mainScreen].bounds.size;
}

- (void)newFrameReadyAtTime:(CMTime)frameTime atIndex:(NSInteger)textureIndex {
    
}

- (NSInteger)nextAvailableTextureIndex {
    return 1;
}

- (void)setCurrentlyReceivingMonochromeInput:(BOOL)newValue {
    
}

- (void)setInputFramebuffer:(GPUImageFramebuffer *)newInputFramebuffer atIndex:(NSInteger)textureIndex {
    CVPixelBufferRef newBuffer = newInputFramebuffer.pixelBuffer;
    CVPixelBufferRef old = _latestPixelBuffer;
    while (!OSAtomicCompareAndSwapPtrBarrier(old, newBuffer, (void **)&_latestPixelBuffer)) {
        old = _latestPixelBuffer;
    }
    if (old != nil) {
        CFRelease(old);
    }
    if(newBuffer != nil){
        CFRelease(newBuffer);
    }
    if (_onFrameAvailable) {
        _onFrameAvailable();
    }
}

- (void)setInputRotation:(GPUImageRotationMode)newInputRotation atIndex:(NSInteger)textureIndex {
    
}

- (void)setInputSize:(CGSize)newSize atIndex:(NSInteger)textureIndex {
    
}

- (BOOL)shouldIgnoreUpdatesToThisTarget {
    return false;
}

- (BOOL)wantsMonochromeInput {
    return false;
}

@end
