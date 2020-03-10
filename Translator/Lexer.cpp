#include "Lexer.h"



Lexer::Lexer()
{
	error = Error();
	out = UI();
}

void Lexer::runLexer(string filename)
{
	
	analization(path + filename);
	out.PrintLexemeTable("results/" + filename, lexemeList);
	out.PrintConstantTable("results/" + filename, _constantList);
	out.PrintIdTable("results/" + filename, identifierList);
	error.LexerErrors("results/" + filename);
}

void Lexer::analization(string filename)
{
	int SDCode = 0;
	int MDCode = 501;
	int KWCode = 1001;
	int CNCode = 2001;
	int IDCode = 3001;
	int line = 1;
	int position = 1;
	int in;
	ifstream file;
	file.open(filename, ios::in);
	char inVal = 0;
	file.get(inVal);
	in = int(inVal);
	while (!file.eof())
	{

		switch (getCategory(in))
		{
			case 0:
			{
				if (in == 32)
					position++;
				if (in == 10) {
					line++;
					position = 1;
				}
				file.get(inVal);
				in = int(inVal);
				break;
			}

			case 1:
			{
				string str = "";
				while (getCategory(in) == 1) {
					str += inVal;
					file.get(inVal);
					in = int(inVal);
				}
				std::transform(str.begin(), str.end(), str.begin(), ::toupper);
				if (getCategory(in) == 2) {
					//GENERATE ERROR: NUMBER EXPECTED
					error.GenerateLexerError(2, line, position + str.length(), inVal);
					return;
				}
				if (!contains(str, _constantList)) {
					lexemeList.push_back(Token(line, position, CNCode, str));
					_constantList[str] = CNCode++;

				}
				else
					lexemeList.push_back(Token(line, position, _constantList[str], str));
				position += str.length();
				break;
			}

			case 2:
			{
				string str = "";
				while (getCategory(in) == 1 || getCategory(in) == 2) 
				{
					str += inVal;
					file.get(inVal);
					in = int(inVal);
				}
				std::transform(str.begin(), str.end(), str.begin(), ::toupper);
				if (isKeyWord(str)) {
					lexemeList.push_back(Token(line, position, KWCode++, str));
				}
				else if (!contains(str, identifierList)) {
					lexemeList.push_back(Token(line, position, IDCode, str));
					identifierList[str] = IDCode++;
				}
				else
					lexemeList.push_back(Token(line, position, identifierList[str], str));
				position += str.length();
				break;
			}

			case 3: {
				string temp(1, inVal);
				lexemeList.push_back(Token(line, position++, MDCode++, temp));
				file.get(inVal);
				in = int(inVal);
				break;
			}

			case 4: {
				file.get(inVal);
				in = int(inVal);
				if (inVal != '=') {
					//GENERATE ERROR: = EXPECTED
					error.GenerateLexerError(3, line, ++position, inVal);
					return;
				}
				lexemeList.push_back(Token(line, position, MDCode++, ":="));
				position += 2;
				file.get(inVal);
				in = int(inVal);
				break;
			}

			case 5: {
				file.get(inVal);
				in = int(inVal);
				position++;
				if (inVal != '*') {
					//GENERATE ERROR: * EXPECTED
					error.GenerateLexerError(4, line, position++, inVal);
					return;
				}
				file.get(inVal);
				in = int(inVal);
				position += 2;
				bool prevStar = false;
				while (!(prevStar && inVal == ')')) {
					if ((in == -1) || file.eof()) {
						//GENERATE ERROR: UNCLOSED COMMENT
						error.GenerateLexerError(5, line, --position, inVal);
						return;
					}
					if (in == 10) {
						line++;
						position = 1;
					}
					if (in == '*') {
						prevStar = true;
					}
					file.get(inVal);
					in = int(inVal);
					position++;
				}
				file.get(inVal);
				in = int(inVal);
				break;
			}

			case 6: {
				//GENERATE ERROR: INVALID SYMBOL
				error.GenerateLexerError(1, line, position, inVal);
				return;
			}
		}
	}
	file.close();

}


int Lexer::getCategory(int symb) {
	/* 0 - all whitespaces
	   1 - digits
	   2 - letters (identifiers and keywords)
	   3 - single symbol delimiters
	   4 - multy symbol delimiters (:=)
	   5 - comments
	   6 - invalid symbols */
	if (symb == 32 || symb == 13 || symb == 10) 
	{
		return 0;
	}
	else if (symb >= 48 && symb <= 57) 
	{
		return 1;
	}
	else if (symb >= 65 && symb <= 90 || symb >= 97 && symb <= 122) 
	{
		return 2;
	}
	else if (symb >= 45 && symb < 47 || symb == 59 || symb == 61)
	{
		return 3;
	}
	else if (symb == 58)
	{
		return 4;
	}
	else if (symb == 40)
	{
		return 5;
	}
	else 
	{
		return 6;
	}
}


bool Lexer::contains(string key, map<string, int> dict)
{
	return dict[key] != NULL;
}

bool Lexer::isKeyWord(string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	for (int i = 0; i < 4; i++)
	{
		if (this->_keyWords[i] == str)
		{
			return true;
		}
			
	}
	return false;
}


Lexer::~Lexer()
{
}
