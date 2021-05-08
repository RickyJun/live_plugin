#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint live_plugin.podspec' to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'live_plugin'
  s.version          = '0.0.1'
  s.summary          = 'A new flutter plugin project.'
  s.description      = <<-DESC
A new flutter plugin project.
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }
  s.source_files = 'Classes/*','Classes/RtmpLivePushSDK/**/*.{hpp,h,inl}','Classes/GPUImage/**/*.{hpp,h,inl}'
  s.vendored_libraries = 'Classes/GPUImage/lib/*.a', 'Classes/RtmpLivePushSDK/lib/*.a', 'Classes/RtmpLivePushSDK/VideoCore/RtmpManager/lib/*.a'
  s.frameworks = 'VideoToolbox', 'OpenGLES', 'CoreVideo', 'CoreMedia', 'CoreGraphics', 'AVFoundation', 'AudioToolbox', 'CFNetwork', 'CoreGraphics', 'UIKit'
  s.libraries = 'stdc++', 'z', 'c++'
  s.public_header_files = 'Classes/*.h'
  s.user_target_xcconfig = {
     'HEADER_SEARCH_PATHS' => ['$(inherited)','${PODS_ROOT}/../.symlinks/plugins/live_plugin/ios/Classes/GPUImage/Headers','${PODS_ROOT}/../.symlinks/plugins/live_plugin/ios/Classes/RtmpLivePushSDK/boost','${PODS_ROOT}/../.symlinks/plugins/live_plugin/ios/Classes/RtmpLivePushSDK/glm','${PODS_ROOT}/../.symlinks/plugins/live_plugin/ios/Classes/RtmpLivePushSDK'],
     'USER_HEADER_SEARCH_PATHS' => ['$(inherited)','${PODS_ROOT}/../.symlinks/plugins/live_plugin/ios/Classes/RtmpLivePushSDK/boost']
  }
  s.dependency 'Flutter'
  s.platform = :ios, '9.0'
  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386', 'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES', 'HEADER_SEARCH_PATHS' => ['$(inherited)','${PODS_TARGET_SRCROOT}/Classes/GPUImage/Headers','${PODS_TARGET_SRCROOT}/Classes/RtmpLivePushSDK/boost','${PODS_TARGET_SRCROOT}/Classes/RtmpLivePushSDK/glm','${PODS_TARGET_SRCROOT}/Classes/RtmpLivePushSDK']}
  s.swift_version = '4.0'
end
