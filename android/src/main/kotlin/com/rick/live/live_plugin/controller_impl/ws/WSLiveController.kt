package com.rick.live.live_plugin.controller_impl.ws

import android.content.Context
import android.graphics.SurfaceTexture
import android.os.Build
import android.util.Size
import androidx.annotation.NonNull
import androidx.annotation.RequiresApi
import com.rick.live.live_plugin.LivePlugin
import com.rick.live.live_plugin.camera.CameraUtils
import com.rick.live.live_plugin.camera.DartMessenger
import com.rick.live.live_plugin.camera.types.FlashMode
import com.rick.live.live_plugin.controller_interface.LiveController
import com.rick.live.live_plugin.controller_interface.RecordStatus
import com.rick.live.live_plugin.controller_interface.StreamOption
import io.flutter.plugin.common.BinaryMessenger
import io.flutter.plugin.common.FlutterException
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.view.TextureRegistry
import me.lake.librestreaming.client.RESClient
import me.lake.librestreaming.core.listener.RESConnectionListener
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
import me.lake.librestreaming.ws.filter.audiofilter.SetVolumeAudioFilter


interface ErrorListener {
    fun onError(errorType:String,dec:String)
}
class WSLiveController(val flutterTexture: TextureRegistry.SurfaceTextureEntry, val messenger: BinaryMessenger, val result: MethodChannel.Result, context: Context?): LiveController() {

    private lateinit var resClient: RESClient
    private var resConfig: RESConfig? = null
    private var surfaceTexture: SurfaceTexture? = null
    private var avOption: StreamAVOption = StreamAVOption()
    private var outerStreamStateListeners: java.util.ArrayList<RESConnectionListener> = ArrayList()
    private val quality_value_min = 400 * 1024
    private val quality_value_max = 700 * 1024
    var wsCamera: WSCamera? = null
    /**
     * 根据AVOption初始化&打开预览
     * @param avOption
     */
    override fun init(context: Context?, avOption: StreamOption):Int{
        try {
            initAvOption(avOption)
            //初始化resclient
            this.resClient = this.getRESClient()!!
            //设置res的上下文
            setContext(LivePlugin.activity)

            //初始化camera
            wsCamera = WSCamera(flutterTexture,messenger)
            //初始化preview size
            this.avOption.videoWidth = wsCamera!!.camera!!.previewSize.width
            this.avOption.videoHeight = wsCamera!!.camera!!.previewSize.height
            this.avOption.previewWidth = wsCamera!!.camera!!.previewSize.width
            this.avOption.previewHeight = wsCamera!!.camera!!.previewSize.height
            StreamAVOption.recordVideoWidth = wsCamera!!.camera!!.previewSize.width
            StreamAVOption.recordVideoHeight = wsCamera!!.camera!!.previewSize.height
            //生产resConfig
            this.resConfig = StreamConfig.build(context, this.avOption)
            this.resClient.prepare(this.resConfig,this.wsCamera)
            //初始化preview texture到resclient
            surfaceTexture = flutterTexture.surfaceTexture()
            surfaceTexture!!.setDefaultBufferSize(avOption.previewWidth,avOption.previewHeight)
            addListenerAndFilter()
            startRecord()
            return 0
        }catch (e:Exception){
            getErrorMsg(e,"init")
            return -1
        }
    }
    //StreamOption转为ws的StreamAVOption
    fun initAvOption(avOption: StreamOption){
        this.avOption.previewHeight = avOption.previewHeight;
        this.avOption.previewWidth = avOption.previewWidth;
        this.avOption.videoHeight = avOption.videoHeight;
        this.avOption.videoWidth = avOption.videoWidth;
        this.avOption.videoBitrate = avOption.videoBitrate;
        this.avOption.videoFramerate = avOption.videoFramerate;
        this.avOption.streamUrl = avOption.streamUrl;
    }
    @RequiresApi(Build.VERSION_CODES.LOLLIPOP)

