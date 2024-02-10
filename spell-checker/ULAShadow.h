#pragma once
#include"ParametricState.h"
#include"ULAState.h"
#include<vector>

using std::vector;

typedef std::vector<bool> bit_vector_t;

class ULAShadow
{
public:
	vector<bit_vector_t> bit_vectors;
	vector<vector<ULAState>> ula_states;
	vector<int> finalities;

	ULAShadow(const int tolerance = 0);
	ULAShadow(const vector<bit_vector_t>& bit_vectors, const vector<vector<ULAState>>& ula_states, const vector<int>& finalities);

	static const vector<bit_vector_t> generate_bit_vectors_from_length(const int n);
	static int min_boundary_from_state(const ParametricState& parametrized_state);

	static int find_id_of_state(const vector<ParametricState>& states, const ParametricState& state);
};

