/*
 *  wordHash.cpp
 *  Ian Dhar and Ben Schmelkin
 *  4/26/2022
 *
 *  CS 15 Proj3 GERP
 *
 *  Implementation for a wordHash Class. 
 *  Provides functionality behind the intentions of the header class
 *  Capable of creating a wordHash object and provides functions to
 *  operate on this object
 *
 */
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <ctype.h>
#include <stdio.h>
#include "wordHash.h" 
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "stringProcessing.h"

using namespace std;

/*
 * name:      Word Hash Constructor
 * purpose:   Initializes allWordsList
 * arguments: none
 * returns:   none
 * effects:   Adds empty collisions word list to each index.
 *            Starts with size 83 but will be expanded later
 */
WordHash::WordHash(){
    for (size_t i = 0; i < 1001; i++)// check 83 number for initial size
	{
        CollisionsWordList newCWL;
		allWordsList.push_back(newCWL);
	}
}
/*
 * name:      Word Hash Destructor
 * purpose:   Recycles all memory associated with allWordsList/all sub lists
 * arguments: none
 * returns:   none
 * effects:   recycles all memory and clears lists
 */
WordHash::~WordHash(){
    for (size_t i = 0; i < allWordsList.size(); i++){
        CollisionsWordList *cwl = &allWordsList[i];
        for (std::list<WordList>::iterator it = cwl->collisionsWordList.begin()
                                    ;it != cwl->collisionsWordList.end(); it++)
        {
            WordList *cn = &*it;
            cn->wordList.clear();  
        }
        cwl->collisionsWordList.clear();
    }
    allWordsList.clear();
    pathList.clear();
}
/*
 * name:      Find Correct Word List
 * purpose:   Loops through a collisions word list to find the right word list
 * arguments: string key, int index (index in all words list)
 * returns:   WordList
 * effects:   Returns empty list with key "WORD NOT FOUND" if no key is matched 
 */
WordList &WordHash::findCorrectWordList(std::string key, int index){
    CollisionsWordList *toLoop = &allWordsList[index];
    for (std::list<WordList>::iterator it = toLoop->collisionsWordList.begin()
                                ; it != toLoop->collisionsWordList.end(); it++)
    {
        if (it->key == key){
            return *it;
        }
    }
    WordList *notFound = new WordList;
    notFound->key = "WORD NOT FOUND";
    return *notFound;
}
/*
 * name:      Find Correct Word
 * purpose:   Loops through a word list to find the right word
 * arguments: string key, WordList list
 * returns:   Word
 * effects:   Returns empty word with key "WORD NOT FOUND" if no key is matched
 */

Word &WordHash::findCorrectWord(std::string caseSens, WordList *list){
    for (std::list<Word>::iterator it = list->wordList.begin(); 
                                   it != list->wordList.end(); it++)
    {
        if (it->wordWithCaps == caseSens){
            return *it;
        }
    }
    Word *notFound = new Word;
    notFound->wordWithCaps = "WORD NOT FOUND";
    return *notFound;
}
/*
 * name:      Main Hash Size
 * purpose:   Returns size of allWordsList 
 * arguments: none
 * returns:   int size of allWordsList
 * effects:   none
 */
int WordHash::mainHashSize()
{
    return allWordsList.size();
}
/*
 * name:      Print Pathways
 * purpose:   Prints all pathways associated with a word 
 * arguments: Word toBePrinted, string outputFile
 * returns:   none
 * effects:   Prints pathways to file named outputFile
 */
void WordHash::printPathways(Word toBePrinted, std::string outputFile){
    std::ofstream outstream;
    outstream.open(outputFile, std::fstream::app);
    if (!outstream.is_open()){ // check if can open correctly
        std::cerr << "Error: could not open file" << outputFile;
        exit (EXIT_FAILURE);
    }
    for (size_t i = 0; i < toBePrinted.pathwayIndex.size(); i++){
        outstream << pathList[toBePrinted.pathwayIndex[i]].pathway << endl;
    }
    outstream.close();
}
/*
 * name:      Add Pathways
 * purpose:   Adds pathway node to pathway list 
 * arguments: string inputPathway
 * returns:   int index (index of newly added pathway)
 * effects:   Adds pathway node to end of list
 */
