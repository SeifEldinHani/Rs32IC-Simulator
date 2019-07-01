#include "S_B_Format.h"
#include <iostream>
S_B_Format::S_B_Format()
{
	rd = 0;
	rs1 = 0;
	rs2 = 0;
	funct3 = 0;
	funct7 = 0;
	S_Imm = 0;
	address = 0; 
}
void S_B_Format::S_Decode(int Word, int reg[] , char memory[])
{
	rs1 = (Word >> 15) & 0x1F;
	rs2 = (Word >> 20) & 0x1F;
	funct3 = (Word >> 12) & 0x07;
	S_Imm = ((((Word >> 20) & 0x7E0)) | ((Word >> 7) & 0x1F)) | ((Word>> 31) ? 0xFFFFF800 : 0);
	if (funct3 == 0)
	{
		address = rs1 + S_Imm;
		memory[address] = Byte(reg[rs2]); 
		std::cout << "\tSB\tx" << rs2 <<" , " <<S_Imm<< "(x" << rs1 << ")" << "\n";
	}
	else if (funct3==1)
	{
		address = rs1 + S_Imm;
		memory[address]   = Byte(reg[rs2]);
		memory[address+1] = Byte(reg[rs2]>>8);
		std::cout << "\tSH\tx" << rs2 << " , " << S_Imm << "(x" << rs1 << ")" << "\n";
	}
	else if (funct3 == 2)
	{
		address = rs1 + S_Imm;
		memory[address]		= Byte(reg[rs2]);
		memory[address + 1] = Byte(reg[rs2] >> 8);
		memory[address + 2] = Byte(reg[rs2] >> 16);
		memory[address + 3] = Byte(reg[rs2] >> 24);
		std::cout << "\tSW\tx" << rs2 << " , " << S_Imm << "(x" << rs1 << ")" << "\n";
	}
}
void S_B_Format::B_Decode(int Word ,int reg[] ,  int  & pc )
{
	rs1 = (Word >> 15) & 0x1F;
	rs2 = (Word >> 20) & 0x1F;
	funct3 = (Word >> 12) & 0x07;
	B_Imm = ((Word >> 7) & 0x1E) | ((Word >> 20) & 0x7E0) | (Word << 4 & 0x800) | ((Word >> 31) ? 0xFFFFF000 : 0);
	if (funct3 == 0)
	{
		if (BEQ(reg[rs1], reg[rs2]))
			pc += B_Imm; 
			std::cout << "\tBEQ\tx" << rs1 << ", x" << rs2 <<", 0x"<<std::hex << B_Imm << "\n";
	}
	else if (funct3 == 1)
	{
		if (BNE(reg[rs1], reg[rs2]))
			pc += B_Imm; 
			std::cout << "\tBNE\tx" << rs1 << ", x" << rs2 << ", 0x" << std::hex << B_Imm << "\n";

	}
	else if (funct3 == 4)
	{
		if (BLT(reg[rs1], reg[rs2]))
			pc += B_Imm;
			std::cout << "\tBLT\tx" << rs1 << ", x" << rs2 << ", 0x" << std::hex << B_Imm << "\n";

	}
	else if (funct3 == 5)
	{
		if (BGE(reg[rs1], reg[rs2]))
			pc += B_Imm;
			std::cout << "\tBGE\tx" << rs1 << ", x" << rs2 << ", 0x" << std::hex << B_Imm << "\n";
	}
	else if (funct3 == 6)
	{
		unsigned int a = unsigned(reg[rs1]); 
		unsigned int b = unsigned(reg[rs2]);
		if (BLTU(a,b))
			pc += B_Imm;
		std::cout << "\tBLTU\tx" << rs1 << ", x" << rs2 << ", 0x" << std::hex << B_Imm << "\n";

	}
	else if (funct3 == 7)
	{
		unsigned int a = unsigned(reg[rs1]);
			unsigned int b = unsigned(reg[rs2]);
			if (BGEU(a, b))
				pc += B_Imm;
			std::cout << "\tBGEU\tx" << rs1 << ", x" << rs2 << ", 0x" << std::hex << B_Imm << "\n";

	}
}
unsigned char S_B_Format::Byte(int w)
{
	int x = w & 0xFF; 
	unsigned char z = (unsigned char)x; 
	return z; 
}

bool S_B_Format::BEQ(int x, int y)
{
	return (x == y); 
}
bool S_B_Format::BNE(int x, int y)
{
	return (x != y);
}
bool S_B_Format::BLT(int x, int y)
{
	return (x < y);
}
bool S_B_Format::BGE(int x, int y)
{
	return (x >= y);
}
bool S_B_Format::BLTU(unsigned int x, unsigned int y)
{
	return (x < y);

}
bool S_B_Format::BGEU(unsigned int x, unsigned int y)
{
	return (x >= y);
}