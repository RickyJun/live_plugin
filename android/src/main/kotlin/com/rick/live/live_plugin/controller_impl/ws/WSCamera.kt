package com.rick.live.live_plugin.controller_impl.ws

import android.graphics.SurfaceTexture
import com.rick.live.live_plugin.LivePlugin
import com.rick.live.live_plugin.camera.Camera
import com.rick.live.live_plugin.camera.CameraUtils
import com.rick.live.live_plugin.camera.DartMessenger
import io.flutter.plugin.common.BinaryMessenger
import io.flutter.view.TextureRegistry
import me.lake.librestreaming.client.video.CameraDelegate
import me.lake.librestreaming.model.RESCoreParameters

class WSCamera(val flutterTexture: TextureRegistry.SurfaceTextureEntry, val messenger: BinaryMessenger): CameraDelegate {
    var camera:Camera? = null
    var cameraResolutionPreset:String? = null
    var cameraName:String? =null
    var lensIndex:Int = 0;
    var lens:ArrayList<String> = ArrayList();
    init {
        lens.add("front");
        lens.add("back");
        lens.add("external");
        instantiateCamera(null)
    }
    private fun instantiateCamera(resolutionPreset:String?) {
        var cameras: MutableList<Map<String, Any>> = java.util.ArrayList()
        cameras = CameraUtils.getAvailableCameras(LivePlugin.activity!!);
        for(map in cameras){
            if(map["lensFacing"] == lens[lensIndex]){
                cameraName = map["name"] as String;
            }
        }
        cameraResolutionPreset = resolutionPreset
        if(cameraResolutionPreset == null){
            cameraResolutionPreset = "high"
        }
        val enableAudio = true
        val dartMessenger = DartMessenger(messenger, flutterTexture.id())
        camera = Camera(
                LivePlugin.activity,
                null,
                dartMessenger,
                cameraName!!,
                cameraResolutionPreset,
                enableAudio)
    }

    override fun swapCamera() {
        camera = null;
        lensIndex = (lensIndex+1)%3
        instantiateCamera(null)
    }

    override fun selectCameraFpsRange(coreParameters: RESCoreParameters?) {
        coreParameters!!.previewMinFps = camera!!.fpsRange.getLower()
        coreParameters.previewMaxFps = camera!!.fpsRange.getUpper()
    }



    override fun open(imageFormatGroup: String?, cam: SurfaceTexture?) {
        camera!!.open(imageFormatGroup,cam)
    }

    override fun selectCameraColorFormat(coreParameters: RESCoreParameters?) {
        coreParameters!!.previewColorFormat = Camera.supportedImageFormats[camera!!.imageFormatGroup]!!
    }

    override fun close() {
        camera!!.close()
    }

    override fun dispose() {
        camera!!.dispose()
    }
}