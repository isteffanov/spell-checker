#pragma once
#include"ParametrizedState.h"
#include"ULAState.h"
#include<vector>

using std::vector;

typedef std::vector<bool> bit_vector_t;

class ULAShadow
{
public:
	vector<bit_vector_t> bit_vectors;
	vector<vector<ULAState>> matrix;
	vector<int> max_i_minus_e;

	ULAShadow(int tolerance);

	static const vector<bit_vector_t> generate_bit_vectors_from_tolerance(int tolerance);
	static int min_boundary_from_state(const ParametrizedState& parametrized_state);

	static int find_id_of_state(const vector<ParametrizedState>& states, const ParametrizedState& state);
};

