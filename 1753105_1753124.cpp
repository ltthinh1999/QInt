#include "IOFile.h"

int main(int argc, char *argv[])
{
	string input = argv[1];
	string output = argv[2];

	int line = CountLinesOfFile(input);
	ofstream fout(output);

	for (int i = 1; i <= line; i++)
	{
		switch (GetMethodFromLine(input, i))
		{
		case 1:
			fout << Addition(input, i) << endl;
			break;
		case 2:
			fout << Subtraction(input, i) << endl;
			break;
		case 3:
			fout << Multiplication(input, i) << endl;
			break;
		case 4:
			fout << Division(input, i) << endl;
			break;
		case 5:
			fout << ShiftLeft(input, i) << endl;
			break;
		case 6:
			fout << ShiftRight(input, i) << endl;
			break;
		case 7:
			fout << RoL(input, i) << endl;
			break;
		case 8:
			fout << RoR(input, i) << endl;
			break;
		case 9:
			fout << And(input, i) << endl;
			break;
		case 10:
			fout << Or(input, i) << endl;
			break;
		case 11:
			fout << Xor(input, i) << endl;
			break;
		case 12:
			fout << Not(input, i) << endl;
			break;
		case 13:
			fout << FBinToDec(input, i) << endl;
			break;
		case 14:
			fout << FBinToHex(input, i) << endl;
			break;
		case 15:
			fout << FDecToBin(input, i) << endl;
			break;
		case 16:
			fout << FDecToHex(input, i) << endl;
			break;
		default:
			break;
		}
	}
	
	fout.close();


	system("pause");
	return 0;
}