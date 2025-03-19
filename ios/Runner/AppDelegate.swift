import Flutter
import UIKit

@UIApplicationMain
@objc class AppDelegate: FlutterAppDelegate {
    
    
    private let channelName = "com.example.myapp/channel"
    private var methodChannel: FlutterMethodChannel?
    
    
    
    override func application(
        _ application: UIApplication,
        didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?
    ) -> Bool {
        GeneratedPluginRegistrant.register(with: self)
        
        let controller : FlutterViewController = window?.rootViewController as! FlutterViewController
        methodChannel = FlutterMethodChannel(name: channelName, binaryMessenger: controller.binaryMessenger)
        
        setupMethodChannel()
        registerSecurityEventCallback()
        
        RiskStub.initAppsecEverisk(stringkey)
        
        return super.application(application, didFinishLaunchingWithOptions: launchOptions)
    }
    
    
    private func setupMethodChannel() {
        methodChannel?.setMethodCallHandler { [weak self] (call: FlutterMethodCall, result: @escaping FlutterResult) in
            guard let self = self else { return }
            switch call.method {
            case "setIronSkyUserID":
                self.handleSetUserID(call: call, result: result)
            default:
                result(FlutterMethodNotImplemented)
            }
        }
    }
    
    
    private func handleSetUserID(call: FlutterMethodCall, result: FlutterResult) {
        guard let args = call.arguments as? [String: Any],
              let userID = args["userID"] as? String else {
            result(FlutterError(code: "INVALID_ARGUMENT", message: "Invalid argument", details: nil))
            return
        }
        setUserID(userID: userID, result: result)
    }
    
    private func setUserID(userID: String, result: FlutterResult) {
        RiskStub.setUserID(userID)
        result("UserID \(userID) telah diatur di iOS")
    }
    
    
    private func registerSecurityEventCallback() {
        RiskStub.registerService { data, type in
            print("Event Callback: ", data ?? "error")
            
            // Lakukan Handling Response di sini
            // Ex: Melakukan pengiriman data ke REST API Lainnya.
            
        }
    }
}
