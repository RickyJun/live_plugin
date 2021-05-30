//
//  Filters.m
//  live_plugin
//
//  Created by wenwenjun on 2021/3/24.
//
#import "Constants.h"

@interface Filters()
@end
@implementation Filters




+ (GPUImageOutput<GPUImageInput> *)getFilterByType:(NSString *)type{
    GPUImageBeautifyFilter *defaultFilter = [[GPUImageBeautifyFilter alloc] init];
    if([type isEqualToString:@"GPUImageBeautyFilter"]){
        GPUImageBrightnessFilter *brightnessFilter = [[GPUImageBrightnessFilter alloc] init];
        brightnessFilter.brightness = 0;
        [defaultFilter addFilter:brightnessFilter];
        return defaultFilter;
    }else{
        return defaultFilter;
    }
}

@end

@interface Bitrates()
@end
@implementation Bitrates
+ (int)getBitrateByType:(NSString *)type{
    if([type isEqualToString:@"960x540"]){
        return 960*540;
    }else if([type isEqualToString:@"352x288"]){
        return 352*288;
    }else{
        return 600*1000;
    }
}

@end
