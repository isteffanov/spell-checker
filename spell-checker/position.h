#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<set>

using namespace std;

typedef std::vector<bool> bit_vector_t;

class position_t {
public:
	int e;
	int i;

	position_t(int _e, int _i) : e(_e), i(_i) {};

	bool operator==(const position_t& other) const;
	bool operator!=(const position_t& other) const;
	bool operator<(const position_t& rhs) const;

	vector<position_t> transition(bit_vector_t bit_vector, unsigned tolerance);

	bool subsumes(const position_t& other) const;
};


