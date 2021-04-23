package com.rick.live.live_plugin.controller_interface

import android.content.Context
import android.util.Size
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
    open fun init(context: Context?, avOption: StreamOption,result: MethodChannel.Result) {}
    open fun getPreviewSize(result: MethodChannel.Result){}
    open fun close(result: MethodChannel.Result) {}
    //获取textureId
    open var textureId:Long? = null
        get() = 0
    open fun startStreaming(result: MethodChannel.Result,rtmpUrl: String?) {}
    open fun stopStreaming(result: MethodChannel.Result) {}
    open fun pauseRecord(result: MethodChannel.Result){}
    open fun resumeRecord(result: MethodChannel.Result){}
    open fun stopRecord(result: MethodChannel.Result): String? {return null}
     /**
     * 切换摄像头
     */
    open fun swapCamera(result: MethodChannel.Result) {}
    /**
     * 摄像头焦距 [0.0f,1.0f]
     */
    open fun setZoomByPercent(result: MethodChannel.Result,targetPercent: Float) {}
    /**
     * 摄像头开关闪光灯
     */
    open fun toggleFlashLight(result: MethodChannel.Result) {}
    /**
     * 推流过程中，重新设置帧率
     */
    open fun reSetVideoFPS(result: MethodChannel.Result,fps: Int) {}
    /**
     * 推流过程中，重新设置码率
     */
    open fun reSetVideoBitrate(result: MethodChannel.Result,type: String) {}
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
    open fun setMirror(result: MethodChannel.Result,isEnableMirror: Boolean):Int {return -1}
    /**
     * 设置滤镜
     */
    open fun setHardVideoFilterByName(result: MethodChannel.Result,type: String) {}
}