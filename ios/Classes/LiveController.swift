//
//  LiveController.swift
//  live_plugin
//
//  Created by wenwenjun on 2021/3/21.
//

import Foundation
import Flutter

class LiveTexture: NSObject,FlutterTexture{
    override init() {
        super.init()
    }
    var available:() -> Void? = {} as () -> Void?
    var laestCVPixelBuffer:CVPixelBuffer?

    
    func copyPixelBuffer() -> Unmanaged<CVPixelBuffer>? {
        
        return Unmanaged<CVPixelBuffer>.passRetained(laestCVPixelBuffer!)
    }
}
class LiveController: NSObject {
    override init() {
        self.texture = LiveTexture()
        super.init()
        
    }
    public var texture:LiveTexture
}
