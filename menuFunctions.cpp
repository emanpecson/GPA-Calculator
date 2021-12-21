/*
	* Description:	Implementaiton file for the menu functions.
*/

#include "menuFunctions.h"

/*
	Outputs main menu options and indicates the current semester
	defined.
*/
void main_MenuPrompt(Cumulative &career) {
	cout << "----------------------------------------------\n";
	if(!career.isEmptyList())
		textEdit(red, "[Semester: " + career.mainSem->name + "]\n");
	cout << "[C] See course options.\n";
	cout << "[S] See semester options.\n";
	cout << "[G] See GPA calculation options.\n";
	cout << "[<] Switch to previous semester.\n";
	cout << "[>] Switch to next semester.\n";
	cout << "[Q] Quit program.\n";
	cout << "----------------------------------------------\n";
}

/*
	Outputs course menu options.
*/
void course_MenuPrompt() {
	cout
	<< "----------------------------------------------\n"
	<< "\t[N] New course.\n"
	<< "\t[D] Delete course.\n"
	<< "\t[P] Print courses.\n"
	<< "\t[B] Back.\n"
	<< "----------------------------------------------\n";
}

/*
	Outputs semester menu options.
*/
void semester_MenuPrompt() {
	cout
	<< "----------------------------------------------\n"
	<< "\t[N] New semester.\n"
	<< "\t[D] Delete semester.\n"
	<< "\t[P] Print semesters.\n"
	<< "\t[B] Back.\n"
	<< "----------------------------------------------\n";
}

/*
	Outputs course deleting menu options.
*/
void deleteCourse_MenuPrompt() {
	cout
	<< "----------------------------------------------\n"
	<< "\t\t[F] Delete first course.\n"
	<< "\t\t[L] Delete last course.\n"
	<< "\t\t[T] Delete course by title.\n"
	<< "\t\t[B] Return back.\n"
	<< "----------------------------------------------\n";
}

/*
	Outputs semester deleting menu options.
*/
void deleteSemester_MenuPrompt() {
	cout
	<< "----------------------------------------------\n"
	<< "\t\t[F] Delete first semester.\n"
	<< "\t\t[L] Delete last semester.\n"
	<< "\t\t[N] Delete semester by name.\n"
	<< "\t\t[B] Return back.\n"
	<< "----------------------------------------------\n";
}

/*
	Outputs GPA calculating menu options.
*/
void calc_MenuPrompt() {
	cout
	<< "----------------------------------------------\n"
	<< "\t[S] Calculate semester GPA.\n"
	<< "\t[C] Calculate cumulative GPA.\n"
	<< "\t[B] Back.\n"
	<< "----------------------------------------------\n";
}

/*
	Takes user input to select a main menu option.
*/
bool main_MenuSelect(Cumulative &career) {
	char input;
	cout << "Select: ";
	cin >> input;

	switch(toupper(input)) {
		case 'C':
			do {
				course_MenuPrompt();
			} while(course_MenuSelect(career));
			break;
		case 'S':
			do {
				semester_MenuPrompt();
			} while(semester_MenuSelect(career));
			break;
		case 'G':
			do {
				calc_MenuPrompt();
			} while(calc_MenuSelect(career));
			break;
		case '<':
			if(career.mainSem->prev != nullptr && career.getSemesterCount() > 1)
				career.mainSem = career.mainSem->prev;
			else
				textEdit(red, "ERROR:", " No available preceding semesters.\n");
			break;
		case '>':
			if(career.mainSem->next != nullptr && career.getSemesterCount() > 1)
				career.mainSem = career.mainSem->next;
			else
				textEdit(red, "ERROR:", " No available further semesters.\n");
			break;
		case 'Q':
			textEdit(red, "\nThank you for using the GPA calculator!\n");
			career.mainSem->destroyList();	// manually deallocate courses
			career.destroyList(); // manually deallocate semesters
			exit(0);	// exit program
		default:
			textEdit(red, "ERROR:", " Invalid input, please try again.\n");
	}
	return true;
}

