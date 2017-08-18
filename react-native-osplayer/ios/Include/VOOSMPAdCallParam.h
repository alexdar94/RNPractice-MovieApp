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
#ifndef __VOOSMP_AD_CALL_PARM_H__
#define __VOOSMP_AD_CALL_PARM_H__

#include "VOOSMPInterface.h"
#include "VOOSMPType.h"
#include "VOOSMPString.h"

enum VO_OSMP_AD_CALL_TYPE
{
    /** VAST preroll URL - Client-Stitched */
    VO_OSMP_AD_CALL_VAST = 0,

    /** VMAP URL - Client-Stitched */
    VO_OSMP_AD_CALL_VMAP,

    /** Ad.xml format URL - Client-Stitched */
    VO_OSMP_AD_CALL_ADSXML,

    /** Google IMA - Client-Stitched */
    VO_OSMP_AD_CALL_IMA,
    
    /** Google IMA - Dynamic Ad Insertion - Server-Stitched */
    VO_OSMP_AD_CALL_IMADAI,

    /** Google mDialog - Server-Stitched */
    VO_OSMP_AD_CALL_MDIALOG,

    /** AdFlow does not intervene to trigger ad insertion. This is for plain
        content playback or for server-stitched ads where ad related info
        comes from DASH manifest / HLS playlist */
    VO_OSMP_AD_CALL_NONE,
    
    VO_OSMP_AD_CALL_NUM
};

enum VO_OSMP_AD_OPEN_FLAG
{
    VO_ADSMANAGER_OPENFLAG_UNKNOWN         = 0x00000000,
    VO_ADSMANAGER_OPENFLAG_PID         	   = 0x00000001,
    VO_ADSMANAGER_OPENFLAG_URI_LIVE        = 0x00000002,
    VO_ADSMANAGER_OPENFLAG_URI_RAW         = 0x00000004,//Indicate the pSource will be VO_ADSMANAGER_SOURCE_PID* , pPID should be a URI of raw content
    VO_ADSMANAGER_OPENFLAG_URI_VAST        = 0x00000008,//Indicate the pSource will be VO_ADSMANAGER_SOURCE_PID* , pPID should be a URI of VAST file
    VO_ADSMANAGER_OPENFLAG_PID_LIVE        = 0x000000010,//Indicate the pSource will be VO_ADSMANAGER_SOURCE_PID* , pPID should be a ID can be converted to ...
    VO_ADSMANAGER_OPENFLAG_PID_DVR         = 0x000000020//Indicate the pSource will be VO_ADSMANAGER_SOURCE_PID* , pPID should be a ID can be converted to ...
};

class VOCommonPlayerAPI VOOSMPIMASettings
{
public:
    VOOSMPIMASettings():mContext(NULL),mViewController(NULL),mView(NULL) { }
    ~VOOSMPIMASettings() { }
    /**
     * Set view. IMA for iOS and Android both need view
     */
    void setView(void* view) { mView = view; }
    /**
     * Set iOS player view controller
     */
    void setViewController(void* ctrl) { mViewController = ctrl; }
    /**
     * Set Android player activity
     */
    void setContext(void* context) { mContext = context; }
    /**
     * Get view
     */
    void* getView() { return mView; }
    /**
     * Get iOS player view controller
     */
    void* getViewController() { return mViewController; }
    /**
     * Get Android player's activity
     */
    void* getContext() { return mContext; }
private:
    void* mContext; // for Android only
    void* mViewController; // for iOS only
    void* mView;
};

class VOCommonPlayerAPI VOOSMPAdCallParam
{
    public:
        VOOSMPAdCallParam();
        ~VOOSMPAdCallParam();

        /**
         * Get Ad call URL setting
         *
         * @return  Ad call URL
         */
        VOOSMPString getAdCallUrl() const;

        /**
         * Get Ad call URL type
         *
         * @return  Ad call URL type
         */
        VO_OSMP_AD_CALL_TYPE getAdCallType() const;

        /**
         * Specify Ad call URL 
         *
         * @param  url [in] Ad call URL
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         */
        VO_OSMP_RETURN_CODE setAdCallUrl(const VOOSMPString&  url);

        /**
         * Specify the type of Ad call URL 
         *
         * @param  type [in] Ad call URL type. Refer to {@link VO_OSMP_AD_CALL_TYPE}
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         */
        VO_OSMP_RETURN_CODE setAdCallType(VO_OSMP_AD_CALL_TYPE type);

        /**
         * Specify required settings for IMA
         *
         * @param  settings [in] Required settings and objects for IMA. Refer to {@link VOOSMPIMASettings}
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         */ 
        VO_OSMP_RETURN_CODE setIMASettings(VOOSMPIMASettings settings);

        /**
         * Get required settings for IMA
         *
         * @return  {@link VOOSMPIMASettings} if successful
         */
        VOOSMPIMASettings getIMASettings();
    
    private:
        VOOSMPString _adCallUrl;
        VO_OSMP_AD_CALL_TYPE _adCallType;
        VOOSMPIMASettings _IMASettings;
};

#endif
