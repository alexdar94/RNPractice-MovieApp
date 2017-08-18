package com.visualon.player;

import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.common.MapBuilder;
import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.annotations.ReactProp;
import com.visualon.player.OSPlayerView.Events;

import java.util.Map;

import javax.annotation.Nullable;

public class OSPlayerViewManager extends SimpleViewManager<OSPlayerView> {

    public static final String REACT_CLASS = "RCTOSPlayer";

    public static final String PROP_PLAYER_ID = "playerId";
    public static final String PROP_SRC = "src";
    public static final String PROP_SRC_URI = "uri";
    public static final String PROP_SRC_DRM = "drm";
    public static final String PROP_PAUSED = "paused";
    public static final String PROP_MUTED = "muted";
    public static final String PROP_VOLUME = "volume";
    public static final String PROP_SEEK = "seek";

    private OSPlayerManagerModule mPlayerManager;

    public OSPlayerViewManager(OSPlayerManagerModule playerManager) {
        mPlayerManager = playerManager;
    }

    @Override
    public String getName() {
        return REACT_CLASS;
    }

    @Override
    @Nullable
    public Map getExportedCustomDirectEventTypeConstants() {
        MapBuilder.Builder builder = MapBuilder.builder();
        for (Events event : Events.values()) {
            builder.put(event.toString(), MapBuilder.of("registrationName", event.toString()));
        }
        return builder.build();
    }

    @Override
    protected OSPlayerView createViewInstance(ThemedReactContext themedReactContext) {
        return new OSPlayerView(themedReactContext, mPlayerManager);
    }

    @ReactProp(name = PROP_PLAYER_ID, defaultInt = -1)
    public void setPlayerId(final OSPlayerView playerView, final int playerId) {
        playerView.setPlayerId(playerId);
    }

    @ReactProp(name = PROP_SRC)
    public void setSrc(final OSPlayerView playerView, @Nullable ReadableMap src) {
        playerView.setSrc(src.getString(PROP_SRC_URI), src.hasKey(PROP_SRC_DRM) ? src.getString(PROP_SRC_DRM) : null);
    }

    @ReactProp(name = PROP_PAUSED, defaultBoolean = false)
    public void setPaused(final OSPlayerView playerView, final boolean paused) {
        playerView.setPaused(paused);
    }

    @ReactProp(name = PROP_MUTED, defaultBoolean = false)
    public void setMuted(final OSPlayerView playerView, final boolean muted) {
        playerView.setMuted(muted);
    }

    @ReactProp(name = PROP_VOLUME, defaultFloat = 1.0f)
    public void setVolume(final OSPlayerView playerView, final float volume) {
        playerView.setVolume(volume);
    }

    @ReactProp(name = PROP_SEEK)
    public void setSeek(final OSPlayerView playerView, final float seek) {
        long milliseconds = (long) (seek * 1000.0f);

        playerView.seekTo(milliseconds);
    }
}