import 'package:flutter/material.dart';

import 'live_controller.dart';

class LivePreview extends StatelessWidget {
  const LivePreview(this.controller);
  final LiveController controller;
  @override
  Widget build(BuildContext context) {
    return controller.isInitialized
        ? AspectRatio(
            aspectRatio: 1 / controller.aspectRatio,
            child: Texture(
              textureId: 10,
              filterQuality: FilterQuality.high,
            ))
        : Container();
  }
}
