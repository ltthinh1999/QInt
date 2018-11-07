#pragma once

#include "func.h"

class QInt
{
private:
	int64_t head; // Phần bit chứa dấu âm hoặc dương (0 hoặc 1).
	uint64_t body; // Phần đuôi của bit.

	bool isZero();
	bool isNegative();
	vector<bool> GetBits(); // Lấy dãy bit của QInt.
	void SaveBits(vector<bool> bits); // Lưu dãy bit vào QInt.
	void TwosComplement(); // Bù 2.
public:
	QInt(); // Giá trị default của biến QInt (bằng 0).
	QInt(uint64_t a);
	QInt(string a);
	~QInt();
	friend void ScanQInt(QInt &x); // Nhập giá trị, lưu vào biến QInt.
	string QIntToString(); // Chuyển các bit trong QInt thành 1 số rất lớn được lưu dưới dạng string.
	friend void PrintQInt(QInt x); // Xuất biến QInt ra màn hình.
	friend vector<bool> DecToBin(QInt a);
	friend QInt BinToDec(vector<bool> bits);
	friend string BinToHex(vector<bool> bits);
	friend string DecToHex(QInt a);
	friend QInt operator+(QInt a, QInt b);
	friend QInt operator-(QInt a, QInt b);
	friend QInt operator*(QInt a, QInt b);
	friend QInt operator/(QInt a, QInt b);
	friend QInt operator&(QInt a, QInt b);
	friend QInt operator|(QInt a, QInt b);
	friend QInt operator^(QInt a, QInt b);
	friend QInt operator~(QInt a);
	friend QInt operator<<(QInt a, uint64_t s);
	friend QInt operator>>(QInt a, uint64_t s);
	QInt& rol(int t);
	QInt& ror(int t);
	string Add2Strings(string& a, string& b); // Cộng 2 số rất lớn được biểu diễn bằng string.
	string Sub2Strings(string& a, string& b); // Trừ 2 số rất lớn được biểu diễn bằng string.
};

bool QInt::isZero()
{
	vector<bool> bit = this->GetBits();

	for (int i = 0; i < 128; i++)
		if (bit[i] == 1)
			return false;

	return true;
}

bool QInt::isNegative()
{
	vector<bool> bit = this->GetBits();

	if (bit[0])
		return true;
	return false;
}

vector<bool> QInt::GetBits()
{
	vector<bool> bits(128);

	int64_t tmp = body;

	for (int i = 127; i >= 64; i--)
	{
		bits[i] = tmp & 1;
		tmp >>= 1;
	}

	tmp = head;

	for(int i = 63; i >= 0; i--)
	{
		bits[i] = tmp & 1;
		tmp >>= 1;
	}

	return bits;
}

void QInt::TwosComplement()
{
	bool rem = 1;

	vector<bool> bits = GetBits();

	for (int i = 0; i < 128; i++) // Bù 1 (lấy phủ định của bit thứ i).
	{
		bits[i] = !bits[i];
	}

	for (int i = 127; i >= 0; i--) // Bù 2 (Cộng 1).
	{
		if (bits[i] == 1 && rem == 1)
		{
			bits[i] = 0;
			rem = 1;
		}
		else
		{
			bits[i] = bits[i] | rem;
			rem = 0;
		}
	}

	SaveBits(bits); // Sau khi bù, lưu bits mới vào biến QInt.
}

void QInt::SaveBits(vector<bool> bits) // Lưu bits vào biến QInt.
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

QInt::QInt(uint64_t a)
{
	head = 0;
	body = a;
}

QInt::QInt(string largeNumber)
{
	head = body = 0;

	bool Negative = false; // false: số dương | true: số âm.

	if (largeNumber[0] == '-') // Nếu như tring bắt đầu bằng dấu - => là số âm
	{
		Negative = true;       // nên Negative ở đây sẽ là true.
		largeNumber = largeNumber.erase(0, 1); // Tạm quên dấu âm (để tách số đối của nó thành bits sau đó bù 2).
	}                                          // ví dụ như nhập vào -9 thì bỏ dấu âm đi để tách số 9 thành bit rồi
											   // bù 2 sẽ có được dãy bit của -9.	

	vector<bool> bits(128); // Tạo mảng bool gồm 128 phần tử để chứa bits (bool là 0 hoặc 1 | true hoặc false).

	for (int i = 0; i < 128; i++)
	{
		bits[i] = (largeNumber[largeNumber.size() - 1] - '0') % 2; // Lấy phần dư (1 hoặc 0) gán vào bit thứ i
		largeNumber = VeryLargeDivision(largeNumber, 2);           // sau đó số mình nhập vào sẽ được chia đôi.
	}

	reverse(bits.begin(), bits.end()); // Đảo chiều dãy bits, vì sau khi ta chia xong thì phải lấy bits từ cuối lên.

	if (Negative) // Nếu là số âm
	{
		SaveBits(bits);       // Lưu dãy bit vào QInt.
		TwosComplement();     // sau đó bù 2. 
	}
	else
		SaveBits(bits); // Nếu không thì lưu nhưng không bù.
}

