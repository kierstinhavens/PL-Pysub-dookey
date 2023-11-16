#include <iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>
#include "interface.h"
#include "lexanalyzer.h"
#include "expevaluator.h"
#include "interpreter.h"
using namespace std;

//constructor
Interface::Interface() {
}

//starts the program
void Interface::startInterface()
{
	Interface inter1;
	lexAnalyzer lexAn;
	expEvaluator expE;
	Interpreter pysubi;

	cout << "Pysub Interpreter 1.0 on Windows (September 2023)" << endl;
	cout << "Enter program lines or read (<filename.py>) at command line interface" << endl;
	cout << "Type 'help' for more information or 'quit' to exit" << endl;

	input(inter1, lexAn, expE, pysubi);
}

void Interface::input (Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE, Interpreter& pysubi)
{
originalPath: //to direct program back 

	string input;
	pysubi.interpMode = false;
	//get the input from user
	cout << endl << ">>> ";

	getline(cin, input);
	int stringLength = input.length();

	//User enters the quit command
	if (input == "quit" || input == "quit()")
		exit(0);

	//User enters the show command; must have entered a file beforehand through read command, will display contents of file.
	else if (input == "show" || input == "show()")
	{
		if (inter1.programCode.empty() == true)
		{
			cout << "You have not entered a file yet. Please use the read command in order to view a file. " << endl;
			goto originalPath;
		}
		else
		{
			showCommand(inter1, lexAn, expE, pysubi);
			goto originalPath;
		}
	}



	//User enters expression
	else if (input.length() >= 2 && ((isdigit(input[0]) || input[0] == '(') || (input[0] == 'n' && input[1] == 'o' && input[2] == 't')))
	{
		if (pysubi.interpMode == false)
		{
			inter1.clearCommand(inter1, lexAn, expE, pysubi);
			inter1.programCode.push_back(input);
			lexAn.getTokenInfo(inter1, lexAn, expE, pysubi);
			expE.startExp(inter1, lexAn, expE, pysubi);
			goto originalPath;
		}
	}

	//User enters show(tokens) to view each token of python file 
	else if (input == "show(tokens)")
	{
		if (inter1.programCode.empty() == true)
		{
			cout << "You have not entered a file yet. Please use the read command in order to view a file. " << endl;
			goto originalPath;
		}
		//This will call the "show tokens" function after the check has been made that a file is stored in read
		else
		{
			lexAn.showTokenInfo(inter1, lexAn, expE, pysubi);
			//inter1.clearCommand(inter1, lexAn, expE);
			goto originalPath;
		}
	}

	//User enters clear command
	else if (input == "clear" || input == "clear()")
	{
		clearCommand(inter1, lexAn, expE, pysubi);
		cout << "Information has been cleared from the system. " << endl;
		goto originalPath;
	}

	//User enters the help command
	else if (input == "help" || input == "help()")
		helpCommand(inter1, lexAn, expE, pysubi);

	//User enters read command; the following else statements check for different variations of user input
	else if (input[0] == 'r' && input[1] == 'e' && input[2] == 'a' && input[3] == 'd' && stringLength < 5)
	{
		cout << "You must enter a file to read from. " << endl;
		goto originalPath;
	}
	//read function if user does not enter parentheses with space after read
	else if (input[0] == 'r' && input[1] == 'e' && input[2] == 'a' && input[3] == 'd' && stringLength > 5 && input[stringLength - 1] != ')')
	{
		userFile.clear();
		for (int i = 5; i < stringLength; i++)
			userFile.push_back(input[i]);
		readCommand(inter1, lexAn, expE, pysubi);
		goto originalPath;
	}
	//read function if user does enter parentheses
	else if (input[0] == 'r' && input[1] == 'e' && input[2] == 'a' && input[3] == 'd' && input[4] == '(' && input[stringLength - 1] == ')')
	{
		userFile.clear();
		//indexing for the file starts after parenthesis
		for (int i = 5; i < stringLength - 1; i++)
			userFile.push_back(input[i]);
		readCommand(inter1, lexAn, expE, pysubi);
		goto originalPath;
	}
	else if (input == "run()" || input == "run")
	{
		if (inter1.programCode.empty()==true)
			cout << "Please use the read() command first" << endl;
		else
		{
			pysubi.interpretTheLine(inter1, lexAn, expE, pysubi);
			pysubi.interpMode = false;
		}
		goto originalPath;
	}
	else if (input == "show(variables)" || input == "show(var)")
	{
		expE.showVariables(inter1, lexAn, expE, pysubi);
	}
	else
	{
		if (pysubi.interpMode == false && pysubi.userInput==false)
		{
			cout << "Please enter a proper command." << endl;
			goto originalPath;
		}
	}
}


