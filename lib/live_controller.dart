import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

import 'Constants.dart';
import 'Utils.dart';

enum RecordStatus { Stop, Recording, Pause }

class LiveController {
  final MethodChannel _channel;
  String rmptServer = "rtmp://ossrs.net/";
  String rmptUrl = "";
  int fps;
  int bitrate;
  int videoWidth;
  int videoHeight;
  bool isInitialized = false;
  bool isEnableMirror = false;
  int _textureId;
  LiveController(this._channel, {this.rmptServer});
  String _generateRmptUrl() {
    return "$rmptServer${Utils.getRandomAlphaString(3)}/${Utils.getRandomAlphaDigitString(5)}";
  }

  //初始化
  initLiveConfig(
      {String rmptServer,
      String rmptUrl,
      int fps,
      int bitrate,
      int videoWidth,
      int videoHeight}) async {
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
    Map<String, dynamic> res = await _channel.invokeMethod("initLiveConfig", {
      "rmptUrl": rmptUrl,
      "fps": fps,
      "bitrate": bitrate,
      "videoWidth": videoWidth,
      "videoHeight": videoHeight
    });
    if (res != null) {
      _textureId = res["_textureId"];
      isInitialized = true;
    }
  }

  get textureId {
    if (isInitialized) {
      if (_textureId == null) {
        throw FlutterError(
            "_textureId is empty,please check the step 'init',maybe throw some error");
      } else {
        return _textureId;
      }
    } else {
      throw FlutterError("liveController had no init");
    }
  }

  void startRecord() async {
    int res = await _channel.invokeMethod("recordStatus");
    if (res != null && res != 0) {
      throw FlutterError("startRecord fail with code -1,check the native code");
    }
  }

  void pauseRecord() async {
    await _channel.invokeMethod("pauseRecord");
  }

  void resumeRecord() async {
    await _channel.invokeMethod("resumeRecord");
  }

  Future<String> stopRecord() async {
    String path = await _channel.invokeMethod("stopRecord");
    return path;
  }

  void swapCamera() {
    _channel.invokeMethod("swapCamera");
  }

  void setZoomByPercent(double targetPercent) {
    assert(targetPercent > 0.0 && targetPercent < 1.0);
    _channel.invokeMethod("setZoomByPercent", targetPercent);
  }

  void toggleFlashLight() {
    _channel.invokeMethod("toggleFlashLight");
  }

  void reSetVideoFPS(int fps) {
    _channel.invokeMethod("reSetVideoFPS", fps);
  }

  void reSetVideoBitrate(Bitrates type) {
    _channel.invokeMethod("reSetVideoBitrate", type.value);
  }

  //录像状态
  Future<int> recordStatus() async {
    return await _channel.invokeMethod("recordStatus");
  }

  //截图
  Future<String> takeScreenShot() async {
    String imageFilePath = await _channel.invokeMethod("takeScreenShot");
    return imageFilePath;
  }

  void setMirror(bool isEnableMirror) async {
    int res = await _channel.invokeMethod("setMirror", isEnableMirror);
    if (res != null && res == 0) {
      this.isEnableMirror = isEnableMirror;
    }
  }

  void setHardVideoFilterByName(Filters filter) {
    _channel.invokeMethod("setHardVideoFilterByName", filter.value);
  }

  //关闭
  void close() {
    _channel.invokeMethod("close");
  }
}
