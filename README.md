# Simple C++ VM

A simple Stack Virtual Machine which Lexes, Parses and Compiles a basic calculator grammar

## File structure:

Lexer.cpp - Reads in a file and lexs the contents into tokens

Parser.cpp - Reads in a vector of tokens and returns a binary tree structure

Sasm.cpp - Main file which compiles a Postorder BT traversal into binary

Stack-VM.cpp - Simulates a stack based CPU to execute the binary instructions

Sasm.h - Main header file containing all class, type and function predefinitions for use throughout the project

## Grammar Examples:

Basic - (3+4)
Nested - ((5+9)*3)

etc. Note the whole expression must have parentheses around it.
