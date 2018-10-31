#include "QInt.h"

int main()
{
	QInt p, k;
	p.ScanQInt(p);
	p.PrintQInt(p);
	cout << endl;
	vector<bool> ans = DecToBin(p);
	for (int i = 0; i < 128; i++)
		cout << ans[i];
	cout << endl;

	system("pause");
	return 0;
}