QInt::~QInt()
{}

void ScanQInt(QInt &x) 
{
	string largeNumber; // Nhập giá trị QInt dưới dạng string.
	getline(cin, largeNumber);

	x.head = x.body = 0;

	bool Negative = false; // false: số dương | true: số âm.

	if (largeNumber[0] == '-') // Nếu như tring bắt đầu bằng dấu - => là số âm
	{
		Negative = true;       // nên Negative ở đây sẽ là true.
		largeNumber = largeNumber.erase(0, 1); // Tạm quên dấu âm (để tách số đối của nó thành bits sau đó bù 2).
	}                                          // ví dụ như nhập vào -9 thì bỏ dấu âm đi để tách số 9 thành bit rồi
										       // bù 2 sẽ có được dãy bit của -9.	
	
	vector<bool> bits(128); // Tạo mảng bool gồm 128 phần tử để chứa bits (bool là 0 hoặc 1 | true hoặc false).

	for(int i = 0; i < 128; i++)
	{
		bits[i] = (largeNumber[largeNumber.size() - 1] - '0') % 2; // Lấy phần dư (1 hoặc 0) gán vào bit thứ i
		largeNumber = VeryLargeDivision(largeNumber, 2);           // sau đó số mình nhập vào sẽ được chia đôi.
	}

	reverse(bits.begin(), bits.end()); // Đảo chiều dãy bits, vì sau khi ta chia xong thì phải lấy bits từ cuối lên.

	if (Negative) // Nếu là số âm
	{
		x.SaveBits(bits);       // Lưu dãy bit vào QInt.
		x.TwosComplement();     // sau đó bù 2. 
	}
	else
		x.SaveBits(bits); // Nếu không thì lưu nhưng không bù.
}

string QInt::QIntToString()
{
	if (head == 0 && body == 0) // Nếu đầu đuôi của QInt đều là 0 thì QInt mang giá trị 0
		return "0";             // => trả về 0.

	long double temp;
	string tmp; // String tạm để chứa giá trị tức thời.
	string str; // String kết quả.
	int dot = 0;

	vector<bool> bits = GetBits(); // Lấy dãy bits của QInt.

	reverse(bits.begin(), bits.end()); // Đảo chiều dãy bits để tiện tính toán. Lúc này bit dấu sẽ là bit cuối (là
	                                   // bits[127]).

	for (int i = 0; i < 127; ++i)
	{
		temp = bits[i] * pow(2, i); // = bits[i] x 2 mũ i.
		if (temp < DBL_EPSILON)
			continue;
		tmp = to_string(temp); // Chuyển bits[i] x 2 mũ i sang dạng string để cộng. (string tmp = bits[i] x 2 mũ i).
		                       
		dot = tmp.find_first_of(".");
		tmp.erase(dot, tmp.size() - dot);

		str = Add2Strings(str, tmp); // Kết quả tại thời điểm i sẽ bằng kết quả tại i - 1 + tmp tại i.
		                             // Phải cộng 2 số dưới dạng string vì có thể 2 số rất lớn không có kiểu dữ
		                             // liệu nào chứa được.
	}

	if (bits[127]) // Nếu như bit dấu là 1 => số âm
	{
		tmp = "-170141183460469231731687303715884105728"; // = -2^127
		str = Add2Strings(str, tmp); // Lấy -2^127 + tmp sẽ được số âm biểu diễn dưới dạng string.
	}

	return str;
}

void PrintQInt(QInt x)
{
	string ans = x.QIntToString();
	cout << ans;
}

