import React, { Component } from 'react';
import { Text, StyleSheet } from 'react-native';
import { connect } from 'react-redux';
import { moviesFetch } from '../../actions';
import Video from 'react-native-video';
import { Card, CardSection, Button } from '../common';

class MovieDetailsScene extends Component {

	render(){
		console.log(this.props.movie.link[1].attributes.href);
		return(
			<Video source={{uri: this.props.movie.link[1].attributes.href}}   // Can be a URL or a local file.
       ref={(ref) => {
         this.player = ref
       }}                                      // Store reference
       rate={1.0}                              // 0 is paused, 1 is normal.
       volume={1.0}                            // 0 is muted, 1 is normal.
       muted={false}                           // Mutes the audio entirely.
       paused={false}                          // Pauses playback entirely.
       resizeMode="contain"                      // Fill the whole screen at aspect ratio.*
       repeat={true}                           // Repeat forever.
       playInBackground={false}                // Audio continues to play when app entering background.
       playWhenInactive={false}                // [iOS] Video continues to play when control or notification center are shown.
       ignoreSilentSwitch={"ignore"}           // [iOS] ignore | obey - When 'ignore', audio will still play with the iOS hard silent switch set to silent. When 'obey', audio will toggle with the switch. When not specified, will inherit audio settings as usual.
       progressUpdateInterval={250.0}          // [iOS] Interval to fire onProgress (default to ~250ms)
       style={styles.backgroundVideo} />
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

