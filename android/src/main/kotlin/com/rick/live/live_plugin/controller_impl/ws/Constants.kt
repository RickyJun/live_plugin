package com.rick.live.live_plugin.controller_impl.ws

import me.lake.librestreaming.filter.hardvideofilter.BaseHardVideoFilter
import me.lake.librestreaming.ws.StreamConfig
import me.lake.librestreaming.ws.filter.hardfilter.GPUImageBeautyFilter
import me.lake.librestreaming.ws.filter.hardfilter.extra.GPUImageCompatibleFilter


class Bitrates{
    companion object{
        fun getBitrateByType(type:String): Int {
            return when(type){
                "352x288" -> 352*288
                "600x1024"->600 * 1024
                else -> {
                    return 960*540
                }
            };
        }
    }

}
class Filters{
    companion object{
        fun getFilterByType(type:String): BaseHardVideoFilter {
            return when(type){
                "GPUImageBeautyFilter" -> GPUImageCompatibleFilter(GPUImageBeautyFilter())
                "GPUImageBeautyFilter" -> GPUImageCompatibleFilter(GPUImageBeautyFilter())
                else -> {
                    GPUImageCompatibleFilter(GPUImageBeautyFilter());
                }
            };
        }
    }
}