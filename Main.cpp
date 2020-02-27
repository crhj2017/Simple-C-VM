#include "Lexer.h"

typedef uint32_t ui32;
using namespace std;

//Functions
vector<ui32> compileToInstruction(strings s);
bool isInteger(string s);
bool isPrimitive(char c);
ui32 mapToNumber(string s);

int main() {
	// Read Input
	ifstream infile;
	string line; string contents;
	infile.open("input.txt",ios::in);
	
	// Output error if file cannot be opened
	if (!infile.is_open()) {
		cout << "Error: Could not open [Test]" << endl;
		exit(1);
	}
	
	// Get all file data
	while (getline(infile,line)) {
		contents += line + '\n';
	}
	infile.close();

	// Lex file
	Lexer lexer;
	tokvector lexemes = lexer.lex(contents);
	
	// Output tokens
	cout << "Lexed:" << endl;

	for (size_t x = 0; x < lexemes.size(); x ++) {
		cout << lexemes[x].tokType << ": " << lexemes[x].tokVal << "\n";
	}
	
	// Parse the tokens
	BinaryTree* p = buildParseTree(lexemes);
	
	// Get Postorder traversal of AST
	string POS[256]; vector<string> postOrder;
	postorderPrint(p, POS);

	for (const string& text : POS)
		if (text != "") {
			postOrder.push_back(text);
			cout << text;
		}
	
	// Compile to instructions
	vector<ui32> instructions = compileToInstruction(postOrder);

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

// Main compilation function
vector<ui32> compileToInstruction(strings s) {
	vector<ui32> instructions;

	// Loop through token
	for (ui32 i = 0; i < s.size(); i++) {

		// Check token type and respond accordingly
		if (isInteger(s[i])) {
			instructions.push_back(stoi(s[i]));
		}
		else if (isPrimitive(s[i][0])){
			// Check operator type
			ui32 instruction = mapToNumber(s[i]);
			if (instruction != -1) {
				instructions.push_back(instruction);
			}

			// Return error if instruction undefined in compiler
			else {
				cout << "Error: Invalid instruction \"" << s[i] << "\"" << endl;
			}
		}
	}

	// Add halt code and return instruction set
	instructions.push_back(0x40000000);
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

bool isPrimitive(char c) {
	switch (c) {
	case '+':
	case '-':
	case '/':
	case '*':
		return true;
	default:
		return false;
	}
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
