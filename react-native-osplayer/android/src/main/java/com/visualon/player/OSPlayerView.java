package com.visualon.player;

import android.graphics.Matrix;
import android.graphics.SurfaceTexture;
import android.os.Handler;
import android.util.Log;
import android.view.Surface;
import android.view.TextureView;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.LifecycleEventListener;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.events.RCTEventEmitter;
import com.visualon.OSMPPlayer.VOCommonPlayerListener;
import com.visualon.OSMPPlayer.VOCommonPlayerListener.VO_OSMP_CB_EVENT_ID;
import com.visualon.OSMPPlayer.VOOSMPType.VO_OSMP_RETURN_CODE;
import com.yqritc.scalablevideoview.ScalableType;
import com.yqritc.scalablevideoview.ScaleManager;
import com.yqritc.scalablevideoview.Size;

public class OSPlayerView extends TextureView implements TextureView.SurfaceTextureListener, LifecycleEventListener {

    public enum Events {
        EVENT_PLAYER_INIT("onPlayerInit"),
        EVENT_LOAD_START("onVideoLoadStart"),
        EVENT_LOAD("onVideoLoad"),
        EVENT_ERROR("onVideoError"),
        EVENT_PROGRESS("onVideoProgress"),
        EVENT_SEEK_COMPLETE("onVideoSeekComplete"),
        EVENT_READY_FOR_DISPLAY("onReadyForDisplay");

        private final String mName;

        Events(final String name) {
            mName = name;
        }

        @Override
        public String toString() {
            return mName;
        }
    }

    private static final String TAG = "Player";
    private static final String EVENT_PARAM_SRC = "src";
    private static final String ERROR_PARAM_CODE = "code";
    private static final String ERROR_PARAM_TYPE = "type";
    private static final String EVENT_PARAM_CURRENT_TIME = "currentTime";
    private static final String EVENT_PARAM_DURATION = "duration";
    private static final String EVENT_PARAM_DRMID = "drmID";

    private RCTEventEmitter mEventEmitter;
    private OSPlayer mPlayer = null;
    private String mVideoUri = "";
    private String mDrm = "";
    private boolean mPaused = false;
    private boolean mMuted = false;
    private float mVolume = 1.0f;
    private int mPlayerId = -1;
    private Surface mSurface = null;
    private OSPlayerManagerModule mPlayerManager;

    private Handler mProgressUpdateHandler = new Handler();
    private Runnable mProgressUpdateRunnable = null;

