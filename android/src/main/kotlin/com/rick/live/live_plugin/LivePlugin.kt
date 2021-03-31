package com.rick.live.live_plugin
import android.content.Context
import androidx.annotation.NonNull
import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result
import me.lake.librestreaming.core.listener.RESConnectionListener
import me.lake.librestreaming.ws.StreamAVOption
import java.lang.reflect.Method
import kotlin.collections.HashMap

/** LivePlugin */
class LivePlugin: FlutterPlugin, MethodCallHandler {
  /// The MethodChannel that will the communication between Flutter and native Android
  ///
  /// This local reference serves to register the plugin with the Flutter Engine and unregister it
  /// when the Flutter Engine is detached from the Activity
  private lateinit var channel: MethodChannel
  private lateinit var context: Context
  //推流controller
  private lateinit var liveController: LiveController

  //推流配置
  private lateinit var streamAVOption: StreamAVOption
  private lateinit var flutterPluginBinding: FlutterPlugin.FlutterPluginBinding
  private val methods:HashMap<String,Method> = HashMap();


  override fun onAttachedToEngine(@NonNull flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
    try {
      this.flutterPluginBinding = flutterPluginBinding
      channel = MethodChannel(flutterPluginBinding.binaryMessenger, "live_rtmp")
      channel.setMethodCallHandler(this)
      this.context = flutterPluginBinding.applicationContext;
    }catch (e:Exception){
      e.printStackTrace()
    }

    
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

        liveController = LiveController(this.flutterPluginBinding.textureRegistry.createSurfaceTexture(),this.flutterPluginBinding.applicationContext)
        streamAVOption = StreamAVOption();
        var args:Map<*,*>? = null
        if(call.arguments is Map<*, *>){
          args = call.arguments as Map<*, *>
        }
        streamAVOption.streamUrl = args!!["rmptUrl"].toString();

//        streamAVOption.videoFramerate = args!!["fps"] as Int;
//        streamAVOption.videoBitrate = args!!["bitrate"] as Int;
        streamAVOption.videoWidth = args!!["videoWidth"] as Int;
        streamAVOption.videoHeight = args!!["videoHeight"] as Int;
        streamAVOption.previewWidth = args!!["videoWidth"] as Int;
        streamAVOption.previewHeight = args!!["videoHeight"] as Int;
        StreamAVOption.recordVideoWidth = args!!["videoWidth"] as Int;
        StreamAVOption.recordVideoHeight = args!!["videoHeight"] as Int;
        liveController.init(this.context,streamAVOption)
        liveController.addStreamStateListener(resConnectionListener)
        liveController.javaClass.methods.forEach { method -> methods[method.name]=method }
        liveController.errorListener = object : ErrorListener{
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
          res["aspectRatio"] = liveController.getRESClient()!!.videoSize.width*1.0F/liveController.getRESClient()!!.videoSize.height
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
          var res:Any? = null
          if(call.arguments == null){
            res = methods[call.method]!!.invoke(liveController)
          }else{
            res = methods[call.method]!!.invoke(liveController,call.arguments)
          }

          if(res != null){
            result.success(res);
          }else{
            result.success("return null");
          }
        }else{
          result.notImplemented()
        }

      }
    }
  }

  override fun onDetachedFromEngine(@NonNull binding: FlutterPlugin.FlutterPluginBinding) {
    channel.setMethodCallHandler(null)
  }

}
