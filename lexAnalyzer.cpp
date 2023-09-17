#include <iostream>
#include<cctype>
#include<utility>
#include<string>
#include<vector>
#include "lexanalyzer.h"
#include "interface.h"

using namespace std;

lexAnalyzer::lexAnalyzer() {
}



void lexAnalyzer::getTokenInfo(Interface& inter1, lexAnalyzer& lexAn)
{
	tokenType finalTokenType;
	string store;
	char token;

	for (int i = 0; i < inter1.programCode.size(); i++)
	{
		pairType startPair;
		tokenLineType whatTokenLineType;

		store = inter1.programCode[i];

		int totalTokens = 0;
		int loopIter = 0;

		for (int j = 0; j < inter1.programCode[i].length(); j++)
		{
			token = store[j];

			//Check if token is a ', also known as string literal, int(39) is the ASCII character for '
			if (store[j] == int(39))
			{
				string helpStr;
				j++;
				while (store[j] != int(39))
				{
					if (store[j] == ')' && j >= store.size() - 1)
					{
						cout << "There is no ending quote in your file" << endl;
						exit(1);
					}
					helpStr += store[j];
					j++;
				}
				helpStr += "";
				startPair = make_pair(helpStr, categoryType::STRING_LITERAL);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("STRING_LITERAL");
				totalTokens++;
			}

			//Check if token is a ", also known as string literal, int(34) is the ASCII character for "
			else if (store[j] == int(34))
			{
				string helpStr;
				j++;
				while (store[j] != int(34))
				{
					if (store[j] == ')' && j >= store.size() - 1)
					{
						cout << "There is no ending quote in your file" << endl;
						exit(1);
					}
					helpStr += store[j];
					j++;
				}
				helpStr += "";
				startPair = make_pair(helpStr, categoryType::STRING_LITERAL);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("STRING_LITERAL");
				totalTokens++;
			}

			//Check if token is a comment
			else if (token == '#')
			{
				string storeComment;
				j++;

				while (j < inter1.programCode[i].length())
				{
					storeComment += store[j];
					j++;
				}
				startPair = make_pair(storeComment, categoryType::COMMENT);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("COMMENT");
				totalTokens++;
			}

			//Check if token is integer
			else if (isdigit(store[j]))
			{
				string newDigits;
				while (isdigit(store[j]) && isdigit(store[j + 1]))
				{
					newDigits += store[j];
					j++;
				}

				newDigits += store[j];
				startPair = make_pair(newDigits, categoryType::NUMERIC_LITERAL);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("NUMERIC_LITERAL");
				totalTokens++;
			}

			//Check if token is the assignment operator
			else if (token == '=')
			{
				startPair = make_pair(token, categoryType::ASSIGNMENT_OP);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("ASSIGNMENT_OP");
				totalTokens++;
			}

			//Check if token is a COMMA-- ","
			else if (token == ',')
			{
				startPair = make_pair(token, categoryType::COMMA);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("COMMA");
				totalTokens++;
			}

			//Check if token is a '==', also known as relational operator
			else if (token == '=' && store[j + 1] == '=' && j < (inter1.programCode.size() - 1))
			{
				startPair = make_pair('==', categoryType::RELATIONAL_OP);
				j++;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("RELATIONAL_OP");
				totalTokens++;
			}

			//Check if token is a '<=', relational operator
			else if (token == '<' && store[j + 1] == '=' && j < (inter1.programCode.size() - 1))
			{
				startPair = make_pair('<=', categoryType::RELATIONAL_OP);
				j++;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("RELATIONAL_OP");
				totalTokens++;
			}

			//Check if token is a '>=', relational operator
			else if (token == '>' && store[j + 1] == '=' && j < (inter1.programCode.size() - 1))
			{
				startPair = make_pair('>=', categoryType::RELATIONAL_OP);
				j++;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("RELATIONAL_OP");
				totalTokens++;
			}

			//Check if token is a '!=', relational operator
			else if (token == '!' && store[j + 1] == '=' && j < (inter1.programCode.size() - 1))
			{
				startPair = make_pair('!=', categoryType::RELATIONAL_OP);
				j++;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("RELATIONAL_OP");
				totalTokens++;
			}

			//Check if token is a '<', relational operator
			else if (token == '<')
			{
				startPair = make_pair(token, categoryType::RELATIONAL_OP);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("RELATIONAL_OP");
				totalTokens++;
			}

			//Check if token is a '>', relational operator
			else if (token == '>')
			{
				startPair = make_pair(token, categoryType::RELATIONAL_OP);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("RELATIONAL_OP");
				totalTokens++;
			}

			//Check if token is logical operator: not
			else if (token == 'n' && (j + 1 < (inter1.programCode.size() - 1)) && store[j + 1] == 'o' && store[j + 2] == 't')
			{
				string storeKey = "not";
				startPair = make_pair(storeKey, categoryType::LOGICAL_OP);
				j += 2;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("LOGICAL_OP");
				totalTokens++;
			}

			//Check if token is logical operator: and
			else if (token == 'a' && (j + 1 < (inter1.programCode.size() - 1)) && store[j + 1] == 'n' && store[j + 2] == 'd')
			{
				string storeKey = "and";
				startPair = make_pair(storeKey, categoryType::LOGICAL_OP);
				j += 2;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("LOGICAL_OP");
				totalTokens++;
			}

			//Check if token is logical operator: or
			else if (token == 'o' && (j  < (inter1.programCode.size() - 1)) && store[j + 1] == 'r')
			{
				string storeKey = "or";
				startPair = make_pair(storeKey, categoryType::LOGICAL_OP);
				j ++;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("LOGICAL_OP");
				totalTokens++;
			}

			//Check if token is a COLON or ':'
			else if (token == ':')
			{
				startPair = make_pair(token, categoryType::COLON);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("COLON");
				totalTokens++;
			}

			//Check if token is keyword: input
			else if ((j + 3 < (inter1.programCode[i].size() - 1)) && store[j] == 'i' && store[j + 1] == 'n' && store[j + 2] == 'p' && store[j + 3] == 'u' && store[j + 4] == 't')
			{
				string storeKey = "input";
				startPair = make_pair(storeKey, categoryType::KEYWORD);
				j += 4;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: while
			else if ((j + 3 < (inter1.programCode[i].size() - 1)) && store[j] == 'w' && store[j + 1] == 'h' && store[j + 2] == 'i' && store[j + 3] == 'l' && store[j + 4] == 'e')
			{
				string storeKey = "while";
				startPair = make_pair(storeKey, categoryType::KEYWORD);
				j += 4;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: else
			else if (token == 'e' && (j + 2 < (inter1.programCode.size() - 1)) && store[j + 1] == 'l' && store[j + 2] == 's' && store[j + 3] == 'e')
			{
				string storeKey = "else";
				startPair = make_pair(storeKey, categoryType::KEYWORD);
				j += 3;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: elif
			else if (token == 'e' && (j + 2 < (inter1.programCode.size() - 1)) && store[j + 1] == 'l' && store[j + 2] == 'i' && store[j + 3] == 'f')
			{
				string storeKey = "elif";
				startPair = make_pair(storeKey, categoryType::KEYWORD);
				j += 3;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: if
			else if (token == 'i' && (j + 2 < (inter1.programCode.size() - 1)) && store[j+1] == 'f')
			{
				string storeKey = "if";
				startPair = make_pair(storeKey, categoryType::KEYWORD);
				j ++;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: int
			else if (token == 'i' && (j + 2 < (inter1.programCode.size() - 1)) && store[j + 1] == 'n' && store[j + 2] == 't')
			{
				string storeKey = "int";
				startPair = make_pair(storeKey, categoryType::KEYWORD);
				j += 2;
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is left parenthesis
			else if (token == '(')
			{
				startPair = make_pair(token, categoryType::LEFT_PAREN);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("LEFT_PAREN");
				totalTokens++;
			}

			//Check if token is right parenthesis
			else if (token == ')')
			{
				startPair = make_pair(token, categoryType::RIGHT_PAREN);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("RIGHT_PAREN");
				totalTokens++;
			}

			//Check if token is a '+', arithmetic operator
			else if (token == '+')
			{
				startPair = make_pair(token, categoryType::ARITH_OP);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("ARITH_OP");
				totalTokens++;
			}

			//Check if token is a '-', arithmetic operator
			else if (token == '-')
			{
				startPair = make_pair(token, categoryType::ARITH_OP);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("ARITH_OP");
				totalTokens++;
			}

			//Check if token is a '*', arithmetic operator
			else if (token == '*')
			{
				startPair = make_pair(token, categoryType::ARITH_OP);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("ARITH_OP");
				totalTokens++;
			}

			//Check if token is a '%', arithmetic operator
			else if (token == '%')
			{
				startPair = make_pair(token, categoryType::ARITH_OP);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("ARITH_OP");
				totalTokens++;
			}

			//Check if token is a '/', arithmetic operator
			else if (token == '/')
			{
				startPair = make_pair(token, categoryType::ARITH_OP);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("ARITH_OP");
				totalTokens++;
			}

			//Checks if token is an indentation, also known as 4 spaces
			else if (token == '/t' || (j + 3 < (inter1.programCode[i].size() - 1)) && store[j] == ' ' && store[j + 1] == ' ' && store[j + 2] == ' ' && store[j + 3] == ' ')
			{
				startPair = make_pair(token, categoryType::INDENT);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("INDENT");
				totalTokens++;
			}

			//Checks if token if an identifier using cctype
			else if (isalpha(store[j]))
			{
				string storeId;
				while (isalpha(store[j]) && isalpha(store[j + 1]))
				{
					storeId += store[j];
					j++;
				}

				storeId += store[j];
				startPair = make_pair(storeId, categoryType::IDENTIFIER);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("IDENTIFIER");
				totalTokens++;
			}

			//Checks if the token is not recognized or unknown
			else if (!isspace(token) && (!isblank(token)))
			{
				startPair = make_pair(token, categoryType::UNKNOWN);
				whatTokenLineType.push_back(startPair);
				whatCategoryVector.push_back("UNKNOWN");
				totalTokens++;
			}
		}
	}
}
/*
void lexAnalyzer::showTokenInfo(Interface& inter1, lexAnalyzer& lexAn)
{
	//nested for loop will display info from read func
	int indexVariable = 0;
	for (int i = 0; i < inter1.programCode.size(); i++)
	{
		cout << "Line#" << i << ":" << endl;
		for (int j = 0; j < lexAn.numTokenLine[i]; j++)
		{
			cout << "Token(" << lexAn.
		}
	}
}
*/
