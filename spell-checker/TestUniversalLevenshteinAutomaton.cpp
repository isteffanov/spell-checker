#include "gtest/gtest.h"
#include"UniversalLevenshteinAutomaton.h"


TEST(TestBitVectorToId, WithSize0) {
	bit_vector_t bit_vector = {};

	int result = UniversalLevenshteinAutomaton::bit_vector_to_id(bit_vector);
	int expected = 0;

	EXPECT_EQ(result, expected);
}

TEST(TestBitVectorToId, WithSize1) {
	bit_vector_t bit_vector = {0};

	int result = UniversalLevenshteinAutomaton::bit_vector_to_id(bit_vector);
	int expected = 1;

	EXPECT_EQ(result, expected);

	bit_vector = { 1 };

	result = UniversalLevenshteinAutomaton::bit_vector_to_id(bit_vector);
	expected = 2;

	EXPECT_EQ(result, expected);
}

TEST(TestBitVectorToId, WithSize2) {
	bit_vector_t bit_vector = { 0, 0 };

	int result = UniversalLevenshteinAutomaton::bit_vector_to_id(bit_vector);
	int expected = 3;

	EXPECT_EQ(result, expected);

	bit_vector = { 0, 1 };
	result = UniversalLevenshteinAutomaton::bit_vector_to_id(bit_vector);
	expected = 4;

	EXPECT_EQ(result, expected);

	bit_vector = { 1, 0 };
	result = UniversalLevenshteinAutomaton::bit_vector_to_id(bit_vector);
	expected = 5;

	EXPECT_EQ(result, expected);


	bit_vector = { 1, 1 };
	result = UniversalLevenshteinAutomaton::bit_vector_to_id(bit_vector);
	expected = 6;

	EXPECT_EQ(result, expected);
}