/*
	Takes user input to select a course menu option.
*/
bool course_MenuSelect(Cumulative &career) {
	char input;
	cout << "Select: ";
	cin >> input;

	switch(toupper(input)) {
		case 'N':
			if(career.getSemesterCount() >= 1)
				career.mainSem->createCourse();
			else textEdit(red, "ERROR:", " Must define a semester first.\n");
			break;
		case 'D':
			if(!career.mainSem->isEmptyList())
				do {
					deleteCourse_MenuPrompt();
				} while(deleteCourse_MenuSelect(career));
			else
				textEdit(red, "ERROR:", " No courses defined yet.\n");
			break;
		case 'P':
			career.mainSem->printCourseList();
			break;
		case 'B':
			return false;
		default:
			textEdit(red, "ERROR:", " Invalid input, please try again.\n");
	}
	return true;
}

/*
	Takes in user input to select a semester menu option.
*/
bool semester_MenuSelect(Cumulative &career) {
	char input;
	cout << "Select: ";
	cin >> input;

	switch(toupper(input)) {
		case 'N':
			career.mainSem = career.createSemester();
			break;
		case 'D':
			if(!career.isEmptyList())
				do {
					deleteSemester_MenuPrompt();
				} while(deleteSemester_MenuSelect(career));
			else
				textEdit(red, "ERROR:", " No semesters defined yet.\n");
			break;
		case 'P':
			career.printSemesterList();
			break;
		case 'B':
			return false;	// exit menu
		default:
			textEdit(red, "ERROR:", " Invalid input, please try again.\n");
	}
	return true;	// all other cases will loop menu
}

/*
	Takes in user input to select a delete course menu option.
*/
bool deleteCourse_MenuSelect(Cumulative &career) {
	char input;
	cout << "Select: ";
	cin >> input;

	switch(toupper(input)) {
		case 'F':
			career.mainSem->removeFirstCourse();
			break;
		case 'L':
			career.mainSem->removeLastCourse();
			break;
		case 'T':
			career.mainSem->removeCourseByTitle();
			break;
		case 'B':
			return false;	// exit menu
		default:
			textEdit(red, "ERROR:", " Invalid input, please try again.\n");
			return true;	// loop menu
	}
	return false;	// all other cases will exit menu
}

/*
	Takes in user input to select a delete semester menu option.
*/
bool deleteSemester_MenuSelect(Cumulative &career) {
	char input;
	cout << "Select: ";
	cin >> input;

	switch(toupper(input)) {
		case 'F':
			career.removeFirstSemester();
			break;
		case 'L':
			career.removeLastSemester();
			break;
		case 'N':
			career.removeSemesterByName();
			break;
		case 'B':
			return false;	// exit menu
		default:
			textEdit(red, "ERROR:", " Invalid input, please try again.\n");
			return true;	// loop menu
	}
	return false;	// all other cases will exit menu
}

/*
	Takes in user input to select a GPA calculation menu option.
*/
bool calc_MenuSelect(Cumulative &career) {
	char input;
	cout << "Select: ";
	cin >> input;

	switch(toupper(input)) {
		case 'S':
			if(!career.mainSem->isEmptyList()) {
				textEdit(red, "Semester GPA: ");
				cout << career.mainSem->calculateGPA() << endl;
			}
			else
				textEdit(red, "ERROR:", " No courses defined yet.\n");
			break;
		case 'C':
			if(!career.isEmptyList()) {
				textEdit(red, "Cumulative GPA: ");
				cout << career.calculateGPA() << endl;
			}
			else
				textEdit(red, "ERROR:", " No semesters defined yet.\n");
			break;
		case 'B':
			return false;
		default:
			textEdit(red, "ERROR:", " Invalid input, please try again.\n");
			return true;
	}
	return false;
}
