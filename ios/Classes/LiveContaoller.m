//
//  LiveContaoller.m
//  live_plugin
//
//  Created by wenwenjun on 2021/3/23.
//

#import "LiveContaoller.h"
#import <libkern/OSAtomic.h>
@implementation LiveContaoller

- (CVPixelBufferRef _Nullable)copyPixelBuffer {
    
}

- (BOOL)enabled {
    return true;
}

- (void)endProcessing {
    
}

- (CGSize)maximumOutputSize {
    return CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX);
}

- (void)newFrameReadyAtTime:(CMTime)frameTime atIndex:(NSInteger)textureIndex {
    
}

- (NSInteger)nextAvailableTextureIndex {
    
}

- (void)setCurrentlyReceivingMonochromeInput:(BOOL)newValue {
    
}

- (void)setInputFramebuffer:(GPUImageFramebuffer *)newInputFramebuffer atIndex:(NSInteger)textureIndex {
    
    CVPixelBufferRef newBuffer = newInputFramebuffer.pixelBuffer;
    CFRetain(newBuffer);
    CVPixelBufferRef old = _latestPixelBuffer;
    while (!OSAtomicCompareAndSwapPtrBarrier(old, newBuffer, (void **)&_latestPixelBuffer)) {
        old = _latestPixelBuffer;
    }
    if (old != nil) {
        CFRelease(old);
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
