import 'dart:async';

import 'package:flutter/services.dart';

class LivePlugin {
  static const MethodChannel _channel =
      const MethodChannel('plugins.flutter.io/live_rtmp');

  static Future<String> get platformVersion async {
    final String version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }
}
