#include "UI.h"



UI::UI()
{
}

void UI::PrintLexemeTable(string filename, vector<Token> list)
{
	ofstream out(filename, ios::app);
	out << "LEXEME TABLE: \n";
	for (int i = 0; i < list.size(); i++)
	{
		out << list[i].ToString() << endl;
	}
	out.close();
}


void UI::PrintConstantTable(string filename, map<string, int> dict)
{
	ofstream out(filename, ios::app);
	out << "\nCONSTANTS TABLE: \n";
	for (auto item : dict)
	{
		out << "|" + item.first + "|" + to_string(item.second) + "|\n";
	}
	out.close();
}


void UI::PrintIdTable(string filename, map<string, int> dict)
{
	ofstream out(filename, ios::app);
	out << "\nIDENTIFIERS TABLE: \n";
	for (auto item : dict)
	{
		out << "|\t" + item.first + "|\t" + to_string(item.second) + "|\n";
	}
	out.close();
}
UI::~UI()
{
}