    override fun getPreviewSize(){
        if(wsCamera!!.camera!!.previewSize == null){
            throw java.lang.Exception("camera have not init,previewSize is null");
        }
        val size:Size =  wsCamera!!.camera!!.previewSize
        val res:MutableMap<String,Any?> = HashMap<String,Any?>()
        res["width"] = size.width
        res["height"] = size.height
        this.result.success(res)
    }
    /**
     * 开始录制
     */
    private lateinit var mMuxer: MediaMuxerWrapper
    override fun startRecord() {
        try {
            resClient.startPreview(surfaceTexture,avOption.previewWidth,avOption.previewHeight)
            this.resClient.setNeedResetEglContext(true)
            mMuxer = MediaMuxerWrapper(".mp4") // if you record audio only, ".m4a" is also OK.
            MediaVideoEncoder(mMuxer, mMediaEncoderListener, StreamAVOption.recordVideoWidth, StreamAVOption.recordVideoHeight)
            MediaAudioEncoder(mMuxer, mMediaEncoderListener)
            mMuxer.prepare()
            mMuxer.startRecording()
            recordStatus = RecordStatus.Recording
            //startStreaming(this.avOption.streamUrl)
        } catch (e: Exception) {
            recordStatus = RecordStatus.Stop
            getErrorMsg(e,"startRecord")
        }
    }

    /**
     * destroy
     */
    override fun close() {
        try {
            this.resClient.setConnectionListener(null)
            this.resClient.setVideoChangeListener(null)
            if (this.resClient.isStreaming) {
                this.resClient.stopStreaming()
            }
            if (recordStatus == RecordStatus.Recording) {
                stopRecord()
            }
            this.resClient.destroy()
        }catch (e:Exception){
            getErrorMsg(e,"destroy")
        }

    }

    /**
     * 添加推流状态监听
     * @param listener
     */
    fun addStreamStateListener(listener: RESConnectionListener?) {
        try {
            if (listener != null && !outerStreamStateListeners.contains(listener)) {
                outerStreamStateListeners.add(listener)
            }
        }catch (e:Exception){
            getErrorMsg(e,"addStreamStateListener")
        }

    }

    //获取textureId
    override var textureId:Long? = null
        get() = flutterTexture.id()
    //连接状态监听
    var reConnMaxTime:Int = 10;
    private var ConnectionListener: RESConnectionListener = object : RESConnectionListener {
        override fun onOpenConnectionResult(result: Int) {
            if (result == 1) {
                if(reConnMaxTime > 0){
                    resClient.reStartStreaming(avOption.streamUrl)
                    reConnMaxTime -= 1
                }else{
                    resClient.stopStreaming();
                    //TODO 提示连接失败
                }
            }else{
                System.out.println("result == 0,success!");
            }
            for (listener in outerStreamStateListeners) {
                listener.onOpenConnectionResult(result)
            }
        }

        override fun onWriteError(errno: Int) {
            if(errno == 9 || errno == 32){
                //when sending, socket closed by socket error 32,broken pipe，重写连接
                System.out.println("socket closed by other error =======================");
                resClient.reStartStreaming(avOption.streamUrl);
            }
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
            System.out.println("width="+width)
            //textureView.setAspectRatio(AspectTextureView.MODE_INSIDE, width.toDouble() / height)
        }
    }

    /**
     * callback methods from encoder
     */
    var mMediaEncoderListener: MediaEncoder.MediaEncoderListener = object : MediaEncoder.MediaEncoderListener {
        override fun onPrepared(encoder: MediaEncoder?) {
            if (encoder is MediaVideoEncoder && resClient != null) resClient.setVideoEncoder(encoder as MediaVideoEncoder?)
        }

        override fun onStopped(encoder: MediaEncoder?) {
            if (encoder is MediaVideoEncoder && resClient != null) resClient.setVideoEncoder(null)
        }
    }
    private fun addListenerAndFilter() {
            this.resClient.setConnectionListener(ConnectionListener)
            this.resClient.setVideoChangeListener(VideoChangeListener)
            this.resClient.setSoftAudioFilter(SetVolumeAudioFilter())

    }
    @Synchronized
    fun getRESClient(): RESClient? {
        this.resClient = RESClient()
        return this.resClient
    }


    /**
     * 设置上下文
     */
    fun setContext(context: Context?) {
        this.resClient.setContext(context)
    }
    /**
     * 是否在录制
     */
    fun recordStatus(): Int {
        return recordStatus.ordinal
    }

