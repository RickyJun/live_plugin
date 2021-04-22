import 'dart:io';

import 'package:flutter/material.dart';

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
    if (Platform.isAndroid) {
      preview = RotatedBox(
        quarterTurns: 3,
        child: preview,
      );
    }
    return AspectRatio(
      aspectRatio:
          controller.previewSize.width * 1.0 / controller.previewSize.height,
      child: preview,
    );
  }
}
