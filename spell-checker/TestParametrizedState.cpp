#include "gtest/gtest.h"
#include"ParametrizedState.h"

TEST(TestGenerateParametrizedStates, WithToleranceOne) {
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

TEST(TestGenerateParametrizedStates, WithToleranceTwo) {
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
	
	EXPECT_EQ(result, expected) << result.size() << ", " << expected.size() << "\n";
}