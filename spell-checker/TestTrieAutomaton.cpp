#include "gtest/gtest.h"
#include "TrieAutomaton.h"

TEST(TestTrieAutomatonConstruction, EmptyCase) {

	dictionary_t dictionary = {};

	TrieAutomaton trie = TrieAutomaton(dictionary);

	EXPECT_EQ(trie.transitions.size(), 0);
}

TEST(TestTrieAutomatonConstruction, CaseSingleWord) {

	dictionary_t dictionary = {
		"cat"
	};

	TrieAutomaton trie = TrieAutomaton(dictionary);

	EXPECT_EQ(trie.transitions.size(), 4);
}

TEST(TestTrieAutomatonConstruction, CaseCommonPrefixOfTwoWords) {

	dictionary_t dictionary = {
		"cat",
		"caterpillar"
	};

	TrieAutomaton trie = TrieAutomaton(dictionary);

	EXPECT_EQ(trie.transitions.size(), 12);
}

TEST(TestTrieAutomatonConstruction, CaseSplitPathWithOneFinal) {

	dictionary_t dictionary = {
		"cat",
		"caterpillar",
		"carburetor"
	};

	TrieAutomaton trie = TrieAutomaton(dictionary);

	EXPECT_EQ(trie.transitions.size(), 20);
}

TEST(TestTrieAutomatonContainsWord, PositiveCase) {

	dictionary_t dictionary = {
		"cat",
		"caterpillar",
		"carburetor"
	};

	TrieAutomaton trie = TrieAutomaton(dictionary);

	EXPECT_TRUE(trie.contains("cat"));
	EXPECT_TRUE(trie.contains("caterpillar"));
	EXPECT_TRUE(trie.contains("carburetor"));
}

TEST(TestTrieAutomatonContainsWord, NegativeCase) {

	dictionary_t dictionary = {
		"cat",
		"caterpillar",
		"carburetor"
	};

	TrieAutomaton trie = TrieAutomaton(dictionary);

	EXPECT_FALSE(trie.contains("dog"));
	EXPECT_FALSE(trie.contains("worm"));
	EXPECT_FALSE(trie.contains("engine"));
}

TEST(TestTrieAutomatonContainsWord, PrematurePositive) {

	dictionary_t dictionary = {
		"cat",
		"caterpillar",
		"carburetor"
	};

	TrieAutomaton trie = TrieAutomaton(dictionary);

	EXPECT_FALSE(trie.contains("ca"));
	EXPECT_FALSE(trie.contains("caterpillars"));
	EXPECT_FALSE(trie.contains("car"));
}