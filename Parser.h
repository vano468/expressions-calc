#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Parser {
	vector<vector<string>> Grammar;
	vector<vector<vector<string>>> CYK;
	void GrammarInit(void); // Чтение грамматики в нормальной форме Хомского из файла Config.ini. Кидает исключение типа *char если файла нет;
	vector<vector<string>> StringToVecVecStrConvert(string search);
public:
	bool CYKParser(string search); // Функция принимает в качестве аргумента строку терминальных символов и реализует алгоритм синтаксического анализа Кока-Янгера-Косами. Возвращает true, если строка принадлежит грамматике, иначе else;
	Parser(void);
	~Parser(void);
};
