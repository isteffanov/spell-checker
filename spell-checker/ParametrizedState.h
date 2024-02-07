#pragma once
#include"Position.h"

#include<set>

using std::set;

class ParametrizedState
{
public:
	static const std::set<Position> empty_parametrized_state;
	std::set<Position> container;

	ParametrizedState(const set<Position>& _positions = set<Position>());

	static vector<ParametrizedState> generate_from_tolerance(int tolerance);
	static ParametrizedState reduced_union(const vector<ParametrizedState>& states);

	const ParametrizedState step(bit_vector_t bit_vector, int tolerance) const;
	int get_min_boundary() const;
	ParametrizedState subtract_min_boundary(int min_boundary);
	
	int get_max_i_minus_e();

	bool operator==(const ParametrizedState& other) const;
	const Position& operator[](int index) const;

	string to_string() const;
	friend ostream& operator<<(ostream& out, const ParametrizedState& parametrized_state);
	
private:
	vector<Position> generate_next_positions(int tolerance) const;
	static int get_minimum_index(const vector<ParametrizedState>& states, const vector<int>& indexes);
};

