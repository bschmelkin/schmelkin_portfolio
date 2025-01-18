/*
 *  unit_test.cpp
 *  Ian Dhar and Ben Schmelkin
 *  4/26/2022
 *
 *  CS 15 Proj3 unit_test
 *
 *  Contains all tests for stripNonAlphaNum
 */


#include "stringProcessing.h"
#include <cassert>
#include <sstream>
#include <iostream>
#include <string>

void stringProcessingTest(){

    // string with 24 characters continuous
    std::string output1 = stripNonAlphaNum("---@@@@####ABcDeFG---+++");
    // string with 24 characters non-continuous
    std::string output2 = stripNonAlphaNum("---@@@@####ABc--DeFG-+++");
    // test with 11 characters no leading and numbers
    std::string output3 = stripNonAlphaNum("123Abcde--+");
    // test with 11 characters no trailing and numbers
    std::string output4 = stripNonAlphaNum("-%^123Abcde");

    assert(output1 == "ABcDeFG");
    assert(output2 == "ABc--DeFG");
    assert(output3 == "123Abcde");
    assert(output4 == "123Abcde");
}

/*
 * stripNonAlphaNum test 1
 * tests functionality of the method for strings where there are
 * non-alphanumeric characters on both ends
 */
void stripNonALphaNum_test_1() {
    std::string input = "!@#$%^abc!@#$%^";
    assert(stripNonAlphaNum(input) == "abc");
}
/*
 * stripNonAlphaNum test 2
 * tests functionality of the method for strings where there are
 * non-alphanumeric characters at the front
 */
void stripNonALphaNum_test_2() {
    std::string input = "!@#$%^abc978";
    assert(stripNonAlphaNum(input) == "abc978");
}
/*
 * stripNonAlphaNum test 3
 * tests functionality of the method for strings where there are
 * non-alphanumeric characters at the back
 */
void stripNonALphaNum_test_3() {
    std::string input = "abc978!@#$%^";
    assert(stripNonAlphaNum(input) == "abc978");
}
/*
 * stripNonAlphaNum test 4
 * tests functionality of the method for strings where there are
 * non-alphanumeric characters around only numbers
 */
void stripNonALphaNum_test_4() {
    std::string input = "!@#$%^978!@#$%^";
    assert(stripNonAlphaNum(input) == "978");
}
/*
 * stripNonAlphaNum test 5
 * tests functionality of the method for strings where there are
 * non-alphanumeric characters around both numbers and chars
 */
void stripNonALphaNum_test_5() {
    std::string input = "!@#$%^978abc!@#$%^";
    assert(stripNonAlphaNum(input) == "978abc");
}
/*
 * stripNonAlphaNum test 6
 * tests functionality of the method for strings where there are
 * non-alphanumeric characters around one char
 */
void stripNonALphaNum_test_6() {
    std::string input = "!@#$%^a@#$%^";
    assert(stripNonAlphaNum(input) == "a");
}
/*
 * stripNonAlphaNum test 7
 * tests functionality of the method for strings where there are
 * non-alphanumeric characters around one number
 */
void stripNonALphaNum_test_7() {
    std::string input = "!@#$%^9@#$%^";
    assert(stripNonAlphaNum(input) == "9");
}
/*
 * stripNonAlphaNum test 8
 * tests functionality of the method for strings where there are
 * non-alphanumeric characters around alphanumerics with hyphen
 */
void stripNonALphaNum_test_8() {
    std::string input = "!@#$%^abc-978@#$%^";
    assert(stripNonAlphaNum(input) == "abc-978");
}