#pragma once
#include"Position.h"

#include<set>

using std::set;

typedef std::set <Position, bool(*)(const Position&, const Position&)> position_set_t;

class ParametricState
{
public:
	static const std::set<Position> empty_parametrized_state;
	set<Position> container;

	ParametricState(const set<Position>& _positions = set<Position>());

	static vector<ParametricState> generate_from_tolerance(const int tolerance);
	static ParametricState reduced_union(const vector<ParametricState>& states);

	const ParametricState step(const bit_vector_t& bit_vector, const int tolerance) const;
	int get_min_boundary() const;
	ParametricState subtract_min_boundary(int min_boundary);
	
	int get_finalities();

	bool operator==(const ParametricState& other) const;
	bool operator<(const ParametricState& other) const;
	const Position& operator[](int index) const;

	string to_string() const;
	friend ostream& operator<<(ostream& out, const ParametricState& parametrized_state);
	vector<Position> generate_next_positions(const int tolerance) const;
	
private:
	static int get_minimum_index(const vector<ParametricState>& states, const vector<int>& indexes);
};