int WordHash::addPathway(std::string inputPathway){
    PathNode newNode;
    newNode.pathway = inputPathway;
    pathList.push_back(newNode); // why no push back?
    return pathList.size()-1;
    
}
/*
 * name:      Add Word
 * purpose:   Adds word to correct index in allWordsList
 * arguments: string caseSens, int printIndex
 * returns:   none
 * effects:   Creates new WordList if the key is not found anywhere
 *            If the word shows up more than once in a line it is not added
 */
void WordHash::addWord(std::string caseSens, int printIndex){
    std::string key = allLowerCase(caseSens);
    size_t hashIndex = hashFunction(key, allWordsList.size());
    CollisionsWordList *collisions = &allWordsList[hashIndex];
    for (std::list<WordList>::iterator it = 
                collisions->collisionsWordList.begin(); 
                it != collisions->collisionsWordList.end(); it++)
    {
        if (it->key == key){
            WordList *wList = &*it;
            addWordHelper(wList, caseSens, printIndex);
            return;
        }
    }
    WordList toAdd;
    toAdd.key = key;
    Word addedWord;
    addedWord.wordWithCaps = caseSens;
    addedWord.pathwayIndex.push_back(printIndex);
    toAdd.wordList.push_front(addedWord);
    collisions->collisionsWordList.push_front(toAdd);
    if(collisions->collisionsWordList.size() > 4){
        expand();
    }
}
/*
 * name:      Add Word Helper
 * purpose:   Aids the process of adding words,
 * arguments: WordList *wList, string caseSens, int printIndex
 * returns:   none
 * effects:   sets up pathway pointers and creates new pathways if necessary
 */
void WordHash::addWordHelper(WordList *wList, std::string caseSens,
                                                    int printIndex){
    for (std::list<Word>::iterator it = wList->wordList.begin();
                                   it != wList->wordList.end(); it++){
        if (it->wordWithCaps == caseSens){
            int index = it->pathwayIndex.size();
            if(it->pathwayIndex[index-1] == printIndex) return;
            else{
                it->pathwayIndex.push_back(printIndex);
                return;
            }
        }
    }
    Word addedWord;
    addedWord.wordWithCaps = caseSens;
    addedWord.pathwayIndex.push_back(printIndex);
    wList->wordList.push_back(addedWord);
}
/*
 * name:      Hash Function
 * purpose:   Creates hash baseed on key
 * arguments: string wordToHash, int tableSize
 * returns:   int hashIndex
 * effects:   none
 */
int WordHash::hashFunction(std::string wordToHash, int tableSize){
    string key = allLowerCase(wordToHash);
    int hashIndex = wordHash(key) % tableSize;
    return hashIndex;
}
/*
 * name:      Expand
 * purpose:   Expands allWordsList when there are too many collisions
 * arguments: none
 * returns:   none
 * effects:   Recycles old list by deconstructing each collisions word list
 */
void WordHash::expand(){
    size_t sizeExpanded = allWordsList.size() * 2 + 1;
    std::vector<CollisionsWordList> expanded;
    // // init empty collisions list at each index  
    // for (size_t i = 0; i < sizeExpanded; i++)
	// {
    //     CollisionsWordList newCWL;
	// 	expanded.push_back(newCWL);
	// }
    expanded.resize(sizeExpanded);
    for (size_t i = 0; i < allWordsList.size(); i++){
        CollisionsWordList *cwl = &allWordsList[i];
        for (std::list<WordList>::iterator it = cwl->collisionsWordList.begin()
                                ; it != cwl->collisionsWordList.end(); it++)
        {
            WordList cn = *it;
            CollisionsWordList *addTo = 
                               &expanded[hashFunction(cn.key, sizeExpanded)];
            addTo->collisionsWordList.push_front(cn);  
            it->wordList.clear();
        }
        cwl->collisionsWordList.clear();
    }
    //allWordsList.resize(sizeExpanded);
    // allWordsList.clear();
    allWordsList.swap(expanded); // check copy constructor
}
/*
 * name:      Change Collisions List
 * purpose:   Helper function to expand to remove each WordList from each
 *             collisionsWordList
 * arguments: CollisionsWordList *toRemoveList, CollisionsWordList 
 *            *expanded_cwl
 * returns:   none
 * effects:   Moves each WordList in toRemoveList to a new expanded_cwl to be 
 *            added to the expanded allWordsList
 */
