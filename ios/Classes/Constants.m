//
//  Filters.m
//  live_plugin
//
//  Created by wenwenjun on 2021/3/24.
//

#import "Filters.h"
#import "GPUImage/Headers/GPUImageOutput.h"
#import "GPUImage/Headers/GPUImageBeautifyFilter.h"
@interface Filters()
@end
@implementation Filters
+ (GPUImageOutput<GPUImageInput> *)getFilterByType:(NSString *)type{
    GPUImageOutput<GPUImageInput> *defaultFilter = [[GPUImageBeautifyFilter alloc] init];
    if([type isEqualToString:@"GPUImageBeautyFilter"]){
        return defaultFilter;
    }else{
        return defaultFilter;
    }
}

@end

@interface Bitrates()
@end
@implementation Bitrates
+ (AVCaptureSessionPreset)getBitrateByType:(NSString *)type{
    if([type isEqualToString:@"352x288"]){
        return AVCaptureSessionPreset352x288;
    }else{
        return AVCaptureSessionPreset960x540;
    }
}

@end