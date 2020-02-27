#include "Lexer.h"

tokvector Lexer::lex(string s) {
	tokvector strlst;
	char lexeme[256];
	int i = 0, j = 0, balance = 0;
	State state = START;
	int len = s.length();

	while (i < len) {
		
		// Finite state machine
		switch (state) {
				
		case START:
			// Skip Spaces
			if (my_isspace(s[i])) {
				state = SKIP;
			}
				
			// Adds groups to Lexeme
			else if(isgroup(s[i])){
				if (s[i] == '"') {
					lexeme[j] = s[i];
					j++;
					i++;
				}
				state = READBLOCK;
			}
				
			// Skips Comments
			else if (s[i] == '/' && s[i+1] == '/') {
				i += 2;
				state = COMMENT;
			}
				
			// Read character
			else {
				state = READCHAR;
			}
			break;
		case READCHAR:
			// End of lexeme
			if (my_isspace(s[i])) {
				state = DUMP;
			}
			
			else if (isgroup(s[i])) {
				if (s[i] == '"') {
					lexeme[j] = s[i];
						j++;
						i++;
				}
				state = READCHAR;
			}
			else if(isspecial(s[i]) || isPrimitive(s[i])){
				if (j == 0) {
					lexeme[j] = s[i];
					j++;
					i++;
				}
				state = DUMP;
			}
				
			// Handle comments
			else if (s[i] == '/' && s[i + 1] == '/') { 
				i += 2; 
				state = COMMENT; 
			}
			else {
				lexeme[j] = s[i];
				j++;
				i++;
			}
			break;
		case READBLOCK:
			if (s[i] == beg_char && s[i] != '"') {
				balance++;
				lexeme[j] = s[i];
				j++;
				i++;
			}
			else if (s[i] == end_char) {
				balance--;
				lexeme[j] = s[i];
				j++;
				i++;
				if (balance <= 0) {
					state = DUMP;
				}
			}
			else if (end_char == '"' && s[i] == '\\') {
				i += 2;
			}
			else {
				lexeme[j] = s[i];
				j++;
				i++;
			}
			break;
		case SKIP:
			if (my_isspace(s[i])) {
				i++;
			}
			else {
				state = READCHAR;
			}
			break;
		case DUMP:
			if (j > 0) {
				lexeme[j] = 0;
				Token tok(lexeme);
				strlst.push_back(tok);
				j = 0;
			}
			state = START;
			break;
		case COMMENT:
			if (s[i] != '\n') {
				i++;
			}
			else {
				state = READCHAR;
			}
			break;
		case END:
			i = len;
			break;
		}
	}
	if (j > 0) {
		lexeme[j] = 0;
		Token tok(lexeme);
		strlst.push_back(tok);
	}
	return strlst;
}

// Defines a primitive operation to the Lexer
bool Lexer::isPrimitive(char c) {
	switch (c) {
	case '+':
	case '-':
	case '*':
	case '/':
		return true;
	default:
		return false;
	}
}

// Function defining a space
bool Lexer::my_isspace(char c) {
	switch (c) {
	case '\n':
	case '\r':
	case '\t':
	case '\v':
	case ' ':
	case '\f':
		return true;
	default:
		return false;
	}
}

// Function defining pairs eg. quotes
bool Lexer::isgroup(char c) {
	beg_char = c;
	switch (c) {
	case '"':
		end_char = '"';
		return true;
	case '[':
		end_char = ']';
		return true;
	default:
		return false;
	}

}

//Function defining special characters
bool Lexer::isspecial(char c) {
	beg_char = c;
	switch (c) {
	case '(':
	case ')':
	case ';':
		return true;
	default:
		return false;
	}
}
