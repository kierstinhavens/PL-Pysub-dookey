#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <map>
#include <utility>
#include <stack>
#include <iostream>
#include "expevaluator.h"
#include "lexanalyzer.h"
#include "interface.h"
#include "expevaluator.h"



class Interpreter {

	friend class expEvaluator;
	friend class lexAnalyzer;
	friend class Interface;

public:
	Interpreter();
	bool interpretTheLine(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);
	void print(Interface&,lexAnalyzer&, expEvaluator&, Interpreter&);
	void clear(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);

private:
	bool interpMode;
	int finalVal;
	bool ifAssigned;
	bool userInput;
};
#endif
