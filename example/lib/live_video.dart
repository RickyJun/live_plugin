import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:live_plugin/Constants.dart';
import 'package:live_plugin/LivePreview.dart';
import 'package:live_plugin/live_controller.dart';
import 'package:live_plugin/live_plugin.dart';

class LivePage extends StatefulWidget {
  LivePage({Key key}) : super(key: key);

  @override
  _LivePageState createState() => _LivePageState();
}

class _LivePageState extends State<LivePage> {
  LiveController _liveController;
  String videoFilePath;
  @override
  void initState() {
    super.initState();
    LivePlugin.init(
      rmptServer: "rtmp://ossrs.net/",
      fps: 25,
      bitrate: Bitrates.Bitrate960x540.intValue,
      videoWidth: 350,
      videoHeight: 700,
    ).then((value) {
      setState(() {
        _liveController = value;
      });
      _liveController.startRecord();
    });
  }

  @override
  Widget build(BuildContext context) {
    return Stack(
      children: [
        Container(
            width: _liveController.videoWidth.toDouble(),
            height: _liveController.videoHeight.toDouble(),
            alignment: Alignment.center,
            child: LivePreview(_liveController)),
        Align(
          alignment: Alignment.bottomCenter,
          child: Container(
            height: 88,
            child: Row(
              children: [
                Expanded(
                    child: FlatButton(
                        onPressed: () {
                          _liveController.pauseRecord();
                        },
                        child: Text("暂停"))),
                Expanded(
                    child: FlatButton(
                        onPressed: () {
                          _liveController.stopRecord().then((value) {
                            videoFilePath = value;
                            if (value != null) {
                              Clipboard.setData(
                                  ClipboardData(text: videoFilePath));
                              //ToastUtils.show("$videoFilePath已复制到剪切板");
                            }
                          });
                        },
                        child: Text("结束"))),
                Expanded(
                    child: FlatButton(
                        onPressed: () {
                          _liveController.toggleFlashLight();
                        },
                        child: Text("开闪光灯"))),
                Expanded(
                    child: FlatButton(
                        onPressed: () {
                          _liveController
                              .setHardVideoFilter(Filters.GPUImageBeautyFilter);
                        },
                        child: Text("美颜滤镜")))
              ],
            ),
          ),
        )
      ],
    );
  }
}
