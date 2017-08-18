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
#ifndef __OSMP_TRACKING_EVENT_LISTENER_H__
#define __OSMP_TRACKING_EVENT_LISTENER_H__

#include "VOOSMPString.h"
#include "VOOSMPType.h"

/**
 * Enumeration of Tracking event IDs.
 */
enum VO_OSMP_TRACKING_EVENT_ID 
{
    /** Open operation completed */
    VO_OSMP_TRACKING_EVENT_OPEN_COMPLETE = 0,

    /** Run() was executed */
    VO_OSMP_TRACKING_EVENT_RUN,

    /** Started playing an Ad or a Content period, but not necessarily at
        the beginning of the period. For example, this event is triggered at
        a seek target when seeking from a different content period. */
    VO_OSMP_TRACKING_EVENT_START,

    /** Stopped playing an Ad or a Content period, but not necessarily at the
        end of the period. For example, this event is also triggered after a
        skipAd and when seek's target is in a different content period. */
    VO_OSMP_TRACKING_EVENT_END,

    /** Playback session was stopped by the viewer or after completion */
    VO_OSMP_TRACKING_EVENT_STOP,

    /** Playback was paused */
    VO_OSMP_TRACKING_EVENT_PAUSE,

    /** Playback leaves paused state */
    VO_OSMP_TRACKING_EVENT_UNPAUSE,

    /** Audio was muted */
    VO_OSMP_TRACKING_EVENT_MUTE,

    /** Audio was unmuted */
    VO_OSMP_TRACKING_EVENT_UNMUTE,

    /** Seek action requested */
    VO_OSMP_TRACKING_EVENT_SEEK,

    /** Seek action ended */
    VO_OSMP_TRACKING_EVENT_SEEK_END,

    /** SkipAd control was activated */
    VO_OSMP_TRACKING_EVENT_SKIP_AD,

    /** Player expanded to full screen */
    VO_OSMP_TRACKING_EVENT_FULLSCREEN,

    /** Player left full screen mode */
    VO_OSMP_TRACKING_EVENT_EXIT_FULLSCREEN,

    /** Error. Event info contains VAST/VMAP error code */
    VO_OSMP_TRACKING_EVENT_ERROR,

    /** Playback reached a specified position in the Ad period, specified in ms
     * (requested event) */
    VO_OSMP_TRACKING_EVENT_REACHED_AD_POSITION_MS,

    /** Viewed a cumulative amount of a period (specified as a %)
     *  at normal speed at least once (requested event) */
    VO_OSMP_TRACKING_EVENT_VIEWED_AD_DURATION_PCT,

    /** Suspend() was executed */
    VO_OSMP_TRACKING_EVENT_SUSPEND,

    /** Resume() was executed */
    VO_OSMP_TRACKING_EVENT_RESUME,

    /** Buffering (of audio or video) started */
    VO_OSMP_TRACKING_EVENT_BUF_START,

    /** Buffering (of audio or video) ended */
    VO_OSMP_TRACKING_EVENT_BUF_END,

    /** User clicked on Ad, generating click-through response */
    VO_OSMP_TRACKING_EVENT_CLICK_THROUGH,

    /** Close() was executed */
    VO_OSMP_TRACKING_EVENT_CLOSE,

    /** Event generated about twice per second when playing/paused,
        but not when suspended */
    VO_OSMP_TRACKING_EVENT_HEARTBEAT,

    /** Subtitles/captions became available and enabled. This may happen
        when playback starts, or when the user toggles a CC button */
    VO_OSMP_TRACKING_EVENT_CAPTION_ON,

    /** Subtitles/captions became available or disabled. This may happen
        before playback starts, or when the user toggles a CC button */
    VO_OSMP_TRACKING_EVENT_CAPTION_OFF,

    VO_OSMP_TRACKING_EVENT_NUM
};

/** Interface of info returned associated with a tracking event */
class VOOSMPTrackingEventInfo
{
    public: 
        /** Returns the event type enum */
        virtual VO_OSMP_TRACKING_EVENT_ID getType() const = 0;

        /** Returns the event type string */
        virtual VOOSMPString getTypeStr() const = 0;

        /** Returns true if the event is for an Ad period or Ad Break.
         *  (some events can be triggered during Content playback) */
        virtual bool isAd() const = 0;

        /** True if the event is for a preroll Ad. */
        virtual bool isPreroll() const = 0;

        /** True if the event is for a midroll Ad. */
        virtual bool isMidroll() const = 0;

        /** True if the event is for a postroll Ad. */
        virtual bool isPostroll() const = 0;

        /** Returns true for a START event at the beginning of any
            ad or content period */
        virtual bool isPeriodStart() const = 0;

        /** Returns true for an END event at the end of any
            ad or content period */
        virtual bool isPeriodEnd() const = 0;

        /** Returns true for the start of the first period (the first ad of a
            preroll ad break, or the start of content if there's no preroll) */
        virtual bool isVideoStart() const = 0;

        /** Returns true for the end of the last period (the last ad of a
            postroll ad break, or the end of content if there's no postroll) */
        virtual bool isVideoEnd() const = 0;

        /** Returns true for the start of the first content period */
        virtual bool isContentStart() const = 0;

        /** Returns true for the end of the last content period */
        virtual bool isContentEnd() const = 0;

