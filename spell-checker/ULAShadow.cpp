#include "ULAShadow.h"
#include<iostream>

ULAShadow::ULAShadow(const int tolerance)
{
    
    std::cout << "... constructing shadow ..." << std::endl;

    this->bit_vectors = generate_bit_vectors_from_length(2 * tolerance + 1);
    vector<ParametricState> states = ParametricState::generate_from_tolerance(tolerance);

    this->ula_states = vector<vector<ULAState>>(states.size(), vector<ULAState>(bit_vectors.size()));
    for (int i = 0; i < states.size(); ++i) {
        const ParametricState& state = states[i];

        for (int j = 0; j < bit_vectors.size(); ++j) {
            const bit_vector_t& bit_vector = bit_vectors[j];
            ParametricState next_state = state.step(bit_vector, tolerance);
            int min_boundary = min_boundary_from_state(next_state);

            ParametricState subtracted = next_state.subtract_min_boundary(min_boundary);
            ula_states[i][j] = ULAState(find_id_of_state(states, subtracted), min_boundary);
        }
    }

    this->finalities = vector<int>(states.size(), 0);
    for (int i = 0; i < states.size(); ++i) {
        ParametricState& state = states[i];
        if (!state.container.empty()) {
            this->finalities[i] = state.get_finalities();
        }
    }
}

ULAShadow::ULAShadow(
    const vector<bit_vector_t>& _bit_vectors, 
    const vector<vector<ULAState>>& _ula_states, 
    const vector<int>& _finalities) : bit_vectors(_bit_vectors), ula_states(_ula_states), finalities(_finalities) { }

const vector<bit_vector_t> ULAShadow::generate_bit_vectors_from_length(const int n)
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

int ULAShadow::min_boundary_from_state(const ParametricState& parametrized_state)
{
    if (parametrized_state.container.empty()) {
        return 0;
    }

    int min_boundary = (*(parametrized_state.container.begin())).word_idx;

    for (const Position& position : parametrized_state.container) {
        if (position.word_idx < min_boundary) {
            min_boundary = position.word_idx;
        }
    }

    return min_boundary;
}

int ULAShadow::find_id_of_state(const vector<ParametricState>& states, const ParametricState& state)
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


