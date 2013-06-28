#include "Calculator.h"

Calculator::Calculator(void)
{
}

Calculator::~Calculator(void)
{
}

double Calculator::Eval(string expression)
{
	if (!CheckCorrectExpression(expression))
		throw "Incorrect expression input...";
	Scanner scan(expression);
	stack<string> operation;
	stack<double> numbers;
	bool prev = true;
	while (scan.ReadNextToken(prev)) {
		char type = scan.GetCurrentTokenType();
		string token = scan.GetCurrentToken();
		if (type == 'd') { 
			prev = false;
			numbers.push(StrToDouble(token));
		}
		else {
			prev = true;
			if (token == ")") {
				prev = false;
				while (operation.top() != "(") {
					if (operation.top() == "sin" || operation.top() == "cos") {
						double arg = numbers.top(); numbers.pop();
						numbers.push(EvalUnOperation(arg, operation.top()));
					} else {
						double second = numbers.top(); numbers.pop();
						double first  = numbers.top(); numbers.pop();
						numbers.push(EvalBinOperation(first, second, operation.top()));
					}
					operation.pop();
				}
				operation.pop();
				continue;
			}
			else while (!operation.empty() && token != "(" && (Priority(token) >= Priority(operation.top()))) {
					if (operation.top() == "sin" || operation.top() == "cos") {
						double arg = numbers.top(); numbers.pop();
						numbers.push(EvalUnOperation(arg, operation.top()));
					} else {
						double second = numbers.top(); numbers.pop();
						double first  = numbers.top(); numbers.pop();
						numbers.push(EvalBinOperation(first, second, operation.top()));
					}
					operation.pop();
				} 
			operation.push(token);
		}
	}
	while (!operation.empty()) {
		if (operation.top() != "(" ) {
			if (operation.top() == "sin" || operation.top() == "cos") {
				double arg = numbers.top(); numbers.pop();
				numbers.push(EvalUnOperation(arg, operation.top()));
			} else {
				double second = numbers.top(); numbers.pop();
				double first  = numbers.top(); numbers.pop();
				numbers.push(EvalBinOperation(first, second, operation.top()));
			}
		}
		operation.pop();
	}
	return numbers.top();
}

int Calculator::Priority(string operation)
{
	if (operation == "(") return 4;
	else if (operation == "+" || operation == "-") return 3;
	else if (operation == "*" || operation == "/") return 2;
	else if (operation == "^") return 1;
	else if (operation == "sin" || operation == "cos") return 0;
	else return -1;
}

bool Calculator::CheckCorrectExpression(string expression)
{
	Scanner scan(expression);
	Parser parse;
	string terminals;
	bool prev = true; // Если предыдущий токен - не оператор, тогда, если считываем минус, то считаем его бинарным, иначе - унарным. После закрывающей скобки может идти только бинарный минус;
	while (scan.ReadNextToken(prev)) {
		char type = scan.GetCurrentTokenType();
		string token = scan.GetCurrentToken();
		switch (type) {
		case 'd': terminals += 'd'; prev = false; break;
		case 's': terminals += 's'; prev = true;  break;
		case 'c': terminals += 'c'; prev = true;  break;
		case 'o': terminals += token;
			if (token == ")") prev = false;
			else prev = true;
			break;
		}
	}
	if (parse.CYKParser(terminals)) return true;
	else return false;
}

double Calculator::StrToDouble(string str)
{
	std::istringstream stm;
	stm.str(str);
	double doub;
	stm >> doub;
	return doub;
}

double Calculator::EvalBinOperation(double first, double second, string operation)
{
	if (operation == "+") return first + second;
	if (operation == "-") return first - second;
	if (operation == "*") return first * second;
	if (operation == "/") return first / second;
	if (operation == "^") return pow(first, second);
	return 0;
}

double Calculator::EvalUnOperation(double arg, string operation)
{
	if (operation == "sin") return sin(arg);
	if (operation == "cos") return cos(arg);
	return 0;
}
