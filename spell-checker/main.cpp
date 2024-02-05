#pragma once
#include "gtest/gtest.h"
//#include "ParametrizedState.h"

//#include<iostream>

int main() {
	testing::InitGoogleTest();

	return RUN_ALL_TESTS();

	/*std::vector<ParametrizedState> result = ParametrizedState::generate_from_tolerance(2);
	for (const ParametrizedState& ps : result) {
		std::cout << ps;
	}

	std::cout << result.size();*/
}