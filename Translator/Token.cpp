#include "Token.h"

Token::Token(int r, int p, int c, string l)
{
	_row = r;
	_position = p;
	_code = c;
	_lexeme = l;

}


int Token::GetRow()
{
	return this->_row;
}


int Token::GetPosition()
{
	return this->_position;
}


int Token::GetCode()
{
	return this->_code;
}

string Token::GetLexeme()
{
	return this->_lexeme;
}

string Token::ToString()
{
	return "|" + to_string(_row) + 
		"\t" + to_string(_position) + 
		"\t" + to_string(_code) + "|" + _lexeme;
}


Token::~Token()
{
}
