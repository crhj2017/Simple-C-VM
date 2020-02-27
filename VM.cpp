#include "Sasm.h"

/*
Instruction format
	Header: 2 bits
	Data: 30 bits
Header format:
	0 - positive integer
	1 - primitive instruction
	2 - negative integer
	3 - undefined

Allows for negative instruction bits
*/

//Functions
StackVM::StackVM() {	//Reserves memory for VM
	memory.resize(1000000);
}

i32 StackVM::getType(i32 instruction) {	//Returns instruction type (See Above)
	i32 type = 0xc0000000;
	type = (type & instruction) >> 30;
	return type;
}

i32 StackVM::getData(i32 instruction) {	//Returns instruction data (See Above)
	i32 data = 0x3fffffff;
	data = data & instruction;
	return data;
}

void StackVM::fetch() {
	pc++;
}

void StackVM::decode() {
	typ = getType(memory[pc]);
	dat = getData(memory[pc]);
}

void StackVM::execute() {
	if (typ == 0 || typ == 2) {
		sp++;
		memory[sp] = dat;
	}
	else {
		doPrimitive();
	}
}

void StackVM::doPrimitive() {
	switch (dat) {	//Instruction set
	case 0:			//Halt
		cout << "Halt" << endl;
		running = 0;
		break;
	case 1:			//Add
		cout << "Add " << memory[sp - 1] << " & " << memory[sp] << endl;
		memory[sp - 1] = memory[sp - 1] + memory[sp]; //Two items popped off stack so more efficient to set pointer second
		sp--;
		break;
	case 2:			//Subtraction
		cout << "Subtract " << memory[sp - 1] << " & " << memory[sp] << endl;
		memory[sp - 1] = memory[sp - 1] - memory[sp]; //Two items popped off stack so more efficient to set pointer second
		sp--;
		break;
	case 3:			//Multiplication
		cout << "Multiply " << memory[sp - 1] << " & " << memory[sp] << endl;
		memory[sp - 1] = memory[sp - 1] * memory[sp]; //Two items popped off stack so more efficient to set pointer second
		sp--;
		break;
	case 4:			//Division
		cout << "Divide " << memory[sp - 1] << " & " << memory[sp] << endl;
		memory[sp - 1] = memory[sp - 1] / memory[sp]; //Two items popped off stack so more efficient to set pointer second
		sp--;
		break;
	}
}

void StackVM::run() {	//Main Function
	pc -= 1;
	while (running == 1) {
		fetch();
		decode();
		execute();
		cout << "Top Of Stack: " << memory[sp] << endl;
	}
}

void StackVM::loadProgram(vector<i32> prog) {
	for (i32 i = 0; i < prog.size(); i++) {
		memory[pc + i] = prog[i];
	}
}
