#include <iostream>
#include <fstream>
#include "vm.h"

using namespace std;

int main() {
	ifstream r("out.bin", ios::binary);
	i32 i;
	vector<i32> prog;

	while (r.read((char*)&i, sizeof(i))) {
		prog.push_back(i);
	}

	StackVM vm;
	vm.loadProgram(prog);
	vm.run();
	return 0;
}
