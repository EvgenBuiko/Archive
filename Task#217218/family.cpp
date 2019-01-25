#include "family.h"
using namespace std;
Family::Family(string surname)
{
	Surname = surname;
	parent_sv = 0;
	child_sv = 0;
	min_parent_age = 150;
}
bool Family::AddParent(string name, string lastname, int age)
{
	if (parent_sv == 2)
	{
	   cout << "Error in AddParent(" << name << ',' << lastname << ',' << age << "): list of family full" << endl;
	   return false;
    }
 	else
 	{
 		if ((age < 0) || (age > 150))
 		{
		    cout << "Error in AddParent(" << name << ',' << lastname << ',' << age << "): invalid age" << endl;
 			return false;
  		}   
 		if (age < min_parent_age)
 		   min_parent_age = age;
  	    parents[parent_sv].Name = name;
  	    parents[parent_sv].LastName = lastname;
  	    parents[parent_sv].Age = age;
  	    parent_sv++;
  	    return true;
 	}
 	return false;
}
bool Family::AddChild(string name, string lastname, int age)
{
	if (child_sv == 10)
	{
	   cout << "Error in AddChild(" << name << ',' << lastname << ',' << age << "): list of children full" << endl;
	   return false;
    }
 	else
 	{
 		if ((age < 0) || (age >= min_parent_age))
 		{
		    cout << "Error in AddChild(" << name << ',' << lastname << ',' << age << "): invalid age" << endl;
 			return false;
  		}   
 		children[child_sv].Name = name;
  	    children[child_sv].LastName = lastname;
  	    children[child_sv].Age = age;
  	    child_sv++;
  	    return true;
 	}
 	return false;	
}
void Family::GetInfo()
{
	cout << "Information about family:" << endl;
	cout << "\tFamily surname: " << Surname << endl;
	cout << "\tParents:" << endl;
	for (int i = 0; i < parent_sv; i++)
	{
		cout << "\t\t" << i + 1 << ") First Name: " << parents[i].Name << endl;
		cout << "\t\t   Last Name: " << parents[i].LastName << endl;
		cout << "\t\t   Age: " << parents[i].Age << endl;
		cout << endl;
	}
	cout << "\tChildren:" << endl;
	for (int i = 0; i < child_sv; i++)
	{
		cout << "\t\t" << i + 1 << ") First Name: " << children[i].Name << endl;
		cout << "\t\t" << ((i + 1 == 10) ? " " : "") << "   Last Name: " << children[i].LastName << endl;
		cout << "\t\t" << ((i + 1 == 10) ? " " : "") << "   Age: " << children[i].Age << endl;
		cout << endl;
	} 
	cout << endl; 
}
Parents* Family::GetParents(int& count)
{
	count = parent_sv;
	return parents;
}
Children* Family::GetChildren(int& count)
{
	count = child_sv;
	return children;
}
string Family::GetSurname()
{ return Surname; }
bool operator==(Parents elem1, Parents elem2)
{
	bool flag = true;
	flag = (elem1.Name == elem2.Name);
	flag = (elem1.LastName == elem2.LastName);
	flag = (elem1.Age == elem2.Age);
	return flag;
}
bool operator==(Children elem1, Children elem2)
{
	bool flag = true;
	flag = (elem1.Name == elem2.Name);
	flag = (elem1.LastName == elem2.LastName);
	flag = (elem1.Age == elem2.Age);
	return flag;
}
bool operator==(Family elem1, Family elem2)
{
	bool flag = true;
	int count1, count2;
	Parents* parent1, *parent2;
	parent1 = elem1.GetParents(count1);
	parent2 = elem2.GetParents(count2);
	flag = (count1 == count2);
	if (flag == false)
		return flag;
	for (int i = 0; i < count1; i++)
		flag = (parent1[i] == parent2[i]);
	if (flag == false)
		return flag;
	Children* children1, *children2;
	children1 = elem1.GetChildren(count1);
	children2 = elem2.GetChildren(count2);
	flag = (count1 == count2);
	if (flag == false)
		return flag;
	for (int i = 0; i < count1; i++)
		flag = (children1[i] == children2[i]);
	if (flag == false)
		return flag;
	flag = (elem1.GetSurname() == elem2.GetSurname());
	return flag;
}
