/*
	* Description:	Implementation file for Semester class.
*/

#include "Semester.h"

/*
	Class constructor which initializes the class
	member variables to a neutral value.
*/
Semester::Semester() {
	GPA = 0.0;
	name = "N/A";
	head = nullptr;
	tail = nullptr;
}

/*
	Class destrucotr which deallocates all
	of the courses.
*/
Semester::~Semester() {
	destroyList();
}

/*
	Iterates through the list and deallocates
	each of the created courses.
*/
void Semester::destroyList() {
	Course *removeCourse, *thisCourse = head;

	if(!isEmptyList())
		while(thisCourse != nullptr) {
			removeCourse = thisCourse;
			thisCourse = thisCourse->link;
			delete removeCourse;
		}
}

/*
	Formula which calculates the semester GPA by accumulating
	all grade points and dividing it by accumulated credits
	taken. This GPA value is then returned as a float type.
*/
float Semester::calculateGPA() {
	Course *thisCourse = head;
	float gradePoints = 0.0;
	unsigned int accumulatedCredits = 0;

	while(thisCourse != nullptr) {
		gradePoints += (thisCourse->credits * thisCourse->gradeWeight);
		accumulatedCredits += thisCourse->credits;
		thisCourse = thisCourse->link;
	}
	GPA = gradePoints / accumulatedCredits;
	return GPA;
}

/*
	Dynamically allocates a new course. The data values for
	this course are prompted and defined by the user. Then
	the course is placed at the end of the list.
*/
void Semester::createCourse() {
	Course *newCourse = new Course;
	newCourse->link = nullptr;

	promptCourseTitle(newCourse);
	promptCourseGrade(newCourse);
	promptCourseCredits(newCourse);

	if(head == nullptr) {
		head = newCourse;
		tail = newCourse;
	}
	else {
		tail->link = newCourse;
		tail = newCourse;
	}
	cout << "----------------------------------------------\n";
	textEdit(red, "[Course successfully created]\n");
	textEdit(red, "Title               Grade");
	textEdit(red, "               Credits\n");
	cout << std::setprecision(2) << std::fixed;
	cout << std::setw(20) << std::left << newCourse->title;
	cout << std::setw(20) << std::left << newCourse->grade;
	cout << std::right << newCourse->credits << endl;
}

/*
	Deallocates a course by prompting the user for the course
	title. This title is checked at a 3-case basis to determine
	how to appropriately destroy the course without disrupting
	the linked list structure.
*/
void Semester::removeCourseByTitle() {
	Course *thisCourse = head;
	string title;

	if(!isEmptyList()) {
		cout << "----------------------------------------------\n";
		textEdit(red, "[Enter title]\n");
		cout << "Enter: ";
		getline(cin >> std::ws, title);

		// Iterate through list until out of bounds or course is found.
		while(thisCourse != nullptr && thisCourse->title != title)
			thisCourse = thisCourse->link;

		// If the course was found, delete it at that position. Otherwise, notify
		// user that the course does not exist.
		if(thisCourse != nullptr) {
			// Case 1: Removal when course is at the head of the course list.
			if(thisCourse == head) removeFirstCourse();
			// Case 2: Removal when course is at the tail of the course list.
			else if(thisCourse == tail) removeLastCourse();
			// Case 3: Removal within the middle of the course list.
			else removeThisCourse(thisCourse);
		}
		else textEdit(red, "ERROR:", " That course does not exist.\n");
	}
	else textEdit(red, "ERROR:", " No courses defined yet.\n");
}

