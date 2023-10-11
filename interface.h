#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <vector>
#include "lexanalyzer.h"
#include "expevaluator.h"

using namespace std;

class Interface
{
	friend class lexAnalyzer;
	friend class expEvaluator;

public:
	void startInterface();
	void input(Interface&, lexAnalyzer&, expEvaluator&);
	void helpCommand(Interface&, lexAnalyzer&, expEvaluator&);
	void showCommand(Interface&, lexAnalyzer&, expEvaluator&);
	void readCommand(Interface&, lexAnalyzer&, expEvaluator&);
	void clearCommand(Interface&, lexAnalyzer&, expEvaluator&);
	Interface();
private:
	typedef vector<string> programType;
	programType programCode;
	
	string userFile;
};

#endif
