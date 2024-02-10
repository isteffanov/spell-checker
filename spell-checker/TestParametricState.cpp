#include "gtest/gtest.h"
#include"ParametricState.h"

TEST(TestGenerateParametricStates, WithTolerance1) {
	std::vector<ParametricState> result = ParametricState::generate_from_tolerance(1);

	std::vector<ParametricState> expected = {
		ParametricState({Position(0, 0)}),
		ParametricState({Position(1, 0)}),
		ParametricState({Position(1, 0), Position(1, 1)}),
		ParametricState({Position(1, 0), Position(1, 2)}),
		ParametricState({Position(1, 0), Position(1, 1), Position(1, 2)})
	};

	std::string error_msg;
	for (const ParametricState& parametrized_state : result) {
		error_msg += (parametrized_state.to_string() + ", ");
	}

	EXPECT_EQ(result, expected);
}

TEST(TestGenerateParametricStates, WithTolerance2) {
	vector<ParametricState> result = ParametricState::generate_from_tolerance(2);
	
	vector<ParametricState> expected = {
	    ParametricState({Position(0, 0)}),
	    ParametricState({Position(1, 0)}),
	    ParametricState({Position(2, 0)}),
	    ParametricState({Position(1, 0), Position(1, 1)}),
	    ParametricState({Position(1, 0), Position(1, 2)}),
	    ParametricState({Position(1, 0), Position(2, 2)}),
	    ParametricState({Position(1, 0), Position(2, 3)}),
	    ParametricState({Position(2, 0), Position(1, 2)}),
	    ParametricState({Position(2, 0), Position(1, 3)}),
	    ParametricState({Position(2, 0), Position(2, 1)}),
	    ParametricState({Position(2, 0), Position(2, 2)}),
	    ParametricState({Position(2, 0), Position(2, 3)}),
	    ParametricState({Position(2, 0), Position(2, 4)}),
	    ParametricState({Position(1, 0), Position(1, 1), Position(1, 2)}),
	    ParametricState({Position(1, 0), Position(1, 1), Position(2, 3)}),
	    ParametricState({Position(1, 0), Position(2, 2), Position(2, 3)}),
	    ParametricState({Position(2, 0), Position(1, 2), Position(1, 3)}),
	    ParametricState({Position(2, 0), Position(1, 2), Position(2, 4)}),
	    ParametricState({Position(2, 0), Position(1, 3), Position(2, 1)}),
	    ParametricState({Position(2, 0), Position(2, 1), Position(2, 2)}),
	    ParametricState({Position(2, 0), Position(2, 1), Position(2, 3)}),
	    ParametricState({Position(2, 0), Position(2, 1), Position(2, 4)}),
	    ParametricState({Position(2, 0), Position(2, 2), Position(2, 3)}),
	    ParametricState({Position(2, 0), Position(2, 2), Position(2, 4)}),
	    ParametricState({Position(2, 0), Position(2, 3), Position(2, 4)}),
	    ParametricState({Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)}),
	    ParametricState({Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 4)}),
	    ParametricState({Position(2, 0), Position(2, 1), Position(2, 3), Position(2, 4)}),
	    ParametricState({Position(2, 0), Position(2, 2), Position(2, 3), Position(2, 4)}),
	    ParametricState({Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3), Position(2, 4)}),
	};
	
	EXPECT_EQ(result, expected);
}

TEST(TestGenerateParametricStates, WithTolerance3) {
	vector<ParametricState> result = ParametricState::generate_from_tolerance(3);

	EXPECT_EQ(result.size(), 196);
}


TEST(TestGenerateParametricStates, WithTolerance4) {
	vector<ParametricState> result = ParametricState::generate_from_tolerance(4);

	EXPECT_EQ(result.size(), 1353);
}


TEST(TestReducedUnion, KeepsPositionsSorted) {
	ParametricState ps1({ Position(0, 0), Position(1, 3) });
	ParametricState ps2({ Position(0, 1) });

	ParametricState expected({ Position(0, 0), Position(0, 1), Position(1, 3) });
	ParametricState result = ParametricState::reduced_union({ ps1, ps2 });

	EXPECT_EQ(result, expected);
}

TEST(TestReducedUnion, RemovesSubsumedPositions) {

	ParametricState ps1({ Position(0, 0), Position(1, 3) });
	ParametricState ps2({ Position(0, 1) });
	ParametricState ps3({ Position(1, 1) });

	ParametricState expected({ Position(0, 0), Position(0, 1), Position(1, 3) });
	ParametricState result = ParametricState::reduced_union({ ps1, ps2, ps3 });

	EXPECT_EQ(result, expected);
}

TEST(TestReducedUnion, RemovesDublicates) {

	ParametricState ps1({ Position(1, 0), Position(1, 1) });
	ParametricState ps2({ Position(1, 1), Position(1, 2)});

	ParametricState expected({ Position(1, 0), Position(1, 1), Position(1, 2) });
	ParametricState result = ParametricState::reduced_union({ ps1, ps2 });

	EXPECT_EQ(result, expected);
}

TEST(TestStep, VariousTransitions1) {
	ParametricState state({ Position(1, 0), Position(1, 1) });
	ParametricState expected({ Position(2, 0), Position(2, 1), Position(2, 2) });

	ParametricState result = state.step({ 0, 0, 0 }, 2);

	EXPECT_EQ(result, expected);
}

TEST(TestStep, VariousTransitions2) {
	ParametricState state({ Position(1, 0), Position(1, 1) });
	ParametricState expected({ });

	ParametricState result = state.step({ 0, 0, 0 }, 1);

	EXPECT_EQ(result, expected);
}

TEST(TestStep, VariousTransitions3) {
	ParametricState state({ Position(1, 0), Position(1, 1) });
	ParametricState expected({ Position(1, 2), Position(2, 0)});

	ParametricState result = state.step({ 0, 1, 0 }, 2);

	EXPECT_EQ(result, expected);
}

TEST(TestStep, VariousTransitions4) {
	ParametricState state({ Position(1, 0), Position(1, 1) });
	ParametricState expected({ Position(1, 0) });

	ParametricState result = state.step({ 1, 0, 0 }, 2);
	result = result.subtract_min_boundary(result.get_min_boundary());

	EXPECT_EQ(result, expected);
}

//TEST(QjMi, Guza) {
//	ParametricState state({ Position(2, 0), Position(2, 4), Position(3, 2) });
//	vector<Position> candidates = state.generate_next_positions(2);
//	vector<Position> expected = { Position(3, 3), Position(3, 4), Position(3, 5) };
//
//	EXPECT_EQ(candidates, expected);
//	
//}