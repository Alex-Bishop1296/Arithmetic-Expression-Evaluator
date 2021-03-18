//  Lexer.h : This file contains the prototypes for the "Lexer" class.
#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "TokenType.h"
using namespace std;

class Lexer
{
public:
	Lexer();											// Constructor method
	TokenType	getNextToken();							// Primary method, pass the current token being read from the equation and remove last token
	TokenType	getCurrentToken() const;				// Acesssor method, get Lexer::currentToken
	double		getNumber() const;						// Accessor method, get Lexer::currentNumber
	void		setEquation(const string &userInput);	// Mutator method, set Lexer::stringEquation with input to tokenize and clear input of whitespace 
private:
	double		currentNumber;							// Member variable containing the current number of the last TokenType::NUMBER token read
	string		stringEquation;							// Member variable containing the equation to be tonkenized, does change as Lexer::getNextToken() is executed
	TokenType	currentToken;							// Member variable containing the current token of the last TokeType object read

};
#endif // !LEXER_H