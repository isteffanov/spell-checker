#include "ULAShadowMemoizer.h"
#include<algorithm>
#include<iterator>

ULAShadowMemoizer* ULAShadowMemoizer::singleton_instance = nullptr;

void ULAShadowMemoizer::save(const string& file_path, const int tolerance)
{
	// write to the file
// size of bitvector, then bitvector elements

// number of vectors
// for each size of vector then their values

	memoizer[tolerance] = std::make_unique<ULAShadow>(tolerance);
	std::ofstream output_file(file_path, std::fstream::out);
	output_file << memoizer[tolerance]->bit_vectors.size() << " ";
	for (const auto& bitVector : memoizer[tolerance]->bit_vectors)
	{
		output_file << bitVector.size() << " ";
		for (const bool element : bitVector)
		{
			output_file << element << " ";
		}
	}

	output_file << memoizer[tolerance]->ula_states.size() << " ";
	for (const auto& states : memoizer[tolerance]->ula_states)
	{
		output_file << states.size() << " ";
		for (const auto& state : states)
		{
			output_file << state.id << " " << state.min_boundary << " ";
		}
	}

	output_file << memoizer[tolerance]->finalities.size() << " ";
	for (const auto& finilStates : memoizer[tolerance]->finalities)
	{
		output_file << finilStates << " ";
	}
}

void ULAShadowMemoizer::load(std::ifstream& file, const int tolerance)
{
	size_t vector_size = 0;
	file >> vector_size;
	std::vector<bit_vector_t> bit_vectors;
	bit_vectors.reserve(vector_size);
	for (size_t i = 0; i < vector_size; ++i)
	{
		size_t currentVectorSize = 0;
		file >> currentVectorSize;
		bit_vector_t bits;
		bits.reserve(currentVectorSize);
		for (size_t j = 0; j < currentVectorSize; ++j)
		{
			bool currentValue;
			file >> currentValue;
			bits.push_back(currentValue);
		}
		bit_vectors.push_back(bits);
	}

	size_t numberOfVectorOfStates = 0;
	file >> numberOfVectorOfStates;
	vector<vector<ULAState>> vectorOfStates;
	vectorOfStates.reserve(numberOfVectorOfStates);
	for (size_t i = 0; i < numberOfVectorOfStates; ++i)
	{
		size_t currentNumberOfStates;
		file >> currentNumberOfStates;
		vector<ULAState> states;
		states.reserve(currentNumberOfStates);
		for (size_t j = 0; j < currentNumberOfStates; ++j)
		{
			int id = 0;
			int min_boundary = 0;
			file >> id >> min_boundary;
			states.push_back(ULAState{ id, min_boundary });
		}
		vectorOfStates.push_back(states);
	}

	size_t numberOfFinalities = 0;
	file >> numberOfFinalities;
	vector<int> finalities;
	finalities.reserve(numberOfFinalities);
	for (size_t i = 0; i < numberOfFinalities; ++i)
	{
		int currentFinality = 0;
		file >> currentFinality;
		finalities.push_back(currentFinality);
	}
	memoizer[tolerance] = std::make_unique<ULAShadow>(bit_vectors, vectorOfStates, finalities);
}

string ULAShadowMemoizer::get_filename_from_tolerance(const int tolerance)
{
	return "./ula_shadow_memo_" + std::to_string(tolerance) + ".txt";
}

ULAShadowMemoizer::ULAShadowMemoizer() {}

ULAShadowMemoizer* ULAShadowMemoizer::get_instance()
{
	if (singleton_instance == nullptr) {
		singleton_instance = new ULAShadowMemoizer();
	}

	return singleton_instance;
}

const ULAShadow& ULAShadowMemoizer::get_ula_shadow_for_tolerance(int tolerance)
{
	if (memoizer.find(tolerance) == memoizer.end()) {
		const string file_path = get_filename_from_tolerance(tolerance);
		std::ifstream file(file_path, std::fstream::in);
		if (file.good())
		{
			load(file, tolerance);
		}
		else
		{
			save(file_path, tolerance);
		}

	}

	return *memoizer[tolerance];
}
