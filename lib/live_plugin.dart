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
      int videoHeight,
      Function(Map msg) errorMsghandler}) async {
    _liveController = LiveController(_channel,
        rmptServer: rmptServer,
        fps: fps,
        bitrate: bitrate,
        videoWidth: videoWidth,
        videoHeight: videoHeight);
    await _liveController.initLiveConfig();
    setErrorMagHandler(errorMsghandler);
    return _liveController;
  }

  static void setErrorMagHandler(Function(Map msg) handler) {
    _channel.setMethodCallHandler((call) {
      switch (call.method) {
        case "error":
          {
            if (handler != null) {
              handler(call.arguments);
            }
            print("setMethodCallHandler==============" +
                call.arguments.toString());
            break;
          }
        default:
          print("method:${call.method} ==== args:${call.arguments.toString()}");
      }
      return null;
    });
  }
}
