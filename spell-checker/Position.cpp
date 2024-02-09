#include "Position.h"

Position::Position(int _e, int _i) : e(_e), i(_i) {}

vector<Position> Position::step(bit_vector_t bit_vector, unsigned tolerance) const
{
	vector<Position> result;

	if (bit_vector.size() == 0) {
		result.push_back(Position(this->e+1, this->i));
	}
	else if (bit_vector.front() == 1) {
		result.push_back(Position(this->e, this->i + 1));
	}
	else {
		result.push_back(Position(this->e + 1, this->i));
		result.push_back(Position(this->e + 1, this->i + 1));

		for (int b = 1; b < bit_vector.size(); ++b) {
			bool bit = bit_vector[b];
			if (bit) {
				result.push_back(Position(this->e + b, this->i + b + 1));
				break;
			}
		}
	}

	vector<Position> filtered_result;
	for (auto position : result) {
		if (position.e <= tolerance) {
			filtered_result.push_back(position);
		}
	}

	return filtered_result;
}

bool Position::operator==(const Position& other) const
{
	return (this->e == other.e) && (this->i == other.i);
}

bool Position::operator!=(const Position& other) const
{
	return !(*this == other);
}

bool Position::operator<(const Position& rhs) const
{
	if (this->i < rhs.i) {
		return true;
	}
	if (this->i == rhs.i && this->e < rhs.e) {
		return true;
	}

	return false;

	//return this->inverse_less_than(rhs);
}

bool Position::inverse_less_than(const Position& rhs) const
{
	if (this->e < rhs.e) {
		return true;
	}
	if (this->e == rhs.e && this->i < rhs.i) {
		return true;
	}

	return false;
}

bool Position::subsumes(const Position& other) const
{
	return (this->e <= other.e) && (std::abs(this->i - other.i) <= other.e - this->e);
}

string Position::to_string() const
{
	return "Position(" + std::to_string(this->e) + ", " + std::to_string(this->i) + ")";
}

ostream& operator<<(ostream& out, const Position& position)
{
	out << position.to_string();
	return out;
}
