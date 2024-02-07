#include "ULAState.h"

ULAState::ULAState(int _id, int _min_boundary) : id(_id), min_boundary(_min_boundary) {}

bool ULAState::operator==(const ULAState& rhs) const
{
    return this->id == rhs.id && this->min_boundary == rhs.min_boundary;
}

ostream& operator<<(ostream& out, const ULAState& ula_state)
{
    out << "ULAState(" << ula_state.id << ", " << ula_state.min_boundary << ")";
    return out;
}
