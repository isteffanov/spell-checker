#pragma once
#include"Position.h"

#include<set>

using std::set;

class ParametrizedState
{
public:
	static const std::set<Position> empty_parametrized_state;
	std::set<Position> container;

	ParametrizedState(set<Position> _positions = set<Position>());

	static vector<ParametrizedState> generate_from_tolerance(int tolerance);

	bool operator==(const ParametrizedState& other) const;

	string to_string() const;
	friend ostream& operator<<(ostream& out, const ParametrizedState& parametrized_state);
	
private:
	vector<Position> generate_next_positions(int tolerance) const;
};

