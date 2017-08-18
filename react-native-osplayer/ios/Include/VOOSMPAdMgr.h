/************************************************************************
VisualOn Proprietary
Copyright (c) 2013, VisualOn Incorporated. All Rights Reserved

VisualOn, Inc., USA

All data and information contained in or disclosed by this document are
confidential and proprietary information of VisualOn, and all rights
therein are expressly reserved. By accepting this material, the
recipient agrees that this material and the information contained
therein are held in confidence and in trust. The material may only be
used and/or disclosed as authorized in a license agreement controlling
such use and disclosure.
************************************************************************/
#ifndef __VOOSMP_AD_MGR_H__
#define __VOOSMP_AD_MGR_H__

#include "VOOSMPInterface.h"
#include "VOOSMPType.h"
#include "VOOSMPAdInitParam.h"
#include "VOOSMPAdCallParam.h"
#include "VOOSMPAdEventListener.h"
#include "VOOSMPTrackingEventListener.h"

/**
 * Enumeration of application notification IDs.
 */
enum VO_OSMP_APP_NOTIFICATION_ID
{
    /** Mute setting is turned on */
    VO_OSMP_APP_NOTIFICATION_MUTE = 0,

    /** Mute setting is turned off */
    VO_OSMP_APP_NOTIFICATION_UNMUTE,

    /** Playback enters fullscreen mode */
    VO_OSMP_APP_NOTIFICATION_FULLSCREEN,

    /** Playback exits fullscreen mode */
    VO_OSMP_APP_NOTIFICATION_EXIT_FULLSCREEN,

    /** User clicked on ad, causing a click-through action */
    VO_OSMP_APP_NOTIFICATION_CLICK_THROUGH,

    VO_OSMP_APP_NOTIFICATION_NUM
};

/** 
 * This type is an enumeration of all supported built-in SDKs
 */
enum VO_OSMP_SDK_ID
{
    VO_OSMP_SDK_ADOBE_HEARTBEAT = 0x00000000,
    VO_OSMP_SDK_COMSCORE        = 0x00000001,
    VO_OSMP_SDK_NIELSEN         = 0x00000002,
    VO_OSMP_SDK_DW              = 0x00000003,
    VO_OSMP_SDK_MDIALOG         = 0x00000004,
    VO_OSMP_SDK_IMADAI          = 0x00000005,
    // For internal use only:
    VO_OSMP_SDK_VMAP_VAST       = 0x7FFFFFFD,
    VO_OSMP_SDK_PASSTHROUGH     = 0x7FFFFFFE,
    VO_OSMP_SDK_NONE            = 0x7FFFFFFF
};


class VOCommonPlayerAPI VOOSMPAdMgr
{
    public:
        /** 
         * Initialize an Ad manager instance 
         *
         * <pre>
         *     This function must be called first to start a session
         * </pre>
         *
         * @param initParam [in] Refer to {@link VOOSMPAdInitParam}
         * 
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         */
        virtual VO_OSMP_RETURN_CODE init(const VOOSMPAdInitParam& iniParam) = 0;


        /** 
         * Release Ad manager resources 
         *
         * <pre>
         *     This function must be called to close a session
         * </pre>
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         */
        virtual VO_OSMP_RETURN_CODE unInit() = 0;

    
        /**
         * Set a player to the Ad manager,
         * or unset the currently set player by passing a NULL.
         * NOTE: After a player is set to Ad manager, if it's going to be
         * destroyed, it MUST be unset while it's still a valid object.
         * Calls to this method must alternate between setting / unsetting.
         * If two consecutive calls pass a player (even if the same one),
         * or if two consecutive calls pass a NULL, an error code is returned,
         * and the call has no effect.
         *
         * @param player [in] Ad player. This is typically a 
         *                    {@link VOCommonPlayer}. Set it to NULL 
         *                    to detach Ad manager from its current player
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful 
         *          or {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_UNINITIALIZE}
         *          if player has not been properly initialized,
         *          or if this method is called to set a player before
         *          the previously set player has been unset, or if it's called
         *          with NULL when no player is currently set to Ad manager.
         */
        virtual VO_OSMP_RETURN_CODE setPlayer(void* player) = 0;

        /**
         * Enable an integrated SDK, setting some initial parameters.
         * This method should be called after AdsMgr's init().
         * Refer to {@link VO_OSMP_SDK_ID} for SDK-specific parameters.
         * @param id      [in] Identifies which kind of SDK to enable.
         * @param params  [in] A HashMap with configuration parameters.
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_AD_ERR_NONE} if successful
         */
        virtual VO_OSMP_RETURN_CODE enableSDK(VO_OSMP_SDK_ID id,
                                                      void* params) = 0;

