#include "position.h"

bool position_t::operator==(const position_t& other) const
{
	return this->e == other.e && this->i == other.i;
}

bool position_t::operator!=(const position_t& other) const
{
	return !(*this == other);
}

bool position_t::operator<(const position_t& rhs) const
{
	if (this->e < rhs.e) {
		return true;
	}
	if (this->e == rhs.e && this->i < rhs.i) {
		return true;
	}

	return false;
}

vector<position_t> position_t::transition(bit_vector_t bit_vector, unsigned tolerance)
{
	vector<position_t> result;

	if (bit_vector.size() == 0) {
		result = { { e + 1, i } };
	}
	else if (bit_vector[0] == 1) {
		result = { { e, i + 1 } };
	}
	else {
		result = { { e + 1, i }, { e + 1, i + 1 } };

		for (int k = 1; k < bit_vector.size(); ++k) {
			bool bit = bit_vector[k];
			if (bit == 1) {
				result.push_back({ e + k + 1, i + k + 2 });
				break;
			}
		}
	}

	vector<position_t> filtered_result;
	for (auto position : result) {
		if (position.e <= tolerance) {
			filtered_result.push_back(position);
		}
	}

	return filtered_result;
}

bool position_t::subsumes(const position_t& other) const
{
	return this->e <= other.e &&
		std::abs(int(this->i) - int(other.i)) <= other.e - this->e;
}
