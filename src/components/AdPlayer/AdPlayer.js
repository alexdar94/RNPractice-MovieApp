import React, {Component} from 'react';
import Video from 'react-native-video';
import {
    TouchableWithoutFeedback,
    TouchableHighlight,
    PanResponder,
    StyleSheet,
    Touchable,
    Animated,
    Platform,
    Easing,
    Image,
    View,
    Text
} from 'react-native';
import _ from 'lodash';

export default class VideoPlayer extends Component {

    constructor(props) {
        super(props);

        /**
         * All of our values that are updated by the
         * methods and listeners in this class
         */
        const isFullscreen = this.props.resizeMode === 'cover' || false;
        this.state = {
            // Video
            resizeMode: this.props.resizeMode || 'contain',
            paused: this.props.paused || false,
            muted: this.props.muted || false,
            rate: this.props.rate || 1,
            // Controls
            isFullscreen: isFullscreen,
            showTimeRemaining: true,
            lastScreenPress: 0,
            seekerFillWidth: 0,
            showControls: true,
            seekerPosition: 0,
            seekerOffset: 0,
            seeking: false,
            loading: false,
            currentTime: 0,
            error: false,
            duration: 0,
            mustWatchAdLength: 5,
            visible: true
        };

        /**
         * Any options that can be set at init.
         */
        this.opts = {
            playWhenInactive: this.props.playWhenInactive || false,
            playInBackground: this.props.playInBackground || false,
            repeat: this.props.repeat || false,
        };

        /**
         * Our app listeners and associated methods
         */
        this.events = {
            onError: this.props.onError || this._onError.bind(this),
            onEnd: this._onEnd.bind(this),
            onScreenPress: this._onScreenPress.bind(this),
            onLoadStart: this._onLoadStart.bind(this),
            onProgress: this._onProgress.bind(this),
            onLoad: this._onLoad.bind(this),
        };

        /**
         * Functions used throughout the application
         */
        this.methods = {
            onVisitAdvertiser: this.props.onVisitAdvertiser || this._onVisitAdvertiser.bind(this),
            toggleControls: this._toggleControls.bind(this),
        };

        /**
         * Player information
         */
        this.player = {
            controlTimeoutDelay: this.props.controlTimeout || 15000,
            controlTimeout: null,
            ref: Video,
        };

        /**
         * Various animations
         */
        this.animations = {
            bottomControl: {
                marginBottom: new Animated.Value(0),
                opacity: new Animated.Value(1),
            },
            topControl: {
                marginTop: new Animated.Value(0),
                opacity: new Animated.Value(1),
            },
            video: {
                opacity: new Animated.Value(1),
            },
            loader: {
                rotate: new Animated.Value(0),
                MAX_VALUE: 360,
            }
        };

        /**
         * Various styles that be added...
         */
        this.styles = {
            videoStyle: this.props.videoStyle || {},
            containerStyle: this.props.style || {}
        };
    }


    /*------------------------------------------------------
    | Events
    |-------------------------------------------------------
    |
    | These are the events that the <Video> component uses
    | and can be overridden by assigning it as a prop.
    | It is suggested that you override onEnd.
    |
    */

    /**
     * When load starts we display a loading icon
     * and show the controls.
     */
    _onLoadStart() {
        let state = this.state;
        state.loading = true;
        this.loadAnimation();
        this.setState(state);

        if (typeof this.props.onLoadStart === 'function') {
            this.props.onLoadStart(...arguments);
        }
    }

    /**
     * When load is finished we hide the load icon
     * and hide the controls. We also set the
     * video duration.
     *
     * @param {object} data The video meta data
     */
    _onLoad(data = {}) {
        let state = this.state;

        state.duration = data.duration;
        state.loading = false;
        this.setState(state);

        if (state.showControls) {
            this.setControlTimeout();
        }

        if (typeof this.props.onLoad === 'function') {
            this.props.onLoad(...arguments);
        }
    }

    /**
     * For onprogress we fire listeners that
     * update our seekbar and timer.
     *
     * @param {object} data The video meta data
     */
    _onProgress(data = {}) {
        let state = this.state;
        state.currentTime = data.currentTime;

        if (!state.seeking) {
            const position = this.calculateSeekerPosition();
            this.setSeekerPosition(position);
        }

        if (typeof this.props.onProgress === 'function') {
            this.props.onProgress(...arguments);
        }

        this.setState(state);
    }

