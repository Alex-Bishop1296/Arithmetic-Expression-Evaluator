//  Parser.h : This file contains the prototypes for the "Parser" class.
#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "TokenType.h"
using namespace std;

class Parser
{
public:
	Parser(Lexer* lexer);

	double parsePrimaryExpression();
	double parseMulDiv();
	double parseAddSub();

	double calculate();

private:
	Lexer* parserLexer = nullptr;
};


#endif // !PARSER_H
