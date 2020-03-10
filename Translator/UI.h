#pragma once
#include <vector>
#include <iostream>
#include "Token.h"
#include <fstream>
#include <map>

using namespace std;

class UI
{
public:
	UI();
	void PrintLexemeTable(string, vector<Token>);
	void PrintConstantTable(string, map<string, int>);
	void PrintIdTable(string, map<string, int>);
	~UI();
};

