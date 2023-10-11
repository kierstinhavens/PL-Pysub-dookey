#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <stack>
#include "interface.h"
#include "lexanalyzer.h"
#include "expevaluator.h"


using namespace std;

expEvaluator::expEvaluator() {
}

void expEvaluator::startExp (Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE)
{
	//inter1.showCommand(inter1, lexAn);
	//lexAn.showTokenInfo(inter1, lexAn, expE);
	infixToPostfix(inter1, lexAn, expE);
}

void expEvaluator::infixToPostfix (Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE)
{
	stack<pair<string, categoryType>> stackVect;
}
