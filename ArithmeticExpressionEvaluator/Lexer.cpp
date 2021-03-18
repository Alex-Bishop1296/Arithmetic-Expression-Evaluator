//  Lexer.cpp : This file contains the defintions for the "Lexer" class.
/*  Date: 3/16/2021

	Programmer: Alex Bishop

	Purpose: The Lexer takes user input from the main() and begins to Tokenize it so it can be passed to the Parser for understanding. 
			 The Parser calls the Lexer each time it needs a new token to try and minimize the amount of times the user input needs to be iterated through.
			 Currently, the time is retrival for operations on the Lexer is O(n).
*/
#include "Lexer.h"

/*
	Constructor, set member variables to safe values
*/
Lexer::Lexer() : currentNumber(0), stringEquation(""), currentToken(TokenType::END) {}

/*
	Main method that causes the lexer to interpret the next token from the input sequence
	@return the next token interpreted from the equation stored in the lexer
*/
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
	if (!isdigit(ch) && ch != '.') {
		// We use append here to prevent an error that was occuring with errorText + ch, which would return junk memory after garbage collection happended
		throw string("Invalid character found: ").append(1, ch);
	}
	stringNumber += ch;
	// While leading equation character is not empty and either a digit or a dot (ie would not stop on dot of 3.14), keep adding to our stringNumber until full number is obtained
	bool didFindDecimal; //used to prevent multiple decimal points in a single number
	didFindDecimal = (ch == '.') ? true : false;
	while (!stringEquation.empty()
		&& (isdigit(stringEquation.front()) || stringEquation.front() == '.')) {
		if (!didFindDecimal && stringEquation.front() == '.')
			didFindDecimal = true;
		else if (didFindDecimal && stringEquation.front() == '.') {
			throw string("Multiple decimals found in arguement");
		}
		stringNumber += stringEquation.front();
		stringEquation.erase(0, 1);
	}
	//stod = string to double
	currentNumber = stod(stringNumber);
	return currentToken = TokenType::NUMBER;
}

/*
	Accessor for TokenType currentToken, similar output to getNextToken but does not progress the lexer's progresss on the equation
	@return a const TokenType containing value of currentToken
*/
TokenType Lexer::getCurrentToken() const {
	return currentToken;
}

/*
	Accessor for double currentNumber 
	@return a const double containing value of currentNumber
*/
double Lexer::getNumber() const {
	return currentNumber;
}

/*
	Assigns the user input to the string container inside the Lexer and removes whitespace and newline
*/
void Lexer::setEquation(const string& userInput) {
	stringEquation = userInput;
	stringEquation.erase(remove_if(stringEquation.begin(), stringEquation.end(), ::isspace), stringEquation.end());  //remove invalid characters from the equation and resize the string it is contained in
}
