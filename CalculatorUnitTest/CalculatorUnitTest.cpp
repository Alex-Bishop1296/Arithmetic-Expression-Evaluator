// CalculatorUnitTest.cpp : This file contains unit tests for the AritheticExpressionEvaluator project, specifically those relating to calculator inputs
#include "pch.h"
#include "CppUnitTest.h"
#include "../ArithmeticExpressionEvaluator/Lexer.h"
#include "../ArithmeticExpressionEvaluator/Lexer.cpp"
#include "../ArithmeticExpressionEvaluator/Parser.h"
#include "../ArithmeticExpressionEvaluator/Parser.cpp"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorUnitTest
{
	TEST_CLASS(CalculatorUnitTest)
	{
	public:
		// Declare Variables
		Lexer* lexerPtr;
		Parser* parserPtr;

		// Test Constructor 
		CalculatorUnitTest() {
			lexerPtr = new Lexer;
			parserPtr = new Parser(lexerPtr);
		}
		// Test Destructor
		~CalculatorUnitTest() {
			delete lexerPtr;
			delete parserPtr;
		}
		// Generic method to get answer from calculator, I don't catch for exceptions because I expect them not to happen in these tests
		double getAnswer(string equation) {
			double result;
			lexerPtr->setEquation(equation);
			result = parserPtr->calculate();
			return result;
		}
		// Method for equations designed to fail and receive an error throw, returns the error message of that throw
		string getError(string equation) {
			string errorMessage;
			try {
				lexerPtr->setEquation(equation);
				parserPtr->calculate();
			}
			//Catches all errors from the lexer and parser
			catch (const string& errorText) {
				errorMessage = errorText;
			}
			return errorMessage;
		}

		TEST_METHOD(TestBasicAddition) //This also test the inital example input from the problem prompt
		{
			double expectedResult = 2;
			Assert::AreEqual(getAnswer("1+1"), expectedResult);
		}

		TEST_METHOD(TestBasicSubtration)
		{
			double expectedResult = 0;
			Assert::AreEqual(getAnswer("1-1"), expectedResult);
		}

		TEST_METHOD(TestBasicMultiplication)
		{
			double expectedResult = 4;
			Assert::AreEqual(getAnswer("2*2"), expectedResult);
		}

		TEST_METHOD(TestBasicDivision)
		{
			double expectedResult = 2;
			Assert::AreEqual(getAnswer("4/2"), expectedResult);
		}

		TEST_METHOD(TestBasicParentheses)
		{
			double expectedResult = 4;
			Assert::AreEqual(getAnswer("(1+1)*2"), expectedResult);
		}

		TEST_METHOD(TestBasicNegation)
		{
			double expectedResult = 0;
			Assert::AreEqual(getAnswer("-1+1"), expectedResult);
		}

		TEST_METHOD(TestBasicOrderOfOperations)
		{
			double expectedResult = 5;
			Assert::AreEqual(getAnswer("2*(9-2+3)/4"), expectedResult);
		}

		TEST_METHOD(TestBasicExtraWhitespace)
		{
			double expectedResult = 2;
			Assert::AreEqual(getAnswer("1	\t\n+1"), expectedResult);
		}

		TEST_METHOD(TestErrorThrowPrimaryExpression)
		{
			string expectedResult = "Expected primary expression";
			Assert::AreEqual(getError("1+"), expectedResult);
		}

		TEST_METHOD(TestErrorThrowEmptyExpression) {
			string expectedResult = "Expected primary expression";
			Assert::AreEqual(getError(""), expectedResult);
		}

		TEST_METHOD(TestErrorThrowMissingParenthesis)
		{
			string expectedResult = "Missing parenthesis";
			Assert::AreEqual(getError("(1+1"), expectedResult);
		}

		TEST_METHOD(TestErrorThrowDivisionByZero)
		{
			string expectedResult = "Division by zero";
			Assert::AreEqual(getError("2/0"), expectedResult);
		}

		TEST_METHOD(TestErrorThrowInvalidCharacter)
		{
			string expectedResult = "Invalid character found: x";
			Assert::AreEqual(getError("1+x"), expectedResult);
		}

		TEST_METHOD(TestErrorThrowMultipleDecimals)
		{
			string expectedResult = "Multiple decimals found in arguement";
			Assert::AreEqual(getError("1..1+1"), expectedResult);
		}

		TEST_METHOD(TestExampleExpressionOne) //Tests one of the example input given by the intital problem prompt
		{
			double expectedResult = 42;
			Assert::AreEqual(getAnswer("(3 + 4) * 6"), expectedResult);
		}

		TEST_METHOD(TestExampleExpressionTwo) //Tests another one of the example inputs given by the intial problem prompt
		{
			double expectedResult = 14;
			Assert::AreEqual(getAnswer("(1 * 4) + (5 * 2)"), expectedResult);
		}
	};
}
