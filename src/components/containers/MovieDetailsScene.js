import React, {Component} from 'react';
import {View, StyleSheet, Text, Dimensions} from 'react-native';
import Video from 'react-native-video';
import VideoPlayer from 'react-native-video-controls';

class MovieDetailsScene extends Component {

    state = {startPreRoll: true, startVideo: false, startPostRoll: false};

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

    render() {
        return (
            //{this.state.startVideo ? this.renderVideoView({uri: this.props.movie.link[1].attributes.href}, this.onVideoEnd) : null}
            <View style={{flex: 1}}>
                <View style={{height: Dimensions.get('window').width * (9 / 16), backgroundColor: 'black'}}>
                    {this.state.startPostRoll ? this.renderVideoView(require('../../resources/video.mp4'), this.onPostRollEnd) : null}
                    {this.state.startVideo ? this.renderVideoView({uri: this.props.movie.link[1].attributes.href}, this.onVideoEnd) : null}
                    {this.state.startPreRoll ? this.renderVideoView(require('../../resources/video.mp4'), this.onPreRollEnd) : null}
                </View>
                <View style={{flex: 1, background: 'white'}}/>
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
        height: Dimensions.get('window').width * (9 / 16),
        backgroundColor: 'black'
    },
    textStyle: {
        zIndex: 1,
        fontSize: 20,
        position: 'absolute',
        alignSelf: 'flex-end'
    }
});

export default MovieDetailsScene;
