#pragma once
class R_I_Format
{

private: 
	unsigned int rd, rs1, rs2, funct3, funct7, I_Imm; 
	int add(int  , int );   //Worka with both I and R Formats but with different passed parameters 
	int sub(int, int); 
	int SLL(int, unsigned int);
	int SLT(int, int);
	int SLTU(unsigned int,unsigned int);
	int Xor(int, int); 
	int SRL(int, unsigned int);
	int SRA(int, unsigned int);
	int Or(int, int);
	int And(int, int); 
	
public:
	R_I_Format();
	void R_decode(int , int , int []);
	void I_decode(int , int , int []);
};
