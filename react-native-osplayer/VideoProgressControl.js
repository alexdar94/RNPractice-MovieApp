import React, { Component, PropTypes } from 'react'
import {
  Animated,
  StyleSheet,
  Text,
  Image,
  TouchableOpacity,
  TouchableWithoutFeedback,
  View,
  Alert,
} from 'react-native'

import Trackbar from './Trackbar'

const trackHeight = 2
const thumbSize = 10
const touchableHeight = 20

const styles = StyleSheet.create({
  container: {
    flex: 1,
    flexDirection: 'row',
    alignItems: 'center',
  },
  text: {
    color: 'white',
  },
  track: {
    marginHorizontal: 10,
    flex: 1,
    flexDirection: 'row',
  },
  filled: {
    backgroundColor: 'white',
    height: trackHeight,
    alignSelf: 'center',
  },
  unfilled: {
    backgroundColor: 'rgba(255,255,255,0.2)',
    height: trackHeight,
    alignSelf: 'center',
  },
  thumb: {
    width: thumbSize,
    height: thumbSize,
    backgroundColor: 'skyblue',
    alignSelf: 'center',
  },
  trackbar: {
    position: 'absolute',
    top: - (touchableHeight - trackHeight) / 2,
    right: 0,
    bottom: 0,
    left: 0,
    height: touchableHeight,
  },
})

const formatSeconds = (s) => {
  return s < 10 ? `0${s}` : s
}

const formatMinutes = (s) => {
  const m = Math.floor(s / 60)

  return `${m}:${formatSeconds(s % 60)}`
}

export default class VideoProgressControl extends Component {

  static propTypes = {
    style: PropTypes.any,
    duration: PropTypes.number,
    currentTime: PropTypes.number,
    onChange: PropTypes.func,
    onChangeStart: PropTypes.func,
    onChangeEnd: PropTypes.func,
  }

  static defaultProps = {
    onChange: () => {},
    onChangeStart: () => {},
    onChangeEnd: () => {},
  }

  calculateProgress = (duration, ratio) => Math.floor(duration * ratio)

  handleTouch = (ratio) => {
    const {onChange, duration} = this.props

    onChange(this.calculateProgress(duration, ratio))
  }

  handleTouchStart = (ratio) => {
    const {onChangeStart, duration} = this.props

    onChangeStart(this.calculateProgress(duration, ratio))
  }

  handleTouchEnd = (ratio) => {
    const {onChangeEnd, duration} = this.props

    onChangeEnd(this.calculateProgress(duration, ratio))
  }

  render() {
    const {style, duration, currentTime} = this.props

    return (
      <View style={style}>
        <View style={styles.container}>
          <Text style={styles.text}>
            {formatMinutes(currentTime)}
          </Text>
          <View style={styles.track}>
            <View style={[styles.filled, {flex: currentTime}]} />
            <View style={styles.thumb} />
            <View style={[styles.unfilled, {flex: duration - currentTime}]} />
            <Trackbar
              style={styles.trackbar}
              onTouch={this.handleTouch}
              onTouchStart={this.handleTouchStart}
              onTouchEnd={this.handleTouchEnd}
            />
          </View>
          <Text style={styles.text}>
            {formatMinutes(duration)}
          </Text>
        </View>
      </View>
    )
  }
}
