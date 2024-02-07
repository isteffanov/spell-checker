#include "UniversalLevenshteinAutomaton.h"
#include<cassert>

UniversalLevenshteinAutomaton::UniversalLevenshteinAutomaton(
    unsigned _tolerance, 
    const string& _word, 
    const alphabet_t& _alphabet) : tolerance(_tolerance), word(_word)
{
    this->ula_shadow = ULAShadowMemoizer::get_instance()->get_ula_shadow_for_tolerance(_tolerance);
    this->i_minus_e_threshold = _word.length() - _tolerance;
}

int UniversalLevenshteinAutomaton::bit_vector_to_id(const bit_vector_t& bit_vector)
{
    if (bit_vector.empty()) {
        return 0;
    }

    int lower_bound = int(pow(2, bit_vector.size())) - 1; 
    int upper_bound = int(pow(2, bit_vector.size() + 1)) - 1;

    for (int i = 0; i < bit_vector.size(); ++i) {
        if (bit_vector[i] == 1) {
            lower_bound += (upper_bound - lower_bound) / 2;
        }
        else {
            upper_bound -= (upper_bound - lower_bound) / 2;
        }
    }

    assert(lower_bound + 1 == upper_bound);
    return lower_bound;

}

int UniversalLevenshteinAutomaton::transition_to_bit_vector_id(int min_boundary, char symbol) const
{
    bit_vector_t bit_vector;

    int range = min_boundary + 2 * tolerance + 1;
    int upper_bound = range < word.length() ? range : word.length();

    for (char word_letter : this->word.substr(min_boundary, upper_bound - min_boundary)) {
        bit_vector.push_back(word_letter == symbol);
    }

    return bit_vector_to_id(bit_vector);
}

ULAState UniversalLevenshteinAutomaton::step(const ULAState& ula_state, char symbol) const
{
    int bit_vector_id = transition_to_bit_vector_id(ula_state.min_boundary, symbol);
    ULAState next_state = this->ula_shadow.matrix[ula_state.id][bit_vector_id];
    
    return ULAState(next_state.id, next_state.min_boundary + ula_state.min_boundary);
}

bool UniversalLevenshteinAutomaton::is_final(const ULAState& ula_state) const
{
    int i_minus_e = this->ula_shadow.max_i_minus_e[ula_state.id];

    return i_minus_e + ula_state.min_boundary >= this->i_minus_e_threshold;
}

const ULAState UniversalLevenshteinAutomaton::get_root() const
{
    return ULAState(0, 0);
}