/*
	Deallocates the first course from the semester.
*/
void Semester::removeFirstCourse() {
	Course *removeCourse = head;
	
	if(head->link != nullptr) {
		head = head->link;
		delete removeCourse;
	}
	else {
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	cout << "----------------------------------------------\n";
	textEdit(red, "[Course successfully deleted]\n");
}

/*
	Deallocates the last course from the semester.
*/
void Semester::removeLastCourse() {
	Course *removeCourse = tail, *prevCourse = head;

	if(head->link != nullptr) {
		while(prevCourse->link != tail)
			prevCourse = prevCourse->link;

		tail = prevCourse;
		delete removeCourse;
		tail->link = nullptr;
	}
	else {
		delete tail;
		tail = nullptr;
		head = nullptr;
	}
	cout << "----------------------------------------------\n";
	textEdit(red, "[Course successfully deleted]\n");
}

/*
	Deallocates a course from the semester as a passed argument.
*/
void Semester::removeThisCourse(Course *thisCourse) {
	Course *prevCourse = head;

	if(head->link != nullptr) {
		while(prevCourse->link != thisCourse)
			prevCourse = prevCourse->link;

		prevCourse->link = thisCourse->link;
		delete thisCourse;
	}
	else {
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	cout << "----------------------------------------------\n";
	textEdit(red, "[Course successfully deleted]\n");
}

/*
	Prompts the user to input a course title, then stores
	this value.
*/
void Semester::promptCourseTitle(Course *thisCourse) {
	cout << "----------------------------------------------\n";
	textEdit(red, "[Please enter course title]\n");
	cout << "Enter: ";
	getline(cin >> std::ws, thisCourse->title);
}

/*
	Prompt user for course grade. Store the input if it's valid,
	otherwise, loop until a valid value is input.
*/
void Semester::promptCourseGrade(Course *newCourse) {
	do {
		cout << "----------------------------------------------\n";
		textEdit(red, "[Please select a course grade]\n");
		textEdit(red, "A  A- B+ B  B- C+ C  C- D+ D  D- F\n");
		cout << "Enter: ";
		cin >> newCourse->grade;

		// In case the input is invalid, reset the input, notify user, 
		// and reprompt for a valid grade.
		if(!isValidGrade(newCourse)) {
			textEdit(red, "ERROR:", " Invalid grade entered. Try again.\n");
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while(!isValidGrade(newCourse));
}

/*
	Takes in a string argument to see if it's a valid grade.
	If valid, set its respective grade weight and return true.
	Otherwise, return false.
*/
bool Semester::isValidGrade(Course *newCourse) {
	if(newCourse->grade == "A") newCourse->gradeWeight = 4.0;
	else if(newCourse->grade == "A-") newCourse->gradeWeight = 3.7;
	else if(newCourse->grade == "B+") newCourse->gradeWeight = 3.3;
	else if(newCourse->grade == "B") newCourse->gradeWeight = 3.0;
	else if(newCourse->grade == "B-") newCourse->gradeWeight = 2.7;
	else if(newCourse->grade == "C+") newCourse->gradeWeight = 2.3;
	else if(newCourse->grade == "C") newCourse->gradeWeight = 2.0;
	else if(newCourse->grade == "C-") newCourse->gradeWeight = 1.7;
	else if(newCourse->grade == "D+") newCourse->gradeWeight = 1.3;
	else if(newCourse->grade == "D") newCourse->gradeWeight = 1.0;
	else if(newCourse->grade == "D-") newCourse->gradeWeight = 0.7;
	else if(newCourse->grade == "F") newCourse->gradeWeight = 0.0;
	else return false;
	return true;
}

/*
	Prompt user to input course credits, then stores this value.
*/
void Semester::promptCourseCredits(Course *newCourse) {
	do {
		cout << "----------------------------------------------\n";
		textEdit(red, "[Please enter course credits]\n");
		cout << "Enter: ";
		cin >> newCourse->credits;

		// In case the input is invalid, reset the input, notify user, 
		// and reprompt for valid credits.
		if(cin.fail() || newCourse->credits < 1 || newCourse->credits > 5) {
			textEdit(red, "ERROR:", " Please Enter credits between 1–5.\n");
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while(cin.fail() || newCourse->credits < 1 || newCourse->credits > 5);
}

/*
	Indicates whether the semester holds no courses. Thus,
	returns true when empty, returns false otherwise.
*/
bool Semester::isEmptyList() const {
	return (head == nullptr);
}

/*
	Outputs the course list for the user to see.
*/
void Semester::printCourseList() const {
	Course *thisCourse = head;

	if(!isEmptyList()) {
		textEdit(red, "Title               Grade");
		textEdit(red, "               Credits\n");

		while(thisCourse != nullptr) {
			cout << std::setprecision(2) << std::fixed
			<< std::setw(20) << std::left << thisCourse->title
			<< std::setw(20) << std::left << thisCourse->grade
			<< std::right << float(thisCourse->credits) << endl;

			thisCourse = thisCourse->link;
		}
	}
	else textEdit(red, "ERROR:", " No courses defined yet.\n");
}

/*
	Non-member function that applies an edit to a string. The first argument
	is the edit to apply, the second argument is the text to apply it too,
	the optional third argument is a following text which the edit doesn't
	get applied to.
*/
void textEdit(const char *edit, string str_edited, string str_default) {
	const char *reset = "\033[0m";
	cout << edit << str_edited << reset << str_default;
}
