//Project Identifier: 1CAEF3A0FEDD0DEC26BA9808C69D4D22A9962768

/**
 * hello.cpp
 *
 * Says hello to the world.
 */


#include <iostream>
#include <stack>
#include <iterator>
using namespace std;

int main() {
	/*
	Need to decrease memory used:
	- is almost definitely in the reading in part
	
	*/
	ios_base::sync_with_stdio(false);
	/*string text;
	string word;
	while (cin >> word >> ws) {
		text += word;
	}*/

	stack<char> text;
	char c = 0;
	bool isBalanced = true;
	while (cin.get(c)) {
		if (c == '{' || c == '[' || c == '(' ){
			text.push(c);
		}
		if (c == ')') {
			if (text.empty()) {
				isBalanced = false;
				break;
			}
			if (text.top() == '(') text.pop();
			else {
				isBalanced = false;
				break;
			}
		}
		if (c == '}') {
			if (text.empty()) {
				isBalanced = false;
				break;
			}
			if (text.top() == '{') text.pop();
			else {
				isBalanced = false;
				break;
			}
		}
		if (c == ']') {
			if (text.empty()) {
				isBalanced = false;
				break;
			}
			if (text.top() == '[') text.pop();
			else {
				isBalanced = false;
				break;
			}
		}
			
	}

	if (isBalanced && text.empty()) cout << "Balanced\n";
	else cout << "Not balanced\n";
}