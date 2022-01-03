#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result);
bool isOperand(char c);
bool isOperator(char c);
bool paren(string s);
int precidence(char c);
bool checkChar(string s);





int evaluate(string infix, string& postfix, bool& result) {
	result = true;
	
	string s;
	postfix = "";
	for (size_t i = 0; i != infix.size(); i++) {
		if (!isOperand(infix[i]) && !isOperator(infix[i]) && infix[i] != ' ' && infix[i] != '!' && infix[i] != '(' && infix[i] != ')')
			return 1;
		else if (infix[i] != ' ') {
			s += infix[i];
			
			if (s.size() == 0)
				return 1;
		}	
	}
	infix = s;
	char ch;
	stack<char> operatorstack;
	if (infix == "" || !paren(infix) || !checkChar(infix))
		return 1;
	for (size_t i = 0; i < infix.size(); i++) {

		ch = infix.at(i);
		switch (ch) {
		case 'T':
		case 'F':
			postfix += ch;
			if (i + 1 < infix.size() && (infix[i + 1] != '^' && infix[i + 1] != '&' && infix[i+1]!=')')) {
				return 1;
			}
			else
				break;
		case ' ':
			continue;
		case '!':
			operatorstack.push(ch);
			if (i + 1 > infix.size() || (i + 1 < infix.size() && (infix[i + 1] != 'T' && infix[i + 1] != 'F' && infix[i + 1] != '!'
				&& infix[i+1]!='('))) {
				return 1;
			}
			else
				break;
		case '(':
			operatorstack.push(ch);
			if (i + 1 > infix.size() || (i + 1 < infix.size() && (infix[i + 1] != 'T' && infix[i + 1] != 'F' && infix[i + 1] != '!'
				&&infix[i+1]!='('))) {
				return 1;
			}
			else
				
			break;
		case ')':
			if (i + 1 < infix.size() && (infix[i + 1] != '^' && infix[i + 1] != '&' && infix[i+1]!=')')) {
				return 1;
			}
			while (!operatorstack.empty() && operatorstack.top() != '(') {
				postfix += operatorstack.top();
				operatorstack.pop();

			}
			operatorstack.pop();
				break;
		case '&':
		case '^':
			if (i + 1 >= infix.size() || (i + 1 < infix.size() && (infix[i + 1] != 'T' && infix[i + 1] != 'F' && infix[i + 1] != '!' && infix[i + 1] != '(')))
				return 1;
			else {
				while (!operatorstack.empty() && operatorstack.top() != '(' && precidence(ch) <= precidence(operatorstack.top())) {
					postfix += operatorstack.top();
					operatorstack.pop();
				}
				operatorstack.push(ch);
				break;
			}

		}	

	}
	while (!operatorstack.empty()) {
		postfix += operatorstack.top();
		operatorstack.pop();
	}

	stack<bool> operandstack;
	
	bool operand1;
	bool operand2;
	
	bool c;
	for (int i = 0; i != postfix.size();i++) {
		char cht = postfix.at(i);
		if (isOperand(cht)) {
			if (cht == 'F') 
				 c = false;
			else
				 c = true;
			
			operandstack.push(c);
		}
		else {
			operand2 = operandstack.top();
			operandstack.pop();
				if (cht != '!') {
					operand1 = operandstack.top();
					operandstack.pop();
				}
			if (cht == '!') {
				operandstack.push(!operand2);
			}
			else if (cht == '^' && operand1 == true && operand2 == true) {
				operandstack.push(false);
			
			}
			else if (cht == '^') {
				operandstack.push(operand1 || operand2);
			}
			else if (cht == '&') {
				operandstack.push((operand2 && operand1));
			}
		}
	}
	result = operandstack.top();
	return 0;

}

int precidence(char c) {
	if (c == '!')
		return 4;
	else if (c == '&')
		return 3;
	else if (c == '^')
		return 2;
	else
		return 0;
}

bool isOperand(char c) {
	if (c == 'F' || c == 'T')
		return true;
	else
		return false;
}
bool isOperator(char c) {
	if (c == '&' || c == '^')
		return true;
	else
		return false;
}

bool paren(string s) {
	string t;
	for (int i = 0; i != s.size();i++) {
		if (s.at(i) == '(' || s.at(i) == ')')
			t += s[i];

	}
	stack <char> a;
	//char ch;
	for (int i = 0; i != t.size();i++) {
		if (t[i] == '(') {
			a.push(t[i]);
		}
		else {
			if (a.empty()) {
				return false;
			}
			else if (t[i] == ')') {
				//ch = a.top();
				a.pop();
			}
		}
	}
	if (a.empty())
		return true;
	else
		return false;

}

bool checkChar(string s) {
	int length = s.size();
	if (s[0] == '^' || s[0] == '&') {
		return false;
	}
	for (int i = 0; i < length; i++) {
		if (i == length - 1 && (!isOperand(s[i]) && s[i]!=')')) {
			return false;
		}
	}
	return true;
}

int main() {

	

}