import React, { Component } from 'react';
import { Scene, Router, Actions } from 'react-native-router-flux';

import TopMoviesScene from './components/containers/TopMoviesScene';
import MovieDetailsScene from './components/containers/MovieDetailsScene';

class RouterComponent extends Component {

	render(){
		return (
			<Router>
				<Scene key="root">
					<Scene key="topMovies" initial component={TopMoviesScene} title="Top Movies" />
					<Scene key="movieDetails" component={MovieDetailsScene} title="Movie" />
				</Scene>
			</Router>
		);
	}
}

export default RouterComponent;