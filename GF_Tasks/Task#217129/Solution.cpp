#include<iostream>
using namespace std;
int main()
{
	char array[6] = { 'a', 'a', 'a', '1', '1', '\0' };
	cout << array << endl;
	int count = 1, i = 2, x;
	bool flag = false;
	while (true)
	{
		if (flag == false)
		{
			if (array[4] == '1')
   			   array[4]++;
   			else 
   			{
		 	if (array[3] == '2')
			   flag = true;
			else 
 			{
 	 	 	 	array[3]++;
 	 	 		array[4]--;
			}
			}
		}
		if (flag == true)
		{
			array[4]--;
			array[3]--;
			flag = false;
			while (array[i] == 'c')
			{
				if (i == 0)
	   			{
	   	  		   cout << "Total number of strings: " << count << endl;
	   	  		   cout << "Counting rule: the value \'count\' is incremented by 1 after each generation of a new string of the described rule.";
				   return 0;
				}
   				array[i] = 'a';
				i--;					
   			}
			array[i]++;
			i = 2;
  		}
		count++;
		cout << array << endl;
	}
}
