package com.rick.live.live_plugin

import android.app.Activity
import io.flutter.view.TextureRegistry
import me.lake.librestreaming.client.RESClient


class LiveController(val activity: Activity?,
                     val flutterTexture: TextureRegistry.SurfaceTextureEntry) {
    fun init(){
        //初始化尺寸
        //初始化resclient
        //设置res的上下文
        //生产resConfig
        //根据resConfig准备resclient
        //初始化texture到resclient
        //设置连接状态，视频状态监等等其他监听
    }

}