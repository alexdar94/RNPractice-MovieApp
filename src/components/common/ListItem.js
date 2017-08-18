import React, { Component } from 'react';
import { Image, Text, TouchableWithoutFeedback, View } from 'react-native';
import { Actions } from 'react-native-router-flux';
import { CardSection } from './index';

class ListItem extends Component {
  onRowPress() {
    // Actions.employeeEdit({ employee: this.props.employee });
  }

  render() {
    const { title } = this.props.movies;
		const image = this.props.movies['im:image'][2].label;
		console.log(this.props.movies);
    return (
      <TouchableWithoutFeedback onPress={this.onRowPress.bind(this)}>
        <View>
          <CardSection style={{flexDirection: 'row'}}>
          	<Image style={{width: 50, height: 50}} source={{uri: image}}/>
            <Text style={styles.titleStyle}>
              {title.label}
            </Text>
          </CardSection>
        </View>
      </TouchableWithoutFeedback>
    );
  }
}

const styles = {
  titleStyle: {
    fontSize: 18,
    paddingLeft: 15
  }
};

export default ListItem;
