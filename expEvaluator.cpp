#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <stack>
#include "interface.h"
#include "lexanalyzer.h"
#include "expevaluator.h"
#include "interpreter.h"


using namespace std;

enum class categoryType;

expEvaluator::expEvaluator() {
}

void expEvaluator::startExp(Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE, Interpreter& pysubi)
{
	infixToPostfix(inter1, lexAn, expE, pysubi);
}

void expEvaluator::infixToPostfix(Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE, Interpreter& pysubi)
{
	int size;
	if (pysubi.interpMode == true)
	{
		size = lexAn.tempExp.size();

		for (int i = 0; i < size; i++)
		{
			//ensures the ability for operators to be scanned in properly, otherwise stack empty error; gets popped off at end
			if (stackVect.empty())
			{
				pairType tempPair;
				tempPair.first = "(";
				tempPair.second = categoryType::LEFT_PAREN;
				stackVect.push_back(tempPair);
			}
			if (lexAn.tempExp[i].second == categoryType::IDENTIFIER)
			{
				pairType tempPair2;

				int var;
				string varStr = "";
				var = getTableVal(lexAn.tempExp[i].first, inter1, lexAn, expE, pysubi);
				varStr = to_string(var);
				tempPair2.first = varStr;
				tempPair2.second = categoryType::NUMERIC_LITERAL;
				postVect.push_back(tempPair2);
			}
			else if (lexAn.tempExp[i].second == categoryType::NUMERIC_LITERAL)
			{
				postVect.push_back(lexAn.tempExp[i]);
			}
			else if (lexAn.tempExp[i].second == categoryType::LEFT_PAREN)
			{
				stackVect.push_back(lexAn.tempExp[i]);
			}
			else if ((lexAn.tempExp[i].second == categoryType::ARITH_OP) || (lexAn.tempExp[i].second == categoryType::RELATIONAL_OP) || (lexAn.tempExp[i].second == categoryType::LOGICAL_OP))
			{
				int precedenceComp, precedenceTop;
				//will return 0 if stack is "empty" (auto left paren)
				precedenceTop = getPrecedence(stackVect[stackVect.size() - 1].first);
				precedenceComp = getPrecedence(lexAn.tempExp[i].first);
				while ((!stackVect.empty()) && (stackVect[stackVect.size() - 1].second != categoryType::LEFT_PAREN) && (precedenceTop >= precedenceComp))
				{
					postVect.push_back(stackVect[stackVect.size() - 1]);
					stackVect.pop_back();
				}
				stackVect.push_back(lexAn.tempExp[i]);
			}
			else if (lexAn.tempExp[i].second == categoryType::RIGHT_PAREN)
			{
				if (!stackVect.empty())
				{
					while (stackVect[stackVect.size() - 1].second != categoryType::LEFT_PAREN)
					{
						postVect.push_back(stackVect[stackVect.size() - 1]);
						stackVect.pop_back();
					}
					//pop left paren
					stackVect.pop_back();
				}
				else
					cout << "Not a valid expression, missing a parenthesis" << endl;
			}
		}
		while (!stackVect.empty())
		{
			//pops off initial left paren
			if (stackVect[stackVect.size() - 1].second == categoryType::LEFT_PAREN)
			{
				stackVect.pop_back();
			}
			else
			{
				postVect.push_back(stackVect[stackVect.size() - 1]);
				stackVect.pop_back();
			}
		}
		postfixEval(inter1, lexAn, expE, pysubi);
	}
	else
	{
		size = inter1.programCode.size();
		for (int i = 0; i < size; i++)
		{
			//ensures the ability for operators to be scanned in properly, otherwise stack empty error; gets popped off at end
			if (stackVect.empty())
			{
				pairType tempPair;
				tempPair.first = "(";
				tempPair.second = categoryType::LEFT_PAREN;
				stackVect.push_back(tempPair);
			}
			for (int j = 0; j < lexAn.numTokenLine[i]; j++)
			{
				if (lexAn.tokenInfo[i][j].second == categoryType::IDENTIFIER)
				{
					pairType tempPair2;

					int var;
					string varStr = "";
					var = getTableVal(lexAn.tokenInfo[i][j].first, inter1, lexAn, expE, pysubi);
					varStr = to_string(var);
					tempPair2.first = varStr;
					tempPair2.second = categoryType::NUMERIC_LITERAL;
					postVect.push_back(tempPair2);
				}
				else if (lexAn.tokenInfo[i][j].second == categoryType::NUMERIC_LITERAL)
				{
					postVect.push_back(lexAn.tokenInfo[i][j]);
				}
				else if (lexAn.tokenInfo[i][j].second == categoryType::LEFT_PAREN)
				{
					stackVect.push_back(lexAn.tokenInfo[i][j]);
				}
				else if ((lexAn.tokenInfo[i][j].second == categoryType::ARITH_OP) || (lexAn.tokenInfo[i][j].second == categoryType::RELATIONAL_OP) || (lexAn.tokenInfo[i][j].second == categoryType::LOGICAL_OP))
				{
					int precedenceComp, precedenceTop;
					//will return 0 if stack is "empty" (auto left paren)
					precedenceTop = getPrecedence(stackVect[stackVect.size() - 1].first);
					precedenceComp = getPrecedence(lexAn.tokenInfo[i][j].first);
					while ((!stackVect.empty()) && (stackVect[stackVect.size() - 1].second != categoryType::LEFT_PAREN) && (precedenceTop >= precedenceComp))
					{
						postVect.push_back(stackVect[stackVect.size() - 1]);
						stackVect.pop_back();
					}
					stackVect.push_back(lexAn.tokenInfo[i][j]);
				}
				else if (lexAn.tokenInfo[i][j].second == categoryType::RIGHT_PAREN)
				{
					if (!stackVect.empty())
					{
						while (stackVect[stackVect.size() - 1].second != categoryType::LEFT_PAREN)
						{
							postVect.push_back(stackVect[stackVect.size() - 1]);
							stackVect.pop_back();
						}
						//pop left paren
						stackVect.pop_back();
					}
					else
						cout << "Not a valid expression, missing a parenthesis" << endl;
				}
			}
		}
		while (!stackVect.empty())
		{
			//pops off initial left paren
			if (stackVect[stackVect.size() - 1].second == categoryType::LEFT_PAREN)
			{
				stackVect.pop_back();
			}
			else
			{
				postVect.push_back(stackVect[stackVect.size() - 1]);
				stackVect.pop_back();
			}
		}
		postfixEval(inter1, lexAn, expE, pysubi);
	}
}
void expEvaluator::postfixEval (Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE, Interpreter& pysubi)
{
	stack<int> tempStack;

	while (!postVect.empty())
	{
		if (postVect[0].second == categoryType::NUMERIC_LITERAL)
		{
			tempStack.push(stoi(postVect[0].first));
			postVect.erase(postVect.begin()); 
		}
		else if((postVect[0].second == categoryType::ARITH_OP) || (postVect[0].second == categoryType::RELATIONAL_OP) || (postVect[0].second == categoryType::LOGICAL_OP))
		{
			if (postVect[0].first == "not")
			{
				int unaryOp;

				if (tempStack.empty()) {
					cout << "Error not a valid expression. for not op" << endl;
					exit(1);
				}

				unaryOp = tempStack.top();

				if (unaryOp == 1) 
				{
					tempStack.pop();
					tempStack.push(0);
					postVect.erase(postVect.begin());
				}
				else if (unaryOp == 0)
				{
					tempStack.pop();
					tempStack.push(1);
					postVect.erase(postVect.begin());
				}
				else 
				{
					cout << "Not a valid expression. for not op 2" << endl;
					exit(1);
				}
			}
			else
			{
				int operand1, operand2, calculation;
				//check stack for errors
				if (tempStack.empty()) 
				{
					cout << "Not a valid expression. not two operands in stack" << endl;
					exit(1);
				}
				string operate = postVect[0].first;
				postVect.erase(postVect.begin());
				operand2 = tempStack.top();
				tempStack.pop();
				//check for errors in stack
				if (tempStack.empty()) 
				{
					cout << "Not a valid expression. not enough operands" << endl;
					exit(1);
				}
				operand1 = tempStack.top();
				tempStack.pop();
				calculation = calculate(operand1, operand2, operate);
				tempStack.push(calculation);
			}
		}
	}
	//Check for errors
	if (tempStack.empty())
	{
		cout << "Error" << endl;
		exit(1);
	}
	else
	{
		if (pysubi.interpMode == false)
		{
			cout << tempStack.top();
		}
		else
		{
			if (pysubi.ifAssigned == true)
			{
				pysubi.finalVal = tempStack.top();
			}
			else
			{
				cout << tempStack.top();
			}
		}
	}
}

