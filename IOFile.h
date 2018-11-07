#include "QInt.h"

int CountLinesOfFile(string fname)
{
	ifstream File(fname);
	string line;
	int count = 0;

	while (getline(File, line))
		count++;

	return count;
}

int GetMethodFromLine(string fname, int line)
{
	ifstream File(fname);
	string c;

	for (int i = 1; i <= line; i++)
		getline(File, c);

	if (c.find(" + ") != string::npos)
		return 1;

	else if (c.find(" - ") != string::npos)
		return 2;

	else if (c.find(" * ") != string::npos)
		return 3;

	else if (c.find(" / ") != string::npos)
		return 4;

	else if (c.find(" << ") != string::npos)
		return 5;

	else if (c.find(" >> ") != string::npos)
		return 6;

	else if (c.find(" rol ") != string::npos)
		return 7;

	else if (c.find(" ror ") != string::npos)
		return 8;

	else if (c.find(" & ") != string::npos)
		return 9;

	else if (c.find(" | ") != string::npos)
		return 10;

	else if (c.find(" ^ ") != string::npos)
		return 11;

	else if (c.find(" ~ ") != string::npos)
		return 12;

	else if (c[0] == '2' && c[1] == ' ' && c[2] == '1' && c[4] == ' ')
	{
		if (c[3] == '0')
			return 13;
		else if (c[3] == '6')
			return 14;
	}

	else if (c[0] == '1' && c[1] == '0' && c[2] == ' ')
	{
		if (c[3] == '2' && c[4] == ' ')
			return 15;
		else if (c[3] == '1' && c[4] == '6' && c[5] == ' ')
			return 16;
	}
}

string LineNumberI(string fname, int line)
{
	ifstream File(fname);
	string result;

	for (int i = 1; i <= line; i++)
		getline(File, result);

	File.close();

	return result;
}

string Addition(string fname, int line);
string Subtraction(string fname, int line);
string Multiplication(string fname, int line);
string Division(string fname, int line);
string FBinToDec(string fname, int line);
string FDecToBin(string fname, int line);
string FBinToHex(string fname, int line);
string FDecToHex(string fname, int line);
string And(string fname, int line);
string Or(string fname, int line);
string Xor(string fname, int line);
string Not(string fname, int line);
string ShiftLeft(string fname, int line);
string ShiftRight(string fname, int line);
string RoL(string fname, int line);
string RoR(string fname, int line);

string Addition(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string result;

	int pos = data.find("+");

	if (data[0] == '2' && data[1] == ' ')
	{
		vector<bool> bitA(128);
		vector<bool> bitB(128);
		int j = 127;

		for (int i = pos - 2; i >= 2; i--)
		{
			bitA[j] = (data[i] == '1');
			j--;
		}

		j = 127;

		for (int i = data.size() - 1; i >= pos + 2; i--)
		{
			bitB[j] = (data[i] == '1');
			j--;
		}

		QInt a = BinToDec(bitA);
		QInt b = BinToDec(bitB);
		QInt Add = a + b;
		
		vector<bool> bitAdd = DecToBin(Add);
		for (int i = 0; i < 128; i++)
		{
			if (!bitAdd[i])
				result.push_back('0');
			else
				result.push_back('1');
		}

		int i = 0;
		while (result[i] == '0')
		{
			if (result.size() == 32)
				break;
			result.erase(i, 1);
		}
	}

	else if (data[0] == '1' && data[1] == '0' && data[2] == ' ')
	{
		string tempA, tempB;

		for (int i = 3; i <= pos - 2; i++)
		{
			tempA.push_back(data[i]);
		}

		for (int i = pos + 2; i <= data.size() - 1; i++)
		{
			tempB.push_back(data[i]);
		}

		QInt a(tempA);
		QInt b(tempB);
		QInt Add = a + b;

		result = Add.QIntToString();
	}

	return result;
}

