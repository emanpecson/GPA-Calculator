/*
	* Description:	Header file containing the Semester class type
					and the Course struct type.
*/

#ifndef SEMESTER_H
#define SEMESTER_H

#include <iostream>
#include <iomanip>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

/*
	Course struct is structured as a node to a linked list. A course
	contains data variables and a link to a subsequent course.
*/
struct Course {
	string title;
	string grade;
	float gradeWeight;
	unsigned int credits;
	Course *link;	// link to next course
};

/*
	Semester class is structured as a linked list, consisting of courses
	as nodes. Additionally, semester will act as a node to a doubly
	linked list which encapsulates all of the semesters together.
*/
class Semester {
private:
	float GPA;
	Course *head, *tail;
public:
	string name;
	Semester *next;		// link to next semester
	Semester *prev;		// link to previous semester
	Semester();
	~Semester();
	float calculateGPA();
	void printCourseList() const;
	void createCourse();
	void removeCourseByTitle();
	void removeFirstCourse();
	void removeLastCourse();
	void removeThisCourse(Course *);
	void promptCourseTitle(Course *);
	void promptCourseGrade(Course *);
	void promptCourseCredits(Course *);
	bool isValidGrade(Course *);
	bool isEmptyList() const;
	void destroyList();
};

void textEdit(const char *, string, string = "");
static const char *red = "\033[0;31m";	// variable for red text

#endif
