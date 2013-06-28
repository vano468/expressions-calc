#pragma once
#include <string>
using namespace std;

class Scanner
{
	string expression;
	string token;
	unsigned int i;
	enum States { // Состояния детерминированного автомата для выделения лексем
		st_start,
		st_c,
		st_o,
		st_cos,
		st_s,
		st_i,
		st_sin,
		st_const,
		st_const1,
		st_point,
		st_const2,
		st_minus,
		st_operator,
		st_undef,
	};
	States state;
public:
	Scanner(string ex);
	~Scanner(void);
	bool ReadNextToken(bool prev); // Фунция реализует детерминированный конечный автомат передвигаясь по состояниям. Читает следующий токен при обращении и возвращает true, если прочитано успешно и else, если прочитать не удалось. Принимает аргумент типа bool: если он true, то предыдущий прочититанный токен был операцией, иначе false. Кидает исключение типа *char если обнаружена ошибка при вводе;
	char GetCurrentTokenType(void); // Возвращает тип последнего прочитанного токена;
	string GetCurrentToken(void); // Возвращает последний прочитанный токен;
};
