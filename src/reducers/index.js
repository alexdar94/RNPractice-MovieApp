import {
  MOVIES_FETCH
} from '../actions/types';

const INITIAL_STATE = {
	movies:''
};

export default (state = INITIAL_STATE, action) => {
  switch (action.type) {
    case MOVIES_FETCH:
      return {...state, movies:action.payload};
    default:
      return state;
  }
};
