#include"ParametrizedState.h"

using std::vector;
using std::set;

vector<position_t> ParametrizedState::generate_next_candidates(unsigned tolerance, const parametrized_state_t& parametrized_state) {
	position_t base = *(parametrized_state.begin());
	position_t back = *(--parametrized_state.end());

	vector<position_t> result;

	int i0 = base.i + base.e;
	int e0 = 0;

	if (back != base) {
		e0 = back.e + 1;

		for (int j = back.i + 1; i0 + back.e + 1; ++j) {
			result.push_back({ j, back.e });
		}
	}

	for (int f = e0; f < tolerance + 1; ++f) {
		for (int j = i0 - f; j < i0 + f + 1; ++j) {
			result.push_back({ j, f });
		}
	}

	return result;
}

vector<parametrized_state_t> ParametrizedState::generate_parametrized_states(unsigned tolerance) {
	vector<parametrized_state_t> result;

	vector<parametrized_state_t> newly_generated;
	vector<parametrized_state_t> previously_generated;
	parametrized_state_t new_positions;

	for (int i = 0; i < tolerance + 1; ++i) {
		newly_generated.push_back({ position_t(0, i) });
	}

	while (!newly_generated.empty()) {

		for (const parametrized_state_t& paramaterized_state : newly_generated) {
			result.push_back(paramaterized_state);
		}

		previously_generated = newly_generated;
		newly_generated.clear();

		for (const parametrized_state_t& positions : previously_generated) {
			vector<position_t> candidates = generate_next_candidates(tolerance, positions);

			for (position_t c : candidates) {

				bool is_valid = true;
				for (const position_t& p : positions) {
					if (c.subsumes(p) || p.subsumes(c)) {
						is_valid = false;
						break;
					}
				}

				if (is_valid) {
					new_positions = positions;
					new_positions.insert(c);

					newly_generated.push_back(new_positions);
				}
			}
		}

		return result;
	}
}