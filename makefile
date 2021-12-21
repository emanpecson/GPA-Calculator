# Make file for GPA Calculator.

OBJS	= main.o Semester.o Cumulative.o menuFunctions.o 
CC 		= g++
CCFLAGS = -Wall -Wextra -pedantic -std=c++11 -g 
DEPS	= Semester.h Cumulative.h menuFunctions.h

all: main

main: $(OBJS)
		$(CC) $(CCFLAGS) -o main $(OBJS)

main.o: main.cpp $(DEPS)
		$(CC) $(CCFLAGS) -c main.cpp

Semester.o: Semester.cpp $(DEPS)
		$(CC) $(CCFLAGS) -c Semester.cpp

Cumulative.o: Cumulative.cpp $(DEPS)
		$(CC) $(CCFLAGS) -c Cumulative.cpp

menuFunctions.o: menuFunctions.cpp $(DEPS)
		$(CC) $(CCFLAGS) -c menuFunctions.cpp

# cleaning
clean:
		rm $(OBJS) main