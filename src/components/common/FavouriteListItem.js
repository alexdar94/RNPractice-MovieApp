import React, { Component } from 'react';
import {
  View, Image, TouchableOpacity, Text, StyleSheet
} from 'react-native';
import CacheableImage from 'react-native-cached-image';
import { connect } from 'react-redux';
import {
  gotoChannelView,
} from '../../actions';
import Colors from '../../constants/Colors';
import { formatTime } from '../../helper/FormatterHelper';

class FavouriteListItem extends Component {
  _onClickChannel(channel_id) {
    this.props.onClickChannel(channel_id);
  }

  renderSingleRow() {
    let channelLogo0 = undefined;
    if( this.props.data[0].channel.logo != null && this.props.data[0].channel.logo != undefined && this.props.data[0].channel.logo.length > 0 ) {
      channelLogo0 = this.props.data[0].channel.logo
    }
    let coverImage0 = undefined;
    if( this.props.data[0].cover_wide != null && this.props.data[0].cover_wide != undefined && this.props.data[0].cover_wide.length > 0 ) {
      coverImage0 = this.props.data[0].cover_wide
    }

    return (
      <View style={styles.container}>
        <View style={styles.bigSide}>
          { this.props.data[0] && <TouchableOpacity onPress={() => this.props.onPressVideo(this.props.data[0].id,this.props.data[0].path)}>
            <CacheableImage activityIndicatorProps={{color:'white',style: {backgroundColor:'transparent'} }} defaultSource={require('../../assets/imgs/luvevideoplaceholder.png')} resizeMode='cover' source={{uri: coverImage0}} style={styles.bigThumb}>
              <View style={{flex:1}}>
              </View>

              <View style={styles.duration}>
                <Text style={styles.durationText}>{formatTime(this.props.data[0].duration)}</Text>
              </View>

              <Image source={require('../../assets/imgs/overlay_1.png')} style={styles.caption}>
                <View style={styles.bottomLeftSide}>
                  <Text style={styles.bigText}>{this.props.data[0].title}</Text>
                </View>
              </Image>

              <TouchableOpacity style={styles.overthumb} onPress={() => this._onClickChannel(this.props.data[0].channel_id)}>
                <Image source={{uri: channelLogo0}} style={styles.avatar} />
              </TouchableOpacity>
            </CacheableImage>
          </TouchableOpacity>  }
        </View>

        <View style={{backgroundColor: this.props.current_background, height: 3}} />
      </View>
    )
  }

  renderDoubleRow() {
    let coverImage1 = undefined;
    if( this.props.data[0].cover_wide != null && this.props.data[0].cover_wide != undefined && this.props.data[0].cover_wide.length > 0 ) {
      coverImage1 = this.props.data[0].cover_wide
    }

    let coverImage2 = undefined;
    if( this.props.data[1].cover_wide != null && this.props.data[1].cover_wide != undefined && this.props.data[1].cover_wide.length > 0 ) {
      coverImage2 = this.props.data[1].cover_wide
    }

    let captionStyle1 = styles.smallCaption1;
    let captionStyle2 = styles.smallCaption2;

    return (
      <View style={styles.smallSide}>
        { this.props.data[0] &&  <TouchableOpacity onPress={() => this.props.onPressVideo(this.props.data[0].id,this.props.data[0].path)} style={styles.smallThumbContainer}>
          <CacheableImage activityIndicatorProps={{color:'white',style: {backgroundColor:'transparent'} }} defaultSource={require('../../assets/imgs/luveplaceholder.png')} source={{uri: coverImage1}} style={styles.smallThumb}>
            <View style={{flex:1}}>
            </View>

            <View style={styles.duration}>
              <Text style={styles.durationText}>{formatTime(this.props.data[0].duration)}</Text>
            </View>

            <View style={captionStyle1}>
              <View style={styles.bottomLeftSide}>
                <Text numberOfLines={2} style={styles.text}>{this.props.data[0].title}</Text>
              </View>
            </View>
          </CacheableImage>
        </TouchableOpacity> }
        { this.props.data[1] && <TouchableOpacity onPress={() =>  this.props.onPressVideo(this.props.data[1].id,this.props.data[1].path)} style={styles.smallThumbContainer}>
          <CacheableImage activityIndicatorProps={{color:'white',style: {backgroundColor:Colors.luveblue} }} defaultSource={require('../../assets/imgs/luveplaceholder.png')} source={{uri: coverImage2}} style={styles.smallThumb}>
            <View style={{flex:1}}>
            </View>

            <View style={styles.duration}>
              <Text style={styles.durationText}>{formatTime(this.props.data[1].duration)}</Text>
            </View>

            <View style={captionStyle2}>
              <View style={styles.bottomLeftSide}>
                <Text numberOfLines={2} style={styles.text}>{this.props.data[1].title}</Text>
              </View>
            </View>
          </CacheableImage>
        </TouchableOpacity> }
      </View>
    );
  }