string Subtraction(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string result;

	int pos = data.find("-");

	if (data[0] == '2' && data[1] == ' ')
	{
		vector<bool> bitA(128);
		vector<bool> bitB(128);
		int j = 127;

		for (int i = pos - 2; i >= 2; i--)
		{
			bitA[j] = (data[i] == '1');
			j--;
		}

		j = 127;

		for (int i = data.size() - 1; i >= pos + 2; i--)
		{
			bitB[j] = (data[i] == '1');
			j--;
		}

		QInt a = BinToDec(bitA);
		QInt b = BinToDec(bitB);
		QInt Add = a - b;

		vector<bool> bitAdd = DecToBin(Add);
		for (int i = 0; i < 128; i++)
		{
			if (!bitAdd[i])
				result.push_back('0');
			else
				result.push_back('1');
		}

		int i = 0;
		while (result[i] == '0')
		{
			if (result.size() == 32)
				break;
			result.erase(i, 1);
		}
	}

	else if (data[0] == '1' && data[1] == '0' && data[2] == ' ')
	{
		string tempA, tempB;

		for (int i = 3; i <= pos - 2; i++)
		{
			tempA.push_back(data[i]);
		}

		for (int i = pos + 2; i <= data.size() - 1; i++)
		{
			tempB.push_back(data[i]);
		}

		QInt a(tempA);
		QInt b(tempB);
		QInt Add = a - b;

		result = Add.QIntToString();
	}

	return result;
}

string Multiplication(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string result;

	int pos = data.find("*");

	if (data[0] == '2' && data[1] == ' ')
	{
		vector<bool> bitA(128);
		vector<bool> bitB(128);
		int j = 127;

		for (int i = pos - 2; i >= 2; i--)
		{
			bitA[j] = (data[i] == '1');
			j--;
		}

		j = 127;

		for (int i = data.size() - 1; i >= pos + 2; i--)
		{
			bitB[j] = (data[i] == '1');
			j--;
		}

		QInt a = BinToDec(bitA);
		QInt b = BinToDec(bitB);
		QInt Add = a * b;

		vector<bool> bitAdd = DecToBin(Add);
		for (int i = 0; i < 128; i++)
		{
			if (!bitAdd[i])
				result.push_back('0');
			else
				result.push_back('1');
		}

		int i = 0;
		while (result[i] == '0')
		{
			if (result.size() == 32)
				break;
			result.erase(i, 1);
		}
	}

	else if (data[0] == '1' && data[1] == '0' && data[2] == ' ')
	{
		string tempA, tempB;

		for (int i = 3; i <= pos - 2; i++)
		{
			tempA.push_back(data[i]);
		}

		for (int i = pos + 2; i <= data.size() - 1; i++)
		{
			tempB.push_back(data[i]);
		}

		QInt a(tempA);
		QInt b(tempB);
		QInt Add = a * b;

		result = Add.QIntToString();
	}

	return result;
}

string Division(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string result;

	int pos = data.find("/");

	if (data[0] == '2' && data[1] == ' ')
	{
		vector<bool> bitA(128);
		vector<bool> bitB(128);
		int j = 127;

		for (int i = pos - 2; i >= 2; i--)
		{
			bitA[j] = (data[i] == '1');
			j--;
		}

		j = 127;

		for (int i = data.size() - 1; i >= pos + 2; i--)
		{
			bitB[j] = (data[i] == '1');
			j--;
		}

		QInt a = BinToDec(bitA);
		QInt b = BinToDec(bitB);
		QInt Add = a / b;

		vector<bool> bitAdd = DecToBin(Add);
		for (int i = 0; i < 128; i++)
		{
			if (!bitAdd[i])
				result.push_back('0');
			else
				result.push_back('1');
		}

		int i = 0;
		while (result[i] == '0')
		{
			if (result.size() == 32)
				break;
			result.erase(i, 1);
		}
	}

	else if (data[0] == '1' && data[1] == '0' && data[2] == ' ')
	{
		string tempA, tempB;

		for (int i = 3; i <= pos - 2; i++)
		{
			tempA.push_back(data[i]);
		}

		for (int i = pos + 2; i <= data.size() - 1; i++)
		{
			tempB.push_back(data[i]);
		}

		QInt a(tempA);
		QInt b(tempB);
		QInt Add = a / b;

		result = Add.QIntToString();
	}

	return result;
}

