//  Lexer.h : This file contains the prototypes for the "Lexer" class.
#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "TokenType.h"
using namespace std;

class Lexer
{
public:
	double		getNumber() const;
	TokenType	getNextToken();
	TokenType	getCurrentToken() const;
	void		setEquation(const string &userInput);
private:
	double		currentNumber;
	string		stringEquation;
	TokenType	currentToken;

};
#endif // !LEXER_H