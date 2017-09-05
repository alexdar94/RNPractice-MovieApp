import React, {Component} from 'react';
import {View, StyleSheet, Animated, Dimensions, Text, PanResponder,} from 'react-native';
import VideoPlayer from 'react-native-video-controls';
import AdPlayer from '../AdPlayer/AdPlayer';
import {Actions} from 'react-native-router-flux';

const {width: screenWidth, height: screenHeight} = Dimensions.get("window");
const height = screenWidth * 0.5625;
let minimized = false;
let onHorizontalTouch = false;

class MovieDetailsScene extends Component {

  state = {startPreRoll: true, startVideo: false, startPostRoll: false};

  componentWillMount() {
    this.initViewPanResponder();
  }

  initViewPanResponder() {
    this.minimizeVideoAnim = new Animated.Value(0);
    this.dismissMinimizedVideoAnim = new Animated.Value(0);

    // View is out of screen when dismissMinimizedVideoAnim value is -200 or 200
    // Dismiss view when view is out of screen
    this.dismissMinimizedVideoAnim.addListener(({value}) => {
      if (Math.abs(value) === 200) {
        if (this.props.onDismiss) {
          this.props.onDismiss();
        } else {
          console.warn('Missing onDismiss props to destroy MovieDetailsScene sibling.')
        }
      }
    });

    this._panResponder = PanResponder.create({
      onStartShouldSetPanResponder: () => true,
      onMoveShouldSetPanResponder: () => true,

      onPanResponderMove: (e, gestureState) => {

        /*if (Math.abs(gestureState.dx) > Math.abs(gestureState.dy) || onHorizontalTouch) {
          if(minimized){
            onHorizontalTouch = true;
            this.minimizeVideoAnim.setOffset(300);

            Animated.event([null, {
              dx: this.dismissMinimizedVideoAnim,
            }])(e, gestureState);
          }
        } else {
          minimized = false;
          Animated.event([null, {
            dy: this.minimizeVideoAnim,
          }])(e, gestureState);
        }*/

        //console.log(gestureState.dx + ' ' + gestureState.dy + ' ' + minimized);

        // When video is minimized and user drag video horizontally
        // Lock animation to only onHorizontalTouch, listen to dx
        // When onHorizontalTouch is released, listen to dy
        if (minimized && gestureState.dx !== 0) {
          onHorizontalTouch = true;
          Animated.event([null, {
            dx: this.dismissMinimizedVideoAnim,
          }])(e, gestureState);
        } else if (!onHorizontalTouch) {
          minimized = false;
          Animated.event([null, {
            dy: this.minimizeVideoAnim,
          }])(e, gestureState);
        }

      },

      onPanResponderRelease: (e, gestureState) => {
        onHorizontalTouch = false;
        if (minimized) {
          // Drag far right dismiss
          if (gestureState.dx > 80) {
            Animated.timing(this.dismissMinimizedVideoAnim, {
              toValue: 200,
              duration: 200,
            }).start();
          }
          // Drag far left dismiss
          else if (gestureState.dx < -50) {
            Animated.timing(this.dismissMinimizedVideoAnim, {
              toValue: -200,
              duration: 200,
            }).start();
          }
          // Small drag return to normal
          else {
            Animated.timing(this.dismissMinimizedVideoAnim, {
              toValue: 0,
              duration: 200,
            }).start();
          }
        } else {
          // Detected drag release near bottom right, move view to bottom right
          if (gestureState.dy > 150 || (gestureState.dy > -150 && gestureState.dy < 0)) {
            Animated.timing(this.minimizeVideoAnim, {
              toValue: 300,
              duration: 200,
            }).start();
            this.minimizeVideoAnim.setOffset(300);
            minimized = true;
          }
          // Else, move view to top left
          else {
            Animated.timing(this.minimizeVideoAnim, {
              toValue: 0,
              duration: 200,
            }).start();
            this.minimizeVideoAnim.setOffset(0);
            minimized = false;
          }
          console.log(this.minimizeVideoAnim._offset);
        }
      },
    });
  }

  renderAdView(source, onEndCallback) {
    return (
      <AdPlayer source={source}   // Can be a URL or a local file.
                ref={(ref) => {
                  this.player = ref
                }}                                      // Store reference
                rate={1.0}                              // 0 is paused, 1 is normal.
                volume={1.0}                            // 0 is muted, 1 is normal.
                muted={false}                           // Mutes the audio entirely.
                paused={false}                          // Pauses playback entirely.
                resizeMode="contain"                      // Fill the whole screen at aspect ratio.*
                repeat={false}                           // Repeat forever.
                playInBackground={false}                // Audio continues to play when app entering background.
                playWhenInactive={false}                // [iOS] Video continues to play when control or notification center are shown.
                ignoreSilentSwitch={"ignore"}           // [iOS] ignore | obey - When 'ignore', audio will still play with the iOS hard silent switch set to silent. When 'obey', audio will toggle with the switch. When not specified, will inherit audio settings as usual.
                progressUpdateInterval={250.0}          // [iOS] Interval to fire onProgress (default to ~250ms)
                onEnd={onEndCallback.bind(this)}
                onVisitAdvertiser={() => Actions.visitAdvertiser()}
                preview={{uri: this.props.movie['im:image'][2].label}}/>
    );
  }

