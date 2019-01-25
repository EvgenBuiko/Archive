//********************************************************
// Name:        --------
// KUID:        --------
// Assignment:  Fall 2018 Project 2
//********************************************************
//
//

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void menu();
// final output to screen and file
void print (double exam[],
            int no_of_exams,
            double lab[],
            int no_of_labs,
            double project[],
            int no_of_projects,
            double weighted_mean,
            double best_of_project,
            double average_of_labs,
            double total_marks,
            char grade,
            char comments[],
            char name[])
{
	ofstream fout("output.txt");
	cout << "student name: " << name << endl;
	fout << "student name: " << name << endl;
	cout << "grade is: " << grade << endl;
	fout << "grade is: " << grade << endl;
	cout << "sample file output starts next: " << endl;
	fout << "sample file output starts next: " << endl;
	for (int i = 0; i < no_of_projects; i++)
	{
		cout << "project" << i + 1 << " marks: " << project[i] << endl;
		fout << "project" << i + 1 << " marks: " << project[i] << endl;
	}
	cout << "the best of project marks is: " << best_of_project << endl; 
	fout << "the best of project marks is: " << best_of_project << endl; 
	for (int i = 0; i < no_of_exams; i++)
	{
		cout << "exam" << i + 1 << " marks: " << exam[i] << endl;
		fout << "exam" << i + 1 << " marks: " << exam[i] << endl;
	}
	cout << "the weighted mean of exam marks is: " << weighted_mean << endl;
	fout << "the weighted mean of exam marks is: " << weighted_mean << endl;
	for (int i = 0; i < no_of_labs; i++)
	{
		cout << "lab" << i + 1 << " marks: " << lab[i] << endl;
		fout << "lab" << i + 1 << " marks: " << lab[i] << endl;
	}
	cout << "the average of lab marks is: " << average_of_labs << endl;
	fout << "the average of lab marks is: " << average_of_labs << endl;
	cout << "total marks obtained is: " << total_marks << endl;
	fout << "total marks obtained is: " << total_marks << endl;
	cout << "comments: " << comments << endl; 
	fout << "comments: " << comments << endl; 
	fout.close();
	int *alloc_buf_int = &no_of_exams;
	delete alloc_buf_int;
	alloc_buf_int = &no_of_labs;
	delete alloc_buf_int;
	alloc_buf_int = &no_of_projects;
	delete alloc_buf_int;
	alloc_buf_int = NULL;
	double *alloc_buf_double = &weighted_mean;
	delete alloc_buf_double;
	alloc_buf_double = &best_of_project;
	delete alloc_buf_double;
	alloc_buf_double = &average_of_labs;
	delete alloc_buf_double;
	alloc_buf_double = &total_marks;
	delete alloc_buf_double;
	alloc_buf_double = NULL;
	char *alloc_buf_char = &grade;
	delete alloc_buf_char;
	alloc_buf_char = NULL;
 	exam = NULL;	
	lab = NULL;
	project = NULL;
	comments = NULL;
	name = NULL;
}

