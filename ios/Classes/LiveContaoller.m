//
//  LiveContaoller.m
//  live_plugin
//
//  Created by wenwenjun on 2021/3/23.
//

#import "LiveContaoller.h"
#import <libkern/OSAtomic.h>

@interface LiveContaoller()
@property(assign, nonatomic) int64_t textureId;
@end

@implementation LiveContaoller

- (instancetype)init
{
    self = [super init];
    if (self) {
        //初始化session
        self.rtmpSession = [[VCRtmpSession alloc] initWithVideoSize:VIDEO_SIZE_CIF fps:25 bitrate:BITRATE_CIF];
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
        NSString *pathToMovie = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/Movie.m4v"];
        unlink([pathToMovie UTF8String]); // If a file already exists, AVAssetWriter won't let you record new frames, so delete the old movie
        NSURL *movieURL = [NSURL fileURLWithPath:pathToMovie];
        self.movieWriter = [[GPUImageMovieWriterEx alloc] initWithMovieURL:movieURL size:CGSizeMake(360.0, 640.0)];
        self.movieWriter.encodingLiveVideo = YES;
        self.movieWriter.pixelBufferdelegate = self;
        [self.videoCamera addTarget:self.movieWriter];
        [self.videoCamera addTarget:self];
    }
    return self;
}
#pragma mark--视频控制
- (int64_t)getTextureId{
    return _textureId;
}
- (void)startRecord{
    [self.rtmpSession startRtmpSession:@"rtmp://192.168.1.104/live/123456"];
    
    [self.videoCamera startCameraCapture];
    
    [self.movieWriter startRecording];
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
    _filter = [Filters getFilterByEnum:type];
    if(_filter != nil){
        [_filter addTarget:self];
        [_videoCamera addTarget:_filter];
    }
}
- (void)stopRecord{
    [self.rtmpSession endRtmpSession];
    [self.videoCamera stopCameraCapture];
    [self.movieWriter cancelRecording];
    [self.videoCamera removeTarget:self];
    [self.videoCamera removeTarget:self.movieWriter];
}
- (void)swapCamera{
    [self.videoCamera rotateCamera];
}
- (void)setZoomByPercent{
    
}
- (void)dealloc
{
    if(_latestPixelBuffer != nil){
        CFRelease(_latestPixelBuffer);
    }
}
#pragma mark--视频数据处理回调
-(void)PixelBufferCallback:(CVPixelBufferRef)pixelFrameBuffer{
//    unsigned long ulLen = CVPixelBufferGetDataSize(pixelFrameBuffer);
//    unsigned long iWidth = CVPixelBufferGetWidth(pixelFrameBuffer);
//    unsigned long iHeight = CVPixelBufferGetHeight(pixelFrameBuffer);
//    int iFormatType = CVPixelBufferGetPixelFormatType(pixelFrameBuffer);
//    NSLog(@"PixelBufferCallback: %lu X %lu, formattype=%d, ulLen=%lu", iWidth, iHeight, iFormatType, ulLen);
    
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
