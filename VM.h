#ifndef STACK_VM_H
#define STACK_VM_H

#include <iostream>
#include <vector>
using namespace std;

//Type Definitions
typedef int32_t i32;

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

#endif
