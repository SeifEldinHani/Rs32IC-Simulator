#include "R_I_Format.h"
#include <iostream>
R_I_Format::R_I_Format()
{
	rd = 0; 
	rs1 = 0; 
	rs2 = 0;  
	funct3 = 0; 
	funct7 = 0; 
	I_Imm=0;
}
void R_I_Format::R_decode(int instWord, int opcode, int reg[])
{
	rd = (instWord >> 7) & 0x1F;   
	funct3 = (instWord >> 12) & 0x07;  
	rs1 = (instWord >> 15) & 0x1F;  
	rs2 = (instWord >> 20) & 0x1F;  
	funct7 = (instWord >> 25) & 0x7F;    
	if (funct3 == 0)
	{
		if (funct7 == 0)
		{
			reg[rd] = add(reg[rs1], reg[rs2]);
			std::cout << "\tADD\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
		}
		else if (funct7 == 32)
		{
			reg[rd] = sub(reg[rs1], reg[rs2]);
			std::cout << "\tSUB\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
		}
	}
	else if (funct3 == 1)
	{
		reg[rd] = SLL(reg[rs1], reg[rs2]);
		std::cout << "\tSLL\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
	}
	else if (funct3 == 2)
	{
		reg[rd] = SLT(reg[rs1], reg[rs2]);
		std::cout << "\tSLT\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
	}
	else if (funct3 == 3)
	{
		reg[rd] = SLTU(reg[rs1], reg[rs2]);
		std::cout << "\tSLTU\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
	}
	else if (funct3 == 4)
	{
		reg[rd] = Xor(reg[rs1], reg[rs2]);
		std::cout << "\tXOR\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
	}
	else if (funct3 == 5)
	{
		if (funct7 == 0)
		{
			reg[rd] = SRL(reg[rs1], reg[rs2]);
			std::cout << "\tSRL\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
		}
		else if (funct7 == 32)
		{
			reg[rd] = SRA(reg[rs1], reg[rs2]);
			std::cout << "\tSRA\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
		}
	}
	else if (funct3 == 6)
	{
		reg[rd] = Or(reg[rs1], reg[rs2]);
		std::cout << "\tOR\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
	}
	else if (funct3 == 7)
	{
		reg[rd] = And(reg[rs1], reg[rs2]);
		std::cout << "\tAND\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
	}
}
void R_I_Format::I_decode(int instWord, int opcode, int reg[])
{
	

}
int R_I_Format::add(int y, int z)
{
	return (y + z);
}
int R_I_Format::sub(int y, int z)
{
	return (y - z);
}
int R_I_Format::SLL(int y, unsigned int z)
{
	return (y << z);
}
int R_I_Format::SLT(int y, int z)
{
	if (y < z)
		return 1;
	else
		return 0; 
}
int R_I_Format::SLTU(unsigned int y, unsigned int z)
{
	if (y < z)
		return 1;
	else
		return 0;
}
int R_I_Format::Xor(int y, int z)
{
	return (y ^ z); 
}
int R_I_Format::SRL(int y, unsigned int z)
{
	return (y >> z);
}
int R_I_Format::SRA(int y, unsigned int z)
{
	return (y >> z);//Arithmatic Shift is automatically done when the shifted number is negative
}
int R_I_Format::Or(int y, int z)
{
	return (y | z);
}
int R_I_Format::And(int y, int z)
{
	return (y & z);
}