#include "ULAShadowMemoizer.h"

ULAShadowMemoizer* ULAShadowMemoizer::singleton_instance = nullptr;

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
