package com.rick.live.live_plugin.controller_interface

import android.hardware.Camera

class StreamOption {
    var cameraIndex = AVOptionsHolder.DEFAULT_CAMERA_INDEX //前后置摄像头
    var previewWidth = AVOptionsHolder.DEFAULT_PREVIEW_WIDTH //预览宽
    var previewHeight = AVOptionsHolder.DEFAULT_PREVIEW_HEIGHT //预览高
    var videoWidth = AVOptionsHolder.DEFAULT_VIDEO_WIDTH //推流的视频宽
    var videoHeight = AVOptionsHolder.DEFAULT_VIDEO_HEIGHT //推流的视频高
    var videoBitrate = AVOptionsHolder.DEFAULT_VIDEO_BITRATE //比特率
    var videoFramerate =AVOptionsHolder.DEFAULT_VIDEO_FPS //帧率
    var videoGOP = AVOptionsHolder.DEFAULT_VIDEO_GOP //gop 关键帧间隔
    var streamUrl = ""

    companion object {
        var recordVideoWidth = 544 //录制的视频宽
        var recordVideoHeight = 960 //录制的视频高
    }
    object AVOptionsHolder {
        const val DEFAULT_CAMERA_INDEX = Camera.CameraInfo.CAMERA_FACING_BACK
        const val DEFAULT_FILTER_MODE = 1
        const val DEFAULT_RENDER_MODE = 2
        const val DEFAULT_PREVIEW_WIDTH = 1280
        const val DEFAULT_PREVIEW_HEIGHT = 720
        const val DEFAULT_VIDEO_WIDTH = 640
        const val DEFAULT_VIDEO_HEIGHT = 360
        const val DEFAULT_VIDEO_BITRATE = 600 * 1024
        const val DEFAULT_VIDEO_FPS = 20
        const val DEFAULT_VIDEO_GOP = 2
    }
}