//User enters the help command. This is the help command function definition
void Interface::helpCommand(Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE, Interpreter& pysubi)
{
	cout << endl;
	cout << "Welcome to the Help Utility! " << endl;
	cout << "To go back to the interpreter, please enter 'exit' and you will be taken back to the original interface menu. " << endl;
	cout << "In order to view a list and description of the viable commands, please enter 'commands'. " << endl;

helpPath:
	string helpMe = "";
	cout << "help> ";

	getline(cin, helpMe);

	if (helpMe == "commands")
	{
		cout << "Our python interpreter is here to help. Please enter any of the following commands shown below to view more information. " << endl;
		cout << "All commands can be entered as functions as well! -- i.e. myCommand() -- " << endl;
		cout << endl;
		cout << "'clear'     'quit'     'read'     'show'     'help'" << endl;
		cout << "Type 'exit' to exit the help utility and be directed back to the main interface. " << endl;
		goto helpPath;
	}
	else if (helpMe == "exit" || helpMe == "(exit()")
	{
		cout << "You have exited the help utility. You will be directed back to the main interface now. " << endl;
		input(inter1, lexAn, expE, pysubi);
	}
	else if (helpMe == "help" || helpMe == "help()")
	{
		cout << "This command provides helpful information to the user. " << endl;
		goto helpPath;
	}
	else if (helpMe == "quit" || helpMe == "quit()")
	{
		cout << "This command allows the user to quit the program. " << endl;
		goto helpPath;
	}
	else if (helpMe == "read" || helpMe == "read()")
	{
		cout << "This command will read a python file the user enters. " << endl;
		goto helpPath;
	}
	else if (helpMe == "show" || helpMe == "show()")
	{
		cout << "Shows the lines of the program that are stored in program data structure. " << endl;
		goto helpPath;
	}
	else if (helpMe == "clear" || helpMe == "clear()")
	{
		cout << "This command clears out or deletes any lines that are stored in the program data structure. " << endl;
		goto helpPath;
	}
	else
	{
		cout << "You did not enter a proper command, please try again. " << endl;
		goto helpPath;
	}
}

//this will clear any data in the program code vector and then read in the user's python file
void Interface::readCommand(Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE, Interpreter& pysubi)
{
	clearCommand(inter1, lexAn, expE, pysubi);

	ifstream ifile(userFile);
	if (!ifile)
	{
		cout << "Sorry, we had a problem opening your file. You will be directed back to the main interface now. " << endl;
		input(inter1, lexAn, expE, pysubi);
	}

	string readString = "";

	while (getline(ifile, readString))
	{
		inter1.programCode.push_back(readString);
		if (!ifile)
			break;
	}
	lexAn.getTokenInfo(inter1, lexAn, expE, pysubi);
	cout << "Your file has been read, you may view it through the show command now. " << endl;
	ifile.close();
}

//utilizes the vector "clear()" built in func to clear any data already/previously stored in the vector
void Interface::clearCommand(Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE, Interpreter& pysubi)
{
	inter1.programCode.clear();
	lexAn.clearTokenInfo();
	expE.clearTable();
}

//this function will display the code in the user's python file once entered through the read command
//it will also include line numbers (this is completed by the use of i in the iteration of the for loop)
void Interface::showCommand(Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE, Interpreter& pysubi)
{
	for (int i = 0; i < inter1.programCode.size(); i++)
	{
		cout << "[" << i << "]" << inter1.programCode[i] << endl;
	}
}
