import React, {Component} from 'react';
import {Image, Text, TouchableWithoutFeedback, View} from 'react-native';
import {Actions} from 'react-native-router-flux';
import {CardSection} from './index';
import RootSiblings from 'react-native-root-siblings';

import MovieDetailsScene from '../containers/MovieDetailsScene';

let sibling = null;

class ListItem extends Component {
  onRowPress() {
    //Actions.movieDetails({ movie: this.props.movie });
    this.addSibling();
  }

  addSibling() {
    sibling && sibling.destroy();
    sibling = new RootSiblings(
      <MovieDetailsScene movie={this.props.movie}/>
    );
  };

  render() {
    const {title} = this.props.movie;
    const image = this.props.movie['im:image'][2].label;

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
