#include <iostream>
#include <string>
#include <cstring>
using namespace std;
struct Birthdate
{
	int day;
	int month;
	int year;
};
struct Account
{
	char* name;
	char* password;
	Birthdate birthdate;
	char* contact;
	Account()
	{
		name = new char[255];
		password = new char[255];
		contact = new char[255];
	}
};
bool CheckPalindrome(char* str)
{
	int i = 0;
	bool flag = true;
	while (strlen(str) - i - 1 >= i)
	{
		if  (str[i] != str[strlen(str) - i - 1])
			flag = false;
		i++;
	}
	return flag;
}
int main()
{
	Account account = Account();
 	char *str = new char[255];
	bool flag = false;	   
	while (flag == false)
	{
 	     cout << "-------->Start Pointing-------->" << endl << 
 		 	   	 "Welcome to Rhode's Airline Inc.." << endl;
		 cout << "Please enter your name on your account:" << endl;
		 cin.getline(account.name, 255);
 		 cout << "Please enter your birthdate:" << endl;
		 cout << "Please enter day of birthdate:" << endl;
		 cin >> account.birthdate.day;
 		 cout << "Please enter month of birthdate:" << endl;
		 cin >> account.birthdate.month;
		 cout << "Please enter year of birthdate:" << endl;
 		 cin >> account.birthdate.year;
 		 cin.get();
		 cout << "Please enter your password:" << endl;
		 cin.getline(account.password, 255);
		 cout << "Please enter your contact (e-mail, telephone or smb.):" << endl;
		 cin.getline(account.contact, 255);
 		 cout << "Account name: " << account.name << endl;
		 cout << "Account password: " << account.password << endl;
		 cout << "Account birthdate: " << account.birthdate.day << ':' << account.birthdate.month << ':' << account.birthdate.year << endl;
		 cout << "Account contact: " << account.contact << endl;
		 cout << "Create account (Yes, No): " << endl;
		 cin.getline(str, 255);
		 if (strcmp(str, "Yes") == 0)
		 	flag = true;
	 	 else system("cls");
    }
	cout << "Rhode's Airline Inc. account created" << endl;
 	system("pause");
 	do
 	{
 		system("cls");
 		flag = true;
		cout << "-------->Start Pointing-------->" << endl << 
	 		  	"Welcome to Rhode's Airline Inc.." << endl;
		cout << "Please sign in:" << endl;
		cout << "User name: ";
		cin.getline(str, 255);
		if (strcmp(str, account.name) != 0)
  		{
  			cout << "Uncorrect user name. Please try again" << endl;	
		    flag = false;
		}
		else
		{
		 	cout << "Password: ";
			cin.getline(str, 255);
			if (strcmp(str, account.password) != 0)
 			{
  			   cout << "Uncorrect password. Please try again" << endl;	
   	 		   flag = false;
			}
		}
		system("pause");
    } while (flag == false);
    cout << "Complited" << endl;
    cout << "-------->Start Pointing-------->" << endl;
	cout << "Your password: " << account.password << " is ";
	char *pointer = account.password; 
	if (CheckPalindrome(pointer) == true) 
 	   cout << "a palindrome\nAdress of Pointer Palindrome: " << (int)&pointer << " B" << endl;
	else cout << "Not a palindrome" << endl;
	delete str;
	delete pointer;
	delete account.name;
	delete account.password;
	delete account.contact; 
	return 0;
}
