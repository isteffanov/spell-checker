#include "gtest/gtest.h"
#include"ParametrizedState.h"

TEST(TestGenerateParametrizedStates, WithTolerance1) {
	std::vector<ParametrizedState> result = ParametrizedState::generate_from_tolerance(1);

	std::vector<ParametrizedState> expected = {
		ParametrizedState({Position(0, 0)}),
		ParametrizedState({Position(1, 0)}),
		ParametrizedState({Position(1, 0), Position(1, 1)}),
		ParametrizedState({Position(1, 0), Position(1, 2)}),
		ParametrizedState({Position(1, 0), Position(1, 1), Position(1, 2)})
	};

	std::string error_msg;
	for (const ParametrizedState& parametrized_state : result) {
		error_msg += (parametrized_state.to_string() + ", ");
	}

	EXPECT_EQ(result, expected);
}

TEST(TestGenerateParametrizedStates, WithTolerance2) {
	vector<ParametrizedState> result = ParametrizedState::generate_from_tolerance(2);
	
	vector<ParametrizedState> expected = {
	    ParametrizedState({Position(0, 0)}),
	    ParametrizedState({Position(1, 0)}),
	    ParametrizedState({Position(2, 0)}),
	    ParametrizedState({Position(1, 0), Position(1, 1)}),
	    ParametrizedState({Position(1, 0), Position(1, 2)}),
	    ParametrizedState({Position(1, 0), Position(2, 2)}),
	    ParametrizedState({Position(1, 0), Position(2, 3)}),
	    ParametrizedState({Position(2, 0), Position(1, 2)}),
	    ParametrizedState({Position(2, 0), Position(1, 3)}),
	    ParametrizedState({Position(2, 0), Position(2, 1)}),
	    ParametrizedState({Position(2, 0), Position(2, 2)}),
	    ParametrizedState({Position(2, 0), Position(2, 3)}),
	    ParametrizedState({Position(2, 0), Position(2, 4)}),
	    ParametrizedState({Position(1, 0), Position(1, 1), Position(1, 2)}),
	    ParametrizedState({Position(1, 0), Position(1, 1), Position(2, 3)}),
	    ParametrizedState({Position(1, 0), Position(2, 2), Position(2, 3)}),
	    ParametrizedState({Position(2, 0), Position(1, 2), Position(1, 3)}),
	    ParametrizedState({Position(2, 0), Position(1, 2), Position(2, 4)}),
	    ParametrizedState({Position(2, 0), Position(1, 3), Position(2, 1)}),
	    ParametrizedState({Position(2, 0), Position(2, 1), Position(2, 2)}),
	    ParametrizedState({Position(2, 0), Position(2, 1), Position(2, 3)}),
	    ParametrizedState({Position(2, 0), Position(2, 1), Position(2, 4)}),
	    ParametrizedState({Position(2, 0), Position(2, 2), Position(2, 3)}),
	    ParametrizedState({Position(2, 0), Position(2, 2), Position(2, 4)}),
	    ParametrizedState({Position(2, 0), Position(2, 3), Position(2, 4)}),
	    ParametrizedState({Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)}),
	    ParametrizedState({Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 4)}),
	    ParametrizedState({Position(2, 0), Position(2, 1), Position(2, 3), Position(2, 4)}),
	    ParametrizedState({Position(2, 0), Position(2, 2), Position(2, 3), Position(2, 4)}),
	    ParametrizedState({Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3), Position(2, 4)}),
	};
	
	EXPECT_EQ(result, expected);
}

TEST(TestGenerateParametrizedStates, WithTolerance3) {
	vector<ParametrizedState> result = ParametrizedState::generate_from_tolerance(3);

	EXPECT_EQ(result.size(), 196);
}


TEST(TestGenerateParametrizedStates, WithTolerance4) {
	vector<ParametrizedState> result = ParametrizedState::generate_from_tolerance(4);

	EXPECT_EQ(result.size(), 1353);
}


TEST(TestReducedUnion, KeepsPositionsSorted) {
	ParametrizedState ps1({ Position(0, 0), Position(1, 3) });
	ParametrizedState ps2({ Position(0, 1) });

	ParametrizedState expected({ Position(0, 0), Position(0, 1), Position(1, 3) });
	ParametrizedState result = ParametrizedState::reduced_union({ ps1, ps2 });

	EXPECT_EQ(result, expected);
}

TEST(TestReducedUnion, RemovesSubsumedPositions) {

	ParametrizedState ps1({ Position(0, 0), Position(1, 3) });
	ParametrizedState ps2({ Position(0, 1) });
	ParametrizedState ps3({ Position(1, 1) });

	ParametrizedState expected({ Position(0, 0), Position(0, 1), Position(1, 3) });
	ParametrizedState result = ParametrizedState::reduced_union({ ps1, ps2, ps3 });

	EXPECT_EQ(result, expected);
}

TEST(TestReducedUnion, RemovesDublicates) {

	ParametrizedState ps1({ Position(1, 0), Position(1, 1) });
	ParametrizedState ps2({ Position(1, 1), Position(1, 2)});

	ParametrizedState expected({ Position(1, 0), Position(1, 1), Position(1, 2) });
	ParametrizedState result = ParametrizedState::reduced_union({ ps1, ps2 });

	EXPECT_EQ(result, expected);
}

TEST(TestStep, VariousTransitions1) {
	ParametrizedState state({ Position(1, 0), Position(1, 1) });
	ParametrizedState expected({ Position(2, 0), Position(2, 1), Position(2, 2) });

	ParametrizedState result = state.step({ 0, 0, 0 }, 2);

	EXPECT_EQ(result, expected);
}

TEST(TestStep, VariousTransitions2) {
	ParametrizedState state({ Position(1, 0), Position(1, 1) });
	ParametrizedState expected({ });

	ParametrizedState result = state.step({ 0, 0, 0 }, 1);

	EXPECT_EQ(result, expected);
}

TEST(TestStep, VariousTransitions3) {
	ParametrizedState state({ Position(1, 0), Position(1, 1) });
	ParametrizedState expected({ Position(1, 2), Position(2, 0)});

	ParametrizedState result = state.step({ 0, 1, 0 }, 2);

	EXPECT_EQ(result, expected);
}

TEST(TestStep, VariousTransitions4) {
	ParametrizedState state({ Position(1, 0), Position(1, 1) });
	ParametrizedState expected({ Position(1, 0) });

	ParametrizedState result = state.step({ 1, 0, 0 }, 2);
	result = result.subtract_min_boundary(result.get_min_boundary());

	EXPECT_EQ(result, expected);
}

//TEST(QjMi, Guza) {
//	ParametrizedState state({ Position(2, 0), Position(2, 4), Position(3, 2) });
//	vector<Position> candidates = state.generate_next_positions(2);
//	vector<Position> expected = { Position(3, 3), Position(3, 4), Position(3, 5) };
//
//	EXPECT_EQ(candidates, expected);
//	
//}