#include <iostream>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;
int main()
{
    srand(time(NULL));
    int Arr[1000], ch = 0;
    for (int i = 0; i < 1000; i++)
        Arr[i] = rand() % 100 + 0;
    ifstream fin("input.txt");
    int x;
    if (!fin.is_open())
        cout << "File not found or don't open!" << endl;
    while (fin.eof() == false)
    {
        fin >> x;
        for (int k = 0; k < 1000; k++)
        {
            if (Arr[k] == x)
                ch++;
        }
        cout << "$> query: " << x << "\tcount: " << ch << " \tpid: " << GetCurrentProcessId() << endl;
        ch = 0;
    }
    fin.close();
    return 0;
}
