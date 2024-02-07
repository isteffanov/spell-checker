#pragma once
#include<string>
#include<unordered_set>
#include<vector>

#include"ULAShadow.h"
#include"ULAShadowMemoizer.h"

using std::string;
using std::unordered_set;

typedef std::unordered_set<char> alphabet_t;
typedef std::vector<bool> bit_vector_t;

class UniversalLevenshteinAutomaton
{

	string word;
	unsigned tolerance;
	ULAShadow ula_shadow;
	int i_minus_e_threshold;

public:
	UniversalLevenshteinAutomaton(unsigned tolerance, const string& word, const alphabet_t& alphabet = alphabet_t());

	static int bit_vector_to_id(const bit_vector_t& bit_vector);
	int transition_to_bit_vector_id(int min_boundary, char symbol) const;

	ULAState step(const ULAState& ula_state, char symbol) const;

	bool is_final(const ULAState& ula_state) const;

	const ULAState get_root() const;
};

