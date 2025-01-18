


#ifndef FILE_PARSE_h
#define FILE_PARSE_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "FSTree.h"
#include "DirNode.h"
#include "wordHash.h"

using namespace std;

class fileParse{

public:

    fileParse(WordHash hash, std::string directory);

    
    void openFiles(std::string name);
    void readFiles(istream &inputfile, std::string path);
    

private:
void getFiles(DirNode *node, std::string path);
    std::vector<std::string> separateWords(string toSeparate);
    void traverseDirectory(DirNode *directory, std::string path);


    // string filepath;
    // DirNode *root;
    // wordHash hash;

};
#endif
