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
  PanResponder,
} from 'react-native'

const styles = StyleSheet.create({
  container: {
    // Won't render without a color - needs to render to handle touches
    backgroundColor: 'rgba(0,0,0,0)',
  },
})

const clamp = (value, min, max) => Math.max(min, Math.min(max, value))

export default class Trackbar extends Component {

  static propTypes = {
    onTouch: PropTypes.func,
    onTouchStart: PropTypes.func,
    onTouchEnd: PropTypes.func,
  }

  static defaultProps = {
    onTouch: () => {},
    onTouchStart: () => {},
    onTouchEnd: () => {},
  }

  state = {
    width: 0,
  }

  panResponder = {}

  componentWillMount() {
    this.panResponder = PanResponder.create({
      onStartShouldSetPanResponder: this.handleStartShouldSetPanResponder,
      onPanResponderGrant: this.handlePanResponderGrant,
      onPanResponderMove: this.handlePanResponderMove,
      onPanResponderRelease: this.handlePanResponderRelease,
    })
  }

  calculateTouchRatio = (e, gestureState) => {
    const {onTouch} = this.props
    const {width} = this.state
    const {locationX} = e.nativeEvent
    const {dx} = gestureState

    const distance = locationX + dx
    return clamp(distance / width, 0, 1)
  }

  // Should we become active when the user presses down?
  handleStartShouldSetPanResponder = () => true

  handlePanResponderGrant = (e, gestureState) => {
    const {onTouchStart} = this.props

    onTouchStart(this.calculateTouchRatio(e, gestureState))
  }

  handlePanResponderMove = (e, gestureState) => {
    const {onTouch} = this.props

    onTouch(this.calculateTouchRatio(e, gestureState))
  }

  handlePanResponderRelease = (e, gestureState) => {
    const {onTouchEnd} = this.props

    onTouchEnd(this.calculateTouchRatio(e, gestureState))
  }

  handleLayout = (e) => {
    const {width} = e.nativeEvent.layout

    if (width === this.state.width) return

    this.setState({width})
  }

  render() {
    const {style, duration, currentTime} = this.props

    return (
      <View
        onLayout={this.handleLayout}
        {...this.panResponder.panHandlers}
        style={[styles.container, style]}
      />
    )
  }
}
