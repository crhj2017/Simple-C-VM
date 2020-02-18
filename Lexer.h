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

// Class for a token
class Token {
public:
	strings Type = { "Operator","Number","Identifier","Equal","Keyword","End","Unexpected" };

	// Token attributes
	string tokType;
	string tokVal;

	// Constructor function
	Token(string value) {
		tokVal = value;
		if (value == "+" || value == "-" || value == "*" || value == "/") {
			tokType = Type[0];
		}
		else if (isdigit(value[0])) {
			tokType = Type[1];
		}
		else if (isalpha(value[0])) {
			if (value == "print") {
				tokType = Type[4];
			}
			else {
				tokType = Type[2];
			}
		}
		else if (value == "=") {
			tokType = Type[3];
		}
		else if (value == ";") {
			tokType = Type[5];
		}
		else {
			tokType = Type[6];
		}
	}
};

// Definition of token vector for parser to read
typedef vector<Token> tokvector;

class Lexer { //Class for Lexer
	bool my_isspace(char c);
	bool isspecial(char c);
	bool isgroup(char c);
	bool isPrimitive(char c);
	char end_char, beg_char;

public:
	tokvector lex(string s);
};
#endif
