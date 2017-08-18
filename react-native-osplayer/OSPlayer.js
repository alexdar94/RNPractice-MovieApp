import React, { Component, PropTypes } from 'react'
import {
  StyleSheet,
  View,
  Text,
  Button,
  StatusBar,
  NativeModules,
  TouchableWithoutFeedback,
  Animated,
} from 'react-native'
import Modal from 'react-native-root-modal'
import OSPlayerVideo from './OSPlayerVideo'

const { OSPlayerManager } = NativeModules

OSPlayerManager.reset()

const styles = StyleSheet.create({
  fullscreen: {
    position: 'absolute',
    top: 0,
    right: 0,
    bottom: 0,
    left: 0,
  },
  background: {
    backgroundColor: 'black',
  },
  base: {
    overflow: 'hidden',
  },
})

export default class OSPlayer extends Component {

  static propTypes = {
    renderControls: PropTypes.func,
    onLoad: PropTypes.func,
    onError: PropTypes.func,
    onProgress: PropTypes.func,
    onSeekComplete: PropTypes.func,
    fullscreen: PropTypes.bool,
  }

  static defaultProps = {
    renderControls: () => null,
    onLoad: () => {},
    onError: () => {},
    onProgress: () => {},
    onSeekComplete: () => {},
    fullscreen: false,
  }

  state = {
    fullscreen: this.props.fullscreen || false,
    playerId: -1,
    error: null,
    opacity: new Animated.Value(1),
  }

  componentWillMount() {
    this.requestPlayer()
  }

  componentWillUnmount() {
    this.releasePlayer()
  }

  componentWillReceiveProps(nextProps) {
    if (this.props.fullscreen !== nextProps.fullscreen) {
      this.setState({fullscreen: !!nextProps.fullscreen})
    }
  }

  componentWillUpdate(nextProps, nextState) {
    if (!this.state.fullscreen && nextState.fullscreen) {
      this.fadeIn()
    }
  }

  fadeIn() {
    const {opacity} = this.state

    opacity.setValue(1)

    Animated.timing(opacity, {toValue: 0}).start()
  }

  async requestPlayer() {
    let playerId

    try {
      playerId = await OSPlayerManager.createPlayer()
    } catch (e) {
      this.setState({error: e.toString()})
      return
    }

    this.setState({playerId})
  }

  releasePlayer() {
    const {playerId} = this.state

    if (playerId === -1) return

    OSPlayerManager.destroyPlayer(playerId)
  }

  presentFullscreenPlayer = () => {
    this.setState({fullscreen: true})
  }

  dismissFullscreenPlayer = () => {
    this.setState({fullscreen: false})
  }

  renderControls() {
    const {renderControls} = this.props
    const {fullscreen} = this.state

    return renderControls({
      fullscreen,
      presentFullscreen: this.presentFullscreenPlayer,
      dismissFullscreen: this.dismissFullscreenPlayer,
    })
  }

  seek(time) {
    this.player.seek(time)
  }

  renderPlayer(style) {
    const {onLoadStart, onLoad, onProgress, onSeekComplete, onError} = this.props
    const {playerId, opacity, fullscreen} = this.state

    return (
      <View style={[styles.base, style]}>
        <View style={[styles.fullscreen, styles.background]} />
        <OSPlayerVideo
          ref={ref => this.player = ref}
          {...this.props}
          onVideoLoadStart={onLoadStart}
          onVideoLoad={onLoad}
          onVideoError={onError}
          onVideoProgress={onProgress}
          onVideoSeekComplete={onSeekComplete}
          style={styles.fullscreen}
          fullscreen={this.state.fullscreen}
          playerId={playerId}
        />
        {fullscreen && (
          <Animated.View
            style={[styles.fullscreen, styles.background, {opacity}]}
          />
        )}
        <View style={styles.fullscreen}>
          {this.renderControls()}
        </View>
      </View>
    )
  }

  renderModal() {
    const {opacity} = this.state

    return (
      <Modal
        style={[styles.fullscreen, styles.background]}
        visible
        animationType={'none'}
      >
        <StatusBar
          hidden
          animated={false}
        />
        {this.renderPlayer(styles.fullscreen)}
      </Modal>
    )
  }

  render() {
    const {style} = this.props
    const {playerId, fullscreen} = this.state

    if (playerId === -1) return null

    return fullscreen ? this.renderModal() : this.renderPlayer(style)
  }
}
