/*
 *  runGerp.cpp
 *  Ian Dhar and Ben Schmelkin
 *  4/26/2022
 *
 *  CS 15 Proj3 GERP
 *
 *  Implementation for a wordHash Class. 
 *  Provides functionality behind the intentions of the header class
 *  Capable of creating a runGerp object and provides functions to
 *  operate on this object. This file provides our commandLoop, enabling
 *  user interaction and performs the resulting tasks of user input
 *
 */

#include <iostream>
#include <sstream>
#include "wordHash.h"
#include "stringProcessing.h"
#include "runGerp.h"
#include <fstream>
#include <string>

using namespace std;

/*
 * name:      Run Gerp Constructor
 * purpose:   Initializes Run Gerp
 * arguments: none
 * returns:   none
 * effects:   none
 */
RunGerp::RunGerp(){
}
/*
 * name:      Run Gerp Destructor
 * purpose:   Recycles all memory associated with runGerp
 * arguments: none
 * returns:   none
 * effects:   recycles all memory and clears lists
 */
RunGerp::~RunGerp(){
}

/*
 * name:      Command Loop
 * purpose:   process user inputs and manage simulation
 * arguments: string outputFile (name) and WordHash *mainHash
 * returns:   none
 * effects:   allows user to interact with simulation and execute commands.
 *            Carries out commands and calls helper functions to do so when
 *            necessary.
 */
void RunGerp::commandLoop(std::string outputFile, WordHash *mainHash){
    std::string command, key, caseSensitive;
    bool insens = false;
    cout << "Query? ";
    cin >> command;
    while(!cin.eof() and command != "@q" and command != "@quit")
    {
        if(command == "@f"){
            cin >> command;
            outputFile = command;
        }
        else{
            if(command == "@i" or command == "@insensitive"){
                cin >> command;
                insens = true;
            }
            caseSensitive = stripNonAlphaNum(command);
            key = mainHash->allLowerCase(caseSensitive);
            wordSearch(key, caseSensitive, insens, outputFile, mainHash);
            
        }
        insens = false;
        cout << "Query? ";
        cin >> command;
    }
    std::cout << "Goodbye! Thank you and have a nice day." << endl;
}
/*
 * name:      Word Search
 * purpose:   finds queried word and outputs the pathway, location, 
 *            and line to the outputFile
 * arguments: string key of word, string case sensitive version of word, 
 *            bool of if query is insensitive or not,
 *            string outputFile (name) and WordHash *mainHash
 * returns:   none
 * effects:   outputs the result of word queries from user input
 */
void RunGerp::wordSearch(string key, string caseSens, bool insen,
                         string outputFile, WordHash *mainHash){
    int index = mainHash->hashFunction(key, mainHash->mainHashSize());
    std::ofstream outstream;
    outstream.open(outputFile, std::fstream::app);
    if (!outstream.is_open()){ // check if can open correctly
        std::cerr << "Error: could not open file" << outputFile;
        exit (EXIT_FAILURE);
    }
    if (insen){
        if (mainHash->findCorrectWordList(key, index).key == "WORD NOT FOUND")
            outstream << caseSens << " Not Found." << endl;
            
        else{
            WordList *result = &mainHash->findCorrectWordList(key, index);
            for (std::list<Word>::iterator it = result->wordList.begin(); 
                                        it != result->wordList.end(); it++){
                mainHash->printPathways(*it, outputFile);
            }
        }
    }
    else{
        if (mainHash->findCorrectWord(caseSens, 
                    &mainHash->findCorrectWordList(key, index)).wordWithCaps 
                                                        == "WORD NOT FOUND")
            outstream << caseSens << " Not Found. Try with @insensitive or @i."
                      << endl;
        else{
            Word result = mainHash->findCorrectWord(caseSens, 
                    &mainHash->findCorrectWordList(key, index));
            mainHash->printPathways(result, outputFile);
        }
    }
    outstream.close();
}
