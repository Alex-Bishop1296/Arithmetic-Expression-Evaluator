//  Parser.h : This file contains the prototypes for the "Parser" class.
#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "TokenType.h"
using namespace std;

class Parser
{
public:
	Parser(Lexer* lexer);				// Constructor method, takes a pointer to a instance of a Lexer object
	double calculate();					// Primary method, performs a calculation given the tokens passed back from the Parser::parserLexer variable
private:
	Lexer* lexerPtr = nullptr;			// Member VariableContains the pointer to an existing Lexer
	double parseAddSub();				// Private method, Parse the Lexer for Addition and Subtraction
	double parseMulDiv();				// Private method, Parse the Lexer for Multiplication and Division
	double parsePrimaryExpression();	// Private method, Parse the Lexer for PrimaryExpressions; Recursive
};
#endif // !PARSER_H