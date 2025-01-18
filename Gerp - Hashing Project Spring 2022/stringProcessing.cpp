/*
 * stringProcessing.cpp
 *
 *  Modified on: April 13th, 2022
 *       Author: Ben Schmelkin and Ian Dhar
 *    
 *
 *  Implementation of stripAlphaNum function
 * 
 *  
 */

#include "stringProcessing.h"
#include <iostream>

using namespace std;


std::string stripNonAlphaNum(std::string inputString){
    int front = 0;
    int back = inputString.length() - 1;
    while(!isalnum(inputString[front]) and front <= back) {
        front++;
    }
    while(!isalnum(inputString[back]) and back >= front) {
        back--;
    }
    if(front == back) return "";
    return inputString.substr(front, back - front + 1);
}