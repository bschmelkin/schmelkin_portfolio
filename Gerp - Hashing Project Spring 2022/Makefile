
### Authors:  Ben Schmelkin & Ian Dhar
### Makefile for project 3 GERP

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

MAKEFLAGS += -L 

gerp: main.o runGerp.o wordHash.o FSTree.o DirNode.o stringProcessing.o
	$(CXX) -o gerp $^

runGerp.o: runGerp.cpp runGerp.h
	$(CXX) $(CXXFLAGS) -c runGerp.cpp

wordHash.o: wordHash.cpp wordHash.h
	$(CXX) $(CXXFLAGS) -c wordHash.cpp

main.o: main.cpp wordHash.h runGerp.h
	$(CXX) $(CXXFLAGS) -c main.cpp

FSTreeTraversal.o: FSTreeTraversal.cpp
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp

stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp

unit_test: unit_test_driver.o stringProcessing.o
	$(CXX) $(CXXFLAGS) $^

provide:
	provide comp15 proj3_gerp README Makefile main.cpp wordHash.cpp \ 
	        wordHash.h runGerp.cpp runGerp.h stringProcessing.cpp   \ 
			stringProcessing.h unit_tests.h FSTreeTraversal.cpp \ 
			commands1.txt sortedrefmedout.txt sortedourmedout.txt \
			commands2.txt commands3.txt 
	