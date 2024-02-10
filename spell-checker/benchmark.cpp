#pragma once
#include"SpellChecker.h"

#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<chrono>

using std::vector;
using std::string;
using std::ifstream;

dictionary_t load_dictionary(const string& filename) {
	ifstream file(filename);

	string word;
	dictionary_t dictionary;
	while (std::getline(file, word)) {
		dictionary.push_back(word);
	}

	return dictionary;
}

void benchmark_with_tolerance(int tolerance) {

	string filename = "en-words.txt";
	string garbled_word = "liquifoer";

	std::chrono::steady_clock::time_point start, end;
	std::chrono::milliseconds duration_milli;
	std::chrono::seconds duration_seconds;

	std::cout << "Loading dictionary started." << std::endl;
	start = std::chrono::high_resolution_clock::now();

	const dictionary_t dictionary = load_dictionary(filename);

	end = std::chrono::high_resolution_clock::now();
	duration_milli = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Dictionary with " << dictionary.size() << " items loaded in: " << duration_milli.count() << " milliseconds" << std::endl;

	// ========================================

	std::cout << "Building spell checker started." << std::endl;
	start = std::chrono::high_resolution_clock::now();

	SpellChecker spell_checker(dictionary, tolerance);

	end = std::chrono::high_resolution_clock::now();
	duration_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);

	std::cout << "Spell checker with tolerance of " << tolerance << " built in: " << duration_seconds.count() << " seconds" << std::endl;

	// =========================================

	std::cout << "Caching shadow for tolerance of " << tolerance << std::endl;
	start = std::chrono::high_resolution_clock::now();

	ULAShadowMemoizer::get_instance()->get_ula_shadow_for_tolerance(tolerance);

	end = std::chrono::high_resolution_clock::now();
	duration_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);

	std::cout << "Cached shadow in: " << duration_seconds.count() << " seconds." << std::endl;

	// =========================================

	std::cout << "Word correction check for " << garbled_word << " started." << std::endl;
	start = std::chrono::high_resolution_clock::now();

	vector<string> corrections = spell_checker.correct_word(garbled_word);

	end = std::chrono::high_resolution_clock::now();
	duration_milli = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << "Spell checker found " << corrections.size() << " corrections in: " << duration_milli.count() << " milliseconds" << std::endl;
}


void separate() {
	std::cout << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << std::endl;
}

int main() {

	benchmark_with_tolerance(2);
	separate();
	benchmark_with_tolerance(3);
	separate();
	benchmark_with_tolerance(4);
	separate();
	benchmark_with_tolerance(5);
	separate();
	benchmark_with_tolerance(6);

	return 0;
}