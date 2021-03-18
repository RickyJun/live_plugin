package com.rick.live.live_plugin

import me.lake.librestreaming.filter.hardvideofilter.BaseHardVideoFilter
import me.lake.librestreaming.ws.filter.hardfilter.GPUImageBeautyFilter
import me.lake.librestreaming.ws.filter.hardfilter.extra.GPUImageCompatibleFilter
class Filters{
    companion object{
        fun getFilterByEnum(type:String): BaseHardVideoFilter{
            return when(type){
                "GPUImageBeautyFilter" -> GPUImageCompatibleFilter(GPUImageBeautyFilter());
                else -> {
                    GPUImageCompatibleFilter(GPUImageBeautyFilter());
                }
            };
        }
    }

}