        /** Returns true for the start of an ad break */
        virtual bool isAdBreakStart() const = 0;

        /** Returns true for the end of an ad break */
        virtual bool isAdBreakEnd() const = 0;

        /** Returns true for the start of the first preroll ad */
        virtual bool isPrerollStart() const = 0;

        /** Returns true for the end of the last preroll ad */
        virtual bool isPrerollEnd() const = 0;

        /** Returns true for the start of the first ad of each midroll */
        virtual bool isMidrollStart() const = 0;

        /** Returns true for the end of the last ad of each midroll */
        virtual bool isMidrollEnd() const = 0;

        /** Returns true for the start of the first postroll ad */
        virtual bool isPostrollStart() const = 0;

        /** Returns true for the end of the last postroll ad */
        virtual bool isPostrollEnd() const = 0;

        /** Returns true for the content period end event and the content
            start event in a content-content period transition, e.g. when
            the ad break in between is not being replayed. 
            Note: this is not true for end/start events triggered by a seek,
                  when the event is not at a period end/start. */
        virtual bool isContentToContent() const = 0;

        /** Returns true if the event is for a live content stream */
        virtual bool isLive() const = 0;

        /** If not -1, this event was triggered by playing at normal speed
         *  past the specified position */
        virtual long getTriggerReachedPosition() const = 0;

        /** If not -1, this event was triggered after this percentage of the
         *  video was viewed at normal speed at least once */
        virtual double getTriggerViewedPercentage() const = 0;

        /** Return duration of the current period */
        virtual long getDuration() const = 0;

        /** The playback position in ms, within the currently playing stream. 
            In server-stitched flows this is the position in the combined 
            Ad+Content stream. In client-stitched flows, this is the position
            in the currently playing ad, or in the content. */
        virtual long getCurrPos() const = 0;

        /** The Ad playback position in ms. During Content playback return -1 */
        virtual long getAdPos() const = 0;

        /** The Content playback position in ms. During Ad playback, this is
         *  the current Ad Break's cue point */
        virtual long getContentPos() const = 0;

        /** Return the target position for seek events */
        virtual long getSeekTarget() const = 0;

        /** Return true if the ad was ended by a SkipAd action */
        virtual bool isAdSkipped() const = 0;

        /** The Url of the video asset */
        virtual VOOSMPString getAssetUrl() const = 0;

        /** Ad ID, if available */
        virtual VOOSMPString getAdId() const = 0;

        /** Creative ID, if available */
        virtual VOOSMPString getCreativeId() const = 0;

        /** The VAST/VMAP error code */
        virtual int getVASTErrorCode() const = 0;

        /** The VAST/VMAP tracking URL, with some macros replaced */
        virtual VOOSMPString getVASTTrackingUrl() const = 0;

        /** For content period: the index (from 1) of the period among all
         *  content periods.
         *  For ad period: the index (from 1) of the period among all ads that
         *  have the same cue point */
        virtual int getPartNumber() const = 0;

        /** For content period: the total number of content periods. 
         *  For ad period: the number of ads that have this ad's cue point. */
        virtual int getTotalParts() const = 0;

        /** The status returned by Open operation.
         *  Valid values: 
         *      VOOSMP_ERR_None - OK
         *      all other       - Error
         */
        virtual int getOpenCompleteStatus() const = 0;

        /** Returns the event info as a JSON string*/
        virtual VOOSMPString getJSONStr() const = 0;

    protected:
        VOOSMPTrackingEventInfo() {}
        virtual ~VOOSMPTrackingEventInfo() {}
};

/**
 * Interface for Tracking event listener. Implement this interface 
 * to receive Tracking events from AdsMgr
 */
class VOOSMPTrackingEventListener
{
    public:
        VOOSMPTrackingEventListener() {}
        virtual ~VOOSMPTrackingEventListener() {}

        /**
         * When AdsMgr has VMAP/VAST information, it can generate VMAP/VAST 
         * events (Error, Impression, Tracking etc.) in addition to its own
         * tracking events. VMAP/VAST events are sent automatically (HTTP GET).
         * A tracking event listener can request to handle VMAP/VAST events 
         * by itself, by having this method return true. In that case, AdsMgr
         * will not send HTTP GET requests to tracking servers, and the listener
         * will receive both the original tracking event, and all VMAP/VAST
         * events triggered by it. For example, one event at the start of an
         * Ad period can trigger multiple Impression/creativeView events
         * from a chain of Wrapper Ads and the InLine Ad.
         * VMAP/VAST events provide the tracking URL in VOOSMPTrackingEventInfo.
         *
         * @return true if this listener wants to handle VMAP/VAST events.
         */
        virtual bool handleVASTEvents() const = 0;

        /**
         * Interface to receive tracking events
         *
         * @param id    [in] Event type. See {@link VO_OSMP_TRACKING_EVENT_ID}.
         * @param info  [in] Information associated with the event. Refer to 
         *                   {@link VOOSMPTrackingEventInfo}
         *
         * @return {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful.
         */
        virtual VO_OSMP_RETURN_CODE onTrackingEvent(VO_OSMP_TRACKING_EVENT_ID id, VOOSMPTrackingEventInfo* info) = 0;
};

#endif
