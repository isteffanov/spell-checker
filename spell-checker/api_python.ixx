%module spell_checker

%{
#define SWIG_FILE_WITH_INIT
#include "SpellChecker.h"
#include<string>
#include<vector>
%}

%include <std_vector.i>;
%include <std_string.i>;

using std::vector;
using std::string;

%template(dictionary_t) std::vector<std::string>;

%include SpellChecker.h
%include main.cpp
