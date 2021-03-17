//  Lexer.cpp : This file contains the defintions for the "Lexer" class.
/*  Date: 3/16/2021

	Programmer: Alex Bishop

	Purpose: The Lexer takes user input from the main() and begins to Tokenize it so it can be passed to the Parser for understanding. 
			 The Parser calls the Lexer each time it needs a new token to try and minimize the amount of times the user input needs to be iterated through.
			 Currently, the time is retrival for operations on the Lexer is O(n).
*/
#include <iostream>
#include <string>
#include "Lexer.h"
using namespace std;


double Lexer::getNumber() {
	return currentNumber;
}

// Gets the next token for the Parser such that 
TokenType Lexer::getNextToken() {
	// If the equation is empty, simply return an END token
	if (stringEquation.empty())
		return currentToken = TokenType::END;

	// Get the first character of the equation
	char ch = stringEquation.front();
	stringEquation.erase(0, 1);

	// Check character for non-number token types
	switch (ch) {
		case'*': return currentToken = TokenType::MULTIPLY;
		case'/': return currentToken = TokenType::DIVIDE;
		case'+': return currentToken = TokenType::PLUS;
		case'-': return currentToken = TokenType::MINUS;
		case'(': return currentToken = TokenType::OPEN_PAREN;
		case')': return currentToken = TokenType::CLOSE_PAREN;
	}
	// Check character and other leading characters for number
	string stringNumber = "";
	if (isdigit(ch)) {
		stringNumber += ch;
		// While leading equation character is not empty and either a digit or a dot (ie would not stop on dot of 3.14), keep adding to our stringNumber until full number is obtained
		while (!stringEquation.empty() && (isdigit(stringEquation.front()) || stringEquation.front() == '.')) {
			stringNumber += stringEquation.front();
			stringEquation.erase(0, 1);
		}
		//stod = string to double
		currentNumber = stod(stringNumber);
		return currentToken = TokenType::NUMBER;
	}
	else
	{
		cout << "Error: Invlid character found: " << ch << endl;
		exit(-1);
	}
}


TokenType Lexer::getCurrentToken() {
	return currentToken;
}

//Assigns the user input to the string container inside the Lexer and removes whitespace
void Lexer::setEquation(string& userInput) {
	stringEquation = userInput;
	stringEquation.erase(remove_if(userInput.begin(), userInput.end(), isspace)); //remove whitespace from the equation and resize the string it is contained in
}
