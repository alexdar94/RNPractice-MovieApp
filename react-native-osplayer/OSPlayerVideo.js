import React, { PureComponent, PropTypes } from 'react'
import Modal from 'react-native-root-modal'
import {
  requireNativeComponent,
  View,
} from 'react-native'

export default class OSPlayer extends PureComponent {

  static propTypes = {
    ...View.propTypes,
    src: PropTypes.object,
    paused: PropTypes.bool,
    muted: PropTypes.bool,
    volume: PropTypes.number,
    onPlayerInit: PropTypes.func,
    onVideoLoadStart: PropTypes.func,
    onVideoLoad: PropTypes.func,
    onVideoError: PropTypes.func,
    onVideoProgress: PropTypes.func,
    onVideoSeekComplete: PropTypes.func,
    onReadyForDisplay: PropTypes.func,
  }

  setNativeProps(nativeProps) {
    this.root.setNativeProps(nativeProps)
  }

  seek = (time) => {
    this.setNativeProps({seek: time})
  }

  assignRoot = (ref) => {
    this.root = ref
  }

  render() {
    return (
      <RCTOSPlayer
        ref={this.assignRoot}
        {...this.props}
      />
    )
  }
}

const RCTOSPlayer = requireNativeComponent('RCTOSPlayer', OSPlayer, {
  nativeOnly: {
    seek: true,
    playerId: true,
  },
})
