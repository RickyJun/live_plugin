import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:permission_handler/permission_handler.dart';
import 'Constants.dart';
import 'Utils.dart';

enum RecordStatus { Stop, Recording, Pause }

class LiveController {
  final MethodChannel _channel;
  String rmptServer = "rtmp://ossrs.net/";
  String rmptUrl;
  int fps;
  int bitrate;
  bool isInitialized = false;
  bool isEnableMirror = false;
  Size previewSize;
  LiveController(this._channel, {this.rmptServer, this.fps, this.bitrate});
  String _generateRmptUrl() {
    return '${rmptServer}live/livestream';
    //return "$rmptServer${Utils.getRandomAlphaString(3)}/${Utils.getRandomAlphaDigitString(5)}";
  }

  //
  Future<int> initLiveConfig() async {
    PermissionStatus status = await Permission.camera.request();
    if (status != PermissionStatus.granted) {
      return -2;
    }
    status = await Permission.storage.request();
    if (status != PermissionStatus.granted) {
      return -2;
    }
    status = await Permission.microphone.request();
    if (status != PermissionStatus.granted) {
      return -2;
    }
    assert(!(rmptServer == null && rmptUrl == null));
    this.rmptUrl ??= _generateRmptUrl();
    this.fps ??= 25;
    this.bitrate ??= 960 * 540;
    await getTextureId();
    Clipboard.setData(ClipboardData(text: this.rmptUrl));
    Map<dynamic, dynamic> res = await _channel.invokeMethod("initLiveConfig", {
      "rmptUrl": this.rmptUrl,
      "fps": this.fps,
      "bitrate": this.bitrate,
    });
    await _getPreviewSize();
    if (res != null) {
      isInitialized = true;
    }
    return 0;
  }

  Future<Size> _getPreviewSize() async {
    Map<String, dynamic> res = await _channel.invokeMethod("getPreviewSize");
    if (res == null) {
      throw FlutterError("getPreviewSize return null");
    }
    previewSize = Size(res["width"], res["height"]);
    return previewSize;
  }

  int textureId;
  Future<int> getTextureId() async {
    Map<dynamic, dynamic> res = await _channel.invokeMethod("textureId");
    if (res != null) {
      textureId = res["textureId"];
      return textureId;
    }
  }

  void startRecord() async {
    initLiveConfig();
    int res = await _channel.invokeMethod("startRecord");
    if (res != null && res != 0) {
      throw FlutterError(
          "startRecord fail with code $res,check the native code");
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

  void setHardVideoFilter(Filters filter) {
    _channel.invokeMethod("setHardVideoFilterByName", filter.value);
  }

  //关闭
  void close() {
    _channel.invokeMethod("close");
  }
}
