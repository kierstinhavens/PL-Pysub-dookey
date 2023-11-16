#ifndef LEXANALYZER_H
#define LEXANALYZER_H

#include "interface.h"
#include "expevaluator.h"
#include "interpreter.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

enum class categoryType
{
    KEYWORD,
    IDENTIFIER,
    STRING_LITERAL,
    NUMERIC_LITERAL,
    ASSIGNMENT_OP,
    ARITH_OP,
    LOGICAL_OP,
    RELATIONAL_OP,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COMMA,
    COMMENT,
    INDENT,
    UNKNOWN
};

class lexAnalyzer
{
    friend class Interface;
    friend class expEvaluator;
    friend class Interpreter;

public:
    void getTokenInfo(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);
    void showTokenInfo(Interface&, lexAnalyzer&, expEvaluator&, Interpreter&);
    void clearTokenInfo();

    lexAnalyzer();
private:
    typedef vector<vector<pair<string, categoryType>>> tokenType;
    typedef vector<pair<string, categoryType>> tokenLineType;
    typedef pair<string, categoryType> pairType;
    tokenType tokenInfo;

    vector<int> numTokenLine;
    vector<string> whatCategoryVector;
    tokenLineType tempExp;
};

#endif
