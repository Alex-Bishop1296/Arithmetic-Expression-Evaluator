# Arithmetic-Expression-Evaluator
A interview question poses to make a program to parse and evaluate arithmetic expressions without using the "Shunting Yard" algorithm. This program poses to do so.

## Algorithm explanation
The program executes from ArithmeticExpressionEvaluator.cpp. In main(), we get user input from after a welcome message then feed it to our lexer class object. The lexer's goal is
to take user input and translate that into tokens that can be read by the parser object. These tokens are defined in TokenType.h as they are stored in an enum. When the user
input is passed to the lexer, it is scrubbed of whitespace characters.

After input is place in the lexer we instanciate our parser class object. The job of the parser is to translate the tokens read in from the lexer into an answer to the arithemetic
problem. It does this by going through the the tokens and organizing them as a recursive descent parser. It does this by creating a "tree" of descending problems to solve and then
backtracking up that tree as methods start to return. It is recursive since it is ultimately trying to solve a primary expression that can contain other primary expressions, 
thus methods call themselves.

Once the expression is evaluated, it is passed back to the user to view and more expressions can be entered to evaluate.