// called from fillA
// compute compV based on s for formula selection
// return value is either weighted mean, average or max of values in a[]
double computeV(char &s, double a[])
{
	double max = a[0], min = a[0], sum = 0;
	if (s == 'a')
 	{
 		for (int i = 0; i < 3; i++)
 			if (max < a[i])
 			   max = a[i];
	    a = NULL;
	    double *alloc_buf_double = &min;
		delete alloc_buf_double;
		alloc_buf_double = &sum;
		delete alloc_buf_double;
	    alloc_buf_double = NULL;
		return max;
    }
	if (s == 'b')
	{
		for (int i = 0; i < 5; i++)
 			sum += a[i];
		a = NULL;
	 	double *alloc_buf_double = &max;
		delete alloc_buf_double;
		alloc_buf_double = &min;
		delete alloc_buf_double;
		alloc_buf_double = NULL;
	    return sum / 5;
	}
	if (s == 'c')
	{
		double *alloc_buf_double = &max;
		delete alloc_buf_double;
		alloc_buf_double = &min;
		delete alloc_buf_double;
		alloc_buf_double = &sum;
		delete alloc_buf_double;
		alloc_buf_double = NULL;
		if (a[0] >= a[1])
		   return ((2 * a[0] + a[1] ) / 3);
        else return ((2 * a[1] + a[0] ) / 3);
	}
}
// either accept input or show bypass message based on D
// accept input from the user and fill in each data array
// call computeV after the array has been filled
// compV is passed by reference to return best project score back to menu() function, return average score of labs and similarly for exams depending on choice value 
// choice determine we are filling lab,project or exam marks
void fillA(double a[], int almt, char &choice, double& compV, bool &D)
{
	if (D == true)
	{
		if (choice == 'd')
		   cout << "select all other choices before selecting that choice." << endl;
        else cout << "that menu choice was already selected. " << endl;
		return;
	}
	char *type = new char[255]; 
	if (choice == 'a')
	   strcpy(type, "project");
	if (choice == 'b')
	   strcpy(type, "lab");
    if (choice == 'c')
	   strcpy(type, "exam");
	for (int i = 0; i < almt; i++)
	{
	   cout << "enter " << type << " " << i + 1 << " mark>";
       cin >> a[i];
	   while((a[i] < 0) || (a[i] > 100)) 
       {
	        cout << "the mark entered is invalid. valid range is 0 to 100 inclusive." << endl
     	         << "enter " << type << " " << i + 1 << " mark>";
            cin >> a[i];
	   }
    }
	compV = computeV(choice, a);
	cout << "the " << type << " mark considered for grade is: " << compV << endl;
	D = true; 
	a = NULL;
	int *alloc_buf_int = &almt;
	delete alloc_buf_int;
	alloc_buf_int = NULL;
	delete[] type;
	type = NULL;
	cin.get();
}
// create a call-by-reference getname function
void getname(char *pointer)
{
	cout << "Enter the name of the student: ";
	cin.getline(pointer, 255);
}
// create a badinput function
bool badinput(char *input)
{
	bool result = false;
	if (strlen(input) != 1)
	   result = true;
	if ((input[0] < 'a') || (input[0] > 'd'))
	   result = true;
    if (result == true)
       cout << input << " is an invalid menu choice" << endl;
	return result;   
}
// create a done with input function
char Input()
{
	char *input = new char[255];
	menu();
	cin.getline(input, 255);
	while (badinput(input) == true)
	{
		menu();
		cin.getline(input, 255);
	}
	char result = input[0];
	delete[] input;
	input = NULL;
	return result;
}
// create the controlling menu
// initialize all variables
// post input processing of data
// call print with final results
void menu()
{
	cout << "Select a menu choice from the following options." << endl
		 << "a. Project Marks" << endl
		 << "b. Lab Marks" << endl
		 << "c. Exam Marks" << endl
	  	 << "d. Calculate total marks" << endl
		 << "> ";	
}
int main()
{
	char *name = new char[255],
		 *comments = new char[255];
    char choice = 0, grade = 0;
    bool selected[4] = { false, false, false, false },
		 allselected = false,
		 buf = true;
    double projects[3] = { -1, -1, -1 },
		   labs[5] = { -1, -1, -1, -1, -1 },
		   exams[2] = { -1, -1 },
		   compV[4] = { 0, 0, 0, 0 };
	getname(name);
	while (true)
	{
		choice = Input();
		if (choice == 'a')
		   fillA(projects, 3, choice, compV[choice - 'a'], selected[choice - 'a']);
		if (choice == 'b')
		   fillA(labs, 5, choice, compV[choice - 'a'], selected[choice - 'a']);
		if (choice == 'c')
		   fillA(exams, 2, choice, compV[choice - 'a'], selected[choice - 'a']);
		if (choice == 'd')
		{
		    if (allselected == false)
		   	   fillA(compV, 0, choice, compV[choice - 'a'], buf);
  	        else
	        {
	        	compV[3] = compV[1] * 0.25 + compV[0] * 0.25 + compV[2]* 0.5;
				if (compV[3] < 60)
				{
				   grade = 'F';
				   strcpy(comments, "Failed");
			    }
				if (compV[3] >= 60)
				{
				   grade = 'D';
				   strcpy(comments, "Warning of probation");
			    }
			    if (compV[3] >= 70)
				{
				   grade = 'C';
				   strcpy(comments, "Needs to improve");
			    }
			    if (compV[3] >= 80)
				{
				   grade = 'B';
				   strcpy(comments, "Good");
			    }
			    if (compV[3] >= 90)
				{
				   grade = 'A';
				   strcpy(comments, "Outstanding");
			    }
				selected[3] = true;
				print (exams, 2, labs, 5, projects, 3, compV[2], compV[0], compV[1], compV[3], grade, comments, name);
			}
		}
		allselected = true;
		for (int i = 0; i < 3; i++)
			if (selected[i] == false)
			   allselected = false;
		if (selected[3] == true)
		   break;
	}
	delete[] name;
	name = NULL;
	delete[] comments;
	comments = NULL;
	// clearing memory!
	char *alloc_buf_char = &choice;
	delete alloc_buf_char;
	alloc_buf_char = &grade;
	delete alloc_buf_char;
	alloc_buf_char = NULL;
 	bool *alloc_buf_bool = selected;
 	delete[] alloc_buf_bool;
	alloc_buf_bool = &allselected;
	delete alloc_buf_bool;
	alloc_buf_bool = &buf;
    delete alloc_buf_bool;
    alloc_buf_bool = NULL;
	double *alloc_buf_double = projects;
	delete[] alloc_buf_double;
	alloc_buf_double = labs;
	delete[] alloc_buf_double;
	alloc_buf_double = exams;
	delete[] alloc_buf_double;
	alloc_buf_double = compV;
	delete[] alloc_buf_double;
	alloc_buf_double = NULL;
	return 0;
}
