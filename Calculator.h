#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "Scanner.h"
#include "Parser.h"
using namespace std;

class Calculator
{
	double StrToDouble(string str); // Функция преобразует строку в число;
	double EvalBinOperation(double first, double second, string operation); // Функция вычисляет выражение с бинарной операцией и возвращает его значение;
	double EvalUnOperation(double arg, string operation); // Функция вычисляет выражение с унарной операцией и возвращает его значение;
	int Priority(string operation); // Функция принимает аргумент - строка с операцией и возвращает её приоритет;
	bool CheckCorrectExpression(string expression);  // По выражению создает строку терминальных символов и проверяет её на принадлежность грамматике;
public:
	Calculator(void);
	~Calculator(void);
	double Eval(string expression); // Функция проверяет корректность введенного выражения и вычисляет его. Для этого используется алгоритм Дейкстры (Алгоритм сортировочной станции) с одновременным вычислением значений при выталкивании операций из стека. Результат выражения - последнее число на стеке чисел. Кидает исключение типа *char если введенное выражение - некорректно;
};
