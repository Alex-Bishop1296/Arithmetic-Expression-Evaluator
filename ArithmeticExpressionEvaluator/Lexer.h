#pragma once
#ifndef LEXER_H
#define LEXER_H
/*
Rules for ENBF (Extended Backus-Naur Form), these explain the grammer of our formal language, in this case, the calculator

exp		: term
		| exp + term
		| exp - term
		;
term	: factor
		| factor * term
		| factor / term
		;
factor	: number
		| ( exp )
		;
*/

#include <string>
using namespace std;


// Tokens for our Lexer to translate into
enum TokenType
{
	NUMBER,
	END,
	PLUS = '+',
	MINUS = '-',
	MULTIPLY = '*',
	DIVIDE = '/',
	OPEN_PAREN = '(',
	CLOSE_PAREN = ')'
};

class Lexer
{
public:
	double		getNumber();
	TokenType	getNextToken();
	TokenType	getCurrentToken();
	void		setEquation(string &userInput);
private:
	double		currentNumber;
	string		stringEquation;
	TokenType	currentToken;

};
#endif // !LEXER_H