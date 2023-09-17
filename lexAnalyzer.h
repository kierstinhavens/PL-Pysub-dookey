#ifndef LEXANALYZER_H
#define LEXANALYZER_H

#include "interface.h"
#include <iostream>
#include <vector>
#include <string>

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

public:
    void getTokenInfo(Interface&, lexAnalyzer&);
    void showTokenInfo(Interface&, lexAnalyzer&);
    void clearTokenInfo(Interface&, lexAnalyzer&);

    lexAnalyzer();
private:
    typedef vector<vector<pair<string, categoryType>>> tokenType;
    typedef vector<pair<string, categoryType>> tokenLineType;
    typedef pair<string, categoryType> pairType;
    tokenType tokenInfo;

    vector<int> numTokenLine;
    vector<string> whatCategoryVector;
};

#endif
