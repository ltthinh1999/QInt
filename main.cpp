#include "QInt.h"

int main()
{
	QInt p, q;
	cout << "Enter p: ";
	ScanQInt(p);
	cout << "Enter q: ";
	ScanQInt(q);

	QInt k = p / q;
	cout << "p / q = ";
	PrintQInt(k);

	cout << endl;
	
	system("pause");
	return 0;
}