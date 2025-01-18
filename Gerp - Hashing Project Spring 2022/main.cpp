/*
 *  main.cpp
 *  Ian Dhar and Ben Schmelkin
 *  4/26/2022
 *
 *  CS 15 Proj3 GERP
 *
 *  Main driver class that runs the simulation for the GERP program 
 *  Creates WordHash object and calls the traverse directory method
 *  on it to set up the Hash Table. Then a RunGerp object was created
 *  and the commandLoop was called on this object, allowing the user
 *  to enter commands and interact with the object.
 *  returns 0 at the end.
 */

#include <iostream>
#include <sstream>
#include "wordHash.h"
#include "runGerp.h"
#include "stringProcessing.h"
#include "FSTree.h"
#include "DirNode.h"
#include <string>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./gerp directory output_file" << std::endl;
        exit (EXIT_FAILURE);
    }
    std::string directory = argv[1];
    WordHash mainHash;
    FSTree tree(directory);
    mainHash.traverseDirectory(tree.getRoot(), "");
    RunGerp runCommandLoop;
    runCommandLoop.commandLoop(argv[2], &mainHash);
    return 0;
}