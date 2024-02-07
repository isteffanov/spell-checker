#pragma once
#include"TrieAutomaton.h"
#include"UniversalLevenshteinAutomaton.h"

#include<string>
#include<vector>
#include<stack>

using std::string;
using std::vector;
using std::stack;

struct correction_node_t {
	node_t trie_node;
	ULAState ula_node;
	string prefix;
};


class SpellChecker
{
private:

	TrieAutomaton trie;

	const dictionary_t& dictionary;
	const int tolerance;

public:

	SpellChecker(dictionary_t _dictionary, int _tolerance);

	bool check_word(const string& query) const;
	vector<string> correct_word(const string& query) const;


};

