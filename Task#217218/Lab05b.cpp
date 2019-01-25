#include "family.h"
struct FamilyList
{
	Family *family;
	FamilyList* previous;
	FamilyList* next;
	FamilyList();
};
void AddFamily(FamilyList** begin, FamilyList** end, Family* element);
void AddFamily(FamilyList** begin, FamilyList** end, Parents* element, int count);
void AddFamily(FamilyList** begin, FamilyList** end, Children* element, int count);
void ShowFamily(FamilyList** begin, FamilyList** end);
FamilyList* FindFamily(FamilyList** begin, FamilyList** end, string surname);
bool DeleteFamily(FamilyList** begin, FamilyList** end, string surname);
int main()
{
	FamilyList *begin = new FamilyList, *end = new FamilyList;
	string name, surname;
	Family* family = NULL;
	int age, x;
	while (true)
	{
		cout << "1 - create family" << endl;
		cout << "2 - add parent" << endl;
		cout << "3 - add child" << endl;
		cout << "4 - show family" << endl;
		cout << "5 - delete family" << endl;
	 	cout << "6 - add family in family list (using 1)" << endl;
	 	cout << "7 - add family (parents) in family list (using 1)" << endl;
	 	cout << "8 - add family (children) in family list (using 1)" << endl;
	 	cout << "9 - find family (search surname)" << endl;
	 	cout << "10 - delete family (using 9)" << endl;
	 	cout << "11 - show family list" << endl;
	 	cout << "12 - exit" << endl;
	 	cin >> x;
	 	if (x == 1)
	 	{
	 		if (family == NULL)
	 		{
	   		    cout << "Surname: ";
	 			cin >> surname;
	 			family = new Family(surname);
		 	} else cout << "You already have family. You should add this family to list or delete family." << endl;
	 	}
	 	else
	 	if (x == 2)
	 	{
			if (family != NULL)
	 		{
	   		 	cout << "Name: ";
	 			cin >> name;
	 			cout << "Surname: ";
	 			cin >> surname;
	 			cout << "Age: ";
	 			cin >> age;
	 			family->AddParent(name, surname, age);
 		 	} else cout << "Family not exist. You should create family." << endl;
	 	}
	 	else
	 	if (x == 3)
	 	{
	 		if (family != NULL)
	 		{
	   		   cout << "Name: ";
	 		   cin >> name;
	 		   cout << "Surname: ";
	 		   cin >> surname;
	 		   cout << "Age: ";
	 		   cin >> age;
	 		   family->AddChild(name, surname, age);
	 	 	} else cout << "Family not exist. You should create family." << endl;
	 	}
	 	else
		if (x == 4)
		{
			if (family != NULL)
				family->GetInfo();
			else cout << "Family not exist. You should create family." << endl;
		}
		else if (x == 5)
		{
			delete family;
			family = NULL;
		}
	 	else if (x == 6)
	 	{
	 		if (family != NULL)
	 			AddFamily(&begin, &end, family);
	 		else cout << "Nothing to add. You should create family" << endl;		
		}
	 	else if (x == 7)
	 	{
	 		if (family != NULL)
	 		{
	   		   int count;
			   Parents* elem = family->GetParents(count);
			   if (count > 0)
					AddFamily(&begin, &end, elem, count);
			   else cout << "Nothing to add. You should add parents in family" << endl;
 		    } else cout << "Nothing to add. You should create family" << endl;
		}
		else if (x == 8)
	 	{
	 		if (family != NULL)
	 		{
	   		   int count;
			   Children* elem = family->GetChildren(count);
			   if (count > 0)
				   AddFamily(&begin, &end, elem, count);
			   else cout << "Nothing to add. You should add children in family" << endl;
			} else cout << "Nothing to add. You should create family" << endl;
		}
		else if (x == 9)
	 	{
	 		cout << "Surname: ";
	 		cin >> surname;
	 		FindFamily(&begin, &end, surname);
 		}
		else if (x == 10)
	 	{
	 		cout << "Surname: ";
	 		cin >> surname;
	 		DeleteFamily(&begin, &end, surname);
 		}
		else if (x == 11)
	 	   ShowFamily(&begin, &end);
		else if (x == 12)
	 	   break;
	 	else cout << "Invalid input" << endl;
	}
	if ((begin == NULL) || ((begin->family == NULL) && (begin->next == NULL) && (begin->previous == NULL)))
		cout << "Bye-bye";
	else cout << "So long from the " << begin->family->GetSurname() << " family!";
	delete begin;
	delete end;
	delete family;
	return 0;
}
FamilyList::FamilyList()
	{
		family = NULL;
		previous = NULL;
		next = NULL;
	};