string FBinToDec(string fname, int line)
{
	string data = LineNumberI(fname, line);
	vector<bool> bits(128);
	QInt temp;
	string result;
	int j = 127;

	for (int i = data.size() - 1; i >= 5; i--)
	{
		bits[j] = (data[i] == '1');
		j--;
	}

	temp = BinToDec(bits);
	result = temp.QIntToString();

	return result;
}

string FDecToBin(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string temp;
	string result;
	int j = 127;

	for (int i = 5; i <= data.size() - 1; i++)
	{
		temp.push_back(data[i]);
	}

	QInt tmp(temp);
	
	vector<bool> bits = DecToBin(tmp);

	for (int i = 0; i < 128; i++)
	{
		if (!bits[i])
			result.push_back('0');
		else
			result.push_back('1');
	}

	int i = 0;
	while (result[i] == '0')
	{
		if (result.size() == 32)
			break;
		result.erase(i, 1);
	}

	return result;
}

string FBinToHex(string fname, int line)
{
	string data = LineNumberI(fname, line);
	vector<bool> bits(128);
	string result;
	int j = 127;

	for (int i = data.size() - 1; i >= 5; i--)
	{
		bits[j] = (data[i] == '1');
		j--;
	}

	result = BinToHex(bits);

	return result;
}

string FDecToHex(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string tmp;
	string result;

	for (int i = 6; i <= data.size() - 1; i++)
	{
		tmp.push_back(data[i]);
	}

	QInt temp(tmp);

	result = DecToHex(temp);

	return result;
}

string And(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string result;

	int pos = data.find("&");

	if (data[0] == '2' && data[1] == ' ')
	{
		vector<bool> bitA(128);
		vector<bool> bitB(128);
		int j = 127;

		for (int i = pos - 2; i >= 2; i--)
		{
			bitA[j] = (data[i] == '1');
			j--;
		}

		j = 127;

		for (int i = data.size() - 1; i >= pos + 2; i--)
		{
			bitB[j] = (data[i] == '1');
			j--;
		}

		QInt a = BinToDec(bitA);
		QInt b = BinToDec(bitB);
		QInt Add = a & b;

		vector<bool> bitAdd = DecToBin(Add);
		for (int i = 0; i < 128; i++)
		{
			if (!bitAdd[i])
				result.push_back('0');
			else
				result.push_back('1');
		}

		int i = 0;
		while (result[i] == '0')
		{
			if (result.size() == 32)
				break;
			result.erase(i, 1);
		}
	}

	else if (data[0] == '1' && data[1] == '0' && data[2] == ' ')
	{
		string tempA, tempB;

		for (int i = 3; i <= pos - 2; i++)
		{
			tempA.push_back(data[i]);
		}

		for (int i = pos + 2; i <= data.size() - 1; i++)
		{
			tempB.push_back(data[i]);
		}

		QInt a(tempA);
		QInt b(tempB);
		QInt Add = a & b;

		result = Add.QIntToString();
	}

	return result;
}

string Or(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string result;

	int pos = data.find("|");

	if (data[0] == '2' && data[1] == ' ')
	{
		vector<bool> bitA(128);
		vector<bool> bitB(128);
		int j = 127;

		for (int i = pos - 2; i >= 2; i--)
		{
			bitA[j] = (data[i] == '1');
			j--;
		}

		j = 127;

		for (int i = data.size() - 1; i >= pos + 2; i--)
		{
			bitB[j] = (data[i] == '1');
			j--;
		}

		QInt a = BinToDec(bitA);
		QInt b = BinToDec(bitB);
		QInt Add = a | b;

		vector<bool> bitAdd = DecToBin(Add);
		for (int i = 0; i < 128; i++)
		{
			if (!bitAdd[i])
				result.push_back('0');
			else
				result.push_back('1');
		}

		int i = 0;
		while (result[i] == '0')
		{
			if (result.size() == 32)
				break;
			result.erase(i, 1);
		}
	}

	else if (data[0] == '1' && data[1] == '0' && data[2] == ' ')
	{
		string tempA, tempB;

		for (int i = 3; i <= pos - 2; i++)
		{
			tempA.push_back(data[i]);
		}

		for (int i = pos + 2; i <= data.size() - 1; i++)
		{
			tempB.push_back(data[i]);
		}

		QInt a(tempA);
		QInt b(tempB);
		QInt Add = a | b;

		result = Add.QIntToString();
	}

	return result;
}

