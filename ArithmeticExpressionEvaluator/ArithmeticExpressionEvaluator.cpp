//  ArithmeticExpressionEvaluator.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*  Date: 3/16/2021
    
    Programmer: Alex Bishop
    
    Purpose: Interview Technical Question
    
    Prompt: Write a program to parse and evaluate arithmetic expressions.
            Your problem should support addition and multiplication at a minimum.
            You input will be text similar to the following:

            1 + 1

            (3 + 4) * 6

            (1 * 4) + (5 * 2)

            Your output should be the computed value of the expression.
            Write your program in an Object Oriented fashion and be prepared to show us your code and discuss your solution. Do not use the "Shunting Yard" algorithm.
*/
#include <iostream>
#include <string>
#include "Parser.h"
#include "Lexer.h"
using namespace std;

int main()
{
    // Declare Variables
    string userInput;   // Holds the user's inputed expression

    // Greet the user and get their input
    cout << "Welcome! Please input a valid arithmetic expression to evaluate." << endl 
         << "Please note this program only accepts expressions that use addition, subtraction, multiplication, and division." << endl 
         << "Parentheses are valid in a given expression as well." << endl 
         << "Input expression, or \"exit\" to stop, and hit enter: ";
    getline(cin, userInput);

    Lexer* activeLexerPtr = new Lexer();
    Parser* activeParserPtr = new Parser(activeLexerPtr);

    // Main execution loop   
    while (userInput != "exit") {
        // Set userInput into the lexer and try to run parser
        try {
            activeLexerPtr->setEquation(userInput);
            cout << "Answer: " << activeParserPtr->calculate() << endl;
        }
        //Catches all errors from the lexer and parser
        catch (const string &errorText) { 
            cout << "Error: " << errorText << endl;
        }
        //Requery User
        cout << "Enter expression, or \"exit\" to stop, and hit enter: ";
        getline(cin, userInput);
    }

    // Garbage collection and program exit
    delete activeLexerPtr;
    delete activeParserPtr;
    return 0;
}