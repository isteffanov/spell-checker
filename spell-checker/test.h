#pragma once
#include "position.h"
#include "ParametrizedState.h"

#include<vector>
#include<cassert>


class TestPosition {
public:
    void test_position_t();
    void test_transition_remove_results_above_tolerance();
    void test_subsumes();

    void test_generate_parametrized_states_1();
    void test_generate_parametrized_states_2();

};

//class TestParametrizedState {
//public:
//    void test_generate_parametrized_states_1();
//    void test_generate_parametrized_states_2();
//};