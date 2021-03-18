//  TokenType.h : This file contains the defintions for the TokenType enum
/*	Date: 3/17/2021

	Programmer: Alex Bishop

	Purpose: Tokens here are the grammer our Lexer will use to send information to the Parser
*/
#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

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
#endif // !TOKEN_TYPE_H