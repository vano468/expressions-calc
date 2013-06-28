#include "Scanner.h"

Scanner::Scanner(string ex)
{
	expression = ex;
	i = 0;
}

Scanner::~Scanner(void)
{
}

bool Scanner::ReadNextToken(bool prev)
{
	token.clear();
	state = st_start;
	if (expression[i] == '\n') return false;
	while (expression[i] != '\n') {
		if (state == st_sin   || state == st_cos)      break;
		if (state == st_const || state == st_operator) break;
		if (state == st_undef)
			throw "Incorrect expression input...";
		if (expression[i] == ' ') { ++i; continue; }

		switch (state)
		{
		case st_start:
			if (expression[i] == 's')        state = st_s;
			else if (expression[i] == 'c')   state = st_c;
			else if (expression[i] == '.')   state = st_point;
			else if (isdigit(expression[i])) state = st_const1;
			else if (prev && expression[i] == '-')
											 state = st_minus;
			else if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '/' ||
					  expression[i] == ')' || expression[i] == '(' || expression[i] == '*' ||
					  expression[i] == '^')) state = st_operator;
			else state = st_undef;
			break;
		case st_s:
			if (expression[i] == 'i') state = st_i;
			else state = st_undef;
			break;
		case st_i:
			if (expression[i] == 'n') state = st_sin;
			else state = st_undef;
			break;
		case st_c:
			if (expression[i] == 'o') state = st_o;
			else state = st_undef;
			break;
		case st_o:
			if (expression[i] == 's') state = st_cos;
			else state = st_undef;
			break;
		case st_const1:
			if (expression[i] == '.') state = st_point;
			else if (!isdigit(expression[i]))
				if (!(expression[i] == '+' || expression[i] == '-' || expression[i] == '/' ||
					  expression[i] == '*' || expression[i] == '^' || expression[i] == ')'))
				{ state = st_undef; continue; }
				else { state = st_const; continue; }
			break;
		case st_point:
			if (isdigit(expression[i])) state = st_const2;
			else
				if (!(expression[i] == '+' || expression[i] == '-' || expression[i] == '/' ||
				      expression[i] == '*' || expression[i] == '^' || expression[i] == ')'))
				{ state = st_undef; continue; }
				else { state = st_const; continue; }
			break;
		case st_const2:
			if (!isdigit(expression[i]))
				if (!(expression[i] == '+' || expression[i] == '-' || expression[i] == '/' ||
					  expression[i] == '*' || expression[i] == '^' || expression[i] == ')'))
				{ state = st_undef; continue; }
				else { state = st_const; continue; }
			break;
		case st_minus:
			if (isdigit(expression[i])) state = st_const1;
			else { state = st_undef; continue; }
			break;
		}
		token += expression[i];
		i++;
	}
	return true;
}

string Scanner::GetCurrentToken()
{
	return token;
}

char Scanner::GetCurrentTokenType()
{
	if (state == st_sin)      return 's'; 
	if (state == st_cos)      return 'c';
	if (state == st_const  ||
		state == st_const1 ||
		state == st_const2 ||
		state == st_point)    return 'd'; // d == digit
	if (state == st_operator) return 'o';
	return -1;
}
