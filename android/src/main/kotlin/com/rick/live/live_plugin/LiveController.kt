package com.rick.live.live_plugin

import android.app.Activity
import android.content.Context
import android.graphics.SurfaceTexture
import io.flutter.view.TextureRegistry
import me.lake.librestreaming.client.RESClient
import me.lake.librestreaming.core.listener.RESConnectionListener
import me.lake.librestreaming.core.listener.RESScreenShotListener
import me.lake.librestreaming.core.listener.RESVideoChangeListener
import me.lake.librestreaming.encoder.MediaAudioEncoder
import me.lake.librestreaming.encoder.MediaEncoder
import me.lake.librestreaming.encoder.MediaMuxerWrapper
import me.lake.librestreaming.encoder.MediaVideoEncoder
import me.lake.librestreaming.filter.hardvideofilter.BaseHardVideoFilter
import me.lake.librestreaming.model.RESConfig
import me.lake.librestreaming.tools.CameraUtil
import me.lake.librestreaming.ws.StreamAVOption
import me.lake.librestreaming.ws.StreamConfig
import me.lake.librestreaming.ws.StreamLiveCameraView
import me.lake.librestreaming.ws.filter.audiofilter.SetVolumeAudioFilter
import java.io.IOException


class LiveController(activity: Activity?,val flutterTexture: TextureRegistry.SurfaceTextureEntry, context: Context?) {


