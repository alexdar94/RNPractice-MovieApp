import {
  MOVIES_FETCH,
} from './types';
import axios from 'axios';

export const moviesFetch = () => {
	return (dispatch) => {
		axios.get('https://itunes.apple.com/us/rss/topmovies/limit=25/json')
		  .then((response) => {
		  	console.log(response.data);
        dispatch({ type: MOVIES_FETCH, payload:  response.data});
      })
		  .catch(function (error) {
		    console.log(error);
		  });
  };
};