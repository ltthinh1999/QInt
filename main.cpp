#include "QInt.h"

int main()
{
	string s = "2147483647";
	QInt p;
	p.ScanQInt(p);
	p.PrintQInt(p);
	cout << endl;

	system("pause");
	return 0;
}