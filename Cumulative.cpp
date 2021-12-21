/*
	* Description:	Implementation file for the Cumulative class.
*/

#include "Cumulative.h"

/*
	Class constructor which initializes the
	private members to a neutral value.
*/
Cumulative::Cumulative() {
	GPA = 0.0;
	semesterCount = 0;
	head = nullptr;
	tail = nullptr;
}

/*
	Class destructor which deallocates all of the
	semesters.
*/
Cumulative::~Cumulative() {
	destroyList();
}

/*
	Iterates through the list and deallocates
	each of the created semesters.
*/
void Cumulative::destroyList() {
	Semester *removeSem = head, *thisSem = head;

	if(!isEmptyList())
		while(thisSem != nullptr) {
			removeSem = thisSem;
			thisSem = thisSem->next;
			delete removeSem;
		}
}

/*
	Outputs the list of semesters for the user to see.
*/
void Cumulative::printSemesterList() const {
	Semester *thisSem = head;

	if(!isEmptyList()) {
		textEdit(red, "Name                GPA\n");
		while(thisSem != nullptr) {
			cout << std::setprecision(2) << std::fixed;
			cout << std::setw(20) << std::left << thisSem->name;
			cout << std::right << thisSem->calculateGPA() << endl;

			thisSem = thisSem->next;
		}
	}
	else textEdit(red, "ERROR:", " No semesters defined yet.\n");
}

/*
	Indicates whether there are no semesters in the cumulative
	linked list. Returns true when empty, false otherwise.
*/
bool Cumulative::isEmptyList() const {
	return (head == nullptr);
}

/*
	Calculates the cumulative GPA based on the
	average GPA amonst all semesters.
*/
float Cumulative::calculateGPA() {
	Semester *thisSem = head;
	float accumulatedGPA = 0.0;

	if(!thisSem->isEmptyList()) {
		while(thisSem != nullptr) {
			accumulatedGPA += thisSem->calculateGPA();
			thisSem = thisSem->next;
		}
	}
	GPA = accumulatedGPA / semesterCount;
	return GPA;
}

/*
	Dynamically allocates a new semester. The name variable for
	this semester is prompted and defined by the user. Then
	the semester is placed at the end of the list.
*/
Semester * Cumulative::createSemester() {
	Semester *newSem = new Semester;
	newSem->next = nullptr;
	newSem->prev = nullptr;

	promptSemesterName(newSem);

	if(head == nullptr) {
		head = newSem;
		tail = newSem;
	}
	else {
		tail->next = newSem;
		newSem->prev = tail;
		tail = newSem;
	}
	cout << "----------------------------------------------\n";\
	textEdit(red, "[Semester successfully created]\n");

	semesterCount++;
	return newSem;
}

/*
	Deallocates a semester by prompting the user for the semester
	name. This name is checked at a 3-case basis to determine
	how to appropriately destroy the semester without disrupting
	the linked list structure.
*/
void Cumulative::removeSemesterByName() {
	Semester *thisSem = head;
	string name;

	if(!isEmptyList()) {
		cout << "----------------------------------------------\n";
		textEdit(red, "[Enter name]\n");
		cout << "Enter: ";
		getline(cin >> std::ws, name);

		// Iterate through list until out of bounds or semester is found.
		while(thisSem != nullptr && thisSem->name != name)
			thisSem = thisSem->next;
		
		// If the course was found, delete it at that position. Otherwise, notify
		// user that the course does not exist.
		if(thisSem != nullptr) {
			// Case 1: Removal when semester is at the head of the list.
			if(thisSem == head) removeFirstSemester();
			// Case 2: Removal when semester is at the tail of the list.
			else if(thisSem == tail) removeLastSemester();
			// Case 3: Removal within the middle of the list.
			else removeThisSemester(thisSem);
		}
		else textEdit(red, "ERROR:", " That semester does not exist.\n");
	}
	else textEdit(red, "ERROR:", " No semesters defined yet.\n");
}

/*
	Deallocates the first semester from the cumulative linked list.
*/
void Cumulative::removeFirstSemester() {
	if(head->next != nullptr) {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	}
	else {
		head->prev = nullptr;
		tail->next = nullptr;
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	semesterCount--;
	cout << "----------------------------------------------\n";
	textEdit(red, "[Semester successfully deleted]\n");
}

/*
	Deallocates the last semester from the cumulative linked list.
*/
void Cumulative::removeLastSemester() {
	if(head->next != nullptr) {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
	}
	else {
		head->prev = nullptr;
		tail->next = nullptr;
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	semesterCount--;
	cout << "----------------------------------------------\n";
	textEdit(red, "[Semester successfully deleted]\n");
}

/*
	Deallocates a semester from the cumulative linked list as a
	passed argument.
*/
void Cumulative::removeThisSemester(Semester *thisSem) {
	Semester *prevSem;
	Semester *nextSem;

	if(head->next != nullptr) {
		prevSem = thisSem->prev;
		nextSem = thisSem->next;

		prevSem->next = nextSem;
		nextSem->prev = prevSem;
		delete thisSem;
	}
	else {
		head->prev = nullptr;
		tail->next = nullptr;
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	semesterCount--;
	cout << "----------------------------------------------\n";
	textEdit(red, "[Semester successfully deleted]\n");
}

/*
	Prompts the user to input a semester name, then stores
	this value.
*/
void Cumulative::promptSemesterName(Semester *newSem) const {
	cout << "----------------------------------------------\n";
	textEdit(red, "[Please name this semester]\n");
	cout << "Enter: ";
	getline(cin >> std::ws, newSem->name);
}

/*
	Accessor which returns the private semesterCount variable
	from the class.
*/
unsigned int Cumulative::getSemesterCount() const {
	return semesterCount;
}
