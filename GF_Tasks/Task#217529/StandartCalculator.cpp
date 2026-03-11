#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stack>
using namespace std;
char LastSymbol(char *line, int i)
{
	if ((line[i] == '(') || (line[i] == ')')) return LastSymbol(line, i - 1);
	else return line[i];
}
bool InvalidCheck(char *line, bool &hesis)
{
	char pred; int lefthesis = 0, righthesis = 0, length = strlen(line);
	for (int i = 0; i < length; i++)
	{
		if (line[i] == '(') lefthesis++;
		if (line[i] == ')') righthesis++;
		if (line[i] == ' ') pred = LastSymbol(line, i - 1);
        if ((i - 1 > -1) && (line[i - 1] == ' '))
        {
           if ((line[i] > 47) && (line[i] < 58) && ((pred > 47) && (pred < 58))) return true;
		   if ((i + 1 < length) && (line[i] == '-') && ((line[i + 1] > 47) && (line[i + 1] < 58)) && ((pred > 47) && (pred < 58))) return true;
		   if (((line[i] == '+') || (line[i] == '-') || (line[i] == '/') || (line[i] == '*')) && ((pred == '+') || (pred == '-') || (pred == '/') || (pred == '*')) && (((i + 1 < length) && ((line[i + 1] < 48) || (line[i + 1] > 57))) || (i + 1 >= length))) return true;
        }
	}
	if (lefthesis > 0) hesis = true;
	if (lefthesis != righthesis) return true;
	return false;
}
void MakeStep(double &result, int &flag, char *str)
{	
	if (flag == -1)
	{
	   result = strtod(str, NULL);
	   flag = 0;
    }
    else if (flag == 0) flag = str[0];
    else 
	{
        if (flag == 43) result += strtod(str, NULL);
		else if (flag == 45) result -= strtod(str, NULL);
		else if (flag == 42) result *= strtod(str, NULL);
		else if (flag == 47) result /= strtod(str, NULL);
		flag = 0;
	}
}
double Calculate(char *line)
{
	double result = 0; int i = 0, j = -1, flag = -1, length = strlen(line); char *str = new char[255];
	while (true)
	{
		if ((line[i] == ' ') || (i == length - 1))
		{
			if (i == length - 1) str[++j] = line[i];
			str[++j] = '\0'; j = -1; 
			MakeStep(result, flag, str);
			if (i == length - 1) break;  
		} else str[++j] = line[i];
		i++;
	}
	delete str; return result;
}
// (5 * (5 + 7 - 1)
void Pop(stack<double> &value, stack<char> &symbol)
{
	double x, y;
	x = value.top(); value.pop();
	y = value.top(); value.pop();
	if (symbol.top() == '+') value.push(y + x);
	if (symbol.top() == '-') value.push(y - x);
	if (symbol.top() == '/') value.push(y / x);
	if (symbol.top() == '*') value.push(y * x);  
	symbol.pop(); 
}
double HardCalculate(char *line)
{
    int i = 0, j = -1, length = strlen(line); char *str = new char[255];
    stack<char> symbolstack; stack<double> valuestack;
	while (true)
	{
		if (i >= length) break;
		if ((line[i] == ' ') || (line[i] == '(') || (line[i] == ')') || (i == length - 1))
		{
			if ((line[i] == '(') || (i == length - 1)) str[++j] = line[i];
			str[++j] = '\0'; j = -1; 
			if (str[0] == '(') symbolstack.push(str[0]);
			else if ((str[0] == '+') || (str[0] == '-') || (str[0] == '*') || (str[0] == '/'))
			{
				if ((symbolstack.empty() != true) && (symbolstack.top() != '(')) 
				   while ((symbolstack.empty() == false) && (symbolstack.top() != '(')) Pop(valuestack, symbolstack);
 			    symbolstack.push(str[0]);
			} else valuestack.push(strtod(str, NULL));
			if ((i == length - 1) && (line[i] != ')')) break;  
		} else str[++j] = line[i];
		if (line[i] == ')')
		{
		  	while (symbolstack.top() != '(') Pop(valuestack, symbolstack);
		  	symbolstack.pop();
		}
		i++;
	}
	delete str;
	while (valuestack.size() > 1) Pop(valuestack, symbolstack);
	return valuestack.top();
}
void StandartCalculator()
{
	bool hesises = false;
	char *line = new char[255];
	cout << "What is your equation ? ";
	cin.getline(line, 255);
	if (InvalidCheck(line, hesises) == true)
 		cout << "Error: invalid equation";
	else
	{
	 	if (hesises == false) cout << "Result: " << Calculate(line) << endl;
	   		else cout << "Result: " << HardCalculate(line) << endl;
		delete line;
	}
}
