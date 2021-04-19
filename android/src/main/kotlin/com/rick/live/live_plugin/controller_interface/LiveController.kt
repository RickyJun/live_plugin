package com.rick.live.live_plugin.controller_interface

import android.content.Context
import com.rick.live.live_plugin.controller_impl.ws.ErrorListener
import io.flutter.plugin.common.MethodChannel
import me.lake.librestreaming.ws.StreamAVOption
enum class RecordStatus{
    Stop,
    Recording,
    Pause
}
abstract class LiveController {
    var recordStatus: RecordStatus = RecordStatus.Stop
    lateinit var errorListener: ErrorListener
    open fun getErrorMsg(e:Exception,method:String){
        e.printStackTrace();
        errorListener.onError("$method err$e","msg:${e.message.toString()},cause:${e.cause.toString()}")
    }
    open fun init(context: Context?, avOption: StreamOption) {}
    open fun startRecord():Int{return -1}
    open fun destroy() {}
    //获取textureId
    open var textureId:Long? = null
        get() = 0
    open fun startStreaming(rtmpUrl: String?) {}
    open fun stopStreaming() {}
    open fun pauseRecord(){}
    open fun resumeRecord(){}
    open fun stopRecord(): String? {return null}
     /**
     * 切换摄像头
     */
    open fun swapCamera() {}
    /**
     * 摄像头焦距 [0.0f,1.0f]
     */
    open fun setZoomByPercent(targetPercent: Float) {}
    /**
     * 摄像头开关闪光灯
     */
    open fun toggleFlashLight() {}
    /**
     * 推流过程中，重新设置帧率
     */
    open fun reSetVideoFPS(fps: Int) {}
    /**
     * 推流过程中，重新设置码率
     */
    open fun reSetVideoBitrate(type: String) {}
    /**
     * 截图
     */
    open fun takeScreenShot(result: MethodChannel.Result) {}
    /**
     * 镜像
     * @param isEnableMirror   是否启用镜像功能 总开关
     * isEnablePreviewMirror  是否开启预览镜像
     *  isEnableStreamMirror   是否开启推流镜像
     */
    open fun setMirror(isEnableMirror: Boolean):Int {return -1}
    /**
     * 设置滤镜
     */
    open fun setHardVideoFilterByName(type: String) {}
}