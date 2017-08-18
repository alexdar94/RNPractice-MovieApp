package com.visualon.player;

import android.os.Build;

import android.content.Context;
import android.util.Log;
import android.view.Surface;

import com.visualon.OSMPPlayer.VOCommonPlayer;
import com.visualon.OSMPPlayer.VOCommonPlayerListener;
import com.visualon.OSMPPlayer.VOOSMPInitParam;
import com.visualon.OSMPPlayer.VOOSMPOpenParam;
import com.visualon.OSMPPlayer.VOOSMPType;
import com.visualon.OSMPPlayer.VOOSMPVerificationInfo;
import com.visualon.OSMPPlayerImpl.VOCommonPlayerImpl;

import static com.visualon.player.OSPlayerUtils.getUserPath;
import static com.visualon.player.OSPlayerUtils.isErrorCode;
import static com.visualon.player.OSPlayerUtils.isValidUri;

public class OSPlayer {
    private static final boolean m_bUseOldVersion = Build.VERSION.SDK_INT < Build.VERSION_CODES.JELLY_BEAN_MR2;

    private static final String TAG = "OSPlayer";
    private final String DRM_LIB_NAME = m_bUseOldVersion ? "voDRM_Verimatrix_AES128_S42" : "voDRM_Verimatrix_AES128_S43";
    private final String DRM_API_NAME = "voGetVerimatrixDRMAPI";

    private VOCommonPlayer mPlayer = null;
    private String mVideoUri = null;
    private boolean mInitialized = false;
    private boolean mHasOpened = false;
    private int mVideoWidth = 0;
    private int mVideoHeight = 0;
    private VOCommonPlayerListener mListener = null;
    private String uuid = null;
    private boolean mHasSurface = false;
    private boolean mIsSeeking = false;
    private String drmID = null;
    private boolean mIsDestroyed=false;

    public VOCommonPlayer getPlayerInstance() {
        return mPlayer;
    }

    public String getDrmID(){
        return drmID;
    }

    public boolean isInitialized() {
        return mInitialized;
    }

    public boolean hasDimensions() {
        return mVideoWidth > 0 && mVideoHeight > 0;
    }

    public boolean hasOpened() {
        return mHasOpened;
    }

    public boolean isSeeking() {
        return mIsSeeking;
    }

    public boolean isDestroyed() {
        return mIsDestroyed;
    }

    public int getVideoWidth() { return mVideoWidth; }

    public int getVideoHeight() { return mVideoHeight; }

    public int getDuration() {
        if (mPlayer == null || mIsDestroyed == true) return 0;
        // Unsafe cast, but should work for videos < ~24 days long
        if( mPlayer != null && !mIsDestroyed ) {
            return (int) (mPlayer.getDuration() / 1000);
        } else {
            return 0;
        }
    }

    public int getPosition() {
        if (mPlayer == null) return 0;

        // Unsafe cast, but should work for videos < ~24 days long
        return (int) (mPlayer.getPosition() / 1000);
    }

    public void setPosition(long position) {
        if (mPlayer == null) return;

        mPlayer.setPosition(position);
        mIsSeeking = true;
    }

    public void setVolume(float volume) {
        if (mPlayer == null) return;

        mPlayer.setVolume(volume);
    }

    public VOOSMPType.VO_OSMP_RETURN_CODE start() {
        if (!mInitialized) return VOOSMPType.VO_OSMP_RETURN_CODE.VO_OSMP_ERR_NONE;

        return mPlayer.start();
    }

    public void suspend() {
        if (mPlayer == null) return;

        mPlayer.suspend(false);
    }

    public void resume(Surface surface) {
        if (mPlayer == null) return;

        mPlayer.resume(surface);
    }

    public void pause() {
        if (mPlayer == null) return;

        mPlayer.pause();
    }

    public void mute() {
        if (mPlayer == null) return;

        mPlayer.mute();
    }

    public void unmute() {
        if (mPlayer == null) return;

        mPlayer.unmute();
    }

    public void setSurface(Surface surface) {
        mPlayer.setSurface(surface);

        mHasSurface = true;
    }

    public void setSurfaceChangeFinished() {
        mPlayer.setSurfaceChangeFinished();
    }

    public void setOnEventListener(VOCommonPlayerListener listener) {
        mListener = listener;
    }

