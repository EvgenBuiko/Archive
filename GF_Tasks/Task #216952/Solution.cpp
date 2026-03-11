#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	int i = -8;
	//start counting on x - axis
	while (i < 9)
	// end of counting on x - axis is number 8
	{
 	    // check i for coorect output
		if (i < 0)
		{
		   cout << i << '|';
		   for (int j = 0; j < i * i + 1; j++) cout << ' ';
		   cout << '*' << i * i << endl;
		   // write i and symbol '|', upper start of y - axis
		}
  		else if (i > 0)
		{
		   cout << ' ' << i << '|';
		   for (int j = 0; j < i * i + 1; j++) cout << ' ';
		   cout << '*' << i * i << endl;
		   // write space(because i > 0), i and symbol '|', bellow start of y - axis
		}
  		else if (i == 0)
		   cout << ' ' << i << "|*0" << "----------------------------------------------------------------------------y - axis" << endl;
		   // start of y- axis
	   	i++; 
 		// add 1 after every step of loop 
	}
	return 0;
}
