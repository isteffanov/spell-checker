#include "ParametrizedState.h"

ParametrizedState::ParametrizedState(set<Position> _positions): container(_positions){}

vector<ParametrizedState> ParametrizedState::generate_from_tolerance(int tolerance)
{
	vector<ParametrizedState> result;

	vector<ParametrizedState> newly_generated;
	vector<ParametrizedState> previously_generated;
	ParametrizedState new_positions;

	for (int e = 0; e < tolerance + 1; ++e) {
		newly_generated.push_back(ParametrizedState({ Position(e, 0) }));
	}

	while (!newly_generated.empty()) {

		for (const ParametrizedState& paramaterized_state : newly_generated) {
			result.push_back(paramaterized_state);
		}

		previously_generated = newly_generated;
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
	return result;
}

bool ParametrizedState::operator==(const ParametrizedState& other) const
{
	return(this->container == other.container);
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

vector<Position> ParametrizedState::generate_next_positions(int tolerance) const
{
	Position base = *(container.begin());
	Position back = *(--container.end());

	vector<Position> result;

	int i0 = base.e + base.i;
	int e0 = 0;

	if (back != base) {
		e0 = back.e + 1;

		for (int j = back.i + 1; j < i0 + back.e + 1; ++j) {
			result.push_back({ back.e, j });
		}
	}

	for (int f = e0; f < tolerance + 1; ++f) {
		for (int j = i0 - f; j < i0 + f + 1; ++j) {
			result.push_back({ f, j });
		}
	}

	return result;
}


ostream& operator<<(ostream& out, const ParametrizedState& parametrized_state)
{
	out << parametrized_state.to_string() << "\n";
	return out;
}
