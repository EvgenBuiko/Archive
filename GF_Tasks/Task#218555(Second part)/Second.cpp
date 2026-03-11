#include <iostream>
using namespace std;
void calculate(int hours, double payrate)
{
	double grosspay, taxes = 0;
	if (hours > 38)
	   grosspay = payrate * 38 + payrate * 1.5 * (hours - 38);
	else grosspay = payrate * hours;
	if (grosspay - 300 >= 0)
	{
	   taxes += 300 / 100 * 15;
	   if (grosspay - 500 >= 0)
	   {
 			taxes += 200 / 100 * 20;
		  	if (grosspay - 650 >= 0)
	   	  	{
			    taxes += 150 / 100 * 25;
		  		if (grosspay > 650)
	   	  	 	   taxes += (grosspay - 650) / 100 * 30;
 	  		} else taxes += (grosspay - 500) / 100 * 25;
	   } else taxes += (grosspay - 300) / 100 * 20;
	} else taxes += grosspay / 100 * 15;
	cout << "Gross pay: " << grosspay << endl 
		 << "Taxes: " << taxes << endl 
		 << "Net pay: " << grosspay - taxes << endl;
}
int main()
{
	int in;
    cout << "****************************************************************" << endl   
		 << "Enter the number corresponding to the desired pay rate:" << endl    
		 << "1 - 8.50 GBP/hour" << endl      
		 << "2 - 9.90 GBP/hour" << endl 
  		 << "3 - 22.40 GBP/hour" << endl   
		 << "4 - 30.00 GBP/hour" << endl   
		 << "****************************************************************" << endl;
    cin >> in;
    if ((in > 0) && (in < 5))
    {
	   int hours;
       cout << "Enter the hours worked in a week: ";
       cin >> hours;
       if (in == 1)
       	  calculate(hours, 8.50);
	   if (in == 2)
       	  calculate(hours, 9.90);
	   if (in == 3)
       	  calculate(hours, 22.40);
	   if (in == 4)
       	  calculate(hours, 30.00);	  
	}
	return 0;
}
