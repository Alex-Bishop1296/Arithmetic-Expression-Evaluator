//  Parser.cpp : This file contains the defintions for the "Parser" class.
/*  Date: 3/16/2021

	Programmer: Alex Bishop

	Purpose: The Parser takes tokens and numbers from the Lexer and translates them into a solved arithmetic problem using a Recursive Descent Parser.
*/
#include "Parser.h"

/*	
	Constructor
	@param parameterLexer - 
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
	// Call parseMulDiv() as they are higher in Order of Operations
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
	double curResult = parsePrimaryExpression();

	while (true)
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
				if (tempResult != 0.0)
				{
					curResult /= tempResult;
					break;
				}
				else
				{
					throw string("Division by zero.");
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
	lexerPtr->getNextToken();

	switch (lexerPtr->getCurrentToken()) {
		case TokenType::NUMBER:
		{
			double curResult = lexerPtr->getNumber();
			lexerPtr->getNextToken();
			return curResult;
		}
		case TokenType::MINUS:
		{
			//Return the negative of the expression
			return -(1.0) * parsePrimaryExpression();
		}
		case TokenType::OPEN_PAREN:
		{
			double curResult = parseAddSub();
			if (lexerPtr->getCurrentToken() != TokenType::CLOSE_PAREN)
			{
				throw string("Missing parenthesis");
			}
			lexerPtr->getNextToken();
			return curResult;
		}
		default:
		{
			throw string("Expected primary expression");
		}
	}
}