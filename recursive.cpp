#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class evaluator
{
private:
	string infix_;
	mutable const char* p;

public:
	void init(string infix) { infix_ = infix; }

	int evaluate() const
	{
		p = infix_.c_str();
		return evaluate_expression();
	}

private:
	int evaluate_factor() const // factor := number | '(' expression ')'
	{
		if (*p == '(') {
			++p;
			int v = evaluate_expression();
			assert(*p == ')');
			++p;
			return v;
		} else if (*p >= '0' && *p <= '9') {
			return *p++ - '0';
		} else {
			assert(false);
		}
	}

	int evaluate_term() const // term := factor { ('*'|'/') factor }
	{
		int a = evaluate_factor();
		while (*p == '*' || *p == '/') {
			char op = *p++;
			int b = evaluate_factor();
			switch (op) {
				default: assert(false);
				case '*': a *= b; break;
				case '/': a /= b; break;
			}
		}
		return a;
	}

	int evaluate_expression() const // expression := term { ('+'|'-') term }
	{
		int a = evaluate_term();
		while (*p == '+' || *p == '-') {
			char op = *p++;
			int b = evaluate_term();
			switch (op) {
				default: assert(false);
				case '+': a += b; break;
				case '-': a -= b; break;
			}
		}
		return a;
	}
};

int main()
{
	string expression = "1*(2+3/4)";

	evaluator e;
	e.init(expression);
	cout << "infix   : " << expression << endl;
	cout << "evaluate: " << e.evaluate() << endl;
	return 0;
}
