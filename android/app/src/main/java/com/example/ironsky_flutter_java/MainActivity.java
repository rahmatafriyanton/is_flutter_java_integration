package com.example.ironsky_flutter_java;

import android.Manifest;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;

import com.appsec.everisk.core.CallBack;
import com.appsec.everisk.core.RiskStubAPI;
import com.appsec.everisk.core.Type;

import io.flutter.embedding.android.FlutterActivity;
import io.flutter.plugin.common.MethodChannel;

import org.json.JSONObject;

public class MainActivity extends FlutterActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        initPermissions();
        registerSecurityEventCallback();
        setupMethodChannel();
        initializeRiskStubAPI();
    }

    private void initPermissions() {
        String[] reqPermissions = {
                Manifest.permission.ACCESS_FINE_LOCATION,
                Manifest.permission.ACCESS_COARSE_LOCATION,
                Manifest.permission.READ_PHONE_STATE,
                Manifest.permission.ACCESS_NETWORK_STATE,
                Manifest.permission.ACCESS_WIFI_STATE
        };

        RiskStubAPI.initAppsecPermission(this, reqPermissions);
    }

    private void setupMethodChannel() {
        String channel = "com.example.myapp/channel";  // Ganti dengan nama channel yang sesuai

        if (getFlutterEngine() != null && getFlutterEngine().getDartExecutor() != null) {
            new MethodChannel(getFlutterEngine().getDartExecutor().getBinaryMessenger(), channel).setMethodCallHandler((call, result) -> {
                switch (call.method) {
                    case "setIronSkyUserID":
                        String userID = call.argument("userID");
                        if (userID != null) {
                            String nativeResult = setUserID(userID);
                            if (nativeResult != null) {
                                result.success(nativeResult);
                            } else {
                                result.error("UNAVAILABLE", "Native function not available.", null);
                            }
                        } else {
                            result.error("INVALID_ARGUMENT", "Argument 'userID' is required.", null);
                        }
                        break;

                    default:
                        result.notImplemented();
                        break;
                }
            });
        }
    }

    private String setUserID(String userID) {
        try {
            RiskStubAPI.setUserId(this, userID);
            return "Success";
        } catch (Exception e) {
            Log.e("nativeFunction", "Error setting user ID", e);
            return null;
        }
    }

    private void registerSecurityEventCallback() {
        RiskStubAPI.initEventResponse(this);

        RiskStubAPI.registerService(new CallBack() {
            @Override
            public void onResult(Type type, Object result) {
                JSONObject jsonObject = (JSONObject) result;
                String responseI18n = jsonObject.optString("responseI18n");
                String key = jsonObject.optString("key");

                Log.d("responseI18n", responseI18n);
                Log.d("ruleengine", "onReceive:" + key);

                int responseType = jsonObject.optInt("responseType", -1);

                // Lakukan Handling Response di sini
                // Ex: Melakukan pengiriman data ke REST API Lainnya.
            }
        }, Type.RISKEVENT, 0.5);
    }

    private void initializeRiskStubAPI() {
        String key = "+a88XBOU/bvfk6al7Sliem8RKQWb/N5F+LkjPlX44KxGiVjJTm/QZ1f1Pgawoioacgpk8LKCyN/qlcWti5DRm8PilTe/J/hOWKg8kJ6MR2KCbW++kI2ecX+SThK0OztOQMs2U5cjWUM4s/pavLRTh1TP4wmFfSnDgtC03jxbGUPpPeP8vc1FZXyRqNt4AI6U7qgC0iMZtkFy8ZS4s6XvDW7UrIjGyecb8pRBv8xFyCuSgdvWQ6FrCH3un8A9ASWL";
        boolean isInit = RiskStubAPI.initAppsecEverisk(this, key);
        Log.d("Status", "is init everisk: " + isInit);
    }

    private void registerEventReceiver() {
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction("SecEventDetected");
    }
}
