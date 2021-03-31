import 'package:flutter/material.dart';

import 'live_controller.dart';

class LivePreview extends StatelessWidget {
  const LivePreview(this.controller);
  final LiveController controller;
  @override
  Widget build(BuildContext context) {
    return controller.isInitialized
        ? AspectRatio(
            aspectRatio: controller.aspectRatio,
            child: Transform(transform: ,child: Texture(textureId: controller.textureId),),
          )
        : Container();
  }
}
