//
//  Filters.h
//  live_plugin
//
//  Created by wenwenjun on 2021/3/24.
//

#import <Foundation/Foundation.h>
#import <GPUImageOutput.h>
#import <GPUImageBeautifyFilter.h>
@interface Filters : NSObject
+ (GPUImageOutput<GPUImageInput>*)getFilterByType:(NSString *)type;
@end

@interface Bitrates : NSObject
+ (int)getBitrateByType:(NSString *)type;
@end