    public OSPlayerView(ThemedReactContext context, OSPlayerManagerModule playerManager) {
        super(context);

        // Hide this view until the video is ready
        setAlpha(0f);

        mEventEmitter = context.getJSModule(RCTEventEmitter.class);
        mPlayerManager = playerManager;

        context.addLifecycleEventListener(this);
        setSurfaceTextureListener(this);

        mProgressUpdateRunnable = new Runnable() {
            @Override
            public void run() {
            mProgressUpdateHandler.postDelayed(mProgressUpdateRunnable, 250);

            if (mPlayer == null || !mPlayer.hasOpened() || mPlayer.isSeeking() || mPlayer.isDestroyed()) return;

            emit(Events.EVENT_PROGRESS);
            }
        };

        mProgressUpdateHandler.post(mProgressUpdateRunnable);
    }

    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surfaceTexture, int width, int height) {
        mSurface = new Surface(surfaceTexture);

        init();
    }

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
        if (mPlayer.isInitialized()) {
            mPlayer.setSurfaceChangeFinished();
        }
    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        return true;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {
    }

    @Override
    protected void onDetachedFromWindow() {
        super.onDetachedFromWindow();

        mProgressUpdateHandler.removeCallbacks(mProgressUpdateRunnable);
    }

    private static boolean isErrorCode(VO_OSMP_RETURN_CODE code) {
        return code != VO_OSMP_RETURN_CODE.VO_OSMP_ERR_NONE;
    }

    private static boolean isErrorCode(int code) {
        return code != VO_OSMP_RETURN_CODE.VO_OSMP_ERR_NONE.getValue();
    }

    private void scaleVideoSize() {
        if (mPlayer == null || !mPlayer.hasDimensions()) return;

        int videoWidth = mPlayer.getVideoWidth();
        int videoHeight = mPlayer.getVideoHeight();

        Size viewSize = new Size(getWidth(), getHeight());
        Size videoSize = new Size(videoWidth, videoHeight);
        ScaleManager scaleManager = new ScaleManager(viewSize, videoSize);
        Matrix matrix = scaleManager.getScaleMatrix(ScalableType.FIT_CENTER);
        if (matrix != null) {
            setTransform(matrix);
        }

        // Wait for the video scale to take effect before displaying the surface.
        // Otherwise, we'll see one frame of the unscaled video.
        setAlphaDelayed(1f, 50);
    }

    private void setAlphaDelayed(final float alpha, final int delay) {
        postDelayed(new Runnable() {
            @Override
            public void run() {
                setAlpha(alpha);
            }
        }, delay);
    }

    public void setSrc(String uri, String drm) {
        mVideoUri = uri;
        mDrm = drm;

        if (mPlayer == null) return;

        emit(Events.EVENT_LOAD_START);
        VO_OSMP_RETURN_CODE code = mPlayer.open(uri, drm);

        if (isErrorCode(code)) {
            emitError(code);
        }
    }

    public void setPaused(boolean paused) {
        mPaused = paused;

        applyPausedModifier();
    }

    public void setMuted(boolean muted) {
        mMuted = muted;

        applyMutedModifier();
    }

    public void setVolume(float volume) {
        mVolume = volume;

        applyVolumeModifier();
    }

    private void applyPausedModifier() {
        if (mPlayer == null) return;

        if (mPaused) {
            mPlayer.pause();
        } else {
            VO_OSMP_RETURN_CODE code = mPlayer.start();

            if (isErrorCode(code)) {
                emitError(code);
            }
        }
    }

    private void applyMutedModifier() {
        if (mPlayer == null) return;

        if (mMuted) {
            mPlayer.mute();
        } else {
            mPlayer.unmute();
        }
    }

    private void applyVolumeModifier() {
        if (mPlayer == null) return;

        mPlayer.setVolume(mVolume);
    }

    private void applyModifiers() {
        applyVolumeModifier();
        applyMutedModifier();
        applyPausedModifier();
    }

    public void seekTo(long position) {
        if (mPlayer == null) return;

        mPlayer.setPosition(position);
    }

    public void setPlayerId(int playerId) {
        mPlayerId = playerId;

        if (mPlayerId == -1) {
            mPlayer = null;
            return;
        }

        mPlayer = mPlayerManager.getPlayer(mPlayerId);

        init();
    }

    private void init() {
        if (mSurface == null || mPlayer == null || !mPlayer.isInitialized()) return;

        mPlayer.setOnEventListener(mPlayerEventListener);
        mPlayer.setSurface(mSurface);

        emit(Events.EVENT_PLAYER_INIT);
        VO_OSMP_RETURN_CODE code = mPlayer.open(mVideoUri, mDrm);

        if (isErrorCode(code)) {
            emitError(code);
        }
    }

    private void emit(Events eventName) {
        WritableMap event = Arguments.createMap();
        event.putString(EVENT_PARAM_DRMID, mPlayer.getDrmID());
        event.putString(EVENT_PARAM_SRC, mVideoUri);
        event.putInt(EVENT_PARAM_DURATION, mPlayer.getDuration());
        event.putInt(EVENT_PARAM_CURRENT_TIME, mPlayer.getPosition());

        mEventEmitter.receiveEvent(getId(), eventName.toString(), event);
    }

    private void emitError(VO_OSMP_RETURN_CODE code) {
        WritableMap event = Arguments.createMap();
        event.putInt(ERROR_PARAM_CODE, code.getValue());
        event.putString(ERROR_PARAM_TYPE, VO_OSMP_RETURN_CODE.class.getSimpleName());

        Log.e(TAG, "Emit return code error " + code + ".");

        mEventEmitter.receiveEvent(getId(), Events.EVENT_ERROR.toString(), event);
    }

    private void emitError(VO_OSMP_CB_EVENT_ID code) {
        WritableMap event = Arguments.createMap();
        event.putInt(ERROR_PARAM_CODE, code.getValue());
        event.putString(ERROR_PARAM_TYPE, VO_OSMP_CB_EVENT_ID.class.getSimpleName());

        Log.e(TAG, "Emit event id error " + code + ".");

        mEventEmitter.receiveEvent(getId(), Events.EVENT_ERROR.toString(), event);
    }

    @Override
    protected void onLayout(boolean changed, int left, int top, int right, int bottom) {
        super.onLayout(changed, left, top, right, bottom);

        if (!changed || mPlayer == null) {
            return;
        }

        scaleVideoSize();
    }

    private VOCommonPlayerListener mPlayerEventListener = new VOCommonPlayerListener() {

        public VO_OSMP_RETURN_CODE onVOEvent(VO_OSMP_CB_EVENT_ID eventId, final int param1, final int param2, Object obj) {
            switch (eventId) {
                case VO_OSMP_CB_ERROR:
                case VO_OSMP_SRC_CB_CONNECTION_FAIL:
                case VO_OSMP_SRC_CB_DOWNLOAD_FAIL:
                case VO_OSMP_SRC_CB_DRM_FAIL:
                case VO_OSMP_SRC_CB_PLAYLIST_PARSE_ERR:
                case VO_OSMP_SRC_CB_CONNECTION_REJECTED:
                case VO_OSMP_SRC_CB_DRM_NOT_SECURE:
                case VO_OSMP_SRC_CB_DRM_AV_OUT_FAIL:
                case VO_OSMP_CB_LICENSE_FAIL: {
                    emitError(eventId);
                    break;
                }

                case VO_OSMP_SRC_CB_OPEN_FINISHED: {
                    if (isErrorCode(param1)) {
                        emitError(eventId);
                        break;
                    }

                    emit(Events.EVENT_LOAD);
                    applyModifiers();
                    break;
                }

                case VO_OSMP_CB_VIDEO_RENDER_START: {
                    emit(Events.EVENT_READY_FOR_DISPLAY);
                    break;
                }

                case VO_OSMP_CB_SEEK_COMPLETE: {
                    emit(Events.EVENT_SEEK_COMPLETE);
                    break;
                }

                case VO_OSMP_CB_VIDEO_SIZE_CHANGED: {
                    post(new Runnable() {
                        @Override
                        public void run() {
                            scaleVideoSize();
                        }
                    });
                    break;
                }
            }

            return VO_OSMP_RETURN_CODE.VO_OSMP_ERR_NONE;
        }

        public VO_OSMP_RETURN_CODE onVOSyncEvent(VO_OSMP_CB_SYNC_EVENT_ID arg0, int arg1, int arg2, Object arg3) {
            return VO_OSMP_RETURN_CODE.VO_OSMP_ERR_NONE;
        }
    };

    @Override
    public void onHostPause() {
        if (mPlayer == null) return;

        mPlayer.suspend();
    }

    @Override
    public void onHostResume() {
        if (mSurface == null || mPlayer == null || !mPlayer.isInitialized()) return;

        mPlayer.resume(mSurface);
    }

    @Override
    public void onHostDestroy() {
    }
}
