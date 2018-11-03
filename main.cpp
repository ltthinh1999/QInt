#include "QInt.h"

int main()
{
	QInt p, q;
	ScanQInt(p);
	ScanQInt(q);

	QInt k = p / q;
	PrintQInt(k);
	

	cout << endl;
	
	system("pause");
	return 0;
}