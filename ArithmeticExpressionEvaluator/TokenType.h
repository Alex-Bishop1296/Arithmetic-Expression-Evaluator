#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H
/*
	Tokens here are the grammer our Lexer will use to send information to the Parser
*/
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
#endif TOKEN_TYPE_H