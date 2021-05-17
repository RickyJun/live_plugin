//
//  GPUImageViewFlutterTexture.h
//  live_plugin
//
//  Created by wenwenjun on 2021/5/17.
//

#import <UIKit/UIKit.h>
#import <Flutter/Flutter.h>
#import <GPUImageOutput.h>
#import "GPUImageContext.h"
#import "GPUImageView.h"
@interface GPUImageViewFlutterTexture : UIView<GPUImageInput>
{
    GPUImageRotationMode inputRotation;
}

@property(assign, nonatomic) int64_t textureId;
/** The fill mode dictates how images are fit in the view, with the default being kGPUImageFillModePreserveAspectRatio
 */
@property(readwrite, nonatomic) GPUImageFillModeType fillMode;

/** This calculates the current display size, in pixels, taking into account Retina scaling factors
 */
@property(readonly, nonatomic) CGSize sizeInPixels;


@property BOOL enabled;

/** Handling fill mode
 
 @param redComponent Red component for background color
 @param greenComponent Green component for background color
 @param blueComponent Blue component for background color
 @param alphaComponent Alpha component for background color
 */
- (id)initWithFrame:(CGRect)frame registry:(NSObject<FlutterTextureRegistry>*)registry texture:(NSObject<FlutterTexture>*)texture;
- (void)setBackgroundColorRed:(GLfloat)redComponent green:(GLfloat)greenComponent blue:(GLfloat)blueComponent alpha:(GLfloat)alphaComponent;

- (void)setCurrentlyReceivingMonochromeInput:(BOOL)newValue;
@end
