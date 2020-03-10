#pragma once
#include "Token.h"
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Error.h"
#include "UI.h"
using namespace std;
class Lexer
{
	public:
		Lexer();
		void runLexer(string filename);
		~Lexer();

	private:
		string _keyWords[4] = { "PROGRAM", "BEGIN", "END", "CONST" };
		map<string, int> _constantList;
		map<string, int> identifierList;
		vector<Token> lexemeList;
		Error error;
		UI out;
		string path = "test/";

		void analization(string );
		int getCategory(int );
		bool contains(string key, map<string, int> dict);
		bool isKeyWord(string);
};