    /**
     * It is suggested that you override this
     * command so your app knows what to do.
     * Either close the video or go to a
     * new page.
     */
    _onEnd() {
        this.setState({visible: false});
        // If onEndCallback is provided
        if (this.props.onEnd !== undefined) {
            this.props.onEnd()
        }
    }

    /**
     * Set the error state to true which then
     * changes our renderError function
     *
     * @param {object} err  Err obj returned from <Video> component
     */
    _onError(err) {
        let state = this.state;
        state.error = true;
        state.loading = false;

        this.setState(state);
    }

    /**
     * This is a single and double tap listener
     * when the user taps the screen anywhere.
     * One tap toggles controls, two toggles
     * fullscreen mode.
     */
    _onScreenPress() {
        let state = this.state;
        const time = new Date().getTime();
        const delta = time - state.lastScreenPress;

        if (delta < 300) {
            this.methods.toggleFullscreen();
        }

        this.methods.toggleControls();
        state.lastScreenPress = time;

        this.setState(state);
    }


    /*------------------------------------------------------
    | Methods
    |-------------------------------------------------------
    |
    | These are all of our functions that interact with
    | various parts of the class. Anything from
    | calculating time remaining in a video
    | to handling control operations.
    |
    */

    /**
     * Set a timeout when the controls are shown
     * that hides them after a length of time.
     * Default is 15s
     */
    setControlTimeout() {
        this.player.controlTimeout = setTimeout(() => {
            this._hideControls();
        }, this.player.controlTimeoutDelay);
    }

    /**
     * Clear the hide controls timeout.
     */
    clearControlTimeout() {
        clearTimeout(this.player.controlTimeout);
    }

    /**
     * Reset the timer completely
     */
    resetControlTimeout() {
        this.clearControlTimeout();
        this.setControlTimeout();
    }

    /**
     * Animation to hide controls. We fade the
     * display to 0 then move them off the
     * screen so they're not interactable
     */
    hideControlAnimation() {
        Animated.parallel([
            Animated.timing(
                this.animations.topControl.opacity,
                {toValue: 0}
            ),
            Animated.timing(
                this.animations.topControl.marginTop,
                {toValue: -100}
            ),
            Animated.timing(
                this.animations.bottomControl.opacity,
                {toValue: 0}
            ),
            Animated.timing(
                this.animations.bottomControl.marginBottom,
                {toValue: -100}
            ),
        ]).start();
    }

    /**
     * Animation to show controls...opposite of
     * above...move onto the screen and then
     * fade in.
     */
    showControlAnimation() {
        Animated.parallel([
            Animated.timing(
                this.animations.topControl.opacity,
                {toValue: 1}
            ),
            Animated.timing(
                this.animations.topControl.marginTop,
                {toValue: 0}
            ),
            Animated.timing(
                this.animations.bottomControl.opacity,
                {toValue: 1}
            ),
            Animated.timing(
                this.animations.bottomControl.marginBottom,
                {toValue: 0}
            ),
        ]).start();
    }

    /**
     * Loop animation to spin loader icon. If not loading then stop loop.
     */
    loadAnimation() {
        if (this.state.loading) {
            Animated.sequence([
                Animated.timing(
                    this.animations.loader.rotate,
                    {
                        toValue: this.animations.loader.MAX_VALUE,
                        duration: 1500,
                        easing: Easing.linear,
                    }
                ),
                Animated.timing(
                    this.animations.loader.rotate,
                    {
                        toValue: 0,
                        duration: 0,
                        easing: Easing.linear,
                    }
                ),
            ]).start(this.loadAnimation.bind(this));
        }
    }

    /**
     * Function to hide the controls. Sets our
     * state then calls the animation.
     */
    _hideControls() {
        let state = this.state;
        state.showControls = false;
        this.hideControlAnimation();

        this.setState(state);
    }

    /**
     * Function to toggle controls based on
     * current state.
     */
    _toggleControls() {
        let state = this.state;
        state.showControls = !state.showControls;

        if (state.showControls) {
            this.showControlAnimation();
            this.setControlTimeout();
        }
        else {
            this.hideControlAnimation();
            this.clearControlTimeout();
        }

        this.setState(state);
    }

    /**
     * The default 'onVisitAdvertiser' function pops the navigator
     * and as such the video player requires a
     * navigator prop by default.
     */
    _onVisitAdvertiser() {
        if (this.props.navigator && this.props.navigator.pop) {
            this.props.navigator.pop();
        }
        else {
            console.warn('Warning: _onVisitAdvertiser requires navigator property to function. Either modify the onVisitAdvertiser prop or pass a navigator prop');
        }
    }

