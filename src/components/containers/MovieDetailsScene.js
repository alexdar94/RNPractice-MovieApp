import React, {Component} from 'react';
import {View, StyleSheet} from 'react-native';
import Video from 'react-native-video';

class MovieDetailsScene extends Component {

    state = {preRollComplete: false, videoComplete: false};

    renderVideoView(source, zIndex, onEndCallback) {
        return (
            <Video source={source}   // Can be a URL or a local file.
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
                   onEnd={onEndCallback()}
                   style={[styles.backgroundVideo, {zIndex: zIndex}]}/>
        );
    }

    onPreRollEnd() {
        this.setState({preRollComplete: true});
    }

    onVideoEnd() {
        this.setState({videoComplete: true});
        this.setState({preRollComplete: false});
    }

    render() {
        return (
            <View style={{flex: 1}}>
                {this.state.videoComplete ? this.renderVideoView(require('../../resources/video.mp4'), 2, null) : null}
                {this.state.preRollComplete ? this.renderVideoView({uri: this.props.movie.link[1].attributes.href}, 1, this.onVideoEnd()) : null}
                {!this.state.preRollComplete ? this.renderVideoView(require('../../resources/video.mp4'), 0, this.onPreRollEnd().bind(this)) : null}
            </View>
        );
    }
}

const styles = StyleSheet.create({
    backgroundVideo: {
        position: 'absolute',
        top: 0,
        left: 0,
        bottom: 0,
        right: 0,
    },
});

export default MovieDetailsScene;
