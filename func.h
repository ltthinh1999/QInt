#ifndef _FUNC_H
#define _FUNC_H


#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

string VeryLargeDivision(string number, int divisor);

string VeryLargeDivision(string number, int divisor)
{
	// Kết quả có thể sẽ rất lớn nên chứa trong string.
	string ans;

	int idx = 0;
	int temp = number[idx] - '0';

	// Liên tục thêm vào temp 1 con số cho tới
	// khi temp lớn hơn divisor.
	while (temp < divisor)
	{
		if (number.length() == 1)
			break;
		temp = temp * 10 + (number[++idx] - '0');
	}

	// Liên tục chia temp cho divisor,
	// sau mỗi lần chia ta update temp thêm 1 đơn vị.
	while (number.size() > idx)
	{
		// Chứa kết quả ở trong ans.
		ans += (temp / divisor) + '0';

		// Tăng temp thêm 1 đơn vị. 
		temp = (temp % divisor) * 10 + number[++idx] - '0';
	}

	// Nếu số bị chia nhỏ hơn số chia
	// thì trả về 0
	if (ans.length() == 0)
		return "0";

	// Còn lại trả về ans
	return ans;
}

#endif // _FUNC_H