#import <Flutter/Flutter.h>

@interface LivePlugin : NSObject<FlutterPlugin>
@property(assign,nonatomic) NSObject<FlutterTextureRegistry> *registrarTextures;
@end
