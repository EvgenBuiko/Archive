#include <iostream>
#include <string>
using namespace std;
struct Parents
{
	string Name;
	string LastName;
	int Age;
};
struct Children
{
    string Name;
    string LastName;
	int Age;	
};
class Family
{
	private:
		string Surname;
		int child_sv, 
			parent_sv,
			min_parent_age;
		Parents parents[2];
		Children children[10];
	public:
		Family(string surname);
		bool AddChild(string name, string surname, int age);
		bool AddParent(string name, string surname, int age);
		Parents* GetParents(int& count);
		Children* GetChildren(int& count);
		string GetSurname();
		void GetInfo();
};
bool operator==(Family elem1, Family elem2);
bool operator==(Children elem1, Children elem2);
bool operator==(Parents elem1, Parents elem2);

