package com.rick.live.live_plugin.controller_impl.yasea
import android.content.Context
import android.graphics.Canvas
import android.graphics.Rect
import android.graphics.SurfaceTexture
import android.hardware.Camera
import android.opengl.GLES20
import android.opengl.Matrix
import android.os.Build
import android.view.Surface
import android.view.SurfaceHolder
import androidx.annotation.RequiresApi
import com.seu.magicfilter.base.gpuimage.GPUImageFilter
import com.seu.magicfilter.utils.MagicFilterFactory
import com.seu.magicfilter.utils.MagicFilterType
import com.seu.magicfilter.utils.OpenGLUtils
import net.ossrs.yasea.SrsCameraView
import java.io.IOException
import java.util.*
import javax.microedition.khronos.opengles.GL10

/**
 * Created by Leo Ma on 2016/2/25.
 */
class StreamPreview(context: Context?) : SrsCameraView(context), SurfaceHolder {
    var flutterSurfaceTexture: SurfaceTexture? = null
        set(value) {
            mSurfaceTexture = value
            mSurface = Surface(value)
        }
    var mSurfaceTexture: SurfaceTexture? = null
    var textureId:Long? = null
    lateinit var mSurface:Surface

    override fun getHolder(): SurfaceHolder {

        return this
    }

    override fun setType(type: Int) {
        System.out.println("setType")
    }

    override fun getSurface(): Surface {
       return mSurface
    }

    override fun setSizeFromLayout() {
        System.out.println("setSizeFromLayout")
    }

    @RequiresApi(Build.VERSION_CODES.M)
    override fun lockCanvas(): Canvas {
        return mSurface.lockHardwareCanvas()
    }

    override fun lockCanvas(dirty: Rect?): Canvas {
        rect = dirty
        return mSurface.lockCanvas(dirty)
    }
    var rect:Rect? = null
    override fun getSurfaceFrame(): Rect {
        return rect!!
    }

    override fun setFixedSize(width: Int, height: Int) {
        this.askCallBacks()!!.forEach { it!!.surfaceChanged(null,0,width,height) }
    }

    override fun removeCallback(callback: SurfaceHolder.Callback?) {
        this.askCallBacks()!!.remove(callback)
    }

    override fun isCreating(): Boolean {
        return false
    }

    var callbacks: HashSet<SurfaceHolder.Callback?>? =  null
    fun askCallBacks():HashSet<SurfaceHolder.Callback?>?{
        if(this.callbacks == null){
            this.callbacks = HashSet()
        }
        return this.callbacks
    }
    override fun addCallback(callback: SurfaceHolder.Callback?) {
        askCallBacks()!!.add(callback)
        System.out.println("addCallback")
    }

    override fun setFormat(format: Int) {
        System.out.println("setFormat")
    }

    override fun unlockCanvasAndPost(canvas: Canvas?) {
        mSurface.unlockCanvasAndPost(canvas)
    }

}