string Xor(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string result;

	int pos = data.find("^");

	if (data[0] == '2' && data[1] == ' ')
	{
		vector<bool> bitA(128);
		vector<bool> bitB(128);
		int j = 127;

		for (int i = pos - 2; i >= 2; i--)
		{
			bitA[j] = (data[i] == '1');
			j--;
		}

		j = 127;

		for (int i = data.size() - 1; i >= pos + 2; i--)
		{
			bitB[j] = (data[i] == '1');
			j--;
		}

		QInt a = BinToDec(bitA);
		QInt b = BinToDec(bitB);
		QInt Add = a ^ b;

		vector<bool> bitAdd = DecToBin(Add);
		for (int i = 0; i < 128; i++)
		{
			if (!bitAdd[i])
				result.push_back('0');
			else
				result.push_back('1');
		}

		int i = 0;
		while (result[i] == '0')
		{
			if (result.size() == 32)
				break;
			result.erase(i, 1);
		}
	}

	else if (data[0] == '1' && data[1] == '0' && data[2] == ' ')
	{
		string tempA, tempB;

		for (int i = 3; i <= pos - 2; i++)
		{
			tempA.push_back(data[i]);
		}

		for (int i = pos + 2; i <= data.size() - 1; i++)
		{
			tempB.push_back(data[i]);
		}

		QInt a(tempA);
		QInt b(tempB);
		QInt Add = a ^ b;

		result = Add.QIntToString();
	}

	return result;
}

string Not(string fname, int line)
{
	string data = LineNumberI(fname, line);
	int pos = data.find("~");
	string temp;
	string result;

	if (data[0] == '2' && data[1] == ' ')
	{
		vector<bool> ans(128);
		int j = 127;

		for (int i = data.size() - 1; i >= pos + 2; i--)
		{
			ans[j] = (data[i] == '1');
			j--;
		}

		QInt a = BinToDec(ans);
		a = ~a;
		ans = DecToBin(a);

		for (int i = 0; i < 128; i++)
		{
			if (ans[i])
				result.push_back('1');
			else
				result.push_back('0');
		}

		int i = 0;
		while (result[i] == '0')
		{
			if (result.size() == 32)
				break;
			result.erase(i, 1);
		}
	}

	else if (data[0] == '1' && data[1] == '0' && data[2] == ' ')
	{
		for (int i = pos + 2; i <= data.size() - 1; i++)
			temp.push_back(data[i]);

		QInt tmp(temp);
		tmp = ~tmp;
		result = tmp.QIntToString();
	}

	return result;
}

string ShiftLeft(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string result, temp;
	int pos = data.find("<<");

	if (data[0] == '2' && data[1] == ' ')
	{
		vector<bool> ans(128);
		int j = 127;
		int shift;

		for (int i = pos - 2; i >= 2; i--)
		{
			ans[j] = (data[i] == '1');
			j--;
		}
		QInt tmp = BinToDec(ans);

		for (int i = pos + 3; i < data.size(); i++)
			temp.push_back(data[i]);

		shift = stoi(temp);

		tmp = tmp << shift;

		ans = DecToBin(tmp);

		for (int i = 0; i < 128; i++)
		{
			if (ans[i])
				result.push_back('1');
			else
				result.push_back('0');
		}

		int i = 0;
		while (result[i] == '0')
		{
			if (result.size() == 32)
				break;
			result.erase(i, 1);
		}
	}

	else if (data[0] == '1' && data[1] == '0' && data[2] == ' ')
	{
		for (int i = 3; i <= pos - 2; i++)
			temp.push_back(data[i]);

		QInt tmp(temp);
		string temp2;

		for (int i = pos + 3; i < data.size(); i++)
			temp2.push_back(data[i]);

		int shift = stoi(temp2);

		tmp = tmp << shift;
		result = tmp.QIntToString();
	}

	return result;
}

