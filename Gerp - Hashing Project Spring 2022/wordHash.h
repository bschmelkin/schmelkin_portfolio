/*
 *  wordHash.h
 *  Ian Dhar
 *  4/26/2022
 *  
 *  CS 15 Proj3 GERP
 *  
 *  Interface for a wordHash Class. Includes all
 *  methods and variables that will be implemented in the 
 *  wordHash.cpp file
 */

#ifndef WORD_HASH_H
#define WORD_HASH_H

#include <vector>
#include <list>
#include <string>
#include "FSTree.h"
#include "DirNode.h"


struct Word{ 
    std::string wordWithCaps;
    std::vector<int> pathwayIndex;
};

struct WordList{
    std::string key; // all lower case version of word
    std::list<Word> wordList; // list of words
};

struct CollisionsWordList{
    std::list<WordList> collisionsWordList; // list of word lists
};

struct PathNode{
    std::string pathway; // string with pathway, line number, and actual string
};

class WordHash{
public:
    WordHash();
    ~WordHash();
    
    WordList &findCorrectWordList(std::string key, int printIndex); 
    Word &findCorrectWord(std::string caseSens, WordList *list);
    void printPathways(Word toBePrinted, std::string outputFile);
    int addPathway(std::string inputPathway);
    void addWord(std::string word, int pathIndex); 
    void traverseDirectory(DirNode *directory, std::string path);
    std::string allLowerCase(std::string word);
    int mainHashSize();
    int hashFunction(std::string wordToHash, int tableSize);


private:
    std::vector<PathNode> pathList;
    std::vector<CollisionsWordList> allWordsList;
    std::hash<std::string> wordHash;
    
    void changeCollisionLists(CollisionsWordList *toRemoveList,
                              CollisionsWordList *expanded_cwl);
    void expand();
    void getFiles(DirNode *node, std::string path);
    std::vector<std::string> seperateWords(std::string toSeperate);
    void addWordHelper(WordList *wList, std::string caseSens, int printIndex);
};
#endif
