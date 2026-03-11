#include <iostream>
#include <cstdlib>
#include <cstring>
#include <math.h>
using namespace std;
unsigned int BinToDec(char *line)
{
	unsigned int value = 0, n = strlen(line);
 	for (int i = 0; i < n; i++)
   		if (line[i] == '1') value += pow(2, n - i - 1);
  	return value;   
}
char* DecToBin(unsigned int value)
{
    int x, j = -1;
    char *result = new char[255];
    for (int i =31; i>=0; i--)
    {
        x = ((value >> i) & 1);
        if (x == 1) result[++j] = '1';
		if ((x == 0) && (j > -1)) result[++j] = '0'; 
    }
    result[++j] = '\0';
    return result;

}
void BinaryCalculator()
{
 	char *line = new char[255], *buf = new char[255]; int in;
	cout << "Convert value to " << endl;
	cout << "1 - binary" << endl << "2 - decimial" << endl << "Other - exit" << endl;
	cout << "Select: ";
	cin.getline(line, 255);
	if ((strcmp(line, "1") == 0) || (strcmp(line, "2") == 0))
	{
	   in = atoi(line);
	   cout << "What is your value to convert? ";
	   cin.getline(line, 255);
	   if (in == 1)
	   {
 	   	   unsigned int value = atoi(line);
	   	   char *pointer = DecToBin(value);
	   	   cout << "Result: " << pointer << endl;
	   	   delete pointer;
	   }
       if (in == 2) cout << "Result: " << BinToDec(line) << endl;
    }
	delete line; delete buf;
}

