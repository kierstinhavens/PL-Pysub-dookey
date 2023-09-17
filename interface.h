#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Interface
{
	friend class lexAnalyzer;

public:
	void startInterface();
	void input(Interface&, lexAnalyzer&);
	void helpCommand(Interface&, lexAnalyzer&);
	void showCommand(Interface&, lexAnalyzer&);
	void readCommand(Interface&, lexAnalyzer&);
	void clearCommand(Interface&, lexAnalyzer&);
	Interface();
private:
	typedef vector<string> programType;
	programType programCode;
	
	string userFile;
};

#endif
