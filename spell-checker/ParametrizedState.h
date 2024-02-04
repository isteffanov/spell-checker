#pragma once
#include "position.h"

#include<vector>
#include<set>


typedef std::set<position_t> parametrized_state_t;
parametrized_state_t empty_parametrized_state = parametrized_state_t();

class ParametrizedState {
public:
	static vector<position_t> generate_next_candidates(unsigned tolerance, const parametrized_state_t& parametrized_state);
	static vector<parametrized_state_t> generate_parametrized_states(unsigned tolerance);
};