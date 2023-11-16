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

Interpreter::Interpreter() {
}

bool Interpreter::interpretTheLine(Interface& inter1, lexAnalyzer& lexAn, expEvaluator& expE, Interpreter& pysubi)
{
	
	pysubi.interpMode = true;
	
	for (int i = 0; i < inter1.programCode.size(); i++)
	{
		bool nextLine = false;
		for (int j = 0; j < lexAn.numTokenLine[i] && nextLine==false; j++)
		{
			if (lexAn.tokenInfo[i][j].second == categoryType::COMMENT)
			{
				nextLine = true;
			}
			else if (lexAn.tokenInfo[i][j].first=="print")
			{
				//ensures closing parenthesis is included
				if (lexAn.tokenInfo[i][lexAn.numTokenLine[i]-1].second != categoryType::RIGHT_PAREN)
				{
					cout << "Improper syntax. Line ["<<i<<"]. Please re read your file and try again." << endl;
					inter1.input(inter1, lexAn, expE, pysubi);
				}
				if (lexAn.tokenInfo[i][j + 1].second == categoryType::LEFT_PAREN)
				{
					j += 2;
					while (lexAn.tokenInfo[i][j].second != categoryType::RIGHT_PAREN)
					{
						//Checks the token after print statement and left paren
						if (lexAn.tokenInfo[i][j].second == categoryType::STRING_LITERAL)
						{
							cout << lexAn.tokenInfo[i][j].first;
							j++;
						}
						else if ((lexAn.tokenInfo[i][j].second == categoryType::IDENTIFIER) || (lexAn.tokenInfo[i][j].second == categoryType::NUMERIC_LITERAL))
						{
							while (lexAn.tokenInfo[i][j].second != categoryType::COMMA && lexAn.tokenInfo[i][j].second != categoryType::RIGHT_PAREN)
							{
								lexAn.tempExp.push_back(lexAn.tokenInfo[i][j]);
								j++;
							}
							expE.infixToPostfix(inter1, lexAn, expE, pysubi);
							lexAn.tempExp.clear();
						}
						else if (lexAn.tokenInfo[i][j].second == categoryType::COMMA)
						{
							j++;
						}
					}
					//will start a new line once right paren is found.
					cout << endl;
				}
				else
				{
					cout << "Syntax Error: Missing left parenthesis. Please re read your program and try again.";
					inter1.input(inter1, lexAn, expE, pysubi);
				}
			}
			else if ((lexAn.numTokenLine[i]>2)&&(lexAn.tokenInfo[i][j + 1].second == categoryType::ASSIGNMENT_OP))
			{
				//if assigning an identifier to an expression; will be an arith_op at 4th position in string
				if ((lexAn.numTokenLine[i]>3) && (lexAn.tokenInfo[i][j + 3].second == categoryType::ARITH_OP))
				{
					//start at 2 because beginning of expression
					for (int k = 2; k < lexAn.numTokenLine[i]; k++)
					{
						lexAn.tempExp.push_back(lexAn.tokenInfo[i][k]);
					}
					ifAssigned = true;
					expE.infixToPostfix(inter1, lexAn, expE, pysubi);
					ifAssigned = false;
					string result;
					result = to_string(pysubi.finalVal);
					expE.storeTable(lexAn.tokenInfo[i][j].first, result);
					nextLine = true;
					lexAn.tempExp.clear();
				}
				else if ((lexAn.numTokenLine[i] > 4) && (lexAn.tokenInfo[i][j + 4].first == "input"))
				{
					//checks proper syntax with parentheses
					if ((lexAn.tokenInfo[i][lexAn.numTokenLine[i] - 1].second == categoryType::RIGHT_PAREN) && (lexAn.tokenInfo[i][lexAn.numTokenLine[i] - 2].second == categoryType::RIGHT_PAREN))
					{
						userInput = true;
						//j+6 is after left paren from "input("
						if ((lexAn.numTokenLine[i] > 5) && (lexAn.tokenInfo[i][j + 6].second == categoryType::STRING_LITERAL))
						{
							cout << lexAn.tokenInfo[i][j + 6].first;
						}
						string val;
						cin >> val;
						expE.storeTable(lexAn.tokenInfo[i][j].first, val);
						nextLine = true;
					}
					else
					{
						cout << "Improper syntax. Line [" << i << "]. Please re read your file and try again.";
						inter1.input(inter1, lexAn, expE, pysubi);
					}
				}
				//If only var and numeric literal
				else if (lexAn.numTokenLine[i]==3)
				{
					expE.storeTable(lexAn.tokenInfo[i][j].first, lexAn.tokenInfo[i][j + 2].first);
					nextLine = true;
					lexAn.tempExp.clear();
				}
				else
				{
					cout << "Improper syntax. Please re-read file and start again." << endl;
					inter1.input(inter1, lexAn, expE, pysubi);
				}
			}
			else
			{
				cout << "Improper syntax. Please re read your file and try again." << endl;
				inter1.input(inter1, lexAn, expE, pysubi);
			}
		}
	}
	interpMode=false;
	inter1.input(inter1, lexAn, expE, pysubi);
	return(true);
}
