#include <iostream>
#include <fstream>
#include <string>
#include <random>

bool doesUserWantsToUseATMMachine()
{
	bool rResult = false;

	while (true)
	{
		std::cout << "Press l to login with your account number and PIN\nPress q to quit\n";

		std::string answer;
		std::cin >> answer;

		if ((answer == "l") || (answer == "q"))
		{
			rResult = (answer == "l");
			break;
		}

		std::cout << "Sorry, I didn't understand." << std::endl;
	}

	return rResult;
}
bool checkAccountNumber(std::string &number)
{
	if (number.size() != 5)
	{
		return false;
	}
	for (auto a : number)
	{
		if (static_cast<int>(a) < '0' || static_cast<int>(a) > '9')
		{
			return false;
		}
	}
	return true;
}

bool checkPIN(std::string &pin)
{
	if (pin.size() != 4)
	{
		return false;
	}
	for (auto a : pin)
	{
		if (static_cast<int>(a) < '0' || static_cast<int>(a) > '9')
		{
			return false;
		}
	}
	return true;
}
std::string login(std::fstream &fin)
{
	bool rResult = false;

	while (true)
	{

		std::cout << "Enter you Account Number" << std::endl;
		std::string number;
		std::cin >> number;
		rResult = checkAccountNumber(number);

		std::cout << "Enter you PIN" << std::endl;
		std::string pin;
		std::cin >> pin;

		rResult = checkPIN(pin);
		if (rResult == true)
		{
			fin.open("input.txt", std::fstream::in);
			std::string str_buf;
			while (fin.eof() == false)
			{
				getline(fin, str_buf);
				if ((str_buf.find(number) != -1) && (str_buf.find(number) < 5))
				{
					fin.close();
					return str_buf;
				}
			}
		}
		fin.close();
		std::cout << "Sorry, I didn't understand." << std::endl;
	}
}


void info()
{
	std::cout << std::endl << "Press q to quit." << std::endl
		<< "Press w to withdraw money." << std::endl
		<< "Press r to request balance." << std::endl
		<< "Press d to deposit money." << std::endl;
}
void depositMoney(double &balance, double &value)
{
	balance += value;
	std::cout << "Done" << std::endl;
}
void withdrawMoney(double &balance, double &value)
{
	if (value > balance)
	{
		std::cout << "Not enough money." << std::endl;
		return;
	}
	else
	{
		std::cout << "Take your money." << std::endl;
		balance -= value;
	}
}
void useATMMachine(std::fstream &fdata, int &count)
{
	std::string str = login(fdata);
	int balance_pos = str.find(',') + 2;
	double balance = stod(str.substr(balance_pos));
	double deposit = 0;
	std::cout << "Hello " << str.substr(6, balance_pos - 8) << std::endl;
	std::string answer = "";
	while (answer != "q")
	{
		info();
		std::cin >> answer;
		if (answer == "w")
		{
			double value = 0;
			std::cout << "Enter the amount you want to withdraw" << std::endl;
			std::cin >> value;
			withdrawMoney(balance, value);
		}
		else if (answer == "r")
		{
			std::cout << "Balance money = " << balance << " $" << std::endl;
		}
		else if (answer == "d")
		{
			double value = 0;
			std::cout << "Enter the amount you want to deposit" << std::endl;
			std::cin >> value;
			depositMoney(balance, value);
			//std::cout<<"Deposit money = "<<deposit<<" $"<<std::endl;
		}
		else if (answer != "q")
		{
			std::cout << "Sorry, I didn't understand." << std::endl;
		}
	}
	std::string *strarr = new std::string[count];
	int i = 0;
	fdata.open("input.txt", std::fstream::in);
	while ((fdata.eof() == false) && (i < count))
	{
		getline(fdata, strarr[i]);
		i++;
	}
	fdata.close();
	fdata.open("input.txt", std::fstream::out);
	fdata.trunc;
	for (i = 0; i < count; i++)
		if (strarr[i] != str)
			fdata << strarr[i] << std::endl;
		else fdata << str.substr(0, balance_pos) << balance << std::endl;
	fdata.close();
	delete[] strarr;
}

int main()
{
	std::fstream fdata;
	std::string buf;
	int count = 0;
	fdata.open("input.txt", std::fstream::in);
	while (fdata.eof() == false)
	{
		getline(fdata, buf);
		count++;
	}
	fdata.close();
	while (doesUserWantsToUseATMMachine())
	{
		useATMMachine(fdata, count);
	}
}