string QInt::Sub2Strings(string& a, string& b)
{
	string ans; // Kết quả
	string temp;// string tạm để chứa số trừ.
	bool isNegative = false; // false vì chưa biết kết quả sẽ là âm hay dương.
	int rem = 0; // Biến trả. Ban đầu sẽ bằng 0

	auto pos = a.find_first_not_of('0');
	if (pos != string::npos)
		a.erase(0, pos);
	pos = b.find_first_not_of('0');
	if (pos != string::npos)
		b.erase(0, pos);

	int blank = a.size() - b.size(); // Lấy độ dài số a trừ độ dài số b ta được khoảng cách giữa a b.

	if (blank < 0) // Nếu a bé hơn b => kết quả là số âm.
	{
		swap(a, b); // Ta swap a b. Để a luôn là số lớn hơn trừ sẽ dễ hơn.
		isNegative = true; // âm nên Negative thành true.
		for (int i = 0; i < abs(blank); i++) // liên tục thêm số 0 vào string số chia (lấp cách trống giữa a b).
			temp.push_back('0');
	}
	else if(blank == 0) // Nếu a có độ dài bằng b.
	{
		for (int i = 0; i < a.size(); i++) // Liên tục xét từng chữ số của a b 
		{
			if (a[i] - '0' < b[i] - '0')   // nếu tại 1 thời điểm chữ số thứ i của a nhỏ hơn b.
			{
				swap(a, b);                // Ta swap a b. Để a luôn là số lớn hơn trừ sẽ dễ hơn.
				isNegative = true;		   // Negative lúc này sẽ là true.
				break;
			}
		}
	}
	else // Còn lại thì a luôn lớn hơn b nên không cần swap.
	{
		for (int i = 0; i < blank; i++)
			temp.push_back('0');		
	}
	temp += b; // Lúc này ta có số chia có cùng độ dài với a và nhỏ hơn a.
	           // VD: a = 1234, b = 12 thì temp sẽ là 0012. Ta sẽ trừ a cho temp thay vì cho b.

	int tmp;

	for (int i = a.size() - 1; i >= 0; i--) // Trừ từ hàng đơn vị lên.
	{
		if ((a[i] - '0') < (temp[i] - '0') + rem) // nếu a tại i nhỏ hơn b tại i.
		{
			tmp = ((a[i] - '0') + 10) - (temp[i] - '0') - rem; // Mượn 1
			ans += tmp + '0'; // Đẩy con số vừa ra được vào string kết quả.
			rem = 1; // Trả 1.
		}

		else // Nếu không thì trừ bình thường rồi trả 0.
		{
			tmp = (a[i] - '0') - (temp[i] - '0') - rem;
			ans += tmp + '0';
			rem = 0;
		}
	}

	// Ví dụ 1234 - 1232. Sau khi trừ sẽ ra 2000 
	
	if (isNegative) // Nếu là số âm.
		ans += '-'; // Thêm dấu trừ vô kết quả

	reverse(ans.begin(), ans.end()); // Lúc trừ kết quả sẽ bị ngược nên đảo lại 
	                                 // lúc này kết quả sẽ thành 0002 (bị thừa 3 số 0 không cần thiết.)

	int k = 1;
	while (ans[k] == '0') // Xóa các số 0 bị thừa.
	{
		ans.erase(k, 1);
	}

	return ans;
}

string QInt::Add2Strings(string& a, string& b)
{
	string ans;
	string temp;
	bool isNegative = false;
	int n;
	int rem = 0;
	
	if (a[0] == '-' && b[0] == '-') // Nếu cả 2 cùng âm
	{
		a.erase(0, 1);              // Tạm quên 2 dấu âm để sau khi tính ta thêm dấu âm sau.
		b.erase(0, 1);
		isNegative = true;          // Lúc này Negative sẽ là true.
	}

	else if (a[0] == '-' && b[0] != '-') // Nếu a âm b dương.
	{
		a[0] = '0';                      
		return Sub2Strings(b, a);        // thì tổng của nó là b-a. Ta gọi hàm trừ đã làm sẵn.
	}

	else if (b[0] == '-' && a[0] != '-') // Ngược lại
	{
		b[0] = '0';
		return Sub2Strings(a, b);        // thì tổng sẽ là a-b.
	}

	int blank = a.size() - b.size();
	blank = abs(blank);

	if (a.size() >= b.size())            // Nếu a lớn hơn b.
	{
		for (int i = 0; i < blank; i++)  // giống trên hàm trừ (liên tục thêm 0 vào trước temp).
			temp.push_back('0');
		temp += b;
		n = a.size();
		for (int i = n - 1; i >= 0; i--) // Sẽ thực hiện a + temp.
		{
			int tmp = (a[i] - '0') + (temp[i] - '0') + rem;
			ans += tmp % 10 + '0';
			rem = tmp / 10;
		}
	}

	else                                 // Ngược lại lấy b + temp. 
	{
		for (int i = 0; i < blank; i++)
			temp.push_back('0');
		temp += a;
		n = b.size();
		for (int i = n - 1; i >= 0; i--)
		{
			int tmp = (b[i] - '0') + (temp[i] - '0') + rem;
			ans += tmp % 10 + '0';
			rem = tmp / 10;
		}
	}

	if (rem == 1)
		ans += rem + '0';
	if (isNegative)
		ans += '-';

	reverse(ans.begin(), ans.end()); // Tương tự như hàm trừ.

	return ans;
}

