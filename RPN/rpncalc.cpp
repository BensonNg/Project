/* CSCI1520
* Assignment:6
* Student ID:1155034528
* Name      :Ng Yin Hei
* E-mail adr:bensonyongvanich@gmail.com
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "Stack.h"
using namespace std;

int main() {
	string input;
	string s1;
	string s2;
	int pos = 0, temp, depth;

	cout << "Enter an RPN expression: ";
	while (input.find(" = ") == -1) {				//make sure the iterations can be stopped by s1="="
		getline(cin, s2);							//prevent the case of "*=***" pass this loop
		input = input + s2 + " ";					//seperate each input string
		if (input.find("= ") == 0)					//prevent the error of the case input="= *****"
			break;
	}
	Stack Stack;
	while (s1 != "=") {
		do {
			pos = input.find(" ");					//cut out a substring s1 of each iterations before each " "
			s1 = input.substr(0, pos);
			input.erase(0, pos + 1);
			if (s1 == "=")
				break;
		} while (s1 == "");
		if (s1 == "=");								//for the case input="= *****"
		else if (s1 == "+") {
			temp = Stack.pop();
			temp += Stack.pop();					//the cases are cummutative except division and subtration
			Stack.push(temp);						//a+b=b+a a*b=b*a so that temp += Stack.pop is same with the ans.
		}
		else if (s1 == "-") {
			temp = Stack.pop();
			temp = Stack.pop() - temp;				//arrangement are important in subtration and division cases
			Stack.push(temp);
		}
		else if (s1 == "*") {
			temp = Stack.pop();
			temp *= Stack.pop();
			Stack.push(temp);
		}
		else if (s1 == "/") {
			temp = Stack.pop();
			temp = Stack.pop() / temp;
			Stack.push(temp);
		}
		else {
			temp = atoi(s1.c_str());				//convert other case in integer
			Stack.push(temp);
		}
	}
	depth = Stack.getDepth();						//if depth = 1 => result
	temp = Stack.pop();								//if depth = 0 => pop print out empty
	if (depth == 1)									//if depth >1  => invalid 
		cout << "Result = " << temp << endl;
	else
		cout << "Invalid input!" << endl;

	return 0;
}