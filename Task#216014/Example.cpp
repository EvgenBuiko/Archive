#include<iostream>
#include"MixedFraction.h"
using namespace std;
int main()
{
	MixedFraction mf0 = MixedFraction(5, 555, 5),
				  mf1 = MixedFraction(0, 4, 0),
 				  mf2 = MixedFraction(43, 264, 27),
 				  mf3 = MixedFraction(35, 3, 4),
    			  mf4 = mf2 + mf3,
				  mf5 = mf2 * mf3;
    cout << "mf0 = " << mf0 << endl;
    cout << "mf1 = " << mf1 << endl;
	cout << "mf2 + mf3 = " << mf3 << endl;
	cout << "mf2 * mf3 = " << mf4 << endl;
	return 0;
}
