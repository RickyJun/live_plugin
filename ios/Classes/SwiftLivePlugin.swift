import Flutter
import UIKit

class SwiftLivePlugin: NSObject, FlutterPlugin {
    override init() {
        super.init()
    }
    var liveController:LiveController?
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "live_plugin", binaryMessenger: registrar.messenger())
    let instance = SwiftLivePlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    switch call.method {
    case "init":
        self.liveController = LiveController()
        break;
    default:
        break;
    }
    result("iOS " + UIDevice.current.systemVersion)
  }
}
