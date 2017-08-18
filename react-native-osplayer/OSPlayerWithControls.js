import React, { Component } from 'react'
import {
  Animated,
  StyleSheet,
  Text,
  Image,
  TouchableOpacity,
  TouchableHighlight,
  TouchableWithoutFeedback,
  View,
  Button,
  Modal,
  Alert,
  ActivityIndicator,
} from 'react-native'

import OSPlayer from './OSPlayer'
import VideoProgressControl from './VideoProgressControl'

const CONTROLS_HIDE_DELAY_LONG = 3000
const CONTROLS_HIDE_DELAY_SHORT = 1000

const styles = StyleSheet.create({
  flex: {
    flex: 1,
  },
  loading: {
    flex: 1,
    backgroundColor: 'black',
    alignItems: 'center',
    justifyContent: 'center',
  },
  controls: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  icon: {
    width: 44,
    height: 44,
  },
  bottomControls: {
    position: 'absolute',
    bottom: 0,
    flexDirection: 'row',
  },
  progress: {
    flex: 1,
    marginLeft: 10,
  },
})

export default class OSPlayerWithControls extends Component {

  state = {
    volume: 1,
    muted: false,
    loading: true,
    duration: 0,
    currentTime: 0,
    paused: false,
    fullscreen: false,
    showControls: false,
    controlsOpacity: new Animated.Value(0),
    isScrubbing: false,
    isSeeking: false,
  }

  toggleControls = () => {
    const {showControls, controlsOpacity} = this.state

    const visible = !showControls

    this.stopInactiveTimer()

    if (visible) {
      this.startInactiveTimer(CONTROLS_HIDE_DELAY_LONG)
    }

    this.setState({showControls: visible})

    Animated.timing(controlsOpacity, {
      toValue: visible ? 1 : 0,
      duration: 300,
    }).start()
  }

  toggleFullscreen = () => {
    const {fullscreen} = this.state

    const visible = !fullscreen

    this.setState({fullscreen: visible})
    this.startInactiveTimer(visible ? CONTROLS_HIDE_DELAY_SHORT : CONTROLS_HIDE_DELAY_LONG)
  }

  togglePaused = () => {
    const {paused} = this.state

    this.setState({paused: !paused})

    this.startInactiveTimer(CONTROLS_HIDE_DELAY_LONG)
  }

  startInactiveTimer = (delay) => {
    const hideControls = () => {
      const {showControls} = this.state

      this.inactiveTimeoutId = null

      if (showControls) {
        this.toggleControls()
      }
    }

    this.stopInactiveTimer()

    this.inactiveTimeoutId = setTimeout(hideControls, delay)
  }

  stopInactiveTimer = () => {
    if (!this.inactiveTimeoutId) return

    clearTimeout(this.inactiveTimeoutId)
    this.inactiveTimeoutId = null
  }

  handleProgressChange = (time) => {
    this.setState({
      currentTime: time,
    })

    this.startInactiveTimer(CONTROLS_HIDE_DELAY_LONG)
  }

  handleProgressChangeStart = (time) => {
    this.setState({
      isScrubbing: true,
    })
  }

  handleProgressChangeEnd = (time) => {
    this.setState({
      isScrubbing: false,
      isSeeking: true,
      currentTime: time,
    })

    this.startInactiveTimer(CONTROLS_HIDE_DELAY_LONG)

    this.video.seek(time)
  }

  renderControls = () => {
    const {
      fullscreen,
      paused,
      showControls,
      controlsOpacity,
      loading,
      duration,
      currentTime,
    } = this.state

    if (loading) {
      return (
        <View style={styles.loading}>
          <ActivityIndicator
            color={'white'}
            size={'large'}
          />
        </View>
      )
    }

    return (
      <TouchableOpacity
        style={styles.flex}
        activeOpacity={1}
        onPress={this.toggleControls}
      >
        <Animated.View
          style={[styles.controls, {opacity: controlsOpacity}]}
          pointerEvents={showControls ? 'box-none' : 'none'}
        >
          <TouchableOpacity
            activeOpacity={0.7}
            onPress={this.togglePaused}
          >
            <Image
              style={styles.icon}
              source={
                paused
                  ? require('./images/play.png')
                  : require('./images/pause.png')
              }
            />
          </TouchableOpacity>
          <View style={styles.bottomControls}>
            <VideoProgressControl
              style={styles.progress}
              duration={duration}
              currentTime={currentTime}
              onChange={this.handleProgressChange}
              onChangeStart={this.handleProgressChangeStart}
              onChangeEnd={this.handleProgressChangeEnd}
            />
            <TouchableOpacity
              activeOpacity={0.7}
              onPress={this.toggleFullscreen}
            >
              <Image
                style={styles.icon}
                source={
                  fullscreen
                    ? require('./images/fullscreen_exit.png')
                    : require('./images/fullscreen.png')
                }
              />
            </TouchableOpacity>
          </View>
        </Animated.View>
      </TouchableOpacity>
    )
  }

  onLoad = (e) => {
    const {duration} = e.nativeEvent

    this.setState({
      duration,
    })
  }

  onReadyForDisplay = () => {
    this.setState({
      loading: false,
    })
  }

  onSeekComplete = (e) => {
    this.setState({
      isSeeking: false,
    })
  }

  onProgress = (e) => {
    const {isScrubbing, isSeeking} = this.state

    if (isScrubbing || isSeeking) return

    const {currentTime} = e.nativeEvent

    this.setState({
      currentTime,
    })
  }

  render() {
    const {src, style, onError} = this.props
    const {fullscreen, paused, volume, muted} = this.state
    console.log('Where my player?');
    return (
      <OSPlayer
        ref={ref => this.video = ref}
        src={src}
        style={style}
        fullscreen={fullscreen}
        paused={paused}
        volume={volume}
        muted={muted}
        renderControls={this.renderControls}
        onLoad={this.onLoad}
        onReadyForDisplay={this.onReadyForDisplay}
        onProgress={this.onProgress}
        onSeekComplete={this.onSeekComplete}
        onError={onError}
      />
    )
  }
}