  renderVideoView(source, onEndCallback) {
    return (
      <VideoPlayer source={source}   // Can be a URL or a local file.
                   ref={(ref) => {
                     this.player = ref
                   }}                                      // Store reference
                   rate={1.0}                              // 0 is paused, 1 is normal.
                   volume={1.0}                            // 0 is muted, 1 is normal.
                   muted={false}                           // Mutes the audio entirely.
                   paused={false}                          // Pauses playback entirely.
                   resizeMode="contain"                      // Fill the whole screen at aspect ratio.*
                   repeat={false}                           // Repeat forever.
                   playInBackground={false}                // Audio continues to play when app entering background.
                   playWhenInactive={false}                // [iOS] Video continues to play when control or notification center are shown.
                   ignoreSilentSwitch={"ignore"}           // [iOS] ignore | obey - When 'ignore', audio will still play with the iOS hard silent switch set to silent. When 'obey', audio will toggle with the switch. When not specified, will inherit audio settings as usual.
                   progressUpdateInterval={250.0}          // [iOS] Interval to fire onProgress (default to ~250ms)
                   onEnd={onEndCallback.bind(this)}
                   navigator={this.props.navigator}/>
    );
  }

  onPreRollEnd() {
    this.setState({startPreRoll: false, startVideo: true});
  }

  onVideoEnd() {
    this.setState({startVideo: false, startPostRoll: true});
  }

  onPostRollEnd() {
    this.setState({startPostRoll: false});
  }

  onVisitAdvertiser() {
    Actions.visitAdvertiser();
  }

  render() {
    const opacityInterpolate = this.minimizeVideoAnim.interpolate({
      inputRange: [0, 300],
      outputRange: [1, 0],
    });

    const translateYInterpolate = this.minimizeVideoAnim.interpolate({
      inputRange: [0, 300],
      outputRange: [0, screenHeight - height + 45],
      extrapolate: "clamp",
    });

    const scaleInterpolate = this.minimizeVideoAnim.interpolate({
      inputRange: [0, 300],
      outputRange: [1, 0.5],
      extrapolate: "clamp",
    });

    const translateXInterpolate = this.minimizeVideoAnim.interpolate({
      inputRange: [0, 300],
      outputRange: [0, 85],
      extrapolate: "clamp",
    });

    const opacityInterpolate_Minimized = this.dismissMinimizedVideoAnim.interpolate({
      inputRange: [-200, 0, 200],
      outputRange: [0, 1, 0],
    });

    const translateXInterpolate_Minimized = this.dismissMinimizedVideoAnim.interpolate({
      inputRange: [-200, 200],
      outputRange: [-600, 600],
      extrapolate: "clamp",
    });

    const belowVideoStyles = {
      opacity: opacityInterpolate,
      transform: [
        {
          translateY: translateYInterpolate,
        },
      ],
    };

    const videoStyles = {
      opacity: opacityInterpolate_Minimized,
      transform: [
        {
          translateY: translateYInterpolate,
        },
        {
          translateX: translateXInterpolate,
        },
        {
          scale: scaleInterpolate,
        },
        {
          translateX: translateXInterpolate_Minimized,
        },
      ]
    };

    return (
      <View style={StyleSheet.absoluteFill} pointerEvents="box-none">
        <Animated.View
          style={[{height}, videoStyles]} {...this._panResponder.panHandlers}>
          {this.state.startPreRoll ? this.renderAdView({uri: `http${this.props.movie.link[1].attributes.href.substring(5)}`}, this.onPreRollEnd) : null}
          {this.state.startVideo ? this.renderVideoView({uri: `http${this.props.movie.link[1].attributes.href.substring(5)}`}, this.onVideoEnd) : null}
          {this.state.startPostRoll ? this.renderAdView(require('../../resources/video.mp4'), this.onPostRollEnd) : null}
        </Animated.View>
        <Animated.View style={[{flex: 1}, belowVideoStyles]}>
          <Text>ABC</Text>
        </Animated.View>
      </View>
    );
  }
}

export default MovieDetailsScene;
