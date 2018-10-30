#pragma once

#include "func.h"

class QInt
{
private:
	int64_t head;
	uint64_t body;

	vector<bool> GetBits(); // Lấy dãy bit của QInt.
	void SaveBits(vector<bool> &bits); // Lưu dãy bit vào QInt.
public:
	QInt(); // Giá trị default của biến QInt.
	~QInt();
	void ScanQInt(QInt &x);
	void PrintQInt(QInt x);
	string Add2Strings(string a, string b);
};

vector<bool> QInt::GetBits()
{
	vector<bool> bits(128);

	int64_t tmp = body;

	for (int i = 127; i >= 0; i--)
	{
		bits[i] = tmp & 1;
		tmp >>= 1;
	}
	
	return bits;
}

void QInt::SaveBits(vector<bool> &bits)
{
	for (int i = 0; i < 64; i++)
	{
		head <<= 1;
		head |= bits[i];
	}

	for (int i = 64; i < 128; i++)
	{
		body <<= 1;
		body |= bits[i];
	}
}

QInt::QInt()
{
	head = 0;
	body = 0;
}

QInt::~QInt()
{}

void QInt::ScanQInt(QInt &x)
{
	string largeNumber;
	getline(cin, largeNumber);
	
	vector<bool> bits(128);

	for (int i = 127; i >= 0; i--)
	{
		bits[i] = (largeNumber[largeNumber.length() - 1] - '0') % 2;
		largeNumber = VeryLargeDivision(largeNumber, 2);
	}

	SaveBits(bits);
}

void QInt::PrintQInt(QInt x)
{
	long double temp;
	string tmp;
	string str;
	int dot = 0;
	vector<bool> bits = GetBits();
	reverse(bits.begin(), bits.end());

	if (head == 0 && body == 0)
		cout << 0;

	for (int i = 0; i < 127; i++)
	{
		temp = bits[i] * pow(2, i);
		if (temp < DBL_EPSILON)
			continue;
		tmp = to_string(temp);
		dot = tmp.find_first_of(".");
		tmp.erase(dot, tmp.size() - dot);
		str = Add2Strings(str, tmp);
	}

	if (bits[127])
	{
		tmp = "170141183460469231731687303715884105728";
		str = Add2Strings(str, tmp);
	}

	cout << str;
}

string QInt::Add2Strings(string a, string b)
{
	string ans;
	string temp;
	int n;
	int rem = 0;

	int blank = a.length() - b.length();
	blank = abs(blank);

	if (a.length() >= b.length())
	{
		for (int i = 0; i < blank; i++)
			temp.push_back('0');
		temp += b;
		n = a.length();
		for (int i = n - 1; i >= 0; i--)
		{
			int tmp = (a[i] - '0') + (temp[i] - '0') + rem;
			ans += tmp % 10 + '0';
			rem = tmp / 10;
		}
	}

	else
	{
		for (int i = 0; i < blank; i++)
			temp.push_back('0');
		temp += a;
		n = b.length();
		for (int i = n - 1; i >= 0; i--)
		{
			int tmp = (b[i] - '0') + (temp[i] - '0') + rem;
			ans += tmp % 10 + '0';
			rem = tmp / 10;
		}
	}

	if (rem == 1)
		ans += rem + '0';

	reverse(ans.begin(), ans.end());

	return ans;
}