#pragma once
#include<algorithm>
#include<vector>
#include<string>
#include<ostream>

using std::vector;
using std::string;
using std::ostream;

typedef std::vector<bool> bit_vector_t;

class Position {
public:
	int error_idx;
	int word_idx;

	Position(int _error_idx, int _word_idx);

	vector<Position> step(const bit_vector_t& bit_vector, const int tolerance) const;

	bool operator==(const Position& other) const;
	bool operator!=(const Position& other) const;
	bool operator<(const Position& rhs) const;
	bool inverse_less_than(const Position& rhs) const;

	bool subsumes(const Position& rhs) const;

	string to_string() const;
	friend ostream& operator<<(ostream& out, const Position& position);
};



