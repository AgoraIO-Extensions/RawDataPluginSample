#import "VideoRawDataPlugin.h"
#if __has_include(<video_raw_data/video_raw_data-Swift.h>)
#import <video_raw_data/video_raw_data-Swift.h>
#else
// Support project import fallback if the generated compatibility header
// is not copied when this plugin is created as a library.
// https://forums.swift.org/t/swift-static-libraries-dont-copy-generated-objective-c-header/19816
#import "video_raw_data-Swift.h"
#endif

@implementation VideoRawDataPlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  [SwiftVideoRawDataPlugin registerWithRegistrar:registrar];
}
@end