  render() {
    if (this.props.data.length === 1) {
      return this.renderSingleRow();
    } else if ( this.props.data.length === 2 ) {
      return this.renderDoubleRow();
    } else {
      return null;
    }
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    flexDirection: 'column',
  },
  bigThumb: {
    flex: 1,
    width: undefined,
    height: 250,
    backgroundColor:'#E8E8E8',
    flexDirection: 'column',
  },
  smallThumb: {
    flex: 1,
    width: undefined,
    height: 185,
    backgroundColor:'#E8E8E8',
    flexDirection: 'column',
  },
  smallThumbContainer: {
    flex: 1,
  },
  caption: {
    width: undefined,
    height: 56,
    flexDirection: 'row',
  },
  smallCaption1: {
    height: 60,
    backgroundColor:Colors.luveblue,
    flexDirection: 'row',
  },
  smallCaption2: {
    height: 60,
    backgroundColor:'#6AE8F3',
    flexDirection: 'row',
  },
  overthumb: {
    position: 'absolute',
    left: 10,
    bottom: 10,
    backgroundColor:'transparent',
    borderColor: 'white',
    borderWidth: 2,
    width: 72,
    height: 72,
    justifyContent: 'center',
    alignItems: 'center',
    borderRadius: 36,
  },
  avatar: {
    width: 70,
    height: 70,
    resizeMode: 'cover',
    borderRadius: 35,
  },
  smallSide: {
    flex: 1,
    flexDirection: 'row',
  },
  text: {
    flex: 1,
    paddingLeft: 5,
    paddingBottom: 5,
    color: '#363636',
    fontSize: 13,
    marginTop: 12,
    marginLeft: 12,
    marginRight: 12,
  },
  bigText: {
    paddingLeft: 5,
    paddingBottom: 5,
    color: '#363636',
    fontSize: 13,
    marginLeft: 80,
    marginTop: 12,
    backgroundColor: 'transparent',
  },
  iconFB: {
    width: 22,
    height: 22,
    resizeMode: 'contain',
    marginLeft: 10,
    marginRight: 10,
    marginTop: 12,
    alignSelf: 'flex-end',
  },
  bottomLeftSide: {
    flex: 5,
  },
  bottomRightSide: {
    flex: 1,
  },
  duration: {
    paddingRight: 4,
    paddingBottom: 2,
    alignItems:'flex-end',
    backgroundColor:'transparent',
  },
  durationText: {
    fontSize:14,
    color:'white',
    textShadowColor: 'black',
    textShadowOffset:{width:2,height:2},
    textShadowRadius: 3,
    paddingRight: 2,
  }
});

const mapStateToProps = (state) => {
  return {
    onClickChannel: gotoChannelView,
    current_background: state.background.current_background
  }
}

export default connect(
  mapStateToProps,
  {
    onClickChannel: gotoChannelView,
  }
)(FavouriteListItem);