    /**
     * Calculate the time to show in the timer area
     * based on if they want to see time remaining
     * or duration. Formatted to look as 00:00.
     */
    calculateTime() {
        if (this.state.showTimeRemaining) {
            const time = this.state.duration - this.state.currentTime;
            return `Ad • ${ this.formatTime(time) } ⓘ`;
        }
        return `${ this.formatTime(this.state.currentTime) }`;
    }

    /**
     * Format a time string as mm:ss
     *
     * @param {int} time time in milliseconds
     * @return {string} formatted time string in mm:ss format
     */
    formatTime(time = 0) {
        const symbol = this.state.showRemainingTime ? '-' : '';
        time = Math.min(
            Math.max(time, 0),
            this.state.duration
        );
        const minutes = time / 60;
        const seconds = time % 60;

        const formattedMinutes = _.padStart(Math.floor(minutes).toFixed(0), 2, 0);
        const formattedSeconds = _.padStart(Math.floor(seconds).toFixed(0), 2, 0);

        return `${ symbol }${ formattedMinutes }:${ formattedSeconds }`;
    }

    /**
     * Set the position of the seekbar's components
     * (both fill and handle) according to the
     * position supplied.
     *
     * @param {float} position position in px of seeker handle}
     */
    setSeekerPosition(position = 0) {
        position = this.constrainToSeekerMinMax(position);
        let state = this.state;

        state.seekerFillWidth = position;
        state.seekerPosition = position;
        if (!state.seeking) {
            state.seekerOffset = position;
        }
        this.setState(state);
    }

    /**
     * Contrain the location of the seeker to the
     * min/max value based on how big the
     * seeker is.
     *
     * @param {float} val position of seeker handle in px
     * @return {float} contrained position of seeker handle in px
     */
    constrainToSeekerMinMax(val = 0) {
        if (val <= 0) {
            return 0;
        }
        else if (val >= this.player.seekerWidth) {
            return this.player.seekerWidth;
        }
        return val;
    }

    /**
     * Calculate the position that the seeker should be
     * at along its track.
     *
     * @return {float} position of seeker handle in px based on currentTime
     */
    calculateSeekerPosition() {
        const percent = this.state.currentTime / this.state.duration;
        return this.player.seekerWidth * percent;
    }

    /*------------------------------------------------------
    | React Component functions
    |-------------------------------------------------------
    |
    | Here we're initializing our listeners and getting
    | the component ready using the built-in React
    | Component methods
    |
    */
    /**
     * When the component is about to unmount kill the
     * timeout less it fire in the prev/next scene
     */
    componentWillUnmount() {
        this.clearControlTimeout();
    }

    /*------------------------------------------------------
    | Rendering
    |-------------------------------------------------------
    |
    | This section contains all of our render methods.
    | In addition to the typical React render func
    | we also have all the render methods for
    | the controls.
    |
    */

    /**
     * Standard render control function that handles
     * everything except the sliders. Adds a
     * consistent <TouchableHighlight>
     * wrapper and styling.
     */
    renderControl(children, callback, style = {}) {
        return (
            <TouchableHighlight
                underlayColor="transparent"
                activeOpacity={0.3}
                onPress={() => {
                    this.resetControlTimeout();
                    callback();
                }}
                style={[
                    style
                ]}
            >
                {children}
            </TouchableHighlight>
        );
    }

    /**
     * Render SkipAd button
     * Countdown start from mustWatchAdLength state
     * After countdown completes, allow user to skip ad
     */
    renderSkipAd() {
        let mustWatchAdTimeLeft = Math.floor(this.state.mustWatchAdLength - this.state.currentTime);
        if (mustWatchAdTimeLeft < 1) {
            return (
                <Animated.View style={[
                    styles.controls.bottom,
                    {
                        opacity: this.animations.bottomControl.opacity,
                        marginBottom: this.animations.bottomControl.marginBottom,
                    }
                ]}>
                    <TouchableWithoutFeedback
                        onPress={this.events.onEnd} style={{alignSelf: 'flex-end'}}>
                        <View style={styles.ad.container}>
                            <Text style={{color: 'white', margin: 8}}>
                                Skip ad
                            </Text>
                            <Image source={require('./assets/img/next.png')}
                                   style={{width: 15, height: 15, marginRight: 8}}/>
                        </View>
                    </TouchableWithoutFeedback>
                </Animated.View>
            );
        } else {
            return (
                <Animated.View style={[
                    styles.controls.bottom,
                    {
                        opacity: this.animations.bottomControl.opacity,
                        marginBottom: this.animations.bottomControl.marginBottom,
                    }
                ]}>
                    <View style={styles.ad.countdownContainer}>
                        <Text style={{color: 'white', width: 80, textAlign: 'center', marginRight: 8}}>
                            {`You can skip ad in ${mustWatchAdTimeLeft}s`}
                        </Text>
                        <Image source={this.props.preview}
                               style={{width: 40, height: 50, flex: 1}}/>
                    </View>
                </Animated.View>
            );
        }
    }

