import 'dart:io';
import 'dart:math';

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

import 'live_controller.dart';

class LivePreview extends StatelessWidget {
  const LivePreview(this.controller);
  final LiveController controller;
  @override
  Widget build(BuildContext context) {
    Widget preview = controller.isInitialized
        ? Texture(
            textureId: controller.textureId,
          )
        : Container();

    return AspectRatio(
      aspectRatio: 1 / controller.aspectRatio,
      child: Stack(
        fit: StackFit.expand,
        children: [
          RotatedBox(
            quarterTurns: 0,
            child: preview,
          ),
        ],
      ),
    );
  }
  // int _getQuarterTurns() {
  //   int platformOffset = defaultTargetPlatform == TargetPlatform.iOS ? 1 : 0;
  //   Map<DeviceOrientation, int> turns = {
  //     DeviceOrientation.portraitUp: 0,
  //     DeviceOrientation.landscapeLeft: 1,
  //     DeviceOrientation.portraitDown: 2,
  //     DeviceOrientation.landscapeRight: 3,
  //   };
  //   return turns[_getApplicableOrientation()] + platformOffset;
  // }
  // DeviceOrientation _getApplicableOrientation() {
  //   return controller.isRecordingVideo
  //       ? controller.recordingOrientation
  //       : (controller.lockedCaptureOrientation ??
  //           controller.deviceOrientation);
  // }

}
