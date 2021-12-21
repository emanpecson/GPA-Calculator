/*
	* Description:	Header file containing the Cumulative class type.
*/

#ifndef CUMULATIVE_H
#define CUMULATIVE_H

#include <iostream>
#include "Semester.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

/*
	Cumulative class is structured as a doubly linked list, consisting of
	semesters as nodes. Each semester contains data variables and a link
	to the next semester and preceding semester.
*/
class Cumulative {
private:
	float GPA;
	Semester *head, *tail;
	unsigned int semesterCount;
public:
	Semester *mainSem;
	Cumulative();
	~Cumulative();
	float calculateGPA();
	void printSemesterList() const;
	Semester * createSemester();
	void removeSemesterByName();
	void removeFirstSemester();
	void removeLastSemester();
	void removeThisSemester(Semester *);
	void promptSemesterName(Semester *) const;
	bool isEmptyList() const;
	void destroyList();
	unsigned int getSemesterCount() const;
};

#endif
