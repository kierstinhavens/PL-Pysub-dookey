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

void lexAnalyzer::clearTokenInfo()
{
	tokenInfo.clear();
	whatCategoryVector.clear();
	numTokenLine.clear();
}

void lexAnalyzer::getTokenInfo(Interface& inter1, lexAnalyzer& lexAn)
{
	tokenType finalTokenType;
	string store;
	char token;

	whatCategoryVector.clear();

	for (int i = 0; i < inter1.programCode.size(); i++)
	{
		pairType tempPair;
		tokenLineType whatTokenLineType;

		store = inter1.programCode[i];

		int totalTokens = 0;
	
		int j = 0;
		while (j < store.length())
		{
			token = store[j];

			//Check if token is a ', also known as string literal, int(39) is the ASCII character for '
			if (store[j] == int(39))
			{
				string tempStr;
				j++;
				while (store[j] != int(39))
				{
					if (store[j] == ')' && j >= store.size() - 1)
					{
						cout << "There is no ending quote in your file" << endl;
						exit(1);
					}
					tempStr += store[j];
					j++;
				}
				tempStr += "";
				tempPair.first = tempStr;
				tempPair.second = categoryType::STRING_LITERAL;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("STRING_LITERAL");
				totalTokens++;
			}

			//Check if token is a ", also known as string literal, int(34) is the ASCII character for "
			else if (store[j] == int(34))
			{
				string tempStr;
				j++;
				while (store[j] != int(34))
				{
					if (store[j] == ')' && j >= store.size() - 1)
					{
						cout << "There is no ending quote in your file" << endl;
						exit(1);
					}
					tempStr += store[j];
					j++;
				}
				tempStr += "";
				tempPair.first = tempStr;
				tempPair.second = categoryType::STRING_LITERAL;
				whatTokenLineType.push_back(tempPair);
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
				tempPair.first = storeComment;
				tempPair.second = categoryType::COMMENT;
				whatTokenLineType.push_back(tempPair);
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
				tempPair.first = newDigits;
				tempPair.second = categoryType::NUMERIC_LITERAL;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("NUMERIC_LITERAL");
				totalTokens++;
			}

			//Check if token is a COMMA-- ","
			else if (token == ',')
			{
				tempPair.first = token;
				tempPair.second = categoryType::COMMA;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("COMMA");
				totalTokens++;
			}

			//Check if token is a '==', also known as relational operator
			else if (token == '=' && store[j + 1] == '=')
			{
				tempPair.first = "==";
				tempPair.second = categoryType::RELATIONAL_OP;
				j++;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("RELATIONAL_OP");
				totalTokens++;
			}

			//Check if token is a '<=', relational operator
			else if (token == '<' && store[j + 1] == '=')
			{
				tempPair.first = "<=";
				tempPair.second = categoryType::RELATIONAL_OP;
				j++;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("RELATIONAL_OP");
				totalTokens++;
			}

			//Check if token is a '>=', relational operator
			else if (token == '>' && store[j + 1] == '=')
			{
				tempPair.first = ">=";
				tempPair.second = categoryType::RELATIONAL_OP;
				j++;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("RELATIONAL_OP");
				totalTokens++;
			}

			//Check if token is a '!=', relational operator
			else if (token == '!' && store[j + 1] == '=')
			{
				tempPair.first = '!=';
				tempPair.second = categoryType::RELATIONAL_OP;
				j++;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("RELATIONAL_OP");
				totalTokens++;
			}

			//Check if token is a '<', relational operator
			else if (token == '<')
			{
				tempPair.first = token;
				tempPair.second = categoryType::RELATIONAL_OP;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("RELATIONAL_OP");
				totalTokens++;
			}

			//Check if token is a '>', relational operator
			else if (token == '>')
			{
				tempPair.first = token;
				tempPair.second = categoryType::RELATIONAL_OP;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("RELATIONAL_OP");
				totalTokens++;
			}

			//Check if token is the assignment operator
			else if (token == '=')
			{
				tempPair.first = token;
				tempPair.second = categoryType::ASSIGNMENT_OP;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("ASSIGNMENT_OP");
				totalTokens++;
			}

			//Check if token is logical operator: not
			else if (token == 'n' && store[j + 1] == 'o' && store[j + 2] == 't')
			{
				string storeKey = "not";
				tempPair.first = storeKey;
				tempPair.second = categoryType::LOGICAL_OP;
				j += 2;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("LOGICAL_OP");
				totalTokens++;
			}

			//Check if token is logical operator: and
			else if (token == 'a' && store[j + 1] == 'n' && store[j + 2] == 'd')
			{
				string storeKey = "and";
				tempPair.first = storeKey;
				tempPair.second = categoryType::LOGICAL_OP;
				j += 2;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("LOGICAL_OP");
				totalTokens++;
			}

			//Check if token is logical operator: or
			else if (token == 'o' && store[j + 1] == 'r')
			{
				string storeKey = "or";
				tempPair = make_pair(storeKey, categoryType::LOGICAL_OP);
				j++;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("LOGICAL_OP");
				totalTokens++;
			}

			//Check if token is a COLON or ':'
			else if (token == ':')
			{
				tempPair.first = token;
				tempPair.second = categoryType::COLON;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("COLON");
				totalTokens++;
			}

			//Check if token is keyword: input
			else if (store[j] == 'i' && store[j + 1] == 'n' && store[j + 2] == 'p' && store[j + 3] == 'u' && store[j + 4] == 't')
			{
				string storeKey = "input";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j += 4;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: false
			else if (store[j] == 'F' && store[j + 1] == 'a' && store[j + 2] == 'l' && store[j + 3] == 's' && store[j + 4] == 'e')
			{
				string storeKey = "False";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j += 4;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token keyword: True
			else if (store[j] == 'T' && store[j + 1] == 'r' && store[j + 2] == 'u' && store[j + 3] == 'e')
			{
				string storeKey = "True";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j += 3;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: break
			else if (store[j] == 'b' && store[j + 1] == 'r' && store[j + 2] == 'e' && store[j + 3] == 'a'&& store[j+4]=='k')
			{
				string storeKey = "break";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j += 4;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: class
			else if (store[j] == 'c' && store[j + 1] == 'l' && store[j + 2] == 'a' && store[j + 3] == 's' && store[j + 4] == 's')
			{
				string storeKey = "break";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j += 4;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: return
			else if (store[j] == 'r' && store[j + 1] == 'e' && store[j + 2] == 't' && store[j + 3] == 'u' && store[j + 4] == 'r' && store[j+5]=='n')
			{
				string storeKey = "return";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j += 5;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: for
			else if (store[j] == 'f' && store[j + 1] == 'o' && store[j + 2] == 'r')
			{
				string storeKey = "for";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j += 2;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: import
			else if (store[j] == 'i' && store[j + 1] == 'm' && store[j + 2] == 'p' && store[j + 3] == 'o' && store[j + 4] == 'r' && store[j + 5] == 't')
			{
				string storeKey = "import";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j += 5;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: while
			else if (store[j] == 'w' && store[j + 1] == 'h' && store[j + 2] == 'i' && store[j + 3] == 'l' && store[j + 4] == 'e')
			{
				string storeKey = "while";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j += 4;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: else
			else if (token == 'e' && store[j + 1] == 'l' && store[j + 2] == 's' && store[j + 3] == 'e')
			{
				string storeKey = "else";
				tempPair.first = storeKey; 
				tempPair.second= categoryType::KEYWORD;
				j += 3;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: elif
			else if (token == 'e' && store[j + 1] == 'l' && store[j + 2] == 'i' && store[j + 3] == 'f')
			{
				string storeKey = "elif";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j += 3;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: if
			else if (token == 'i' && store[j+1] == 'f')
			{
				string storeKey = "if";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j ++;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword 'print'
			else if (store[j] == 'p' && store[j + 1] == 'r' && store[j + 2] == 'i' && store[j + 3] == 'n' && store[j + 4] == 't')
			{
				string storeKey = "print";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j += 4;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is keyword: int
			else if (store[j] == 'i' && store[j + 1] == 'n' && store[j + 2] == 't')
			{
				string storeKey = "int";
				tempPair.first = storeKey;
				tempPair.second = categoryType::KEYWORD;
				j += 2;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("KEYWORD");
				totalTokens++;
			}

			//Check if token is left parenthesis
			else if (token == '(')
			{
				tempPair.first = token;
				tempPair.second = categoryType::LEFT_PAREN;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("LEFT_PAREN");
				totalTokens++;
			}

			//Check if token is right parenthesis
			else if (token == ')')
			{
				tempPair = make_pair(token, categoryType::RIGHT_PAREN);
				tempPair.first = token;
				tempPair.second = categoryType::RIGHT_PAREN;
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("RIGHT_PAREN");
				totalTokens++;
			}

			//Check if token is a arithmetic operator
			else if (token == '%'|| token=='/' || token=='*' || token== '-' || token=='+')
			{
				tempPair = make_pair(token, categoryType::ARITH_OP);
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("ARITH_OP");
				totalTokens++;
			}

			//Checks if token is an indentation, also known as 4 spaces
			else if (token == '/t' || store[j] == ' ' && store[j + 1] == ' ' && store[j + 2] == ' ' && store[j + 3] == ' ')
			{
				tempPair = make_pair(token, categoryType::INDENT);
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("INDENT");
				totalTokens++;
			}

			//Checks if token if an identifier/variable using cctype
			else if (isalpha(store[j])|| store[j]=='_') 
			{
				string storeId;
				//This ensures that any digit that is in the variable name is included in the identifier category and not classified as a numeric literal
				while ((isalpha(store[j]) || store[j]=='_') && (isalpha(store[j+1])))
				{
					storeId += store[j];
					j++;
				}
				storeId += store[j];
				tempPair = make_pair(storeId, categoryType::IDENTIFIER);
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("IDENTIFIER");
				totalTokens++;
			}

			//Checks if the token is not recognized or unknown
			else if (!isspace(token) && (!isblank(token)))
			{
				tempPair = make_pair(token, categoryType::UNKNOWN);
				whatTokenLineType.push_back(tempPair);
				whatCategoryVector.push_back("UNKNOWN");
				totalTokens++;
			}
			j++;
		}

		lexAn.tokenInfo.push_back(whatTokenLineType);
		lexAn.numTokenLine.push_back(1);
		lexAn.numTokenLine[i] = totalTokens;
	}
}


void lexAnalyzer::showTokenInfo(Interface& inter1, lexAnalyzer& lexAn) 
{

	// Seperate counter for categories
	int categoryTotal = 0;

	// nested for loop will display info from read function
	for (int i = 0; i < inter1.programCode.size(); i++) 
	{
		cout << "Line #" << i << ":" << endl;

		for (int j = 0; j < lexAn.numTokenLine[i]; j++) 
		{
			cout << "Token[" << j << "]: ";
			cout << lexAn.tokenInfo[i][j].first << " - " << lexAn.whatCategoryVector[categoryTotal] << endl;
			categoryTotal++;
		}
		cout << "------------------------------------------------------------------" << endl;
	}
}
