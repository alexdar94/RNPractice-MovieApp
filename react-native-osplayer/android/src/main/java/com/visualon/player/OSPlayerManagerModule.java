package com.visualon.player;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;

import java.util.HashMap;
import java.util.Map;

import static com.visualon.player.OSPlayerUtils.copyFile;

public class OSPlayerManagerModule extends ReactContextBaseJavaModule {

    private static final String TAG = "PLAYER_MANAGER_MODULE";
    private static final String E_PLAYER_ERROR = "E_PLAYER_ERROR";
    private Map<Integer, OSPlayer> mPlayers = new HashMap<Integer, OSPlayer>();
    private int mNextId = 0;
    private ReactApplicationContext mContext = null;

    public OSPlayerManagerModule(ReactApplicationContext reactContext) {
        super(reactContext);

        mContext = reactContext;

        copyFile(reactContext, "voVidDec.dat", "voVidDec.dat");
        copyFile(reactContext, "cap.xml", "cap.xml");
    }

    @Override
    public String getName() {
        return "OSPlayerManager";
    }

    @ReactMethod
    public void createPlayer(Promise promise) {
        OSPlayer player = new OSPlayer(mContext);

        if (player.isInitialized()) {
            int id = mNextId++;

            mPlayers.put(id, player);

            promise.resolve(id);
        } else {
            promise.reject(E_PLAYER_ERROR, "Could not instantiate player.");
        }
    }

    @ReactMethod
    public void destroyPlayer(int id) {
        OSPlayer player = mPlayers.get(id);

        if (player != null) {
            player.destroy();

            mPlayers.remove(id);
        }
    }

    @ReactMethod
    // For debugging, to make sure player instances are being cleaned up.
    public void getPlayerCount(Promise promise) {
        promise.resolve(mPlayers.size());
    }

    @ReactMethod
    public void reset() {
        for (OSPlayer player : mPlayers.values()) {
            player.destroy();
        }

        mPlayers.clear();
    }

    public OSPlayer getPlayer(int id) {
        return mPlayers.get(id);
    }
}