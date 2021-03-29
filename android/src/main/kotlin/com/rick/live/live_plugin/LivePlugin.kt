package com.rick.live.live_plugin

import android.app.Activity
import androidx.annotation.NonNull
import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.embedding.engine.plugins.activity.ActivityAware
import io.flutter.embedding.engine.plugins.activity.ActivityPluginBinding
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result
import me.lake.librestreaming.core.listener.RESConnectionListener
import me.lake.librestreaming.ws.StreamAVOption
import java.lang.reflect.Method
import java.util.*
import kotlin.collections.HashMap

/** LivePlugin */
class LivePlugin: FlutterPlugin, MethodCallHandler, ActivityAware {
  /// The MethodChannel that will the communication between Flutter and native Android
  ///
  /// This local reference serves to register the plugin with the Flutter Engine and unregister it
  /// when the Flutter Engine is detached from the Activity
  private lateinit var channel: MethodChannel
  private lateinit var activity: Activity
  //推流controller
  private lateinit var liveController: LiveController
  //推流地址
  private lateinit var rtmpUrl: String
  //推流配置
  private lateinit var streamAVOption: StreamAVOption
  private lateinit var flutterPluginBinding: FlutterPlugin.FlutterPluginBinding
  private val methods:HashMap<String,Method> = HashMap();


  override fun onAttachedToEngine(@NonNull flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
    this.flutterPluginBinding = flutterPluginBinding
    channel = MethodChannel(flutterPluginBinding.binaryMessenger, "live_rtmp")
    channel.setMethodCallHandler(this)
    
  }
  private var resConnectionListener: RESConnectionListener = object : RESConnectionListener {
    override fun onOpenConnectionResult(result: Int) {
      //result 0成功  1 失败
      channel.invokeMethod("onOpenConnectionResult",result)
    }

    override fun onWriteError(errno: Int) {
      channel.invokeMethod("onWriteError",errno)
    }

    override fun onCloseConnectionResult(result: Int) {
      //result 0成功  1 失败
      channel.invokeMethod("onCloseConnectionResult",result)
    }
  }
  override fun onMethodCall(@NonNull call: MethodCall, @NonNull result: Result) {
    when(call.method){
      "getPlatformVersion" -> result.success("Android ${android.os.Build.VERSION.RELEASE}")
      //初始化推流控制器
      "initLiveConfig" -> {

        liveController = LiveController(this.activity,this.flutterPluginBinding.textureRegistry.createSurfaceTexture(),this.flutterPluginBinding.applicationContext)
        streamAVOption = StreamAVOption();
        var args:Map<*,*>? = null
        if(call.arguments is Map<*, *>){
          args = call.arguments as Map<*, *>
        }
        streamAVOption.streamUrl = args!!["rmptUrl"].toString();
        streamAVOption.videoFramerate = args!!["fps"] as Int;
        streamAVOption.videoBitrate = args!!["fps"] as Int;
        streamAVOption.videoWidth = args!!["videoWidth"] as Int;
        streamAVOption.videoHeight = args!!["videoHeight"] as Int;
        liveController.init(this.activity,streamAVOption)
        liveController.addStreamStateListener(resConnectionListener)
        liveController.javaClass.methods.forEach { method -> methods[method.name]=method }
        liveController.onError = object : ErrorListener{
          override fun onError(errorType:String, dec:String){
            var errorMsg:HashMap<String,Any> = HashMap();
            errorMsg["errorType"] = errorType;
            errorMsg["dec"] = dec;
            channel.invokeMethod("error",errorMsg)
          }
        }
        if(liveController.textureId != null){
          var res:MutableMap<String,Any?> = HashMap<String,Any?>()
          res["textureId"] = liveController.textureId;
          result.success(res)
        }
      }
      "takeScreenShot" -> {
        liveController.takeScreenShot(result)
      }
      "close" -> {
        liveController.destroy()
      }
      else -> {
        if(methods.containsKey(call.method)){
          var res:Any? = methods[call.method]!!.invoke(liveController,call.arguments)
          if(res != null){
            result.success(res);
          }else{
            result.success("return null");
          }
        }
        result.notImplemented()
      }
    }
  }

  override fun onDetachedFromEngine(@NonNull binding: FlutterPlugin.FlutterPluginBinding) {
    channel.setMethodCallHandler(null)
  }

  override fun onDetachedFromActivity() {
    TODO("Not yet implemented")
  }

  override fun onReattachedToActivityForConfigChanges(binding: ActivityPluginBinding) {
    this.activity = binding.activity;
    TODO("Not yet implemented")
  }

  override fun onAttachedToActivity(binding: ActivityPluginBinding) {
    TODO("Not yet implemented")
  }

  override fun onDetachedFromActivityForConfigChanges() {
    TODO("Not yet implemented")
  }
}
