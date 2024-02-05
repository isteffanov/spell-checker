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
	int e;
	int i;

	Position(int _e, int _i);

	vector<Position> step(bit_vector_t bit_vector, unsigned tolerance) const;

	bool operator==(const Position& other) const;
	bool operator!=(const Position& other) const;
	bool operator<(const Position& rhs) const;
	
	bool subsumes(const Position& rhs) const;

	string to_string() const;
	friend ostream& operator<<(ostream& out, const Position& position);
};



