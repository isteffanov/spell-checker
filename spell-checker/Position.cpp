#include "Position.h"

Position::Position(int _error_idx, int _word_idx) : error_idx(_error_idx), word_idx(_word_idx) {}

vector<Position> Position::step(const bit_vector_t& bit_vector, const int tolerance) const
{
	vector<Position> result;

	if (bit_vector.size() == 0) {
		result.push_back(Position(this->error_idx+1, this->word_idx));
	}
	else if (bit_vector.front() == 1) {
		result.push_back(Position(this->error_idx, this->word_idx + 1));
	}
	else {
		result.push_back(Position(this->error_idx + 1, this->word_idx));
		result.push_back(Position(this->error_idx + 1, this->word_idx + 1));

		for (int b = 1; b < bit_vector.size(); ++b) {
			bool bit = bit_vector[b];
			if (bit) {
				result.push_back(Position(this->error_idx + b, this->word_idx + b + 1));
				break;
			}
		}
	}

	vector<Position> filtered_result;
	for (auto position : result) {
		if (position.error_idx <= tolerance) {
			filtered_result.push_back(position);
		}
	}

	return filtered_result;
}

bool Position::operator==(const Position& other) const
{
	return (this->error_idx == other.error_idx) && (this->word_idx == other.word_idx);
}

bool Position::operator!=(const Position& other) const
{
	return !(*this == other);
}

bool Position::operator<(const Position& rhs) const
{
	if (this->word_idx < rhs.word_idx) {
		return true;
	}
	if (this->word_idx == rhs.word_idx && this->error_idx < rhs.error_idx) {
		return true;
	}

	return false;

	//return this->inverse_less_than(rhs);
}

bool Position::inverse_less_than(const Position& rhs) const
{
	if (this->error_idx < rhs.error_idx) {
		return true;
	}
	if (this->error_idx == rhs.error_idx && this->word_idx < rhs.word_idx) {
		return true;
	}

	return false;
}

bool Position::subsumes(const Position& other) const
{
	return (this->error_idx <= other.error_idx) && (std::abs(this->word_idx - other.word_idx) <= other.error_idx - this->error_idx);
}

string Position::to_string() const
{
	return "Position(" + std::to_string(this->error_idx) + ", " + std::to_string(this->word_idx) + ")";
}

ostream& operator<<(ostream& out, const Position& position)
{
	out << position.to_string();
	return out;
}