    private lateinit var resClient: RESClient
    private var resConfig: RESConfig? = null
    private var surfaceTexture: SurfaceTexture? = null
    private var avOption: StreamAVOption? = null
    private var outerStreamStateListeners: java.util.ArrayList<RESConnectionListener> = ArrayList()
    private val quality_value_min = 400 * 1024
    private val quality_value_max = 700 * 1024
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
        this.resClient = this.getRESClient()!!
        //设置res的上下文
        setContext(context)
        //生产resConfig
        this.resConfig = StreamConfig.build(context, avOption)
        //根据resConfig准备resclient
        var isSucceed = this.resClient.prepare(this.resConfig)
        //初始化texture到resclient
        surfaceTexture = flutterTexture.surfaceTexture()
        //设置连接状态，视频状态监等等其他监听
        surfaceTexture!!.setOnFrameAvailableListener { surfaceTexture ->
            if(resClient != null){
                print("surfaceTexture set suuuu==================")
                resClient.startPreview(surfaceTexture,avOption!!.videoWidth,avOption!!.videoHeight)
            }
        }
        addListenerAndFilter()
    }

    /**
     * destroy
     */
    fun destroy() {
        if (this.resClient != null) {
            this.resClient.setConnectionListener(null)
            this.resClient.setVideoChangeListener(null)
            if (this.resClient.isStreaming) {
                this.resClient.stopStreaming()
            }
            if (isRecord()) {
                stopRecord()
            }
            this.resClient.destroy()
        }
    }




    /**
     * 添加推流状态监听
     * @param listener
     */
    fun addStreamStateListener(listener: RESConnectionListener?) {
        if (listener != null && !outerStreamStateListeners.contains(listener)) {
            outerStreamStateListeners.add(listener)
        }
    }

    //获取textureId
    fun getTextureId() = flutterTexture.id()
    //连接状态监听
    private var ConnectionListener: RESConnectionListener = object : RESConnectionListener {
        override fun onOpenConnectionResult(result: Int) {
            if (result == 1) {
                resClient.stopStreaming()
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
    //尺寸改变监听
    var VideoChangeListener = RESVideoChangeListener { width, height ->
        if (flutterTexture != null) {

            //textureView.setAspectRatio(AspectTextureView.MODE_INSIDE, width.toDouble() / height)
        }
    }

    /**
     * callback methods from encoder
     */
    var mMediaEncoderListener: MediaEncoder.MediaEncoderListener = object : MediaEncoder.MediaEncoderListener {
        override fun onPrepared(encoder: MediaEncoder?) {
            if (encoder is MediaVideoEncoder && resClient != null) resClient!!.setVideoEncoder(encoder as MediaVideoEncoder?)
        }

        override fun onStopped(encoder: MediaEncoder?) {
            if (encoder is MediaVideoEncoder && resClient != null) resClient!!.setVideoEncoder(null)
        }
    }
    private fun addListenerAndFilter() {
        if (this.resClient != null) {
            this.resClient.setConnectionListener(ConnectionListener)
            this.resClient.setVideoChangeListener(VideoChangeListener)
            this.resClient.setSoftAudioFilter(SetVolumeAudioFilter())
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
    /**
     * 是否在录制
     */
    fun isRecord(): Boolean {
        return isRecord
    }


    /**
     * 开始推流
     */
    fun startStreaming(rtmpUrl: String?) {
        if (this.resClient != null) {
            this.resClient.startStreaming(rtmpUrl)
        }
    }

    /**
     * 停止推流
     */
    fun stopStreaming() {
        if (this.resClient != null) {
            this.resClient.stopStreaming()
        }
    }

    /**
     * 开始录制
     */
    private var mMuxer: MediaMuxerWrapper? = null
    private var isRecord = false
    fun startRecord() {
        if (this.resClient != null) {
            this.resClient.setNeedResetEglContext(true)
            try {
                mMuxer = MediaMuxerWrapper(".mp4") // if you record audio only, ".m4a" is also OK.
                MediaVideoEncoder(mMuxer, mMediaEncoderListener, StreamAVOption.recordVideoWidth, StreamAVOption.recordVideoHeight)
                MediaAudioEncoder(mMuxer, mMediaEncoderListener)
                mMuxer!!.prepare()
                mMuxer!!.startRecording()
                isRecord = true
            } catch (e: IOException) {
                isRecord = false
                e.printStackTrace()
            }
        }
    }
    /**
     * 停止录制
     */
    fun stopRecord(): String? {
        isRecord = false
        if (mMuxer != null) {
            val path: String = mMuxer!!.getFilePath()
            mMuxer!!.stopRecording()
            mMuxer = null
            System.gc()
            return path
        }
        System.gc()
        return null
    }

    /**
     * 切换摄像头
     */
    fun swapCamera() {
        if (this.resClient != null) {
            this.resClient.swapCamera()
        }
    }

    /**
     * 摄像头焦距 [0.0f,1.0f]
     */
    fun setZoomByPercent(targetPercent: Float) {
        if (this.resClient != null) {
            this.resClient.setZoomByPercent(targetPercent)
        }
    }

    /**
     * 摄像头开关闪光灯
     */
    fun toggleFlashLight() {
        if (this.resClient != null) {
            this.resClient.toggleFlashLight()
        }
    }

    /**
     * 推流过程中，重新设置帧率
     */
    fun reSetVideoFPS(fps: Int) {
        if (this.resClient != null) {
            this.resClient.reSetVideoFPS(fps)
        }
    }

    /**
     * 推流过程中，重新设置码率
     */
    fun reSetVideoBitrate(bitrate: Int) {
        if (this.resClient != null) {
            this.resClient.reSetVideoBitrate(bitrate)
        }
    }

    /**
     * 截图
     */
    fun takeScreenShot(listener: RESScreenShotListener?) {
        if (this.resClient != null) {
            this.resClient.takeScreenShot(listener)
        }
    }

    /**
     * 镜像
     * @param isEnableMirror   是否启用镜像功能 总开关
     * @param isEnablePreviewMirror  是否开启预览镜像
     * @param isEnableStreamMirror   是否开启推流镜像
     */
    fun setMirror(isEnableMirror: Boolean, isEnablePreviewMirror: Boolean, isEnableStreamMirror: Boolean) {
        if (this.resClient != null) {
            this.resClient.setMirror(isEnableMirror, isEnablePreviewMirror, isEnableStreamMirror)
        }
    }


    /**
     * 设置滤镜
     */
    fun setHardVideoFilter(baseHardVideoFilter: BaseHardVideoFilter?) {
        if (this.resClient != null) {
            this.resClient.setHardVideoFilter(baseHardVideoFilter)
        }
    }

    /**
     * 获取BufferFreePercent
     */
    fun getSendBufferFreePercent(): Float {
        return this.resClient.sendBufferFreePercent
    }

    /**
     * AVSpeed 推流速度 和网络相关
     */
    fun getAVSpeed(): Int {
        return this.resClient.avSpeed
    }


}