    /**
     * 开始推流,
     */
    override fun startStreaming(rtmpUrl: String?) {
        try {
            this.resClient.startStreaming(rtmpUrl)
        }catch (e:Exception){
            getErrorMsg(e,"startStreaming")
        }

    }

    /**
     * 停止推流,关闭推流
     */
    override fun stopStreaming() {
        try {
            this.resClient.stopStreaming()
        }catch (e:Exception){
            getErrorMsg(e,"stopStreaming")
        }

    }


    override fun pauseRecord(){
        try {
            if(recordStatus == RecordStatus.Recording){
                resClient.stopPreview(false)
                recordStatus = RecordStatus.Pause
            }
        }catch (e:Exception){
            getErrorMsg(e,"pauseRecord")
        }


    }
    override fun resumeRecord(){
        try {
            if(recordStatus == RecordStatus.Pause || recordStatus == RecordStatus.Stop){
                resClient.startPreview(surfaceTexture,avOption.videoWidth,avOption.videoHeight)
                recordStatus = RecordStatus.Recording
            }
        }catch (e:Exception){
            getErrorMsg(e,"resumeRecord")
        }

    }
    /**
     * 停止录制
     */
    override fun stopRecord(): String? {
        try {
            stopStreaming()
            recordStatus = RecordStatus.Stop
            val path: String = mMuxer.getFilePath()
            mMuxer.stopRecording()

            System.gc()
            return path
        }catch (e:Exception){
            getErrorMsg(e,"resumeRecord")
            return null;
        }

    }

    /**
     * 切换摄像头
     */
    override fun swapCamera() {
        this.resClient.swapCamera()
    }

    /**
     * 摄像头焦距 [0.0f,1.0f]
     */
    override fun setZoomByPercent(targetPercent: Float) {
        if (this.resClient != null) {
            this.resClient.setZoomByPercent(targetPercent)
        }
    }

    /**
     * 摄像头开关闪光灯
     */
    var flashMode:FlashMode = FlashMode.off
    override fun toggleFlashLight() {
        if(flashMode == FlashMode.off){
            flashMode = FlashMode.always
        }else{
            flashMode = FlashMode.off
        }
        wsCamera!!.camera!!.setFlashMode(this.result,flashMode)
    }

    /**
     * 推流过程中，重新设置帧率
     */
    override fun reSetVideoFPS(fps: Int) {
        if (this.resClient != null) {
            this.resClient.reSetVideoFPS(fps)
        }
    }

    /**
     * 推流过程中，重新设置码率
     */
    override fun reSetVideoBitrate(type: String) {
        if (this.resClient != null) {
            this.resClient.reSetVideoBitrate(Bitrates.getBitrateByType(type))
        }
    }

    /**
     * 截图
     */
    override fun takeScreenShot() {
        if (this.resClient != null) {
            this.resClient.takeScreenShot{
                //存储bitmap到本地data
                //返回文件路径到flutter】
                //result.success(path)
            }
        }
    }

    /**
     * 镜像
     * @param isEnableMirror   是否启用镜像功能 总开关
     * isEnablePreviewMirror  是否开启预览镜像
     *  isEnableStreamMirror   是否开启推流镜像
     */
    override fun setMirror(isEnableMirror: Boolean):Int {
        if (this.resClient != null) {
            this.resClient.setMirror(isEnableMirror, isEnableMirror, isEnableMirror)
            return 0;
        }
        return -1;
    }


    /**
     * 设置滤镜
     */
    override fun setHardVideoFilterByName(type: String) {
        try {
            if (this.resClient != null) {
                val filter:BaseHardVideoFilter = Filters.getFilterByType(type)
                this.resClient.setHardVideoFilter(filter)
            }
        }catch (e:Exception){
            getErrorMsg(e,"setHardVideoFilterByName")
        }

    }

    /**
     * 获取BufferFreePercent,获取发送缓存区的剩余空间比，0则已经满了，说明网络阻塞或者太慢
     */
//    fun getSendBufferFreePercent(): Float {
//        return this.resClient.sendBufferFreePercent
//    }

    /**
     * AVSpeed 推流速度 和网络相关
     */
//    fun getAVSpeed(): Int {
//        return this.resClient.avSpeed
//    }


}