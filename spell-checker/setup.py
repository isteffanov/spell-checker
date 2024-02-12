#!/usr/bin/env python

"""
setup.py file for SWIG port from C++ SpellChecker class to Python
"""

from distutils.core import setup, Extension


spell_checker_module = Extension('_spell_checker',
                           sources=[
                               'api_python_wrap.cxx',
                               'Position.cpp',
                               'ParametricState.cpp',
                               'ULAShadow.cpp',
                               'ULAShadowMemoizer.cpp',
                               'ULAState.cpp',
                               'UniversalLevenshteinAutomaton.cpp',
                               'TrieAutomaton.cpp',
                               'SpellChecker.cpp'],
                           )

setup (name = 'spell-checker',
       version = '0.1',
       author      = "Ivan Stefanov",
       description = """Spell Checker based on Universal Levenshtein Automata""",
       ext_modules = [spell_checker_module],
       py_modules = ["spell-checker"],
       )
