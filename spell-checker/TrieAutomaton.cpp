#include "TrieAutomaton.h"

TrieAutomaton::TrieAutomaton(const dictionary_t& dictionary, alphabet_t alphabet)
{
	for (const string& word : dictionary) {
		this->add_word(word, alphabet);
	}
}

const node_t& TrieAutomaton::step(const node_t& node, char symbol) const
{
	return this->transitions[node].at(symbol);
}

bool TrieAutomaton::contains(const string& word) const
{
	node_t n_id = 0;
	for (char letter : word) {
		if (this->transitions[n_id].find(letter) != this->transitions[n_id].end()) {
			n_id = this->transitions[n_id].at(letter);
		}
		else {
			return false;
		}
	}

	return this->final_nodes[n_id];
}

bool TrieAutomaton::is_final(const node_t& node) const
{
	return final_nodes[node];
}

vector<char> TrieAutomaton::get_next_symbols(const node_t& node) const
{
	vector<char> next_symbols;
	for (std::pair<char, node_t> item : this->transitions[node]) {
		next_symbols.push_back(item.first);
	}

	return next_symbols;
}

dictionary_t TrieAutomaton::get_dictionary() const
{
	return dictionary_t();
}

void TrieAutomaton::add_word(const string& word, alphabet_t& alphabet)
{
	if (word.empty()) {
		return;
	}

	if (this->transitions.empty()) {
		this->transitions.push_back(node_map_t());
		this->final_nodes.push_back(false);
	}

	node_t n_id = 0;
	for (char symbol : word) {
		alphabet.insert(symbol);

		if (this->transitions[n_id].find(symbol) == this->transitions[n_id].end()) {
			node_t next_id = unsigned(this->transitions.size());
			this->transitions.push_back(node_map_t());
			this->final_nodes.push_back(false);
			this->transitions[n_id][symbol] = next_id;
			n_id = next_id;
		}
		else {
			n_id = this->transitions[n_id].at(symbol);
		}

	}
	this->final_nodes[n_id] = true;
}

bool TrieAutomaton::is_final(const node_t& node)
{
	return this->final_nodes[node];
}

const alphabet_t TrieAutomaton::get_node_alphabet(const node_t& node)
{
	alphabet_t node_alphabet;

	for (std::pair<char, node_t> node_map_el : this->transitions[node]) {
		node_alphabet.insert(node_map_el.first);
	}

	return node_alphabet;
}

const node_t& TrieAutomaton::get_child_node(const node_t& node, char symbol)
{
	return this->transitions[node].at(symbol);
}

const node_t TrieAutomaton::get_root() const
{
	return 0;
}
