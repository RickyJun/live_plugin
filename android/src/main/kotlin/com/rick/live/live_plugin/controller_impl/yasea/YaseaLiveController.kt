package com.rick.live.live_plugin.controller_impl.yasea

import android.content.Context
import android.graphics.ImageFormat
import android.graphics.SurfaceTexture
import android.hardware.Camera
import android.os.Build
import androidx.annotation.RequiresApi
import com.github.faucamp.simplertmp.RtmpHandler.RtmpListener
import com.rick.live.live_plugin.LivePlugin
import com.rick.live.live_plugin.camera.CameraUtils
import com.rick.live.live_plugin.controller_interface.LiveController
import com.rick.live.live_plugin.controller_interface.StreamOption
import io.flutter.plugin.common.BinaryMessenger
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.view.TextureRegistry
import net.ossrs.yasea.SrsEncodeHandler.SrsEncodeListener
import net.ossrs.yasea.SrsEncoder
import net.ossrs.yasea.SrsPublisher
import net.ossrs.yasea.SrsRecordHandler.SrsRecordListener
import java.io.IOException
import java.net.SocketException
import java.util.ArrayList

class YaseaLiveController(val flutterTexture: TextureRegistry.SurfaceTextureEntry,val messenger:BinaryMessenger, context: Context?):LiveController(), RtmpListener,
        SrsRecordListener, SrsEncodeListener {
    lateinit var mCameraView: StreamPreview
    lateinit var mPublisher: SrsPublisher
    private lateinit var avOption:StreamOption
    private lateinit var surfaceTexture: SurfaceTexture
    lateinit var context: Context
    override fun init(context: Context?, avOption: StreamOption) {
        try {
            this.avOption = avOption
            this.context = context!!
           // surfaceTexture = flutterTexture.surfaceTexture()
//            mCameraView = StreamPreview(context)
//            mCameraView.flutterSurfaceTexture = flutterTexture.surfaceTexture()
//            mCameraView.mSurfaceTexture!!.setDefaultBufferSize(this.avOption.previewWidth,this.avOption.previewHeight)
//            mCameraView.textureId = flutterTexture.id()
//            mCameraView.surfaceCreated(null)
//            mCameraView.setFixedSize(this.avOption.previewWidth,this.avOption.previewHeight)
//            mCameraView.startRun()
//            mPublisher = SrsPublisher(mCameraView)
//            mPublisher.setEncodeHandler(SrsEncodeHandler(this))
//            mPublisher.setRtmpHandler(RtmpHandler(this))
//            mPublisher.setRecordHandler(SrsRecordHandler(this))
//            mPublisher.setPreviewResolution(this.avOption.previewWidth, this.avOption.previewHeight)
//            mPublisher.setOutputResolution(this.avOption.previewWidth, this.avOption.previewHeight) // 这里要和preview反过来
//            mPublisher.setVideoHDMode()
//            mPublisher.startCamera()
//            mCamera = openCamera()
//            startCamera()
        }catch (e:Exception){
            e.printStackTrace();
        }
    }
    //获取textureId
    override var textureId:Long? = null
        get() = flutterTexture.id()
    protected var mCamId = -1
     var mCamera: Camera? = null
    protected var mPreviewRotation = 90

    var camera: com.rick.live.live_plugin.camera.Camera? = null

    @RequiresApi(Build.VERSION_CODES.LOLLIPOP)
//    fun instantiateCamera(call: MethodCall, result: MethodChannel.Result) {
//        var cameras: MutableList<Map<String, Any>> = ArrayList()
//        cameras = CameraUtils.getAvailableCameras(LivePlugin.activity!!);
//        var cameraName:String? = null
//        for(map in cameras){
//            if(map["lensFacing"] == "front"){
//                cameraName = map["name"] as String;
//            }
//        }
//        val resolutionPreset = "medium"
//        val streamingPreset = "medium"
//        val enableAudio = true
//        var enableOpenGL = true
//      // if (call.hasArgument("enableAndroidOpenGL")) {
//            //enableOpenGL = call.argument<Boolean>("enableAndroidOpenGL")!!
//       // }
//        val dartMessenger = DartMessenger(messenger, flutterTexture.id())
//        camera = com.rick.live.live_plugin.camera.Camera(
//                LivePlugin.activity,
//                flutterTexture,
//                dartMessenger,
//                cameraName!!,
//                resolutionPreset,
//                enableAudio)
//        camera!!.open("jpeg")
//    }

    override fun startRecord():Int{
        Thread(Runnable {




        }).start()
        return 0;
    }

    // Implementation of SrsRtmpListener.
    override fun onRtmpConnecting(msg: String?) {
      //  Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_SHORT).show()
    }

    override fun onRtmpConnected(msg: String?) {
       // Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_SHORT).show()
    }

    override fun onRtmpVideoStreaming() {}

    override fun onRtmpAudioStreaming() {}

    override fun onRtmpStopped() {
        //Toast.makeText(getApplicationContext(), "Stopped", Toast.LENGTH_SHORT).show()
    }

    override fun onRtmpDisconnected() {
       // Toast.makeText(getApplicationContext(), "Disconnected", Toast.LENGTH_SHORT).show()
    }

    override fun onRtmpVideoFpsChanged(fps: Double) {
        //Log.i(MainActivity.TAG, String.format("Output Fps: %f", fps))
    }

    override fun onRtmpVideoBitrateChanged(bitrate: Double) {
        val rate = bitrate.toInt()
        if (rate / 1000 > 0) {
          //  Log.i(MainActivity.TAG, String.format("Video bitrate: %f kbps", bitrate / 1000))
        } else {
           // Log.i(MainActivity.TAG, String.format("Video bitrate: %d bps", rate))
        }
    }

    override fun onRtmpAudioBitrateChanged(bitrate: Double) {
        val rate = bitrate.toInt()
        if (rate / 1000 > 0) {
          //  Log.i(MainActivity.TAG, String.format("Audio bitrate: %f kbps", bitrate / 1000))
        } else {
           // Log.i(MainActivity.TAG, String.format("Audio bitrate: %d bps", rate))
        }
    }

    override fun onRtmpSocketException(e: SocketException?) {
       // handleException(e)
    }

    override fun onRtmpIOException(e: IOException?) {
       // handleException(e)
    }

    override fun onRtmpIllegalArgumentException(e: IllegalArgumentException?) {
       // handleException(e)
    }

    override fun onRtmpIllegalStateException(e: IllegalStateException?) {
     //   handleException(e)
    }

    // Implementation of SrsRecordHandler.

    // Implementation of SrsRecordHandler.
    override fun onRecordPause() {
      //  Toast.makeText(getApplicationContext(), "Record paused", Toast.LENGTH_SHORT).show()
    }

    override fun onRecordResume() {
      //  Toast.makeText(getApplicationContext(), "Record resumed", Toast.LENGTH_SHORT).show()
    }

    override fun onRecordStarted(msg: String) {
        //Toast.makeText(getApplicationContext(), "Recording file: $msg", Toast.LENGTH_SHORT).show()
    }

    override fun onRecordFinished(msg: String) {
       // Toast.makeText(getApplicationContext(), "MP4 file saved: $msg", Toast.LENGTH_SHORT).show()
    }

    override fun onRecordIOException(e: IOException?) {
       // handleException(e)
    }

    override fun onRecordIllegalArgumentException(e: IllegalArgumentException?) {
       // handleException(e)
    }

    // Implementation of SrsEncodeHandler.

    // Implementation of SrsEncodeHandler.
    override fun onNetworkWeak() {
       // Toast.makeText(getApplicationContext(), "Network weak", Toast.LENGTH_SHORT).show()
    }

    override fun onNetworkResume() {
       // Toast.makeText(getApplicationContext(), "Network resume", Toast.LENGTH_SHORT).show()
    }

    override fun onEncodeIllegalArgumentException(e: IllegalArgumentException?) {
      //  handleException(e)
    }

}