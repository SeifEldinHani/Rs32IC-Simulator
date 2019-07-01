#include <string>
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include "R_I_Format.h"
using namespace std;
int regs[32] = {0};
unsigned int pc = 0x0;
char memory[8 * 1024];	// only 8KB of memory located at address 0
R_I_Format RIFields; 
void emitError(string s)
{
	cout << s;
	exit(0);
}

void printPrefix(unsigned int instA, unsigned int instW) {
	cout << "0x" << hex << std::setfill('0') << std::setw(8) << instA << "\t0x" << std::setw(8) << instW;
}
void CheckOpCode(unsigned int instWord)
{
	unsigned int opcode;
	unsigned int address;

	unsigned int instPC = pc - 4;
	opcode = instWord & 0x7F; // opcode is the rightmost 7 bits
	printPrefix(instPC, instWord);
	if (opcode == 51)
	{
		RIFields.R_decode(instWord , opcode , regs);
	}
	
	else {
		cout << "\tUnkown Instruction \n";
	}

}

int main() {
	bool flag = true; 
	unsigned int instWord = 0;
	ifstream inFile;
	ofstream outFile;
	string file = "sum.bin";
	inFile.open(file, ios::in | ios::binary | ios::ate);
	if (inFile.is_open())
	{
		long long fsize = inFile.tellg();  // determines the size of the file
		inFile.seekg(0, inFile.beg);  // to read from the beginning of the file
		if (!inFile.read(memory, fsize))
			emitError("Cannot read from input file\n");
	}

	while (flag)
	{
		instWord = (unsigned char)memory[pc] | (((unsigned char)memory[pc + 1]) << 8) |
			(((unsigned char)memory[pc + 2]) << 16) | (((unsigned char)memory[pc + 3]) << 24);
		pc = pc + 4; 
		CheckOpCode(instWord);
	}
		// dump the registers
		for (int i = 0; i < 32; i++)
			cout << "x" << dec<< i << ": \t" << "0x" << hex << std::setfill('0') << std::setw(8) << regs[i] << "\n";

	
	system("pause"); 
}