void AddFamily(FamilyList** begin, FamilyList** end, Family* element)
{
	if ((*begin == NULL) || (((*begin)->family == NULL) && ((*begin)->next == NULL) && ((*begin)->previous == NULL)))
	{
		(*begin)->family = element;
		*end = *begin;
	}
	else
	{
		FamilyList* x = new FamilyList;
		x->family = element;   
		x->previous = *end;
		x->next = (*end)->next;
		(*end)->next = x;
		*end = x;
	}
}
void AddFamily(FamilyList** begin, FamilyList** end, Parents* element, int count)
{
	if ((*begin == NULL) || (((*begin)->family == NULL) && ((*begin)->next == NULL) && ((*begin)->previous == NULL)))
	{
		(*begin)->family = new Family(element[0].LastName);
		for (int i = 0; i < count; i++)
			(*begin)->family->AddParent(element[i].Name, element[i].LastName, element[i].Age);
		*end = *begin;
	}
	else
	{
		FamilyList* x = new FamilyList;
		x->family = new Family(element[0].LastName);   
		for (int i = 0; i < count; i++)
			x->family->AddParent(element[i].Name, element[i].LastName, element[i].Age);
		x->previous = *end;
		x->next = (*end)->next;
		(*end)->next = x;
		*end = x;
	}
}
void AddFamily(FamilyList** begin, FamilyList** end, Children* element, int count)
{
	if ((*begin == NULL) || (((*begin)->family == NULL) && ((*begin)->next == NULL) && ((*begin)->previous == NULL)))
	{
		(*begin)->family = new Family(element[0].LastName);
		for (int i = 0; i < count; i++)
			(*begin)->family->AddChild(element[i].Name, element[i].LastName, element[i].Age);
		*end = *begin;
	}
	else
	{
		FamilyList* x = new FamilyList;
		x->family = new Family(element[0].LastName);   
		for (int i = 0; i < count; i++)
			x->family->AddChild(element[i].Name, element[i].LastName, element[i].Age);
		x->previous = *end;
		x->next = (*end)->next;
		(*end)->next = x;
		*end = x;
	}
}
void ShowFamily(FamilyList** begin, FamilyList** end)
{
	FamilyList *x = *begin;
	if ((*begin == NULL) || (((*begin)->family == NULL)  && ((*begin)->next == NULL) && ((*begin)->previous == NULL)))
		cout << "List is empty" << endl;
	else
		while (true)
		{
			x->family->GetInfo();
			if (x == *end)
				break;
			x = x->next;
		}
	cout << endl;
}
FamilyList* FindFamily(FamilyList** begin, FamilyList** end, string surname)
{
	FamilyList *x = *begin;
	while (true)
	{
		if (x != NULL)
			if (surname == x->family->GetSurname())
			{
				x->family->GetInfo();
				return x;
			}
		if (x == *end)
			break;
		x = x->next;
	}
	cout << "This not exist" << endl;
	return NULL;
}
bool DeleteFamily(FamilyList** begin, FamilyList** end, string surname)
{
 	 FamilyList* x = FindFamily(&(*begin), &(*end), surname);
 	 if (x != NULL)
	 {
		if (x->next != NULL)
		   x->next->previous = x->previous;
 		else *end = x->previous;
		if (x->previous != NULL)
			x->previous->next = x->next;
		else *begin = x->next;
		delete x;
		x = NULL;
		if ((*begin == NULL) || (((*begin)->family == NULL) && ((*begin)->next == NULL) && ((*begin)->previous == NULL)))
		{
			*begin = new FamilyList;
			*end = *begin;
		}
		return true;
 	}
	 return false;
}


