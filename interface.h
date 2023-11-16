#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <vector>
#include "lexanalyzer.h"
#include "expevaluator.h"
#include "interpreter.h"

using namespace std;

class Interface
{
	friend class lexAnalyzer;
	friend class expEvaluator;
	friend class Interpreter;

public:
	void startInterface();
	void input(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);
	void helpCommand(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);
	void showCommand(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);
	void readCommand(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);
	void clearCommand(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);
	Interface();
private:
	typedef vector<string> programType;
	programType programCode;
	programType postInterp;
	
	string userFile;
};

#endif
