/*
 * FSTreeTraversal.cpp
 *
 *  Modified on: April 13th, 2022
 *       Author: Ben Schmelkin and Ian Dhar
 *    
 *
 *  Implementation of treeTraversal and traverseDictionary Functions
 *  Used to print out all files and subdirectories under a given directory
 */


#include "FSTree.h"
#include "DirNode.h"
#include <iostream>
#include <istream>

void traverseDirectory(DirNode *directory, std::string path);
void treeTraversal(std::string directoryName);

using namespace std;

int main(int argc, char *argv[]){
    std::string fileName = argv[1];
    treeTraversal(fileName);
    return 0;
}

/*
 * name:      Tree Traversal
 * purpose:   Gets input directory from command line and calls helper function
 * arguments: istream input
 * returns:   none
 * effects:   none
 */

void treeTraversal(std::string directoryName){
    FSTree tree = FSTree(directoryName);
    traverseDirectory(tree.getRoot(), "");
}

/*
 * name:      Traverse Dictionary
 * purpose:   Recursively runs through directory to print all sub directories 
 *            and files
 * arguments: DirNode directory, string path
 * returns:   none
 * effects:   Updates path as the function moves deeper into the directory
 */

void traverseDirectory(DirNode *directory, std::string path){
    path += directory->getName() + "/";   
    if (directory->isEmpty()) {
        return;
    }
    else {
        if (directory->hasFiles())
        {
            for (int i = 0; i < directory->numFiles(); i++) {
                std::cout << path << directory->getFile(i) << std::endl;
            }
        }
        if (directory->hasSubDir())
        {
            for (int i = 0; i < directory->numSubDirs(); i++) {
                traverseDirectory(directory->getSubDir(i), path);
            }
        }
    }
}