    /**
     * Render visit advertiser button
     */
    renderVisitAdvertiser() {
        return (
            <Animated.View style={[
                styles.controls.top,
                {
                    opacity: this.animations.topControl.opacity,
                    marginTop: this.animations.topControl.marginTop,
                }
            ]}>
                <TouchableWithoutFeedback
                    onPress={this.methods.onVisitAdvertiser} style={{alignSelf: 'flex-end'}}>
                    <View>
                        <Text style={{backgroundColor: 'transparent', color: '#FFF', margin: 8}}>
                            Visit advertiser
                        </Text>
                    </View>
                </TouchableWithoutFeedback>
            </Animated.View>
        );
    }

    /**
     * Render bottom control group and wrap it in a holder
     */
    renderBottomControls() {
        return (
            <Animated.View style={[
                styles.controls.bottom,
                {
                    opacity: this.animations.bottomControl.opacity,
                    marginBottom: this.animations.bottomControl.marginBottom,
                }
            ]}>
                <Image
                    source={require('./assets/img/bottom-vignette.png')}
                    style={[styles.controls.column, styles.controls.vignette,
                    ]}>

                    <View style={[
                        styles.controls.column,
                        styles.controls.bottomControlGroup
                    ]}>
                        {this.renderTimer()}
                    </View>
                    <View style={[
                        styles.player.container,
                        styles.controls.seekbar
                    ]}>
                        {this.renderSeekbar()}
                    </View>
                </Image>
            </Animated.View>
        );
    }

    /**
     * Render the seekbar and attach its handlers
     */
    renderSeekbar() {
        return (
            <View
                style={styles.seek.track}
                onLayout={event => {
                    this.player.seekerWidth = event.nativeEvent.layout.width;
                }}
            >
                <View style={[
                    styles.seek.fill,
                    {
                        width: this.state.seekerFillWidth,
                        backgroundColor: this.props.seekColor || '#f2c84b'
                    }
                ]}>
                </View>
            </View>
        );
    }

    /**
     * Show our timer.
     */
    renderTimer() {
        return this.renderControl(
            <Text style={styles.controls.timerText}>
                {this.calculateTime()}
            </Text>,
            this.methods.onVisitAdvertiser,
            styles.controls.timer
        );
    }

    /**
     * Show loading icon
     */
    renderLoader() {
        if (this.state.loading) {
            return (
                <View style={styles.loader.container}>
                    <Animated.Image source={require('./assets/img/loader-icon.png')} style={[
                        styles.loader.icon,
                        {
                            transform: [
                                {
                                    rotate: this.animations.loader.rotate.interpolate({
                                        inputRange: [0, 360],
                                        outputRange: ['0deg', '360deg']
                                    })
                                }
                            ]
                        }
                    ]}/>
                </View>
            );
        }
        return null;
    }

    renderError() {
        if (this.state.error) {
            return (
                <View style={styles.error.container}>
                    <Image source={require('./assets/img/error-icon.png')} style={styles.error.icon}/>
                    <Text style={styles.error.text}>
                        Video unavailable
                    </Text>
                </View>
            );
        }
        return null;
    }

    /**
     * Provide all of our options and render the whole component.
     */
    render() {
        if (this.state.visible) {
            return (
                <TouchableWithoutFeedback
                    onPress={this.events.onScreenPress}
                    style={[styles.player.container, this.styles.containerStyle]}
                >
                    <View style={[styles.player.container, this.styles.containerStyle]}>
                        <Video
                            {...this.props}
                            ref={videoPlayer => this.player.ref = videoPlayer}

                            resizeMode={this.state.resizeMode}
                            paused={this.state.paused}
                            muted={this.state.muted}
                            rate={this.state.rate}

                            {...this.props}

                            onLoadStart={this.events.onLoadStart}
                            onProgress={this.events.onProgress}
                            onError={this.events.onError}
                            onLoad={this.events.onLoad}
                            onEnd={this.events.onEnd}

                            style={[styles.player.video, this.styles.videoStyle]}

                            source={this.props.source}
                        />
                        {this.renderError()}
                        {this.renderVisitAdvertiser()}
                        {this.renderLoader()}
                        {this.renderSkipAd()}
                        {this.renderBottomControls()}
                    </View>
                </TouchableWithoutFeedback>
            );
        } else {
            return null;
        }

    }
}

