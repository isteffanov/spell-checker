#include "gtest/gtest.h"
#include "Position.h"

TEST(TestPositionStep, WhenStepRight) {
	Position p(0, 0);
	std::vector<Position> expected = { Position(0, 1) };

	EXPECT_EQ(p.step({ 1, 0 }, 3), expected);
	EXPECT_EQ(p.step({ 1, 1, 1, 0, 1 }, 3), expected);
	EXPECT_EQ(p.step({ 1, 0, 0, 0, 0 }, 3), expected);
}

TEST(TestPositionStep, WhenStepHasTwoOptions) {
	Position p(0, 0);
	std::vector<Position> expected = { Position(1, 0), Position(1, 1) };

	EXPECT_EQ(p.step({ 0 }, 3), expected);
	EXPECT_EQ(p.step({ 0, 0, 0 }, 3), expected);
}

TEST(TestPositionStep, WithEmptyBitVector) {
	Position p(0, 0);
	std::vector<Position> expected = { Position(1, 0) };

	EXPECT_EQ(p.step({}, 3), expected);
}

TEST(TestPositionStep, WithTwoOptionsAndZerosInBitVec) {
	Position p(0, 0);
	std::vector<Position> expected = { Position(1, 0), Position(1, 1), Position(3, 4)};

	EXPECT_EQ(p.step({ 0, 0, 0, 1 }, 3), expected);
	EXPECT_EQ(p.step({ 0, 0, 0, 1, 1, 1 }, 3), expected);
	EXPECT_EQ(p.step({ 0, 0, 0, 1, 0, 0 }, 3), expected);
}

TEST(TestPositionStep, RemovesResultsAboveTolerance1) {
	Position p(1, 0);
	std::vector<Position> expected = { Position(1, 1) };

	EXPECT_EQ(p.step({ 1, 0 }, 1), expected);
}

TEST(TestPositionStep, RemovesResultsAboveTolerance2) {
	Position p(1, 0);
	std::vector<Position> expected;

	EXPECT_EQ(p.step({ 0, 0 }, 1), expected);
}

TEST(TestPositionStep, RemovesResultsAboveTolerance3) {
	Position p(1, 0);
	std::vector<Position> expected;

	EXPECT_EQ(p.step({}, 1), expected);
}

TEST(TestSubsumes, WithItself) {
	Position p(0, 0);
	EXPECT_TRUE(p.subsumes(p));

	p = Position(1, 2);
	EXPECT_TRUE(p.subsumes(p));

	p = Position(22, 10);
	EXPECT_TRUE(p.subsumes(p));
}

TEST(TestSubsumes, WithPositiveCase) {
	Position p(0, 0);

	EXPECT_TRUE(p.subsumes(Position(1, 0)));
	EXPECT_TRUE(p.subsumes(Position(1, 1)));
	EXPECT_TRUE(p.subsumes(Position(1, -1)));
	EXPECT_TRUE(p.subsumes(Position(22, 22)));
}

TEST(TestSubsumes, WithNegativeCase) {
	Position p(0, 0);

	EXPECT_FALSE(p.subsumes(Position(2, 3)));
	EXPECT_FALSE(p.subsumes(Position(0, 1)));
}
