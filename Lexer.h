#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <stack>
#include <sstream>
#include <algorithm>
using namespace std;

// Define types for later
typedef uint8_t byte; 
typedef int32_t i32;

typedef vector<string> strings;
enum State : byte { START, READCHAR, READBLOCK, SKIP, DUMP, COMMENT, END };
enum typeState { TSTART, READTOK, EXPR, TERM, FACTOR };

// Class for main VM Stack
class StackVM {
	i32 pc = 100;	//Program Counter
	i32 sp = 0;		//Stack Pointer
	vector<i32> memory; //Assign Memory
	i32 typ = 0;	//Type Register
	i32 dat = 0;	//Data Register
	i32 running = 1;//Running Flag

	//Private Functions
	i32 getType(i32 instruction);
	i32 getData(i32 instruction);
	void fetch();
	void decode();
	void execute();
	void doPrimitive();

public:
	//Public Functions
	StackVM();
	void run();
	void loadProgram(vector<i32> prog);
};

// Class for a token
class Token {
public:
	// Token attributes
	string tokType;
	string tokVal;
	strings Type = { "Operator","Number","Identifier","Equal","Keyword","End","lParen","rParen","Unexpected" };

	// Constructor functions
	Token();
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
		else if (value == "(") {
			tokType = Type[6];
		}
		else if (value == ")") {
			tokType = Type[7];
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

class BinaryTree {
private:
	string key;
	BinaryTree* leftChild;
	BinaryTree* rightChild;

public:
	BinaryTree(string rootObj) {
		this->key = rootObj;
		this->leftChild = NULL;
		this->rightChild = NULL;
	}

	void insertLeft(string newNode);
	void insertRight(string newNode);
	BinaryTree* getRightChild();
	BinaryTree* getLeftChild();
	void setRootVal(string obj);
	string getRootVal();
};

// Definition of parse function taking stream of tokens
BinaryTree* buildParseTree(tokvector tokens);
void postorderPrint(BinaryTree* pt, string arr[]);
#endif