int expEvaluator::calculate(int x, int y, string o)
{
	if (o == "*")
		return x * y;
	else if (o == "/")
		return x / y;
	else if (o == "%")
		return x % y;
	else if (o == "+")
		return x + y;
	else if (o == "-")
		return x - y;
	else if (o == "<") 
	{
		if (x < y)
			return 1;
		else
			return 0;
	}
	else if (o == "<=") 
	{
		if (x <= y)
			return 1;
		else
			return 0;
	}
	else if (o == ">") 
	{
		if (x > y)
			return 1;
		else
			return 0;
	}
	else if (o == ">=") 
	{
		if (x >= y)
			return 1;
		else
			return 0;
	}
	else if (o == "!=") 
	{
		if (x != y)
			return 1;
		else
			return 0;
	}
	else if (o == "==") 
	{
		if (x == y)
			return 1;
		else
			return 0;
	}
	else if (o == "and") 
	{
		//both vals must be 1 to be true
		if ((x == 1) && (y == 1))
			return 1;
		else
			return 0;
	}
	else if (o == "or") {
		if (x == 1 || y == 1)
			return 1;
		else
			return 0;
	}
}

int expEvaluator::getPrecedence(string theOp)
{
	if ((theOp == "*") || (theOp == "/") || (theOp == "%"))
	{
		return(5);
	}
	else if ((theOp == "+") || (theOp == "-"))
	{
		return(4);
	}
	else if ((theOp == "<") || (theOp == ">") || (theOp == "<=") || (theOp == ">=") || (theOp == "!=") || (theOp == "=="))
	{
		return(3);
	}
	else if ((theOp == "not"))
	{
		return(2);
	}
	else if (theOp == "and")
	{
		return(1);
	}
	else if (theOp == "or")
	{
		return (0);
	}
	else
		//vectStack.first is "empty" or left paren so precedence is 0
		return(0);
}

void expEvaluator::clearTable() 
{
	symbolTable.clear();
}

void expEvaluator::storeTable(string key, string value) {

	symbolTable[key] = value;
}

int expEvaluator::getTableVal(string key, Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE, Interpreter& pysubi) 
{

	//Returns int value of the value for the user input key
	if (symbolTable.count(key))
		return stoi(symbolTable[key]);
	else 
	{
		cout << "Value not found" << endl;
		inter1.input(inter1, lexAn, expE, pysubi);
	}
}

void expEvaluator::showVariables(Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE, Interpreter& pysubi)
{
	if (!symbolTable.empty())
	{
		map<string, string>::iterator iter = expE.symbolTable.begin();
		cout << "--VARIABLES--" << endl;
		int count = 0;
		cout << "--KEY--VALUE--" << endl;
		while (iter != expE.symbolTable.end())
		{
			cout <<iter->first << "\t" << iter->second << endl;
			iter++;
			count++;
		}
		inter1.input(inter1, lexAn, expE, pysubi);
	}
	else
	{
		cout << "No variables to display" << endl;
		inter1.input(inter1, lexAn, expE, pysubi);
	}
}