QInt operator+(QInt a, QInt b)
{
	QInt ans;                        // Biến kết quả.
	vector<bool> bitA = a.GetBits(); // Lấy dãy bit của a.
	vector<bool> bitB = b.GetBits(); // Lấy dãy bit của b.
	vector<bool> Ans(128);           // Dãy bit của kết quả.
	
	bool rem = 0;

	for (int i = 127; i >= 0; i--)
	{
		if (bitA[i] == 0 && bitB[i] == 0)
		{
			Ans[i] = rem;
			rem = 0;
		}
		else if (bitA[i] == 1 && bitB[i] == 1)
		{
			Ans[i] = rem;
			rem = 1;
		}
		else
		{
			if (rem == 1)
			{
				Ans[i] = 0;
				rem = 1;
			}
			else
			{
				Ans[i] = 1;
				rem = 0;
			}
		}
	}
	ans.SaveBits(Ans);

	return ans;
}

QInt operator-(QInt a, QInt b)       // a - b đồng nghĩa với a + bù 2 của b. 
{
	QInt ans;                        // Biến kết quả.
	vector<bool> bitA = a.GetBits(); // Lấy dãy bit của a.
	b.TwosComplement();              // Lấy bù 2 của b.
	vector<bool> bitB = b.GetBits(); // Lấy dãy bit của b.
	vector<bool> Ans(128);           // Dãy bit của kết quả.

	ans = a + b;                     // Sau khi lấy bù 2 cho b ta chỉ cộng cả 2 lại.

	return ans;
}

QInt operator*(QInt a, QInt b)
{
	vector<bool> bitA = a.GetBits();
	vector<bool> bitB = b.GetBits();
	bool isNegative = false;
	QInt ans;
	QInt One(1);

	if ((bitA[0] && !bitB[0]) || (!bitA[0] && bitB[0]))
		isNegative = true;

	if (bitA[0])
		a.TwosComplement();

	if (bitB[0])
	{
		b.TwosComplement();
		bitB = b.GetBits();
	}

	while (!(bitB[0] || b.isZero()))
	{
		if (((b & One) - One).isZero())
			ans = ans + a;
		a = a << 1;
		b = b >> 1;
		bitB = b.GetBits();
	}

	if (isNegative)
		ans.TwosComplement();

	return ans;
}

QInt operator/(QInt a, QInt b)
{
	bool isNegative = false;						// Check kết quả là âm hay dương. 

	if (a.isNegative() && b.isNegative())			// Nếu cùng âm
	{
		isNegative = false;							// Kết quả là dương
		a.TwosComplement();							// bù 2 a.
		b.TwosComplement();							// bù 2 b.
	}

	else if (!a.isNegative() && !b.isNegative())	// Nếu cùng dương
		isNegative = false;                         // Kết quả là dương. 

	else                                            // Còn lại nếu trái dấu
	{												
		isNegative = true;							// Kết quả là âm.

		if (a.isNegative())                         // Nếu a âm thì bù 2 a.
			a.TwosComplement();

		if (b.isNegative())							// Nếu b âm thì bù 2 b.
			b.TwosComplement();
	}

	QInt temp;
	vector<bool> bitA = a.GetBits();
	vector<bool> bitB = b.GetBits();
	vector<bool> bitT = temp.GetBits();
	int k = bitA.size();


	while (k > 0)									// Chia 2 số dương.
	{
		temp = temp << 1;							//|
		bitT = temp.GetBits();						//|
		bitT[127] = bitA[0];						//|
		temp.SaveBits(bitT);						//|==>> Dịch trái [temp,a].
		a = a << 1;									//|
		bitA = a.GetBits();							//|

		temp = temp - b;							
		bitT = temp.GetBits();
		
		if (bitT[0])								// Nếu temp < 0.
		{
			temp = temp + b;						//Trả temp về giá trị cũ.				
		}

		else                                        // Còn không thì
		{
			bitA[127] = 1;							// Bit cuối của a sẽ là 1.
			a.SaveBits(bitA);
		}

		k--;
	}

	if (isNegative)									// Nếu kết quả là âm.
		a.TwosComplement();

	return a;
}

QInt operator&(QInt a, QInt b)
{
	QInt ans;
	vector<bool> bitA = a.GetBits();
	vector<bool> bitB = b.GetBits();
	vector<bool> bitAns(128);

	for (int i = 127; i >= 0; i--)
	{
		bitAns[i] = bitA[i] & bitB[i]; // And 2 bitA và bitB ta sẽ ra bitAns.
	}

	ans.SaveBits(bitAns);
	return ans;
}

