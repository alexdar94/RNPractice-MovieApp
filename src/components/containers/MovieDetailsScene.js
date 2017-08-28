import React, {Component} from 'react';
import {View, StyleSheet, Animated, Dimensions, Text, PanResponder,} from 'react-native';
import VideoPlayer from 'react-native-video-controls';
import AdPlayer from '../AdPlayer/AdPlayer';
import {Actions} from 'react-native-router-flux';

const {width, height: screenHeight} = Dimensions.get("window");
const height = width * 0.5625;

class MovieDetailsScene extends Component {

  state = {startPreRoll: true, startVideo: false, startPostRoll: false, minimized: false};

  componentWillMount() {
    this.initViewPanResponder();
  }

  initViewPanResponder() {
    this._animation = new Animated.Value(0);
    this._panResponder = PanResponder.create({
      onStartShouldSetPanResponder: () => true,
      onMoveShouldSetPanResponder: () => true,

      onPanResponderMove: (e, gestureState) => {
        // custom logic here

        Animated.event([null, {
          //dx: this.state.minimized === true ? this.dismissMinimizedViewAnim : null,
          dy: this._animation,
        }])(e, gestureState);
      },

      onPanResponderRelease: (e, gestureState) => {
        if (gestureState.dy > 100) {
          Animated.timing(this._animation, {
            toValue: 300,
            duration: 200,
          }).start();
          this._animation.setOffset(300);
          this.setState({minimized: true});
        } else {
          this._animation.setOffset(0);
          this.setState({minimized: false});
          Animated.timing(this._animation, {
            toValue: 0,
            duration: 200,
          }).start();
        }
      },
    });
  }

  renderAdView(source, onEndCallback, onVisitAdvertiser = this.onVisitAdvertiser) {
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
                onVisitAdvertiser={onVisitAdvertiser.bind(this)}
                navigator={this.props.navigator}
                style={styles.backgroundVideo}
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
                   navigator={this.props.navigator}
                   style={styles.backgroundVideo}/>
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
    const opacityInterpolate = this._animation.interpolate({
      inputRange: [0, 300],
      outputRange: [1, 0],
    });

    const translateYInterpolate = this._animation.interpolate({
      inputRange: [0, 300],
      outputRange: [0, screenHeight - height + 45],
      extrapolate: "clamp",
    });

    const scaleInterpolate = this._animation.interpolate({
      inputRange: [0, 300],
      outputRange: [1, 0.5],
      extrapolate: "clamp",
    });

    const translateXInterpolate = this._animation.interpolate({
      inputRange: [0, 300],
      outputRange: [0, 85],
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
      ]
    };

    return (
      <View style={StyleSheet.absoluteFill} pointerEvents="box-none">
        <Animated.View
          style={[{height: Dimensions.get('window').width * (9 / 16)}, videoStyles]} {...this._panResponder.panHandlers}>
          {this.state.startPreRoll ? this.renderAdView({uri: `http${this.props.movie.link[1].attributes.href.substring(5)}`}, this.onPreRollEnd) : null}
          {this.state.startVideo ? this.renderVideoView({uri: `http${this.props.movie.link[1].attributes.href.substring(5)}`}, this.onVideoEnd) : null}
          {this.state.startPostRoll ? this.renderAdView(require('../../resources/video.mp4'), this.onPostRollEnd) : null}
        </Animated.View>
        <Animated.View style={[{flex: 1}, belowVideoStyles]}>
          <Text>
            ABC
          </Text>
        </Animated.View>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  backgroundVideo: {
    position: 'absolute',
    top: 0,
    left: 0,
    right: 0,
    bottom: 0,
    height: Dimensions.get('window').width * (9 / 16),
  },
});

export default MovieDetailsScene;
