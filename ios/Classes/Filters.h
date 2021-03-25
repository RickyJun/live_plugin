//
//  Filters.h
//  live_plugin
//
//  Created by wenwenjun on 2021/3/24.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Filters : NSObject
+ (GPUImageOutput<GPUImageInput>*)getFilterByEnum:(NSString *)type;
@end

NS_ASSUME_NONNULL_END