QInt operator|(QInt a, QInt b)
{
	QInt ans;
	vector<bool> bitA = a.GetBits(); // Lấy dãy bit của a.
	vector<bool> bitB = b.GetBits(); // Lấy dãy bit của b.
	vector<bool> bitAns(128);

	for (int i = 127; i >= 0; i--)
	{
		bitAns[i] = bitA[i] | bitB[i]; // Or 2 bitA và bitB ta sẽ ra bitAns.
	}

	ans.SaveBits(bitAns);
	return ans;
}


QInt operator^(QInt a, QInt b)
{
	QInt ans;
	vector<bool> bitA = a.GetBits(); // Lấy dãy bit của a.
	vector<bool> bitB = b.GetBits(); // Lấy dãy bit của b.
	vector<bool> bitAns(128);

	for (int i = 127; i >= 0; i--)
	{
		bitAns[i] = bitA[i] ^ bitB[i]; // Xor 2 bitA và bitB ta sẽ ra bitAns.
	}

	ans.SaveBits(bitAns);
	return ans;
}

QInt operator~(QInt a)
{
	QInt ans;
	vector<bool> bitA = a.GetBits(); // Lấy dãy bit của a.
	vector<bool> bitAns(128);

	for (int i = 127; i >= 0; i--)
		bitAns[i] = !bitA[i]; // Not là lấy phủ định lại.

	ans.SaveBits(bitAns);
	return ans;
}

QInt operator<<(QInt a, uint64_t s)
{
	QInt ans;
	vector<bool> bitAns = a.GetBits(); // Lấy dãy bit của a.

	for(int i = 0; i < s; i++)         // Khi vẫn còn số lần dịch
	{
		for (int j = 0; j < 127; j++)
		{
			bitAns[j] = bitAns[j + 1]; // ta gán bit thứ i thành bit thứ i + 1. Làm như vậy 127 lần
		}
		bitAns[127] = 0;               // Cho đến khi gặp bit thứ 127 ta cho bằng 0.
	}

	ans.SaveBits(bitAns);
	return ans;
}

QInt operator>>(QInt a, uint64_t s)
{
	QInt ans;
	vector<bool> bitAns = a.GetBits(); // Lấy dãy bit của a.

	for (int i = 0; i < s; i++)        // Khi vẫn còn số lần dịch
	{
		for (int j = 127; j > 0; j--)  // ta gán bit thứ i thành bit thứ i - 1. Làm như vậy 127 lần
		{
			bitAns[j] = bitAns[j - 1];
		}
		bitAns[0] = 0;                 // Cho đến khi gặp bit đầu tiên ta cho bằng 0.
	}

	ans.SaveBits(bitAns);
	return ans;
}

QInt& QInt::rol(int t)
{
	vector<bool> bitAns = this->GetBits();

	for (int i = 0; i < t; i++)
	{
		bool temp = bitAns[0];
		for (int j = 0; j < 127; j++)
			bitAns[j] = bitAns[j + 1];

		bitAns[127] = temp;
	}

	this->SaveBits(bitAns);

	return *this;
}

QInt& QInt::ror(int t)
{
	vector<bool> bitAns = this->GetBits();

	for (int i = 0; i < t; i++)
	{
		bool temp = bitAns[127];
		for (int j = 127; j > 0; j--)
			bitAns[j] = bitAns[j - 1];

		bitAns[0] = temp;
	}

	this->SaveBits(bitAns);

	return *this;
}

QInt BinToDec(vector<bool> bits)
{
	QInt ans;
	ans.SaveBits(bits);
	
	return ans;
}

vector<bool> DecToBin(QInt a)
{
	vector<bool> ans = a.GetBits();

	return ans;
}

string BinToHex(vector<bool> bits)
{
	string ans;
	
	reverse(bits.begin(), bits.end());
	for (int i = 0; i < 128; i += 4)
	{
		int temp = 0;

		for (int j = 0; j < 4; j++)
			temp += bits[i + j] * pow(2, j);

		if (temp >= 0 && temp <= 9)
			ans += temp + '0';

		else
			ans += temp + '7';
	}

	reverse(ans.begin(), ans.end());
	
	int k = 0;
	while (ans[k] == '0') // Xóa các số 0 bị thừa.
	{
		ans.erase(k, 1);
	}

	return ans;
}

string DecToHex(QInt a)
{
	vector<bool> tmp = a.GetBits();

	string ans = BinToHex(tmp);

	return ans;
}