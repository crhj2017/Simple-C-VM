#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef uint8_t byte; //Defines a byte
typedef vector<string> strings;

enum State : byte { //Defines byte's possible states
	START,
	READCHAR,
	READBLOCK,
	SKIP,
	DUMP,
	COMMENT,
	END
};

class Lexer { //Class for Lexer
	bool my_isspace(char c);
	bool isspecial(char c);
	bool isgroup(char c);
	bool isPrimitive(char c);
	char end_char, beg_char;

public:
	strings lex(string s);
};
#endif
