#pragma once
#include<ostream>

using std::ostream;

class ULAState {
public:
	int id;
	int min_boundary;

	ULAState(int _id = -1, int _min_boundary = -1);

	bool is_empty() const;

	bool operator==(const ULAState& rhs) const;
	friend ostream& operator<<(ostream& out, const ULAState& ula_state);
};

