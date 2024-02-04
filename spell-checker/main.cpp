#pragma once
#include<iostream>
#include"ParametrizedState.h"
#include"position.h"

#include<vector>
#include<cassert>


void test_position_t() {
    position_t p = position_t(0, 0);

    std::vector<position_t> expected = { position_t(0, 1) };
    assert(p.transition({ 1, 0 }, 3) == expected);
    assert(p.transition({ 1, 1, 1, 0, 1 }, 3) == expected);
    assert(p.transition({ 1, 0, 0, 0, 0 }, 3) == expected);

    expected = { position_t(1, 0), position_t(1, 1) };
    assert(p.transition({ 0 }, 3) == expected);
    assert(p.transition({ 0, 0, 0 }, 3) == expected);

    expected = { position_t(1, 0) };
    assert(p.transition({}, 3) == expected);

    expected = { position_t(1, 0), position_t(1, 1) };
    assert(p.transition({ 0, 0, 0, 1 }, 3) == expected);
    assert(p.transition({ 0, 0, 0, 1, 1, 1 }, 3) == expected);
    assert(p.transition({ 0, 0, 0, 1, 0, 0 }, 3) == expected);
}

void test_transition_remove_results_above_tolerance() {
    auto p = position_t(1, 0);
    assert(p.transition({ 1, 0 }, 1) == std::vector<position_t> { position_t(1, 1) });
    assert(p.transition({ 0, 0 }, 1) == std::vector<position_t> { });
    assert(p.transition({}, 1) == std::vector<position_t> { });
}


void test_subsumes() {

    auto p = position_t(0, 0);

    assert(p.subsumes(p));
    assert(p.subsumes(position_t(1, 0)));
    assert(p.subsumes(position_t(1, 1)));
    assert(p.subsumes(position_t(1, -1)));
    assert(p.subsumes(position_t(88, 88)));

    assert(!p.subsumes(position_t(2, 3)));
    assert(!p.subsumes(position_t(0, 1)));
}

void test_generate_parametrized_states_1()
{
    vector<parametrized_state_t> result = ParametrizedState::generate_parametrized_states(1);

    vector<parametrized_state_t> expected = {
        parametrized_state_t({position_t(0, 0)}),
        parametrized_state_t({position_t(1, 0)}),
        parametrized_state_t({position_t(1, 0), position_t(1, 1)}),
        parametrized_state_t({position_t(1, 0), position_t(1, 2)}),
        parametrized_state_t({position_t(1, 0), position_t(1, 1), position_t(1, 2)})
    };

    assert(result == expected);
}

void test_generate_parametrized_states_2()
{
    vector<parametrized_state_t> result = ParametrizedState::generate_parametrized_states(2);

    vector<parametrized_state_t> expected = {
        parametrized_state_t({position_t(0, 0)}),
        parametrized_state_t({position_t(1, 0)}),
        parametrized_state_t({position_t(2, 0)}),
        parametrized_state_t({position_t(1, 0), position_t(1, 1)}),
        parametrized_state_t({position_t(1, 0), position_t(1, 1)}),
        parametrized_state_t({position_t(1, 0), position_t(2, 2)}),
        parametrized_state_t({position_t(1, 0), position_t(2, 3)}),
        parametrized_state_t({position_t(2, 0), position_t(1, 2)}),
        parametrized_state_t({position_t(2, 0), position_t(1, 3)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 1)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 2)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 3)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 4)}),
        parametrized_state_t({position_t(1, 0), position_t(1, 1), position_t(1, 2)}),
        parametrized_state_t({position_t(1, 0), position_t(1, 1), position_t(2, 3)}),
        parametrized_state_t({position_t(1, 0), position_t(2, 2), position_t(2, 3)}),
        parametrized_state_t({position_t(2, 0), position_t(1, 2), position_t(1, 3)}),
        parametrized_state_t({position_t(2, 0), position_t(1, 2), position_t(2, 4)}),
        parametrized_state_t({position_t(2, 0), position_t(1, 3), position_t(2, 1)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 1), position_t(2, 2)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 1), position_t(2, 3)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 1), position_t(2, 4)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 2), position_t(2, 3)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 2), position_t(2, 4)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 3), position_t(2, 4)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 1), position_t(2, 2), position_t(2, 3)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 1), position_t(2, 2), position_t(2, 4)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 1), position_t(2, 3), position_t(2, 4)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 2), position_t(2, 3), position_t(2, 4)}),
        parametrized_state_t({position_t(2, 0), position_t(2, 1), position_t(2, 2), position_t(2, 3), position_t(2, 4)}),
    };

    assert(result == expected);
}




int main() {
	test_position_t();
	test_subsumes();
	test_transition_remove_results_above_tolerance();

	////TestParametrizedState tps;
	//tp.test_generate_parametrized_states_1();
	//tp.test_generate_parametrized_states_2();

}