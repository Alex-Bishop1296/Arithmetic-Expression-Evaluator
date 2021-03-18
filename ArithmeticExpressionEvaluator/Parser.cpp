//  Parser.cpp : This file contains the defintions for the "Parser" class.
/*  Date: 3/16/2021

	Programmer: Alex Bishop

	Purpose:	The Parser takes tokens and numbers from the Lexer and translates them into a solved arithmetic problem using a Recursive Descent Parser.
				The basics of this parser is that it attempts to calculate a given problem from the lexer passed to it when Parser.calculate() is called.
				It does this by creating a "tree" of descending problems to solve and then backtracking up that tree as methods start to return.
				It is recursive since it is ultimately trying to solve a primary expression that can contain other primary expressions.
*/
#include "Parser.h"

/*	
	Constructor
	@param parameterLexer - Lexer class object that will provide tokens to the parser
*/
Parser::Parser(Lexer* parameterLexer) : lexerPtr(parameterLexer) {}

/*
	Begins parsing the data obtained from the lexer with a leading call to parseAddSub()
	@return The solved arithmetic equation as given by the lexer
*/
double Parser::calculate() {
	return parseAddSub();
}

/*
	Performs Addition and Subtraction from the given Lexer tokens as long as there are no multiplications
	or divisions that need to be execute first as per the Order of Operations
	@return The solved current primary expression from the Lexer
*/
double Parser::parseAddSub() {
	// Call parseMulDiv() as that is where multiplication and division are evaluated, as they are higher in the order of operations
	double curResult = parseMulDiv();

	while (true) //Keep looping until the default switch case is hit
	{
		switch (lexerPtr->getCurrentToken())
		{
		case TokenType::PLUS:
		{
			curResult += parseMulDiv();
			break;
		}
		case TokenType::MINUS:
		{
			curResult -= parseMulDiv();
			break;
		}
		default:
		{
			return curResult;
		}
		}
	}
}

/*
	Performs Multiplication and Division from the given Lexer tokens as long as there are no Primary Expressions
	(ie parentheses) that need to be execute first as per the order of operations
	@return The solved current primary expression from the Lexer
*/
double Parser::parseMulDiv() {
	// Call parsePrimaryExpressions() as that is where parentheses are evaluated, as they are higher in the order of operations 
	double curResult = parsePrimaryExpression();

	while (true) //Keep looping until the default switch case is hit
	{
		switch (lexerPtr->getCurrentToken())
		{
			case TokenType::MULTIPLY:
			{
				curResult *= parsePrimaryExpression();
				break;
			}
			case TokenType::DIVIDE:
			{
				double tempResult = parsePrimaryExpression();
				//Divide by zero error checking
				if (tempResult != 0.0)
				{
					curResult /= tempResult;
					break;
				}
				else
				{
					throw string("Division by zero");
				}
			}
			default:
				return curResult;
		}
	}
}


/*
	Get the first token from the lexer and all other tokens then evaluates the token and either adds
	appropriate number of negation of a value to the the current result or rucurses and evaluates the next
	primary expression in the give airthemetic problem
	@return The solved current primary expression from the Lexer
*/
double Parser::parsePrimaryExpression() {
	// First call to the lexer to get a token to read
	lexerPtr->getNextToken();

	switch (lexerPtr->getCurrentToken()) {
		case TokenType::NUMBER:		//Gets number from the lexer and then get next operater token ready for backtracking
		{
			double curResult = lexerPtr->getNumber();
			lexerPtr->getNextToken();
			return curResult;
		}
		case TokenType::MINUS:		//Return the negative of the expression
		{
			return -(1.0) * parsePrimaryExpression();
		}
		case TokenType::OPEN_PAREN:		//Allows program to begin again from intial process for evaluating a primary expression for nested expressions via parenthesis
		{
			double curResult = parseAddSub();
			if (lexerPtr->getCurrentToken() != TokenType::CLOSE_PAREN)
			{
				throw string("Missing parenthesis");
			}
			lexerPtr->getNextToken();
			return curResult;
		}
		default:	//Error checking for broken expressions like "2++2" or "2+ "
		{
			throw string("Expected primary expression");
		}
	}
}