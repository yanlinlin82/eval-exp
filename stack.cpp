#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

class evaluator
{
private:
	string infix_;
	string postfix_;

public:
	void init(string infix) { infix_ = infix; convert(); }

	const string& postfix() const { return postfix_; }

	int evaluate() const // from postfix
	{
		vector<int> stack;
		for (const char* p = postfix_.c_str(); *p; ++p) {
			if (*p >= '0' && *p <= '9') {
				stack.push_back(*p - '0');
			} else {
				int b = stack.back(); stack.pop_back();
				int a = stack.back(); stack.pop_back();
				switch (*p) {
				case '+': stack.push_back(a + b); break;
				case '-': stack.push_back(a - b); break;
				case '*': stack.push_back(a * b); break;
				case '/': stack.push_back(a / b); break;
				}
			}
		}
		return stack.back();
	}

private:
	void convert() // infix => postfix
	{
		vector<char> stack{'#'};
		postfix_.clear();
		for (const char* p = infix_.c_str(); *p; ++p) {
			if (*p >= '0' && *p <= '9') {
				postfix_ += *p;
			} else if (*p == '(') {
				stack.push_back(*p);
			} else if (*p == ')') {
				while (stack.back() != '(') {
					postfix_ += stack.back(); stack.pop_back();
				}
				stack.pop_back();
			} else {
				while (precedence(*p) <= precedence(stack.back())) {
					postfix_ += stack.back(); stack.pop_back();
				}
				stack.push_back(*p);
			}
		}
		while (stack.back() != '#') {
			postfix_ += stack.back(); stack.pop_back();
		}
	}

	static int precedence(char op)
	{
		switch (op) {
		default: assert(false);
		case '(':
		case '#': return 1;
		case '+':
		case '-': return 2;
		case '*':
		case '/': return 3;
		}
	}
};

int main()
{
	string expression = "1*(2+3/4)";

	evaluator e;
	e.init(expression);
	cout << "infix   : " << expression << endl;
	cout << "postfix : " << e.postfix() << endl;
	cout << "evaluate: " << e.evaluate() << endl;
	return 0;
}
