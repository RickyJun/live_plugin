//
//  Filters.h
//  live_plugin
//
//  Created by wenwenjun on 2021/3/24.
//

#import <Foundation/Foundation.h>



@interface Filters : NSObject
+ (GPUImageOutput<GPUImageInput>*)getFilterByType:(NSString *)type;
@end

@interface Bitrates : NSObject
+ (AVCaptureSessionPreset)getBitrateByType:(NSString *)type;
@end

