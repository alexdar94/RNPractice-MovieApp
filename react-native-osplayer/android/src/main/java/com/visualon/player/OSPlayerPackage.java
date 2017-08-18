package com.visualon.player;

import android.os.Build;

import com.facebook.react.ReactPackage;
import com.facebook.react.bridge.JavaScriptModule;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.uimanager.ViewManager;
import com.visualon.OSMPUtils.voLog;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class OSPlayerPackage implements ReactPackage {

    private static final boolean m_bUseOldVersion = Build.VERSION.SDK_INT < Build.VERSION_CODES.JELLY_BEAN_MR2;

    static {
        voLog.v("DRM", "Before loadLibrary, libViewRightWebClient");
        try {
            // make sure loading correct lib according to the current platform
            if (m_bUseOldVersion) {
                System.loadLibrary("ViewRightWebClient");
            } else {
                System.loadLibrary("ViewRightVideoMarkClient");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } catch (UnsatisfiedLinkError e) {
            e.printStackTrace();
        }

        voLog.i("DRM", "After loadLibrary, libViewRightWebClient");
    }

    private OSPlayerManagerModule mPlayerManager;

    private OSPlayerManagerModule getPlayerManager(ReactApplicationContext reactContext) {
        if (mPlayerManager == null) {
            mPlayerManager = new OSPlayerManagerModule(reactContext);
        }

        return mPlayerManager;
    }

    @Override
    public List<NativeModule> createNativeModules(ReactApplicationContext reactContext) {
        List<NativeModule> modules = new ArrayList<>();

        modules.add(getPlayerManager(reactContext));

        return modules;
    }

    @Override
    public List<Class<? extends JavaScriptModule>> createJSModules() {
        return Collections.emptyList();
    }

    @Override
    public List<ViewManager> createViewManagers(ReactApplicationContext reactContext) {
        return Arrays.<ViewManager>asList(new OSPlayerViewManager(getPlayerManager(reactContext)));
    }
}