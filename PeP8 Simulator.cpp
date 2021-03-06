// PeP8 Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <string>;
using namespace std;

struct FourOneThree {
	unsigned int int3 : 3;
	unsigned int int1 : 1;
	unsigned int int4 : 4;
};
struct FiveThree {
	unsigned int int3 : 3;
	unsigned int int5 : 5;
};
struct SevenOne {
	unsigned int int1 : 1;
	unsigned int int7 : 7;
};
union instruct {
	FourOneThree fouronethree;
	FiveThree fivethree;
	SevenOne sevenone;
	unsigned int eight : 8;
};

struct op {
	unsigned int first : 8;
	unsigned int second : 8;
};
union oper {
	op operate;
	unsigned int full : 16;
};

struct values {
	oper A;
	oper X;
};


//memory
unsigned int memory[65536];

//instruction specifier
instruct instruction;

//instruction operand
oper operand;

//accumulator, index, etc
values val;

void main()
{
	char input; //for the charIn instruction
	int deci; //for decimalIn

	while (1) {
		cout << "Enter an Instruction: ";
		int inst_temp;
		cin >> inst_temp;
		instruction.eight = inst_temp;
		int oper_temp;
		cin >> oper_temp;
		operand.full = oper_temp;

		//bitwise invert
		if (instruction.sevenone.int7 == 12)
		{
			if (instruction.sevenone.int1 == 0)
			{
				val.A.full = val.A.full = ~val.A.full;
			}
			else
			{
				val.X.full = val.X.full = ~val.X.full;
			}
		}
		//arithmetic shift left
		else if (instruction.sevenone.int7 == 14)
		{
			if (instruction.sevenone.int1 == 0)
			{
				val.A.full = val.A.full << 1;
			}
			else
			{
				val.X.full = val.X.full << 1;
			}
		}
		//arithmetic shift right
		else if (instruction.sevenone.int7 == 15)
		{
			if (instruction.sevenone.int1 == 0)
			{
				val.A.full = val.A.full >> 1;
			}
			else
			{
				val.X.full = val.X.full >> 1;
			}
		}
		//rotate left
		else if (instruction.sevenone.int7 == 16)
		{
			if (instruction.sevenone.int1 == 0)
			{
				int leftbit = val.A.full >> 15;
				val.A.full = val.A.full << 1;
				val.A.full = val.A.full + leftbit;
			}
			else
			{
				int leftbit = val.X.full >> 15;
				val.X.full = val.X.full << 1;
				val.X.full = val.X.full + leftbit;
			}
		}
		//rotate right
		else if (instruction.sevenone.int7 == 17)
		{
			if (instruction.sevenone.int1 == 0)
			{
				int rightbit = val.A.full % 2;
				val.A.full = val.A.full >> 1;
				val.A.full = val.A.full + (rightbit << 15);
			}
			else
			{
				int rightbit = val.X.full % 2;
				val.X.full = val.X.full >> 1;
				val.X.full = val.X.full + (rightbit << 15);
			}
		}
		//decimal input trap
		else if (instruction.fivethree.int5 == 6)
		{
			cout << "What is the input? \n";
			cin >> deci;
			memory[operand.full] = input;
		}
		//decimal output trap
		else if (instruction.fivethree.int5 == 7)
		{
			if (instruction.fivethree.int3 == 0)
			{
				cout << operand.full;
			}
			else
			{
				cout << memory[operand.full];
			}
		}
		//character input
		else if (instruction.fivethree.int5 == 9)
		{
			cout << "What is the input? \n";
			cin >> input;
			memory[operand.full] = input;
		}
		//character output
		else if (instruction.fivethree.int5 == 10)
		{
			if (instruction.fivethree.int3 == 0)
			{
				cout << operand.full;
			}
			else
			{
				cout << memory[operand.full];
			}
		}
		//add
		else if (instruction.fouronethree.int4 == 7)
		{
			//immediate addressing
			if (instruction.fouronethree.int3 == 0) {
				if (instruction.fouronethree.int1 == 0)
				{
					val.A.full += operand.full;
				}
				else
				{
					val.X.full += operand.full;
				}
			}
			//direct addressing
			else {
				if (instruction.fouronethree.int1 == 0)
				{
					val.A.full += memory[operand.full];
				}
				else
				{
					val.X.full += memory[operand.full];
				}
			}
		}
		//subtract
		else if (instruction.fouronethree.int4 == 8)
		{
			if (instruction.fouronethree.int3 == 0)
			{
				if (instruction.fouronethree.int1 == 0)
				{
					val.A.full -= operand.full;
				}
				else
				{
					val.X.full -= operand.full;
				}
			}
			else {
				if (instruction.fouronethree.int1 == 0)
				{
					val.A.full -= memory[operand.full];
				}
				else
				{
					val.X.full -= memory[operand.full];
				}
			}
		}
		//bitwise AND
		else if (instruction.fouronethree.int4 == 9)
		{
			if (instruction.fouronethree.int3 == 0)
			{
				if (instruction.fouronethree.int1 == 0)
				{
					val.A.full = val.A.full && operand.full;
				}
				else
				{
					val.X.full = val.X.full && operand.full;
				}
			}
			else {
				if (instruction.fouronethree.int1 == 0)
				{
					val.A.full = val.A.full && memory[operand.full];
				}
				else
				{
					val.X.full = val.A.full && memory[operand.full];
				}
			}
		}
		//bitwise OR
		else if (instruction.fouronethree.int4 == 10)
		{
			if (instruction.fouronethree.int3 == 0)
			{
				if (instruction.fouronethree.int1 == 0)
				{
					val.A.full = val.A.full || operand.full;
				}
				else
				{
					val.X.full = val.X.full || operand.full;
				}
			}
			else {
				if (instruction.fouronethree.int1 == 0)
				{
					val.A.full = val.A.full || memory[operand.full];
				}
				else
				{
					val.X.full = val.A.full || memory[operand.full];
				}
			}
		}
		//load r from memory
		else if (instruction.fouronethree.int4 == 12)
		{
			if (instruction.fouronethree.int3 == 0)
			{
				if (instruction.fouronethree.int1 == 0)
				{
					val.A.full = operand.full;
				}
				else
				{
					val.X.full = operand.full;
				}
			}
			else
			{
				if (instruction.fouronethree.int1 == 0)
				{
					val.A.full = memory[operand.full];
				}
				else
				{
					val.X.full = memory[operand.full];
				}
			}
		}
		//load byte from memory
		else if (instruction.fouronethree.int4 == 13)
		{
			if (instruction.fouronethree.int3 == 0)
			{
				if (instruction.fouronethree.int1 == 0)
				{
					val.A.operate.first = operand.full;
				}
				else
				{
					val.X.operate.first = operand.full;
				}
			}
			else
			{
				if (instruction.fouronethree.int1 == 0)
				{
					val.A.operate.first = memory[operand.full];
				}
				else
				{
					val.X.operate.first = memory[operand.full];
				}
			}
		}
		//store r to memory
		else if (instruction.fouronethree.int4 == 14)
		{
			if (instruction.fouronethree.int1 == 0)
			{
				memory[operand.full] = val.A.full;
			}
			else
			{
				memory[operand.full] = val.X.full;
			}
		}
		//store byte to memory
		else if (instruction.fouronethree.int4 == 15)
		{
			if (instruction.fouronethree.int1 == 0)
			{
				memory[operand.full] = val.A.operate.first;
			}
			else
			{
				memory[operand.full] = val.X.operate.first;
			}
		}
		//stop execution
		else if (instruction.eight == 0)
		{
			break;
		}
		else
		{
			cout << "Did not recognize instruction. \n";
		}

		//print our registers and memory
		cout << endl;
		cout << "A: " << val.A.full << endl;
		cout << "X: " << val.X.full << endl;
		cout << "Mem: " << endl;
		for (int z = 0; z < 32; z++) {
			cout << z << "[" << memory[z] << "]\t";
			if (z % 8 == 7 && z != 0) { cout << endl; }
		}
		cout << endl;
	}
}

