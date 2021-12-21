/*
	* Description:	Header file for the GPA calculator menu functions.
*/

#ifndef MENUFUNCTIONS_H
#define MENUFUNCTIONS_H

#include "Cumulative.h"

void main_MenuPrompt(Cumulative &);
bool main_MenuSelect(Cumulative &);
void course_MenuPrompt();
bool course_MenuSelect(Cumulative &);
void semester_MenuPrompt();
bool semester_MenuSelect(Cumulative &);
void calc_MenuPrompt();
bool calc_MenuSelect(Cumulative &);
void deleteCourse_MenuPrompt();
bool deleteCourse_MenuSelect(Cumulative &);
void deleteSemester_MenuPrompt();
bool deleteSemester_MenuSelect(Cumulative &);

#endif
