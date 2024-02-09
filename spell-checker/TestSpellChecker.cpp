#include "gtest/gtest.h"
#include"SpellChecker.h"

TEST(TestSpellCheckerCheckWord, DirectWord) {
	dictionary_t dictionary = {
		"car",
		"cat",
		"catto",
		"latte",
		"pillates"
	};

	SpellChecker spell_checker(dictionary, 1);

	EXPECT_TRUE(spell_checker.check_word("car"));
	EXPECT_TRUE(spell_checker.check_word("cat"));
	EXPECT_TRUE(spell_checker.check_word("catto"));

}

TEST(TestSpellCheckerCheckWord, PrefixGivesFalse) {
	dictionary_t dictionary = {
		"car",
		"cat",
		"catto",
		"latte",
	};

	SpellChecker spell_checker(dictionary, 1);

	EXPECT_FALSE(spell_checker.check_word("c"));
	EXPECT_FALSE(spell_checker.check_word("ca"));
	EXPECT_FALSE(spell_checker.check_word("l"));
	EXPECT_FALSE(spell_checker.check_word("la"));
	EXPECT_FALSE(spell_checker.check_word("lat"));
	EXPECT_FALSE(spell_checker.check_word("latt"));

}

TEST(TestSpellCheckerCheckWord, AddingLettersBehindGivesFalse) {
	dictionary_t dictionary = {
		"car",
		"cat",
		"catto",
		"latte",
	};

	SpellChecker spell_checker(dictionary, 1);

	EXPECT_FALSE(spell_checker.check_word("cars"));
	EXPECT_FALSE(spell_checker.check_word("carr"));
}

TEST(TestSpellCheckerCorrectWord, WithTolerance1) {
	dictionary_t dictionary = {
		"car",
		"cat",
		"catto",
		"latte",
		"pillates"
	};

	SpellChecker spell_checker(dictionary, 1);

	vector<string> result = spell_checker.correct_word("cap");
	vector<string> expected = { "cat", "car" };

	EXPECT_EQ(result, expected);
}

TEST(TestSpellCheckerCorrectWord, WithTolerance2) {
	dictionary_t dictionary = {
		"car",
		"rat",
		"bat",
		"carp",
		"caterpillar",
		"kangaroo",
		"camel",
		"dog",
		"hog",
		"snake",
		"crow",
		"raven",
		"mate"
	};
	SpellChecker spell_checker(dictionary, 2);

	vector<string> result = spell_checker.correct_word("dog");
	vector<string> expected = { "hog", "dog"};

	EXPECT_EQ(result, expected);

	result = spell_checker.correct_word("cat");
	expected = { "mate", "bat", "rat", "car", "carp" };


	EXPECT_EQ(result, expected);
}