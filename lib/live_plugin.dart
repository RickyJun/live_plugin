import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

import 'live_controller.dart';

class LivePlugin {
  static const MethodChannel _channel = const MethodChannel('live_rtmp');
  static LiveController _liveController;
  static Future<String> get platformVersion async {
    final String version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }

  //初始化，rmptServer，rmptUrl传其中一个
  static Future<LiveController> init(
      {String rmptServer,
      String rmptUrl,
      int fps,
      int bitrate,
      int videoWidth,
      int videoHeight}) async {
    _liveController = LiveController(_channel,
        rmptServer: rmptServer,
        fps: fps,
        bitrate: bitrate,
        videoWidth: videoWidth,
        videoHeight: videoHeight);
    await _liveController.initLiveConfig();
    return _liveController;
  }

  static void setHandler({Function(Map msg) handler}) {
    _channel.setMethodCallHandler((call) {
      switch (call.method) {
        case "error":
          {
            handler(call.arguments);
            print(call.arguments.toString());
            break;
          }
        default:
          print("method:${call.method} ==== args:${call.arguments.toString()}");
      }
      return null;
    });
  }
}
