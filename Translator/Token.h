#pragma once
#include <string>
#include <algorithm>

using namespace std;
class Token
{
public:
	Token(int, int, int, string);
	~Token();
	int GetRow();
	int GetPosition();
	int GetCode();
	string GetLexeme();
	string ToString();

private:
	int _row;
	int _position;
	int _code;
	string _lexeme;
};

