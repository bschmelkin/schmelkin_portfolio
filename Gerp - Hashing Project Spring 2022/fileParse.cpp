#include "fileParse.h"
#include "wordHash.h"
/*
fileParse::fileParse(wordHash wHash, std::string directory) {
    filepath = "";
    FSTree fileTree(directory)
    root = fileTree.getRoot();
    hash = wHash;
}

fileParse::~fileParse() {

}
*/

void fileParse::traverseDirectory(DirNode *directory, string path)
{
    path += directory->getName() + "/";   
    if (directory->isEmpty()) {
        return;
    }
    else {
        if (directory->hasFiles())
        {
            getFiles(directory, path);
        }
        if (directory->hasSubDir())
        {
            for(int i = 0; i < directory->numSubDirs(); i++) {
                traverseDirectory(directory->getSubDir(i), path);
            }
        }
    }
}

void fileParse::getFiles(DirNode *node, std::string path){
    int numFiles = node->numFiles();
    std::string fileName;
    std::string curPath;
    for (int i = 0; i < numFiles; i++) {
        fileName = node->getFile(i);
        curPath = path + fileName;
        
        ifstream input;
        input.open(curPath);
        if (!input.is_open()){ // check if can open correctly
            cerr << "Error: could not open file" << input;
            exit (EXIT_FAILURE);
        }
        int lineNum = 0;
        std::string word = "";
        std::string fullLine;
        while (!input.eof()) {
            getline(input, fullLine);
            std::string pathLine = curPath + ":" + to_string(lineNum) + ": " + fullLine;
            int indexOfPath = allWordsList.addPathway(pathLine); // use this when making new word for correct slot in pathways array
            
            vector<std::string> lineWords = separateWords(fullLine);
            for (int j = 0; j < lineWords.size(); j++){
                allWordsList.addWord(lineWords[j], indexOfPath); // requires hash function to be working -> impliment later
            }
            lineWords.~vector();
            lineNum++;
        }
        input.close();
    }   
}

std::vector<std::string> fileParse::separateWords(string toSeparate){
    std::vector<std::string> listOfSeparatedWords;
    istringstream ss(toSeparate);
  
    std::string word;

    while (ss >> word) 
    {
        listOfSeparatedWords.push_back(word);
    }
    return listOfSeparatedWords;
}