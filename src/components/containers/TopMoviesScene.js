import _ from 'lodash';
import React, { Component } from 'react';
import { ListView } from 'react-native';
import { connect } from 'react-redux';
import { moviesFetch } from '../../actions';
import { Card, CardSection, Button } from '../common';

class TopMoviesScene extends Component {
	componentWillMount() {
    this.props.moviesFetch();

    this.createDataSource(this.props);
  }

	createDataSource({ movies }) {
    const ds = new ListView.DataSource({
      rowHasChanged: (r1, r2) => r1 !== r2
    });

    this.dataSource = ds.cloneWithRows(movies);
  }

	renderRow(employee) {
    //return <ListItem employee={employee} />;
  }

	render(){
    return (
         <Text>Hello</Text>
    );
  }

  render() {
    return (
      <ListView
        enableEmptySections
        dataSource={this.dataSource}
        renderRow={this.renderRow}
      />
    );
  }

}

const mapStateToProps = state => {
  const movies = _.map(state.movies, (val) => {
    return { ...val};
  });

  return { movies };
};

export default connect(mapStateToProps, { moviesFetch })(TopMoviesScene);