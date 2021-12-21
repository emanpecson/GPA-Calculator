/*
	* Description:	Program that allows users to define their courses
					and semesters. The calculator then takes the input
					data and gives users the option to view their
					term GPA and cumulative GPA.
*/

#include <iomanip>
#include <iostream>
#include <cctype>
#include "Cumulative.h"
#include "menuFunctions.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
	cout << endl << "******************************"<< endl;
	textEdit(red, "Welcome to the GPA Calculator!\n");
	cout << "******************************" << endl << endl;

	// Declares Cumulative class type to represent one's entire
	// college GPA. This variable is a linked list that holds
	// the semesters that a user defines. éee semester then
	// holds the courses that a user defines.
	Cumulative career;
	career.mainSem = career.createSemester();

	do {
		main_MenuPrompt(career);
	} while(main_MenuSelect(career));
}
