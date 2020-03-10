#include "Error.h"



Error::Error()
{
}


void Error::Reset()
{
	this->lexMessage = "Lexer: No Errors detected";
}

void Error::GenerateLexerError(int type, int line, int col, char symb)
{
	string tmp(1, symb);
	this->lexMessage = "Lexer: Error (line " + to_string(line) + ", column " + to_string(col) + "): ";
	switch (type)
	{
		case 1: 
		{
			this->lexMessage += "Invalid symbol '" + tmp + "'";
			break;
		}
		case 2:
		{
			this->lexMessage += "Number expected, but detected '" + tmp + "'";
			break;
		}
		case 3:
		{
			this->lexMessage += "'=' expected";
			break;
		}
		case 4:
		{
			this->lexMessage += "'*' expected";
		}
		case 5:
		{
			this->lexMessage += "unclosed comment";
			break;
		}
	}
}


void Error::LexerErrors(string filename)
{
	ofstream out(filename, ios::app);
	out << endl << this->lexMessage << endl;
	out.close();
}
Error::~Error()
{
}