        /**
         * Get the value of a SDK configuration parameter.
         * This method should be called while the SDK is enabled.
         * @param id [in] Identifies which SDK's parameter to query
         * @return  the object set to the specified parameter, or NULL if the
         *          SDK is disabled or has no such parameter.
         *          Note: the parameter "enabled" is the only exception:
         *                if the SDK is disabled, it returns "false".
         */
        virtual void* getSDKParam(VO_OSMP_SDK_ID id, const VOOSMPString& paramName) = 0;

        /**
         * Configure an integrated SDK before each streaming session.
         * This method should be called before each call to setAdCallUrl(), 
         * to set playlist-specific values.
         * Refer to {@link VO_OSMP_SDK_ID} for SDK-specific parameters.
         * @param id     [in] Identifies which kind of SDK to configure.
         * @param params [in] A HashMap with configuration parameters.
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_AD_ERR_NONE} if
         * successful
         */
        virtual VO_OSMP_RETURN_CODE setSDKParams(VO_OSMP_SDK_ID id,
                                                         void* params) = 0;

        /* Similar to setSDKParams but used to set a single parameter.
         * Use null value to remove the parameter.
         */
        virtual VO_OSMP_RETURN_CODE setSDKParam(VO_OSMP_SDK_ID id,
                                        VOOSMPString& param, void* value) = 0;

        virtual VO_OSMP_RETURN_CODE execSDKAction(VO_OSMP_SDK_ID id,
                                        VOOSMPString& action) = 0;
        /**
         * Disable an integrated SDK.
         * This method should be called before unInit().
         * @param id [in] Identifies which SDK to disable.
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_AD_ERR_NONE} if
         * successful
         */
        virtual VO_OSMP_RETURN_CODE disableSDK(VO_OSMP_SDK_ID id) = 0;


        /**
         * Specify an Ad URL
         *
         * @param adCallParam [in] Refer to {@link VOOSMPAdCallParam}
         * 
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         */
        virtual VO_OSMP_RETURN_CODE setAdCallUrl(const VOOSMPAdCallParam& adCallParam) = 0;


        /**
         * Set an Ad event listener 
         *
         * @param listener [in] Refer to {@link VOOSMPAdEventListener}
         * 
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         */
        virtual VO_OSMP_RETURN_CODE setAdEventListener(VOOSMPAdEventListener* listener) = 0;


        /**
         * Set a Tracking event listener
         *
         * @param listener [in] Refer to {@link VOOSMPTrackingEventListener}
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         */
        virtual VO_OSMP_RETURN_CODE setTrackingEventListener(VOOSMPTrackingEventListener* listener) = 0;


        /** 
         * Request a tracking event to be tracked when the current ad reaches
         * the specified position.
         *
         * @param pos  [in] The position (in ms) to trigger the event.
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         */
        virtual VO_OSMP_RETURN_CODE requestAdReachedPositionTrackingEvent(long pos) = 0;


        /**
         * Request a tracking event to be tracked when the amount of ad viewed
         * at normal speed at least once reaches the specified percentage
         *
         * @param pct  [in] The % viewed to trigger the event.
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         */
        virtual VO_OSMP_RETURN_CODE requestAdPercentageViewedTrackingEvent(double pct) = 0;


        /**
         * Skip the current playing Ad. This function does not have any effect
         * if it is currently playing the content.
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         */
        virtual VO_OSMP_RETURN_CODE skipAd() = 0;


        /** 
         * Get Ad playback position
         *
         * @return  Ad playback position if it is currently playing an Ad, -1 
         *          if it is playing the content. 
         */
        virtual long getAdPosition() = 0;


        /** 
         * Notify application events to Ad manager
         *
         * @param param1 [in] first parameter associated with the notification.
         *                    The definition depends on the notification ID.
         *          
         * @param param2 [in] second parameter associated with the notification.
         *                    The definition depends on the notification ID.
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if event is processed
         *          successfully
         */
        virtual VO_OSMP_RETURN_CODE onAppNotify(VO_OSMP_APP_NOTIFICATION_ID id, void* param1, void* param2) = 0;

    protected:
        VOOSMPAdMgr() {}
        virtual ~VOOSMPAdMgr() {}
};

class VOCommonPlayerAPI VOOSMPAdMgrFactory
{
    public:
        /** Create a new Ad manager instance */
        static VOOSMPAdMgr* createInstance();

        /** Destroy an Ad manager instance */
        static void destroyInstance(VOOSMPAdMgr*);
};

#endif
