#include "ParametrizedState.h"
#include<algorithm>
#include<cassert>

ParametrizedState::ParametrizedState(const set<Position>& _positions): container(_positions){}

const ParametrizedState ParametrizedState::step(bit_vector_t bit_vector, int tolerance) const
{
	if (this->container.empty()) {
		return ParametrizedState::empty_parametrized_state;
	}

	bit_vector_t position_bit_vector;
	set<Position> next_positions;
	vector<ParametrizedState> possible_transitions;
	for (const Position& position : this->container) {

		position_bit_vector = bit_vector_t((position.i >= bit_vector.size() ? bit_vector.end() : bit_vector.begin() + position.i), bit_vector.end());
		next_positions.clear();

		for (const Position& next_position : position.step(position_bit_vector, tolerance)) {
			next_positions.insert(next_position);
		}

		possible_transitions.push_back(ParametrizedState(next_positions));
	}

	return reduced_union(possible_transitions);
}

ParametrizedState ParametrizedState::reduced_union(const vector<ParametrizedState>& states)
{
	int i;
	vector<int> indexes(states.size());
	set<Position> result_container;

	while ((i = get_minimum_index(states, indexes)) >= 0) {
		const Position& candidate = states[i][indexes[i]];

		bool is_valid = true;
		for (const Position& position : result_container) {
			if (position.subsumes(candidate)) {
				is_valid = false;
			}
		}

		if (is_valid) {
			result_container.insert(candidate);
		}
		indexes[i] += 1;
	}

	return ParametrizedState(result_container);
}

int ParametrizedState::get_max_i_minus_e()
{
	Position max_pos = *(this->container.begin());
	int result = max_pos.i - max_pos.e;

	for (const Position& pos : this->container) {
		if (pos.i - pos.e > result) {
			result = pos.i - pos.e;
		}
	}

	return result;
}

vector<ParametrizedState> ParametrizedState::generate_from_tolerance(const int tolerance)
{
	vector<ParametrizedState> result;

	vector<ParametrizedState> newly_generated;
	ParametrizedState new_positions;

	for (int e = 0; e < tolerance + 1; ++e) {
		newly_generated.push_back(ParametrizedState({ Position(e, 0) }));
	}

	while (!newly_generated.empty()) {

		for (const ParametrizedState& paramaterized_state : newly_generated) {
			result.push_back(paramaterized_state);
		}

		vector<ParametrizedState> previously_generated(newly_generated);
		newly_generated.clear();

		for (const ParametrizedState& positions : previously_generated) {
			vector<Position> candidates = positions.generate_next_positions(tolerance);
			for (const Position& c : candidates) {

				bool is_valid = true;
				for (const Position& p : positions.container) {
					if (c.subsumes(p) || p.subsumes(c)) {
						is_valid = false;
						break;
					}
				}

				if (is_valid) {
					new_positions = positions;
					new_positions.container.insert(c);

					newly_generated.push_back(new_positions);
				}
			}
		}
	}
	// remove duplicates
	//auto it = result.begin();
	//auto el = result[result.size() - 2];

	if (result.size() > 1) {
		for (auto it = result.begin(); it != result.end() - 2; ++it) {
			for (auto it_after = it + 1; it_after != result.end(); ++it_after) {
				if (*it == *it_after) {
					it_after = result.erase(it_after);
				}
			}
		}
	}

	if (result.size() > 1) {
		for (int i = 0; i < result.size() - 1; ++i) {
			for (int j = i + 1; j < result.size(); ++j) {
				if (result[i] == result[j]) {
					result.erase(result.begin() + j);
					j--;
				}
			}
		}
	}


	//std::unique(result.begin(), result.end());


	return result;
}

bool ParametrizedState::operator==(const ParametrizedState& other) const
{
	return this->container == other.container;
}

bool ParametrizedState::operator<(const ParametrizedState& other) const
{
	return false;
}

string ParametrizedState::to_string() const
{
	string result = "{ ";
	for (const Position& pos : container) {
		result += (pos.to_string() + ", ");
	}

	result += "}";

	return result;
}

ParametrizedState ParametrizedState::subtract_min_boundary(int min_boundary)
{
	ParametrizedState subtracted;
	for (const Position& position : this->container) {
		subtracted.container.insert(Position(position.e, position.i - min_boundary));
	}

	return subtracted;
}

int ParametrizedState::get_min_boundary() const
{
	if (this->container.empty()) {
		return 0;
	}

	int min_boundary = (*(this->container.begin())).i;

	for (const Position& position : this->container) {
		if (position.i < min_boundary) {
			min_boundary = position.i;
		}
	}

	return min_boundary;
}


vector<Position> ParametrizedState::generate_next_positions(int tolerance) const
{
	assert(("Container not empty in generate_next_positions", !container.empty()));

	if (container.empty()) {
		return {};
	}

	int foo = container.size();

	Position base = *(container.begin());
	Position back = *(--container.end());

	/*auto base_it = std::min_element(container.begin(), container.end());
	auto back_it = std::max_element(container.begin(), container.end());*/


	vector<Position> result;

	int i0 = base.e + base.i;
	int e0 = 0;

	if (back != base) {
		e0 = back.e + 1;

		for (int new_i = back.i + 1; new_i < i0 + back.e + 1; ++new_i) {
			result.push_back(Position(back.e, new_i));
		}
	}

	for (int new_e = e0; new_e < tolerance + 1; ++new_e) {
		for (int new_i = i0 - new_e; new_i < i0 + new_e + 1; ++new_i) {
			result.push_back(Position(new_e, new_i));
		}
	}

	return result;
}

const Position& ParametrizedState::operator[](int index) const
{
	auto curr = container.begin();
	while (index != 0) {
		curr = ++curr;
		index -= 1;
	}

	return *curr;
}

int ParametrizedState::get_minimum_index(const vector<ParametrizedState>& states, const vector<int>& indexes)
{
	vector<int> possible_results;
	for (int i = 0; i < indexes.size(); ++i) {
		if (indexes[i] < states[i].container.size()) {
			possible_results.push_back(i);
		}
	}

	if (possible_results.empty()) {
		return -1;
	}

	int min_index = possible_results[0];
	for (int i : possible_results) {
		if (states[i][indexes[i]].inverse_less_than(states[min_index][indexes[min_index]])) {
			min_index = i;
		}
	}

	return min_index;
}


ostream& operator<<(ostream& out, const ParametrizedState& parametrized_state)
{
	out << parametrized_state.to_string() << "\n";
	return out;
}

const std::set<Position> ParametrizedState::empty_parametrized_state = std::set<Position>();