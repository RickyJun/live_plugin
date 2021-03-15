package com.rick.live.live_plugin

import android.app.Activity
import android.content.Context
import android.graphics.SurfaceTexture
import io.flutter.view.TextureRegistry
import me.lake.librestreaming.client.RESClient
import me.lake.librestreaming.core.listener.RESConnectionListener
import me.lake.librestreaming.core.listener.RESVideoChangeListener
import me.lake.librestreaming.model.RESConfig
import me.lake.librestreaming.tools.CameraUtil
import me.lake.librestreaming.ws.AspectTextureView
import me.lake.librestreaming.ws.StreamAVOption
import me.lake.librestreaming.ws.StreamConfig
import java.util.*


class LiveController(val activity: Activity?,
                     val flutterTexture: TextureRegistry.SurfaceTextureEntry, context: Context?) {
    private var resClient: RESClient? = null
    private var resConfig: RESConfig? = null
    private var mContext: Context? = null
    private var surfaceTexture: SurfaceTexture? = null
    private var avOption: StreamAVOption? = null
    private val outerStreamStateListeners: List<RESConnectionListener> = ArrayList()
    /**
     * 根据AVOption初始化&打开预览
     * @param avOption
     */
    fun init(context: Context?, avOption: StreamAVOption?){
        requireNotNull(avOption) { "AVOption is null." }
        this.avOption = avOption
        //初始化尺寸
        compatibleSize(avOption)
        //初始化resclient
        this.resClient = this.getRESClient()
        //设置res的上下文
        setContext(mContext)
        //生产resConfig
        this.resConfig = StreamConfig.build(context, avOption)
        //根据resConfig准备resclient
        var isSucceed = this.resClient!!.prepare(this.resConfig)
        //初始化texture到resclient
        surfaceTexture = flutterTexture.surfaceTexture()
        //设置连接状态，视频状态监等等其他监听
        surfaceTexture!!.setOnFrameAvailableListener(SurfaceTexture.OnFrameAvailableListener {
            fun onFrameAvailable(surfaceTexture: SurfaceTexture?) {
                if(this.resClient != null){
                    print("surfaceTexture set suuuu==================")
                    this.resClient!!.startPreview(surfaceTexture,this.avOption!!.videoWidth,this.avOption!!.videoHeight)
                }
            }
        })
    }
    //获取textureId
    fun getTextureId() = flutterTexture.id()

    private var ConnectionListener: RESConnectionListener = object : RESConnectionListener {
        override fun onOpenConnectionResult(result: Int) {
            if (result == 1) {
                resClient!!.stopStreaming()
            }
            for (listener in outerStreamStateListeners) {
                listener.onOpenConnectionResult(result)
            }
        }

        override fun onWriteError(errno: Int) {
            for (listener in outerStreamStateListeners) {
                listener.onWriteError(errno)
            }
        }

        override fun onCloseConnectionResult(result: Int) {
            for (listener in outerStreamStateListeners) {
                listener.onCloseConnectionResult(result)
            }
        }
    }

    var VideoChangeListener = RESVideoChangeListener { width, height ->
        if (flutterTexture != null) {

            //textureView.setAspectRatio(AspectTextureView.MODE_INSIDE, width.toDouble() / height)
        }
    }
    @Synchronized
    fun getRESClient(): RESClient? {
        if (this.resClient == null) {
            this.resClient = RESClient()
        }
        return this.resClient
    }
    private fun compatibleSize(avOptions: StreamAVOption) {
        val cameraSize = CameraUtil.getInstance().getBestSize(CameraUtil.getFrontCameraSize(), "800".toInt())
        if (!CameraUtil.hasSupportedFrontVideoSizes) {
            if (null == cameraSize || cameraSize.width <= 0) {
                avOptions.videoWidth = 720
                avOptions.videoHeight = 480
            } else {
                avOptions.videoWidth = cameraSize.width
                avOptions.videoHeight = cameraSize.height
            }
        }
    }

    /**
     * 设置上下文
     */
    fun setContext(context: Context?) {
        if (this.resClient != null) {
            this.resClient!!.setContext(context)
        }
    }


}