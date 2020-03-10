#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Error
{
public:
	string lexMessage = "Lexer: No Errors detected";
	bool parsError = false;

	Error();
	void Reset();
	void GenerateLexerError(int, int, int, char);
	void LexerErrors(string);
	~Error();

};

