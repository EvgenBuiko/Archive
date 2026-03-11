#include <iostream>
#include <iomanip>
using namespace std;
int diamond(char &i, char &k) {
	cout << endl << setw(16)<< setfill(' ') << i << endl;
	cout << setw(15) << setfill(' ') << i << k << i << endl;
	cout << setw(14) << setfill(' ') << i << setw(4) << setfill(k) << i << endl;
	cout << setw(13) << setfill(' ') << i << setw(6) << setfill(k) << i << endl;
	cout << setw(14) << setfill(' ') << i << setw(4) << setfill(k) << i << endl;
	cout << setw(15) << setfill(' ') << i << k << i << endl;
	cout << setw(16) << setfill(' ') << i << endl;
	cout << endl;
	return i, k;
}
int info(char &i, char &k) {
	cout << "Enter two symbols, first will be on the top of the diamond," << endl;
	cout << "The second will be in diamond" << endl;
	cin >> i >> k;
	return i, k;
}
int main() {
	char i, k;
	info(i, k);
	diamond(i, k);
	system("pause");
	return 0;
}

