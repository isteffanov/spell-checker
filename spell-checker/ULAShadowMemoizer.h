#pragma once
#include<unordered_map>
#include"ULAShadow.h"

typedef std::unordered_map<int, ULAShadow> memoizer_t;

class ULAShadowMemoizer {

private:
	memoizer_t memoizer;
	static ULAShadowMemoizer* singleton_instance;

protected:
	ULAShadowMemoizer();

public:
	ULAShadowMemoizer(ULAShadowMemoizer& other) = delete;
	void operator==(const ULAShadowMemoizer& other) = delete;

	static ULAShadowMemoizer* get_instance();

	const ULAShadow& get_ula_shadow_for_tolerance(int tolerance);
};
