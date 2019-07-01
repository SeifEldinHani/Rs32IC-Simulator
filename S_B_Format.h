#pragma once
class S_B_Format
{
private:
	unsigned int rd, rs1, rs2, funct3, funct7, S_Imm , B_Imm, address;
	unsigned char Byte(int);
	bool BEQ(int, int); 
	bool BNE(int, int);
	bool BLT(int, int);
	bool BGE(int, int);
	bool BLTU(unsigned int,unsigned int);
	bool BGEU(unsigned int,unsigned int);


public:
S_B_Format();
void S_Decode(int ,int[] , char[]);
void B_Decode(int, int[], int &); 
};

