#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H

#include <string>
#include <map>
#include <utility>
#include <stack>
#include "lexanalyzer.h"

using namespace std;

class expEvaluator
{

	friend class Interface;
	friend class lexAnalyzer;

public:

	expEvaluator();
	void startExp(Interface&, lexAnalyzer&, expEvaluator&);
	void infixToPostfix(Interface&, lexAnalyzer&, expEvaluator&);

private:

	vector<pair<string, categoryType>> postVect;
	typedef map<string, string> symbolTableType;
	symbolTableType symbolTable;
};
#endif
