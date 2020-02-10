#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"

typedef uint32_t ui32;

using namespace std;

//Functions
vector<ui32> compileToInstruction(strings s);
bool isInteger(string s);
bool isPrimitive(string s);
ui32 mapToNumber(string s);

int main() {
	//Read Input
	ifstream infile;
	infile.open("input.txt",ios::in);
	if (!infile.is_open()) {
		cout << "Error: Could not open [Test]" << endl;
		exit(1);
	}
	string line;
	string contents;
	while (getline(infile,line)) {
		contents += line + '\n';
	}
	infile.close();

	//Parse file
	Lexer lexer;
	strings lexemes = lexer.lex(contents);

	//Compile to binary
	vector<ui32> instructions = compileToInstruction(lexemes);

	//Write to binary file
	ofstream ofile;
	ofile.open("out.bin", ios::binary);
	if (!ofile.is_open()) {
		cout << "Error: Could not write to [out.bin]" << endl;
		exit(1);
	}
	for (ui32 i = 0; i < instructions.size(); i++) {
		ofile.write(reinterpret_cast<char *>(&instructions[i]), sizeof(ui32));
	}
	ofile.close();
	return 0;
}

vector<ui32> compileToInstruction(strings s) {
	vector<ui32> instructions;
	for (ui32 i = 0; i < s.size(); i++) {
		if (isInteger(s[i])) {
			instructions.push_back(stoi(s[i]));
		}
		else {
			ui32 instruction = mapToNumber(s[i]);
			if (instruction != -1) {
				instructions.push_back(instruction);
			}
			else {
				cout << "Error: Invalid instruction present [" << s[i] << "]" << endl;
			}
		}
	}
	instructions.push_back(0x40000000); //Always halt at the end
	return instructions;
}

bool isInteger(string s) {
	for (ui32 i = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) {
			return false;
		}
		break;
	}
	return true;
}

ui32 mapToNumber(string s) {
	if (s == "+") {
		return 0x40000001;	//Defined in doPrimitive()
	}
	else if (s == "-") {
		return 0x40000002;	//""
	}
	else if (s == "*") {
		return 0x40000003;	//""
	}
	else if (s == "/") {
		return 0x40000004;	//As above
	}
	return -1; //invalid instruction
}