    private VOCommonPlayerListener mListenerProxy = new VOCommonPlayerListener() {
        @Override
        public VOOSMPType.VO_OSMP_RETURN_CODE onVOEvent(VO_OSMP_CB_EVENT_ID eventId, final int param1, final int param2, Object obj) {
            switch (eventId) {
                case VO_OSMP_SRC_CB_OPEN_FINISHED: {
                    if (isErrorCode(param1)) break;

                    mHasOpened = true;
                    break;
                }

                case VO_OSMP_CB_VIDEO_SIZE_CHANGED: {
                    mVideoWidth = param1;
                    mVideoHeight = param2;
                    break;
                }

                case VO_OSMP_CB_SEEK_COMPLETE: {
                    mIsSeeking = false;
                    break;
                }
            }

            if (mListener != null) {
                return mListener.onVOEvent(eventId, param1, param2, obj);
            }

            return VOOSMPType.VO_OSMP_RETURN_CODE.VO_OSMP_ERR_NONE;
        }

        @Override
        public VOOSMPType.VO_OSMP_RETURN_CODE onVOSyncEvent(VO_OSMP_CB_SYNC_EVENT_ID eventId, int param1, int param2, Object obj) {
            return VOOSMPType.VO_OSMP_RETURN_CODE.VO_OSMP_ERR_NONE;
        }
    };

    OSPlayer(Context context) {
        mPlayer = new VOCommonPlayerImpl();
        mIsDestroyed = false;

        mPlayer.setOnEventListener(mListenerProxy);

        if (uuid == null) {
            uuid = new com.visualon.OSMPUtils.voOSUniqID(context).getDrmUUIDString();
        }

        // Setting a new unique DRM ID allows us to handle reloading. This isn't necessary if we
        // don't care about providing a good developer experience, since the SDK will generate
        // a uuid automatically.
        mPlayer.setDRMUniqueIdentifier(uuid);

        String cfgPath = getUserPath(context) + "/";
        String apkPath = getUserPath(context) + "/lib/";
        String capFile = cfgPath + "cap.xml";

        VOOSMPType.VO_OSMP_PLAYER_ENGINE eEngineType = VOOSMPType.VO_OSMP_PLAYER_ENGINE.VO_OSMP_VOME2_PLAYER;

        VOOSMPInitParam init = new VOOSMPInitParam();
        init.setContext(context);
        init.setLibraryPath(apkPath);

        VOOSMPType.VO_OSMP_RETURN_CODE code = mPlayer.init(eEngineType, init);

        if (isErrorCode(code)) {
            // This error code is not reported at the moment - the caller will check isInitialized
            // to determine if an error occurred or not.
            Log.e(TAG, "Failed to initialize player with error " + code + ".");
            destroy();

            return;
        }

        mPlayer.setDeviceCapabilityByFile(capFile);
        mPlayer.setLicenseFilePath(cfgPath);
        mPlayer.setInitialBufferingTime(1000);
        mPlayer.enableLowLatencyVideo(true);
        mPlayer.setInitialBitrate(800000);

        // Causes SIGSEGV
        mPlayer.setDRMLibrary(DRM_LIB_NAME, DRM_API_NAME);
        this.drmID = mPlayer.getDRMUniqueIdentifier();
        mInitialized = true;
    }

    public VOOSMPType.VO_OSMP_RETURN_CODE open(String uri, String drm) {
        if (!isValidUri(uri) || uri.equals(mVideoUri) || !mInitialized || !mHasSurface) {
            return VOOSMPType.VO_OSMP_RETURN_CODE.VO_OSMP_ERR_NONE;
        }

        if (isValidUri(mVideoUri)) {
            mPlayer.stop();
            mPlayer.close();
        }

        if (drm != null) {
            VOOSMPVerificationInfo info = new VOOSMPVerificationInfo();
            info.setVerificationString(drm);
            info.setDataFlag(1);

            mPlayer.setDRMVerificationInfo(info);
        }

        VOOSMPOpenParam openParam = new VOOSMPOpenParam();
        openParam.setDecoderType(VOOSMPType.VO_OSMP_DECODER_TYPE.VO_OSMP_DEC_VIDEO_SW.getValue() |
                VOOSMPType.VO_OSMP_DECODER_TYPE.VO_OSMP_DEC_AUDIO_SW.getValue());

        VOOSMPType.VO_OSMP_RETURN_CODE code = mPlayer.open(uri, VOOSMPType.VO_OSMP_SRC_FLAG.VO_OSMP_FLAG_SRC_OPEN_ASYNC,
                VOOSMPType.VO_OSMP_SRC_FORMAT.VO_OSMP_SRC_AUTO_DETECT, openParam);

        if (isErrorCode(code)) {
            Log.e(TAG, "Failed to open player with error " + code + ". Src is " + uri + " " + drm + ".");
        } else {
            mVideoUri = uri;
        }

        return code;
    }

    public void destroy() {
        mIsDestroyed=true;
        if (mPlayer != null) {
            mPlayer.stop();
            mPlayer.close();
            mPlayer.destroy();
        }

        mPlayer = null;
        mVideoUri = null;
        mInitialized = false;
    }
}
