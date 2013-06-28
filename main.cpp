#include "Calculator.h"
#include <time.h>
#include <iostream>
using namespace std;

int main()
{	
	clock_t time;
	Calculator a;
	string expression;
	cout << "Enter expression to compute: ";
	char symb;
	do {
		cin.get(symb);
		if (symb != '/t' && symb != ' ')
			expression += symb;
	} while (symb != '\n');
	time = clock();
	try {
		cout << "Result: " << setprecision(10) << a.Eval(expression) << endl;
	} catch (char *reason) {
		cerr << reason << endl;
		return 1;
	}
	time = clock() - time;
	cout << "Computation time: " << (double)time/CLOCKS_PER_SEC << endl;
	return 0;
}
