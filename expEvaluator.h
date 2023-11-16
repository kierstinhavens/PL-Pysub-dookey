#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H

#include <string>
#include <map>
#include <utility>
#include <stack>
#include "lexanalyzer.h"
#include "interpreter.h"
#include "interface.h"

using namespace std;

enum class categoryType;

class expEvaluator
{

	friend class Interface;
	friend class lexAnalyzer;
	friend class Interpreter;

public:

	expEvaluator();
	void startExp(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);
	void infixToPostfix(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);
	void postfixEval(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);
	int getPrecedence(string);
	int calculate(int, int, string);
	void storeTable(string, string);
	int getTableVal(string, Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);
	void clearTable();
	void showVariables(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);

private:

	vector<pair<string, categoryType>> postVect, inVect, stackVect;
	typedef map<string, string> symbolTableType;
	typedef pair<string, categoryType> pairType;
	symbolTableType symbolTable;
};
#endif

