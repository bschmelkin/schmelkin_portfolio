/*
 *  runGerp.h
 *  Ian Dhar
 *  4/26/2022
 *  
 *  CS 15 Proj3 GERP
 *  
 *  Interface for a runGerp Class. Includes all
 *  methods and variables that will be implemented in the 
 *  runGerp.cpp file
 */
#ifndef RUN_GERP_H
#define RUN_GERP_H

#include <vector>
#include <list>
#include <string>

class RunGerp{
public:
    RunGerp();
    ~RunGerp();
    void commandLoop(std::string outputFile, WordHash *mainHash);

private:
    WordHash allWordsList;
    void wordSearch(std::string key, std::string caseSens, 
                    bool insen, std::string outputFile, WordHash *mainHash);

};
#endif