string ShiftRight(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string result, temp;
	int pos = data.find(">>");

	if (data[0] == '2' && data[1] == ' ')
	{
		vector<bool> ans(128);
		int j = 127;
		int shift;

		for (int i = pos - 2; i >= 2; i--)
		{
			ans[j] = (data[i] == '1');
			j--;
		}
		QInt tmp = BinToDec(ans);

		for (int i = pos + 3; i < data.size(); i++)
			temp.push_back(data[i]);

		shift = stoi(temp);

		tmp = tmp >> shift;

		ans = DecToBin(tmp);

		for (int i = 0; i < 128; i++)
		{
			if (ans[i])
				result.push_back('1');
			else
				result.push_back('0');
		}

		int i = 0;
		while (result[i] == '0')
		{
			if (result.size() == 32)
				break;
			result.erase(i, 1);
		}
	}

	else if (data[0] == '1' && data[1] == '0' && data[2] == ' ')
	{
		for (int i = 3; i <= pos - 2; i++)
			temp.push_back(data[i]);

		QInt tmp(temp);
		string temp2;

		for (int i = pos + 3; i < data.size(); i++)
			temp2.push_back(data[i]);

		int shift = stoi(temp2);

		tmp = tmp >> shift;
		result = tmp.QIntToString();
	}

	return result;
}

string RoL(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string result, temp;
	int pos = data.find("rol");

	if (data[0] == '2' && data[1] == ' ')
	{
		vector<bool> ans(128);
		int j = 127;
		int shift;

		for (int i = pos - 2; i >= 2; i--)
		{
			ans[j] = (data[i] == '1');
			j--;
		}
		QInt tmp = BinToDec(ans);

		for (int i = pos + 4; i < data.size(); i++)
			temp.push_back(data[i]);

		shift = stoi(temp);

		tmp = tmp.rol(shift);

		ans = DecToBin(tmp);

		for (int i = 0; i < 128; i++)
		{
			if (ans[i])
				result.push_back('1');
			else
				result.push_back('0');
		}

		int i = 0;
		while (result[i] == '0')
		{
			if (result.size() == 32)
				break;
			result.erase(i, 1);
		}
	}

	else if (data[0] == '1' && data[1] == '0' && data[2] == ' ')
	{
		for (int i = 3; i <= pos - 2; i++)
			temp.push_back(data[i]);

		QInt tmp(temp);
		string temp2;

		for (int i = pos + 4; i < data.size(); i++)
			temp2.push_back(data[i]);

		int shift = stoi(temp2);

		tmp = tmp.rol(shift);
		result = tmp.QIntToString();
	}

	return result;
}

string RoR(string fname, int line)
{
	string data = LineNumberI(fname, line);
	string result, temp;
	int pos = data.find("ror");

	if (data[0] == '2' && data[1] == ' ')
	{
		vector<bool> ans(128);
		int j = 127;
		int shift;

		for (int i = pos - 2; i >= 2; i--)
		{
			ans[j] = (data[i] == '1');
			j--;
		}
		QInt tmp = BinToDec(ans);

		for (int i = pos + 4; i < data.size(); i++)
			temp.push_back(data[i]);

		shift = stoi(temp);

		tmp = tmp.ror(shift);

		ans = DecToBin(tmp);

		for (int i = 0; i < 128; i++)
		{
			if (ans[i])
				result.push_back('1');
			else
				result.push_back('0');
		}

		int i = 0;
		while (result[i] == '0')
		{
			if (result.size() == 32)
				break;
			result.erase(i, 1);
		}
	}

	else if (data[0] == '1' && data[1] == '0' && data[2] == ' ')
	{
		for (int i = 3; i <= pos - 2; i++)
			temp.push_back(data[i]);

		QInt tmp(temp);
		string temp2;

		for (int i = pos + 4; i < data.size(); i++)
			temp2.push_back(data[i]);

		int shift = stoi(temp2);

		tmp = tmp.ror(shift);
		result = tmp.QIntToString();
	}

	return result;
}