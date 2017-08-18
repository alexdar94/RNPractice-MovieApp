import React, { Component } from 'react';
import { Text } from 'react-native';
import Video from '../../custom-video-controls';
import { moviesFetch } from '../../actions';

class MovieDetailsScene extends Component {

	render(){
		return(
			<Video source={{uri: 'http://video.itunes.apple.com/apple-assets-us-std-000001/Video118/v4/54/0c/4a/540c4a0d-dfc2-28a2-38f1-f7c64089d8ed/mzvf_8426414888471677444.640x358.h264lc.U.p.m4v', drm: 'key.luve.tv:80'}}
                 style={[{position: 'absolute',
                        top: 0,
                        left: 0,
                        bottom: 0,
                        right: 0,},500,{backgroundColor: 'black'}] }
                 videoStyle={500}
                 rate={1}
                 volume={1}
                 muted={false}
                 resizeMode={'cover'}
                 repeat={false}
                 seekColor='#00CADC'
          />		);
	}
}

export default MovieDetailsScene;

