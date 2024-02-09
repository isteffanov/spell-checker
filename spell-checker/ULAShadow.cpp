#include "ULAShadow.h"

ULAShadow::ULAShadow(int tolerance)
{
    this->bit_vectors = generate_bit_vectors_from_tolerance(2 * tolerance + 1);
    vector<ParametrizedState> states = ParametrizedState::generate_from_tolerance(tolerance);

    this->matrix = vector<vector<ULAState>>(states.size(), vector<ULAState>(bit_vectors.size()));
    for (int i = 0; i < states.size(); ++i) {
        const ParametrizedState& state = states[i];

        for (int j = 0; j < bit_vectors.size(); ++j) {
            const bit_vector_t& bit_vector = bit_vectors[j];
            ParametrizedState next_state = state.step(bit_vector, tolerance);
            int min_boundary = min_boundary_from_state(next_state);

            ParametrizedState subtracted = next_state.subtract_min_boundary(min_boundary);
            matrix[i][j] = ULAState(find_id_of_state(states, subtracted), min_boundary);
        }
    }

    this->max_i_minus_e = vector<int>(states.size(), 0);
    for (int i = 0; i < states.size(); ++i) {
        ParametrizedState& state = states[i];
        if (!state.container.empty()) {
            this->max_i_minus_e[i] = state.get_max_i_minus_e();
        }
    }
}

const vector<bit_vector_t> ULAShadow::generate_bit_vectors_from_tolerance(int n)
{
    vector<bit_vector_t> newly_generated = {bit_vector_t()};
    vector<bit_vector_t> previously_generated;
    vector<bit_vector_t> result;

    for (int i = 0; i < n + 1; ++i) {

        for (const bit_vector_t& bit_vector : newly_generated) {
            result.push_back(bit_vector);
        }

        previously_generated = newly_generated;
        newly_generated.clear();

        for (const bit_vector_t& bit_vector : previously_generated) {
            bit_vector_t bit_vector_0(bit_vector);
            bit_vector_0.push_back(0);
            newly_generated.push_back(bit_vector_0);

            bit_vector_t bit_vector_1(bit_vector);
            bit_vector_1.push_back(1);
            newly_generated.push_back(bit_vector_1);
        }
    }
    return result;
}

int ULAShadow::min_boundary_from_state(const ParametrizedState& parametrized_state)
{
    if (parametrized_state.container.empty()) {
        return 0;
    }

    int min_boundary = (*(parametrized_state.container.begin())).i;

    for (const Position& position : parametrized_state.container) {
        if (position.i < min_boundary) {
            min_boundary = position.i;
        }
    }

    return min_boundary;
}

int ULAShadow::find_id_of_state(const vector<ParametrizedState>& states, const ParametrizedState& state)
{
    if (state.container.empty()) {
        return -1;
    }

    for (int id = 0; id < states.size(); ++id) {
        if (states[id] == state) {
            return id;
        }
    }

    throw "ULAShadow::find_id_of_state : id of parametrized state not found";
}


