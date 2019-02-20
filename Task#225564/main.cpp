#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "gradeutil.h"
using namespace std;
void summary();
void summaryAll();

int main()
{
 	cout << std::fixed;
 	cout << std::setprecision(2);
 	string line;
 	getline(cin, line);
 	ifstream fin(line);
 	if (fin.good())
 	{
 		getline(fin, line, ',');
 		College college(line);
 		cout << "** College of " << line << ", ";
 		getline(fin, line, ',');
 		cout << line << ' ';
 		getline(fin, line);
 		cout << line << " **" << endl;
 		vector<Dept> depts;
 		vector<Course> courses;
	 	getline(fin, line);
	 	int coursescounter = 0, studentscounter = 0, DFW = 0, N = 0, allN = 0;
	 	while (!fin.eof())
 		{
		 	getline(fin, line);
		 	if (line.empty())
		 	   break;
 			Course course = ParseCourse(line);
 			courses.push_back(course);
 			coursescounter++;
 			studentscounter += course.getNumStudents();
 			bool flag = false;
			for (Dept& x : depts)
 				if (course.Dept.compare(x.Name) == 0)
 				{
 					x.Courses.push_back(course);
 					flag = true;
 					break;
			 	}
			if (!flag)
		 	{
			    Dept buf(course.Dept);
		    	buf.Courses.push_back(course);
		    	depts.push_back(buf);
		    }
 		}
 		college.Depts = depts;
 		cout << "# of courses taught: " << coursescounter << endl;
 		cout << "# of students taught: " << studentscounter << endl;
 		GradeStats allstat; 
		double allrate = 0;
 		for (Course& x : courses)
 		{
		 	GradeStats stat = GetGradeDistribution(x);
		 	allstat.N += stat.N;
		 	allstat.PercentA += stat.PercentA * stat.N;
		 	allstat.PercentB += stat.PercentB * stat.N;
		 	allstat.PercentC += stat.PercentC * stat.N;
		 	allstat.PercentD += stat.PercentD * stat.N;
		 	allstat.PercentF += stat.PercentF * stat.N;
		 	allrate += GetDFWRate(x, DFW, N) * N;
		 	allN += N;
		}
		cout << "grade distribution (A-F): " << allstat.PercentA / allstat.N << "%, " 
 			  		   					   	 << allstat.PercentB / allstat.N << "%, "
 		 									 << allstat.PercentC / allstat.N << "%, "
 		 		   					   	 	 << allstat.PercentD / allstat.N << "%, "
		 		   					   	 	 << allstat.PercentF / allstat.N << "%" << endl;
	    cout << "DFW rate: " << allrate / allN << '%' << endl << endl; 
		while (true)
		{
			cout << "Enter a command> ";
			string command;
			getline(cin, command);
			if (command.compare("#") == 0)
			   break;
   			else
			if (command.compare("summary") == 0 || command.compare("search") == 0 || 
			    command.compare("unknown") == 0 || command.compare("dfw") == 0 || command.compare("letterA") == 0)
			{
				cout << "dept name, or all? ";
				getline(cin, line);
				if (line.compare("all") == 0)
				{
					vector<Dept> buf = college.Depts;
					sort(buf.begin(), buf.end(), [](const Dept& val1, const Dept& val2) 
					{ return val1.Name < val2.Name; });	
  					if (command.compare("summary") == 0)
					{
					   for (Dept x : buf)
					   	   SummaryPrint(x, cout);
			   		}
			   		else if (command.compare("search") == 0)
 	   				{
 	   				 	string instructorPrefix;
						int courseNum;
 						cout << "course # or instructor prefix? ";
 						cin >> instructorPrefix;
 						stringstream ss(instructorPrefix); // create stringstream object
 						ss >> courseNum; // try to convert input to a course #:
 						vector<Course> buf1;
						if ( ss.fail() )
				 		{
						   	string str = ss.str();
		   	 			   	// conversion failed, input is not numeric
		   	 		   		for (Dept& x : college.Depts)
		   	 		   			for (Course& y : FindCourses(x, str))
		   	 		   				buf1.push_back(y);
   	 		   					sort(buf1.begin(), buf1.end(), [](const Course& val1, const Course& val2) 
							{ 
							  	if (val1.Instructor.compare(val2.Instructor) != 0)			   
	  				   			   	return val1.Instructor < val2.Instructor;
								else if (val1.Number != val2.Number)
									return val1.Number < val2.Number;
								else return val1.Section < val2.Section;	  
							});	
						}
 						else
						{ 	// conversion worked, courseNum contains numeric value
							for (Dept& x : college.Depts)
		   	 		   			for (Course& y : FindCourses(x, courseNum))
		   	 		   				buf1.push_back(y);
   							sort(buf1.begin(), buf1.end(), [](const Course& val1, const Course& val2) 
							{ 
							  	if (val1.Dept.compare(val2.Dept) != 0)			   
	  				   			   	return val1.Dept < val2.Dept;
								else if (val1.Number != val2.Number)
									return val1.Number < val2.Number;
								else return val1.Section < val2.Section;	  
							});		
		   	 		   	}
						for (Course& y : buf1)
							CourseOutput(y, cout);
						cin.get();
					}
					else if (command.compare("unknown") == 0)
					{
						vector<Course> buf1;
						for (Dept& x : buf)
							for (Course& y : x.Courses)
								if (y.getGradingType() == Course::Unknown)
								   buf1.push_back(y);
		   			    sort(buf1.begin(), buf1.end(), [](const Course& val1, const Course& val2)
						{ 
  				   			if (val1.Dept.compare(val2.Dept) != 0)
  				   			   	return val1.Dept < val2.Dept;
							else if (val1.Number != val2.Number)
								return val1.Number < val2.Number;
							else return val1.Section < val2.Section; 
						});	   
		    			for (Course& x : buf1)
			   				CourseOutput(x, cout);
			   		}
					else if (command.compare("dfw") == 0)
					{
						double threshold;
						cout << "dfw threshold? ";
						cin >> threshold;
						vector<Course> buf1;
						for (Dept& x : buf)
							for (Course& y : x.Courses)
								if (GetDFWRate(y, DFW, N) > threshold)
								   buf1.push_back(y);
		   			    sort(buf1.begin(), buf1.end(), [](const Course& val1, const Course& val2)
					    {
					    	int DFW = 0, N = 0;
					    	double dfw1 = GetDFWRate(val1, DFW, N), dfw2 = GetDFWRate(val2, DFW, N);
					    	if (dfw1 != dfw2)
					    	   return dfw1 > dfw2;
		    	   			else if (val1.Dept.compare(val2.Dept) != 0)
  				   			   	return val1.Dept < val2.Dept;
							else if (val1.Number != val2.Number)
								return val1.Number < val2.Number;
							else return val1.Section < val2.Section;   
						});
						for (Course& x : buf1)
			   				CourseOutput(x, cout);
			   			cin.get();
					}
					else if (command.compare("letterA") == 0)
					{
						double threshold;
						cout << "letter A threshold? ";
						cin >> threshold;
						vector<Course> buf1;
						for (Dept& x : buf)
							for (Course& y : x.Courses)
								if (GetGradeDistribution(y).PercentA > threshold)
								   buf1.push_back(y);
		   			    sort(buf1.begin(), buf1.end(), [](const Course& val1, const Course& val2)
					    {
					    	int DFW = 0, N = 0;
					    	if (GetGradeDistribution(val1).PercentA != GetGradeDistribution(val2).PercentA)
					    	   return GetGradeDistribution(val1).PercentA > GetGradeDistribution(val2).PercentA;
		    	   			else if (val1.Dept.compare(val2.Dept) != 0)
  				   			   	return val1.Dept < val2.Dept;
							else if (val1.Number != val2.Number)
								return val1.Number < val2.Number;
							else return val1.Section < val2.Section;   
						});
						for (Course& x : buf1)
			   				CourseOutput(x, cout);
			   			cin.get();
					}
   			    }
				else
				for (Dept& x : college.Depts)
					if (x.Name.compare(line) == 0)
					{
						if (command.compare("summary") == 0)
			   			    SummaryPrint(x, cout);
						else if (command.compare("search") == 0)
 	   					{
 	   				 	 	string instructorPrefix;
							int courseNum;
 							cout << "course # or instructor prefix? ";
 							cin >> instructorPrefix;
 							stringstream ss(instructorPrefix); // create stringstream object
 							ss >> courseNum; // try to convert input to a course #:
 							vector<Course> buf1;
							if ( ss.fail() )
				 			{
							   	// conversion failed, input is not numeric
		   	 		   			string str = ss.str();
		   	 			   		buf1 = FindCourses(x, str);
		   	 		   		}
 							else buf1 = FindCourses(x, courseNum); // conversion worked, courseNum contains numeric value
							for (Course& y : buf1)
								CourseOutput(y, cout);
							cin.get();
						}
						else if (command.compare("unknown") == 0)
						{
						 	vector<Course> buf1;
							for (Course& y : x.Courses)
								if (y.getGradingType() == Course::Unknown)
								   buf1.push_back(y);
		   			   		sort(buf1.begin(), buf1.end(), [](const Course& val1, const Course& val2)
						  	{ 
  				   			  	if (val1.Number != val2.Number)
									return val1.Number < val2.Number;
								else return val1.Section < val2.Section; 
							});	   
		   			    	for (Course& x : buf1)
			   					CourseOutput(x, cout);
						}
						else if (command.compare("dfw") == 0)
						{
						 	double threshold;
							cout << "dfw threshold? ";
							cin >> threshold;
							vector<Course> buf1;
							for (Course& y : x.Courses)
								if (GetDFWRate(y, DFW, N) > threshold)
									buf1.push_back(y);
		   			    	sort(buf1.begin(), buf1.end(), [](const Course& val1, const Course& val2)
					    	{
					    	 	int DFW = 0, N = 0;
					    		double dfw1 = GetDFWRate(val1, DFW, N), dfw2 = GetDFWRate(val2, DFW, N);
					    		if (dfw1 != dfw2)
					    	   	    return dfw1 > dfw2;
		    	   				else if (val1.Dept.compare(val2.Dept) != 0)
  				   			   		return val1.Dept < val2.Dept;
								else if (val1.Number != val2.Number)
									return val1.Number < val2.Number;
								else return val1.Section < val2.Section;   
							});
							for (Course& x : buf1)
			   					CourseOutput(x, cout);
				   			cin.get();
						}
						else if (command.compare("letterA") == 0)
						{
						 	double threshold;
							cout << "letter A threshold? ";
							cin >> threshold;
							vector<Course> buf1;
							for (Course& y : x.Courses)
								if (GetGradeDistribution(y).PercentA > threshold)
								   buf1.push_back(y);
		   			    	sort(buf1.begin(), buf1.end(), [](const Course& val1, const Course& val2)
					    	{
					    	 	int DFW = 0, N = 0;
					    		if (GetGradeDistribution(val1).PercentA != GetGradeDistribution(val2).PercentA)
					    	   	   	return GetGradeDistribution(val1).PercentA > GetGradeDistribution(val2).PercentA;
		    	   				else if (val1.Dept.compare(val2.Dept) != 0)
  				   			   		return val1.Dept < val2.Dept;
								else if (val1.Number != val2.Number)
									return val1.Number < val2.Number;
								else return val1.Section < val2.Section;   
							});
							for (Course& x : buf1)
			   					CourseOutput(x, cout);
				   			cin.get();
						}
					}
   			}
   			else cout << "**unknowm command" << endl;
		}	 		   					   	 
	}
	else
	cout << "**error: file open failed" << endl;
 	fin.close();
 	return 0;
}
