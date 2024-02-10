#pragma once
#include<unordered_map>
#include"ULAShadow.h"

typedef std::unordered_map<int, std::unique_ptr<ULAShadow>> memoizer_t;

class ULAShadowMemoizer {

private:
	memoizer_t memoizer;
	static ULAShadowMemoizer* singleton_instance;


protected:
	ULAShadowMemoizer();

public:
	ULAShadowMemoizer(ULAShadowMemoizer& other) = delete;
	void operator==(const ULAShadowMemoizer& other) = delete;

	void save(const string& file_path, const int tolerance);
	void load(std::ifstream& file, const int tolerance);

	static string get_filename_from_tolerance(const int tolerance);


	static ULAShadowMemoizer* get_instance();

	const ULAShadow& get_ula_shadow_for_tolerance(int tolerance);
};
