import _ from 'lodash';
import React, {Component} from 'react';
import {ListView, Text, View} from 'react-native';
import {connect} from 'react-redux';
import ListItem from '../common/ListItem';
import {moviesFetch} from '../../actions';

class TopMoviesScene extends Component {

  componentWillMount() {
    this.props.moviesFetch();

    this.createDataSource(this.props);
  }

  componentWillReceiveProps(nextProps) {
    this.createDataSource(nextProps);
  }

  createDataSource({movies}) {
    const ds = new ListView.DataSource({
      rowHasChanged: (r1, r2) => r1 !== r2
    });

    this.dataSource = ds.cloneWithRows(movies);
  }

  renderRow(movie) {
    return <ListItem movie={movie}/>;
  }

  render() {
    return (
      <ListView style={{marginTop: 0}}
                enableEmptySections
                dataSource={this.dataSource}
                renderRow={this.renderRow}
      />
    );
  }
}

const mapStateToProps = state => {
  const movies = _.map(state.topMovies, (val) => {
    return {...val};
  });

  return {movies};
};

export default connect(mapStateToProps, {moviesFetch})(TopMoviesScene);