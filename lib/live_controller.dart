import 'package:flutter/services.dart';

import 'Utils.dart';

class LiveController {
  final MethodChannel _channel;
  String rmptServer = "rtmp://ossrs.net/";
  String rmptUrl = "";
  int fps;
  int bitrate;
  int videoWidth;
  int videoHeight;
  LiveController(this._channel, {this.rmptServer});
  String _generateRmptUrl() {
    return "$rmptServer${Utils.getRandomAlphaString(3)}/${Utils.getRandomAlphaDigitString(5)}";
  }

  initLiveConfig(
      {String rmptServer,
      String rmptUrl,
      int fps,
      int bitrate,
      int videoWidth,
      int videoHeight}) {
    assert(!(rmptServer == null && rmptUrl == null));
    assert(videoHeight != null && videoWidth != null);
    this.rmptServer = rmptServer;
    this.rmptUrl = rmptUrl;
    this.fps = fps;
    this.bitrate = bitrate;
    this.videoWidth = videoWidth;
    this.videoHeight = videoHeight;
    rmptUrl ??= _generateRmptUrl();
    this.fps ??= 25;
    this.bitrate ??= 960 * 540;
    _channel.invokeMethod("initLiveConfig", {
      "rmptUrl": rmptUrl,
      "fps": fps,
      "bitrate": bitrate,
      "videoWidth": videoWidth,
      "videoHeight": videoHeight
    });
  }

  Future<int> recordStatus() async {
    return await _channel.invokeMethod("recordStatus");
  }

  Future<String> takeScreenShot() async {
    String imageFilePath = await _channel.invokeMethod("takeScreenShot");
    return imageFilePath;
  }

  void close() {
    _channel.invokeMethod("close");
  }
}
