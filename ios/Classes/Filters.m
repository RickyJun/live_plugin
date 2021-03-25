//
//  Filters.m
//  live_plugin
//
//  Created by wenwenjun on 2021/3/24.
//

#import "Filters.h"
#import "GPUImage/Headers/GPUImageOutput.h"
#import "GPUImage/Headers/GPUImageBeautifyFilter.h"
@implementation Filters
+ (GPUImageOutput<GPUImageInput> *)getFilterByEnum:(NSString *)type{
    GPUImageOutput<GPUImageInput> *defaultFilter = [[GPUImageBeautifyFilter alloc] init];
    if([type isEqualToString:@"GPUImageBeautyFilter"]){
        return defaultFilter;
    }else{
        return defaultFilter;
    }
}

@end