/**
 * This object houses our styles. There's player
 * specific styles and control specific ones.
 * And then there's seeker styles.
 */
const styles = {
    player: StyleSheet.create({
        container: {
            flex: Platform.OS === 'ios' ? 1 : null,
            alignSelf: 'stretch',
            justifyContent: 'space-between',
        },
        video: {
            overflow: 'hidden',
            position: 'absolute',
            top: 0,
            right: 0,
            bottom: 0,
            left: 0,
        },
    }),
    error: StyleSheet.create({
        container: {
            backgroundColor: 'rgba( 0, 0, 0, 0.5 )',
            position: 'absolute',
            top: 0,
            right: 0,
            bottom: 0,
            left: 0,
            justifyContent: 'center',
            alignItems: 'center',
        },
        icon: {
            marginBottom: 16,
        },
        text: {
            backgroundColor: 'transparent',
            color: '#f27474'
        },
    }),
    loader: StyleSheet.create({
        container: {
            position: 'absolute',
            top: 0,
            right: 0,
            bottom: 0,
            left: 0,
            alignItems: 'center',
            justifyContent: 'center',
        },
    }),
    controls: StyleSheet.create({
        row: {
            flexDirection: 'row',
            alignItems: 'center',
            justifyContent: 'space-between',
            height: null,
            width: null,
        },
        column: {
            flexDirection: 'column',
            alignItems: 'center',
            justifyContent: 'space-between',
            height: null,
            width: null,
        },
        vignette: {
            resizeMode: 'stretch',
        },
        text: {
            backgroundColor: 'transparent',
            color: '#FFF',
            fontSize: 16,
            textAlign: 'center',
        },
        pullRight: {
            flexDirection: 'row',
            alignItems: 'center',
            justifyContent: 'center',
        },
        top: {
            alignItems: 'flex-end',
            justifyContent: 'flex-start',
        },
        bottom: {
            alignItems: 'stretch',
            justifyContent: 'flex-end',
        },
        seekbar: {
            alignSelf: 'stretch',
            alignItems: 'center',
            justifyContent: 'center',
            zIndex: 100,
            marginTop: 0,
            marginBottom: 2
        },
        topControlGroup: {
            alignSelf: 'stretch',
            alignItems: 'center',
            justifyContent: 'space-between',
            flexDirection: 'row',
            width: null,
            margin: 12,
            marginBottom: 18,
        },
        bottomControlGroup: {
            alignSelf: 'stretch',
            alignItems: 'center',
            justifyContent: 'space-between',
            flexDirection: 'row',
            marginLeft: 12,
            marginRight: 12,
            marginBottom: 0
        },
        fullscreen: {
            flexDirection: 'row',
        },
        playPause: {
            position: 'relative',
            width: 80,
            zIndex: 0
        },
        timer: {
            width: 180,
        },
        timerText: {
            backgroundColor: 'transparent',
            color: '#FFF',
            fontSize: 11,
            marginBottom:8
        },
    }),
    seek: StyleSheet.create({
        track: {
            alignSelf: 'stretch',
            justifyContent: 'center',
            backgroundColor: '#333',
            height: 4,
            marginLeft: 0,
            marginRight: 0,
        },
        fill: {
            alignSelf: 'flex-start',
            height: 2,
            width: 1,
        },
    }),
    ad: StyleSheet.create({
        container: {
            width: 80,
            height: 40,
            backgroundColor: 'rgba(52, 52, 52, 0.8)',
            flexDirection: 'row',
            alignItems: 'center',
            justifyContent: 'space-around',
            alignSelf: 'flex-end',
            marginTop: 80
        },
        countdownContainer: {
            width: 150,
            height: 50,
            backgroundColor: 'rgba(52, 52, 52, 0.8)',
            flexDirection: 'row',
            alignItems: 'center',
            justifyContent: 'space-around',
            alignSelf: 'flex-end',
            marginTop: 80,
            marginRight: -15,
        }
    })
};
