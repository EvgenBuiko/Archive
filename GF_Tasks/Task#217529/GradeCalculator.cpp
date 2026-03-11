#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
void GradeCalculator()
{
	int n, in;
	char *line = new char[255];
	cout << "Enter a count of marks: ";
	cin >> n;
	double avg = 0, *arr = new double[n];
	cout << "Marks: ";
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
		avg += arr[i];
	}
	avg /= n;
	cin.get();
	cout << "Result: " << avg << endl;
	cout << "Do you want to calculate a weighted average?" << endl;
	cout << "1 - Yes" << endl;
	cout << "Other - No" << endl;
	cin.getline(line, 255);
	if (strcmp(line, "1") == 0)
	{
		double avg1 = 0, *arr1 = new double[n];
		cout << "Weights: ";
		for (int i = 0; i < n; i++)
		{
			cin >> arr1[i];
			avg1 += arr1[i];
		}
		avg1 /= n;
		cout << "Result: " << avg * avg1 << endl;
		delete arr1;
		cin.get();
	}
	delete line;
	delete arr;
}