void WordHash::changeCollisionLists(CollisionsWordList *toRemoveList, 
                                    CollisionsWordList *expanded_cwl)
{
	WordList *cn = &toRemoveList->collisionsWordList.front();
    toRemoveList->collisionsWordList.pop_front();
    expanded_cwl->collisionsWordList.push_back(*cn);
}
/*
 * name:      All Lower Case
 * purpose:   Turns a word with potentially capital letter to all lower case
 * arguments: string word
 * returns:   string (all lower case) word
 * effects:   Uses tolower function to make each letter lower case
 */
std::string WordHash::allLowerCase(std::string word)
{
	for (size_t i = 0; i < word.length(); i++)
	{
		word[i] = tolower(word[i]);
    }
	return word;
    
}
/*
 * name:      Traverse Directory
 * purpose:   Navigates inputed directory and begins creating pathways
 * arguments: DirNode *directory, string path
 * returns:   none
 * effects:   sets up pathways for words in the inputed directory and
 *            calls function to set up hashtable
 */
void WordHash::traverseDirectory(DirNode *directory, string path)
{
    path += directory->getName() + "/";   
    if (directory->isEmpty()){
        return;
    }
    else{
        if (directory->hasFiles())
        {
            getFiles(directory, path);
        }
        if (directory->hasSubDir())
        {
            for(int i = 0; i < directory->numSubDirs(); i++){
                traverseDirectory(directory->getSubDir(i), path);
            }
        }
    }
}
/*
 * name:      Get Files
 * purpose:   retrieves the Files from inputed directories and subdirectories
 *            and adds words in files to the hash table
 * arguments: DirNode *node, string path
 * returns:   none
 * effects:   adds words of files to hashtables with their pathway index
 */
void WordHash::getFiles(DirNode *node, std::string path){
    int numFiles = node->numFiles();
    std::string fileName, curPath;
    for (int i = 0; i < numFiles; i++){
        fileName = node->getFile(i);
        curPath = path + fileName;
        ifstream input;
        input.open(curPath);
        if (!input.is_open()){ // check if can open correctly
            cerr << "Error: could not open file" << fileName;
            exit (EXIT_FAILURE);
        }
        int lineNum = 1;
        std::string word = "";
        std::string fullLine;
        vector<std::string> lineWords;
        while (!input.eof()){
            getline(input, fullLine);
            std::string pathLine = curPath + ":" + to_string(lineNum) + ": " 
                                                                + fullLine;
            int indexOfPath = addPathway(pathLine);
            lineWords = seperateWords(fullLine);
            for (size_t j = 0; j < lineWords.size(); j++)
                if(!(stripNonAlphaNum(lineWords[j]) == ""))
                    addWord(stripNonAlphaNum(lineWords[j]), indexOfPath);
            lineWords.clear();
            lineNum++;
        }
        input.close();
    }
}
/*
 * name:      Seperate Words
 * purpose:   Seperates words in a string into a vector
 * arguments: string toSeperate
 * returns:   vector of strings
 * effects:   creates and returns a vector of each word in an inputed string
 */
std::vector<std::string> WordHash::seperateWords(string toSeparate){
    std::vector<std::string> listOfSeparatedWords;
    istringstream ss(toSeparate);
    std::string word;
    while (ss >> word) 
    {
        listOfSeparatedWords.push_back(word);
    }
    return listOfSeparatedWords;
}