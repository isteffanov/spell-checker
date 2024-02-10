#include "ULAShadowMemoizer.h"
#include<algorithm>
#include<iterator>

ULAShadowMemoizer* ULAShadowMemoizer::singleton_instance = nullptr;

void ULAShadowMemoizer::save(const int tolerance)
{
	/*std::ofstream output_file(get_filename_from_tolerance(tolerance));

	const ULAShadow& ula_shadow = memoizer.at(tolerance);

	std::ostream_iterator<bit_vector_t> bit_vector_output_iterator(output_file, "\n");
	std::copy(std::begin(ula_shadow.bit_vectors), std::end(ula_shadow.bit_vectors), bit_vector_output_iterator);

	output_file.close();*/
}

const ULAShadow ULAShadowMemoizer::load(const int tolerance)
{
	return ULAShadow();
}

string ULAShadowMemoizer::get_filename_from_tolerance(const int tolerance)
{
	return "ula_shadow_memo_" + std::to_string(tolerance) + ".bin";
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
		memoizer[tolerance] = ULAShadow(tolerance);
	}

	return memoizer[tolerance];
}
