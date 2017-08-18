import {
  MOVIES_FETCH
} from '../actions/types';

const INITIAL_STATE = {
	topMovies:''
};

export default (state = INITIAL_STATE, action) => {
  switch (action.type) {
    case MOVIES_FETCH:
      return {...state, topMovies:action.payload};
    default:
      return state;
  }
};
