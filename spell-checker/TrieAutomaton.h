#pragma once
#include<string>
#include<vector>
#include<unordered_set>
#include<unordered_map>


typedef std::vector<std::string> dictionary_t;
typedef std::unordered_set<char> alphabet_t;
typedef unsigned node_t;

using std::string;
using std::vector;

typedef std::unordered_map<char, node_t> node_map_t;
typedef std::vector<node_map_t> delta_t;

typedef std::vector<bool> final_t;

class TrieAutomaton {
public:

	delta_t transitions;
	final_t final_nodes;

	TrieAutomaton(const dictionary_t& dictionary = dictionary_t(), alphabet_t alphabet = alphabet_t());

	const node_t& step(const node_t& node, char symbol) const;

	bool contains(const string& word) const;
	bool is_final(const node_t& node) const;

	vector<char> get_next_symbols(const node_t& node) const;
	dictionary_t get_dictionary() const;

	const node_t get_root() const;
private:

	void add_word(const string& word, alphabet_t& alphabet);
	bool is_final(const node_t& node);
	const alphabet_t get_node_alphabet(const node_t& node);
	const node_t& get_child_node(const node_t& node, char symbol);

};