#include <iostream>
#include <cstring>
#include <cstdlib>
void StandartCalculator();
void BinaryCalculator();
void GradeCalculator();
using namespace std;
int main()
{
	char *line = new char[255];
	while (true)
	{
		system("cls");
        cout << "Choose calculator: " << endl;
		cout << "1 - standart calculator (without priority of +, -, *, /)" << endl;
		cout << "2 - binary calculator" << endl << "3 - grade calculator" << endl << "Other - exit" << endl;
		cout << "Choose: ";
		cin.getline(line, 255);
		if (strcmp(line, "1") == 0) StandartCalculator();
		else if (strcmp(line, "2") == 0) BinaryCalculator();
		else if (strcmp(line, "3") == 0) GradeCalculator();
		else break;
		cout << "Would you like to continue?" << endl << "1 - Yes" << endl << "Other - No" << endl;
		cin.getline(line, 255);
		if (strcmp(line, "1") != 0) break;
    }
    delete line;
	return 0;
}
