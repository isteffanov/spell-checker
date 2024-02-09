#include "SpellChecker.h"

SpellChecker::SpellChecker(
	dictionary_t _dictionary, 
	int _tolerance) : dictionary(_dictionary), tolerance(_tolerance)
{
	this->trie = TrieAutomaton(_dictionary);
}

bool SpellChecker::check_word(const string& query) const
{
	return trie.contains(query);
}

vector<string> SpellChecker::correct_word(const string& query) const
{
	const UniversalLevenshteinAutomaton ula(tolerance, query);

	vector<string> corrections;

	stack<correction_node_t> front;
	front.push({ trie.get_root(), ula.get_root(), "" });

	while (!front.empty()) {
		correction_node_t current = front.top();
		front.pop();

		node_t trie_node = current.trie_node;
		ULAState ula_node = current.ula_node;
		string prefix = current.prefix;

		if (ula_node.is_empty()) {
			continue;
		}

		if (trie.is_final(trie_node) && ula.is_final(ula_node)) {
			corrections.push_back(prefix);
		}

		for (char symbol : trie.get_next_symbols(trie_node)) {
			const node_t& next_trie_node = trie.step(trie_node, symbol);
			const ULAState& next_ula_node = ula.step(ula_node, symbol);

			if (!next_ula_node.is_empty()) {
				front.push({
					next_trie_node,
					next_ula_node,
					prefix + symbol
				});
			}
		}
	}

	return corrections;
}
