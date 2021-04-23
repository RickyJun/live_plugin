package com.rick.live.live_plugin
import android.app.Activity
import android.content.Context
import android.graphics.SurfaceTexture
import android.os.Build
import android.util.Size
import androidx.annotation.NonNull
import androidx.annotation.RequiresApi
import com.rick.live.live_plugin.controller_impl.ws.ErrorListener
import com.rick.live.live_plugin.controller_impl.ws.WSLiveController
import com.rick.live.live_plugin.controller_interface.LiveController
import com.rick.live.live_plugin.controller_interface.StreamOption
import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result
import io.flutter.view.TextureRegistry
import me.lake.librestreaming.core.listener.RESConnectionListener
import me.lake.librestreaming.ws.StreamAVOption
import java.io.BufferedInputStream
import java.lang.reflect.Method

interface ToListener {
  fun to(surfaceTexture: SurfaceTexture);
}
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
  companion object{
    var activity:Activity? = null
    var bin: BufferedInputStream? = null
    var toListener:ToListener? = null
    var surfaceTextureEntry: TextureRegistry.SurfaceTextureEntry? = null
  }
  //推流配置
  private lateinit var streamAVOption: StreamOption
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
  lateinit var flutterSurfacetexture: TextureRegistry.SurfaceTextureEntry
  @RequiresApi(Build.VERSION_CODES.LOLLIPOP)
  override fun onMethodCall(@NonNull call: MethodCall, @NonNull result: Result) {
    when(call.method){
      "getPlatformVersion" -> result.success("Android ${android.os.Build.VERSION.RELEASE}")
      //初始化推流控制器
      "initLiveConfig" -> {
        liveController = WSLiveController(flutterSurfacetexture,this.flutterPluginBinding.binaryMessenger, this.flutterPluginBinding.applicationContext)
        liveController.errorListener = object : ErrorListener {
          override fun onError(errorType:String, dec:String){
            var errorMsg:HashMap<String,Any> = HashMap();
            errorMsg["errorType"] = errorType;
            errorMsg["dec"] = dec;
            channel.invokeMethod("error",errorMsg)
          }
        }
        streamAVOption = StreamOption();
        var args:Map<*,*>? = null
        if(call.arguments is Map<*, *>){
          args = call.arguments as Map<*, *>
        }
        streamAVOption.streamUrl = args!!["rmptUrl"].toString();
        streamAVOption.videoFramerate = args["fps"] as Int;
        streamAVOption.videoBitrate = args["bitrate"] as Int;
        liveController.init(activity,streamAVOption,result)
        liveController.javaClass.methods.forEach { method -> methods[method.name]=method }
      }
      "textureId" -> {
        flutterSurfacetexture = this.flutterPluginBinding.textureRegistry.createSurfaceTexture()
        val res:MutableMap<String,Any?> = HashMap<String,Any?>()
        res["textureId"] = flutterSurfacetexture.id();
        result.success(res)
      }
      else -> {
        if(methods.containsKey(call.method)){
          if(call.arguments == null){
            methods[call.method]!!.invoke(liveController,result)
          }else{
            methods[call.method]!!.invoke(liveController,result,call.arguments)
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
